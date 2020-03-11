/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_MAP_METRIC_H__
#define __OPENOSC_MAP_METRIC_H__

#ifdef OPENOSC_HEADER_METRIC_FEATURE_ENABLED

/* always insert a magic word if osc_map.h is included */
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_MAP_H_INCLUDED 0x80818d8f80818d8e
#else
#define MAGIC_OSC_MAP_H_INCLUDED 0x8e8d81808f8d8180
#endif
long long int __attribute__((weak)) rtd_osc_map_h_included_int = MAGIC_OSC_MAP_H_INCLUDED;

#endif /* OPENOSC_HEADER_METRIC_FEATURE_ENABLED */

#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#include "openosc_metric_objsize.h"

#ifndef OPENOSC_COPYLEN_NON_CONST_MAGIC
/* This is the embedded copylen value when copy length is not a constant */
#define OPENOSC_COPYLEN_NON_CONST_MAGIC ((size_t)-9)
#endif

#ifdef OPENOSC_METRIC_OBJSIZE_ENABLED
#define OPENOSC_METRIC_COPYLEN(is_len_constant, len)  (is_len_constant ? len : OPENOSC_COPYLEN_NON_CONST_MAGIC)
#else
#define OPENOSC_METRIC_COPYLEN(is_len_constant, len)  len
#endif

#define MEMCPY_MAGIC1  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x11\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC2  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x22\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC3  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x33\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC4  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x44\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC7  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x77\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC8  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x88\n" OSC_JUMPLABEL
#define MEMCPY_MAGIC9  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0x99\n" OSC_JUMPLABEL
#define MEMCPY_MAGICa  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0xaa\n" OSC_JUMPLABEL
#define MEMCPY_MAGICb  OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0xaa, 0xbb\n" OSC_JUMPLABEL

#define MEMMOVE_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x11\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x22\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x33\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x44\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC7 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x77\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC8 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x88\n" OSC_JUMPLABEL
#define MEMMOVE_MAGIC9 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0x99\n" OSC_JUMPLABEL
#define MEMMOVE_MAGICa OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0xaa\n" OSC_JUMPLABEL
#define MEMMOVE_MAGICb OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x00, 0xbb\n" OSC_JUMPLABEL

#define MEMSET_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x11, 0x11\n" OSC_JUMPLABEL
#define MEMSET_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x11, 0x22\n" OSC_JUMPLABEL
#define MEMSET_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x11, 0x33\n" OSC_JUMPLABEL
#define MEMSET_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x11, 0x44\n" OSC_JUMPLABEL

#define BCOPY_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x11\n" OSC_JUMPLABEL
#define BCOPY_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x22\n" OSC_JUMPLABEL
#define BCOPY_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x33\n" OSC_JUMPLABEL
#define BCOPY_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x44\n" OSC_JUMPLABEL
#define BCOPY_MAGIC7 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x77\n" OSC_JUMPLABEL
#define BCOPY_MAGIC8 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x88\n" OSC_JUMPLABEL
#define BCOPY_MAGIC9 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0x99\n" OSC_JUMPLABEL
#define BCOPY_MAGICa OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0xaa\n" OSC_JUMPLABEL
#define BCOPY_MAGICb OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x22, 0xbb\n" OSC_JUMPLABEL

#define BZERO_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x33, 0x11\n" OSC_JUMPLABEL
#define BZERO_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x33, 0x22\n" OSC_JUMPLABEL
#define BZERO_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x33, 0x33\n" OSC_JUMPLABEL
#define BZERO_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x33, 0x44\n" OSC_JUMPLABEL

#define STRCPY_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x44, 0x11\n" OSC_JUMPLABEL
#define STRCPY_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x44, 0x22\n" OSC_JUMPLABEL
#define STRCPY_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x44, 0x33\n" OSC_JUMPLABEL
#define STRCPY_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x44, 0x44\n" OSC_JUMPLABEL

#define STRNCPY_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x55, 0x11\n" OSC_JUMPLABEL
#define STRNCPY_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x55, 0x22\n" OSC_JUMPLABEL
#define STRNCPY_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x55, 0x33\n" OSC_JUMPLABEL
#define STRNCPY_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x55, 0x44\n" OSC_JUMPLABEL

#define STRCAT_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x66, 0x11\n" OSC_JUMPLABEL
#define STRCAT_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x66, 0x22\n" OSC_JUMPLABEL
#define STRCAT_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x66, 0x33\n" OSC_JUMPLABEL
#define STRCAT_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x66, 0x44\n" OSC_JUMPLABEL

