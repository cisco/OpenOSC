#! /usr/bin/env python
'''
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
'''
"""
Utility script to auto-generate OSC mapping header files and runtime check code.
OSC Watermark Magic values are also generated. Testing code is also generated.
WARNING: This script is out-dated! Some updates are needed for it to work.
"""

import argparse
import sys
import os
import subprocess
import json

TOOL_VERSION = '1.0.0'
VERSION = '%(prog)s ' + TOOL_VERSION
HDR1 = "==================================================="
HDR2 = "###################################################"
HDR3 = "---------------------------------"
HDR4 = "------------------------------------------"
HDR5 = "---------------------------------------------------"

LEVEL_0 = 0
LEVEL_1 = 1
LEVEL_2 = 2
LEVEL_3 = 3
LEVEL_4 = 4

args = None
g_functions = []
g_magic_word = 0x1122334455667700
#g_magic_word = 0x00800100
g_magic_words = dict()
g_magic_alignment = 8      # bits reserved for each function
g_outfile = None

def rtd_parse_options():
    """
    Parse command options.
    """
    global args

    # Now the main part: Start with parsing the command line arguments.
    parser = argparse.ArgumentParser(
        description = "Utility script to generate code for OpenOSC new functions")
    parser.add_argument("--version",
                    action = "version",
                    version=VERSION)
    parser.add_argument("-f", "--functions",
                    help = "a list of function names separated by comma")
    parser.add_argument('-t', '--magictype',
                    help = "the type of magic word, either or byte_inline or dwarf_loc")
    parser.add_argument('-a', '--alignment',
                    help = "the magic word alignment for functions, the default is 8 bits aligned")
    parser.add_argument('-m', '--magicword',
                    help = "the 8-byte OSC Metrics magic word to start, like 0x4d41474943d30100 or 4-byte like 134217985")
    parser.add_argument('-p', '--prototype',
                    help = "the function prototype")
    parser.add_argument('-i', '--inputfile',
                    help = "the input file which contains all functions to fortify")
    parser.add_argument('-l', '--linesofinclude',
                    help = "The lines of the include header files of the function. "
                           "Multiple include lines can be provided via comman separated, like "
                           "'#include <sti, #include <fcntl.h>,#include <unistd.h>'")
    parser.add_argument('-o', '--outputfile',
                    help = "the output file to save the auto-genereated code")
    parser.add_argument('-j', '--jsonoutputfile',
                    help = "the output file to put the JSON output."
                           " If omitted, a default file, like ./RESULT_JSON_FILE.txt will be used")
    parser.add_argument("-v", "--verbose",
                    action = "count",
                    default = 0,
                    help = "verbose output, can be supplied multiple times"
                           " to increase verbosity")

    # Parse the command line arguments
    args = parser.parse_args()

    # store the command line arguments
    global g_functions
    if args.functions:
        g_functions = args.functions.split(',')

    global g_magic_alignment
    if args.alignment:
        g_magic_alignment = int(args.alignment, 0)

    global g_magic_word
    if args.magicword:
        g_magic_word = get_wrap_magic_word( int(args.magicword, 0), g_magic_alignment )

    global RESULT_JSON_FILE
    if args.jsonoutputfile:
        RESULT_JSON_FILE = args.jsonoutputfile

    global g_outfile
    if args.outputfile:
        g_outfile = open(args.outputfile, "a")

    print("Your command line is:")
    print(" ".join(sys.argv))
    print("The current directory is: " + os.getcwd())
    print("")


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
                if level < LEVEL_4:
                    indent = " " * level
                else:
                    indent = "     "
            print(indent + string)
        return


RESULT_JSON_FILE = "RESULT_JSON_FILE.txt"

def load_json_db(db_file):
    """ Load the the data from a JSON file

    :param db_file: the JSON database file
    :returns a dictionary that contains the data
    """
    db = dict()
    with open(db_file, 'r') as f:
        db = json.load(f)
    return db


def save_json_db(db_file, db, indentation=4):
    """ Save the dictionary data to a JSON file

    :param db_file: the JSON database file
    :param db: the python dict struct
    :returns None
    """
    if not db:
        return
    try:
        f = open(db_file, 'w')
    except IOError as e:
        print("I/O error({0}): {1}".format(e.errno, e.strerror))
        print("Error in save_json_db, skipping it.")
    else:
        with f:
            json.dump(db, f, indent=indentation, sort_keys=True)


openosc_h_file_top_template = '''/*------------------------------------------------------------------
 * %openosc_map.h% -- OpenOSC Library Public Header File
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 *------------------------------------------------------------------
 */

'''

def get_h_macro(filename):
    '''
    Return the __OPENOSC_FORTIFY_H__ macro string for openosc_fority.h header file
    '''
    tokens = filename.split(".")
    newfilename = '_'.join(tokens)
    return '__' + newfilename.upper() + '__'


def get_openosc_h_file_top_code(filename):
    '''
    Return the first few lines for a .h header file or a .c source file
    '''
    code = openosc_h_file_top_template.replace("%openosc_map.h%", filename)
    if filename[-2:] != '.h':
        if filename[-2:] == '.c':
            code = code.replace(" Public Header File", " Source Code")
        return code
    h_macro = get_h_macro(filename)
    code += '#ifndef ' + h_macro + '\n'
    code += '#define ' + h_macro + '\n\n'
    return code


def get_openosc_h_file_bottom_code(filename):
    '''
    Return the last few lines for a .h header file
    '''
    if filename[-2:] != '.h':
        return ''
    h_macro = get_h_macro(filename)
    return '\n#endif  /* ' + h_macro + ' */\n'


#############  Generating code for OSC MAGIC WORDS ###########

def generate_openosc_redefine_map_code_new(prototype):
    '''
    Generate Macro-redefine code in openosc_fortify_redefine_map.h for a function prototype.
    :param prototype: a function prototype
    :returns the code as a long string.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    print(HDR1)
    print("Now generating OpenOSC Macro Redefine mapping code for: " + funcname)
    print(HDR1)
    magic_str = '_CASE3'
    va_args_code = generate_va_args_redefine_code(funcname, params, magic_str)
    if not va_args_code:
        return generate_openosc_redefine_map_code(prototype)
    func_code = generate_osc_mapping_func_body_with_va_arg_pack(funcname, magic_str)
    func_code += generate_osc_redefine_macro_code(funcname, params)
    func_code += '\n'
    code = '/* Mapping for '  + funcname + ' */\n\n'
    code += '#ifdef __va_arg_pack\n'
    code += func_code
    code += '#elif !defined __cplusplus\n\n'
    code += va_args_code
    code += '\n#endif\n\n'
    print(code)
    openosc_write_filename("openosc_fortify_redefine_map.h", code)
    return code


def generate_openosc_redefine_map_code(prototype):
    '''
    Generate Macro-redefine code in openosc_fortify_redefine_map.h for a function prototype.
    :param prototype: a function prototype
    :returns the code as a long string.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    funcname_up = funcname.upper()
    comma_params = get_comma_joined_param_names(params)
    if "..." in params:
        return "printf_like"
    #print(HDR1)
    #print("Now generating OpenOSC Macro Redefine mapping code for: " + funcname)
    #print(HDR1)
    code = '/* Mapping for '  + funcname + ' */\n\nextern '
    code += retval
    code += '\n__' + funcname + '_to_buf(size_t dest_len, ' + params + ');\n\n'
    code += 'static inline __attribute__ ((always_inline)) ' + retval + '\n'
    code += 'openosc_' + funcname + ' (' + params + ')\n'
    code += '  OSC_THROW\n{\n'
    if not dest_param:
        code += '    return (' + funcname_up + '_CASE3 __' + funcname + '_to_buf(OPENOSC_USE_FORTIFY_LEVEL - 1, ' + comma_params + '));\n'
        code += '}\n\n'
        code += generate_osc_redefine_macro_code(funcname, params)
        code += '\n'
        openosc_write_filename("openosc_fortify_redefine_map.h", code)
        print(code)
        return code
    bosc_check_type = "OSC_OBJECT_SIZE_CHECK_0"
    if "char" in dest_type or "wchar_t" in dest_type:
        bosc_check_type = "OSC_OBJECT_SIZE_CHECK_1"
    byte_sz = "_sz"
    if "wchar_t" in dest_type:
        byte_sz = "_sz_bytes"
        code += '    size_t _sz_bytes = __builtin_object_size(' + dest_param + ', ' + bosc_check_type + ');\n'
        code += '    size_t _sz = _sz_bytes / sizeof(wchar_t);\n'
    else:
        code += '    size_t _sz = __builtin_object_size(' + dest_param + ', ' + bosc_check_type + ');\n'
    if copylen:
        code += '    int is_len_constant = __builtin_constant_p(' + copylen + ');\n'
        code += '    return (((' + byte_sz + ' != (size_t) -1) && (' + byte_sz + ' != 0))\n'
        code += '            ? (is_len_constant\n'
        code += '               ? ((_sz >= ' + copylen + ')\n'
        code += '                  ? (' + funcname_up + '_CASE1 ' + funcname + '(' + comma_params + '))\n'
        code += '                  : (' + funcname_up + '_CASE2 OSC_ASSERT_' + funcname + '()))\n'
        code += '               : (' + funcname_up + '_CASE3 OSC_RUNTIME_CHECK_' + funcname + '()))\n'
        code += '            : (' + funcname_up + '_CASE4 ' + funcname + '(' + comma_params + ')));\n'
    else:
        code += '    return (((' + byte_sz + ' != (size_t) -1) && (' + byte_sz + ' != 0))\n'
        code += '            ? (' + funcname_up + '_CASE3 OSC_RUNTIME_CHECK_' + funcname + '())\n'
        code += '            : (' + funcname_up + '_CASE4 ' + funcname + '(' + comma_params + ')));\n'
    code += '}\n\n'
    code += generate_osc_redefine_macro_code(funcname, params)
    code += '\n'
    print(code)
    openosc_write_filename("openosc_fortify_redefine_map.h", code)
    return code


