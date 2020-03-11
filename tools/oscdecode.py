#! /usr/bin/env python3
'''
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
'''
"""This script decodes OSC/DCDI tracebacks.

October 2018, Yongkui Han

Usage: oscdecode.py -b binaryfile -t traceback_str -d rootdir -c configfile -s customized-subdirs -u -v -h

This tool does the followings:

    Given the OSC/DCDI Traceback string, it calls addr2line for each traceback address,
    and returns a list of function name and filename:lineno info.

    traceback_str must contain the "-Traceback=" string, which is the start marker of the list of tracebacks.
        The first string after the "-Traceback=" string is the main binary that generated this traceback_str.
    binaryfile is optional. Usually the script should be able to find the proper binary file by searching;
        If not, then you need to provide it via command line.
    rootdir is the root directory to search binary files and shared library files. It can be a list of comma-separated directories.
        The script will automatically search a few known sub-directories under this rootdir, like bin, lib, etc. If customized-subdirs
        is also provided, then those additional sub-dirs are also searched.
    configfile is optional. It is a file that contains objdump/addr2line tool locations.
    customized-subdirs is optional. It is a file that contains a list of sub-directories to search inside rootdir.
    -u option is a feature to find all libraries via ldd command, instead of searching in rootdir.
        This can be very useful if you run this script in a development environment
        where ldd is available.
    -v option is the Verbose option. You can increase verbosity level by using multiple v's, like -vvvvv.

1. An example OSC traceback message looks like:

DATACORRUPTION-DATAINCONSISTENCY: v2.3.0 Copy error -Traceback= ./test_harness +0x2aa4 +0x2b4f +0x1cc5 +0x1719 libc.so.6+0x21c05 +0x1749

The decode of the above traceback will be like:

oscdecode.py -t "DATACORRUPTION-DATAINCONSISTENCY: v2.3.0 Copy error -Traceback= ./test_harness +0x1cc5 +0x1719 libc.so.6+0x21c05 +0x1749" -d .,/

bosc_th_print_mem
/ws/yonhan-bxb/sbg-osc-dir/ciscoosc-2.2.1play/gitdevdir2/test/test_harness_bosc_utils.c:99

bosc_th_test_osc_strncpy
/ws/yonhan-bxb/sbg-osc-dir/ciscoosc-2.2.1play/gitdevdir2/test/test_harness_bosc.c:368 (discriminator 2)

__libc_start_main
??:?

bosc_th_test_osc_strncpy
/ws/yonhan-bxb/sbg-osc-dir/ciscoosc-2.2.1play/gitdevdir2/test/test_harness_bosc.c:373

2. Another example for WNBU:
oscdecode.py -t DATACORRUPTION-DATAINCONSISTENCY: v2.3.0 Copy error -Traceback= ./xz +0x2ebb +0x4ebb +0x1dc4 -d ./thirdparty/openwrt-1505/staging_dir/target-corsica/root-ipq806x,./base/build_corsica/cheetah_staging

memlimit_too_small
coder.c:0

progress_remaining
message.c:0

main
??:0

3. An example run for SBG (Security Business Group) TAC engineers:

oscdecode.py -t "v2.3.0 Copy error -Traceback= ./xz +0x2aa4 +0x2b4f +0x1cc5 +0x1719 libc.so.6+0x21c05 libcairo.so+0x1749" -d /var/cfd_libs/6.2.2.1-73/FTD-Virtual

Or from inside the SBG VMs (like ./ims.sh, ./ftd.sh, or ./fire-linux-os.sh VMs):

oscdecode.py -t "v2.3.0 Copy error -Traceback= ./xz +0x2aa4 +0x2b4f +0x1cc5 +0x1719 libc.so.6+0x21c05 libcairo.so+0x1749" -u

"""
import sys
import os
import subprocess
import argparse
import shutil
import shlex
import pipes

# for special filename handling with shell
try:
    from shlex import quote as cmd_quote
except ImportError:
    from pipes import quote as cmd_quote

TOOL_VERSION = '1.0.0'
VERSION = '%(prog)s ' + TOOL_VERSION

LEVEL_0 = 0
LEVEL_1 = 1
LEVEL_2 = 2
LEVEL_3 = 3
LEVEL_4 = 4

args = None
g_configs = dict()

## cache it for performance
g_search_dirs = []

