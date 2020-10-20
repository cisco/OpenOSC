/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_SAFEC_MAP_METRIC_H__
#define __OPENOSC_SAFEC_MAP_METRIC_H__

#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#include "openosc_metric_objsize.h"

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD)

#define MEMCMP_S_MAGIC1		".loc 1 8390033"
#define MEMCMP_S_MAGIC2		".loc 1 8390034"
#define MEMCMP_S_MAGIC3		".loc 1 8390035"
#define MEMCMP_S_MAGIC4		".loc 1 8390036"

#define MEMCPY_S_MAGIC1		".loc 1 8390049"
#define MEMCPY_S_MAGIC2		".loc 1 8390050"
#define MEMCPY_S_MAGIC3		".loc 1 8390051"
#define MEMCPY_S_MAGIC4		".loc 1 8390052"

#define STRCAT_S_MAGIC1		".loc 1 8390065"
#define STRCAT_S_MAGIC2		".loc 1 8390066"
#define STRCAT_S_MAGIC3		".loc 1 8390067"
#define STRCAT_S_MAGIC4		".loc 1 8390068"

#define STRCMP_S_MAGIC1		".loc 1 8390081"
#define STRCMP_S_MAGIC2		".loc 1 8390082"
#define STRCMP_S_MAGIC3		".loc 1 8390083"
#define STRCMP_S_MAGIC4		".loc 1 8390084"

#define STRCPY_S_MAGIC1		".loc 1 8390097"
#define STRCPY_S_MAGIC2		".loc 1 8390098"
#define STRCPY_S_MAGIC3		".loc 1 8390099"
#define STRCPY_S_MAGIC4		".loc 1 8390100"

#define STRNCAT_S_MAGIC1		".loc 1 8390113"
#define STRNCAT_S_MAGIC2		".loc 1 8390114"
#define STRNCAT_S_MAGIC3		".loc 1 8390115"
#define STRNCAT_S_MAGIC4		".loc 1 8390116"
#define STRNCAT_S_MAGIC_SAFECequal	".loc 1 8390117"
#define STRNCAT_S_MAGIC_SAFECless	".loc 1 8390118"

#define STRNCPY_S_MAGIC1		".loc 1 8390129"
#define STRNCPY_S_MAGIC2		".loc 1 8390130"
#define STRNCPY_S_MAGIC3		".loc 1 8390131"
#define STRNCPY_S_MAGIC4		".loc 1 8390132"
#define STRNCPY_S_MAGIC_SAFECequal	".loc 1 8390133"
#define STRNCPY_S_MAGIC_SAFECless	".loc 1 8390134"

#define STRNLEN_S_MAGIC1		".loc 1 8390145"
#define STRNLEN_S_MAGIC2		".loc 1 8390146"
#define STRNLEN_S_MAGIC3		".loc 1 8390147"
#define STRNLEN_S_MAGIC4		".loc 1 8390148"

#define STRSTR_S_MAGIC1		".loc 1 8390161"
#define STRSTR_S_MAGIC2		".loc 1 8390162"
#define STRSTR_S_MAGIC3		".loc 1 8390163"
#define STRSTR_S_MAGIC4		".loc 1 8390164"

#elif (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#define MEMCMP_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x88, 0x11\n" OSC_JUMPLABEL
#define MEMCMP_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x88, 0x22\n" OSC_JUMPLABEL
#define MEMCMP_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x88, 0x33\n" OSC_JUMPLABEL
#define MEMCMP_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x88, 0x44\n" OSC_JUMPLABEL

#define MEMCPY_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x00, 0x11\n" OSC_JUMPLABEL
#define MEMCPY_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x00, 0x22\n" OSC_JUMPLABEL
#define MEMCPY_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x00, 0x33\n" OSC_JUMPLABEL
#define MEMCPY_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x00, 0x44\n" OSC_JUMPLABEL

