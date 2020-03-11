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

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

#include "openosc_metric_objsize.h"

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

#else   /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define MEMCMP_S_MAGIC1                   0x1188d1434947414d
#define MEMCMP_S_MAGIC2                   0x2288d1434947414d
#define MEMCMP_S_MAGIC3                   0x3388d1434947414d
#define MEMCMP_S_MAGIC4                   0x4488d1434947414d
#define MEMCPY_S_MAGIC1                   0x1100d1434947414d
#define MEMCPY_S_MAGIC2                   0x2200d1434947414d
#define MEMCPY_S_MAGIC3                   0x3300d1434947414d
#define MEMCPY_S_MAGIC4                   0x4400d1434947414d
#define STRCAT_S_MAGIC1                    0x1111d1434947414d
#define STRCAT_S_MAGIC2                    0x2211d1434947414d
#define STRCAT_S_MAGIC3                    0x3311d1434947414d
#define STRCAT_S_MAGIC4                    0x4411d1434947414d
#define STRCMP_S_MAGIC1                     0x1122d1434947414d
#define STRCMP_S_MAGIC2                     0x2222d1434947414d
#define STRCMP_S_MAGIC3                     0x3322d1434947414d
#define STRCMP_S_MAGIC4                     0x4422d1434947414d
#define STRCPY_S_MAGIC1                     0x1133d1434947414d
#define STRCPY_S_MAGIC2                     0x2233d1434947414d
#define STRCPY_S_MAGIC3                     0x3333d1434947414d
#define STRCPY_S_MAGIC4                     0x4433d1434947414d
#define STRNCAT_S_MAGIC1                    0x1144d1434947414d
#define STRNCAT_S_MAGIC2                    0x2244d1434947414d
#define STRNCAT_S_MAGIC3                    0x3344d1434947414d
#define STRNCAT_S_MAGIC4                    0x4444d1434947414d
#define STRNCAT_S_MAGIC_SAFECequal          0x4544d1434947414d
#define STRNCAT_S_MAGIC_SAFECless           0x4644d1434947414d
#define STRNCPY_S_MAGIC1                   0x1155d1434947414d
#define STRNCPY_S_MAGIC2                   0x2255d1434947414d
#define STRNCPY_S_MAGIC3                   0x3355d1434947414d
#define STRNCPY_S_MAGIC4                   0x4455d1434947414d
#define STRNCPY_S_MAGIC_SAFECequal         0x4555d1434947414d
#define STRNCPY_S_MAGIC_SAFECless          0x4655d1434947414d
#define STRNLEN_S_MAGIC1                    0x1166d1434947414d
#define STRNLEN_S_MAGIC2                    0x2266d1434947414d
#define STRNLEN_S_MAGIC3                    0x3366d1434947414d
#define STRNLEN_S_MAGIC4                    0x4466d1434947414d
#define STRSTR_S_MAGIC1                   0x1177d1434947414d
#define STRSTR_S_MAGIC2                   0x2277d1434947414d
#define STRSTR_S_MAGIC3                   0x3377d1434947414d
#define STRSTR_S_MAGIC4                   0x4477d1434947414d

#else   /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

#define MEMCMP_S_MAGIC1                   0x4d41474943d18811
#define MEMCMP_S_MAGIC2                   0x4d41474943d18822
#define MEMCMP_S_MAGIC3                   0x4d41474943d18833
#define MEMCMP_S_MAGIC4                   0x4d41474943d18844
#define MEMCPY_S_MAGIC1                   0x4d41474943d10011
#define MEMCPY_S_MAGIC2                   0x4d41474943d10022
#define MEMCPY_S_MAGIC3                   0x4d41474943d10033
#define MEMCPY_S_MAGIC4                   0x4d41474943d10044
#define STRCAT_S_MAGIC1                    0x4d41474943d11111
#define STRCAT_S_MAGIC2                    0x4d41474943d11122
#define STRCAT_S_MAGIC3                    0x4d41474943d11133
#define STRCAT_S_MAGIC4                    0x4d41474943d11144
#define STRCMP_S_MAGIC1                     0x4d41474943d12211
#define STRCMP_S_MAGIC2                     0x4d41474943d12222
#define STRCMP_S_MAGIC3                     0x4d41474943d12233
#define STRCMP_S_MAGIC4                     0x4d41474943d12244
#define STRCPY_S_MAGIC1                     0x4d41474943d13311
#define STRCPY_S_MAGIC2                     0x4d41474943d13322
#define STRCPY_S_MAGIC3                     0x4d41474943d13333
#define STRCPY_S_MAGIC4                     0x4d41474943d13344
#define STRNCAT_S_MAGIC1                    0x4d41474943d14411
#define STRNCAT_S_MAGIC2                    0x4d41474943d14422
#define STRNCAT_S_MAGIC3                    0x4d41474943d14433
#define STRNCAT_S_MAGIC4                    0x4d41474943d14444
#define STRNCAT_S_MAGIC_SAFECequal          0x4d41474943d14445
#define STRNCAT_S_MAGIC_SAFECless           0x4d41474943d14446
#define STRNCPY_S_MAGIC1                   0x4d41474943d15511
#define STRNCPY_S_MAGIC2                   0x4d41474943d15522
#define STRNCPY_S_MAGIC3                   0x4d41474943d15533
#define STRNCPY_S_MAGIC4                   0x4d41474943d15544
#define STRNCPY_S_MAGIC_SAFECequal         0x4d41474943d15545
#define STRNCPY_S_MAGIC_SAFECless          0x4d41474943d15546
#define STRNLEN_S_MAGIC1                    0x4d41474943d16611
#define STRNLEN_S_MAGIC2                    0x4d41474943d16622
#define STRNLEN_S_MAGIC3                    0x4d41474943d16633
#define STRNLEN_S_MAGIC4                    0x4d41474943d16644
#define STRSTR_S_MAGIC1                   0x4d41474943d17711
#define STRSTR_S_MAGIC2                   0x4d41474943d17722
#define STRSTR_S_MAGIC3                   0x4d41474943d17733
#define STRSTR_S_MAGIC4                   0x4d41474943d17744