## cache the results for performance
g_elf_load_base_addr_db = dict()
g_elf_type_db = dict()
g_elf_class_db = dict()

#
# Helper routines
#########################
def verbose(string, level, indent=None):
    """
    Prints information to stdout depending on the verbose level.

    :param string: String to be printed
    :param level: Unsigned Integer, listing the verbose level
    :param indent: indentation string.
    """
    if args.verbose:
        if args.verbose > level:
            if indent is None:
                if level <= LEVEL_4:
                    indent = " " * level
                else:
                    indent = "     "
            print (indent + string)
        return


def get_shell_cmd_output(cmd):
    """
    Returns the output of the shell command "cmd".

    :param cmd: the shell command to execute
    """
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    return output


# The config file contains (keyword, value) pairs.
# Each line is in format of keyword = value, it looks like below:
# objdump = /router/bin/objdump.c4.9.3-p0.ppc-linux
# addr2line = /router/bin/addr2line.c4.9.3-p0.ppc
# You can comment a line with a prefix '#'
def get_config_value(keyword):
    """
     Get the configured value for a keyword.
    :param keyword: objdump, addr2line, etc.
    :returns empty string if no such configs.
    """
    if g_configs and keyword in g_configs:
        return g_configs[keyword]
    return ""


def is_elf_exec_or_dyn_file(afile):
    """
    Return True if the afile is ELF executable or ELF shared object file

    :param afile: a file
    :returns True or False
    """
    elf_type = get_elf_type(afile)
    if "EXEC" == elf_type or "DYN" == elf_type:
        return True
    return False


def get_all_shlib_paths_via_ldd(afile):
    """
    Get all the shared library paths via the ldd command for a file.

    :param afile: a file
    :returns a dictionary that contains all shlib => path mappings.
    """
    cmd = "ldd " + cmd_quote(afile)  + " || true"
    ldd_output = get_shell_cmd_output(cmd)
    verbose("ldd command: " + cmd + " And output is: " + ldd_output, LEVEL_3)
    lines = ldd_output.splitlines()
    shlib_paths = dict()
    for line in lines:
        if "=>" not in line:
            continue
        tokens = line.split(" => ")
        shlib = tokens[0].strip()
        path = tokens[1].split()[0]
        if os.path.exists(path):
            shlib_paths[shlib] = path
    return shlib_paths


def find_shlib(adirs, afile):
    """
    Find the path for a specific file in a list of directories.

    :param adirs: a list of directories
    :param afile: a file (usually a shared library, or the main binary file)
    :returns the path for this specific file. If there are multiple afiles, only the first one is returned.
    """
    verbose("find_shlib: for " + afile + " searching " + str(adirs), LEVEL_2)
    for adir in adirs:
        path = os.path.join(adir, afile)
        verbose("find_shlib: Checking " + path, LEVEL_4)
        if os.path.exists(path) and is_elf_exec_or_dyn_file(path):
            return path
    return afile


def get_elf_load_alignment(afile):
    """
    Get the alignment size of LOAD segment for afile

    :param afile: a file
    :returns the alignment size, the default is 2**16=64KB
    """
    default_load_alignment = 2**16
    objdump_prog = get_config_value("objdump")
    if not objdump_prog:
        objdump_prog = "objdump"
    cmd = objdump_prog + " -p " + cmd_quote(afile) + " | grep align | grep LOAD || true"
    output = get_shell_cmd_output(cmd)
    lines = output.splitlines()
    if not lines:
        return default_load_alignment
    line = lines[0]
    tokens = line.split(" align ")
    if len(tokens) < 2:
        return default_load_alignment
    alignment = tokens[1]
    verbose(afile + " LOAD alignment is: " + alignment, LEVEL_1)
    return eval(alignment)


def get_entry_addr(afile):
    """
    Retrieve ELF Entry point address for a file

    :param afile: a file
    :returns the ELF Entry point address of the file
    """
    cmd = 'readelf -h ' + cmd_quote(afile) + ' | grep "Entry point address:" || true'
    output = get_shell_cmd_output(cmd)
    if output:
        tokens = output.split(":")
        entry_addr = tokens[1].split()[0]
        #verbose(afile + " entry point address is: " + entry_addr, LEVEL_2)
        return int(entry_addr, 0)
    return 0


