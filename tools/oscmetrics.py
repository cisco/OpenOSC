#! /usr/bin/env python3
'''
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
'''
"""
Utility script for OpenOSC OSC Metrics extraction.

Usage:
  oscmetrics.py -b -m -w -d builddir -j output_json -v -h

October 2019, Yongkui Han
"""

import argparse
import sys
import os
import subprocess
from datetime import datetime
import json
import shlex
import pipes

# for special filename handling with shell
try:
    from shlex import quote as cmd_quote
except ImportError:
    from pipes import quote as cmd_quote

TOOL_VERSION = '1.0.1'
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
builddirs = []
DEFAULT_PASS_PERCENT = -1
RESULT_JSON_FILE = "OSCMETRICS_RESULT.json"
skip_linkage_check_if_lib_not_present = True
g_configs = dict()
g_objdump_prog = 'objdump'
g_addr2line_prog = 'addr2line'
g_readelf_prog = 'readelf'

# The magics array to be used to collect the OSC-Metrics.
# if magic_type is dwarf_loc, then it is loc_all_magics;
# if magic_type is byte_inline, then it is water_all_magics.
g_all_magics = dict()

# the magics array for dwarf_loc method
loc_all_magics = {
    'FILEMAGICS': {
        '80818d8e80818d8e': 'MAGIC_OSC_HEADER_INCLUDED',
        '80818d8e80818d8f': 'MAGIC_OSC_NOMAP_H_INCLUDED',
        '80818d8e80818d01': 'MAGIC_OSC_NOMAP_H_REASON_NOOPTIMIZE',
        '80818d8e80818d02': 'MAGIC_OSC_NOMAP_H_REASON_NOINLINE',
        '80818d8e80818d03': 'MAGIC_OSC_NOMAP_H_REASON_FORTIFY_SOURCE',
        '80818d8e80818d04': 'MAGIC_OSC_NOMAP_H_REASON_ASM',
        '80818d8e80818d05': 'MAGIC_OSC_NOMAP_H_REASON_STRICT_ANSI',
        '80818d8e80818d06': 'MAGIC_OSC_NOMAP_H_REASON_METRIC_ONLY',
        '97cfa25a9fb39d01': 'MAGIC_OSC_COMPILER_ICC',
        '97cfa25a9fb39d02': 'MAGIC_OSC_COMPILER_CLANG',
        '97cfa25a9fb39d03': 'MAGIC_OSC_COMPILER_GCC',
        '97cfa25a9fb39d04': 'MAGIC_OSC_COMPILER_OTHER',
    },
    ### LIBC functions
    'memcpy': {
        '8388864': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388865': 'MAGIC_FUNC_MAGIC1',
        '8388866': 'MAGIC_FUNC_MAGIC2',
        '8388867': 'MAGIC_FUNC_MAGIC3',
        '8388868': 'MAGIC_FUNC_MAGIC4',
        '8388871': 'MAGIC_FUNC_MAGIC7',
        '8388872': 'MAGIC_FUNC_MAGIC8',
        '8388873': 'MAGIC_FUNC_MAGIC9',
        '8388874': 'MAGIC_FUNC_MAGICa',
        '8388875': 'MAGIC_FUNC_MAGICb',
    },
    'memmove': {
        '8388880': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388881': 'MAGIC_FUNC_MAGIC1',
        '8388882': 'MAGIC_FUNC_MAGIC2',
        '8388883': 'MAGIC_FUNC_MAGIC3',
        '8388884': 'MAGIC_FUNC_MAGIC4',
        '8388887': 'MAGIC_FUNC_MAGIC7',
        '8388888': 'MAGIC_FUNC_MAGIC8',
        '8388889': 'MAGIC_FUNC_MAGIC9',
        '8388890': 'MAGIC_FUNC_MAGICa',
        '8388891': 'MAGIC_FUNC_MAGICb',
    },
    'memset': {
        '8388896': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388897': 'MAGIC_FUNC_MAGIC1',
        '8388898': 'MAGIC_FUNC_MAGIC2',
        '8388899': 'MAGIC_FUNC_MAGIC3',
        '8388900': 'MAGIC_FUNC_MAGIC4',
    },
    'bcopy': {
        '8388912': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388913': 'MAGIC_FUNC_MAGIC1',
        '8388914': 'MAGIC_FUNC_MAGIC2',
        '8388915': 'MAGIC_FUNC_MAGIC3',
        '8388916': 'MAGIC_FUNC_MAGIC4',
        '8388919': 'MAGIC_FUNC_MAGIC7',
        '8388920': 'MAGIC_FUNC_MAGIC8',
        '8388921': 'MAGIC_FUNC_MAGIC9',
        '8388922': 'MAGIC_FUNC_MAGICa',
        '8388923': 'MAGIC_FUNC_MAGICb',
    },
    'bzero': {
        '8388928': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388929': 'MAGIC_FUNC_MAGIC1',
        '8388930': 'MAGIC_FUNC_MAGIC2',
        '8388931': 'MAGIC_FUNC_MAGIC3',
        '8388932': 'MAGIC_FUNC_MAGIC4',
    },
    'strcpy': {
        '8388944': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388945': 'MAGIC_FUNC_MAGIC1',
        '8388946': 'MAGIC_FUNC_MAGIC2',
        '8388947': 'MAGIC_FUNC_MAGIC3',
        '8388948': 'MAGIC_FUNC_MAGIC4',
    },
    'strncpy': {
        '8388960': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388961': 'MAGIC_FUNC_MAGIC1',
        '8388962': 'MAGIC_FUNC_MAGIC2',
        '8388963': 'MAGIC_FUNC_MAGIC3',
        '8388964': 'MAGIC_FUNC_MAGIC4',
    },
    'strcat': {
        '8388976': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388977': 'MAGIC_FUNC_MAGIC1',
        '8388978': 'MAGIC_FUNC_MAGIC2',
        '8388979': 'MAGIC_FUNC_MAGIC3',
        '8388980': 'MAGIC_FUNC_MAGIC4',
    },
    'strncat': {
        '8388992': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8388993': 'MAGIC_FUNC_MAGIC1',
        '8388994': 'MAGIC_FUNC_MAGIC2',
        '8388995': 'MAGIC_FUNC_MAGIC3',
        '8388996': 'MAGIC_FUNC_MAGIC4',
    },
    'strnlen': {
        '8389008': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389009': 'MAGIC_FUNC_MAGIC1',
        '8389010': 'MAGIC_FUNC_MAGIC2',
        '8389011': 'MAGIC_FUNC_MAGIC3',
        '8389012': 'MAGIC_FUNC_MAGIC4',
    },
    'vsnprintf': {
        '8389024': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389025': 'MAGIC_FUNC_MAGIC1',
        '8389026': 'MAGIC_FUNC_MAGIC2',
        '8389027': 'MAGIC_FUNC_MAGIC3',
        '8389028': 'MAGIC_FUNC_MAGIC4',
    },
    ### GLIBC fortify-source functions
    'asprintf': {
        '8389040': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389041': 'MAGIC_FUNC_MAGIC1',
        '8389042': 'MAGIC_FUNC_MAGIC2',
        '8389043': 'MAGIC_FUNC_MAGIC3',
        '8389044': 'MAGIC_FUNC_MAGIC4',
    },
    'dprintf': {
        '8389056': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389057': 'MAGIC_FUNC_MAGIC1',
        '8389058': 'MAGIC_FUNC_MAGIC2',
        '8389059': 'MAGIC_FUNC_MAGIC3',
        '8389060': 'MAGIC_FUNC_MAGIC4',
    },
    'fprintf': {
        '8389072': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389073': 'MAGIC_FUNC_MAGIC1',
        '8389074': 'MAGIC_FUNC_MAGIC2',
        '8389075': 'MAGIC_FUNC_MAGIC3',
        '8389076': 'MAGIC_FUNC_MAGIC4',
    },
    'fwprintf': {
        '8389088': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389089': 'MAGIC_FUNC_MAGIC1',
        '8389090': 'MAGIC_FUNC_MAGIC2',
        '8389091': 'MAGIC_FUNC_MAGIC3',
        '8389092': 'MAGIC_FUNC_MAGIC4',
    },
    'printf': {
        '8389104': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389105': 'MAGIC_FUNC_MAGIC1',
        '8389106': 'MAGIC_FUNC_MAGIC2',
        '8389107': 'MAGIC_FUNC_MAGIC3',
        '8389108': 'MAGIC_FUNC_MAGIC4',
    },
    'snprintf': {
        '8389120': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389121': 'MAGIC_FUNC_MAGIC1',
        '8389122': 'MAGIC_FUNC_MAGIC2',
        '8389123': 'MAGIC_FUNC_MAGIC3',
        '8389124': 'MAGIC_FUNC_MAGIC4',
    },
    'sprintf': {
        '8389136': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389137': 'MAGIC_FUNC_MAGIC1',
        '8389138': 'MAGIC_FUNC_MAGIC2',
        '8389139': 'MAGIC_FUNC_MAGIC3',
        '8389140': 'MAGIC_FUNC_MAGIC4',
    },
    'swprintf': {
        '8389152': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389153': 'MAGIC_FUNC_MAGIC1',
        '8389154': 'MAGIC_FUNC_MAGIC2',
        '8389155': 'MAGIC_FUNC_MAGIC3',
        '8389156': 'MAGIC_FUNC_MAGIC4',
    },
    'wprintf': {
        '8389168': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389169': 'MAGIC_FUNC_MAGIC1',
        '8389170': 'MAGIC_FUNC_MAGIC2',
        '8389171': 'MAGIC_FUNC_MAGIC3',
        '8389172': 'MAGIC_FUNC_MAGIC4',
    },
    'confstr': {
        '8389184': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389185': 'MAGIC_FUNC_MAGIC1',
        '8389186': 'MAGIC_FUNC_MAGIC2',
        '8389187': 'MAGIC_FUNC_MAGIC3',
        '8389188': 'MAGIC_FUNC_MAGIC4',
    },
    'fgets': {
        '8389200': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389201': 'MAGIC_FUNC_MAGIC1',
        '8389202': 'MAGIC_FUNC_MAGIC2',
        '8389203': 'MAGIC_FUNC_MAGIC3',
        '8389204': 'MAGIC_FUNC_MAGIC4',
    },
    'fgets_unlocked': {
        '8389216': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389217': 'MAGIC_FUNC_MAGIC1',
        '8389218': 'MAGIC_FUNC_MAGIC2',
        '8389219': 'MAGIC_FUNC_MAGIC3',
        '8389220': 'MAGIC_FUNC_MAGIC4',
    },
    'fgetws': {
        '8389232': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389233': 'MAGIC_FUNC_MAGIC1',
        '8389234': 'MAGIC_FUNC_MAGIC2',
        '8389235': 'MAGIC_FUNC_MAGIC3',
        '8389236': 'MAGIC_FUNC_MAGIC4',
    },
    'fgetws_unlocked': {
        '8389248': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389249': 'MAGIC_FUNC_MAGIC1',
        '8389250': 'MAGIC_FUNC_MAGIC2',
        '8389251': 'MAGIC_FUNC_MAGIC3',
        '8389252': 'MAGIC_FUNC_MAGIC4',
    },
    'fread': {
        '8389264': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389265': 'MAGIC_FUNC_MAGIC1',
        '8389266': 'MAGIC_FUNC_MAGIC2',
        '8389267': 'MAGIC_FUNC_MAGIC3',
        '8389268': 'MAGIC_FUNC_MAGIC4',
    },
    'fread_unlocked': {
        '8389280': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389281': 'MAGIC_FUNC_MAGIC1',
        '8389282': 'MAGIC_FUNC_MAGIC2',
        '8389283': 'MAGIC_FUNC_MAGIC3',
        '8389284': 'MAGIC_FUNC_MAGIC4',
    },
    'getcwd': {
        '8389296': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389297': 'MAGIC_FUNC_MAGIC1',
        '8389298': 'MAGIC_FUNC_MAGIC2',
        '8389299': 'MAGIC_FUNC_MAGIC3',
        '8389300': 'MAGIC_FUNC_MAGIC4',
    },
    'getdomainname': {
        '8389312': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389313': 'MAGIC_FUNC_MAGIC1',
        '8389314': 'MAGIC_FUNC_MAGIC2',
        '8389315': 'MAGIC_FUNC_MAGIC3',
        '8389316': 'MAGIC_FUNC_MAGIC4',
    },
    'getgroups': {
        '8389328': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389329': 'MAGIC_FUNC_MAGIC1',
        '8389330': 'MAGIC_FUNC_MAGIC2',
        '8389331': 'MAGIC_FUNC_MAGIC3',
        '8389332': 'MAGIC_FUNC_MAGIC4',
    },
    'gethostname': {
        '8389344': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389345': 'MAGIC_FUNC_MAGIC1',
        '8389346': 'MAGIC_FUNC_MAGIC2',
        '8389347': 'MAGIC_FUNC_MAGIC3',
        '8389348': 'MAGIC_FUNC_MAGIC4',
    },
    'gets': {
        '8389360': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389361': 'MAGIC_FUNC_MAGIC1',
        '8389362': 'MAGIC_FUNC_MAGIC2',
        '8389363': 'MAGIC_FUNC_MAGIC3',
        '8389364': 'MAGIC_FUNC_MAGIC4',
    },
    'getwd': {
        '8389376': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389377': 'MAGIC_FUNC_MAGIC1',
        '8389378': 'MAGIC_FUNC_MAGIC2',
        '8389379': 'MAGIC_FUNC_MAGIC3',
        '8389380': 'MAGIC_FUNC_MAGIC4',
    },
    'longjmp': {
        '8389392': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389393': 'MAGIC_FUNC_MAGIC1',
        '8389394': 'MAGIC_FUNC_MAGIC2',
        '8389395': 'MAGIC_FUNC_MAGIC3',
        '8389396': 'MAGIC_FUNC_MAGIC4',
    },
    'mbsnrtowcs': {
        '8389408': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389409': 'MAGIC_FUNC_MAGIC1',
        '8389410': 'MAGIC_FUNC_MAGIC2',
        '8389411': 'MAGIC_FUNC_MAGIC3',
        '8389412': 'MAGIC_FUNC_MAGIC4',
    },
    'mbsrtowcs': {
        '8389424': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389425': 'MAGIC_FUNC_MAGIC1',
        '8389426': 'MAGIC_FUNC_MAGIC2',
        '8389427': 'MAGIC_FUNC_MAGIC3',
        '8389428': 'MAGIC_FUNC_MAGIC4',
    },
    'mbstowcs': {
        '8389440': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389441': 'MAGIC_FUNC_MAGIC1',
        '8389442': 'MAGIC_FUNC_MAGIC2',
        '8389443': 'MAGIC_FUNC_MAGIC3',
        '8389444': 'MAGIC_FUNC_MAGIC4',
    },
    'mempcpy': {
        '8389456': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389457': 'MAGIC_FUNC_MAGIC1',
        '8389458': 'MAGIC_FUNC_MAGIC2',
        '8389459': 'MAGIC_FUNC_MAGIC3',
        '8389460': 'MAGIC_FUNC_MAGIC4',
    },
    'poll': {
        '8389472': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389473': 'MAGIC_FUNC_MAGIC1',
        '8389474': 'MAGIC_FUNC_MAGIC2',
        '8389475': 'MAGIC_FUNC_MAGIC3',
        '8389476': 'MAGIC_FUNC_MAGIC4',
    },
    'ppoll': {
        '8389488': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389489': 'MAGIC_FUNC_MAGIC1',
        '8389490': 'MAGIC_FUNC_MAGIC2',
        '8389491': 'MAGIC_FUNC_MAGIC3',
        '8389492': 'MAGIC_FUNC_MAGIC4',
    },
    'pread': {
        '8389504': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389505': 'MAGIC_FUNC_MAGIC1',
        '8389506': 'MAGIC_FUNC_MAGIC2',
        '8389507': 'MAGIC_FUNC_MAGIC3',
        '8389508': 'MAGIC_FUNC_MAGIC4',
    },
    'read': {
        '8389520': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389521': 'MAGIC_FUNC_MAGIC1',
        '8389522': 'MAGIC_FUNC_MAGIC2',
        '8389523': 'MAGIC_FUNC_MAGIC3',
        '8389524': 'MAGIC_FUNC_MAGIC4',
    },
    'readlinkat': {
        '8389536': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389537': 'MAGIC_FUNC_MAGIC1',
        '8389538': 'MAGIC_FUNC_MAGIC2',
        '8389539': 'MAGIC_FUNC_MAGIC3',
        '8389540': 'MAGIC_FUNC_MAGIC4',
    },
    'readlink': {
        '8389552': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389553': 'MAGIC_FUNC_MAGIC1',
        '8389554': 'MAGIC_FUNC_MAGIC2',
        '8389555': 'MAGIC_FUNC_MAGIC3',
        '8389556': 'MAGIC_FUNC_MAGIC4',
    },
    'realpath': {
        '8389568': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389569': 'MAGIC_FUNC_MAGIC1',
        '8389570': 'MAGIC_FUNC_MAGIC2',
        '8389571': 'MAGIC_FUNC_MAGIC3',
        '8389572': 'MAGIC_FUNC_MAGIC4',
    },
    'recv': {
        '8389584': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389585': 'MAGIC_FUNC_MAGIC1',
        '8389586': 'MAGIC_FUNC_MAGIC2',
        '8389587': 'MAGIC_FUNC_MAGIC3',
        '8389588': 'MAGIC_FUNC_MAGIC4',
    },
    'recvfrom': {
        '8389600': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389601': 'MAGIC_FUNC_MAGIC1',
        '8389602': 'MAGIC_FUNC_MAGIC2',
        '8389603': 'MAGIC_FUNC_MAGIC3',
        '8389604': 'MAGIC_FUNC_MAGIC4',
    },
    'stpcpy': {
        '8389616': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389617': 'MAGIC_FUNC_MAGIC1',
        '8389618': 'MAGIC_FUNC_MAGIC2',
        '8389619': 'MAGIC_FUNC_MAGIC3',
        '8389620': 'MAGIC_FUNC_MAGIC4',
    },
    'stpncpy': {
        '8389632': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389633': 'MAGIC_FUNC_MAGIC1',
        '8389634': 'MAGIC_FUNC_MAGIC2',
        '8389635': 'MAGIC_FUNC_MAGIC3',
        '8389636': 'MAGIC_FUNC_MAGIC4',
    },
    'ttyname_r': {
        '8389648': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389649': 'MAGIC_FUNC_MAGIC1',
        '8389650': 'MAGIC_FUNC_MAGIC2',
        '8389651': 'MAGIC_FUNC_MAGIC3',
        '8389652': 'MAGIC_FUNC_MAGIC4',
    },
    'vasprintf': {
        '8389664': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389665': 'MAGIC_FUNC_MAGIC1',
        '8389666': 'MAGIC_FUNC_MAGIC2',
        '8389667': 'MAGIC_FUNC_MAGIC3',
        '8389668': 'MAGIC_FUNC_MAGIC4',
    },
    'vdprintf': {
        '8389680': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389681': 'MAGIC_FUNC_MAGIC1',
        '8389682': 'MAGIC_FUNC_MAGIC2',
        '8389683': 'MAGIC_FUNC_MAGIC3',
        '8389684': 'MAGIC_FUNC_MAGIC4',
    },
    'vfprintf': {
        '8389696': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389697': 'MAGIC_FUNC_MAGIC1',
        '8389698': 'MAGIC_FUNC_MAGIC2',
        '8389699': 'MAGIC_FUNC_MAGIC3',
        '8389700': 'MAGIC_FUNC_MAGIC4',
    },
    'vfwprintf': {
        '8389712': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389713': 'MAGIC_FUNC_MAGIC1',
        '8389714': 'MAGIC_FUNC_MAGIC2',
        '8389715': 'MAGIC_FUNC_MAGIC3',
        '8389716': 'MAGIC_FUNC_MAGIC4',
    },
    'vprintf': {
        '8389728': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389729': 'MAGIC_FUNC_MAGIC1',
        '8389730': 'MAGIC_FUNC_MAGIC2',
        '8389731': 'MAGIC_FUNC_MAGIC3',
        '8389732': 'MAGIC_FUNC_MAGIC4',
    },
    'vsprintf': {
        '8389744': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389745': 'MAGIC_FUNC_MAGIC1',
        '8389746': 'MAGIC_FUNC_MAGIC2',
        '8389747': 'MAGIC_FUNC_MAGIC3',
        '8389748': 'MAGIC_FUNC_MAGIC4',
    },
    'vswprintf': {
        '8389760': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389761': 'MAGIC_FUNC_MAGIC1',
        '8389762': 'MAGIC_FUNC_MAGIC2',
        '8389763': 'MAGIC_FUNC_MAGIC3',
        '8389764': 'MAGIC_FUNC_MAGIC4',
    },
    'vwprintf': {
        '8389776': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389777': 'MAGIC_FUNC_MAGIC1',
        '8389778': 'MAGIC_FUNC_MAGIC2',
        '8389779': 'MAGIC_FUNC_MAGIC3',
        '8389780': 'MAGIC_FUNC_MAGIC4',
    },
    'wcpcpy': {
        '8389792': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389793': 'MAGIC_FUNC_MAGIC1',
        '8389794': 'MAGIC_FUNC_MAGIC2',
        '8389795': 'MAGIC_FUNC_MAGIC3',
        '8389796': 'MAGIC_FUNC_MAGIC4',
    },
    'wcpncpy': {
        '8389808': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389809': 'MAGIC_FUNC_MAGIC1',
        '8389810': 'MAGIC_FUNC_MAGIC2',
        '8389811': 'MAGIC_FUNC_MAGIC3',
        '8389812': 'MAGIC_FUNC_MAGIC4',
    },
    'wcrtomb': {
        '8389824': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389825': 'MAGIC_FUNC_MAGIC1',
        '8389826': 'MAGIC_FUNC_MAGIC2',
        '8389827': 'MAGIC_FUNC_MAGIC3',
        '8389828': 'MAGIC_FUNC_MAGIC4',
    },
    'wcscat': {
        '8389840': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389841': 'MAGIC_FUNC_MAGIC1',
        '8389842': 'MAGIC_FUNC_MAGIC2',
        '8389843': 'MAGIC_FUNC_MAGIC3',
        '8389844': 'MAGIC_FUNC_MAGIC4',
    },
    'wcscpy': {
        '8389856': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389857': 'MAGIC_FUNC_MAGIC1',
        '8389858': 'MAGIC_FUNC_MAGIC2',
        '8389859': 'MAGIC_FUNC_MAGIC3',
        '8389860': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsncat': {
        '8389872': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389873': 'MAGIC_FUNC_MAGIC1',
        '8389874': 'MAGIC_FUNC_MAGIC2',
        '8389875': 'MAGIC_FUNC_MAGIC3',
        '8389876': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsncpy': {
        '8389888': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389889': 'MAGIC_FUNC_MAGIC1',
        '8389890': 'MAGIC_FUNC_MAGIC2',
        '8389891': 'MAGIC_FUNC_MAGIC3',
        '8389892': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsnrtombs': {
        '8389904': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389905': 'MAGIC_FUNC_MAGIC1',
        '8389906': 'MAGIC_FUNC_MAGIC2',
        '8389907': 'MAGIC_FUNC_MAGIC3',
        '8389908': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsrtombs': {
        '8389920': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389921': 'MAGIC_FUNC_MAGIC1',
        '8389922': 'MAGIC_FUNC_MAGIC2',
        '8389923': 'MAGIC_FUNC_MAGIC3',
        '8389924': 'MAGIC_FUNC_MAGIC4',
    },
    'wcstombs': {
        '8389936': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389937': 'MAGIC_FUNC_MAGIC1',
        '8389938': 'MAGIC_FUNC_MAGIC2',
        '8389939': 'MAGIC_FUNC_MAGIC3',
        '8389940': 'MAGIC_FUNC_MAGIC4',
    },
    'wctomb': {
        '8389952': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389953': 'MAGIC_FUNC_MAGIC1',
        '8389954': 'MAGIC_FUNC_MAGIC2',
        '8389955': 'MAGIC_FUNC_MAGIC3',
        '8389956': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemcpy': {
        '8389968': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389969': 'MAGIC_FUNC_MAGIC1',
        '8389970': 'MAGIC_FUNC_MAGIC2',
        '8389971': 'MAGIC_FUNC_MAGIC3',
        '8389972': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemmove': {
        '8389984': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8389985': 'MAGIC_FUNC_MAGIC1',
        '8389986': 'MAGIC_FUNC_MAGIC2',
        '8389987': 'MAGIC_FUNC_MAGIC3',
        '8389988': 'MAGIC_FUNC_MAGIC4',
    },
    'wmempcpy': {
        '8390000': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390001': 'MAGIC_FUNC_MAGIC1',
        '8390002': 'MAGIC_FUNC_MAGIC2',
        '8390003': 'MAGIC_FUNC_MAGIC3',
        '8390004': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemset': {
        '8390016': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390017': 'MAGIC_FUNC_MAGIC1',
        '8390018': 'MAGIC_FUNC_MAGIC2',
        '8390019': 'MAGIC_FUNC_MAGIC3',
        '8390020': 'MAGIC_FUNC_MAGIC4',
    },
    ### SAFEC functions
    'memcmp_s': {
        '8390032': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390033': 'MAGIC_FUNC_MAGIC1',
        '8390034': 'MAGIC_FUNC_MAGIC2',
        '8390035': 'MAGIC_FUNC_MAGIC3',
        '8390036': 'MAGIC_FUNC_MAGIC4',
    },
    'memcpy_s': {
        '8390048': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390049': 'MAGIC_FUNC_MAGIC1',
        '8390050': 'MAGIC_FUNC_MAGIC2',
        '8390051': 'MAGIC_FUNC_MAGIC3',
        '8390052': 'MAGIC_FUNC_MAGIC4',
    },
    'strcat_s': {
        '8390064': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390065': 'MAGIC_FUNC_MAGIC1',
        '8390066': 'MAGIC_FUNC_MAGIC2',
        '8390067': 'MAGIC_FUNC_MAGIC3',
        '8390068': 'MAGIC_FUNC_MAGIC4',
    },
    'strcmp_s': {
        '8390080': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390081': 'MAGIC_FUNC_MAGIC1',
        '8390082': 'MAGIC_FUNC_MAGIC2',
        '8390083': 'MAGIC_FUNC_MAGIC3',
        '8390084': 'MAGIC_FUNC_MAGIC4',
    },
    'strcpy_s': {
        '8390096': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390097': 'MAGIC_FUNC_MAGIC1',
        '8390098': 'MAGIC_FUNC_MAGIC2',
        '8390099': 'MAGIC_FUNC_MAGIC3',
        '8390100': 'MAGIC_FUNC_MAGIC4',
    },
    'strncat_s': {
        '8390112': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390113': 'MAGIC_FUNC_MAGIC1',
        '8390114': 'MAGIC_FUNC_MAGIC2',
        '8390115': 'MAGIC_FUNC_MAGIC3',
        '8390116': 'MAGIC_FUNC_MAGIC4',
        '8390117': 'MAGIC_FUNC_MAGIC5',
        '8390118': 'MAGIC_FUNC_MAGIC6',
    },
    'strncpy_s': {
        '8390128': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390129': 'MAGIC_FUNC_MAGIC1',
        '8390130': 'MAGIC_FUNC_MAGIC2',
        '8390131': 'MAGIC_FUNC_MAGIC3',
        '8390132': 'MAGIC_FUNC_MAGIC4',
        '8390133': 'MAGIC_FUNC_MAGIC5',
        '8390134': 'MAGIC_FUNC_MAGIC6',
    },
    'strnlen_s': {
        '8390144': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390145': 'MAGIC_FUNC_MAGIC1',
        '8390146': 'MAGIC_FUNC_MAGIC2',
        '8390147': 'MAGIC_FUNC_MAGIC3',
        '8390148': 'MAGIC_FUNC_MAGIC4',
    },
    'strstr_s': {
        '8390160': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '8390161': 'MAGIC_FUNC_MAGIC1',
        '8390162': 'MAGIC_FUNC_MAGIC2',
        '8390163': 'MAGIC_FUNC_MAGIC3',
        '8390164': 'MAGIC_FUNC_MAGIC4',
    },
}