def generate_openosc_redirect_map_code_new(prototype):
    '''
    Generate ASM-Label Redirect code in openosc_fortify_redirect_map.h for a function prototype.
    :param prototype: a function prototype
    :returns the code as a long string.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    print(HDR1)
    print("Now generating OpenOSC ASM-Label Redirect Mapping code for: " + funcname)
    print(HDR1)
    magic_str = '_CASE3'
    va_args_code = generate_va_args_redefine_code(funcname, params, magic_str)
    if not va_args_code:
        return generate_openosc_redirect_map_code(prototype)
    func_code = generate_osc_mapping_func_body_with_va_arg_pack(funcname, magic_str)
    code = '/* Mapping for '  + funcname + ' */\n\n'
    code += '#ifdef __va_arg_pack\n'
    code += func_code
    code += '#elif !defined __cplusplus\n\n'
    code += va_args_code
    code += '\n#endif\n\n'
    print(code)
    openosc_write_filename("openosc_fortify_redirect_map.h", code)
    return code


def generate_openosc_redirect_map_code(prototype):
    '''
    Generate ASM-Label Redirect code in openosc_fortify_redirect_map.h for a function prototype.
    :param prototype: a function prototype
    :returns the code as a long string.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    funcname_up = funcname.upper()
    comma_params = get_comma_joined_param_names(params)
    if "..." in params:
        return "printf_like"
    #print(HDR1)
    #print("Now generating OpenOSC ASM-Label Redirect Mapping code for: " + funcname)
    #print(HDR1)
    code = '/* Mapping for '  + funcname + ' */\n\nextern '
    code += retval
    code += '\n__' + funcname + '_to_buf(size_t dest_len, ' + params + ');\n'
    code += 'extern ' + retval + ' __REDIRECT_NTH (__openosc_' + funcname + '_alias,\n'
    code += '                              (' + params + '), ' + funcname + ');\n'
    code += 'extern ' + retval + ' __REDIRECT_NTH (openosc_' + funcname + '_chk_warn,\n'
    code += '                              (size_t dest_len, ' + params + '), __' + funcname + '_to_buf)\n'
    code += '       __warnattr ("' + funcname + ' caller with bigger length than size of destination buffer");\n\n'
    code += '__fortify_function ' + retval + '\n'
    code += '__NTH (' + funcname + ' (' + params + '))\n{\n'
    if not dest_param:
        code += '    return (' + funcname_up + '_CASE3 __' + funcname + '_to_buf(OPENOSC_USE_FORTIFY_LEVEL - 1, ' + comma_params + '));\n'
        code += '}\n\n'
        print(code)
        openosc_write_filename("openosc_fortify_redirect_map.h", code)
        return code
    bosc_check_type = "OSC_OBJECT_SIZE_CHECK_0"
    if "char" in dest_type or "wchar_t" in dest_type:
        bosc_check_type = "OSC_OBJECT_SIZE_CHECK_1"
    byte_sz = "_sz"
    if "wchar_t" in dest_type:
        byte_sz = "_sz_bytes"
        code += '    size_t _sz_bytes = __builtin_object_size(' + dest_param + ', ' + bosc_check_type + ');\n'
        code += '    size_t _sz = _sz_bytes / sizeof(wchar_t);\n'
    else:
        code += '    size_t _sz = __builtin_object_size(' + dest_param + ', ' + bosc_check_type + ');\n'
    if copylen:
        code += '    int is_len_constant = __builtin_constant_p(' + copylen + ');\n'
        code += '    return (((' + byte_sz + ' != (size_t) -1) && (' + byte_sz + ' != 0))\n'
        code += '            ? (is_len_constant\n'
        code += '               ? ((_sz >= ' + copylen + ')\n'
        code += '                  ? (' + funcname_up + '_CASE1 __openosc_' + funcname + '_alias(' + comma_params + '))\n'
        code += '                  : (' + funcname_up + '_CASE2 openosc_' + funcname + '_chk_warn(_sz, ' + comma_params + ')))\n'
        code += '               : (' + funcname_up + '_CASE3 __' + funcname + '_to_buf(_sz, ' + comma_params + ')))\n'
        code += '            : (' + funcname_up + '_CASE4 __openosc_' + funcname + '_alias(' + comma_params + ')));\n'
    else:
        code += '    return (((' + byte_sz + ' != (size_t) -1) && (' + byte_sz + ' != 0))\n'
        code += '            ? (' + funcname_up + '_CASE3 __' + funcname + '_to_buf(_sz, ' + comma_params + '))\n'
        code += '            : (' + funcname_up + '_CASE4 __openosc_' + funcname + '_alias(' + comma_params + ')));\n'
    code += '}\n\n'
    print(code)
    openosc_write_filename("openosc_fortify_redirect_map.h", code)
    return code


osc_runtime_check_macro_template = '''
/*
 * Define Runtime check macros
 */
#if (OSC_RUNTIME_CHK == OSC_RUNTIME_USE_LIBOSC)

'''

osc_compiletime_check_macro_template = '''
/*
 * Define compile-time static asserts to report buffer overflow
 * detected by OSC
 *
 * Since support for compile-time error reporting are compiler dependent,
 * there will be multiple definitions of these macros. To select a specific
 * implemetaton, define the appropriate flag within this header file. For
 * the build enviroment that use multiple compilers, the flag can be defined
 * on the command line using the "-D" switch.
 *
 * Note: OSC_ASSERT_USE_BUILTIN should only be used for compile-time check
 * only. It must NOT be used in release code or a risk of abort() call get
 * inserted into production image by the compiler.
 */
#if (OSC_COMPILE_CHK == OSC_ASSERT_USE_ERR_ATTR)
'''

### #pragma message ("No compile time OSC checking, use original libc/safec function")
osc_compiletime_check_macro_end = '''
#else
#pragma message ("No compile time OSC checking method selected, contact jaguars-dev alias for guidance")
#endif
'''

def generate_osc_original_runtime_check_macro(prototype):
    '''
    Generate runtime check macro to itself mapping.
    :param prototype: function prototype
    :returns the generated code.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    comma_params = get_comma_joined_param_names(params)
    return  '#define OSC_RUNTIME_CHECK_' + funcname + '()\t\t' + funcname + '(' + comma_params + ')\n'


def generate_osc_runtime_check_macro(prototype):
    '''
    Generate runtime check macro to __memcpy_to_buf mapping.
    :param prototype: function prototype
    :returns the generated code.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    comma_params = get_comma_joined_param_names(params)
    return  '#define OSC_RUNTIME_CHECK_' + funcname + '()\t\t__' + funcname + '_to_buf(_sz, ' + comma_params + ')\n'


def generate_osc_compiletime_check_macro(prototype, checktype):
    '''
    Generate compile-time check macro for a prototype.
    :param prototype: function prototype
    :param checktype: a few different compile time check types that are supported
    :returns the generated code.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    code = ''
    if "..." in params:
        return code
    comma_params = get_comma_joined_param_names(params)
    if checktype == 'OSC_ASSERT_USE_ERR_ATTR':
        code += 'extern int __attribute__((error("Compiler Assertion: ' + funcname + ' len will always overflow dst"))) \\\n'
        code += ' osc_compile_check_' + funcname + '(void);\n'
        code += '#define OSC_ASSERT_' + funcname + '()  ({osc_compile_check_' + funcname + '(), (' + retval + ')0;})\n\n'
    elif checktype == 'OSC_ASSERT_USE_BUILTIN':
        code += '#define OSC_ASSERT_' + funcname + '()\t\t__' + funcname + '_chk(' + comma_params + ', _sz)\n'
    elif checktype == 'OSC_ASSERT_USE_RUNTIME_CHK':
        code += '#define OSC_ASSERT_' + funcname + '()\t\t__' + funcname + '_to_buf(_sz, ' + comma_params + ')\n'
    elif checktype == 'OSC_ASSERT_USE_NONE':
        code += '#define OSC_ASSERT_' + funcname + '()\t\t' + funcname + '(' + comma_params + ')\n'
    return code


def generate_osc_redefine_macro_code(funcname, params):
    '''
    Generate macro redefine code for a function.
    :param funcname: function name
    :param params: the whole string of function parameters like "void *dest, const void *src, size_t n" for memcpy
    :returns the generated code.
    '''
    code = '#undef ' + funcname + '\n'
    if "..." in params:
        code += '#define ' + funcname + '\t\t' + 'openosc_' + funcname + '\n'
        return code
    names = get_comma_joined_param_names(params)
    code += '#define ' + funcname + '(' + names + ')\t\t'
    code += 'openosc_' + funcname + '(' + names + ')\n'
    return code


def get_byte_array_of_magic_word(magic):
    '''
    Return a byte array for a 64bit integer magic word.
    :param magic: a 64bit integer for the magic word like 0x0102030405060708
    :returns a comma-joined byte array as a string, which is then used for asm(".byte 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8").
    '''
    byte_list = []
    m = magic
    for i in range(8):
        byte_list.append(hex(m & 0xff))
        m = m >> 8
    #print(byte_list)
    byte_array = ", ".join(byte_list[::-1])
    return byte_array


def get_wrap_magic_word(magic, alignment):
    '''
    Get next aligned magic word.
      for example, let's assume alignment = 8 bit.
      if magic = 0x0, new magic = 0x100
      if magic = 0x1, new magic = 0x100
      if magic = 0xFF, new magic = 0x100
      if magic = 0x100, new magic = 0x200
    :param magic: 64bit integer magic word
    :param alignment: number of bits, if 8 bits, then wrap at 2^8=256byte.
    :returns a new 64bit integer magic word which is aligned at 2^alignment
    '''
    #return ((magic + (1 << alignment)) >> alignment) << alignment
    return ((magic >> alignment) + 1) << alignment


def update_global_magic_word(magic):
    '''
    Update the global magic variable with the new value.
    :param magic: the new 64bit integer value for magic
    :returns None
    '''
    global g_magic_word
    g_magic_word = magic


def get_hex_string_of_int_magic(int_magic):
    '''
    Return a hex string for a 64bit integer magic word.
    :param int_magic: a 64bit integer magic word like 0x02030405060708
    :returns a string like "0002030405060708" without "0x" prefix.
    '''
    hex_magic = hex(int_magic)[2:]
    hex_magic = '0' * (16 - len(hex_magic)) + hex_magic
    return hex_magic


def generate_curioscan_code(funcname, int_magic):
    '''
    Generate the magic array for a single function.
    :param funcname: the function name
    :param int_magic: the 64bit integer magic word
    :returns the generated code, which is used by Curioscan.
    '''
    magic = int_magic
    code = ''
    code += "    '" + funcname + "': {\n"
    for i in range(5):
        magic += 1
        magictype = "MAGIC_FUNC_MAGIC"
        if i == 0:
            magictype = "MAGIC_FUNC_NOMAPPING_MAGIC"
        hex_magic = get_hex_string_of_int_magic(magic)
        if args.magictype == 'dwarf_loc': # .loc just uses decimal number
            hex_magic = str(magic - 1)
        code += "        '" + hex_magic + "': '" + magictype + str(i) + "',\n"
    code += "    },\n"
    return code


def generate_nomap_magic_code_for_func(funcname, int_magic=0, macrotype=''):
    '''
    Generate NOMAP magic macro code for a single function for openosc_fortify_nomap_metric.h file.
    :param funcname: the function name
    :param int_magic: the 64bit integer magic word
    :param macrotype: MAGIC/CASE/
    :returns the generated code
    '''
    print("Now generating OpenOSC nomap magic code for function " + funcname + " with MAGIC word: " + hex(int_magic) + " for macro-type: " + macrotype)
    func_up = funcname.upper()
    code = ''
    if macrotype == 'MAGIC':
        if args.magictype == 'dwarf_loc':
            code += '#define ' + func_up + '_NOMAP_MAGIC' + '\t\t".loc 1 '
            code += str(int_magic - 1) + '"\n'
        else:
            code += '#define ' + func_up + '_NOMAP_MAGIC' + '\t\tOSC_JUMPOVER ".byte '
            code += get_byte_array_of_magic_word(int_magic) + '\\n" OSC_JUMPLABEL\n'
        int_magic += 1
        update_global_magic_word(int_magic)
    elif macrotype == 'CASE':
        code += '#define ' + func_up + '_NOMAP_CASE' + '\t\t({asm(' + func_up + '_NOMAP_MAGIC' + ');}),\n'
    else:
        code += '#define ' + func_up + '_NOMAP_CASE' + '\n'
    #openosc_write_filename("openosc_fortify_nomap_metric.h", code)
    return code


def has_dest_param(funcname):
    '''
    Check if a function has destination buffer parameter.
    '''
    prototype = get_func_prototype_from_man(funcname)
    (retval, func, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param) = get_dest_param(params)
    if dest_param:
        return True
    return False


def generate_map_magic_code_for_func(funcname, int_magic=0, macrotype=''):
    '''
    Generate MAP magic macro code for a single function for openosc_fortify_map_metric.h file.
    :param funcname: the function name
    :param int_magic: the 64bit integer magic word
    :param macrotype: MAGIC/CASE/
    :returns the generated code
    '''
    print("Now generating OpenOSC map magic code for function " + funcname + " with MAGIC word: " + hex(int_magic) + " for macro-type: " + macrotype)
    has_dest = has_dest_param(funcname)
    func_up = funcname.upper()
    code = ''
    if macrotype == 'MAGIC':
        for i in range(4):
            if args.magictype == 'dwarf_loc':
                code += '#define ' + func_up + '_MAGIC' + str(i+1) + '\t\t".loc 1 '
                code += str(int_magic - 1) + '"\n'
            else:
                code += '#define ' + func_up + '_MAGIC' + str(i+1) + '\t\tOSC_JUMPOVER ".byte '
                code += get_byte_array_of_magic_word(int_magic) + '\\n" OSC_JUMPLABEL\n'
            int_magic += 1
        update_global_magic_word(int_magic)
    elif macrotype == 'CASE':
        for i in range(4):
            code += '#define ' + func_up + '_CASE' + str(i+1) + '\t\t({asm(' + func_up + '_MAGIC' + str(i+1) + ');}),'
            if has_dest:
                code += ' OSC_DSTSIZE(_sz)\n'
            else:
                code += '\n'
    else:
        for i in range(4):
            code += '#define ' + func_up + '_CASE' + str(i+1) + '\n'
    #openosc_write_filename("openosc_fortify_map_metric.h", code)
    return code + '\n'


'''
This function is Not used any more.
def generate_map_magic_code(funcname, int_magic):
    #print("Now generating OpenOSC map magic code for function " + funcname + " with MAGIC word: " + hex(int_magic))
    func_up = funcname.upper()
    code = '#ifdef OSC_METRIC_FEATURE_ENABLED\n'
    for i in range(4):
        code += '#define ' + func_up + '_MAGIC' + str(i+1) + '\t\tOSC_JUMPOVER ".byte '
        code += get_byte_array_of_magic_word(int_magic) + '\\n" OSC_JUMPLABEL\n'
        int_magic += 1
    update_global_magic_word(int_magic)
    code += '\n'
    for i in range(4):
        code += '#define ' + func_up + '_CASE' + str(i+1) + '\t\t({asm(' + func_up + '_MAGIC' + str(i+1) + ');}), OSC_DSTSIZE(_sz)\n'
    code += '#else\n'
    for i in range(4):
        code += '#define ' + func_up + '_CASE' + str(i+1) + '\n'
    code += '#endif\n'
    openosc_write_filename("openosc_fortify_map_metric.h", code)
    return code