#define STRCAT_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x11, 0x11\n" OSC_JUMPLABEL
#define STRCAT_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x11, 0x22\n" OSC_JUMPLABEL
#define STRCAT_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x11, 0x33\n" OSC_JUMPLABEL
#define STRCAT_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x11, 0x44\n" OSC_JUMPLABEL

#define STRCMP_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x22, 0x11\n" OSC_JUMPLABEL
#define STRCMP_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x22, 0x22\n" OSC_JUMPLABEL
#define STRCMP_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x22, 0x33\n" OSC_JUMPLABEL
#define STRCMP_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x22, 0x44\n" OSC_JUMPLABEL

#define STRCPY_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x33, 0x11\n" OSC_JUMPLABEL
#define STRCPY_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x33, 0x22\n" OSC_JUMPLABEL
#define STRCPY_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x33, 0x33\n" OSC_JUMPLABEL
#define STRCPY_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x33, 0x44\n" OSC_JUMPLABEL

#define STRNCAT_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x11\n" OSC_JUMPLABEL
#define STRNCAT_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x22\n" OSC_JUMPLABEL
#define STRNCAT_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x33\n" OSC_JUMPLABEL
#define STRNCAT_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x44\n" OSC_JUMPLABEL
#define STRNCAT_S_MAGIC_SAFECequal OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x45\n" OSC_JUMPLABEL
#define STRNCAT_S_MAGIC_SAFECless OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x44, 0x46\n" OSC_JUMPLABEL

#define STRNCPY_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x11\n" OSC_JUMPLABEL
#define STRNCPY_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x22\n" OSC_JUMPLABEL
#define STRNCPY_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x33\n" OSC_JUMPLABEL
#define STRNCPY_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x44\n" OSC_JUMPLABEL
#define STRNCPY_S_MAGIC_SAFECequal OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x45\n" OSC_JUMPLABEL
#define STRNCPY_S_MAGIC_SAFECless OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x55, 0x46\n" OSC_JUMPLABEL

#define STRNLEN_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x66, 0x11\n" OSC_JUMPLABEL
#define STRNLEN_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x66, 0x22\n" OSC_JUMPLABEL
#define STRNLEN_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x66, 0x33\n" OSC_JUMPLABEL
#define STRNLEN_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x66, 0x44\n" OSC_JUMPLABEL

#define STRSTR_S_MAGIC1 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x77, 0x11\n" OSC_JUMPLABEL
#define STRSTR_S_MAGIC2 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x77, 0x22\n" OSC_JUMPLABEL
#define STRSTR_S_MAGIC3 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x77, 0x33\n" OSC_JUMPLABEL
#define STRSTR_S_MAGIC4 OSC_JUMPOVER ".byte 0x4d, 0x41, 0x47, 0x49, 0x43, 0xd1, 0x77, 0x44\n" OSC_JUMPLABEL

#endif