initial_start_time = datetime.now()
start_time = datetime.now()
def print_start_time():
    """
    Retrieves the current clock and stores that as the
    'start_time'. Prints banner with 'start_time'.
    """
    global start_time
    start_time = datetime.now()
    print ("")
    print (HDR1)
    print ("Start time is: " + start_time.strftime("%d/%m/%Y %H:%M:%S"))
    print (HDR1)


def print_end_time():
    """
    Retrieves the current clock and calculates running time as well as
    the total running time. Both calculated values are printed in
    banner.
    """
    print ("")
    end_time = datetime.now()
    print (HDR1)
    print ("End time is: " + end_time.strftime("%d/%m/%Y %H:%M:%S"))
    delta = end_time - start_time
    delta2 = end_time - initial_start_time
    print ("The running time is (in seconds): " + str(delta.total_seconds()))
    print ("The total running time is (in seconds): " +
           str(delta2.total_seconds()))
    print (HDR1)


def rtd_parse_options():
    """
    Parse command options.
    """
    global args
    global builddirs
    global buildlogs
    global logdirs
    router_check_cmdline = """
For the -d options, you can specify multiple comma-separated
directories.
"""
    # Now the main part: Start with parsing the command line arguments.
    parser = argparse.ArgumentParser(
        description = ("This tool does OSC coverage check and Metrics extraction"),
        epilog = router_check_cmdline)
    parser.add_argument("--version",
                    action = "version",
                    version=VERSION)
    parser.add_argument('-d', '--builddir',
                    help = "perform check in a directory of your build workspace or unbundled directory."
                           " If omitted, the current directory will be used")
    parser.add_argument("-t", "--magictype",
                    help = "the type of magic words in use, either byte_inline or dwarf_loc")
    parser.add_argument("--watermarkfiles",
                    help = "a list of comma-separated binary file names for watermark-PC check")
    parser.add_argument('-j', '--jsonoutputfile',
                    help = "the output file to put the JSON output."
                           " If omitted, a default file, like ./RESULT_JSON_FILE.txt will be used")
    parser.add_argument("--pc_decode_entry",
                    help = "specify which addr2line decode entry to use."
                           " The decode entry can be negative, which means counting backwards. "
                           "Use --pc_decode_entry=-1 when negative value.")
    parser.add_argument("--pc_extraoffset",
                    help = "Adding extra offset to PC value for addr2line decode."
                           " The extra offset can be negative. "
                           "Use --pc_extraoffset=-0x10 when negative offset.")
    parser.add_argument("-c", "--configfile",
                    help = "configuration file, like objdump/addr2line tool locations, etc.")
    parser.add_argument("-b", "--bosc",
                    action = "store_true",
                    help = "OSC (Object Size Check) check, i.e., all files are linked with -lopenosc; it performs OSC metric scan of MAGIC words too")
    parser.add_argument("-m", "--magiccheck",
                    action = "store_true",
                    help = "OSC magic word check, high-level stats only")
    parser.add_argument("-w", "--watermarkpc",
                    action = "store_true",
                    help = "Watermark-PC check, scan magic words, decode the PCs to source lines")
    parser.add_argument("--scan_all_elf_files",
                    action = "store_true",
                    help = "The default is ELF shared object and executable files only. This flag will scan all ELF files")
    parser.add_argument("-v", "--verbose",
                    action = "count",
                    default = 0,
                    help = "verbose output, can be supplied multiple times"
                           " to increase verbosity")
    parser.add_argument("-y", "--summary",
                    help = "The provided input file is used to generate a summary. "
                           "By default this is printed at the end of a run.")
    parser.add_argument("-Y", "--summary_dir",
                    help = "Specify a specific directory for summary to include.")


    # Parse the command line arguments
    args = parser.parse_args()

    # store the command line arguments
    builddirs = [os.getcwd()]
    if args.builddir:
        builddirs = args.builddir.split(',')

    if not (args.bosc or args.magiccheck or args.watermarkpc or args.summary):
        print ("Please specify the check: -b, -m, -w, or -y!")
        print ("")
        print ('Run "' + sys.argv[0] + ' -h" for help.')
        sys.exit()

    # If there is no any builddir, then print help and exit
    if args.magictype and args.magictype.lower() not in ("dwarf_loc", "byte_inline"):
        print ("Please provide a valid value for magictype: dwarf_loc or byte_inline!")
        print ("")
        print ('Run "' + sys.argv[0] + ' -h" for help.')
        sys.exit()

    # If there is no any builddir, then print help and exit
    if not (builddirs or args.summary):
        print ("Please provide at least one of: build dir, or summary input file!")
        print ("")
        print ('Run "' + sys.argv[0] + ' -h" for help.')
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
        # Set the configured programs for later use.
        set_config_progs()

    global RESULT_JSON_FILE
    if args.jsonoutputfile:
        RESULT_JSON_FILE = args.jsonoutputfile
        print ("the output json file is: " + RESULT_JSON_FILE)

    print ("Your command line is:")
    print (" ".join(sys.argv))
    print ("The current directory is: " + os.getcwd())



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
            print (indent + string)
        return