'''


def get_gnu_redirect_function_name(funcname):
    '''
    Return the alias function name for ASM-Label redirect mechanism.
    '''
    return '__openosc_' + funcname + '_alias'


def generate_gnu_redirect_func_declaration(retval, funcname, params):
    '''
    Return the declaration of the alias function for ASM-Label redirect mechanism.
    '''
    code = ''
    code += 'extern ' + retval + ' __REDIRECT_NTH (' + get_gnu_redirect_function_name(funcname) + ',\n'
    code += '       (' + params + '), ' + funcname + ');\n\n'
    return code


def get_param_name_list(params):
    '''
    Return the list of parameter names only.
    '''
    param_list = get_param_list_from_params_string(params)
    names = []
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        names.append(param_name)
    return names


def get_param_name_2less_list(params):
    '''
    Return the list of parameter names, deleting the last two parameters.
    '''
    name_list = get_param_name_list(params)
    return name_list[:-2]


def get_comma_joined_nofmt_3dots_params(params):
    '''
    Return the list of parameter names, deleting the last two parameters and then adding "...".
    '''
    name_list = get_param_name_list(params)
    newnames = name_list[:-2]
    newnames.append("...")
    return ', '.join(newnames)


def delete_flag_slen_params(params):
    param_list = get_param_list_from_params_string(params)
    newparams = []
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        if param_name not in ("flags", "flag", "s_len", "slen"):
            newparams.append(param)
    return ', '.join(newparams)


def delete_flag_slen_nofmt_3dots_params(params):
    '''
    Delete flag/slen parameters, also remove fmt parameter, add "..." at the end.
    '''
    names = get_param_name_2less_list(params)
    newnames = []
    for name in names:
        if name not in ("flags", "flag", "s_len", "slen"):
            newnames.append(name)
    newnames.append("...")
    return ', '.join(newnames)


def replace_flag_slen_nofmt_params(params):
    '''
    Replace flag/slen parameters, also remove fmt parameter.
    '''
    (dest_type, dest_param) = get_dest_param(params)
    #param_list = get_param_list_from_params_string(params)
    bos_dest = '__builtin_object_size(' + dest_param + ', OSC_OBJECT_SIZE_CHECK_1)'
    names = get_param_name_2less_list(params)
    newnames = []
    for name in names:
        if name == "flags" or name == "flag":
            newnames.append("OPENOSC_USE_FORTIFY_LEVEL - 1")
        elif name == "s_len" or name == "slen":
            newnames.append(bos_dest)
        else:
            newnames.append(name)
    return ', '.join(newnames)


def replace_flag_slen_withfmt_params(params):
    '''
    Replace flag/slen parameters, but keep fmt parameter.
    '''
    (dest_type, dest_param) = get_dest_param(params)
    #param_list = get_param_list_from_params_string(params)
    bos_dest = '__builtin_object_size(' + dest_param + ', OSC_OBJECT_SIZE_CHECK_1)'
    names = get_param_name_list(params)[:-1]
    newnames = []
    for name in names:
        if name == "flags" or name == "flag":
            newnames.append("OPENOSC_USE_FORTIFY_LEVEL - 1")
        elif name == "s_len" or name == "slen":
            newnames.append(bos_dest)
        else:
            newnames.append(name)
    return ', '.join(newnames)


def generate_va_args_redefine_code0(funcname, params):
    '''
    Generate the original function remapping macro using __VA_ARGS__ to replace "..."
    '''
    code = ''
    code += '#define ' + funcname + '(' + get_comma_joined_param_names(params) + ') \\\n'
    code += ' (' + funcname.upper() + '_NOMAP_CASE '
    code += funcname + '(' + ', '.join(get_param_name_2less_list(params)) + ', __VA_ARGS__))\n'
    return code


def generate_va_args_redefine_code(funcname, params, magic_str='_NOMAP_CASE'):
    '''
    Generate the function remapping macro using __VA_ARGS__ to replace "..."
      If magic_str is NOMAP, then map to the original function itself;
      If magic_str is not NOMAP, then map to the glibc *_chk function.
    '''
    glibc_chk_funcname = "__" + funcname + "_chk"
    glibc_chk_prototype = ''
    if glibc_chk_funcname in glibc_print_chk_prototype_db:
        glibc_chk_prototype = glibc_print_chk_prototype_db[glibc_chk_funcname]
    if "..." not in glibc_chk_prototype:
        return ''
    if magic_str == '_NOMAP_CASE':
        return generate_va_args_redefine_code0(funcname, params)
    (retval, chk_funcname, chk_params) = get_func_params_from_prototype(glibc_chk_prototype)
    first_params = delete_flag_slen_nofmt_3dots_params(chk_params)
    second_params = replace_flag_slen_nofmt_params(chk_params)
    code = ''
    code += '#define ' + funcname + '(' + first_params + ') \\\n'
    code += ' (' + funcname.upper() + magic_str + ' '
    code += chk_funcname + '(' + second_params + ', __VA_ARGS__))\n'
    return code


def generate_gnu_redirect_func_body_new(retval, funcname, params):
    '''
    Generate both the declaration of the alias function and the fortify function body
    of the function that calls the NOMAP alias function for ASM-Label redirect mechanism.
    '''
    va_args_code = generate_va_args_redefine_code(funcname, params)
    if not va_args_code:
        return generate_gnu_redirect_func_body(retval, funcname, params)
    func_code = generate_gnu_redirect_func_body(retval, funcname, params)
    #func_code = generate_gnu_redirect_func_body_with_va_arg_pack(funcname, magic_str)
    code = ''
    code += '#ifdef __va_arg_pack\n'
    code += func_code
    code += '#elif !defined __cplusplus\n\n'
    code += va_args_code
    code += '\n#endif\n'
    return code


def generate_gnu_redirect_func_body_with_va_arg_pack(funcname, magic_str):
    '''
    Generate both the declaration of the alias function and the fortify function body
    of the function that calls the NOMAP alias function for ASM-Label redirect mechanism.
    '''
    glibc_chk_funcname = "__" + funcname + "_chk"
    glibc_chk_prototype = ''
    if glibc_chk_funcname in glibc_print_chk_prototype_db:
        glibc_chk_prototype = glibc_print_chk_prototype_db[glibc_chk_funcname]
    if "..." not in glibc_chk_prototype:
        return ''
    (retval, chk_funcname, chk_params) = get_func_params_from_prototype(glibc_chk_prototype)
    second_params = replace_flag_slen_withfmt_params(chk_params)
    second_params += ', __va_arg_pack ()'
    code = ''
    #code += generate_gnu_redirect_func_declaration(retval, funcname, params)
    code += 'extern ' + glibc_chk_prototype + '\n\n'
    code += '__fortify_function ' + retval + '\n'
    code += '__NTH (' + funcname + '(' + delete_flag_slen_params(chk_params) + '))\n{\n'
    #code += '    return (' + funcname.upper() + '_NOMAP_CASE '
    code += '    return (' + funcname.upper() + magic_str + ' '
    code += chk_funcname + '('
    code += second_params + '));\n}\n\n'
    return code


def generate_gnu_redirect_func_body(retval, funcname, params):
    '''
    Generate both the declaration of the alias function and the fortify function body
    of the function that calls the NOMAP alias function for ASM-Label redirect mechanism.
    '''
    code = ''
    code += generate_gnu_redirect_func_declaration(retval, funcname, params)
    code += '__fortify_function ' + retval + '\n'
    code += '__NTH (' + funcname + '(' + params + '))\n{\n'
    code += '    return (' + funcname.upper() + '_NOMAP_CASE '
    code += get_gnu_redirect_function_name(funcname) + '('
    #code += get_comma_joined_param_names(params) + '));\n}\n'
    code += replace_3dots_with_va_args(get_comma_joined_param_names(params)) + '));\n}\n\n'
    return code


def generate_osc_mapping_func_body_new(retval, funcname, params, magic_str='_NOMAP_CASE'):
    '''
    Generate both the declaration of the alias function and the fortify function body
    of the function that calls the NOMAP alias function for ASM-Label redirect mechanism.
    TODO: There is no need to do the mapping to _chk function for NOMAP case!!!!
    '''
    va_args_code = generate_va_args_redefine_code(funcname, params, magic_str)
    if not va_args_code:
        code = generate_osc_mapping_func_body(retval, funcname, params)
        code += generate_osc_redefine_macro_code(funcname, params)
        return code
    func_code = generate_osc_mapping_func_body(retval, funcname, params)
    func_code += generate_osc_redefine_macro_code(funcname, params)
    #func_code = generate_osc_mapping_func_body_with_va_arg_pack(funcname, magic_str)
    code = ''
    code += '#ifdef __va_arg_pack\n'
    code += func_code
    code += '#elif !defined __cplusplus\n\n'
    code += va_args_code
    code += '\n#endif\n'
    return code


def generate_osc_mapping_func_body_with_va_arg_pack(funcname, magic_str):
    '''
    Generate both the declaration of the alias function and the fortify function body
    of the function that calls the NOMAP alias function for ASM-Label redirect mechanism.
    '''
    glibc_chk_funcname = "__" + funcname + "_chk"
    glibc_chk_prototype = ''
    if glibc_chk_funcname in glibc_print_chk_prototype_db:
        glibc_chk_prototype = glibc_print_chk_prototype_db[glibc_chk_funcname]
    if "..." not in glibc_chk_prototype:
        return ''
    (retval, chk_funcname, chk_params) = get_func_params_from_prototype(glibc_chk_prototype)
    second_params = replace_flag_slen_withfmt_params(chk_params)
    second_params += ', __va_arg_pack ()'
    code = ''
    code += 'extern ' + glibc_chk_prototype + '\n\n'
    code += 'static inline __attribute__ ((always_inline))\n'
    code += retval + '\nopenosc_' + funcname + ' (' + delete_flag_slen_params(chk_params) + ')'
    code += '\n{\n'
    if has_dest_param(funcname):
        #prototype = get_func_prototype_from_man(funcname)
        #(retval, funcname, params) = get_func_params_from_prototype(prototype)
        (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(chk_params)
        if "char" in dest_type or "wchar_t" in dest_type:
            bosc_check_type = "OSC_OBJECT_SIZE_CHECK_1"
        #print("yongkuiyongkui: prototype: " + prototype)
        #print("yongkuiyongkui: dest_param: " + dest_param)
        code += '    size_t _sz = __builtin_object_size(' + dest_param + ', ' + bosc_check_type + ');\n'
    #code += '    return (' + funcname.upper() + '_NOMAP_CASE '
    code += '    return (' + funcname.upper() + magic_str + ' '
    code += chk_funcname + '('
    code += second_params + '));\n}\n\n'
    return code


def generate_osc_mapping_func_body(retval, funcname, params):
    '''
    Generate the always_inline function body of the function that calls the NOMAP original function for macro redefine mechanism.
    '''
    code = ''
    if "..." not in params:
        code += 'extern ' + retval + ' __' + funcname + '_to_buf (size_t dest_len, ' + params + ');\n\n'
    code += 'static inline __attribute__ ((always_inline))\n'
    code += retval + '\nopenosc_' + funcname + ' (' + params + ')'
    code += '\n{\n'
    code += '    return (' + funcname.upper() + '_NOMAP_CASE ' + funcname + '('
    #code += get_comma_joined_param_names(params) + '));\n}\n\n'
    code += replace_3dots_with_va_args(get_comma_joined_param_names(params)) + '));\n}\n\n'
    return code


def generate_osc_nomap_func_redirect(retval, funcname, params):
    '''
    Generate both the code for NOMAP ASM-Label redirect mechanism. Also write the code to .h file.
    '''
    print(HDR1)
    print("Now generating OpenOSC nomap code for ASM-label redirect method for: " + funcname)
    print(HDR1)
    code = '\n'
    code += '/* Mapping for ' + funcname + ' */\n\n'
    code += generate_gnu_redirect_func_body_new(retval, funcname, params)
    print(code)
    openosc_write_filename("openosc_fortify_redirect_nomap.h", code)
    return code


def generate_osc_nomap_func_redefine(retval, funcname, params):
    '''
    Generate both the always_inline function body of the function that calls the NOMAP original function
    and the function macro define code for macro redefine mechanism. Also write the code to .h file.
    '''
    print(HDR1)
    print("Now generating OpenOSC nomap code for macro define method for: " + funcname)
    print(HDR1)
    code = '\n'
    code += '/* Mapping for ' + funcname + ' */\n\n'
    code += generate_osc_mapping_func_body_new(retval, funcname, params)
    #code += generate_osc_redefine_macro_code(funcname, params)
    print(code)
    openosc_write_filename("openosc_fortify_redefine_nomap.h", code)
    return code


def generate_osc_nomap_code(prototype, int_magic):
    '''
    Generate NOMAP code for both ASM-Label Redirect method and Function-Macro Redefine method.
    Write the generated code to openosc_fortify_redirect_nomap.h and openosc_fortify_redefine_nomap.h files.
    '''
    print(HDR2)
    print("Now generating OpenOSC nomap code for: " + prototype)
    print(HDR2)
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    code = ''
    code += '\n'
    code += generate_osc_nomap_func_redirect(retval, funcname, params)
    code += generate_osc_nomap_func_redefine(retval, funcname, params)
    #print(code)
    return code


def generate_osc_map_code(prototype, int_magic):
    '''
    Generate MAP code for a function with specified magic word.
    Write the generated code to openosc_fortify_redirect_map.h and openosc_fortify_redefine_map.h files.
    :param prototype: function prototype
    :param int_magic: 64bit integer magic word
    :returns the generated code
    '''
    print(HDR2)
    print("Now generating OpenOSC map code for: " + prototype)
    print(HDR2)
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    code = ''
    code += '\n'
    code += generate_openosc_redefine_map_code_new(prototype)
    code += generate_openosc_redirect_map_code_new(prototype)
    #print(code)
    #print(HDR2)
    return code


glibc_print_chk_functions_prototype = '''
int
__asprintf_chk (char **result_ptr, int flags, const char *format, ...);