def get_elf_load_base_addr(afile):
    """
    Retrieve LOAD segment base address for a file
    the LOAD base address is calculated as rounded down Entry point address

    :param afile: a file
    :returns the ELF Entry point address rounded down to LOAD alignment
    """
    # Using cached result if possible
    if afile in g_elf_load_base_addr_db:
        return g_elf_load_base_addr_db[afile]
    addr = get_entry_addr(afile)
    verbose(afile + " Entry point address is: " + hex(addr), LEVEL_1)
    alignment = get_elf_load_alignment(afile)
    #verbose(afile + " LOAD alignment is: " + str(alignment), LEVEL_1)
    base_addr = addr & ~(alignment - 1)  ### align to LOAD alignment, 65536 by default
    g_elf_load_base_addr_db[afile] = base_addr
    return base_addr


def get_elf_type(afile):
    """
    Retrieve ELF type of afile.

    :param afile: a file
    :returns the ELF type of the file
    """
    if afile in g_elf_type_db:
        return g_elf_type_db[afile]
    cmd = 'readelf -h ' + cmd_quote(afile) + ' | grep "Type:" || true'
    output = get_shell_cmd_output(cmd)
    tokens = output.split(":")
    elf_type = tokens[1].split()[0]
    #verbose(afile + " ELF Type is " + elf_type, LEVEL_2)
    g_elf_type_db[afile] = elf_type
    return elf_type


def get_elf_class(afile):
    """
    Retrieve ELF Class of afile.

    :param afile: a file
    :returns the ELF Class of the file
    """
    if afile in g_elf_class_db:
        return g_elf_class_db[afile]
    cmd = 'readelf -h ' + cmd_quote(afile) + ' | grep "Class:" || true'
    output = get_shell_cmd_output(cmd)
    tokens = output.split(":")
    elf_class = tokens[1].strip()
    verbose(afile + " ELF Class is " + elf_class, LEVEL_2)
    g_elf_class_db[afile] = elf_class
    return elf_class


def get_basic_search_subdirs(afile):
    """
    Get a list of BASIC sub-directories to search for a file.
    For 32bit binary files, it only searchs lib, not lib64 dir.

    :param afile: a file
    :returns a list of sub-dirs to search
    """
    if os.path.exists(afile):
        elf_class = get_elf_class(afile)
        if "ELF32" == elf_class:
            # Do not search lib64 dir for 32bit binary file
            return ['', 'bin', 'sbin', 'lib', 'usr/bin', 'usr/sbin', 'usr/lib']
    return ['', 'bin', 'sbin', 'lib64', 'usr/bin', 'usr/sbin', 'usr/lib64', 'lib', 'usr/lib']


def get_search_subdirs(adir, afile, in_subdirs=[]):
    """
    Get a list of subdirectories to search for a file inside a directory.

    :param adir: a directory
    :param afile: a file
    :param in_subdirs: a list of sub-dirs explicitly specified
    :returns a list of sub-dirs to search
    """
    dirs = []
    search_subdirs = in_subdirs
    if not in_subdirs:
        search_subdirs = get_basic_search_subdirs(afile)
    for subdir in search_subdirs:
        path = os.path.join(adir, subdir)
        dirs.append(path)
    return dirs


def read_file_lines(afile):
    """
    Read all lines of a file.

    :param afile: a file
    :returns a list of all lines in the file
    """
    with open(afile, 'r') as f:
        lines = f.read()
        return lines.splitlines()


def get_customized_search_subdirs(afile):
    """
    Get a customized list of subdirectories to search for a file inside a directory.

    :param afile: a file
    :returns a list of sub-dirs to search
    """
    custom_file = args.customized_dirs_file
    if not custom_file:
        return []
    if not os.path.exists(custom_file):
        verbose("Warning: Your customized_dirs_file " + custom_file + " does not exist!", LEVEL_1)
        return []
    adirs = read_file_lines(custom_file)
    search_subdirs = []
    ### Platform specific search sub-dirs
    for adir in adirs:
        adir2 = adir.strip()
        if not adir2 or adir2[0] == '#':  # ignore empty lines or lines starting with '#' character
            continue
        # Add adir sub-directories to search list
        subdirs2 = get_search_subdirs(adir2, afile)
        search_subdirs.extend(subdirs2)
    return search_subdirs


