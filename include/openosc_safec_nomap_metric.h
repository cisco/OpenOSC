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

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD)

#define MEMCMP_S_NOMAP_MAGIC            ".loc 1 8390032"
#define MEMCPY_S_NOMAP_MAGIC            ".loc 1 8390048"
#define STRCAT_S_NOMAP_MAGIC            ".loc 1 8390064"
#define STRCMP_S_NOMAP_MAGIC            ".loc 1 8390080"
#define STRCPY_S_NOMAP_MAGIC            ".loc 1 8390096"
#define STRNCAT_S_NOMAP_MAGIC           ".loc 1 8390112"
#define STRNCPY_S_NOMAP_MAGIC           ".loc 1 8390128"
#define STRNLEN_S_NOMAP_MAGIC           ".loc 1 8390144"
#define STRSTR_S_NOMAP_MAGIC            ".loc 1 8390160"

#elif (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#define MEMCMP_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x01, 0x00\n" OSC_JUMPLABEL
#define MEMCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x02, 0x00\n" OSC_JUMPLABEL
#define STRCAT_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x03, 0x00\n" OSC_JUMPLABEL
#define STRCMP_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x04, 0x00\n" OSC_JUMPLABEL
#define STRCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x05, 0x00\n" OSC_JUMPLABEL
#define STRNCAT_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x06, 0x00\n" OSC_JUMPLABEL
#define STRNCPY_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x07, 0x00\n" OSC_JUMPLABEL
#define STRNLEN_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x08, 0x00\n" OSC_JUMPLABEL
#define STRSTR_S_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x09, 0x00\n" OSC_JUMPLABEL

#endif

#define MEMCMP_S_NOMAP_CASE         ({__asm__(MEMCMP_S_NOMAP_MAGIC);}),
#define MEMCPY_S_NOMAP_CASE         ({__asm__(MEMCPY_S_NOMAP_MAGIC);}),
#define STRCAT_S_NOMAP_CASE         ({__asm__(STRCAT_S_NOMAP_MAGIC);}),
#define STRCMP_S_NOMAP_CASE         ({__asm__(STRCMP_S_NOMAP_MAGIC);}),
#define STRCPY_S_NOMAP_CASE         ({__asm__(STRCPY_S_NOMAP_MAGIC);}),
#define STRNCAT_S_NOMAP_CASE        ({__asm__(STRNCAT_S_NOMAP_MAGIC);}),
#define STRNCPY_S_NOMAP_CASE        ({__asm__(STRNCPY_S_NOMAP_MAGIC);}),
#define STRNLEN_S_NOMAP_CASE        ({__asm__(STRNLEN_S_NOMAP_MAGIC);}),
#define STRSTR_S_NOMAP_CASE         ({__asm__(STRSTR_S_NOMAP_MAGIC);}),

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