# the global dict to store the result
result_dict = dict()

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
    print ("save_json_db: db file is " + db_file)
    result_dict["version"] = TOOL_VERSION
    try:
        f = open(db_file, 'w')
    except IOError as e:
        print ("I/O error({0}): {1}".format(e.errno, e.strerror))
        print ("Error in save_json_db, skipping it.")
    else:
        with f:
            json.dump(db, f, indent=indentation, sort_keys=True)


def find_all_suffix_dirs(builddir, suffix):
    """
    Find all directories with the specified suffix in the build dir.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :param suffix: the suffix of files to find
    :returns a list that contains all the directory names with the suffix.
    """
    findcmd = "find " + cmd_quote(builddir) + ' -type d -name "*' + suffix + '" -print || true'
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    return files


def find_all_suffix_files(builddir, suffix):
    """
    Find all files with the specified suffix in the build dir.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :param suffix: the suffix of files to find
    :returns a list that contains all the file names with the suffix.
    """
    findcmd = "find " + cmd_quote(builddir) + ' -name "*' + suffix + '" -print || true'
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    return files


def find_all_executable_files(builddir):
    """
    Find all executable files in the build dir.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :returns a list that contains all the binary file names.
    """
    findcmd = "find " + cmd_quote(builddir) + ' -perm +a+x -type f -print || true '
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    return files


def get_total_dir_list(all_files):
    """
    Return a list of directories from a list of files.

    :param all_files: a list of files, returned from find_all_elf_files().
    :returns a list that contains all the directories among those files.
    """
    dirset = set()
    for path in all_files:
        dirset.add(os.path.dirname(path))
    return dirset


# Cache the search result to optimize performance.
d_elf_files = dict()
def find_all_elf_files(builddir):
    """
    Find all ELF(Executable and Linkable Format) files in the build dir.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :returns a list that contains all the binary file names.
    """
    print ("entering find_all_elf_files: the build dir is " + builddir)
    if builddir[0] != "/":
        builddir = os.path.abspath(builddir)
    if builddir in d_elf_files:
        return d_elf_files[builddir]
    findcmd = "find " + cmd_quote(builddir) + " -type f -exec sh -c 'file  \"$1\" | grep \ ELF\  >/dev/null ' _ {} \; -print  || true"
    print (findcmd)
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    d_elf_files[builddir] = files
    return files


# Cache the search result to optimize performance.
d_elf_soexe_files = dict()
def find_all_elf_soexe_files(builddir):
    """
    Find all ELF shared object and executable files in the build dir.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :returns a list that contains all the binary file names.
    """
    print ("entering find_all_elf_soexe_files: the build dir is " + builddir)
    if builddir[0] != "/":
        builddir = os.path.abspath(builddir)
    if builddir in d_elf_soexe_files:
        return d_elf_soexe_files[builddir]
    findcmd = "find " + cmd_quote(builddir) + " -type f -exec sh -c 'file  \"$1\" | grep -E \" ELF.*shared object| ELF.*executable\"  >/dev/null ' _ {} \; -print  || true"
    print (findcmd)
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    d_elf_soexe_files[builddir] = files
    return files


# The config file contains (keyword, value) pairs.
# Each line is in format of keyword = value, it looks like below:
# objdump = /router/bin/objdump.c4.9.3-p0.ppc-linux
# addr2line = /router/bin/addr2line.c4.9.3-p0.ppc
# readelf = /router/bin/readelf.c4.7.0-p3.ppc
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


def set_config_progs():
    """
    Set the configured programs for later use.
    """
    global g_objdump_prog
    global g_addr2line_prog
    global g_readelf_prog
    if "objdump" in g_configs:
        g_objdump_prog = g_configs["objdump"]
    if "addr2line" in g_configs:
        g_addr2line_prog = g_configs["addr2line"]
    if "readelf" in g_configs:
        g_readelf_prog = g_configs["readelf"]


############################################################
#### OSC-METRIC feature, checking embedded MAGIC words ####
############################################################

def get_elf_section_hexdump(afile, section):
    '''
    Get hexdump of an ELF section content for afile.
    '''
    cmd = g_readelf_prog + " -x " + section + ' ' + cmd_quote(afile) + ' | grep "^  0x" || true'
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    lines = output.splitlines()
    array = []
    for line in lines:
        tokens = line.strip().split(" ")[1:5]
        for token in tokens:
            if token:
                array.append(token)
    return ''.join(array)


def get_file_hexdump(afile):
    cmd = "xxd -p " + cmd_quote(afile) + " | tr -d '\n'"
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    return output

## we only count stats for the below MAGIC words, not for safec MAGIC5/MAGIC6
magic_types_for_stats_old = {
    #'MAGIC_OSC_HEADER_INCLUDED': 'osc_header_included',
    'MAGIC_FUNC_NOMAPPING_MAGIC0': 'func_nomapping',
    'MAGIC_FUNC_MAGIC1': 'func_safe',
    'MAGIC_FUNC_MAGIC2': 'func_overflow_and_assert',
    'MAGIC_FUNC_MAGIC3': 'func_unknown_len_and_runtime_check',
    'MAGIC_FUNC_MAGIC4': 'func_unknown_dst_size_and_nothing-we-can-do',
}

## we only count stats for the below MAGIC words, not for safec MAGIC5/MAGIC6
magic_types_for_stats = {
    'COLUMN_0': ['MAGIC_FUNC_NOMAPPING_MAGIC0'],
    'COLUMN_1': ['MAGIC_FUNC_MAGIC1', 'MAGIC_FUNC_MAGIC7', 'MAGIC_FUNC_MAGIC8'],
    'COLUMN_2': ['MAGIC_FUNC_MAGIC2'],
    'COLUMN_3': ['MAGIC_FUNC_MAGIC3'],
    'COLUMN_4': ['MAGIC_FUNC_MAGIC4', 'MAGIC_FUNC_MAGIC9', 'MAGIC_FUNC_MAGICa', 'MAGIC_FUNC_MAGICb'],
}

## we only count stats for the below MAGIC words, not for safec MAGIC5/MAGIC6
magic_types_for_stats_src = {
    'COLUMN_0': ['MAGIC_FUNC_NOMAPPING_MAGIC0'],
    'COLUMN_1': ['MAGIC_FUNC_MAGIC7', 'MAGIC_FUNC_MAGICa'],
    'COLUMN_2': ['MAGIC_FUNC_MAGIC8', 'MAGIC_FUNC_MAGICb'],
    'COLUMN_3': ['MAGIC_FUNC_MAGIC3', 'MAGIC_FUNC_MAGIC9'],
    'COLUMN_4': ['MAGIC_FUNC_MAGIC1', 'MAGIC_FUNC_MAGIC2', 'MAGIC_FUNC_MAGIC4'],
}

g_src_overread_functions = ['memcpy', 'memmove', 'bcopy']

magic_types = {
    'MAGIC_OSC_NOMAP_H_INCLUDED' : 'nomap_header_included',
    'MAGIC_OSC_NOMAP_H_REASON_NOOPTIMIZE' : 'nomap_reason_nooptimize',
    'MAGIC_OSC_NOMAP_H_REASON_NOINLINE' : 'nomap_reason_noinline',
    'MAGIC_OSC_NOMAP_H_REASON_FORTIFY_SOURCE' : 'nomap_reason_fortify_source',
    'MAGIC_OSC_NOMAP_H_REASON_ASM' : 'nomap_reason_asm',
    'MAGIC_OSC_NOMAP_H_REASON_STRICT_ANSI' : 'nomap_reason_strict_ansi',
    'MAGIC_OSC_NOMAP_H_REASON_METRIC_ONLY' : 'nomap_reason_metric_only',
    'MAGIC_OSC_HEADER_INCLUDED': 'osc_header_included',
    'MAGIC_OSC_COMPILER_ICC': 'osc_compiler_icc',
    'MAGIC_OSC_COMPILER_CLANG': 'osc_compiler_clang',
    'MAGIC_OSC_COMPILER_GCC': 'osc_compiler_gcc',
    'MAGIC_OSC_COMPILER_OTHER': 'osc_compiler_other',
    'MAGIC_FUNC_NOMAPPING_MAGIC0': 'func_nomapping',
    'MAGIC_FUNC_MAGIC1': 'func_safe_dst',
    'MAGIC_FUNC_MAGIC2': 'func_dst_overflow_and_assert',
    'MAGIC_FUNC_MAGIC3': 'func_unknown_len_and_runtime_check',
    'MAGIC_FUNC_MAGIC4': 'func_unknown_dst_size_and_nothing-we-can-do',
    'MAGIC_FUNC_MAGIC5': 'func_safec_dmax_equal_to_n',
    'MAGIC_FUNC_MAGIC6': 'func_safec_dmax_less_than_n',
    'MAGIC_FUNC_MAGIC7': 'func_safe_dst_and_src',
    'MAGIC_FUNC_MAGIC8': 'func_src_overread_and_assert',
    'MAGIC_FUNC_MAGIC9': 'func_unknown_len_and_runtime_check_src',
    'MAGIC_FUNC_MAGICa': 'func_unknown_dst_size_and_src_safe',
    'MAGIC_FUNC_MAGICb': 'func_unknown_dst_size_and_src_overread',
}