#endif  /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

#define MEMCMP_S_CASE1                    rtd_osc_map_int = MEMCMP_S_MAGIC1,
#define MEMCMP_S_CASE2                    rtd_osc_map_int = MEMCMP_S_MAGIC2,
#define MEMCMP_S_CASE3                    rtd_osc_map_int = MEMCMP_S_MAGIC3,
#define MEMCMP_S_CASE4                    rtd_osc_map_int = MEMCMP_S_MAGIC4,
#define MEMCPY_S_CASE1                   rtd_osc_map_int = MEMCPY_S_MAGIC1,
#define MEMCPY_S_CASE2                   rtd_osc_map_int = MEMCPY_S_MAGIC2,
#define MEMCPY_S_CASE3                   rtd_osc_map_int = MEMCPY_S_MAGIC3,
#define MEMCPY_S_CASE4                   rtd_osc_map_int = MEMCPY_S_MAGIC4,
#define STRCAT_S_CASE1                    rtd_osc_map_int = STRCAT_S_MAGIC1,
#define STRCAT_S_CASE2                    rtd_osc_map_int = STRCAT_S_MAGIC2,
#define STRCAT_S_CASE3                    rtd_osc_map_int = STRCAT_S_MAGIC3,
#define STRCAT_S_CASE4                    rtd_osc_map_int = STRCAT_S_MAGIC4,
#define STRCMP_S_CASE1                     rtd_osc_map_int = STRCMP_S_MAGIC1,
#define STRCMP_S_CASE2                     rtd_osc_map_int = STRCMP_S_MAGIC2,
#define STRCMP_S_CASE3                     rtd_osc_map_int = STRCMP_S_MAGIC3,
#define STRCMP_S_CASE4                     rtd_osc_map_int = STRCMP_S_MAGIC4,
#define STRCPY_S_CASE1                     rtd_osc_map_int = STRCPY_S_MAGIC1,
#define STRCPY_S_CASE2                     rtd_osc_map_int = STRCPY_S_MAGIC2,
#define STRCPY_S_CASE3                     rtd_osc_map_int = STRCPY_S_MAGIC3,
#define STRCPY_S_CASE4                     rtd_osc_map_int = STRCPY_S_MAGIC4,
#define STRNCAT_S_CASE1                    rtd_osc_map_int = STRNCAT_S_MAGIC1,
#define STRNCAT_S_CASE2                    rtd_osc_map_int = STRNCAT_S_MAGIC2,
#define STRNCAT_S_CASE3                    rtd_osc_map_int = STRNCAT_S_MAGIC3,
#define STRNCAT_S_CASE4                    rtd_osc_map_int = STRNCAT_S_MAGIC4,
#define STRNCAT_S_CASE_SAFECequal          rtd_osc_map_int = STRNCAT_S_MAGICSAFECequal,
#define STRNCAT_S_CASE_SAFECless           rtd_osc_map_int = STRNCAT_S_MAGIC_SAFECless,
#define STRNCPY_S_CASE1                   rtd_osc_map_int = STRNCPY_S_MAGIC1,
#define STRNCPY_S_CASE2                   rtd_osc_map_int = STRNCPY_S_MAGIC2,
#define STRNCPY_S_CASE3                   rtd_osc_map_int = STRNCPY_S_MAGIC3,
#define STRNCPY_S_CASE4                   rtd_osc_map_int = STRNCPY_S_MAGIC4,
#define STRNCPY_S_CASE_SAFECequal         rtd_osc_map_int = STRNCPY_S_MAGIC_SAFECequal,
#define STRNCPY_S_CASE_SAFECless          rtd_osc_map_int = STRNCPY_S_MAGIC_SAFECless,
#define STRNLEN_S_CASE1                    rtd_osc_map_int = STRNLEN_S_MAGIC1,
#define STRNLEN_S_CASE2                    rtd_osc_map_int = STRNLEN_S_MAGIC2,
#define STRNLEN_S_CASE3                    rtd_osc_map_int = STRNLEN_S_MAGIC3,
#define STRNLEN_S_CASE4                    rtd_osc_map_int = STRNLEN_S_MAGIC4,
#define STRSTR_S_CASE1                   rtd_osc_map_int = STRSTR_S_MAGIC1,
#define STRSTR_S_CASE2                   rtd_osc_map_int = STRSTR_S_MAGIC2,
#define STRSTR_S_CASE3                   rtd_osc_map_int = STRSTR_S_MAGIC3,
#define STRSTR_S_CASE4                   rtd_osc_map_int = STRSTR_S_MAGIC4,

#endif    /* OSC_METRIC_METHOD == ASM_BYTE_METHOD */

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