int
__dprintf_chk (int d, int flags, const char *format, ...);

int
__fprintf_chk (FILE *fp, int flag, const char *format, ...);

int
__fwprintf_chk (FILE *fp, int flag, const wchar_t *format, ...);

int
__obstack_vprintf_chk (struct obstack *obstack, int flags, const char *format,
		       va_list args);

int
__obstack_printf_chk (struct obstack *obstack, int flags, const char *format,
		      ...);

int
__printf_chk (int flag, const char *format, ...);

int
__snprintf_chk (char *s, size_t maxlen, int flags, size_t slen,
		 const char *format, ...);

int
__sprintf_chk (char *s, int flags, size_t slen, const char *format, ...);

int
__swprintf_chk (wchar_t *s, size_t n, int flag, size_t s_len,
		const wchar_t *format, ...);

int
__vasprintf_chk (char **result_ptr, int flags, const char *format,
		 va_list args);

int
__vdprintf_chk (int d, int flags, const char *format, va_list arg);

int
__vfprintf_chk (FILE *fp, int flag, const char *format, va_list ap);

int
__vfwprintf_chk (FILE *fp, int flag, const wchar_t *format, va_list ap);

int
__vprintf_chk (int flag, const char *format, va_list ap);

int
__vsnprintf_chk (char *s, size_t maxlen, int flags, size_t slen,
		  const char *format, va_list args);

int
__vsprintf_chk (char *s, int flags, size_t slen, const char *format,
		 va_list args);

int
__vswprintf_chk (wchar_t *s, size_t maxlen, int flags, size_t slen,
		 const wchar_t *format, va_list args);

int
__vwprintf_chk (int flag, const wchar_t *format, va_list ap);