# the magics array for byte_inline method
water_all_magics = {
    'FILEMAGICS': {
        '80818d8e80818d8e': 'MAGIC_OSC_HEADER_INCLUDED',
        '80818d8e80818d8f': 'MAGIC_OSC_NOMAP_H_INCLUDED',
        '80818d8e80818d01': 'MAGIC_OSC_NOMAP_H_REASON_NOOPTIMIZE',
        '80818d8e80818d02': 'MAGIC_OSC_NOMAP_H_REASON_NOINLINE',
        '80818d8e80818d03': 'MAGIC_OSC_NOMAP_H_REASON_FORTIFY_SOURCE',
        '80818d8e80818d04': 'MAGIC_OSC_NOMAP_H_REASON_ASM',
        '80818d8e80818d05': 'MAGIC_OSC_NOMAP_H_REASON_STRICT_ANSI',
        '80818d8e80818d06': 'MAGIC_OSC_NOMAP_H_REASON_METRIC_ONLY',
        '97cfa25a9fb39d01': 'MAGIC_OSC_COMPILER_ICC',
        '97cfa25a9fb39d02': 'MAGIC_OSC_COMPILER_CLANG',
        '97cfa25a9fb39d03': 'MAGIC_OSC_COMPILER_GCC',
        '97cfa25a9fb39d04': 'MAGIC_OSC_COMPILER_OTHER',
    },
    ### LIBC functions
    'memcpy': {
        '4d41474943d0aa00': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d0aa11': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d0aa22': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d0aa33': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d0aa44': 'MAGIC_FUNC_MAGIC4',
        '4d41474943d0aa77': 'MAGIC_FUNC_MAGIC7',
        '4d41474943d0aa88': 'MAGIC_FUNC_MAGIC8',
        '4d41474943d0aa99': 'MAGIC_FUNC_MAGIC9',
        '4d41474943d0aaaa': 'MAGIC_FUNC_MAGICa',
        '4d41474943d0aabb': 'MAGIC_FUNC_MAGICb',
    },
    'memmove': {
        '4d41474943d00000': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d00011': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d00022': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d00033': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d00044': 'MAGIC_FUNC_MAGIC4',
        '4d41474943d00077': 'MAGIC_FUNC_MAGIC7',
        '4d41474943d00088': 'MAGIC_FUNC_MAGIC8',
        '4d41474943d00099': 'MAGIC_FUNC_MAGIC9',
        '4d41474943d000aa': 'MAGIC_FUNC_MAGICa',
        '4d41474943d000bb': 'MAGIC_FUNC_MAGICb',
    },
    'memset': {
        '4d41474943d01100': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d01111': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d01122': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d01133': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d01144': 'MAGIC_FUNC_MAGIC4'
    },
    'bcopy': {
        '4d41474943d02200': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d02211': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d02222': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d02233': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d02244': 'MAGIC_FUNC_MAGIC4',
        '4d41474943d02277': 'MAGIC_FUNC_MAGIC7',
        '4d41474943d02288': 'MAGIC_FUNC_MAGIC8',
        '4d41474943d02299': 'MAGIC_FUNC_MAGIC9',
        '4d41474943d022aa': 'MAGIC_FUNC_MAGICa',
        '4d41474943d022bb': 'MAGIC_FUNC_MAGICb',
    },
    'bzero': {
        '4d41474943d03300': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d03311': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d03322': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d03333': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d03344': 'MAGIC_FUNC_MAGIC4'
    },
    'strcpy': {
        '4d41474943d04400': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d04411': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d04422': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d04433': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d04444': 'MAGIC_FUNC_MAGIC4'
    },
    'strncpy': {
        '4d41474943d05500': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d05511': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d05522': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d05533': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d05544': 'MAGIC_FUNC_MAGIC4'
    },
    'strcat': {
        '4d41474943d06600': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d06611': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d06622': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d06633': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d06644': 'MAGIC_FUNC_MAGIC4'
    },
    'strncat': {
        '4d41474943d07700': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d07711': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d07722': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d07733': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d07744': 'MAGIC_FUNC_MAGIC4'
    },
    'strnlen': {
        '4d41474943d08800': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d08811': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d08822': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d08833': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d08844': 'MAGIC_FUNC_MAGIC4'
    },
    'vsnprintf': {
        '4d41474943d09900': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d09911': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d09922': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d09933': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d09944': 'MAGIC_FUNC_MAGIC4'
    },
    ### SAFEC functions
    'memcmp_s': {
        '4d41474943d10100': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d18811': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d18822': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d18833': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d18844': 'MAGIC_FUNC_MAGIC4'
    },
    'memcpy_s': {
        '4d41474943d10200': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d10011': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d10022': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d10033': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d10044': 'MAGIC_FUNC_MAGIC4'
    },
    'strcat_s': {
        '4d41474943d10300': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d11111': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d11122': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d11133': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d11144': 'MAGIC_FUNC_MAGIC4'
    },
    'strcmp_s': {
        '4d41474943d10400': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d12211': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d12222': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d12233': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d12244': 'MAGIC_FUNC_MAGIC4'
    },
    'strcpy_s': {
        '4d41474943d10500': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d13311': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d13322': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d13333': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d13344': 'MAGIC_FUNC_MAGIC4'
    },
    'strncat_s': {
        '4d41474943d10600': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d14411': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d14422': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d14433': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d14444': 'MAGIC_FUNC_MAGIC4',
        '4d41474943d14445': 'MAGIC_FUNC_MAGIC5',
        '4d41474943d14446': 'MAGIC_FUNC_MAGIC6'
    },
    'strncpy_s': {
        '4d41474943d10700': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d15511': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d15522': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d15533': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d15544': 'MAGIC_FUNC_MAGIC4',
        '4d41474943d15545': 'MAGIC_FUNC_MAGIC5',
        '4d41474943d15546': 'MAGIC_FUNC_MAGIC6',
    },
    'strnlen_s': {
        '4d41474943d10800': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d16611': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d16622': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d16633': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d16644': 'MAGIC_FUNC_MAGIC4'
    },
    'strstr_s': {
        '4d41474943d10900': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d17711': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d17722': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d17733': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d17744': 'MAGIC_FUNC_MAGIC4'
    },
    ### GLIBC fortify-source functions
    'asprintf': {
        '4d41474943d20101': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20102': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20103': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20104': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20105': 'MAGIC_FUNC_MAGIC4',
    },
    'confstr': {
        '4d41474943d20201': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20202': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20203': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20204': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20205': 'MAGIC_FUNC_MAGIC4',
    },
    'dprintf': {
        '4d41474943d20301': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20302': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20303': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20304': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20305': 'MAGIC_FUNC_MAGIC4',
    },
    'fgets': {
        '4d41474943d20401': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20402': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20403': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20404': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20405': 'MAGIC_FUNC_MAGIC4',
    },
    'fgets_unlocked': {
        '4d41474943d20501': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20502': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20503': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20504': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20505': 'MAGIC_FUNC_MAGIC4',
    },
    'fgetws': {
        '4d41474943d20601': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20602': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20603': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20604': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20605': 'MAGIC_FUNC_MAGIC4',
    },
    'fgetws_unlocked': {
        '4d41474943d20701': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20702': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20703': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20704': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20705': 'MAGIC_FUNC_MAGIC4',
    },
    'fprintf': {
        '4d41474943d20801': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20802': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20803': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20804': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20805': 'MAGIC_FUNC_MAGIC4',
    },
    'fread': {
        '4d41474943d20901': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20902': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20903': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20904': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20905': 'MAGIC_FUNC_MAGIC4',
    },
    'fread_unlocked': {
        '4d41474943d20a01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20a02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20a03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20a04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20a05': 'MAGIC_FUNC_MAGIC4',
    },
    'fwprintf': {
        '4d41474943d20b01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20b02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20b03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20b04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20b05': 'MAGIC_FUNC_MAGIC4',
    },
    'getcwd': {
        '4d41474943d20c01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20c02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20c03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20c04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20c05': 'MAGIC_FUNC_MAGIC4',
    },
    'getdomainname': {
        '4d41474943d20d01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20d02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20d03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20d04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20d05': 'MAGIC_FUNC_MAGIC4',
    },
    'getgroups': {
        '4d41474943d20e01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20e02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20e03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20e04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20e05': 'MAGIC_FUNC_MAGIC4',
    },
    'gethostname': {
        '4d41474943d20f01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d20f02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d20f03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d20f04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d20f05': 'MAGIC_FUNC_MAGIC4',
    },
    'gets': {
        '4d41474943d21001': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21002': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21003': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21004': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21005': 'MAGIC_FUNC_MAGIC4',
    },
    'getwd': {
        '4d41474943d21101': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21102': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21103': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21104': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21105': 'MAGIC_FUNC_MAGIC4',
    },
    'longjmp': {
        '4d41474943d21201': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21202': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21203': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21204': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21205': 'MAGIC_FUNC_MAGIC4',
    },
    'mbsnrtowcs': {
        '4d41474943d21301': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21302': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21303': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21304': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21305': 'MAGIC_FUNC_MAGIC4',
    },
    'mbsrtowcs': {
        '4d41474943d21401': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21402': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21403': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21404': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21405': 'MAGIC_FUNC_MAGIC4',
    },
    'mbstowcs': {
        '4d41474943d21501': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21502': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21503': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21504': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21505': 'MAGIC_FUNC_MAGIC4',
    },
    'mempcpy': {
        '4d41474943d21601': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21602': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21603': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21604': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21605': 'MAGIC_FUNC_MAGIC4',
    },
    'poll': {
        '4d41474943d21701': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21702': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21703': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21704': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21705': 'MAGIC_FUNC_MAGIC4',
    },
    'ppoll': {
        '4d41474943d21801': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21802': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21803': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21804': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21805': 'MAGIC_FUNC_MAGIC4',
    },
    'pread': {
        '4d41474943d21901': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21902': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21903': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21904': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21905': 'MAGIC_FUNC_MAGIC4',
    },
    'printf': {
        '4d41474943d21a01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21a02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21a03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21a04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21a05': 'MAGIC_FUNC_MAGIC4',
    },
    'read': {
        '4d41474943d21b01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21b02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21b03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21b04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21b05': 'MAGIC_FUNC_MAGIC4',
    },
    'readlinkat': {
        '4d41474943d21c01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21c02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21c03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21c04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21c05': 'MAGIC_FUNC_MAGIC4',
    },
    'readlink': {
        '4d41474943d21d01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21d02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21d03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21d04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21d05': 'MAGIC_FUNC_MAGIC4',
    },
    'realpath': {
        '4d41474943d21e01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21e02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21e03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21e04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21e05': 'MAGIC_FUNC_MAGIC4',
    },
    'recv': {
        '4d41474943d21f01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d21f02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d21f03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d21f04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d21f05': 'MAGIC_FUNC_MAGIC4',
    },
    'recvfrom': {
        '4d41474943d22001': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22002': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22003': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22004': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22005': 'MAGIC_FUNC_MAGIC4',
    },
    'snprintf': {
        '4d41474943d22101': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22102': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22103': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22104': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22105': 'MAGIC_FUNC_MAGIC4',
    },
    'sprintf': {
        '4d41474943d22201': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22202': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22203': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22204': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22205': 'MAGIC_FUNC_MAGIC4',
    },
    'stpcpy': {
        '4d41474943d22301': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22302': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22303': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22304': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22305': 'MAGIC_FUNC_MAGIC4',
    },
    'stpncpy': {
        '4d41474943d22401': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22402': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22403': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22404': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22405': 'MAGIC_FUNC_MAGIC4',
    },
    'swprintf': {
        '4d41474943d22501': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22502': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22503': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22504': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22505': 'MAGIC_FUNC_MAGIC4',
    },
    'ttyname_r': {
        '4d41474943d22601': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22602': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22603': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22604': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22605': 'MAGIC_FUNC_MAGIC4',
    },
    'vasprintf': {
        '4d41474943d22701': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22702': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22703': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22704': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22705': 'MAGIC_FUNC_MAGIC4',
    },
    'vdprintf': {
        '4d41474943d22801': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22802': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22803': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22804': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22805': 'MAGIC_FUNC_MAGIC4',
    },
    'vfprintf': {
        '4d41474943d22901': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22902': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22903': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22904': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22905': 'MAGIC_FUNC_MAGIC4',
    },
    'vfwprintf': {
        '4d41474943d22a01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22a02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22a03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22a04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22a05': 'MAGIC_FUNC_MAGIC4',
    },
    'vprintf': {
        '4d41474943d22b01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22b02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22b03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22b04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22b05': 'MAGIC_FUNC_MAGIC4',
    },
    'vsprintf': {
        '4d41474943d22c01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22c02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22c03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22c04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22c05': 'MAGIC_FUNC_MAGIC4',
    },
    'vswprintf': {
        '4d41474943d22d01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22d02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22d03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22d04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22d05': 'MAGIC_FUNC_MAGIC4',
    },
    'vwprintf': {
        '4d41474943d22e01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22e02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22e03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22e04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22e05': 'MAGIC_FUNC_MAGIC4',
    },
    'wcpcpy': {
        '4d41474943d22f01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d22f02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d22f03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d22f04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d22f05': 'MAGIC_FUNC_MAGIC4',
    },
    'wcpncpy': {
        '4d41474943d23001': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23002': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23003': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23004': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23005': 'MAGIC_FUNC_MAGIC4',
    },
    'wcrtomb': {
        '4d41474943d23101': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23102': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23103': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23104': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23105': 'MAGIC_FUNC_MAGIC4',
    },
    'wcscat': {
        '4d41474943d23201': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23202': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23203': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23204': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23205': 'MAGIC_FUNC_MAGIC4',
    },
    'wcscpy': {
        '4d41474943d23301': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23302': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23303': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23304': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23305': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsncat': {
        '4d41474943d23401': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23402': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23403': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23404': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23405': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsncpy': {
        '4d41474943d23501': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23502': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23503': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23504': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23505': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsnrtombs': {
        '4d41474943d23601': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23602': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23603': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23604': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23605': 'MAGIC_FUNC_MAGIC4',
    },
    'wcsrtombs': {
        '4d41474943d23701': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23702': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23703': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23704': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23705': 'MAGIC_FUNC_MAGIC4',
    },
    'wcstombs': {
        '4d41474943d23801': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23802': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23803': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23804': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23805': 'MAGIC_FUNC_MAGIC4',
    },
    'wctomb': {
        '4d41474943d23901': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23902': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23903': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23904': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23905': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemcpy': {
        '4d41474943d23a01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23a02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23a03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23a04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23a05': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemmove': {
        '4d41474943d23b01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23b02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23b03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23b04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23b05': 'MAGIC_FUNC_MAGIC4',
    },
    'wmempcpy': {
        '4d41474943d23c01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23c02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23c03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23c04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23c05': 'MAGIC_FUNC_MAGIC4',
    },
    'wmemset': {
        '4d41474943d23d01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23d02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23d03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23d04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23d05': 'MAGIC_FUNC_MAGIC4',
    },
    'wprintf': {
        '4d41474943d23e01': 'MAGIC_FUNC_NOMAPPING_MAGIC0',
        '4d41474943d23e02': 'MAGIC_FUNC_MAGIC1',
        '4d41474943d23e03': 'MAGIC_FUNC_MAGIC2',
        '4d41474943d23e04': 'MAGIC_FUNC_MAGIC3',
        '4d41474943d23e05': 'MAGIC_FUNC_MAGIC4',
    },
}

#g_libc_functions = ['memcpy', 'memcpysrc', 'memmove', 'memset', 'bcopy', 'bzero',
g_libc_functions = ['memcpy', 'memmove', 'memset', 'bcopy', 'bzero',
                    'strcpy', 'strncpy', 'strcat', 'strncat', 'strnlen', 'vsnprintf']
g_safec_functions = ['memcmp_s', 'memcpy_s', 'strcat_s', 'strcmp_s', 'strcpy_s',
                     'strncat_s', 'strncpy_s', 'strnlen_s', 'strstr_s']
### for watermark stats only
func_magics_watermarkpc = ['MAGIC_FUNC_NOMAPPING_MAGIC0', 'MAGIC_FUNC_MAGIC1',
               'MAGIC_FUNC_MAGIC2', 'MAGIC_FUNC_MAGIC3', 'MAGIC_FUNC_MAGIC4',
               'MAGIC_FUNC_MAGIC5', 'MAGIC_FUNC_MAGIC6', 'MAGIC_FUNC_MAGIC7',
               'MAGIC_FUNC_MAGIC8', 'MAGIC_FUNC_MAGIC9', 'MAGIC_FUNC_MAGICa',
               'MAGIC_FUNC_MAGICb']

# Reverse subdicts of 'function', 'type', and 'common' for reverse lookup
reverse_magic_types = dict((v, k) for k, v in magic_types.items())
#print (reverse_magic_types)
reverse_all_magics = {}


def initialize_all_magics(magic_type):
    '''
    Initialize magic arrays based on magic_type.
    '''
    global reverse_all_magics
    global g_all_magics
    reverse_all_magics = {}
    g_all_magics = water_all_magics
    if magic_type == 'dwarf_loc':
        g_all_magics = loc_all_magics
    for function, magics in g_all_magics.items():
        reverse_all_magics[function] = dict((v, k) for k, v in magics.items())
    #print (reverse_all_magics)


# Wrapper function for the actual check_magic
def check_magic(builddir):
    """
    Checks MAGIC words of all binary files in the builddir.
    It prints a summary of the check result.

    :param builddir: Build dir of the workspace
    """
    print_start_time()
    print ("")
    print ("##### Now performing MAGIC words: binary file check.")
    print ("#####  - Generate a list of stats for each MAGIC-WORDS.")
    print ("Build dir is: " + builddir)
    len_prefix = len(os.path.abspath(builddir).rstrip('/')) + 1
    subdict = dict()
    checktype = "MAGIC"
    if checktype in result_dict:
        subdict = result_dict[checktype]
    else:
        result_dict[checktype] = subdict
    subdict[builddir] = dict()

    (stats_db, d_sum) = get_stats_for_all_files(builddir, get_all_osc_magic_words())
    # Do all the functions
    for function in g_all_magics:
        check_magic_for_func(builddir, subdict, function, stats_db)
    subdict[builddir]["SUM_STATS"] = d_sum
    #print (d_sum)
    print ("Total number of OSC functions: " + str(len(g_all_magics) - 1))
    print ("Total number of magic words to count: " + str(len(d_sum)))
    print_end_time()