#define MEMCMP_S_CASE1                    ({__asm__(MEMCMP_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define MEMCMP_S_CASE2                    ({__asm__(MEMCMP_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define MEMCMP_S_CASE3                    ({__asm__(MEMCMP_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define MEMCMP_S_CASE4                    ({__asm__(MEMCMP_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define MEMCPY_S_CASE1                   ({__asm__(MEMCPY_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define MEMCPY_S_CASE2                   ({__asm__(MEMCPY_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define MEMCPY_S_CASE3                   ({__asm__(MEMCPY_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define MEMCPY_S_CASE4                   ({__asm__(MEMCPY_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRCAT_S_CASE1                    ({__asm__(STRCAT_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRCAT_S_CASE2                    ({__asm__(STRCAT_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRCAT_S_CASE3                    ({__asm__(STRCAT_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRCAT_S_CASE4                    ({__asm__(STRCAT_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRCMP_S_CASE1                     ({__asm__(STRCMP_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRCMP_S_CASE2                     ({__asm__(STRCMP_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRCMP_S_CASE3                     ({__asm__(STRCMP_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRCMP_S_CASE4                     ({__asm__(STRCMP_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRCPY_S_CASE1                     ({__asm__(STRCPY_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRCPY_S_CASE2                     ({__asm__(STRCPY_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRCPY_S_CASE3                     ({__asm__(STRCPY_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRCPY_S_CASE4                     ({__asm__(STRCPY_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE1                    ({__asm__(STRNCAT_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE2                    ({__asm__(STRNCAT_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE3                    ({__asm__(STRNCAT_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE4                    ({__asm__(STRNCAT_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE_SAFECequal          ({__asm__(STRNCAT_S_MAGIC_SAFECequal);}), OSC_DSTSIZE(_sz)
#define STRNCAT_S_CASE_SAFECless           ({__asm__(STRNCAT_S_MAGIC_SAFECless);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE1                   ({__asm__(STRNCPY_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE2                   ({__asm__(STRNCPY_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE3                   ({__asm__(STRNCPY_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE4                   ({__asm__(STRNCPY_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE_SAFECequal         ({__asm__(STRNCPY_S_MAGIC_SAFECequal);}), OSC_DSTSIZE(_sz)
#define STRNCPY_S_CASE_SAFECless          ({__asm__(STRNCPY_S_MAGIC_SAFECless);}), OSC_DSTSIZE(_sz)
#define STRNLEN_S_CASE1                    ({__asm__(STRNLEN_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRNLEN_S_CASE2                    ({__asm__(STRNLEN_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRNLEN_S_CASE3                    ({__asm__(STRNLEN_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRNLEN_S_CASE4                    ({__asm__(STRNLEN_S_MAGIC4);}), OSC_DSTSIZE(_sz)
#define STRSTR_S_CASE1                   ({__asm__(STRSTR_S_MAGIC1);}), OSC_DSTSIZE(_sz)
#define STRSTR_S_CASE2                   ({__asm__(STRSTR_S_MAGIC2);}), OSC_DSTSIZE(_sz)
#define STRSTR_S_CASE3                   ({__asm__(STRSTR_S_MAGIC3);}), OSC_DSTSIZE(_sz)
#define STRSTR_S_CASE4                   ({__asm__(STRSTR_S_MAGIC4);}), OSC_DSTSIZE(_sz)

#else   /* OPENOSC_METRIC_FEATURE_ENABLED */

#define MEMCMP_S_CASE1
#define MEMCMP_S_CASE2
#define MEMCMP_S_CASE3
#define MEMCMP_S_CASE4
#define MEMCPY_S_CASE1
#define MEMCPY_S_CASE2
#define MEMCPY_S_CASE3
#define MEMCPY_S_CASE4
#define STRCAT_S_CASE1
#define STRCAT_S_CASE2
#define STRCAT_S_CASE3
#define STRCAT_S_CASE4
#define STRCMP_S_CASE1
#define STRCMP_S_CASE2
#define STRCMP_S_CASE3
#define STRCMP_S_CASE4
#define STRCPY_S_CASE1
#define STRCPY_S_CASE2
#define STRCPY_S_CASE3
#define STRCPY_S_CASE4
#define STRNCAT_S_CASE1
#define STRNCAT_S_CASE2
#define STRNCAT_S_CASE3
#define STRNCAT_S_CASE4
#define STRNCAT_S_CASE_SAFECequal
#define STRNCAT_S_CASE_SAFECless
#define STRNCPY_S_CASE1
#define STRNCPY_S_CASE2
#define STRNCPY_S_CASE3
#define STRNCPY_S_CASE4
#define STRNCPY_S_CASE_SAFECequal
#define STRNCPY_S_CASE_SAFECless
#define STRNLEN_S_CASE1
#define STRNLEN_S_CASE2
#define STRNLEN_S_CASE3
#define STRNLEN_S_CASE4
#define STRSTR_S_CASE1
#define STRSTR_S_CASE2
#define STRSTR_S_CASE3
#define STRSTR_S_CASE4

#endif    /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /*  __OPENOSC_SAFEC_MAP_METRIC_H__ */