def get_search_dirs(rootdirs_to_search, afile):
    """
    Get a list of directories to search for a file.

    :param rootdirs_to_search: a list of root directories
    :param afile: a file
    :returns a list of dirs to search
    """
    verbose("Entering get_search_dirs for " + afile + " dirs: " + str(rootdirs_to_search), LEVEL_4)
    dirs = []
    search_subdirs = get_basic_search_subdirs(afile)

    # Add usr/local sub-directories to search list
    subdirs2 = get_search_subdirs("usr/local", afile)
    search_subdirs.extend(subdirs2)

    ### Add platform specific search sub-directories
    custom_subdirs = get_customized_search_subdirs(afile)
    search_subdirs.extend(custom_subdirs)
    verbose("Final search_subdirs for " + afile + " is: " + str(search_subdirs), LEVEL_4)

    for adir in rootdirs_to_search:
        for subdir in search_subdirs:
            path = os.path.join(adir, subdir)
            # non-existent path will be pruned
            if os.path.exists(path):
                dirs.append(path)
    return dirs


def get_addr2line(traceback, binfile="", search_dirs=[], shlib_db=None):
    """
    Get the decode of one single OSC traceback via addr2line
    Note: 1. for DYN type binary, relative offset value is provided to addr2line;
          2. for EXEC type binary, absolute address value is provided to addr2line.

    :param traceback: one traceback in shlib+offset or +offset format
    :param binfile: the main binary file that prints the traceback
    :param search_dirs: a list of root directories to search
    :param shlib_db: the shlib_db obtained via ldd
    :returns a string containing the "addr2line offset" decode output
    """
    tokens = traceback.split("+")
    afile = tokens[0]
    thefile = ""
    if not afile:
        thefile = binfile
    else:
        if shlib_db and afile in shlib_db:
            thefile = shlib_db[afile]
        else:
            thefile = find_shlib(g_search_dirs, afile)
    verbose("decoding traceback: " + traceback + " file: " + afile + " => " + str(thefile), LEVEL_1)
    if not thefile or not os.path.exists(thefile):
        verbose("Failed to decode because " + afile + " and " + str(thefile) + " do not exist!", LEVEL_1)
        return traceback + "\n"
    offset = tokens[1]
    elf_type = get_elf_type(thefile)
    verbose(thefile + " elf_type: " + elf_type, LEVEL_1)
    if elf_type == "EXEC":
        # Calculate absolute address for EXEC type binary, which is then fed to addr2line
        base_addr = get_elf_load_base_addr(thefile)
        verbose("The LOAD base address or the rounded down entry address is: " + hex(base_addr), LEVEL_1)
        offset = hex(int(offset, 0) + base_addr)
        #print ("the absolute address is: " + offset)
    addr2line_prog = get_config_value("addr2line")
    if not addr2line_prog:
        addr2line_prog = "addr2line"
    cmd = addr2line_prog + " -f -i -e " + cmd_quote(thefile) + " " + offset + " || true"
    verbose("The traceback decode cmd is: " + cmd, LEVEL_1)
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True, stderr=open(os.devnull, 'w'))
    return output


def find_binfile(in_binfile, tb_binfile, search_dirs):
    """
    Find the binary file location.
    It also updates the global search directories for later use, for both consistency and performance purpose.

    :param in_binfile: the command line provided binary file path
    :param tb_binfile: the binary file path included in the traceback string
    :param search_dirs: a list of root directories, usually provided via command line option
    :returns the binary file location after searching known directories
    """
    global g_search_dirs
    verbose("Entering find_binfile for in_binfile: " + in_binfile + " tb_binfile: " + tb_binfile + " and search_dirs: " + str(search_dirs), LEVEL_3)
    binfile = tb_binfile
    if in_binfile and os.path.exists(in_binfile):
        binfile = in_binfile
        verbose("binary file " + in_binfile + " is provided via command line, use it.", LEVEL_1)
    elif search_dirs:
        adirs = get_search_dirs(search_dirs, tb_binfile)
        verbose("Searching binary file " + tb_binfile + " in dirs: " + str(adirs), LEVEL_1)
        binfile = find_shlib(adirs, os.path.basename(tb_binfile))
        verbose("Searching " + tb_binfile + " And found: " + str(binfile), LEVEL_1)
        if not binfile or not os.path.exists(binfile):
            verbose("Warning: cannot find binary file " + str(binfile), LEVEL_0)
        else:
            verbose("No binary file is provided via command line, use the searched binary file " + str(binfile), LEVEL_1)
    g_search_dirs = get_search_dirs(search_dirs, binfile)   # save it for later use
    verbose("\nGlobal g_search_dirs is set as: " + str(g_search_dirs), LEVEL_0)
    return binfile