def get_all_osc_magic_words():
    '''
    Get a list of all magic words for OSC-metric.
    '''
    result = dict()
    for func in g_all_magics:
        magics = g_all_magics[func]
        for m in magics:
            if m in result:
                 print ("***WARNING***: duplicate magic word " + m)
            result[m] = magics[m]
    return result


def get_stats_of_magic_words_water(afile, magics):
    '''
    Get stats for all the magic words in the magics list for afile.
    It generates a hexdump of the file, and then count magic words.
    '''
    hexstr = get_file_hexdump(afile)
    result = dict()
    for magic in magics:
        ct = hexstr.count(magic)
        result[magic] = ct
    return result


def get_stats_of_magic_words_loc(afile, magics):
    '''
    Get stats for all the magic words in the magics list for afile.
    It generates a magic_list of the file, and then count magic words.
    '''
    lines = get_osc_metric_lines_of_afile(afile)
    result = dict()
    for magic in magics:
        ct = lines.count(magic)
        result[magic] = ct
    hexstr = get_elf_section_hexdump(afile, ".data")
    for magic in magics:
        ct = hexstr.count(magic)
        if not result[magic]:
            result[magic] = ct
    return result


def get_stats_of_magic_words(afile, magics):
    '''
    Get stats for all the magic words in the magics list for afile.
    It automatically picks the right magics array based on magic_type configured.
    '''
    if args.magictype and args.magictype == 'byte_inline':
        return get_stats_of_magic_words_water(afile, magics)
    return get_stats_of_magic_words_loc(afile, magics)


def get_nonzero_stats_db(stats_db):
    '''
    Delete all-zero entries in the stats DB.
    '''
    result = dict()
    for line in stats_db:
        stats = stats_db[line]
        if sum(stats.values()) > 0:
            result[line] = dict(stats)
    return result


def get_stats_db_for_func(stats_db, function):
    '''
    Filter stats DB for a specific function.
    '''
    result = dict()
    for line in stats_db:
        stats = stats_db[line]
        newstats = dict()
        sum_stats = 0
        for m in stats:
            if m in g_all_magics[function]:
                sum_stats += stats[m]
                newstats[m] = stats[m]
        if sum_stats > 0:
            result[line] = newstats
    return result


def has_unsuccessful_mappings_for_stats(stats):
    for func in reverse_all_magics:
        if func == 'FILEMAGICS':
            continue
        magics = reverse_all_magics[func]
        if 'MAGIC_FUNC_NOMAPPING_MAGIC0' in magics and stats[magics['MAGIC_FUNC_NOMAPPING_MAGIC0']] > 0:
            return True
    return False


def get_total_unsuccessful_mappings_for_stats(stats):
    sum_mappings = 0
    for func in reverse_all_magics:
        if func == 'FILEMAGICS':
            continue
        magics = reverse_all_magics[func]
        if 'MAGIC_FUNC_NOMAPPING_MAGIC0' in magics:
            sum_mappings += stats[magics['MAGIC_FUNC_NOMAPPING_MAGIC0']]
    return sum_mappings


def get_noheader_nomap_list_from_stats_db(stats_db):
    noheader_list = []
    nomap_list = []
    for line in stats_db:
        stats = stats_db[line]
        if stats[reverse_all_magics['FILEMAGICS']['MAGIC_OSC_HEADER_INCLUDED']] == 0:
            noheader_list.append(line)
        elif has_unsuccessful_mappings_for_stats(stats):
            nomap_list.append(line)
    return (noheader_list, nomap_list)


def create_osc_sum_stats():
    stats = dict()
    for func in g_all_magics:
        magics = g_all_magics[func]
        for m in magics:
            stats[m] = [0, func, magic_types[magics[m]]]
    return stats


def add_stats(stats_sum, stats):
    for m in stats:
        stats_sum[m][0] += stats[m]


def get_stats_for_all_files(builddir, osc_magics):
    stats_db = dict()
    d_sum = create_osc_sum_stats()
    files = []
    if args.scan_all_elf_files:
        files = find_all_elf_files(builddir)
    else:
        files = find_all_elf_soexe_files(builddir)
    for line in files:
        stats = get_stats_of_magic_words(line, osc_magics)
        add_stats(d_sum, stats)
        stats_db[line] = stats
    return (stats_db, d_sum)


def check_magic_for_func(builddir, subdict, function, stats_db):
    rdict = subdict[builddir][function] = {}
    elf_list = "elf_file_stats"
    if function == "FILEMAGICS":    ### save file-stats for FILEMAGICS only
        rdict["all_elf_file_stats"] = get_nonzero_stats_db(stats_db)
        rdict["osc_file_total_count"] = len(stats_db)
        (noheader_list, nomap_list) = get_noheader_nomap_list_from_stats_db(stats_db)
        rdict["osc_file_noheader_list"] = noheader_list
        rdict["osc_file_nomap_list"] = nomap_list
        rdict["osc_file_noheader_list_size"] = len(noheader_list)
        rdict["osc_file_nomap_list_size"] = len(nomap_list)
    rdict[elf_list] = get_stats_db_for_func(stats_db, function)
    return


############################################################
#### End of OSC-METRIC feature, checking MAGIC words ####
############################################################

############################################################
#### OSC-METRIC-SOURCE feature, print Source Code Info ####
############################################################

# the pretty-print output of addr2line (with -p option) is like below:
#__builtin_strncpy at test/openosc_test.c:8389379
# (inlined by) openosc_test_strcpy at test/openosc_test.c:25
# (inlined by) main at test/openosc_test.c:72
def get_func_srcline_from_addr2line_decode_line_pretty(line):
    '''
    Extract function and srcline from the addr2line code line in pretty-print format.
    '''
    line = line.strip()
    tokens = line.split()
    if "(inlined by) " in line and len(tokens) > 4:
        tokens2 = line.split(" at ")
        if len(tokens2) > 1:
            return (tokens[2], tokens2[1])
        return (tokens[2], tokens[4])
    elif len(tokens) > 2:
        tokens2 = line.split(" at ")
        if len(tokens2) > 1:
            return (tokens[0], tokens2[1])
        return (tokens[0], tokens[2])
    if len(tokens) > 1:
        return (tokens[0], tokens[1])
    return (line, '')


def pick_addr2line_decode_entry(lines):
    """
    Pick the best addr2line decode entry for a file for a specific PC.
    this handles "addr2line -p" output or pretty-print format output.

    :param lines: the decode output from addr2line
    :returns the addr2line info for the lines
    """
    func = srcline = ''
    if args.pc_decode_entry:
        entry = int(args.pc_decode_entry, 0)
        if ( (entry >= 0 and len(lines) > 2*entry+1) or
             (entry < 0 and len(lines) > -2*entry+1) ):
            func = lines[2*entry]
            srcline = lines[2*entry + 1]
    if func:
        return (func, srcline)
    #print(lines)
    # always pick the last entry or the first inline entry
    if len(lines) > 2:
        for line in lines:
            if "(inlined by) " in line:
                (func, srcline) = get_func_srcline_from_addr2line_decode_line_pretty(line)
                tokens = srcline.split(":")
                if tokens[0][-2:].lower() != '.h':
                    return (func, srcline)
    if len(lines) > 0:
        return get_func_srcline_from_addr2line_decode_line_pretty(lines[-1])
    return (func, srcline)


def pick_addr2line_decode_entry_nopretty(lines):
    """
    Pick the best addr2line decode entry for a file for a specific PC
    this handles addr2line output without -p option.

    :param lines: the decode output from addr2line
    :returns the addr2line info for the lines
    """
    func = srcline = ''
    if args.pc_decode_entry:
        entry = int(args.pc_decode_entry, 0)
        if ( (entry >= 0 and len(lines) > 2*entry+1) or
             (entry < 0 and len(lines) > -2*entry+1) ):
            func = lines[2*entry]
            srcline = lines[2*entry + 1]
    if func:
        return (func, srcline)
    #print(lines)
    # always pick the last entry or the second-to-last entry
    if len(lines) > 5:
        func = lines[-4]
        srcline = lines[-3]
    elif len(lines) > 1:
        func = lines[-2]
        srcline = lines[-1]
    elif len(lines) > 0:
        func = lines[0]
    return (func, srcline)


def get_addr2line_info(afile, pc):
    """
    Retrieve addr2line info for a file for a specific PC

    :param afile: a file
    :param pc: PC address
    :returns the addr2line info for this PC address.
    """
    # pc_extraoffset is added to get a better decoding of srcline info.
    orig_pc = pc
    extraoffset = args.pc_extraoffset
    if extraoffset:
        int_pc = int(pc, 0) + int(extraoffset, 0)
        pc = hex(int_pc)
    #cmd = g_addr2line_prog + ' -f -i -e ' + cmd_quote(afile) + ' ' + pc + ' || true'
    # Add -C or --demangle option for CPP function decoding
    #cmd = g_addr2line_prog + ' -C -f -i -e ' + cmd_quote(afile) + ' ' + pc + ' || true'
    # Add -p or --pretty-print option for better display
    cmd = g_addr2line_prog + ' -p -C -f -i -e ' + cmd_quote(afile) + ' ' + pc + ' || true'
    output = get_shell_cmd_output(cmd)
    if extraoffset:
        verbose(afile + " addr2line output with extraoffset " + extraoffset + " for orig_pc: " + orig_pc + " new PC " + pc + " is: " + output, LEVEL_2)
    else:
        verbose(afile + " addr2line output for PC " + pc + " is: " + output, LEVEL_2)
    lines = output.splitlines()
    (func, srcline) = pick_addr2line_decode_entry(lines)
    #(func, srcline) = pick_addr2line_decode_entry_nopretty(lines)
    return (cmd, lines, func, srcline)
    #return (cmd, output, func, srcline)


def get_text_section_info(afile):
    """
    Retrieve ELF section .text info for a file

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
 12 .text         000001d2  08048350  08048350  00000350  2**4

    :param afile: a file
    :returns the ELF section .text info, like size, offset, address, etc
    """
    cmd = g_objdump_prog + ' -h ' + cmd_quote(afile) + ' | grep " .text " || true'
    output = get_shell_cmd_output(cmd)
    if output:
        tokens = output.split()
        section_size = tokens[2]
        file_offset = tokens[5]
        vma = tokens[3]
        verbose(afile + " .text size: " + section_size + " offset: " + file_offset + " vma: " + vma, LEVEL_2)
        return (int(section_size, 16), int(file_offset, 16), int(vma, 16))
    print ("Failed to get .text section info from " + afile)
    return (0, 0, 0)


def warn_if_addr2line_notmatch_osc_func(oscfunc, output, word):
    """
    Print some warnings when the addr2line decoded function does not match the expected osc function.
    This usually means false-positive due to MAGIC word conflicts.
    We may need to pick a new MAGIC word to avoid the conflicts.
    """
    lines = output.splitlines()
    if len(lines) > 3:
        func = lines[0]
        if len(func) > 0 and func[0] != "?" and func != "osc_" + oscfunc:
            verbose("The decoded function is " + func + " not the expected osc_" + oscfunc + " Possible MAGIC word conflits for " + word, LEVEL_2);


### For Destination size, source size, and copy length
DSTSIZE_MAGIC  = '778899aabbccddee'
DSTSIZE_MAGIC2 = '778899aabbccddef'


def convert_hex_str_to_signed_int(hexstr):
    x = int(hexstr,0)
    if x > 0x7FFFFFFFFFFFFFFF:
        x -= 0x10000000000000000
    return x


def get_dst_objsize(text):
    i = 0
    while i < len(text) - 16:
        word = text[i:i+16]
        if word == DSTSIZE_MAGIC:
            return "0x" + text[i+16:i+32]
        i += 2
    return "NOT_FOUND"


def convert_hex_str_to_signed_int2(hexstr):
    tokens = hexstr.split(',')
    xlist = []
    for token in tokens:
        x = convert_hex_str_to_signed_int(token)
        xlist.append(str(x))
    return ','.join(xlist)


def get_dst_len_objsize(text):
    '''
    Get hex string of dst, src, len, embedded in text.
    '''
    i = 0
    # while i <= len(text) - 16:
    while i <= 16:
        word = text[i:i+16]
        if word == DSTSIZE_MAGIC:
            if i > len(text) - 32:
                return "NOT_FOUND"
            dst_size = "0x" + text[i+16:i+32]
            if i > len(text) - 48:
                return dst_size
            next_8byte = text[i+32:i+48]
            if next_8byte == DSTSIZE_MAGIC2:
                return dst_size
            else:
                src_size = next_8byte
                if i >= len(text) - 64:
                    return dst_size + ",0x" + src_size
                next_8byte = text[i+48:i+64]
                if next_8byte == DSTSIZE_MAGIC2:
                    return dst_size + ",0x" + src_size
                else:
                    return dst_size + ",0x" + src_size + ",0x" + next_8byte
        i += 2
    return "NOT_FOUND"


def match_magic_word(word, magics):
    """
    Given 64bit word, find the matched predefined magic word.

    :param word: 64bit word in hex string format
    :param magics: the predefined magic words for all OSC functions
    :returns the matched osc function and the case out of those 5 cases.
    """
    for func in magics:
        func_magics = magics[func]
        for magic in func_magics:
            if word == magic:
                return (func, func_magics[magic])
    return None


