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

#ifdef OPENOSC_METRIC_FEATURE_ENABLED

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

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD)

#define MEMCPY_MAGIC1           ".loc 1 8388865"
#define MEMCPY_MAGIC2           ".loc 1 8388866"
#define MEMCPY_MAGIC3           ".loc 1 8388867"
#define MEMCPY_MAGIC4           ".loc 1 8388868"
#define MEMCPY_MAGIC7           ".loc 1 8388871"
#define MEMCPY_MAGIC8           ".loc 1 8388872"
#define MEMCPY_MAGIC9           ".loc 1 8388873"
#define MEMCPY_MAGICa           ".loc 1 8388874"
#define MEMCPY_MAGICb           ".loc 1 8388875"

#define MEMMOVE_MAGIC1          ".loc 1 8388881"
#define MEMMOVE_MAGIC2          ".loc 1 8388882"
#define MEMMOVE_MAGIC3          ".loc 1 8388883"
#define MEMMOVE_MAGIC4          ".loc 1 8388884"
#define MEMMOVE_MAGIC7          ".loc 1 8388887"
#define MEMMOVE_MAGIC8          ".loc 1 8388888"
#define MEMMOVE_MAGIC9          ".loc 1 8388889"
#define MEMMOVE_MAGICa          ".loc 1 8388890"
#define MEMMOVE_MAGICb          ".loc 1 8388891"

#define MEMSET_MAGIC1           ".loc 1 8388897"
#define MEMSET_MAGIC2           ".loc 1 8388898"
#define MEMSET_MAGIC3           ".loc 1 8388899"
#define MEMSET_MAGIC4           ".loc 1 8388900"

#define BCOPY_MAGIC1            ".loc 1 8388913"
#define BCOPY_MAGIC2            ".loc 1 8388914"
#define BCOPY_MAGIC3            ".loc 1 8388915"
#define BCOPY_MAGIC4            ".loc 1 8388916"
#define BCOPY_MAGIC7            ".loc 1 8388919"
#define BCOPY_MAGIC8            ".loc 1 8388920"
#define BCOPY_MAGIC9            ".loc 1 8388921"
#define BCOPY_MAGICa            ".loc 1 8388922"
#define BCOPY_MAGICb            ".loc 1 8388923"

#define BZERO_MAGIC1            ".loc 1 8388929"
#define BZERO_MAGIC2            ".loc 1 8388930"
#define BZERO_MAGIC3            ".loc 1 8388931"
#define BZERO_MAGIC4            ".loc 1 8388932"

#define STRCPY_MAGIC1           ".loc 1 8388945"
#define STRCPY_MAGIC2           ".loc 1 8388946"
#define STRCPY_MAGIC3           ".loc 1 8388947"
#define STRCPY_MAGIC4           ".loc 1 8388948"

#define STRNCPY_MAGIC1          ".loc 1 8388961"
#define STRNCPY_MAGIC2          ".loc 1 8388962"
#define STRNCPY_MAGIC3          ".loc 1 8388963"
#define STRNCPY_MAGIC4          ".loc 1 8388964"

#define STRCAT_MAGIC1           ".loc 1 8388977"
#define STRCAT_MAGIC2           ".loc 1 8388978"
#define STRCAT_MAGIC3           ".loc 1 8388979"
#define STRCAT_MAGIC4           ".loc 1 8388980"

#define STRNCAT_MAGIC1          ".loc 1 8388993"
#define STRNCAT_MAGIC2          ".loc 1 8388994"
#define STRNCAT_MAGIC3          ".loc 1 8388995"
#define STRNCAT_MAGIC4          ".loc 1 8388996"

#define STRNLEN_MAGIC1          ".loc 1 8389009"
#define STRNLEN_MAGIC2          ".loc 1 8389010"
#define STRNLEN_MAGIC3          ".loc 1 8389011"
#define STRNLEN_MAGIC4          ".loc 1 8389012"

#define VSNPRINTF_MAGIC1                ".loc 1 8389025"
#define VSNPRINTF_MAGIC2                ".loc 1 8389026"
#define VSNPRINTF_MAGIC3                ".loc 1 8389027"
#define VSNPRINTF_MAGIC4                ".loc 1 8389028"

#elif (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

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

#endif

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