#define STRNCAT_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x77, 0x11\n" OSC_JUMPLABEL
#define STRNCAT_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x77, 0x22\n" OSC_JUMPLABEL
#define STRNCAT_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x77, 0x33\n" OSC_JUMPLABEL
#define STRNCAT_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x77, 0x44\n" OSC_JUMPLABEL

#define STRNLEN_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x88, 0x11\n" OSC_JUMPLABEL
#define STRNLEN_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x88, 0x22\n" OSC_JUMPLABEL
#define STRNLEN_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x88, 0x33\n" OSC_JUMPLABEL
#define STRNLEN_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x88, 0x44\n" OSC_JUMPLABEL

#define VSNPRINTF_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x99, 0x11\n" OSC_JUMPLABEL
#define VSNPRINTF_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x99, 0x22\n" OSC_JUMPLABEL
#define VSNPRINTF_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x99, 0x33\n" OSC_JUMPLABEL
#define VSNPRINTF_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd0, 0x99, 0x44\n" OSC_JUMPLABEL

#define MEMCPY_CASE1                    ({__asm__(MEMCPY_MAGIC1);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE2                    ({__asm__(MEMCPY_MAGIC2);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE3                    ({__asm__(MEMCPY_MAGIC3);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE4                    ({__asm__(MEMCPY_MAGIC4);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE7                    ({__asm__(MEMCPY_MAGIC7);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE8                    ({__asm__(MEMCPY_MAGIC8);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASE9                    ({__asm__(MEMCPY_MAGIC9);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASEa                    ({__asm__(MEMCPY_MAGICa);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMCPY_CASEb                    ({__asm__(MEMCPY_MAGICb);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE1                   ({__asm__(MEMMOVE_MAGIC1);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE2                   ({__asm__(MEMMOVE_MAGIC2);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE3                   ({__asm__(MEMMOVE_MAGIC3);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE4                   ({__asm__(MEMMOVE_MAGIC4);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE7                   ({__asm__(MEMMOVE_MAGIC7);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE8                   ({__asm__(MEMMOVE_MAGIC8);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASE9                   ({__asm__(MEMMOVE_MAGIC9);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASEa                   ({__asm__(MEMMOVE_MAGICa);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMMOVE_CASEb                   ({__asm__(MEMMOVE_MAGICb);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMSET_CASE1                    ({__asm__(MEMSET_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMSET_CASE2                    ({__asm__(MEMSET_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define MEMSET_CASE3                    ({__asm__(MEMSET_MAGIC3);}), OSC_DSTSIZE(_sz)
#define MEMSET_CASE4                    ({__asm__(MEMSET_MAGIC4);}), OSC_DSTSIZE(_sz)
#define BCOPY_CASE1                     ({__asm__(BCOPY_MAGIC1);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE2                     ({__asm__(BCOPY_MAGIC2);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE3                     ({__asm__(BCOPY_MAGIC3);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE4                     ({__asm__(BCOPY_MAGIC4);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE7                     ({__asm__(BCOPY_MAGIC7);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE8                     ({__asm__(BCOPY_MAGIC8);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASE9                     ({__asm__(BCOPY_MAGIC9);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASEa                     ({__asm__(BCOPY_MAGICa);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BCOPY_CASEb                     ({__asm__(BCOPY_MAGICb);}), OSC_DST_SRC_LEN_SIZE(_sz, _src_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BZERO_CASE1                     ({__asm__(BZERO_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BZERO_CASE2                     ({__asm__(BZERO_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define BZERO_CASE3                     ({__asm__(BZERO_MAGIC3);}), OSC_DSTSIZE(_sz)
#define BZERO_CASE4                     ({__asm__(BZERO_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRCPY_CASE1                    ({__asm__(STRCPY_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, strlen(src)))
#define STRCPY_CASE2                    ({__asm__(STRCPY_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, strlen(src)))
#define STRCPY_CASE3                    ({__asm__(STRCPY_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRCPY_CASE4                    ({__asm__(STRCPY_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNCPY_CASE1                   ({__asm__(STRNCPY_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNCPY_CASE2                   ({__asm__(STRNCPY_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNCPY_CASE3                   ({__asm__(STRNCPY_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNCPY_CASE4                   ({__asm__(STRNCPY_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRCAT_CASE1                    ({__asm__(STRCAT_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, strlen(src)))
#define STRCAT_CASE2                    ({__asm__(STRCAT_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, strlen(src)))
#define STRCAT_CASE3                    ({__asm__(STRCAT_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRCAT_CASE4                    ({__asm__(STRCAT_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNCAT_CASE1                   ({__asm__(STRNCAT_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNCAT_CASE2                   ({__asm__(STRNCAT_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNCAT_CASE3                   ({__asm__(STRNCAT_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNCAT_CASE4                   ({__asm__(STRNCAT_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNLEN_CASE1                   ({__asm__(STRNLEN_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNLEN_CASE2                   ({__asm__(STRNLEN_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define STRNLEN_CASE3                   ({__asm__(STRNLEN_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNLEN_CASE4                   ({__asm__(STRNLEN_MAGIC4);}), OSC_DSTSIZE(_sz)
#define VSNPRINTF_CASE1                 ({__asm__(VSNPRINTF_MAGIC1);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define VSNPRINTF_CASE2                 ({__asm__(VSNPRINTF_MAGIC2);}), OSC_DST_LEN_SIZE(_sz, OPENOSC_METRIC_COPYLEN(is_len_constant, len))
#define VSNPRINTF_CASE3                 ({__asm__(VSNPRINTF_MAGIC3);}), OSC_DSTSIZE(_sz)
#define VSNPRINTF_CASE4                 ({__asm__(VSNPRINTF_MAGIC4);}), OSC_DSTSIZE(_sz)