def decode_traceback(traceback_str, in_binfile="", search_dirs=[]):
    """
    Decode the whole traceback string, which contains a number of tracebacks

    :param traceback_str: the whole traceback string
    :param binfile: the main binary file that prints the traceback
    :param search_dirs: a list of root directories to search
    :returns a multi-line string containing the "addr2line offset" decode output for all tracebacks in the string
    """
    print ("Decoding: " + traceback_str + "\n")
    tb_str = "Traceback="
    start = traceback_str.find(tb_str)
    if start < 0:
        print ("Error: Unexpected Traceback string: it must contain '" + tb_str + "'")
        return "Error: Failed to decode"
    tokens = traceback_str[(start + len(tb_str)):].split()
    if len(tokens) < 1:
        print ("Error: Unexpected Traceback string: too short")
        return "Error: Failed to decode"
    # the first token must be the binary that generates the traceback
    binfile = find_binfile(in_binfile, tokens[0], search_dirs)
    verbose("The main binary file is: " + str(binfile), LEVEL_0)
    shlib_db = dict()
    if args.useldd and binfile and os.path.exists(binfile):
        # only if -u command option is specified
        shlib_db = get_all_shlib_paths_via_ldd(binfile)
        verbose("The shared library database from ldd is: " + str(shlib_db), LEVEL_2)
    decode_result = ""
    for token in tokens:
        if '+' in token:
            result = get_addr2line(token, binfile, search_dirs, shlib_db)
            verbose(result, LEVEL_0)
            decode_result += result + "\n"
    return decode_result


def rtd_parse_options():
    """
    Parse command options.
    """
    # Now the main part: Start with parsing the command line arguments.
    parser = argparse.ArgumentParser(
        description = "This tool decodes OSC/DCDI Traceback string")
    parser.add_argument("--version",
                    action = "version",
                    version=VERSION)
    parser.add_argument('-t', '--traceback',
                    help = "OSC Tracback string")
    parser.add_argument('-b', '--binaryfile',
                    help = "binary file")
    parser.add_argument('-d', '--dirs_to_search',
                    help = "a list of comma-spearated root directory to search for shared libraries")
    parser.add_argument("-c", "--configfile",
                    help = "configuration file, like objdump/addr2line tool locations, etc.")
    parser.add_argument('-s', '--customized_dirs_file',
                    help = "a file that contains customized sub-directories to search")
    parser.add_argument("-u", "--useldd",
                    action = "store_true",
                    help = "use ldd to find shared libraries")
    parser.add_argument("-v", "--verbose",
                    action = "count",
                    default = 0,
                    help = "verbose output, can be supplied multiple times"
                           " to increase verbosity")

    # Parse the command line arguments
    args = parser.parse_args()

    if not (args.traceback):
        print ("Please specify the Traceback string with -t option!")
        print ("")
        parser.print_help()
        sys.exit()

    if args.configfile:
        if not os.path.isfile(args.configfile):
            print ("The configuration file " + args.configfile + " does not exist!")
            print ("")
            print ('Run "' + sys.argv[0] + ' -h" for help.')
            sys.exit()
        with open(args.configfile, 'r') as f:
            for line in f:
                config = line.strip()
                if (config and config[0] == '#') or '=' not in config:
                    continue
                tokens = config.split('=')
                g_configs[tokens[0].strip()] = tokens[1].strip()

    print ("Your command line is:")
    print (" ".join(sys.argv))
    print ("The current directory is: " + os.getcwd())
    print ("")
    return args


def main():
    global args
    # parse command line options first
    args = rtd_parse_options()

    in_binfile = ""
    if args.binaryfile:
        in_binfile = args.binaryfile
    search_dirs = []
    if args.dirs_to_search:
        search_dirs = args.dirs_to_search.split(",")
    decode_result = decode_traceback(args.traceback, in_binfile, search_dirs)
    print ("\nTraceback decoding results:\n")
    print (decode_result)


if __name__ == '__main__':
    main()