int
__wprintf_chk (int flag, const wchar_t *format, ...);
'''

fortify_functions2 = [
"asprintf",
"dprintf",
"fprintf",
"fwprintf",
"printf",
"snprintf",
"sprintf",
"swprintf",
"wprintf"
]

initial_osc_functions = [
"memcpy",
"memmove",
"memset",
"bcopy",
"bzero",
"strcpy",
"strncpy",
"strcat",
"strncat",
"strnlen",
"vsnprintf",
]

initial_safec_functions = [
"memcmp_s",
"memcpy_s",
"strcat_s",
"strcmp_s",
"strcpy_s",
"strncat_s",
"strncpy_s",
"strnlen_s",
"strstr_s",
]

fortify_functions = [
"asprintf",
"dprintf",
"fprintf",
"fwprintf",
"printf",
"snprintf",
"sprintf",
"swprintf",
"wprintf",
#"asprintf",
"confstr",
#"dprintf",
#"explicit",
#"fdelt",
"fgets",
"fgets_unlocked",
"fgetws",
"fgetws_unlocked",
#"fprintf",
"fread",
"fread_unlocked",
#"fwprintf",
"getcwd",
"getdomainname",
"getgroups",
"gethostname",
"gets",
"getwd",
"longjmp",
"mbsnrtowcs",
"mbsrtowcs",
"mbstowcs",
#"memcpy",
#"memmove",
"mempcpy",
#"memset",
#"obprintf",
"poll",
"ppoll",
#"pread64",
"pread",
#"printf",
"read",
"readlinkat",
"readlink",
"realpath",
"recv",
"recvfrom",
#"snprintf",
#"sprintf",
"stpcpy",
"stpncpy",
#"strcat",
#"strcpy",
#"strncat",
#"strncpy",
#"swprintf",
"ttyname_r",
"vasprintf",
"vdprintf",
"vfprintf",
"vfwprintf",
"vprintf",
#"vsnprintf",
"vsprintf",
"vswprintf",
"vwprintf",
"wcpcpy",
"wcpncpy",
"wcrtomb",
"wcscat",
"wcscpy",
"wcsncat",
"wcsncpy",
"wcsnrtombs",
"wcsrtombs",
"wcstombs",
"wctomb",
"wmemcpy",
"wmemmove",
"wmempcpy",
"wmemset",
#"wprintf",
]


fortify_functions3 = [
"asprintf",
"confstr",
"dprintf",
#"explicit",
#"fdelt",
"fgets",
"fgets_unlocked",
"fgetws",
"fgetws_unlocked",
"fprintf",
"fread",
"fread_unlocked",
"fwprintf",
"getcwd",
"getdomainname",
"getgroups",
"gethostname",
"gets",
"getwd",
"longjmp",
"mbsnrtowcs",
"mbsrtowcs",
"mbstowcs",
#"memcpy",
#"memmove",
"mempcpy",
#"memset",
#"obprintf",
"poll",
"ppoll",
#"pread64",
"pread",
"printf",
"read",
"readlinkat",
"readlink",
"realpath",
"recv",
"recvfrom",
"snprintf",
"sprintf",
"stpcpy",
"stpncpy",
#"strcat",
#"strcpy",
#"strncat",
#"strncpy",
"swprintf",
"ttyname_r",
"vasprintf",
"vdprintf",
"vfprintf",
"vfwprintf",
"vprintf",
#"vsnprintf",
"vsprintf",
"vswprintf",
"vwprintf",
"wcpcpy",
"wcpncpy",
"wcrtomb",
"wcscat",
"wcscpy",
"wcsncat",
"wcsncpy",
"wcsnrtombs",
"wcsrtombs",
"wcstombs",
"wctomb",
"wmemcpy",
"wmemmove",
"wmempcpy",
"wmemset",
"wprintf",
]


def generate_functions_runtime_check_macro_code(functions):
    '''
    Generate runtime check macro for openosc_fortify_redefine_map.h file.
    :param functions: a list of function names.
    "returns the generated code
    '''
    print("Now generating runtime check MACRO code for " + str(len(functions)) + " functions.\n")
    code = ''
    code += osc_runtime_check_macro_template
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_runtime_check_macro(prototype)
    code += '\n#else  /* OSC_RUNTIME_CHK != OSC_RUNTIME_USE_LIBOSC */\n\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_original_runtime_check_macro(prototype)
    code += '\n#endif  /* OSC_RUNTIME_CHK */\n'
    #print(code)
    #openosc_write_file(g_outfile, code)
    return code


def generate_functions_compiletime_check_macro_code(functions):
    '''
    Generate compile-time check macro for openosc_fortify_redefine_map.h file.
    :param functions: a list of function names.
    "returns the generated code
    '''
    print("Now generating compile time check MACRO code for " + str(len(functions)) + " functions.\n")
    code = ''
    code += osc_compiletime_check_macro_template
    code += '\n'
    index = 0
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        index += 1
        print("Function Index: " + str(index))
        print(func + " ==> " + prototype)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_compiletime_check_macro(prototype, 'OSC_ASSERT_USE_ERR_ATTR')
    code += '\n#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_BUILTIN)\n\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_compiletime_check_macro(prototype, 'OSC_ASSERT_USE_BUILTIN')
    code += '\n#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_RUNTIME_CHK)\n\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_compiletime_check_macro(prototype, 'OSC_ASSERT_USE_RUNTIME_CHK')
    code += '\n#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_NONE)\n\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if not prototype or "..." in prototype:
            continue
        code += generate_osc_compiletime_check_macro(prototype, 'OSC_ASSERT_USE_NONE')
    code += osc_compiletime_check_macro_end
    #print(code)
    #openosc_write_file(g_outfile, code)
    return code


def generate_functions_map_magic_macro_code(functions, int_magic=0):
    '''
    Generate MAGIC macro code for map case for openosc_fortify_map_metric.h file.
    :param functions: a list of function names.
    "returns the generated code
    '''
    code = ''
    code += '\n#ifdef OSC_METRIC_FEATURE_ENABLED\n'
    code += '\n#include "osc_metric_objsize.h"\n\n'
    for func in functions:
        code += generate_map_magic_code_for_func(func, g_magic_words[func] + 2, 'MAGIC')
    code += '\n'
    for func in functions:
        code += generate_map_magic_code_for_func(func, g_magic_words[func] + 2, 'CASE')
    code += '\n#else  /* !OSC_METRIC_FEATURE_ENABLED */\n\n'
    for func in functions:
        code += generate_map_magic_code_for_func(func, g_magic_words[func] + 2)
    code += '\n#endif  /* OSC_METRIC_FEATURE_ENABLED */\n'
    #print(code)
    openosc_write_filename("openosc_fortify_map_metric.h", code)
    return code


def generate_functions_nomap_magic_macro_code(functions, int_magic=0):
    '''
    Generate MAGIC macro code for nomap case for openosc_fortify_nomap_metric.h file.
    :param functions: a list of function names.
    "returns the generated code
    '''
    code = ''
    code += '\n#ifdef OSC_METRIC_FEATURE_ENABLED\n\n'
    for func in functions:
        code += generate_nomap_magic_code_for_func(func, g_magic_words[func] + 1, 'MAGIC')
    code += '\n'
    for func in functions:
        code += generate_nomap_magic_code_for_func(func, g_magic_words[func] + 2, 'CASE')
    code += '\n#else  /* !OSC_METRIC_FEATURE_ENABLED */\n\n'
    for func in functions:
        code += generate_nomap_magic_code_for_func(func, g_magic_words[func] + 2)
    code += '\n#endif  /* OSC_METRIC_FEATURE_ENABLED */\n'
    #print(code)
    openosc_write_filename("openosc_fortify_nomap_metric.h", code)
    return code


openosc_nomap_mm_template = '''
#ifndef _FORTIFY_SOURCE

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_fortify_extern.h"

#if (OPENOSC_MAPPING_METHOD == OSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_fortify_redirect_nomap.h"
#else
#include "openosc_fortify_redefine_nomap.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
'''

openosc_map_mm_template = '''
#ifndef _FORTIFY_SOURCE

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_fortify_extern.h"

#if (OPENOSC_MAPPING_METHOD == OSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_fortify_redirect_map.h"
#else
#include "openosc_fortify_redefine_map.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
'''

openosc_va_arg_define_template = '''
# ifdef __va_arg_pack
#define OPENOSC_VA_ARGS       __va_arg_pack ()
# elif !defined __cplusplus
#define OPENOSC_VA_ARGS       __VA_ARGS__
# endif
'''

def delete_all_generated_code_files():
    '''
    Delete all those auto-generated files.
    '''
    files = ['openosc_fortify_extern.h',
             'openosc_fortify_map.h',
             'openosc_fortify_redirect_map.h',
             'openosc_fortify_redefine_map.h',
             'openosc_fortify_nomap.h',
             'openosc_fortify_redirect_nomap.h',
             'openosc_fortify_redefine_nomap.h',
             'openosc_fortify_map_metric.h',
             'openosc_fortify_nomap_metric.h',
             'openosc_fortify_map.c',
             'openosc_fortify_magics_curioscan',
             'openosc_fortify_nomap_test.c',
             'openosc_fortify_test.c']
    cmd = 'rm '
    for afile in files:
        cmd += afile + ' '
    cmd += ' || true'
    print(cmd)
    output = subprocess.check_output(cmd, shell=True, stderr=open(os.devnull, 'w'))
    return


def generate_openosc_file_start_code(functions):
    '''
    Write "file_start" code to all those auto-generated files.
    :param functions: a list of function names.
    :returns None
    '''
    code = '\n#ifndef OPENOSC_USE_FORTIFY_LEVEL\n'
    code += '#define OPENOSC_USE_FORTIFY_LEVEL 2\n'
    code += '#endif\n'
    openosc_write_filename("openosc_fortify_redefine_map.h", code, "file_start")
    openosc_write_filename("openosc_fortify_redirect_map.h", code, "file_start")
    code = '\n'
    openosc_write_filename("openosc_fortify_nomap_metric.h", code, "file_start")
    openosc_write_filename("openosc_fortify_map_metric.h", code, "file_start")
    openosc_write_filename("openosc_fortify_redefine_nomap.h", code, "file_start")
    openosc_write_filename("openosc_fortify_redirect_nomap.h", code, "file_start")
    code = '\n#include "openosc_fortify_nomap_metric.h"\n'
    openosc_write_filename("openosc_fortify_nomap.h", code, "file_start")
    code = '\n#include "openosc_fortify_map_metric.h"\n'
    openosc_write_filename("openosc_fortify_map.h", code, "file_start")
    openosc_write_filename("openosc_fortify_nomap.h", openosc_nomap_mm_template)
    openosc_write_filename("openosc_fortify_map.h", openosc_map_mm_template)
    code = get_all_include_file_lines(functions)
    code += '\n'
    openosc_write_filename("openosc_fortify_extern.h", code, "file_start")
    openosc_write_filename("openosc_fortify_map.c", code, "file_start")
    openosc_write_filename("openosc_fortify_test.c", code, "file_start")
    openosc_write_filename("openosc_fortify_nomap_test.c", code, "file_start")
    code = get_all_prototype_lines(functions)
    openosc_write_filename("openosc_fortify_extern.h", code)
    #openosc_write_file(g_outfile, code, "openosc_fortify_redefine_map.h", "file_start")
    #openosc_write_file(g_outfile, code, "openosc_fortify_redirect_map.h", "file_start")


def generate_openosc_file_end_code(functions):
    '''
    Write "file_end" code to all those auto-generated files.
    :param functions: a list of function names.
    :returns None
    '''
    code = '\n'
    openosc_write_filename("openosc_fortify_redefine_map.h", code, "file_end")
    openosc_write_filename("openosc_fortify_redirect_map.h", code, "file_end")
    openosc_write_filename("openosc_fortify_nomap_metric.h", code, "file_end")
    openosc_write_filename("openosc_fortify_map_metric.h", code, "file_end")
    openosc_write_filename("openosc_fortify_redefine_nomap.h", code, "file_end")
    openosc_write_filename("openosc_fortify_redirect_nomap.h", code, "file_end")
    openosc_write_filename("openosc_fortify_nomap.h", code, "file_end")
    openosc_write_filename("openosc_fortify_map.h", code, "file_end")
    openosc_write_filename("openosc_fortify_extern.h", code, "file_end")
    #openosc_write_file(g_outfile, code, "openosc_fortify_redefine_map.h", "file_end")
    #openosc_write_file(g_outfile, code, "openosc_fortify_redirect_map.h", "file_end")


def get_all_include_file_lines(functions):
    '''
    Get all #include lines for a list of functions.
    :param functions: a list of function names.
    :returns all "#include <xxx.h>" lines as a multi-line string.
    '''
    inc_set = set()
    for func in functions:
        include_lines = get_func_include_from_man(func)
        for line in include_lines:
            inc_set.add(line)
    return '\n'.join(inc_set)


def get_all_prototype_lines(functions):
    '''
    Get all prototypes for a list of functions.
    :param functions: a list of function names.
    :returns all function prototypes as a multi-line string.
    '''
    lines = []
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        #if prototype and "..." not in prototype:
        if prototype:
            lines.append("extern " + prototype)
    return '\n'.join(lines)


def generate_fortify_functions_real_code(functions):
    '''
    Generate most of the fortify-source code for a list of functions.
    It generates the following 9 files:
      openosc_fortify_nomap_metric.h/openosc_fortify_map_metric.h
      openosc_fortify_nomap.h/openosc_fortify_redefine_nomap.h/openosc_fortify_redirect_nomap.h
      openosc_fortify_map.h/openosc_fortify_redefine_map.h/openosc_fortify_redirect_map.h
      openosc_fortify_map.c
    :param functions: a list of function names.
    :returns None
    '''
    which_db = dict()
    #openosc_write_file(g_outfile, openosc_cfile_top_template)
    index = 0
    for func in functions:
        include_lines = get_func_include_from_man(func)
        prototype = get_func_prototype_from_man(func)
        index += 1
        print("Function Index: " + str(index))
        print(include_lines)
        print(func + " ==> " + prototype)
        if not prototype:
            like_which = 'no_prototype'
            which_db.setdefault(like_which, [0, []])
            which_db[like_which][0] += 1
            which_db[like_which][1].append(func)
            print("No function prototype found for " + func + ", Please specify prototype via -p option.")
            print("")
            continue
        like_which = "like_default"
        #if "..." in prototype:
        if False:
            print("This is printf-like function, skip it\n")
            like_which = "like_printf"
        else:
            generate_osc_nomap_code(prototype, get_wrap_magic_word(g_magic_word, g_magic_alignment)+1)
            generate_osc_map_code(prototype, g_magic_word)
            like_which = generate_runtime_check_code2(prototype)
            #generate_openosc_test_code(prototype)
        which_db.setdefault(like_which, [0, []])
        which_db[like_which][0] += 1
        which_db[like_which][1].append(func)
        '''
        if like_which in which_db:
            which_db[like_which] += 1
        else:
            which_db[like_which] = 1
        '''
    print("Some stats regarding all fortified functions")
    #print(which_db)
    print(json.dumps(which_db, indent=4, sort_keys=True))
    #save_json_db(RESULT_JSON_FILE, which_db)
    #save_json_db("openosc_fortify_functions.json", which_db)


'''
/* Mapping for memcpy */