#else   /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

long long int __attribute__((weak)) rtd_osc_map_int = 0;

#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#define MEMCPY_MAGIC1                    0x4d41474943d0aa11
#define MEMCPY_MAGIC2                    0x4d41474943d0aa22
#define MEMCPY_MAGIC3                    0x4d41474943d0aa33
#define MEMCPY_MAGIC4                    0x4d41474943d0aa44
#define MEMCPY_MAGIC7                    0x4d41474943d0aa77
#define MEMCPY_MAGIC8                    0x4d41474943d0aa88
#define MEMCPY_MAGIC9                    0x4d41474943d0aa99
#define MEMCPY_MAGICa                    0x4d41474943d0aaaa
#define MEMCPY_MAGICb                    0x4d41474943d0aabb
#define MEMMOVE_MAGIC1                   0x4d41474943d00011
#define MEMMOVE_MAGIC2                   0x4d41474943d00022
#define MEMMOVE_MAGIC3                   0x4d41474943d00033
#define MEMMOVE_MAGIC4                   0x4d41474943d00044
#define MEMMOVE_MAGIC7                   0x4d41474943d00077
#define MEMMOVE_MAGIC8                   0x4d41474943d00088
#define MEMMOVE_MAGIC9                   0x4d41474943d00099
#define MEMMOVE_MAGICa                   0x4d41474943d000aa
#define MEMMOVE_MAGICb                   0x4d41474943d000bb
#define MEMSET_MAGIC1                    0x4d41474943d01111
#define MEMSET_MAGIC2                    0x4d41474943d01122
#define MEMSET_MAGIC3                    0x4d41474943d01133
#define MEMSET_MAGIC4                    0x4d41474943d01144
#define BCOPY_MAGIC1                     0x4d41474943d02211
#define BCOPY_MAGIC2                     0x4d41474943d02222
#define BCOPY_MAGIC3                     0x4d41474943d02233
#define BCOPY_MAGIC4                     0x4d41474943d02244
#define BCOPY_MAGIC7                     0x4d41474943d02277
#define BCOPY_MAGIC8                     0x4d41474943d02288
#define BCOPY_MAGIC9                     0x4d41474943d02299
#define BCOPY_MAGICa                     0x4d41474943d022aa
#define BCOPY_MAGICb                     0x4d41474943d022bb
#define BZERO_MAGIC1                     0x4d41474943d03311
#define BZERO_MAGIC2                     0x4d41474943d03322
#define BZERO_MAGIC3                     0x4d41474943d03333
#define BZERO_MAGIC4                     0x4d41474943d03344
#define STRCPY_MAGIC1                    0x4d41474943d04411
#define STRCPY_MAGIC2                    0x4d41474943d04422
#define STRCPY_MAGIC3                    0x4d41474943d04433
#define STRCPY_MAGIC4                    0x4d41474943d04444
#define STRNCPY_MAGIC1                   0x4d41474943d05511
#define STRNCPY_MAGIC2                   0x4d41474943d05522
#define STRNCPY_MAGIC3                   0x4d41474943d05533
#define STRNCPY_MAGIC4                   0x4d41474943d05544
#define STRCAT_MAGIC1                    0x4d41474943d06611
#define STRCAT_MAGIC2                    0x4d41474943d06622
#define STRCAT_MAGIC3                    0x4d41474943d06633
#define STRCAT_MAGIC4                    0x4d41474943d06644
#define STRNCAT_MAGIC1                   0x4d41474943d07711
#define STRNCAT_MAGIC2                   0x4d41474943d07722
#define STRNCAT_MAGIC3                   0x4d41474943d07733
#define STRNCAT_MAGIC4                   0x4d41474943d07744
#define STRNLEN_MAGIC1                   0x4d41474943d08811
#define STRNLEN_MAGIC2                   0x4d41474943d08822
#define STRNLEN_MAGIC3                   0x4d41474943d08833
#define STRNLEN_MAGIC4                   0x4d41474943d08844
#define VSNPRINTF_MAGIC1                 0x4d41474943d09911
#define VSNPRINTF_MAGIC2                 0x4d41474943d09922
#define VSNPRINTF_MAGIC3                 0x4d41474943d09933
#define VSNPRINTF_MAGIC4                 0x4d41474943d09944

