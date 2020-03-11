/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_SAFEC_NOMAP_METRIC_H__
#define __OPENOSC_SAFEC_NOMAP_METRIC_H__

#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#define MEMCMP_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x01, 0x00\n" OSC_JUMPLABEL
#define MEMCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x02, 0x00\n" OSC_JUMPLABEL
#define STRCAT_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x03, 0x00\n" OSC_JUMPLABEL
#define STRCMP_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x04, 0x00\n" OSC_JUMPLABEL
#define STRCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x05, 0x00\n" OSC_JUMPLABEL
#define STRNCAT_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x06, 0x00\n" OSC_JUMPLABEL
#define STRNCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x07, 0x00\n" OSC_JUMPLABEL
#define STRNLEN_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x08, 0x00\n" OSC_JUMPLABEL
#define STRSTR_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x09, 0x00\n" OSC_JUMPLABEL

#define MEMCMP_S_NOMAP_CASE         ({__asm__(MEMCMP_S_NOMAP_MAGIC);}),
#define MEMCPY_S_NOMAP_CASE         ({__asm__(MEMCPY_S_NOMAP_MAGIC);}),
#define STRCAT_S_NOMAP_CASE         ({__asm__(STRCAT_S_NOMAP_MAGIC);}),
#define STRCMP_S_NOMAP_CASE         ({__asm__(STRCMP_S_NOMAP_MAGIC);}),
#define STRCPY_S_NOMAP_CASE         ({__asm__(STRCPY_S_NOMAP_MAGIC);}),
#define STRNCAT_S_NOMAP_CASE        ({__asm__(STRNCAT_S_NOMAP_MAGIC);}),
#define STRNCPY_S_NOMAP_CASE        ({__asm__(STRNCPY_S_NOMAP_MAGIC);}),
#define STRNLEN_S_NOMAP_CASE        ({__asm__(STRNLEN_S_NOMAP_MAGIC);}),
#define STRSTR_S_NOMAP_CASE         ({__asm__(STRSTR_S_NOMAP_MAGIC);}),

#else   /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define MEMCMP_S_NOMAP_MAGIC                 0x0001d1434947414d
#define MEMCPY_S_NOMAP_MAGIC                 0x0002d1434947414d
#define STRCAT_S_NOMAP_MAGIC                 0x0003d1434947414d
#define STRCMP_S_NOMAP_MAGIC                 0x0004d1434947414d
#define STRCPY_S_NOMAP_MAGIC                 0x0005d1434947414d
#define STRNCAT_S_NOMAP_MAGIC                0x0006d1434947414d
#define STRNCPY_S_NOMAP_MAGIC                0x0007d1434947414d
#define STRNLEN_S_NOMAP_MAGIC                0x0008d1434947414d
#define STRSTR_S_NOMAP_MAGIC                 0x0009d1434947414d

#else

#define MEMCMP_S_NOMAP_MAGIC                 0x4d41474943d10100
#define MEMCPY_S_NOMAP_MAGIC                 0x4d41474943d10200
#define STRCAT_S_NOMAP_MAGIC                 0x4d41474943d10300
#define STRCMP_S_NOMAP_MAGIC                 0x4d41474943d10400
#define STRCPY_S_NOMAP_MAGIC                 0x4d41474943d10500
#define STRNCAT_S_NOMAP_MAGIC                0x4d41474943d10600
#define STRNCPY_S_NOMAP_MAGIC                0x4d41474943d10700
#define STRNLEN_S_NOMAP_MAGIC                0x4d41474943d10800
#define STRSTR_S_NOMAP_MAGIC                 0x4d41474943d10900

#endif

#define MEMCMP_S_NOMAP_CASE         rtd_osc_nomap_int = MEMCMP_S_NOMAP_MAGIC,
#define MEMCPY_S_NOMAP_CASE        rtd_osc_nomap_int = MEMCPY_S_NOMAP_MAGIC,
#define STRCAT_S_NOMAP_CASE         rtd_osc_nomap_int = STRCAT_S_NOMAP_MAGIC,
#define STRCMP_S_NOMAP_CASE          rtd_osc_nomap_int = STRCMP_S_NOMAP_MAGIC,
#define STRCPY_S_NOMAP_CASE          rtd_osc_nomap_int = STRCPY_S_NOMAP_MAGIC,
#define STRNCAT_S_NOMAP_CASE         rtd_osc_nomap_int = STRNCAT_S_NOMAP_MAGIC,
#define STRNCPY_S_NOMAP_CASE        rtd_osc_nomap_int = STRNCPY_S_NOMAP_MAGIC,
#define STRNLEN_S_NOMAP_CASE         rtd_osc_nomap_int = STRNLEN_S_NOMAP_MAGIC,
#define STRSTR_S_NOMAP_CASE        rtd_osc_nomap_int = STRSTR_S_NOMAP_MAGIC,

#endif   /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

#else

#define MEMCMP_S_NOMAP_CASE
#define MEMCPY_S_NOMAP_CASE
#define STRCAT_S_NOMAP_CASE
#define STRCMP_S_NOMAP_CASE
#define STRCPY_S_NOMAP_CASE
#define STRNCAT_S_NOMAP_CASE
#define STRNCPY_S_NOMAP_CASE
#define STRNLEN_S_NOMAP_CASE
#define STRSTR_S_NOMAP_CASE

#endif   /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /*__OPENOSC_SAFEC_NOMAP_METRIC_H__ */