void *
__memcpy_to_buf(size_t dest_len, void *dst, const void *src, size_t len)
'''
memcpy_runtime_check_code_template = '''
{
    unsigned int osc_abort = OSC_DEF_ABORT_STATE;
    if (%len% > dest_len) {
        if (osc_log) {
            danger_error("memcpy", dest_len, %len%);
        }
        osc_get_config(&osc_abort);
        if (osc_abort) {
            abort();
        }
        if (osc_truncate) {
            %len% = dest_len;
        }
    }
#undef memcpy
'''
'''
    return (memcpy(dst, src, len));
}
'''

'''
/* Mapping for memset */

void *
__memset_to_buf(size_t dest_len, void *dst, int c, size_t len)
'''
memset_runtime_check_code_template = '''
{
    unsigned int osc_abort = OSC_DEF_ABORT_STATE;

    if (%len% > dest_len) {
        if (osc_log) {
            danger_error("memset", dest_len, %len%);
        }
        osc_get_config(&osc_abort);
        if (osc_abort) {
            abort();
        }
        if (osc_truncate) {
            %len% = dest_len;
        }
    }
#undef memset
'''
'''
    return (memset(dst, c, len));
}
'''

todo_code_template = '''
{
    /* TODO: Add code */
'''

openosc_cfile_top_template = '''
/*------------------------------------------------------------------
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 *------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osc_common.h"

'''

def generate_openosc_functions_test_code(functions, test_type=''):
    '''
    Generate openosc_fortify_test.c testing code for a list of functions.
    :param functions: a list of function names
    :param test_type: if 'NOMAP', generate for nomap case; otherwise, for map case.
    :returns the generated testing code.
    '''
    code = ''
    code += get_all_include_file_lines(functions)
    code += '\n/* For rand() and time() system calls */\n'
    code += '#include <stdlib.h>\n'
    code += '#include <time.h>\n\n'
    code += '#define OPENOSC_TEST_RAND_RANGE 5\n\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if test_type == 'NOMAP':
            code += generate_openosc_nomap_test_code(prototype, 'test')
        else:
            code += generate_openosc_test_code(prototype, 'test')
    code += 'int main(void) {\n'
    code += '    srand(time(NULL));\n'
    for func in functions:
        prototype = get_func_prototype_from_man(func)
        if test_type == 'NOMAP':
            code += generate_openosc_nomap_test_code(prototype, 'main')
        else:
            code += generate_openosc_test_code(prototype, 'main')
    code += '    return 0;\n}\n\n'
    if test_type == 'NOMAP':
        openosc_write_filename("openosc_fortify_nomap_test.c", code)
    else:
        openosc_write_filename("openosc_fortify_test.c", code)
    return code


def get_default_value_list_for_parameters(params):
    values = []
    param_list = get_param_list_from_params_string(params)
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        if param_name == "...":
            values.pop()
            if "wchar_t" in params:
                values.append('L"%s"')
                values.append('L"abc"')
            else:
                values.append('"%s"')
                values.append('"abc"')
            return values
        elif "va_list" in param_type:
            values.pop()
            if "wchar_t" in params:
                values.append('L""')
                values.append('myap')
            else:
                values.append('""')
                values.append('myap')
            return values
        if '**' in param_type:
            if "const " in param_type:
                values.append("(" + param_type + ") pmysrcbuf ")
            else:
                values.append("(" + param_type + ") pmydstbuf ")
        elif '*' in param_type:
            if "const " in param_type:
                values.append("(" + param_type + ") mysrcbuf ")
            else:
                values.append("(" + param_type + ") mydstbuf ")
        elif 'size_t' in param_type or "int" in param_type:
            values.append("mylen")
        elif "jmp_buf" == param_type:
            values.append(" 0 ")
        else:
            values.append("(" + param_type + ") 0 ")
    return values


def generate_openosc_nomap_test_code(prototype, codetype=''):
    '''
    Generate openosc_fortify_nomap_test.c testing code for a single function.
    :param prototype: function prototype string
    :param codetype: if "test", then generates the definition of openosc_test_memcpy() function;
                     if "main", then generates the invocation of openosc_test_memcpy() function.
    :returns the generated testing code.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    #param_list = get_param_list_from_params_string(params)
    #comma_params = get_comma_joined_param_names(params)
    code = ''
    if codetype == 'test':
        dest_chartype = "char"
        dest_charsize = "sizeof(char)"
        src_chartype = "char"
        literal_prefix = ''
        downfactor = '20'
        if "wchar_t" in dest_type:
            dest_chartype = "wchar_t"
            dest_charsize = "sizeof(wchar_t)"
            downfactor = '1000000000'
        if "wchar_t" in src_type:
            src_chartype = "wchar_t"
            literal_prefix = 'L'
        src_buf = src_param
        code += '\nint openosc_test_' + funcname + '(void) {\n'
        code += '    int mylen = 8;\n'
        code += '    ' + dest_chartype + ' mydstbuf[15 * ' + dest_charsize + '];\n'
        code += '    ' + dest_chartype + ' **pmydstbuf = (' + dest_chartype + ' **)(&mydstbuf);\n'
        code += '    const ' + src_chartype + ' mysrcbuf[20] = ' + literal_prefix + '"I am the source";\n'
        code += '    const ' + src_chartype + ' **pmysrcbuf = (const ' + src_chartype + ' **)(&mysrcbuf);\n'
        if "va_list" in params:
            code += '    va_list myap;\n'
        if "mbstate_t" in params:
            code += '    mbstate_t state;\n    mbstate_t *ps = &state;\n'
            code += '    size_t nms = 1;\n    size_t nwc = 1;\n'
        invoke_params = ", ".join(get_default_value_list_for_parameters(params))
        code += '    printf("Line %d, func %s, mylen is: %d\\n", __LINE__, __FUNCTION__, mylen);\n'
        code += '    ' + funcname + '(' + invoke_params + ');          /* function invocation */\n'
        code += '    printf("End of testing ' + funcname + '\\n");\n'
        code += '    return 0;\n'
        code += '}\n\n'
    elif codetype == 'main':
        code += '    (void)openosc_test_' + funcname + '();\n'
    return code


def generate_openosc_test_code(prototype, codetype=''):
    '''
    Generate openosc_fortify_test.c testing code for a single function.
    :param prototype: function prototype string
    :param codetype: if "test", then generates the definition of openosc_test_memcpy() function;
                     if "main", then generates the invocation of openosc_test_memcpy() function.
    :returns the generated testing code.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    comma_params = get_comma_joined_param_names(params)
    code = ''
    if dest_param and copylen and src_param:
        dest_chartype = "char"
        dest_charsize = "sizeof(char)"
        src_chartype = "char"
        literal_prefix = ''
        downfactor = '20'
        if "wchar_t" in dest_type:
            dest_chartype = "wchar_t"
            dest_charsize = "sizeof(wchar_t)"
            downfactor = '1000000000'
        if "wchar_t" in src_type:
            src_chartype = "wchar_t"
            literal_prefix = 'L'
        src_buf = src_param
        if "**" in src_type:
            #comma_params = comma_params.replace(src_param + ',', '&' + src_param + ',')
            src_buf = "mysrcbuf"
        if codetype == 'test':
            code += '\nint openosc_test_' + funcname + '(void) {\n'
            if "mbstate_t" in params:
                code += '    mbstate_t state;\n    mbstate_t *ps = &state;\n'
                code += '    size_t nms = 1;\n    size_t nwc = 1;\n'
            if "int dirfd," in params:
                code += '    int dirfd = AT_FDCWD;\n'
            code += '    int mylen = 8;\n'
            code += '    ' + dest_chartype + ' ' + dest_param + '[5 * ' + dest_charsize + '];\n'
            code += '    const ' + src_chartype + ' ' + src_buf + '[20] = ' + literal_prefix + '"I am the source";\n'
            if "**" in src_type:
                code += '    ' + src_type + ' ' + src_param + ' = (' + src_type + ')(&' + src_buf + ');\n'
            code += '    size_t ' + copylen + ' = 4;\n'
            code += '    ' + funcname + '(' + comma_params + ');          /* case 1 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '#if 0  /* comment out to avoid compile-time error */\n'
            code += '    ' + copylen + ' = 7;\n'
            code += '    ' + funcname + '(' + comma_params + ');          /* case 2 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '#endif\n'
            code += '    ' + copylen + ' = rand() % OPENOSC_TEST_RAND_RANGE;\n'
            code += '    ' + funcname + '(' + comma_params + ');          /* case 3 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '    ' + copylen + ' = (' + src_buf + '[18]-' + dest_param + '[2])/' + downfactor + ';\n'
            code += '    ' + funcname + '(' + comma_params + ');          /* case 3 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '    ' + copylen + ' = (*((char *)' + '&mylen - ' + src_buf + '[18] * 8))/' + downfactor + ';\n'
            code += '    ' + funcname + '(' + comma_params + ');          /* case 3 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '    ' + copylen + ' = 1;\n'
            new_comma_params = comma_params.replace(dest_param + ',', '(' + dest_type + ')((char *)&mylen - ' + dest_param + '[18] * 4),')
            code += '    ' + funcname + '(' + new_comma_params + ');          /* case 4 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            new_comma_params = comma_params.replace(dest_param + ',', '(' + dest_type + ')((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE),')
            code += '    ' + funcname + '(' + new_comma_params + ');          /* case 4 */\n'
            code += '    printf("Line %d, func %s, copylen is: %d\\n", __LINE__, __FUNCTION__, ' + copylen + ');\n'
            code += '    printf("End of testing ' + funcname + '\\n");\n'
            code += '    return 0;\n'
            code += '}\n\n'
        elif codetype == 'main':
            code += '    (void)openosc_test_' + funcname + '();\n'
    else:
        code += generate_openosc_nomap_test_code(prototype, codetype)
    return code


def generate_code_like_memcpy(funcname, copylen):
    template = memcpy_runtime_check_code_template
    code = template.replace("memcpy", funcname)
    code = code.replace("%len%", copylen)
    return code


def generate_code_like_memset(funcname, copylen):
    template = memset_runtime_check_code_template
    code = template.replace("memset", funcname)
    code = code.replace("%len%", copylen)
    return code


def generate_runtime_check_code(prototype):
    '''
    Generate openosc_fortify_map.c runtime check code for a function prototype.
    :param prototype: function prototype string
    :returns the like-which type of this function prototype.
    '''
    template = memcpy_runtime_check_code_template
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    if "..." in params:
        return "like_printf"
    print(HDR1)
    print("Now generating code for runtime check code for: " + prototype)
    print(HDR1)
    code = '/* Mapping for '  + funcname + ' */\n\n'
    code += retval
    code += '\n__' + funcname + '_to_buf (size_t dest_len, ' + params + ')'
    like_which = "like_memcpy"
    code2 = todo_code_template
    if dest_param:
        if copylen and src_param:
            code2 = generate_code_like_memcpy(funcname, copylen)
        elif copylen and not src_param:
            like_which = "like_memset"
            code2 = generate_code_like_memset(funcname, copylen)
        elif not copylen and src_param:
            like_which = "like_strcpy"
            #code2 = generate_code_like_memset(funcname, "MB_CUR_MAX")
        else:
            like_which = "like_dest_only"
            #code2 = generate_code_like_memset(funcname, "MB_CUR_MAX")
    else:
        like_which = "like_other"
        if src_param and copylen:
            like_which  = "like_strnlen"
        elif "print" in funcname:
            like_which = "vprintf_like"
    code += code2
    comma_params = get_comma_joined_param_names(params)
    code += '\n    return (' + funcname + '(' + comma_params + '));\n}\n\n'
    print(code)
    openosc_write_filename("openosc_fortify_map.c", code)
    print(HDR2)
    return like_which


def strip_semi_colon_in_prototype(prototype):
    '''
    Strip the trailing ; if it is in the function prototype.
    '''
    proto = prototype.strip()
    if proto[-1] == ';':
        return proto[:-1]
    return proto


def insert_glibc_print_chk_flag_with_destlen(params, flag_index):
    '''
    Insert "int (int)dest_len" at flag_index position of params, return comma-joined param names.
    '''
    param_list = get_param_list_from_params_string(params)
    param_list.insert(flag_index, "int (int)dest_len")
    names = []
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        names.append(param_name)
    return ', '.join(names)


def insert_glibc_print_chk_param_bos(params, flag_index, slen_index):
    '''
    Insert both the flag/flags and slen/s_len params, return comma-joined param names.
    '''
    (dest_type, dest_param) = get_dest_param(params)
    param_list = get_param_list_from_params_string(params)
    bos_dest = '__builtin_object_size(' + dest_param + ', OSC_OBJECT_SIZE_CHECK_1)'
    if flag_index < slen_index:
        param_list.insert(slen_index, 'size_t ' + bos_dest)
        param_list.insert(flag_index, 'int OPENOSC_USE_FORTIFY_LEVEL-1')
    else:
        param_list.insert(flag_index, 'int OPENOSC_USE_FORTIFY_LEVEL-1')
        param_list.insert(slen_index, 'size_t ' + bos_dest)
    names = []
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        names.append(param_name)
    return ', '.join(names)


def find_flag_param_index_in_params(params):
    '''
    Find the index of the "int flag"/"int flags" in glibc *print_chk function prototype parameters.
    '''
    param_list = get_param_list_from_params_string(params)
    for i in range(len(param_list)):
        param = param_list[i]
        (param_type, param_name) = get_type_name_from_param(param)
        if param_type == "int" and (param_name == "flag" or param_name == "flags"):
            return i
    return -1


def find_slen_param_index_in_params(params):
    '''
    Find the index of the slen/s_len in glibc *print_chk function prototype parameters.
    '''
    param_list = get_param_list_from_params_string(params)
    for i in range(len(param_list)):
        param = param_list[i]
        (param_type, param_name) = get_type_name_from_param(param)
        if param_type == "size_t" and (param_name == "slen" or param_name == "s_len"):
            return i
    return -1


def replace_glibc_print_chk_flag_with_destlen2(params):
    '''
    Replace the flag/flags parameter with (int)dest_len
    '''
    if "flags" in params:
        return params.replace("flags", "(int)dest_len")
    elif "flag" in params:
        return params.replace("flag", "(int)dest_len")
    return params


def replace_3dots_with_va_args(params):
    '''
    Replace the "..." parameter with "__va_arg_pack ()"
    '''
    if "..." in params:
        return params.replace("...", "__va_arg_pack ()")
    return params


def generate_runtime_check_code2(prototype):
    '''
    Generate openosc_fortify_map.c runtime check code for a function prototype.
    :param prototype: function prototype string
    :returns the like-which type of this function prototype.
    '''
    (retval, funcname, params) = get_func_params_from_prototype(prototype)
    print(HDR1)
    print("Now generating code for runtime check code for: " + prototype)
    print(HDR1)
    if "..." in params:
        print("There is no runtime check code for ... printf-like function!\n")
        return "printf_like"
    comma_params = get_comma_joined_param_names(params)
    (dest_type, dest_param, copylen, src_type, src_param) = analyze_func_params(params)
    code = '/* Mapping for '  + funcname + ' */\n\n'
    ## Add support for calling glibc print_chk functions
    glibc_chk_funcname = "__" + funcname + "_chk"
    if glibc_chk_funcname in glibc_print_chk_prototype_db:
        glibc_chk_prototype = glibc_print_chk_prototype_db[glibc_chk_funcname]
        code += "extern " + strip_semi_colon_in_prototype(glibc_chk_prototype) + ";\n\n"
    code += retval
    code += '\n__' + funcname + '_to_buf (size_t dest_len, ' + params + ')'
    like_which = "like_memcpy"
    code2 = todo_code_template
    if dest_param:
        if copylen:
            code += '\n{\n'
            code += '    unsigned int osc_abort = OSC_DEF_ABORT_STATE;\n\n'
            code += '    if (' + copylen + ' > dest_len) {\n'
            code += '        if (osc_log) {\n'
            code += '            danger_error("' + funcname + '", dest_len, ' + copylen + ');\n'
            code += '        }\n'
            code += '        osc_get_config(&osc_abort);\n'
            code += '        if (osc_abort) {\n'
            code += '            abort();\n'
            code += '        }\n'
            code += '        if (osc_truncate) {\n'
            code += '            ' + copylen + ' = dest_len;\n'
            code += '        }\n'
            code += '    }\n'
            #code += '#undef ' + funcname + '\n'
            #code += '    return (' + funcname + '(' + comma_params + '));\n'
            #code += '}\n\n'
        else:
            code += code2
    else:
        code += code2
    if dest_param:
        if copylen and src_param:
            like_which = "like_memcpy"
            #code2 = generate_code_like_memcpy(funcname, copylen)
        elif copylen and not src_param:
            like_which = "like_memset"
            #code2 = generate_code_like_memset(funcname, copylen)
        elif not copylen and src_param:
            like_which = "like_strcpy"
        else:
            like_which = "like_dest_only"
    else:
        like_which = "like_other"
        if src_param and copylen:
            like_which  = "like_strnlen"
        elif "print" in funcname:
            like_which = "vprintf_like"
    #code += code2
    ## Add support for calling glibc print_chk functions
    if glibc_chk_funcname in glibc_print_chk_prototype_db:
        glibc_chk_prototype = glibc_print_chk_prototype_db[glibc_chk_funcname]
        (glibc_retval, glibc_funcname, glibc_params) = get_func_params_from_prototype(glibc_chk_prototype)
        flag_index = find_flag_param_index_in_params(glibc_params)
        new_comma_params = insert_glibc_print_chk_flag_with_destlen(params, flag_index)
        code += '\n    return (' + glibc_funcname + '(' + new_comma_params + '));\n}\n\n'
    else:
        code += '\n    return (' + funcname + '(' + comma_params + '));\n}\n\n'
    print(code)
    openosc_write_filename("openosc_fortify_map.c", code)
    print(HDR2)
    return like_which


def openosc_write_filename(filename, code, position=''):
    '''
    Write generated code to a file. It appends to the end of the file, so writing order is important.
    :param filename: the file name to write the code.
    :param code: the code as a long string.
    :param position: file_start/file_end
    :returns None
    '''
    if not filename:
        return
    with open(filename, 'a') as f:
        if position == "file_start":
            f.write( get_openosc_h_file_top_code(filename) )
        f.write(code + '\n')
        if position == "file_end":
            f.write( get_openosc_h_file_bottom_code(filename) )


def openosc_write_file(afile, code, filename='', position=''):
    if afile:
        if filename and position == "file_start":
            afile.write('\n/* Beginning of ' + filename + ' */\n\n')
            afile.write( get_openosc_h_file_top_code(filename) )
        afile.write(code + "\n")
        if filename and position == "file_end":
            afile.write( get_openosc_h_file_bottom_code(filename) )
            afile.write('\n/* End of ' + filename + ' */\n\n')


########## Function Prototype Analysis Functions ###########

memcpy_prototype = 'void *memcpy(void *dest, const void *src, size_t n);'
strncpy_prototype = 'char *strncpy(char *dest, const char *src, size_t n);'
vsnprintf_prototype = 'int vsnprintf(char *str, size_t size, const char *format, va_list ap);'
swprintf_prototype = '''int swprintf(wchar_t *wcs, size_t maxlen,
                    const wchar_t *format, ...);'''

def get_func_name_from_prototype(prototype):
    '''
    Get the function name from a function prototype string.
    :param prototype: function prototype string
    :returns the function name.
    '''
    loc1 = prototype.find('(')
    newproto = prototype[:loc1].rstrip()
    loc = newproto.rfind('*')
    if loc < 0:
        loc = newproto.rfind(' ')
    funcname = newproto[(loc + 1):].strip()
    return funcname


def get_func_params_from_prototype(prototype):
    '''
    Get the whole string of function parameters from a function prototype string.
    :param prototype: function prototype string
    :returns the whole string of function parameters like "void *dest, const void *src, size_t n" for memcpy.
    '''
    loc1 = prototype.find('(')
    loc2 = prototype.find(')')
    params = prototype[(loc1 +1):loc2]
    newproto = prototype[:loc1].rstrip()
    loc = newproto.rfind('*')
    if loc < 0:
        loc = newproto.rfind(' ')
    funcname = newproto[(loc + 1):].strip()
    retval = newproto[:(loc + 1)]
    #print((retval, funcname, params))
    return (retval, funcname, params)


def get_param_list_from_params_string(params):
    '''
    Convert the string of function parameters to a list of "param_type param_name".
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns a list like ["void *dest", "const void *src", "size_t n"].
    '''
    tokens = params.split(",")
    return [token.strip() for token in tokens]


def get_type_name_from_param(param):
    '''
    Return (param_type, param_name) tuple for a single function parameter string of "type name".
    '''
    param = param.strip()
    loc = param.rfind('*')
    if loc < 0:
        loc = param.rfind(' ')
    param_type = param[:(loc + 1)].strip()
    param_name = param[(loc + 1):].strip()
    return (param_type, param_name)


def get_param_names_from_params(params):
    '''
    Convert the string of function parameters to a list of parameter names only.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns a list like ["dest", "src", "n"].
    '''
    names = []
    param_list = get_param_list_from_params_string(params)
    for param in param_list:
        (param_type, param_name) = get_type_name_from_param(param)
        names.append(param_name)
    return names


def get_comma_joined_param_names(params):
    '''
    Convert the string of function parameters to a new string of comma-joined parameter names only.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns a new string like "dest, src, n" for memcpy.
    '''
    names = get_param_names_from_params(params)
    return ', '.join(names)


def analyze_func_params(params):
    '''
    Anaylze the string of function parameters and find (dst,src,copylen) parameters.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns the tuple of (dst_type, dst_param, len_param, src_type, src_param)
    '''
    (dest_type, dest_param) = get_dest_param(params)
    (src_type, src_param) = get_src_param(params)
    len_param = get_copylen_param(params)
    #print("Dest param type: " + dest_type + "Dest param: " + dest_param + " Length: " + len_param + " Src param type: " + src_type + " Src param: " + src_param)
    if src_param == dest_param:
        src_param = ""
        src_type = ""
    return (dest_type, dest_param, len_param, src_type, src_param)


def get_copylen_param(params):
    '''
    Find the copy length param from the string of function parameters.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns the copy length parameter like n for memcpy.
    '''
    token_list = []
    tokens = params.split(',')
    for token in tokens:
        token = token.strip()
        #print(token)
        if token == "...":
            continue
        (param_type, param_name) = get_type_name_from_param(token)
        if '*' in param_type or "const " in param_type or "[]" in param_name:
            continue
        if param_name == "n" or param_name == "len":
            return param_name
        if "size" in param_type or "size" == param_name:
            token_list.append(token)
    #print("All the candidate parameters for copy length or buffer size are:")
    #print(token_list)
    if token_list:
        (param_type, param_name) = get_type_name_from_param(token_list[0])
        return param_name
    return ""


def get_dest_param(params):
    '''
    Find the destination buffer param from the string of function parameters.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns (dest_param_type, dest_param_name) like ("void *", "dest")
    '''
    token_list = []
    tokens = params.split(',')
    for token in tokens:
        token = token.strip()
        #print(token)
        if token == "...":
            continue
        (param_type, param_name) = get_type_name_from_param(token)
        if '*' not in param_type or "const " in param_type or "src" in param_name or "FILE" in param_type or "**" in param_type:
            continue
        if param_name == "dest" or param_name == "dst" or param_name == "destination":
            return (param_type, param_name)
        token_list.append(token)
    #print("All the candidate parameters for destinationn param are:")
    #print(token_list)
    if token_list:
        (param_type, param_name) = get_type_name_from_param(token_list[0])
        return (param_type, param_name)
    return ("", "")


def get_src_param(params):
    '''
    Find the source buffer param from the string of function parameters.
    :param params: The whole parameter string like "void *dest, const void *src, size_t n" for memcpy
    :returns (src_param_type, src_param_name) like ("const void *", "src")
    '''
    token_list = []
    tokens = params.split(',')
    for token in tokens:
        token = token.strip()
        #print(token)
        if token == "...":
            continue
        (param_type, param_name) = get_type_name_from_param(token)
        if '*' not in param_type or "format" in param_name or "dest" in param_name or "dst" in param_name or "FILE" in param_type:
            continue
        if param_name == "src" or param_name == "source":
            return (param_type, param_name)
        token_list.append(token)
    #print("All the candidate parameters for source param are:")
    #print(token_list)
    if token_list:
        (param_type, param_name) = get_type_name_from_param(token_list[0])
        return (param_type, param_name)
    return ("", "")


def get_man_section_func_output(func, section):
    '''
    Return output of "man <section> func" command.
    :param func: function name
    :param section: which section to search for manual
    :returns the command output as a string.
    '''
    cmd = 'man ' + section + ' ' + func + ' | cat '
#     print(cmd)
    output = subprocess.check_output(cmd, shell=True, stderr=open(os.devnull, 'w'))
    #print(output)
    #files = output.splitlines()
    return output


def get_man_func_output(func):
    '''
    Return output of "man 2 func" or "man 3 func".
    :param func: function name
    :returns the command output as a string.
    '''
    output = get_man_section_func_output(func, "2")
    if output:
        return output
    return get_man_section_func_output(func, "3")


def get_func_prototype_from_man3(func):
    # Convert gid_t list[] to gid_t *list for getgroups prototype
    proto = get_func_prototype_from_man(func)
    if "[]" not in proto:
        return proto
    tokens = proto.split("[]")
    for i in range(len(tokens) - 1):
        words = tokens[i].split()
        words[-1] = '*' + words[-1]
        tokens[i] = ' '.join(words)
    new_proto = ''.join(tokens)
    return new_proto


def get_func_prototype_from_man(func):
    """
    Parse "man func" output and return the function prototype.
    :param func: function name
    :returns the function prototype as a string. If not found, returns empty string.
    """
    if func in g_prototype_db:
        return g_prototype_db[func]
    man_output = get_man_func_output(func)
    prototype = ''
    synopsis_section = False
    func_found = False
    lines = man_output.splitlines()
    for line in lines:
        line = line.strip()
        if "SYNOPSIS" == line[:8]:
            synopsis_section = True
        if not synopsis_section:
            continue
        if func in line and '(' in line:
            funcname = get_func_name_from_prototype(line)
            if funcname == func:
                if ')' in line:
                    return line
                func_found = True
        if func_found:
            prototype += line + ' '
            if ')' in line:
                return prototype
    return ''


def get_func_include_from_man(func):
    """
    Parse "man func" output and return all the #include lines as a list.
    :param func: function name
    :returns a list of "#include <xxx.h>" lines.
    """
    if func in g_include_db:
        return g_include_db[func]
    man_output = get_man_func_output(func)
    synopsis_section = False
    lines = man_output.splitlines()
    result = []
    include_seen = False
    for line in lines:
        line = line.strip()
        if "SYNOPSIS" == line[:8]:
            synopsis_section = True
        if not synopsis_section:
            continue
        if "#include " in line:
            include_seen = True
            result.append(line)
        if include_seen and "#include " not in line:
            return result
    return result


def print_func_prototype(func):
    prototype = get_func_prototype_from_man(func)
    print(prototype)
    (retval, func, params) = get_func_params_from_prototype(prototype)
    print(get_dest_param(params))


def read_file_lines(afile):
    """
    Read all lines of a file.

    :param afile: a file
    :returns a list of all lines in the file
    """
    with open(afile, 'r') as f:
        lines = f.read()
        return lines.splitlines()


# Global DB to store function's prototypes and include lines.
g_prototype_db = dict()
g_include_db = dict()
glibc_print_chk_prototype_db = dict()

def update_prototype_db(func, prototype, inc_lines, prototype_db, include_db):
    '''
    Update prototype DB and include DB with prototype and inc_lines.
    '''
    if func in prototype_db:
        print("Duplicate functions found: " + func)
    prototype_db[func] = prototype
    if include_db is not None:
        include_db[func] = inc_lines


def read_prototype_lines(lines, prototype_db, include_db):
    """
    Read all function prototypes from a list of C code lines.

    :param lines: a list that contains the C code lines
    :param prototype_db: the prototype DB to update
    :param include_db: the include DB to update
    :returns a list of functions whose prototypes are read from the file.
      The function prototype/include DBs are updated too.
    """
    functions = []
    inc_lines = []
    prototype = ''
    num_functions = 0
    for line in lines:
        line = line.strip()
        if not line or line[:2] == '//':  # ignore empty lines or lines starting with '//'
            continue
        if "#include " == line[:9]:
            inc_lines.append(line)
        else:
            prototype += line + ' '
            if ')' in line:  ## end of prototype
                (retval, func, params) = get_func_params_from_prototype(prototype)
                num_functions += 1
                functions.append(func)
                update_prototype_db(func, prototype, inc_lines, prototype_db, include_db)
                inc_lines = []
                prototype = ''
    #print(g_prototype_db)
    #print(g_include_db)
    return functions


def read_prototype_file(afile):
    """
    Read all function prototypes from a C header file.

    :param afile: a C header file
    :returns a list of functions whose prototypes are read from the file.
      Global function prototype/include DBs are updated
    """
    lines = read_file_lines(afile)
    return read_prototype_lines(lines, g_prototype_db, g_include_db)


def test_fortify_function():
    '''
    Testing code for those 70 glibc fortify-functions.
    '''
    generate_fortify_functions_code(fortify_functions)


def test_function():
    '''
    Testing code: for testing some specific functions only.
    '''
    print_func_prototype("memcpy")
    print_func_prototype("strncpy")
    print_func_prototype("vsnprintf")
    print_func_prototype("swprintf")
    print_func_prototype("abcdefgmemcpy")
    return
    get_func_params_from_prototype(memcpy_prototype)
    get_func_params_from_prototype(strncpy_prototype)
    get_func_params_from_prototype(vsnprintf_prototype)
    get_func_params_from_prototype(swprintf_prototype)
    generate_runtime_check_code(memcpy_prototype)
    generate_runtime_check_code(strncpy_prototype)


def generate_fortify_functions_code(functions):
    '''
    The real main function to generate fortified code for all functions.
    '''
    generate_openosc_file_start_code(functions)
    generate_functions_nomap_magic_macro_code(functions)
    generate_functions_map_magic_macro_code(functions)
    code = generate_functions_runtime_check_macro_code(functions)
    openosc_write_filename("openosc_fortify_redefine_map.h", code)
    code = generate_functions_compiletime_check_macro_code(functions)
    openosc_write_filename("openosc_fortify_redefine_map.h", code)
    generate_fortify_functions_real_code(functions)
    generate_openosc_functions_test_code(functions)
    generate_openosc_functions_test_code(functions, "NOMAP")
    generate_openosc_file_end_code(functions)


def get_all_functions():
    """
    Collect all functions to fortify from command line options.
    """
    functions = []
    if args.functions:
        functions = args.functions.split(',')
    if args.prototype:
        prototype = args.prototype
        (retval, funcname, params) = get_func_params_from_prototype(prototype)
        functions.append(funcname)
        g_prototype_db[funcname] = prototype
        if args.linesofinclude:
            g_include_db[funcname] = args.linesofinclude.split(",")
    if args.inputfile:
        funcs = read_prototype_file(args.inputfile)
        functions.extend(funcs)
    alignment_size = (1 << g_magic_alignment)
    print("MAGIC word start: " + hex(g_magic_word) + " alignment size for function is: " + str(alignment_size))
    if not functions:
        functions = initial_osc_functions
        functions.extend(fortify_functions)
        functions.extend(initial_safec_functions)
    if functions:
        delete_all_generated_code_files()
        i = 0
        for func in functions:
            g_magic_words[func] = g_magic_word + i * alignment_size
            i += 1
        print(g_magic_words)
        code = ''
        for func in functions:
            print("Generating curioscan code for function " + func)
            code += generate_curioscan_code(func, g_magic_words[func])
        # the code in openosc_fortify_magics_curioscan can be directly copied into Curioscan,
        # then Curioscan will be able to recognize/scan magic words for the generated functions.
        openosc_write_filename("openosc_fortify_magics_curioscan", code)
    print("Here are all the funciotns to fortify: ")
    print(functions)
    ## Add support for calling glibc print_chk functions
    lines = glibc_print_chk_functions_prototype.splitlines()
    read_prototype_lines(lines, glibc_print_chk_prototype_db, None)
    #print(glibc_print_chk_prototype_db)
    return functions


def main():
    # parse command line options first
    rtd_parse_options()

    functions = get_all_functions()
    generate_fortify_functions_code(functions)
    #test_function()
    #test_fortify_function()
    print("OK it is done")


if __name__ == '__main__':
    main()

