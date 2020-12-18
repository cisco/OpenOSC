/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_NOMAP_METRIC_H__
#define __OPENOSC_NOMAP_METRIC_H__

#ifdef OPENOSC_HEADER_METRIC_FEATURE_ENABLED

/* always insert a magic word if osc_nomap.h is included */
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_INCLUDED 0x80818d8e80818d8f
#else
#define MAGIC_OSC_NOMAP_H_INCLUDED 0x8f8d81808e8d8180
#endif
long long int __attribute__((weak)) rtd_osc_nomap_h_included_int = MAGIC_OSC_NOMAP_H_INCLUDED;

#if !defined  __OPTIMIZE__
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d01
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x018d81808e8d8180
#endif
#elif defined __NO_INLINE__
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d02
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x028d81808e8d8180
#endif
#elif defined _FORTIFY_SOURCE
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d03
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x038d81808e8d8180
#endif
#elif defined OPENOSC_METRIC_ONLY_MODE
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d06
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x068d81808e8d8180
#endif
#elif defined OSC_ASM
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d04
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x048d81808e8d8180
#endif
#elif defined __STRICT_ANSI__
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_NOMAP_H_REASON 0x80818d8e80818d05
#else
#define MAGIC_OSC_NOMAP_H_REASON 0x058d81808e8d8180
#endif
#endif   /* !defined  __OPTIMIZE__ */
/* identify the specific reason of including osc_nomap.h */
long long int __attribute__((weak)) rtd_osc_nomap_h_reason_int = MAGIC_OSC_NOMAP_H_REASON;

#endif  /* OPENOSC_HEADER_METRIC_FEATURE_ENABLED */

#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD)

#define MEMCPY_NOMAP_MAGIC              ".loc 1 8388864"
#define MEMMOVE_NOMAP_MAGIC             ".loc 1 8388880"
#define MEMSET_NOMAP_MAGIC              ".loc 1 8388896"
#define BCOPY_NOMAP_MAGIC               ".loc 1 8388912"
#define BZERO_NOMAP_MAGIC               ".loc 1 8388928"
#define STRCPY_NOMAP_MAGIC              ".loc 1 8388944"
#define STRNCPY_NOMAP_MAGIC             ".loc 1 8388960"
#define STRCAT_NOMAP_MAGIC              ".loc 1 8388976"
#define STRNCAT_NOMAP_MAGIC             ".loc 1 8388992"
#define STRNLEN_NOMAP_MAGIC             ".loc 1 8389008"
#define VSNPRINTF_NOMAP_MAGIC           ".loc 1 8389024"

#elif (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#define MEMCPY_NOMAP_MAGIC  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x00\n" OSC_JUMPLABEL
#define MEMMOVE_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x00\n" OSC_JUMPLABEL
#define MEMSET_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x11, 0x00\n" OSC_JUMPLABEL
#define BCOPY_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x00\n" OSC_JUMPLABEL
#define BZERO_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x33, 0x00\n" OSC_JUMPLABEL
#define STRCPY_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x44, 0x00\n" OSC_JUMPLABEL
#define STRNCPY_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x55, 0x00\n" OSC_JUMPLABEL
#define STRCAT_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x66, 0x00\n" OSC_JUMPLABEL
#define STRNCAT_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x77, 0x00\n" OSC_JUMPLABEL
#define STRNLEN_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x88, 0x00\n" OSC_JUMPLABEL
#define VSNPRINTF_NOMAP_MAGIC OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x99, 0x00\n" OSC_JUMPLABEL

#endif

#define MEMCPY_NOMAP_CASE         ({__asm__(MEMCPY_NOMAP_MAGIC);}),
#define MEMMOVE_NOMAP_CASE        ({__asm__(MEMMOVE_NOMAP_MAGIC);}),
#define MEMSET_NOMAP_CASE         ({__asm__(MEMSET_NOMAP_MAGIC);}),
#define BCOPY_NOMAP_CASE          ({__asm__(BCOPY_NOMAP_MAGIC);}),
#define BZERO_NOMAP_CASE          ({__asm__(BZERO_NOMAP_MAGIC);}),
#define STRCPY_NOMAP_CASE         ({__asm__(STRCPY_NOMAP_MAGIC);}),
#define STRNCPY_NOMAP_CASE        ({__asm__(STRNCPY_NOMAP_MAGIC);}),
#define STRCAT_NOMAP_CASE         ({__asm__(STRCAT_NOMAP_MAGIC);}),
#define STRNCAT_NOMAP_CASE        ({__asm__(STRNCAT_NOMAP_MAGIC);}),
#define STRNLEN_NOMAP_CASE        ({__asm__(STRNLEN_NOMAP_MAGIC);}),
#define VSNPRINTF_NOMAP_CASE      ({__asm__(VSNPRINTF_NOMAP_MAGIC);}),

#else

#define MEMCPY_NOMAP_CASE
#define MEMMOVE_NOMAP_CASE
#define MEMSET_NOMAP_CASE
#define BCOPY_NOMAP_CASE
#define BZERO_NOMAP_CASE
#define STRCPY_NOMAP_CASE
#define STRNCPY_NOMAP_CASE
#define STRCAT_NOMAP_CASE
#define STRNCAT_NOMAP_CASE
#define STRNLEN_NOMAP_CASE
#define VSNPRINTF_NOMAP_CASE

#endif   /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /*__OPENOSC_NOMAP_METRIC_H__ */