#else   /* defined __BIG_ENDIAN__ || defined __BIG_ENDIAN */

#define MEMCPY_MAGIC1                    0x11aad0434947414d
#define MEMCPY_MAGIC2                    0x22aad0434947414d
#define MEMCPY_MAGIC3                    0x33aad0434947414d
#define MEMCPY_MAGIC4                    0x44aad0434947414d
#define MEMCPY_MAGIC7                    0x77aad0434947414d
#define MEMCPY_MAGIC8                    0x88aad0434947414d
#define MEMCPY_MAGIC9                    0x99aad0434947414d
#define MEMCPY_MAGICa                    0xaaaad0434947414d
#define MEMCPY_MAGICb                    0xbbaad0434947414d
#define MEMMOVE_MAGIC1                   0x1100d0434947414d
#define MEMMOVE_MAGIC2                   0x2200d0434947414d
#define MEMMOVE_MAGIC3                   0x3300d0434947414d
#define MEMMOVE_MAGIC4                   0x4400d0434947414d
#define MEMMOVE_MAGIC7                   0x7700d0434947414d
#define MEMMOVE_MAGIC8                   0x8800d0434947414d
#define MEMMOVE_MAGIC9                   0x9900d0434947414d
#define MEMMOVE_MAGICa                   0xaa00d0434947414d
#define MEMMOVE_MAGICb                   0xbb00d0434947414d
#define MEMSET_MAGIC1                    0x1111d0434947414d
#define MEMSET_MAGIC2                    0x2211d0434947414d
#define MEMSET_MAGIC3                    0x3311d0434947414d
#define MEMSET_MAGIC4                    0x4411d0434947414d
#define BCOPY_MAGIC1                     0x1122d0434947414d
#define BCOPY_MAGIC2                     0x2222d0434947414d
#define BCOPY_MAGIC3                     0x3322d0434947414d
#define BCOPY_MAGIC4                     0x4422d0434947414d
#define BCOPY_MAGIC7                     0x7722d0434947414d
#define BCOPY_MAGIC8                     0x8822d0434947414d
#define BCOPY_MAGIC9                     0x9922d0434947414d
#define BCOPY_MAGICa                     0xaa22d0434947414d
#define BCOPY_MAGICb                     0xbb22d0434947414d
#define BZERO_MAGIC1                     0x1133d0434947414d
#define BZERO_MAGIC2                     0x2233d0434947414d
#define BZERO_MAGIC3                     0x3333d0434947414d
#define BZERO_MAGIC4                     0x4433d0434947414d
#define STRCPY_MAGIC1                    0x1144d0434947414d
#define STRCPY_MAGIC2                    0x2244d0434947414d
#define STRCPY_MAGIC3                    0x3344d0434947414d
#define STRCPY_MAGIC4                    0x4444d0434947414d
#define STRNCPY_MAGIC1                   0x1155d0434947414d
#define STRNCPY_MAGIC2                   0x2255d0434947414d
#define STRNCPY_MAGIC3                   0x3355d0434947414d
#define STRNCPY_MAGIC4                   0x4455d0434947414d
#define STRCAT_MAGIC1                    0x1166d0434947414d
#define STRCAT_MAGIC2                    0x2266d0434947414d
#define STRCAT_MAGIC3                    0x3366d0434947414d
#define STRCAT_MAGIC4                    0x4466d0434947414d
#define STRNCAT_MAGIC1                   0x1177d0434947414d
#define STRNCAT_MAGIC2                   0x2277d0434947414d
#define STRNCAT_MAGIC3                   0x3377d0434947414d
#define STRNCAT_MAGIC4                   0x4477d0434947414d
#define STRNLEN_MAGIC1                   0x1188d0434947414d
#define STRNLEN_MAGIC2                   0x2288d0434947414d
#define STRNLEN_MAGIC3                   0x3388d0434947414d
#define STRNLEN_MAGIC4                   0x4488d0434947414d
#define VSNPRINTF_MAGIC1                 0x1199d0434947414d
#define VSNPRINTF_MAGIC2                 0x2299d0434947414d
#define VSNPRINTF_MAGIC3                 0x3399d0434947414d
#define VSNPRINTF_MAGIC4                 0x4499d0434947414d