def scan_text_section_from_file(afile, magics):
    """
    Scan MAGIC words of all binary files in the builddir
     and derive the PCs/source code lines of those watermarks.
    It prints a summary of the check result.

    :param afile: a binary file to scan magic words and retrieve srcline info
    :param magics: the predefined magic words for all OSC functions
    :returns the list of magic words and its srcline info
    """
    verbose("Scanning .text section from " + afile, LEVEL_1)
    (size, offset, vma) = get_text_section_info(afile)
    verbose(afile + " read .text size: " + str(size) + " offset: " + str(offset) + " vma: " + str(vma), LEVEL_1)
    if size == 0 or offset == 0:
        print ("Failed to get .text section info from " + afile)
        return ([], (size, offset, vma))
    text_bytes = ''
    with open(afile , "rb") as binary_file:
        # Seek a specific position in the file and read N bytes
        binary_file.seek(offset, 0)  # Go to beginning of the file
        text_bytes = binary_file.read(size)
    text_array = []
    if isinstance(text_bytes, str):
        for c in text_bytes:
            text_array.append(format(ord(c), "02x"))    ### for Python2 only
    else:
        for c in text_bytes:
            text_array.append(format(c, "02x"))         ### for Python3
    text = "".join(text_array)
    #print ("text_array len: " + str(len(text_array)) + " text len: " + str(len(text)))
    #print (text)
    magic_list = []
    i = 0
    while i < 2 * size - 16:
        word = text[i:i+16]
        match = match_magic_word(word, magics)
        if not match:
            i += 2
            continue
        pc = vma + i//2
        hex_pc = hex(pc)
        verbose("offset: " + str(i//2) + " magic: " + word + " vma: " + hex(vma) + " pc: " + hex_pc + " " + str(match), LEVEL_1)
        i += 16
        (cmd, output, srcfunc, srcline) = get_addr2line_info(afile, hex_pc)
        d = dict()
        d['PC'] = hex_pc
        d['offset'] = i//2
        d['magic'] = word
        d['oscfunc'] = match[0]
        d['caseno'] = match[1]
        #d['addr2line_output'] = output
        #d['addr2line_cmd'] = 'addr2line -f -i -e ' + cmd_quote(os.path.basename(afile)) + ' ' + hex_pc
        d['srcfunc'] = srcfunc
        d['srcline'] = srcline
        d['addr2line_cmd'] = cmd
        d['addr2line_output'] = output
        # try to see if __builtin_object_size of dst buffer is embedded too
        dst_objsize_hexstr = get_dst_len_objsize(text[i:i+96])
        d['dstsize_hexstr'] = dst_objsize_hexstr
        if dst_objsize_hexstr != "NOT_FOUND":
            #d['dstsize'] = convert_hex_str_to_signed_int(dst_objsize_hexstr)
            d['dstsize'] = convert_hex_str_to_signed_int2(dst_objsize_hexstr)
        magic_list.append(d)
        # warn_if_addr2line_notmatch_osc_func(match[0], output, word)
    #print (magic_list)
    #print (len(magic_list))
    return (magic_list, (size, offset, vma))


def get_total_case_num_of_magic_list(magic_list):
    """
    Get the total num for all 5 cases of a binary file

    :param magic_list: the magic word list for a file
    :returns a tuple of total nums for all cases
    """
    case_nums = {k : 0 for k in func_magics_watermarkpc}
    for d_magic in magic_list:
        caseno = d_magic["caseno"]
        if caseno in case_nums:
            case_nums[caseno] += 1
    total_num = sum(case_nums.values())
    case_nums['total_num'] = total_num
    return case_nums


def get_srcline_pc_list(magic_list):
    """
    Get the PC list indexed by the srcline

    :param magic_list: the magic word list for a file
    :returns a dictionary with srcline as the key
    """
    d_srcline = dict()
    for pc_entry in magic_list:
        srcline = pc_entry["srcline"]
        pc = pc_entry["PC"]
        oscfunc = pc_entry["oscfunc"]
        caseno = pc_entry["caseno"]
        if srcline in d_srcline:
            d_srcline[srcline].append([pc, caseno, oscfunc])
        else:
            d_srcline[srcline] = [[pc, caseno, oscfunc]]
    return d_srcline


### the list of OpenOSC header files
openosc_header_files = ['osc_map.h',
'openosc_fortify_redirect_nomap.h',
'openosc_fortify_redefine_nomap.h',
#'openosc_map.h',
#'openosc_nomap.h',
'openosc_redirect_map.h',
'openosc_redirect_nomap.h',
'osc_nomap.h',
'osc_safec_map.h',
'osc_safec_nomap.h',
#'openosc_fortify_map.h',
#'openosc_fortify_nomap.h',
'openosc_fortify_redefine_map.h',
'openosc_fortify_redirect_map.h',
]

def get_adjusted_num_srcline_magic(d_srcline):
    """
    Adjust number of srcline and magics by excluding OpenOSC header lines
    """
    osc_header_srcline = 0
    osc_header_pc = 0
    total_pc = 0
    for srcline in d_srcline:
        total_pc += len(d_srcline[srcline])
        for hfile in openosc_header_files:
            if hfile in srcline:
                osc_header_srcline += 1
                osc_header_pc += len(d_srcline[srcline])
                break
    return (len(d_srcline) - osc_header_srcline, total_pc - osc_header_pc)


def get_total_adjusted_srcline_num_for_all_files(fdict):
    """
    Get the total adjusted num for srcline and magics.

    :param fdict: the dict of all files with watermark PC.
    :returns a tuple of total nums for all files
    """
    total_adjusted_magic_num = 0
    total_magic_num = 0
    total_adjusted_srcline_num = 0
    total_srcline_num = 0
    for afile in fdict:
        num_srcline = fdict[afile]["num_srcline_list"]
        adjusted_num_srcline = fdict[afile]["adjusted_num_srcline_list"]
        adjusted_num_magic = fdict[afile]["adjusted_num_magic_list"]
        num_magic = fdict[afile]["num_magic_list"]
        total_srcline_num += num_srcline
        total_adjusted_srcline_num += adjusted_num_srcline
        total_adjusted_magic_num += adjusted_num_magic
        total_magic_num += num_magic
    d_total_srcline_stats = dict()
    d_total_srcline_stats["total_srcline_num"] = total_srcline_num
    d_total_srcline_stats["total_adjusted_srcline_num"] = total_adjusted_srcline_num
    d_total_srcline_stats["total_magic_num"] = total_magic_num
    d_total_srcline_stats["total_adjusted_magic_num"] = total_adjusted_magic_num
    d_total_srcline_stats["avg_num_of_pc_per_srcline"] = 0
    if total_srcline_num:
        d_total_srcline_stats["avg_num_of_pc_per_srcline"] = (1.0 * total_magic_num)/total_srcline_num
    d_total_srcline_stats["avg_adjusted_num_of_pc_per_srcline"] = 0
    if total_adjusted_srcline_num:
        d_total_srcline_stats["avg_adjusted_num_of_pc_per_srcline"] = (1.0 * total_adjusted_magic_num)/total_adjusted_srcline_num
    return d_total_srcline_stats


def get_total_watermarkpc_num_for_all_files(fdict):
    """
    Get the total num for all function-magic cases for all binary files

    :param fdict: the dict of all files with watermark PC.
    :returns a tuple of total nums for all files
    """
    total_case_nums = {k : 0 for k in func_magics_watermarkpc}
    total_case_nums['total_num'] = 0
    for afile in fdict:
        case_nums = fdict[afile]["total_case_nums"]
        for k in case_nums:
            total_case_nums[k] += case_nums[k]
    return total_case_nums


def find_match_unstripped_file(afile, wsdirs, text_section_d):
    """
    Find the unstripped file with DEBUG-INFO for afile

    :param afile: a stripped binary file
    :param wsdirs: a list of workspace dirs to search for unstripped file
    :param text_section_d: text section info, like size, offset, vma
    :returns the unstripped file that matches text_section_info
    """
    files = []
    for wsdir in wsdirs:
        files.extend(find_specific_unstripped_file(wsdir, os.path.basename(afile)))
    for ufile in files:
        (size, offset, vma) = get_text_section_info(ufile)
        if (text_section_d["text_size"] == size and
            text_section_d["text_offset"] == offset and
            text_section_d["text_vma"] == vma):
            return ufile
    return None


def print_watermarkpc_summary_table(rdict, wsdirs=[]):
    """
    Print watermark-PC summary table for all files in the result dictionary.

    :param rdict: the dict of all files with watermark PC.
    :param wsdirs: the list of build workspace directory that contains unstripped binary files, this is optional
    :returns None
    """
    print ("")
    print (HDR2)
    print ("OSC-METRIC WatermarkPC summary for all binary files")
    print ("## Note: DSTSIZE is format of: (dstsize, srcsize, copylen), (dstsize, copylen), or (dstsize).")
    print ("##       Copy-length of -9 means that the copy-length parameter")
    print ("##       for memcpy is unknown (non-constant) at compile-time.")
    print (HDR2)
    fmts = ['{:6}', '{:12}', '{:<12}', '{:<7}', '{:<12}', '{:<30}', '{:}']
    heading = ['Idx', 'PC', ' OSCFUNC', ' CASE#', ' DSTSIZE', ' SRCFUNC', ' SRCLINE']
    heading_row = print_row(fmts, heading)
    heading_line = '-' * len(heading_row)
    file_index = 0
    for afile in rdict:
        magic_list = rdict[afile]["magic_list"]
        match = afile
        run_addr2line = False
        if wsdirs:
            pc_entry = magic_list[0]
            if pc_entry["srcline"] == "??:?" or pc_entry["srcline"] == "??:0":
                match = find_match_unstripped_file(afile, wsdirs, rdict[afile]["text_section_info"])
                if match:
                    run_addr2line = True
        print ("")
        print (heading_line)
        file_index += 1
        print ("FileIndex: " + str(file_index) + " " + match)
        print (heading_row)
        print (heading_line)
        i = 0
        for pc_entry in magic_list:
            row_list = []
            row_list.append(str(i))
            i += 1
            row_list.append(pc_entry['PC'])
            row_list.append(' ' + pc_entry['oscfunc'])
            row_list.append(" CASE" + pc_entry['caseno'][-1])
            if 'dstsize' in pc_entry:
                row_list.append(' ' + str(pc_entry['dstsize']))
            else:
                row_list.append(" NOTFOUND")
            #row_list.append(pc_entry['dstsize_hexstr'])
            if run_addr2line:
                (cmd, output, srcfunc, srcline) = get_addr2line_info(match, pc_entry['PC'])
                row_list.append(' ' + srcfunc)
                row_list.append(' ' + srcline)
            else:
                row_list.append(' ' + pc_entry['srcfunc'])
                row_list.append(' ' + pc_entry['srcline'])
            print (print_row(fmts, row_list))


def find_specific_file(builddir, filename):
    """
    Find all files with a specific filename in the build dir, excluding symbolic link files.

    It simply runs the shell's find command and saves the result.

    :param builddir: String, build dir of the workspace
    :param filename: String, a specific filename, like libosc.so/lib4arg.so
    :returns a list that contains all the binary file names.
    """
    findcmd = "find " + cmd_quote(builddir) + " -type f -name '" + filename + "' -print || true "
    output = subprocess.check_output(findcmd, shell=True, universal_newlines=True)
    files = output.splitlines()
    return files


def find_specific_files(builddir, afiles):
    files = []
    for afile in afiles:
        files.extend(find_specific_file(builddir, os.path.basename(afile)))
    return files


def check_watermarkpc(builddir):
    """
    Checks MAGIC words of all binary files in the builddir
     and derive the PCs/source code lines of those watermarks.
    It prints a summary of the check result.

    :param builddir: Build dir of the workspace
    """
    print_start_time()
    print ("")
    print ("##### Now performing WATERMARKPC sourceline check for all binary files.")
    print ("#####  - Generate a list of PC and source code line for each MAGIC-WORD.")
    print ("Build dir is: " + builddir)
    len_prefix = len(os.path.abspath(builddir).rstrip('/')) + 1
    subdict = dict()
    checktype = "WATERMARKPC"
    if checktype in result_dict:
        subdict = result_dict[checktype]
    else:
        result_dict[checktype] = subdict
    subdict[builddir] = dict()
    rdict = subdict[builddir]
    files = []
    if args.watermarkfiles:  # only check specific set of files
        watermarkfiles = args.watermarkfiles.split(',')
        files = find_specific_files(builddir, watermarkfiles)
    elif args.scan_all_elf_files:
        files = find_all_elf_files(builddir)
    else:
        files = find_all_elf_soexe_files(builddir)
    non_watermarkpc_files = []
    watermarkpc_file_dict = dict()
    for line in files:
        if args.magictype and args.magictype == 'byte_inline':
            (magic_list, text_section_info) = scan_text_section_from_file(line, g_all_magics)
        else:
            magic_list = scan_debug_lines_from_file(line, g_all_magics)
        if not magic_list:
            non_watermarkpc_files.append(line)
            continue
        watermarkpc_file_dict[line] = d = dict()
        if args.magictype and args.magictype == 'byte_inline':
            d["text_section_info"] = {'text_size' : text_section_info[0],
                                  'text_offset' : text_section_info[1],
                                  'text_vma' : text_section_info[2]}
        d["magic_list"] = magic_list
        d["num_magic_list"] = len(magic_list)
        d["total_case_nums"] = get_total_case_num_of_magic_list(magic_list)
        d["srcline_list"] = get_srcline_pc_list(magic_list)
        d["num_srcline_list"] = len(d["srcline_list"])
        d["num_of_pc_per_srcline"] = 0
        if d["num_srcline_list"]:
            d["num_of_pc_per_srcline"] = (1.0 * d["num_magic_list"])/d["num_srcline_list"]
        (d["adjusted_num_srcline_list"], d["adjusted_num_magic_list"]) = get_adjusted_num_srcline_magic(d["srcline_list"])
        d["adjusted_num_of_pc_per_srcline"] = 0
        if d["adjusted_num_srcline_list"]:
            d["adjusted_num_of_pc_per_srcline"] = (1.0 * d["adjusted_num_magic_list"])/d["adjusted_num_srcline_list"]
    print ("Total number of files that contain OSC-FUNC watermarks: " + str(len(watermarkpc_file_dict)))
    print ("Total number of files that does NOT contain OSC-FUNC watermarks: " + str(len(non_watermarkpc_files)))
    rdict["total_watermarkpc_case_nums"] = get_total_watermarkpc_num_for_all_files(watermarkpc_file_dict)
    rdict["total_srcline_stats"] = get_total_adjusted_srcline_num_for_all_files(watermarkpc_file_dict)
    rdict["total_watermarkpc_files"] = len(watermarkpc_file_dict)
    rdict["watermarkpc_files"] = watermarkpc_file_dict
    rdict["total_all_candidate_files"] = len(files)
    rdict["non_watermarkpc_file_list"] = non_watermarkpc_files
    rdict["non_watermarkpc_file_list_size"] = len(non_watermarkpc_files)

    pass_count = len(watermarkpc_file_dict)
    fail_count = len(non_watermarkpc_files)
    print ("Results for Watermark PC check:")
    print (HDR3)
    print ("#pass:          " + str(pass_count))
    print ("#fail:          " + str(fail_count))

    total_count = pass_count + fail_count
    print ("#total:         " + str(total_count))
    pass_percent = DEFAULT_PASS_PERCENT
    if total_count > 0:
        pass_percent = 100 * pass_count / total_count
    print ("pass percentage: " + str(pass_percent) + "%")
    print (HDR3)
    rdict["pass_count"] = pass_count
    rdict["fail_count"] = fail_count
    rdict["total_count"] = total_count
    rdict["pass_percent"] = pass_percent
    print_end_time()
    print_start_time()
    print_watermarkpc_summary_table(watermarkpc_file_dict)
    print_end_time()
    return pass_percent



############################################################
#### OSC-METRIC-SOURCE feature, print Source Code Info ####
############################################################

def is_version_string(string):
    """
    Check if a string is version string like 3.0.4-7 or 4.0.37-dev.
    Only digits are allowed for version part.
    Non-digits are allowed for the revision part, like 4.0.37-dev.
    """
    if not string:
        return False
    tokens = string.split("-")
    if len(tokens) > 2 or (len(tokens) == 2 and len(tokens[1]) > 10):
        return False
    versions = tokens[0].split(".")
    if len(versions) > 4:
        return False
    for ver in versions:
        if not ver.isdigit():
            return False
    return True


def get_safec_lib_version(afile, strings_output=""):
    """
    Retrieve SAFEC library version from the SAFEC library file.
    """
    if not strings_output:
        cmd = 'strings ' + cmd_quote(afile) + ' || true'
        strings_output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    lines = strings_output.splitlines()
    for line in lines:
        if line[:11] == "ciscosafec " and is_version_string(line[11:]):
            return line.rstrip()
    return ""


def get_safec_lib_version_of_files(afiles):
    """
    Retrieve SAFEC library version from a list of SAFEC library files.
    """
    for afile in afiles:
        ver = get_safec_lib_version(afile)
        if ver:
            return ver
    return ""


def get_osc_lib_version(afile, strings_output=""):
    """
    Retrieve OSC library version from the OSC library file.
    """
    if not strings_output:
        cmd = 'strings ' + cmd_quote(afile) + ' || true'
        strings_output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    lines = strings_output.splitlines()
    for line in lines:
        if line[:9] == "ciscoosc " and is_version_string(line[9:]):
            return line.rstrip()
        if line[:8] == "openosc " and is_version_string(line[8:]):
            return line.rstrip()
    return "libosc 1.0.x"


def is_osc_lib_file(afile):
    """
    Check if a file is OSC library file.
    """
    ### skip debug version of the OSC library, due to version retrieval issue
    if "debug" in os.path.basename(afile):
        return False
    cmd = g_readelf_prog + ' -sW ' + cmd_quote(afile) + ' | grep __memcpy_to_buf || true'
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if output:
        verbose(afile + ' contains __memcpy_to_buf symbol, so it is OSC library file', LEVEL_1)
        return True
    cmd = 'strings ' + cmd_quote(afile) + ' || true'
    strings_output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    oscstr_list = ['DATACORRUPTION-DATAINCONSISTENCY: ',
               #'DATACORRUPTION-DATAINCONSISTENCY: -Traceback= %s',
               #'DATACORRUPTION-DATAINCONSISTENCY: Attempt to %s %u bytes should have been %u bytes',
               '__memcpy_to_buf', 'osc_get_backtrace', 'osc_bt2str_offset']
    for s in oscstr_list:
        if s in strings_output:
            verbose(afile + ' contains string ' + s + ', so it is OSC library file', LEVEL_1)
            return True
    return False


def linked_with_osc(afile, libosc_str="libosc\.so"):
    """
    Check if an ELF file is linked with libosc.so.
    """
    #cmd = "readelf -d " + cmd_quote(afile) + ' | grep NEEDED | grep "libosc\.so" || true '
    cmd = g_readelf_prog + ' -d ' + cmd_quote(afile) + ' | grep NEEDED | grep "' + libosc_str + '" || true '
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if output:
        verbose(output, LEVEL_1)
        return True
    #libosc_filename = ''.join(libosc_str.split("\\"))
    #if libosc_filename in afile:    # libosc itself is special case
        #return True
    return False


def linked_with_4arg(afile):
    """
    Check if an ELF file is linked with lib4arg.so.
    """
    cmd = g_readelf_prog + ' -d ' + cmd_quote(afile) + ' | grep NEEDED | grep "lib4arg\.so" || true '
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if output:
        verbose(output, LEVEL_1)
        return True
    return False


def linked_with_safec(afile):
    """
    Check if an ELF file is linked with libsafelibc.so.
    """
    #cmd = 'readelf -d ' + afile + ' | grep NEEDED | grep "libsafelibc\.so" || true '
    cmd = g_readelf_prog + ' -d ' + cmd_quote(afile) + " | grep NEEDED | grep safec || true "
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if output:
        verbose(output.rstrip(), LEVEL_1)
        return True
    return False


def is_libciscoosc_library(afile):
    """
    Check if a file is indeed libciscoosc.so file by checking strings.
    """
    cmd = "strings " + cmd_quote(afile) + " | grep DATACORRUPTION-DATAINCONSISTENCY: || true "
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    cmd = "strings " + cmd_quote(afile) + " | grep osc_ || true "
    output2 = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    if output and output2:
        verbose(output.rstrip(), LEVEL_1)
        verbose(output2.rstrip(), LEVEL_1)
        return True
    return False


def has_osc_library(alist, rdict):
    """
    Check if there is OSC library file in a list of file.
    """
    for afile in alist:
        if is_osc_lib_file(afile):
            rdict["libosc_lib_version"] = get_osc_lib_version(afile)
            return True
    return False


def does_osc_library_exist(builddir, rdict):
    """
    Checks if the OSC library exists in a workspace.

    :param builddir: Build dir of the workspace
    :param rdict: result dictionary to save the list of libosc files
    """
    library_presence = True
    libosc_str = "libosc\.so"
    files = find_specific_file(builddir, "libosc.so*")
    if not files or not has_osc_library(files, rdict):
        files2 = find_specific_file(builddir, "libciscoosc.so*")
        if not files2 or not has_osc_library(files2, rdict):
            files3 = find_specific_file(builddir, "libopenosc.so*")
            if not files3 or not has_osc_library(files3, rdict):
                library_presence = False
                print ("OSC library is NOT present!")
            else:
                print ("OSC library is present.")
                rdict["libosc_files"] = files3
                rdict["libosc_files_num"] = len(files3)
                libosc_str = "libopenosc\.so"
        else:
            print ("OSC library is present.")
            rdict["libosc_files"] = files2
            rdict["libosc_files_num"] = len(files2)
            libosc_str = "libciscoosc\.so"
    else:
        print ("OSC library is present.")
        rdict["libosc_files"] = files
        rdict["libosc_files_num"] = len(files)
    rdict["library_presence"] = library_presence
    return (library_presence, libosc_str)


def check_bosc(builddir):
    """
    Checks BOSC conformance for all binary files in the build dir.
    It prints a summary of the check result.

    :param builddir: Build dir of the workspace
    """
    print_start_time()
    print ("")
    print ("##### Now performing BOSC Task0: library presence.")
    print ("Build dir is: " + builddir)
    len_prefix = len(os.path.abspath(builddir).rstrip('/')) + 1
    subdict = dict()
    checktype = "BOSC"
    if checktype in result_dict:
        subdict = result_dict[checktype]
    else:
        result_dict[checktype] = subdict
    subdict[builddir] = dict()
    rdict = subdict[builddir]
    failed_list = "failed_list"
    total_file_count = "total_file_count"
    total_dir_count = "total_dir_count"
    (library_presence, libosc_str) = does_osc_library_exist(builddir, rdict)
    if not library_presence:
        files = find_specific_file(builddir, "libosc.dll")
        if files:
            rdict["library_presence"] = True
            print ("libosc.dll exists, this should be asr9k QNX image, skipping linkage check.")
            rdict["pass_percent"] = 0
            print_end_time()
            return 0
    if not library_presence and skip_linkage_check_if_lib_not_present:
        print ("Skipping file-linkage check since the BOSC library does not exist.")
        pass_percent = 0
        rdict["pass_percent"] = pass_percent
        print_end_time()
        return pass_percent
    print ("")
    print ("##### Now performing BOSC Task1: binary file check.")
    print ("#####  - Must linked with 'osc'")
    print ("Build dir is: " + builddir)
    elf_file_count = 0
    link_osc_count = 0
    nonlink_osc_count = 0
    link_safec_count = 0
    nonlink_safec_count = 0
    symfile_count = 0
    other_count = 0
    non_elf_count = 0
    files = []
    if args.scan_all_elf_files:
        files = find_all_elf_files(builddir)
    else:
        files = find_all_elf_soexe_files(builddir)
    rdict[total_file_count] = len(files)
    rdict[total_dir_count] = len(get_total_dir_list(files))
    rdict[failed_list] = []
    for line in files:
        filecmd = "file " + cmd_quote(line) + " || true"
        output = subprocess.check_output(filecmd, shell=True, universal_newlines=True)
        output = output.rstrip()
        outputs = output.split(": ")[1]
        if not "ELF" in outputs:
            non_elf_count += 1
            continue
        if ("executable" in outputs and not "script" in outputs) or "shared object" in outputs:
            elf_file_count += 1
            if linked_with_osc(line, libosc_str):
                verbose("This file DOES link with libosc.so " + output, LEVEL_1)
                link_osc_count += 1
            else:
                verbose("This file does NOT link with libosc.so " + output, LEVEL_0)
                nonlink_osc_count += 1
                rdict[failed_list].append(output[len_prefix:])
        elif "symbolic link to" in output:
            verbose(output, LEVEL_2)
            symfile_count += 1
        else:
            verbose(output, LEVEL_1)
            other_count += 1
    print ("Results for OSC (Object Size Check):")
    print (HDR3)
    print ("#ELF files:              " + str(elf_file_count))
    print ("#linked with OSC:        " + str(link_osc_count))
    print ("#not linked with OSC:    " + str(nonlink_osc_count))
    print ("#symbolic link:          " + str(symfile_count))
    print ("#other:                  " + str(other_count))

    total_count = elf_file_count + symfile_count + other_count
    print ("#total executable files: " + str(total_count))
    total_count = elf_file_count
    pass_percent = DEFAULT_PASS_PERCENT
    if total_count > 0:
        pass_percent = 100 * link_osc_count / total_count
    print ("pass percent: " + str(pass_percent) + "%")
    print (HDR3)
    rdict["other_count"] = other_count
    rdict["link_osc_count"] = link_osc_count
    rdict["nonlink_osc_count"] = nonlink_osc_count
    rdict["total_count"] = total_count
    rdict["pass_percent"] = pass_percent
    if args.verbose > LEVEL_1:
        print ("Here is the " + checktype + " check result in json format:")
        #print (result_dict[checktype])
        print (json.dumps(result_dict[checktype], indent=4, sort_keys=True))
    rdict["verbosity"] = args.verbose
    if not args.verbose > LEVEL_0:  # omit the failed_list if not verbose
        del rdict[failed_list]
    print_end_time()
    return pass_percent


def watermarkpc_check_dirs(builddirs):
    """
    :param builddirs:
    """
    score = 0
    for builddir in builddirs:
        score += check_watermarkpc(builddir)
    if builddirs:
        score = score / len(builddirs)
    else:
        score = 100
    return score


def bosc_check_dirs(builddirs):
    """
    :param builddirs:
    """
    bosc_score = 100
    score = 0
    for builddir in builddirs:
            score += check_bosc(builddir)
    if builddirs:
        bosc_score = score/len(builddirs)
    return bosc_score


def magic_check_dirs(builddirs):
    """
    :param builddirs:
    """
    for builddir in builddirs:
        check_magic(builddir)


def get_shell_cmd_output(cmd):
    """
    Returns the output of the shell command "cmd".

    :param cmd: the shell command to execute
    """
    #print (cmd)
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)
    return output


def reorder_osc_functions(funcs):
    """ Reorder OSC functions based on libc/safec/other category
    """
    result = []
    libc_funcs = []
    safec_funcs = []
    other_funcs = []
    for func in funcs:
        if func == 'FILEMAGICS' or func == 'SUM_STATS':
            continue
        if func in g_libc_functions:
            libc_funcs.append(func)
        elif func in g_safec_functions:
            safec_funcs.append(func)
        else:
            other_funcs.append(func)
    libc_funcs.sort()
    safec_funcs.sort()
    other_funcs.sort()
    result.extend(libc_funcs)
    result.extend(safec_funcs)
    result.extend(other_funcs)
    return result


def calc_magic_output(row_out, function=""):
    """Helper function to convert certain columns to string percentages
    """
    # Successful mappings
    if row_out[4] != 0:
        row_out[0] = round(float(row_out[0]) * 100 / row_out[4], 2)
        row_out[1] = round(float(row_out[1]) * 100 / row_out[4], 2)
        row_out[2] = round(float(row_out[2]) * 100 / row_out[4], 2)
        row_out[3] = round(float(row_out[3]) * 100 / row_out[4], 2)
    row_out = [str(i) for i in row_out]
    for i in [0, 1, 2, 3]:
        row_out[i] += " %"
    return row_out


def print_row(row_formats, headings):
    """Helper function to print headings of various size
    """
    output = ''
    for row_format, h in zip(row_formats, headings):
        output += row_format.format(h)
    return output


def output_osc_stats_summary(json_data, main_directory, section, directory, osc_stats_type):
    '''
    Output some summary tables for OSC magic word stats.
    '''
    if True:
            #section = 'MAGIC'
            headings11 = [' Function', ' |     Known Good', ' | Known Overflow',
                          ' | Runtime Protection', ' | Unknown dst size',
                          ' | OSC Decisions', ' | OSC Processing',
                          ' |    Total']
            headings12 = ['',          ' | at Compilation', ' | at Compilation',
                          ' |    (OSC Remapping)', ' |   at Compilation',
                          ' |              ', ' |        Failure',
                          ' | Mappings']
            headings21 = ['OSC Header', ' | OSC Header Included,    ',
                          ' | Total files         ', ' | Total Files']
            headings22 = ['not Included', ' | but Unsuccessful Mapping',
                          ' | Including OSC Header', ' |            ']
            headings31 = ['Index', ' | nomap_func', ' | no_optimize', ' | no_inline',
                          ' | fortify', ' | strict_ansi', ' | nomap_h', ' | header', ' | filepath']
            if True:
                # Print per-function summary table
                # Generate formatting string based on max header length
                row_formats = []
                for h1, h2 in zip(headings11, headings12):
                    if len(h1) > len(h2):
                        row_formats.append("{:>" + str(len(h1)) + "}")
                    else:
                        row_formats.append("{:>" + str(len(h2)) + "}")

                print ("Coverage summary for per-function calls")
                print ("---------------------------------------\n\n")
                print ("**************************************************" \
                      "*********************")
                if osc_stats_type == magic_types_for_stats_src:
                    print ("*** Source Over-read Table ***")
                else:
                    print ("*** Destination Overflow Table ***")
                #print ("** Column 1 is percentages of BOTH successful and " \
                #      "unsuccessful mappings")
                print ("** Columns 2-5 are percentages of ONLY successful " \
                      "mappings")
                print ("**************************************************" \
                        "*********************\n")
                print (print_row(row_formats, headings11))
                print (print_row(row_formats, headings12))
                
                magic_totals = [0 for i in headings11[1:]]

                # reorder function print order in the output table
                new_func_list = reorder_osc_functions(json_data[section][directory])
                for function in new_func_list:
                    # Only handle those functions that implement source overread feature.
                    if osc_stats_type == magic_types_for_stats_src:
                        if function not in g_src_overread_functions:
                            continue

                    # Some list or something
                    row_output = [function]
                  
                    # Some stats are already calculated, while others are not
                    #osc_stats = magic_types_for_stats    ### do not count safec magic5 and magic6
                    osc_stats = dict()
                    for stat in osc_stats_type:
                        osc_stats[stat] = 0

                    # Search binaries for matching paths
                    for binary_path in json_data[section][directory][function] \
                            ["elf_file_stats"]:
                        if main_directory not in binary_path:
                            continue

                        for stat in osc_stats:
                            magictype_list = osc_stats_type[stat]
                            #print magictype_list
                            for magictype in magictype_list:
                                # most functions do not have MAGIC7-MAGICb, this check is needed
                                if magictype not in reverse_all_magics[function]:
                                    continue
                                # Lookup MAGIC word, and associated value
                                magic_word = reverse_all_magics[function][magictype]
                                magic_value = json_data[section][directory] \
                                        [function]["elf_file_stats"] \
                                        [binary_path][magic_word]
                                # Add value to total
                                osc_stats[stat] += magic_value

                    row_stats = [osc_stats['COLUMN_1'],
                                 osc_stats['COLUMN_2'],
                                 osc_stats['COLUMN_3'],
                                 osc_stats['COLUMN_4'],
                                 osc_stats['COLUMN_0']]
                    row_stats.insert(4, row_stats[0] + row_stats[1]
                                        + row_stats[2] + row_stats[3])
                    row_stats.append(row_stats[4] + row_stats[5])
            
                    # Add to total stats
                    magic_totals = [sum(i) for i in zip(magic_totals, row_stats)]

                    # Generate output
                    row_output.extend(calc_magic_output(row_stats, function))
                    print (print_row(row_formats, row_output))
            
                # Generate output
                magic_totals = calc_magic_output(magic_totals)
                print ("-----------------------------------------------------" \
                      "-----------------------------------------------------" \
                      "---------------------")
                print (print_row(row_formats, ["TOTAL"] + magic_totals))
                print (HDR1)


def output_summary(json_data, main_directory):
    '''
    Output some summary tables for OSC stats.
    '''
    for section in json_data:
        # Whitelist
        if section not in {"MAGIC"}:
            continue

        print (section + ':')
        # MAGIC
        if section == "MAGIC":
            headings11 = [' Function', ' |     Known Good', ' | Known Overflow',
                          ' | Runtime Protection', ' | Unknown dst size',
                          ' | OSC Decisions', ' | OSC Processing',
                          ' |    Total']
            headings12 = ['',          ' | at Compilation', ' | at Compilation',
                          ' |    (OSC Remapping)', ' |   at Compilation',
                          ' |              ', ' |        Failure',
                          ' | Mappings']
            headings21 = ['OSC Header', ' | OSC Header Included,    ',
                          ' | Total files         ', ' | Total Files']
            headings22 = ['not Included', ' | but Unsuccessful Mapping',
                          ' | Including OSC Header', ' |            ']
            headings31 = ['Index', ' | nomap_func', ' | no_optimize', ' | no_inline',
                          ' | fortify', ' | strict_ansi', ' | nomap_h', ' | header', ' | filepath']
        else:
            headings11 = headings12 = ['']


        for directory in json_data[section]:
            # MAGIC Section
            if section == "MAGIC":
                if main_directory is None:
                    main_directory = directory.lstrip('.')
                #print ("Directory: " + main_directory + "\n")
                print ("Directory: " + directory + "\n")

                # print the nomap_list stats table
                print ("\nList of files that contain unsuccessful mappings or unprotected OSC function calls:")
                print ("-----------------------------------\n\n")
                print ("*" * 100)
                print ("** These statistics are number of object files in shared object/" \
                      "binary, except nomap_func, which is number of functions.")
                print ("**  nomap_func => # of unprotected function calls")
                print ("**  no_optimize => # of objects that are compiled with -O0")
                print ("**  no_inline => # of objects that are compiled with inline disabled")
                print ("**  fortify => # of objects that are compiled with _FORTIFY_SOURCE")
                print ("**  strict_ansi => # of objects that are compiled with -std=c89,-gnu99, etc")
                print ("**  nomap_h => # of objects that are compiled with -include osc_header.h," \
                      " however OSC is disabled due to incompatible CFLAGS")
                print ("**  header => # of objects that are compiled with -include osc_header.h")
                print ("*" * 100 + "\n")
                row_formats = []
                for h1 in headings31:
                        row_formats.append("{:>" + str(len(h1)) + "}")
                print (print_row(row_formats, headings31))
                filefunc = "FILEMAGICS"
                filemagics = reverse_all_magics[filefunc]
                stats_db = json_data[section][directory][filefunc]["all_elf_file_stats"]
                idx = 0
                magic_totals = [0, 0, 0, 0, 0, 0, 0]
                for binary_path in json_data[section][directory][filefunc]["osc_file_nomap_list"]:
                    stats = stats_db[binary_path]
                    idx += 1
                    row_output = [str(idx)]
                    nomap_func_count = get_total_unsuccessful_mappings_for_stats(stats)
                    row_stats = [nomap_func_count,
                                 stats[filemagics['MAGIC_OSC_NOMAP_H_REASON_NOOPTIMIZE']],
                                 stats[filemagics['MAGIC_OSC_NOMAP_H_REASON_NOINLINE']],
                                 stats[filemagics['MAGIC_OSC_NOMAP_H_REASON_FORTIFY_SOURCE']],
                                 stats[filemagics['MAGIC_OSC_NOMAP_H_REASON_STRICT_ANSI']],
                                 stats[filemagics['MAGIC_OSC_NOMAP_H_INCLUDED']],
                                 stats[filemagics['MAGIC_OSC_HEADER_INCLUDED']]]
                    for i in range(len(magic_totals)):
                        magic_totals[i] += row_stats[i]
                    # Generate output
                    row_output.extend([str(i) for i in row_stats])
                    row_output.append("   " + binary_path)
                    print (print_row(row_formats, row_output))
                    #print (binary_path)
                row_output = ["TOTAL"]
                row_output.extend([str(i) for i in magic_totals])
                row_output.append("   ")
                print (print_row(row_formats, row_output))
                print (print_row(row_formats, headings31))
                print ("---------------------------------------\n\n")


                output_osc_stats_summary(json_data, main_directory, section, directory, magic_types_for_stats)
                output_osc_stats_summary(json_data, main_directory, section, directory, magic_types_for_stats_src)

                # Overall summary table
                print ("\nCoverage for all files (Ignores -Y)")
                print ("-----------------------------------\n\n")
                print ("************************************************" \
                      "************************************************" \
                      "*********")
                print ("** These statistics are per overall shared object/" \
                      "binary, *not* each individual object file within " \
                      "those,\n** because we aren't able to count them unless " \
                      "they include the OSC header.")
                print ("** Files are counted as having a property if > 0" \
                      " files within it have that property.")
                print ("************************************************" \
                      "*************************************************" \
                      "********\n")

                row_formats = []
                for h1, h2 in zip(headings21, headings22):
                    if len(h1) > len(h2):
                        row_formats.append("{:>" + str(len(h1)) + "}")
                    else:
                        row_formats.append("{:>" + str(len(h2)) + "}")
                print (print_row(row_formats, headings21))
                print (print_row(row_formats, headings22))

                filefunc = "FILEMAGICS"
                # Total files
                binaries = json_data[section][directory][filefunc] \
                    ["osc_file_total_count"]
                # Files w/o ANY file including OSC header
                binaries_noheader = json_data[section][directory][filefunc] \
                    ["osc_file_noheader_list_size"]
                # Files where > 0 files have an an unsuccessful mapping
                binaries_nomap = json_data[section][directory][filefunc] \
                    ["osc_file_nomap_list_size"]
                # Files that have > 0 files including OSC header,
                #  i.e. successful AND unsuccessful mapped files
                binaries_header = binaries - binaries_noheader
                
                noheader_percent = 0
                nomap_percent = 0
                if binaries > 0:
                    noheader_percent = round(float(binaries_noheader) * 100 /
                                             binaries, 2)
                if binaries_header > 0:
                    nomap_percent = round(float(binaries_nomap) * 100 /
                                           binaries_header, 2)
                
                row_stats = [noheader_percent, nomap_percent, binaries_header,
                    binaries]
                row_stats = [str(i) for i in row_stats]
                for i in [0, 1]:
                    row_stats[i] += " %"
                
                print (print_row(row_formats, row_stats))
            else:
                print ("Unsupported section: " + section)
            
            print (HDR4)

############################################################
#### OSC-METRIC feature, checking DWARF debug info ####
############################################################

def get_osc_metric_info_for_file(afile):
    '''
    Find out the OSC-METRIC type and info for a file.
    '''
    pc_list = get_osc_metric_pclines_of_afile(afile)
    if pc_list:
        return ("LOC", pc_list)
    (magic_list, text_section_info) = scan_text_section_from_file(afile, g_all_magics)
    if magic_list:
        return ("WATERMARK", magic_list)
    return ("NO_METRIC", [])


def get_dwarf_decoded_line_info(afile):
    '''
    Get DWARF .debug_line decoded info from an ELF file.
    It simply runs "readelf -wL afile' and return the lines with PC address.
    '''
    cmd = g_readelf_prog + ' -wL ' + cmd_quote(afile) + ' | grep "     0x" || true'
    #print(cmd)
    output = get_shell_cmd_output(cmd)
    if output:
        return output.splitlines()
    return []


def parse_dwarf_decoded_lines(lines):
    '''
    Parse DWARF .debug_line decoded info and return (PC, Line#) list
    '''
    ret = []
    for line in lines:
        tokens = line.split()
        if len(tokens) != 3:
            continue
        pc = tokens[2]
        srcline = tokens[1]
        #print( (pc, srcline) )
        ret.append( (pc, srcline) )
    return ret


def parse_dwarf_debug_lines_of_afile(afile):
    '''
    Parse DWARF .debug_lines and return a list of all .loc (PC, line#).
    '''
    lines = get_dwarf_decoded_line_info(afile)
    ret = parse_dwarf_decoded_lines(lines)
    #print(len(ret))
    return ret


def get_osc_metric_lines_of_afile(afile):
    '''
    Get a list of LOCs with FUNC-MAGICs only.
    The first FUNC-magic is 8388864 or 0x00800100 in hexadecimal.
    '''
    pc_list = parse_dwarf_debug_lines_of_afile(afile)
    return [entry[1] for entry in pc_list if int(entry[1]) >= 0x00800100]


def get_osc_metric_pclines_of_afile(afile):
    '''
    Get a list of (PC, LOC)s with both CONSTANT-ENCODING-MAGICS and FUNC-MAGICs.
    The first .loc magic is 8388592 or 0x007ffff0 in hexadecimal.
    '''
    pc_list = parse_dwarf_debug_lines_of_afile(afile)
    return [entry for entry in pc_list if int(entry[1]) >= 0x007ffff0]


# A constant is encoded with the below format:
# It starts with one line of the magics in g_loc_len_start_maps,
# then multiple lines of in 8388608-8388623 range,
# finally it ends with a line of LOC_LEN_END = 8388607.

# 8388607 is 0x007fffff in hexadecimal.
LOC_LEN_END = '8388607'

# 8388592 = 0x007ffff0
# 8388603 = 0x007ffffb
g_loc_len_start_maps = {
'8388592' : (1, 1),
'8388593' : (1, 2),
'8388594' : (1, 4),
'8388595' : (2, 1),
'8388596' : (2, 2),
'8388597' : (2, 4),
'8388598' : (4, 1),
'8388599' : (4, 2),
'8388600' : (4, 4),
'8388601' : (8, 1),
'8388602' : (8, 2),
'8388603' : (8, 4),
}

def get_loc_dst_len_objsize(stack):
    '''
    Get encoded (dst_size, src_size, copylen) from the .loc constant-encoding list.

    :param stack: a list of .loc srcline encoding one or more constant values.
    :returns a string of comma-separated constant values.
    '''
    values = []
    value = 0
    shift = 0
    nbytes, mbits = 8, 4
    mask = (1 << mbits) - 1
    for line in stack:
        if line == LOC_LEN_END:
            # we always encode a constant as 64-bit signed integer
            if value > 0x7FFFFFFFFFFFFFFF:
                value -= 0x10000000000000000
            values.append(str(value))
            continue
        elif line in g_loc_len_start_maps:
            (nbytes, mbits) = g_loc_len_start_maps[line]
            mask = (1 << mbits) - 1
            value = 0
            shift = 0
            continue
        value += (int(line) & mask) << shift
        shift += mbits
    #print(values)
    return ','.join(values)


def scan_debug_lines_from_file(afile, magics):
    """
    Scan .debug_lines ELF section for PCs/source code lines of matching magics.

    :param afile: a binary file to scan magic words and retrieve srcline info
    :param magics: the predefined magic words for all OSC functions
    :returns the list of magic words and its srcline info
    """
    verbose("Scanning DWARF debug lines info from " + afile, LEVEL_1)
    pc_list = parse_dwarf_debug_lines_of_afile(afile)
    magic_list = []
    prev_pc = 0
    stack = []
    for pc, line in pc_list:
        #print( (pc, line) )
        if stack and pc != prev_pc:
            # a new PC address is found, and a non-empty stack with encoded constant values.
            #print("pc: " + prev_pc + " stack: " + str(stack) + " d: " + str(d))
            d['dstsize'] = get_loc_dst_len_objsize(stack)
            stack = []
        if int(line) < 0x00700000:
            #print("Line# not in LOC magic range, skip it.")
            continue
        match = match_magic_word(line, magics)
        if not match:
            int_line = int(line)
            if int_line >= 0x007fff00 and int_line < 0x00800100 and pc == prev_pc:
                stack.append(line)
            continue
        hex_pc = pc
        (cmd, output, srcfunc, srcline) = get_addr2line_info(afile, hex_pc)
        d = dict()
        d['PC'] = hex_pc
        d['magic'] = line
        d['oscfunc'] = match[0]
        d['caseno'] = match[1]
        d['srcfunc'] = srcfunc
        d['srcline'] = srcline
        d['addr2line_cmd'] = cmd
        d['addr2line_output'] = output
        d['offset'] = 0
        magic_list.append(d)
        prev_pc = pc
    return magic_list


############################################################
#### End of OSC-METRIC feature, checking debug info ####
############################################################


def main():
    # parse command line options first
    rtd_parse_options()

    # Print stats summary
    if args.summary:
        # Load file
        data = load_json_db(args.summary)
        if builddirs:  ## this is like a hack
            print ("For build workspace, we will use the supplied build directory " + str(builddirs))
        if "WATERMARKPC" in data:
            waterpc_dict = data["WATERMARKPC"]
            water_file_dict = waterpc_dict[waterpc_dict.keys()[0]]["watermarkpc_files"]
            print_watermarkpc_summary_table(water_file_dict, builddirs)
        output_summary(data, args.summary_dir)
        return

    # Print time
    print_start_time()

    magic_type = "dwarf_loc"
    if args.magictype:
        magic_type = args.magictype.lower()
    initialize_all_magics(magic_type)

    # Check build dirs for all binary files
    total_score = 0
    if builddirs:
        print ("Checking the provided build dirs, total num: " +
               str(len(builddirs)))
        print ("")
        num_checks = 0
        # Also perform the OSC check.
        if args.bosc:
            total_score += bosc_check_dirs(builddirs)
            num_checks += 1
        # Also perform the OSC-magic check.
        if args.magiccheck:
            magic_check_dirs(builddirs)
        # Also perform the WATERMARK-PC check.
        if args.watermarkpc:
            watermarkpc_check_dirs(builddirs)
        if num_checks > 0:
            total_score = total_score / num_checks
        print ("total security score is: " + str(total_score))
        #result_dict["security_score"] = total_score
        save_json_db(RESULT_JSON_FILE, result_dict, 4)
        if args.verbose > LEVEL_1:
            print ("Here is the final check result in json format:")
            print (json.dumps(result_dict, indent=4, sort_keys=True))
            #print (result_dict)
        print_end_time()

    # Print summary
    output_summary(result_dict, args.summary_dir)

    # OK. it is done.


if __name__ == '__main__':
    main()