#endif  /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

#define MEMCPY_CASE1                    rtd_osc_map_int = MEMCPY_MAGIC1,
#define MEMCPY_CASE2                    rtd_osc_map_int = MEMCPY_MAGIC2,
#define MEMCPY_CASE3                    rtd_osc_map_int = MEMCPY_MAGIC3,
#define MEMCPY_CASE4                    rtd_osc_map_int = MEMCPY_MAGIC4,
#define MEMCPY_CASE7                    rtd_osc_map_int = MEMCPY_MAGIC7,
#define MEMCPY_CASE8                    rtd_osc_map_int = MEMCPY_MAGIC8,
#define MEMCPY_CASE9                    rtd_osc_map_int = MEMCPY_MAGIC9,
#define MEMCPY_CASEa                    rtd_osc_map_int = MEMCPY_MAGICa,
#define MEMCPY_CASEb                    rtd_osc_map_int = MEMCPY_MAGICb,
#define MEMMOVE_CASE1                   rtd_osc_map_int = MEMMOVE_MAGIC1,
#define MEMMOVE_CASE2                   rtd_osc_map_int = MEMMOVE_MAGIC2,
#define MEMMOVE_CASE3                   rtd_osc_map_int = MEMMOVE_MAGIC3,
#define MEMMOVE_CASE4                   rtd_osc_map_int = MEMMOVE_MAGIC4,
#define MEMMOVE_CASE7                   rtd_osc_map_int = MEMMOVE_MAGIC7,
#define MEMMOVE_CASE8                   rtd_osc_map_int = MEMMOVE_MAGIC8,
#define MEMMOVE_CASE9                   rtd_osc_map_int = MEMMOVE_MAGIC9,
#define MEMMOVE_CASEa                   rtd_osc_map_int = MEMMOVE_MAGICa,
#define MEMMOVE_CASEb                   rtd_osc_map_int = MEMMOVE_MAGICb,
#define MEMSET_CASE1                    rtd_osc_map_int = MEMSET_MAGIC1,
#define MEMSET_CASE2                    rtd_osc_map_int = MEMSET_MAGIC2,
#define MEMSET_CASE3                    rtd_osc_map_int = MEMSET_MAGIC3,
#define MEMSET_CASE4                    rtd_osc_map_int = MEMSET_MAGIC4,
#define BCOPY_CASE1                     rtd_osc_map_int = BCOPY_MAGIC1,
#define BCOPY_CASE2                     rtd_osc_map_int = BCOPY_MAGIC2,
#define BCOPY_CASE3                     rtd_osc_map_int = BCOPY_MAGIC3,
#define BCOPY_CASE4                     rtd_osc_map_int = BCOPY_MAGIC4,
#define BCOPY_CASE7                     rtd_osc_map_int = BCOPY_MAGIC7,
#define BCOPY_CASE8                     rtd_osc_map_int = BCOPY_MAGIC8,
#define BCOPY_CASE9                     rtd_osc_map_int = BCOPY_MAGIC9,
#define BCOPY_CASEa                     rtd_osc_map_int = BCOPY_MAGICa,
#define BCOPY_CASEb                     rtd_osc_map_int = BCOPY_MAGICb,
#define BZERO_CASE1                     rtd_osc_map_int = BZERO_MAGIC1,
#define BZERO_CASE2                     rtd_osc_map_int = BZERO_MAGIC2,
#define BZERO_CASE3                     rtd_osc_map_int = BZERO_MAGIC3,
#define BZERO_CASE4                     rtd_osc_map_int = BZERO_MAGIC4,
#define STRCPY_CASE1                    rtd_osc_map_int = STRCPY_MAGIC1,
#define STRCPY_CASE2                    rtd_osc_map_int = STRCPY_MAGIC2,
#define STRCPY_CASE3                    rtd_osc_map_int = STRCPY_MAGIC3,
#define STRCPY_CASE4                    rtd_osc_map_int = STRCPY_MAGIC4,
#define STRNCPY_CASE1                   rtd_osc_map_int = STRNCPY_MAGIC1,
#define STRNCPY_CASE2                   rtd_osc_map_int = STRNCPY_MAGIC2,
#define STRNCPY_CASE3                   rtd_osc_map_int = STRNCPY_MAGIC3,
#define STRNCPY_CASE4                   rtd_osc_map_int = STRNCPY_MAGIC4,
#define STRCAT_CASE1                    rtd_osc_map_int = STRCAT_MAGIC1,
#define STRCAT_CASE2                    rtd_osc_map_int = STRCAT_MAGIC2,
#define STRCAT_CASE3                    rtd_osc_map_int = STRCAT_MAGIC3,
#define STRCAT_CASE4                    rtd_osc_map_int = STRCAT_MAGIC4,
#define STRNCAT_CASE1                   rtd_osc_map_int = STRNCAT_MAGIC1,
#define STRNCAT_CASE2                   rtd_osc_map_int = STRNCAT_MAGIC2,
#define STRNCAT_CASE3                   rtd_osc_map_int = STRNCAT_MAGIC3,
#define STRNCAT_CASE4                   rtd_osc_map_int = STRNCAT_MAGIC4,
#define STRNLEN_CASE1                   rtd_osc_map_int = STRNLEN_MAGIC1,
#define STRNLEN_CASE2                   rtd_osc_map_int = STRNLEN_MAGIC2,
#define STRNLEN_CASE3                   rtd_osc_map_int = STRNLEN_MAGIC3,
#define STRNLEN_CASE4                   rtd_osc_map_int = STRNLEN_MAGIC4,
#define VSNPRINTF_CASE1                 rtd_osc_map_int = VSNPRINTF_MAGIC1,
#define VSNPRINTF_CASE2                 rtd_osc_map_int = VSNPRINTF_MAGIC2,
#define VSNPRINTF_CASE3                 rtd_osc_map_int = VSNPRINTF_MAGIC3,
#define VSNPRINTF_CASE4                 rtd_osc_map_int = VSNPRINTF_MAGIC4,

#endif    /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

#else   /* OPENOSC_METRIC_FEATURE_ENABLED */

#define MEMCPY_CASE1
#define MEMCPY_CASE2
#define MEMCPY_CASE3
#define MEMCPY_CASE4
#define MEMCPY_CASE7
#define MEMCPY_CASE8
#define MEMCPY_CASE9
#define MEMCPY_CASEa
#define MEMCPY_CASEb
#define MEMMOVE_CASE1
#define MEMMOVE_CASE2
#define MEMMOVE_CASE3
#define MEMMOVE_CASE4
#define MEMMOVE_CASE7
#define MEMMOVE_CASE8
#define MEMMOVE_CASE9
#define MEMMOVE_CASEa
#define MEMMOVE_CASEb
#define MEMSET_CASE1
#define MEMSET_CASE2
#define MEMSET_CASE3
#define MEMSET_CASE4
#define BCOPY_CASE1
#define BCOPY_CASE2
#define BCOPY_CASE3
#define BCOPY_CASE4
#define BCOPY_CASE7
#define BCOPY_CASE8
#define BCOPY_CASE9
#define BCOPY_CASEa
#define BCOPY_CASEb
#define BZERO_CASE1
#define BZERO_CASE2
#define BZERO_CASE3
#define BZERO_CASE4
#define STRCPY_CASE1
#define STRCPY_CASE2
#define STRCPY_CASE3
#define STRCPY_CASE4
#define STRNCPY_CASE1
#define STRNCPY_CASE2
#define STRNCPY_CASE3
#define STRNCPY_CASE4
#define STRCAT_CASE1
#define STRCAT_CASE2
#define STRCAT_CASE3
#define STRCAT_CASE4
#define STRNCAT_CASE1
#define STRNCAT_CASE2
#define STRNCAT_CASE3
#define STRNCAT_CASE4
#define STRNLEN_CASE1
#define STRNLEN_CASE2
#define STRNLEN_CASE3
#define STRNLEN_CASE4
#define VSNPRINTF_CASE1
#define VSNPRINTF_CASE2
#define VSNPRINTF_CASE3
#define VSNPRINTF_CASE4

#endif    /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /*  __OPENOSC_MAP_METRIC_H__ */
