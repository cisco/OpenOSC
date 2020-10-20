/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_METRIC_OBJSIZE_H__
#define __OPENOSC_METRIC_OBJSIZE_H__

/* The single flag to enable/disable this feature */
/* #define OPENOSC_METRIC_OBJSIZE_ENABLED */

#ifdef OPENOSC_METRIC_OBJSIZE_ENABLED

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD)

/*
 * The below macro is used to encode the partial bits of a constant.
 * 8388608 is 0x00800000 in hexadecimal, and 8388623 is 0x0080000f in hexadecimal.
 * the last 4bits is the encoded value for partial N-bits of the constant.
 * The range must not overlap with any magic values for a specific function-case.
 */
#define OSC_ASM_LOC0 ({__asm__(".loc 1 8388608");})
#define OSC_ASM_LOC1 ({__asm__(".loc 1 8388609");})
#define OSC_ASM_LOC2 ({__asm__(".loc 1 8388610");})
#define OSC_ASM_LOC3 ({__asm__(".loc 1 8388611");})
#define OSC_ASM_LOC4 ({__asm__(".loc 1 8388612");})
#define OSC_ASM_LOC5 ({__asm__(".loc 1 8388613");})
#define OSC_ASM_LOC6 ({__asm__(".loc 1 8388614");})
#define OSC_ASM_LOC7 ({__asm__(".loc 1 8388615");})
#define OSC_ASM_LOC8 ({__asm__(".loc 1 8388616");})
#define OSC_ASM_LOC9 ({__asm__(".loc 1 8388617");})
#define OSC_ASM_LOC10 ({__asm__(".loc 1 8388618");})
#define OSC_ASM_LOC11 ({__asm__(".loc 1 8388619");})
#define OSC_ASM_LOC12 ({__asm__(".loc 1 8388620");})
#define OSC_ASM_LOC13 ({__asm__(".loc 1 8388621");})
#define OSC_ASM_LOC14 ({__asm__(".loc 1 8388622");})
#define OSC_ASM_LOC15 ({__asm__(".loc 1 8388623");})

/*
 * The below macro denotes the end of the encoding for a constant.
 * 8388607 is 0x007fffff in hexadecimal.
 * the LOC_LEN_END and LOC_LEN_START values should be close to the above LOCn values.
 */
#define OSC_ASM_LOC_LEN_END ({__asm__(".loc 1 8388607");})

/*
 * The below macro denotes the start of the encoding for a constant.
 * the first is num_bytes, and the second is bits_per_loc.
 * num_bytes can be 1,2,4,8, bits_per_loc can be 1,2,4
 * 8388592 is 0x007ffff0 in hexadecimal, this is the smallest line value for our DWARF_LINE method.
 */
#define OSC_ASM_LOC_LEN_START_1_1 ({__asm__(".loc 1 8388592");})
#define OSC_ASM_LOC_LEN_START_1_2 ({__asm__(".loc 1 8388593");})
#define OSC_ASM_LOC_LEN_START_1_4 ({__asm__(".loc 1 8388594");})

#define OSC_ASM_LOC_LEN_START_2_1 ({__asm__(".loc 1 8388595");})
#define OSC_ASM_LOC_LEN_START_2_2 ({__asm__(".loc 1 8388596");})
#define OSC_ASM_LOC_LEN_START_2_4 ({__asm__(".loc 1 8388597");})

#define OSC_ASM_LOC_LEN_START_4_1 ({__asm__(".loc 1 8388598");})
#define OSC_ASM_LOC_LEN_START_4_2 ({__asm__(".loc 1 8388599");})
#define OSC_ASM_LOC_LEN_START_4_4 ({__asm__(".loc 1 8388600");})

#define OSC_ASM_LOC_LEN_START_8_1 ({__asm__(".loc 1 8388601");})
#define OSC_ASM_LOC_LEN_START_8_2 ({__asm__(".loc 1 8388602");})
#define OSC_ASM_LOC_LEN_START_8_4 ({__asm__(".loc 1 8388603");})

/*
 * The below macro denotes the start of the encoding for a constant.
 * the first parameter num_bytes is number of total bytes for this constant,
 * the second parameter bits_per_loc is how many bits are encoded in each .loc line.
 */
#define OSC_ASM_LOC_LEN_START(num_bytes, bits_per_loc) OSC_ASM_LOC_LEN_START_ ## num_bytes ## _ ## bits_per_loc

/* encode the last 1, 2, or 4 bits of sz */
#define OSC_LOC_1BIT(sz) (sz & 1) ? OSC_ASM_LOC1 : OSC_ASM_LOC0
#define OSC_LOC_2BIT(sz) (sz & 2) ? ((sz & 1) ? OSC_ASM_LOC3 : OSC_ASM_LOC2) : ((sz & 1) ? OSC_ASM_LOC1 : OSC_ASM_LOC0)
#define OSC_LOC_4BIT(sz) (sz & 8) ? ((sz & 4) ? ((sz & 2) ? ((sz & 1) ? OSC_ASM_LOC15 : OSC_ASM_LOC14) : ((sz & 1) ? OSC_ASM_LOC13 : OSC_ASM_LOC12)) : ((sz & 2) ? ((sz & 1) ? OSC_ASM_LOC11 : OSC_ASM_LOC10) : ((sz & 1) ? OSC_ASM_LOC9 : OSC_ASM_LOC8))) : ((sz & 4) ? ((sz & 2) ? ((sz & 1) ? OSC_ASM_LOC7 : OSC_ASM_LOC6) : ((sz & 1) ? OSC_ASM_LOC5 : OSC_ASM_LOC4)) : ((sz & 2) ? ((sz & 1) ? OSC_ASM_LOC3 : OSC_ASM_LOC2) : ((sz & 1) ? OSC_ASM_LOC1 : OSC_ASM_LOC0)))

/* encode the last 1, 2, or 4 bits of sz after right-shifting N bits */
#define OSC_ASM_LOC_1BIT(sz, n) OSC_LOC_1BIT(sz >> n)
#define OSC_ASM_LOC_2BIT(sz, n) OSC_LOC_2BIT(sz >> n)
#define OSC_ASM_LOC_4BIT(sz, n) OSC_LOC_4BIT(sz >> n)

/*
 * This macro encodes the last 1, 2, or 4 bits of sze after right-shifting N bits.
 * The first parameter is sz, the second parameter is number of bits to right-shift,
 * and the third parameter is how many bits to encode.
 * well, this macro is not used.
 */
#define OSC_ASM_LOC_NBIT(sz, n, nbits) OSC_ASM_LOC_ ## nbits ## BIT(sz, n)

/*
 * Each constant encoding starts with one .loc of OSC_ASM_LOC_LEN_START(num_bytes, bits_per_loc),
 * which tells us how many encoded bytes for this constant (8 bytes by default),
 * and how many bits are encoded in each .loc line (4 bits/loc by default);
 * then a few .loc lines, #lines = num_bytes * 8 / bits_per_loc (16 lines by default);
 * and ends with one .loc of OSC_ASM_LOC_LEN_END.
 */

/* encoding N bytes with 4bits-per-loc */
#define OSC_ASM_LOC_1BYTE_1BIT(sz) OSC_ASM_LOC_LEN_START(1,1), OSC_ASM_LOC_1BIT(sz, 0), OSC_ASM_LOC_1BIT(sz, 1), OSC_ASM_LOC_1BIT(sz, 2), OSC_ASM_LOC_1BIT(sz, 3), OSC_ASM_LOC_1BIT(sz, 4), OSC_ASM_LOC_1BIT(sz, 5), OSC_ASM_LOC_1BIT(sz, 6), OSC_ASM_LOC_1BIT(sz, 7), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_2BYTE_1BIT(sz) OSC_ASM_LOC_LEN_START(2,1), OSC_ASM_LOC_1BIT(sz, 0), OSC_ASM_LOC_1BIT(sz, 1), OSC_ASM_LOC_1BIT(sz, 2), OSC_ASM_LOC_1BIT(sz, 3), OSC_ASM_LOC_1BIT(sz, 4), OSC_ASM_LOC_1BIT(sz, 5), OSC_ASM_LOC_1BIT(sz, 6), OSC_ASM_LOC_1BIT(sz, 7), OSC_ASM_LOC_1BIT(sz, 8), OSC_ASM_LOC_1BIT(sz, 9), OSC_ASM_LOC_1BIT(sz, 10), OSC_ASM_LOC_1BIT(sz, 11), OSC_ASM_LOC_1BIT(sz, 12), OSC_ASM_LOC_1BIT(sz, 13), OSC_ASM_LOC_1BIT(sz, 14), OSC_ASM_LOC_1BIT(sz, 15), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_4BYTE_1BIT(sz) OSC_ASM_LOC_LEN_START(4,1), OSC_ASM_LOC_1BIT(sz, 0), OSC_ASM_LOC_1BIT(sz, 1), OSC_ASM_LOC_1BIT(sz, 2), OSC_ASM_LOC_1BIT(sz, 3), OSC_ASM_LOC_1BIT(sz, 4), OSC_ASM_LOC_1BIT(sz, 5), OSC_ASM_LOC_1BIT(sz, 6), OSC_ASM_LOC_1BIT(sz, 7), OSC_ASM_LOC_1BIT(sz, 8), OSC_ASM_LOC_1BIT(sz, 9), OSC_ASM_LOC_1BIT(sz, 10), OSC_ASM_LOC_1BIT(sz, 11), OSC_ASM_LOC_1BIT(sz, 12), OSC_ASM_LOC_1BIT(sz, 13), OSC_ASM_LOC_1BIT(sz, 14), OSC_ASM_LOC_1BIT(sz, 15), OSC_ASM_LOC_1BIT(sz, 16), OSC_ASM_LOC_1BIT(sz, 17), OSC_ASM_LOC_1BIT(sz, 18), OSC_ASM_LOC_1BIT(sz, 19), OSC_ASM_LOC_1BIT(sz, 20), OSC_ASM_LOC_1BIT(sz, 21), OSC_ASM_LOC_1BIT(sz, 22), OSC_ASM_LOC_1BIT(sz, 23), OSC_ASM_LOC_1BIT(sz, 24), OSC_ASM_LOC_1BIT(sz, 25), OSC_ASM_LOC_1BIT(sz, 26), OSC_ASM_LOC_1BIT(sz, 27), OSC_ASM_LOC_1BIT(sz, 28), OSC_ASM_LOC_1BIT(sz, 29), OSC_ASM_LOC_1BIT(sz, 30), OSC_ASM_LOC_1BIT(sz, 31), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_8BYTE_1BIT(sz) OSC_ASM_LOC_LEN_START(8,1), OSC_ASM_LOC_1BIT(sz, 0), OSC_ASM_LOC_1BIT(sz, 1), OSC_ASM_LOC_1BIT(sz, 2), OSC_ASM_LOC_1BIT(sz, 3), OSC_ASM_LOC_1BIT(sz, 4), OSC_ASM_LOC_1BIT(sz, 5), OSC_ASM_LOC_1BIT(sz, 6), OSC_ASM_LOC_1BIT(sz, 7), OSC_ASM_LOC_1BIT(sz, 8), OSC_ASM_LOC_1BIT(sz, 9), OSC_ASM_LOC_1BIT(sz, 10), OSC_ASM_LOC_1BIT(sz, 11), OSC_ASM_LOC_1BIT(sz, 12), OSC_ASM_LOC_1BIT(sz, 13), OSC_ASM_LOC_1BIT(sz, 14), OSC_ASM_LOC_1BIT(sz, 15), OSC_ASM_LOC_1BIT(sz, 16), OSC_ASM_LOC_1BIT(sz, 17), OSC_ASM_LOC_1BIT(sz, 18), OSC_ASM_LOC_1BIT(sz, 19), OSC_ASM_LOC_1BIT(sz, 20), OSC_ASM_LOC_1BIT(sz, 21), OSC_ASM_LOC_1BIT(sz, 22), OSC_ASM_LOC_1BIT(sz, 23), OSC_ASM_LOC_1BIT(sz, 24), OSC_ASM_LOC_1BIT(sz, 25), OSC_ASM_LOC_1BIT(sz, 26), OSC_ASM_LOC_1BIT(sz, 27), OSC_ASM_LOC_1BIT(sz, 28), OSC_ASM_LOC_1BIT(sz, 29), OSC_ASM_LOC_1BIT(sz, 30), OSC_ASM_LOC_1BIT(sz, 31), OSC_ASM_LOC_1BIT(sz, 32), OSC_ASM_LOC_1BIT(sz, 33), OSC_ASM_LOC_1BIT(sz, 34), OSC_ASM_LOC_1BIT(sz, 35), OSC_ASM_LOC_1BIT(sz, 36), OSC_ASM_LOC_1BIT(sz, 37), OSC_ASM_LOC_1BIT(sz, 38), OSC_ASM_LOC_1BIT(sz, 39), OSC_ASM_LOC_1BIT(sz, 40), OSC_ASM_LOC_1BIT(sz, 41), OSC_ASM_LOC_1BIT(sz, 42), OSC_ASM_LOC_1BIT(sz, 43), OSC_ASM_LOC_1BIT(sz, 44), OSC_ASM_LOC_1BIT(sz, 45), OSC_ASM_LOC_1BIT(sz, 46), OSC_ASM_LOC_1BIT(sz, 47), OSC_ASM_LOC_1BIT(sz, 48), OSC_ASM_LOC_1BIT(sz, 49), OSC_ASM_LOC_1BIT(sz, 50), OSC_ASM_LOC_1BIT(sz, 51), OSC_ASM_LOC_1BIT(sz, 52), OSC_ASM_LOC_1BIT(sz, 53), OSC_ASM_LOC_1BIT(sz, 54), OSC_ASM_LOC_1BIT(sz, 55), OSC_ASM_LOC_1BIT(sz, 56), OSC_ASM_LOC_1BIT(sz, 57), OSC_ASM_LOC_1BIT(sz, 58), OSC_ASM_LOC_1BIT(sz, 59), OSC_ASM_LOC_1BIT(sz, 60), OSC_ASM_LOC_1BIT(sz, 61), OSC_ASM_LOC_1BIT(sz, 62), OSC_ASM_LOC_1BIT(sz, 63), OSC_ASM_LOC_LEN_END,


/* encoding N bytes with 2bits-per-loc */
#define OSC_ASM_LOC_1BYTE_2BIT(sz) OSC_ASM_LOC_LEN_START(1,2), OSC_ASM_LOC_2BIT(sz, 0), OSC_ASM_LOC_2BIT(sz, 2), OSC_ASM_LOC_2BIT(sz, 4), OSC_ASM_LOC_2BIT(sz, 6), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_2BYTE_2BIT(sz) OSC_ASM_LOC_LEN_START(2,2), OSC_ASM_LOC_2BIT(sz, 0), OSC_ASM_LOC_2BIT(sz, 2), OSC_ASM_LOC_2BIT(sz, 4), OSC_ASM_LOC_2BIT(sz, 6), OSC_ASM_LOC_2BIT(sz, 8), OSC_ASM_LOC_2BIT(sz, 10), OSC_ASM_LOC_2BIT(sz, 12), OSC_ASM_LOC_2BIT(sz, 14), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_4BYTE_2BIT(sz) OSC_ASM_LOC_LEN_START(4,2), OSC_ASM_LOC_2BIT(sz, 0), OSC_ASM_LOC_2BIT(sz, 2), OSC_ASM_LOC_2BIT(sz, 4), OSC_ASM_LOC_2BIT(sz, 6), OSC_ASM_LOC_2BIT(sz, 8), OSC_ASM_LOC_2BIT(sz, 10), OSC_ASM_LOC_2BIT(sz, 12), OSC_ASM_LOC_2BIT(sz, 14), OSC_ASM_LOC_2BIT(sz, 16), OSC_ASM_LOC_2BIT(sz, 18), OSC_ASM_LOC_2BIT(sz, 20), OSC_ASM_LOC_2BIT(sz, 22), OSC_ASM_LOC_2BIT(sz, 24), OSC_ASM_LOC_2BIT(sz, 26), OSC_ASM_LOC_2BIT(sz, 28), OSC_ASM_LOC_2BIT(sz, 30), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_8BYTE_2BIT(sz) OSC_ASM_LOC_LEN_START(8,2), OSC_ASM_LOC_2BIT(sz, 0), OSC_ASM_LOC_2BIT(sz, 2), OSC_ASM_LOC_2BIT(sz, 4), OSC_ASM_LOC_2BIT(sz, 6), OSC_ASM_LOC_2BIT(sz, 8), OSC_ASM_LOC_2BIT(sz, 10), OSC_ASM_LOC_2BIT(sz, 12), OSC_ASM_LOC_2BIT(sz, 14), OSC_ASM_LOC_2BIT(sz, 16), OSC_ASM_LOC_2BIT(sz, 18), OSC_ASM_LOC_2BIT(sz, 20), OSC_ASM_LOC_2BIT(sz, 22), OSC_ASM_LOC_2BIT(sz, 24), OSC_ASM_LOC_2BIT(sz, 26), OSC_ASM_LOC_2BIT(sz, 28), OSC_ASM_LOC_2BIT(sz, 30), OSC_ASM_LOC_2BIT(sz, 32), OSC_ASM_LOC_2BIT(sz, 34), OSC_ASM_LOC_2BIT(sz, 36), OSC_ASM_LOC_2BIT(sz, 38), OSC_ASM_LOC_2BIT(sz, 40), OSC_ASM_LOC_2BIT(sz, 42), OSC_ASM_LOC_2BIT(sz, 44), OSC_ASM_LOC_2BIT(sz, 46), OSC_ASM_LOC_2BIT(sz, 48), OSC_ASM_LOC_2BIT(sz, 50), OSC_ASM_LOC_2BIT(sz, 52), OSC_ASM_LOC_2BIT(sz, 54), OSC_ASM_LOC_2BIT(sz, 56), OSC_ASM_LOC_2BIT(sz, 58), OSC_ASM_LOC_2BIT(sz, 60), OSC_ASM_LOC_2BIT(sz, 62), OSC_ASM_LOC_LEN_END,


/* encoding N bytes with 4bits-per-loc */
#define OSC_ASM_LOC_1BYTE_4BIT(sz) OSC_ASM_LOC_LEN_START(1,4), OSC_ASM_LOC_4BIT(sz, 0), OSC_ASM_LOC_4BIT(sz, 4), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_2BYTE_4BIT(sz) OSC_ASM_LOC_LEN_START(2,4), OSC_ASM_LOC_4BIT(sz, 0), OSC_ASM_LOC_4BIT(sz, 4), OSC_ASM_LOC_4BIT(sz, 8), OSC_ASM_LOC_4BIT(sz, 12), OSC_ASM_LOC_LEN_END,

#define OSC_ASM_LOC_4BYTE_4BIT(sz) OSC_ASM_LOC_LEN_START(4,4), OSC_ASM_LOC_4BIT(sz, 0), OSC_ASM_LOC_4BIT(sz, 4), OSC_ASM_LOC_4BIT(sz, 8), OSC_ASM_LOC_4BIT(sz, 12), OSC_ASM_LOC_4BIT(sz, 16), OSC_ASM_LOC_4BIT(sz, 20), OSC_ASM_LOC_4BIT(sz, 24), OSC_ASM_LOC_4BIT(sz, 28), OSC_ASM_LOC_LEN_END,

/* the below is the default encoding: 8byte with 4bits-per-loc */
#define OSC_ASM_LOC_8BYTE_4BIT(sz) OSC_ASM_LOC_LEN_START(8,4), OSC_ASM_LOC_4BIT(sz, 0), OSC_ASM_LOC_4BIT(sz, 4), OSC_ASM_LOC_4BIT(sz, 8), OSC_ASM_LOC_4BIT(sz, 12), OSC_ASM_LOC_4BIT(sz, 16), OSC_ASM_LOC_4BIT(sz, 20), OSC_ASM_LOC_4BIT(sz, 24), OSC_ASM_LOC_4BIT(sz, 28), OSC_ASM_LOC_4BIT(sz, 32), OSC_ASM_LOC_4BIT(sz, 36), OSC_ASM_LOC_4BIT(sz, 40), OSC_ASM_LOC_4BIT(sz, 44), OSC_ASM_LOC_4BIT(sz, 48), OSC_ASM_LOC_4BIT(sz, 52), OSC_ASM_LOC_4BIT(sz, 56), OSC_ASM_LOC_4BIT(sz, 60), OSC_ASM_LOC_LEN_END,


/*
 * The below macro encodes a single constant.
 * The first parameter is sz, usually a 64bit or 8byte integer;
 * The second parameter is nbytes, which tells us how many bytes for this integer, only 1, 2, 4, 8 are supported;
 * The third parameter is mbits, which tells us how many bits for each .loc line, only 1, 2, 4 are supported.
 * The default value is nbytes=8 and mbits=4, which creates 16 .loc lines for a 64bit integer.
 */
#define OSC_ASM_LOC_NBYTE_MBIT(sz, nbytes, mbits) OSC_ASM_LOC_ ## nbytes ## BYTE ## _ ## mbits ## BIT(sz)

/* The default value for number of bytes for each constant: 8byte or 64bits */
#define OSC_ASM_LOC_NBYTE_DEFAULT 8

/*
 * The allowed value for OPENOSC_ASM_LOC_MBIT_DEFAULT is 1, 2, 4
 */
#ifdef OPENOSC_ASM_LOC_MBIT_DEFAULT
#define OSC_ASM_LOC_MBIT_DEFAULT OPENOSC_ASM_LOC_MBIT_DEFAULT
#else
/* The default value for number of bits of each .loc line: 4 bits */
#define OSC_ASM_LOC_MBIT_DEFAULT 4
#endif

/* We always convert all constants to 64bits value */
/* OSC_ASM_LOC_MBIT_DEFAULT can be configured with 1, 2, or 4 */
#if OSC_ASM_LOC_MBIT_DEFAULT == 4

#define OSC_DSTSIZE(sz) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 4)
#define OSC_DST_LEN_SIZE(sz, len) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 4) OSC_ASM_LOC_NBYTE_MBIT((long long)len, 8, 4)
#define OSC_DST_SRC_LEN_SIZE(sz, src_sz, len) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 4) OSC_ASM_LOC_NBYTE_MBIT((long long)src_sz, 8, 4) OSC_ASM_LOC_NBYTE_MBIT((long long)len, 8, 4)

#elif OSC_ASM_LOC_MBIT_DEFAULT == 2

#define OSC_DSTSIZE(sz) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 2)
#define OSC_DST_LEN_SIZE(sz, len) OSC_ASM_LOC_NBYTE_MBIT(sz, 8, 2) OSC_ASM_LOC_NBYTE_MBIT(len, 8, 2)
#define OSC_DST_SRC_LEN_SIZE(sz, src_sz, len) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 2) OSC_ASM_LOC_NBYTE_MBIT((long long)src_sz, 8, 2) OSC_ASM_LOC_NBYTE_MBIT((long long)len, 8, 2)

#else /* OSC_ASM_LOC_MBIT_DEFAULT == 1 */

#define OSC_DSTSIZE(sz) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 1)
#define OSC_DST_LEN_SIZE(sz, len) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 1) OSC_ASM_LOC_NBYTE_MBIT((long long)len, 8, 1)
#define OSC_DST_SRC_LEN_SIZE(sz, src_sz, len) OSC_ASM_LOC_NBYTE_MBIT((long long)sz, 8, 1) OSC_ASM_LOC_NBYTE_MBIT((long long)src_sz, 8, 1) OSC_ASM_LOC_NBYTE_MBIT((long long)len, 8, 1)

#endif


#else /* RTD_ASM_BYTE_METHOD */

/* define all 256 possible __asm__ .byte instructions for a single byte */
#define OSC_AB0     ({__asm__(".byte 0");})
#define OSC_AB1     ({__asm__(".byte 1");})
#define OSC_AB2     ({__asm__(".byte 2");})
#define OSC_AB3     ({__asm__(".byte 3");})
#define OSC_AB4     ({__asm__(".byte 4");})
#define OSC_AB5     ({__asm__(".byte 5");})
#define OSC_AB6     ({__asm__(".byte 6");})
#define OSC_AB7     ({__asm__(".byte 7");})
#define OSC_AB8     ({__asm__(".byte 8");})
#define OSC_AB9     ({__asm__(".byte 9");})
#define OSC_AB10     ({__asm__(".byte 10");})
#define OSC_AB11     ({__asm__(".byte 11");})
#define OSC_AB12     ({__asm__(".byte 12");})
#define OSC_AB13     ({__asm__(".byte 13");})
#define OSC_AB14     ({__asm__(".byte 14");})
#define OSC_AB15     ({__asm__(".byte 15");})
#define OSC_AB16     ({__asm__(".byte 16");})
#define OSC_AB17     ({__asm__(".byte 17");})
#define OSC_AB18     ({__asm__(".byte 18");})
#define OSC_AB19     ({__asm__(".byte 19");})
#define OSC_AB20     ({__asm__(".byte 20");})
#define OSC_AB21     ({__asm__(".byte 21");})
#define OSC_AB22     ({__asm__(".byte 22");})
#define OSC_AB23     ({__asm__(".byte 23");})
#define OSC_AB24     ({__asm__(".byte 24");})
#define OSC_AB25     ({__asm__(".byte 25");})
#define OSC_AB26     ({__asm__(".byte 26");})
#define OSC_AB27     ({__asm__(".byte 27");})
#define OSC_AB28     ({__asm__(".byte 28");})
#define OSC_AB29     ({__asm__(".byte 29");})
#define OSC_AB30     ({__asm__(".byte 30");})
#define OSC_AB31     ({__asm__(".byte 31");})
#define OSC_AB32     ({__asm__(".byte 32");})
#define OSC_AB33     ({__asm__(".byte 33");})
#define OSC_AB34     ({__asm__(".byte 34");})
#define OSC_AB35     ({__asm__(".byte 35");})
#define OSC_AB36     ({__asm__(".byte 36");})
#define OSC_AB37     ({__asm__(".byte 37");})
#define OSC_AB38     ({__asm__(".byte 38");})
#define OSC_AB39     ({__asm__(".byte 39");})
#define OSC_AB40     ({__asm__(".byte 40");})
#define OSC_AB41     ({__asm__(".byte 41");})
#define OSC_AB42     ({__asm__(".byte 42");})
#define OSC_AB43     ({__asm__(".byte 43");})
#define OSC_AB44     ({__asm__(".byte 44");})
#define OSC_AB45     ({__asm__(".byte 45");})
#define OSC_AB46     ({__asm__(".byte 46");})
#define OSC_AB47     ({__asm__(".byte 47");})
#define OSC_AB48     ({__asm__(".byte 48");})
#define OSC_AB49     ({__asm__(".byte 49");})
#define OSC_AB50     ({__asm__(".byte 50");})
#define OSC_AB51     ({__asm__(".byte 51");})
#define OSC_AB52     ({__asm__(".byte 52");})
#define OSC_AB53     ({__asm__(".byte 53");})
#define OSC_AB54     ({__asm__(".byte 54");})
#define OSC_AB55     ({__asm__(".byte 55");})
#define OSC_AB56     ({__asm__(".byte 56");})
#define OSC_AB57     ({__asm__(".byte 57");})
#define OSC_AB58     ({__asm__(".byte 58");})
#define OSC_AB59     ({__asm__(".byte 59");})
#define OSC_AB60     ({__asm__(".byte 60");})
#define OSC_AB61     ({__asm__(".byte 61");})
#define OSC_AB62     ({__asm__(".byte 62");})
#define OSC_AB63     ({__asm__(".byte 63");})
#define OSC_AB64     ({__asm__(".byte 64");})
#define OSC_AB65     ({__asm__(".byte 65");})
#define OSC_AB66     ({__asm__(".byte 66");})
#define OSC_AB67     ({__asm__(".byte 67");})
#define OSC_AB68     ({__asm__(".byte 68");})
#define OSC_AB69     ({__asm__(".byte 69");})
#define OSC_AB70     ({__asm__(".byte 70");})
#define OSC_AB71     ({__asm__(".byte 71");})
#define OSC_AB72     ({__asm__(".byte 72");})
#define OSC_AB73     ({__asm__(".byte 73");})
#define OSC_AB74     ({__asm__(".byte 74");})
#define OSC_AB75     ({__asm__(".byte 75");})
#define OSC_AB76     ({__asm__(".byte 76");})
#define OSC_AB77     ({__asm__(".byte 77");})
#define OSC_AB78     ({__asm__(".byte 78");})
#define OSC_AB79     ({__asm__(".byte 79");})
#define OSC_AB80     ({__asm__(".byte 80");})
#define OSC_AB81     ({__asm__(".byte 81");})
#define OSC_AB82     ({__asm__(".byte 82");})
#define OSC_AB83     ({__asm__(".byte 83");})
#define OSC_AB84     ({__asm__(".byte 84");})
#define OSC_AB85     ({__asm__(".byte 85");})
#define OSC_AB86     ({__asm__(".byte 86");})
#define OSC_AB87     ({__asm__(".byte 87");})
#define OSC_AB88     ({__asm__(".byte 88");})
#define OSC_AB89     ({__asm__(".byte 89");})
#define OSC_AB90     ({__asm__(".byte 90");})
#define OSC_AB91     ({__asm__(".byte 91");})
#define OSC_AB92     ({__asm__(".byte 92");})
#define OSC_AB93     ({__asm__(".byte 93");})
#define OSC_AB94     ({__asm__(".byte 94");})
#define OSC_AB95     ({__asm__(".byte 95");})
#define OSC_AB96     ({__asm__(".byte 96");})
#define OSC_AB97     ({__asm__(".byte 97");})
#define OSC_AB98     ({__asm__(".byte 98");})
#define OSC_AB99     ({__asm__(".byte 99");})
#define OSC_AB100     ({__asm__(".byte 100");})
#define OSC_AB101     ({__asm__(".byte 101");})
#define OSC_AB102     ({__asm__(".byte 102");})
#define OSC_AB103     ({__asm__(".byte 103");})
#define OSC_AB104     ({__asm__(".byte 104");})
#define OSC_AB105     ({__asm__(".byte 105");})
#define OSC_AB106     ({__asm__(".byte 106");})
#define OSC_AB107     ({__asm__(".byte 107");})
#define OSC_AB108     ({__asm__(".byte 108");})
#define OSC_AB109     ({__asm__(".byte 109");})
#define OSC_AB110     ({__asm__(".byte 110");})
#define OSC_AB111     ({__asm__(".byte 111");})
#define OSC_AB112     ({__asm__(".byte 112");})
#define OSC_AB113     ({__asm__(".byte 113");})
#define OSC_AB114     ({__asm__(".byte 114");})
#define OSC_AB115     ({__asm__(".byte 115");})
#define OSC_AB116     ({__asm__(".byte 116");})
#define OSC_AB117     ({__asm__(".byte 117");})
#define OSC_AB118     ({__asm__(".byte 118");})
#define OSC_AB119     ({__asm__(".byte 119");})
#define OSC_AB120     ({__asm__(".byte 120");})
#define OSC_AB121     ({__asm__(".byte 121");})
#define OSC_AB122     ({__asm__(".byte 122");})
#define OSC_AB123     ({__asm__(".byte 123");})
#define OSC_AB124     ({__asm__(".byte 124");})
#define OSC_AB125     ({__asm__(".byte 125");})
#define OSC_AB126     ({__asm__(".byte 126");})
#define OSC_AB127     ({__asm__(".byte 127");})
#define OSC_AB128     ({__asm__(".byte 128");})
#define OSC_AB129     ({__asm__(".byte 129");})
#define OSC_AB130     ({__asm__(".byte 130");})
#define OSC_AB131     ({__asm__(".byte 131");})
#define OSC_AB132     ({__asm__(".byte 132");})
#define OSC_AB133     ({__asm__(".byte 133");})
#define OSC_AB134     ({__asm__(".byte 134");})
#define OSC_AB135     ({__asm__(".byte 135");})
#define OSC_AB136     ({__asm__(".byte 136");})
#define OSC_AB137     ({__asm__(".byte 137");})
#define OSC_AB138     ({__asm__(".byte 138");})
#define OSC_AB139     ({__asm__(".byte 139");})
#define OSC_AB140     ({__asm__(".byte 140");})
#define OSC_AB141     ({__asm__(".byte 141");})
#define OSC_AB142     ({__asm__(".byte 142");})
#define OSC_AB143     ({__asm__(".byte 143");})
#define OSC_AB144     ({__asm__(".byte 144");})
#define OSC_AB145     ({__asm__(".byte 145");})
#define OSC_AB146     ({__asm__(".byte 146");})
#define OSC_AB147     ({__asm__(".byte 147");})
#define OSC_AB148     ({__asm__(".byte 148");})
#define OSC_AB149     ({__asm__(".byte 149");})
#define OSC_AB150     ({__asm__(".byte 150");})
#define OSC_AB151     ({__asm__(".byte 151");})
#define OSC_AB152     ({__asm__(".byte 152");})
#define OSC_AB153     ({__asm__(".byte 153");})
#define OSC_AB154     ({__asm__(".byte 154");})
#define OSC_AB155     ({__asm__(".byte 155");})
#define OSC_AB156     ({__asm__(".byte 156");})
#define OSC_AB157     ({__asm__(".byte 157");})
#define OSC_AB158     ({__asm__(".byte 158");})
#define OSC_AB159     ({__asm__(".byte 159");})
#define OSC_AB160     ({__asm__(".byte 160");})
#define OSC_AB161     ({__asm__(".byte 161");})
#define OSC_AB162     ({__asm__(".byte 162");})
#define OSC_AB163     ({__asm__(".byte 163");})
#define OSC_AB164     ({__asm__(".byte 164");})
#define OSC_AB165     ({__asm__(".byte 165");})
#define OSC_AB166     ({__asm__(".byte 166");})
#define OSC_AB167     ({__asm__(".byte 167");})
#define OSC_AB168     ({__asm__(".byte 168");})
#define OSC_AB169     ({__asm__(".byte 169");})
#define OSC_AB170     ({__asm__(".byte 170");})
#define OSC_AB171     ({__asm__(".byte 171");})
#define OSC_AB172     ({__asm__(".byte 172");})
#define OSC_AB173     ({__asm__(".byte 173");})
#define OSC_AB174     ({__asm__(".byte 174");})
#define OSC_AB175     ({__asm__(".byte 175");})
#define OSC_AB176     ({__asm__(".byte 176");})
#define OSC_AB177     ({__asm__(".byte 177");})
#define OSC_AB178     ({__asm__(".byte 178");})
#define OSC_AB179     ({__asm__(".byte 179");})
#define OSC_AB180     ({__asm__(".byte 180");})
#define OSC_AB181     ({__asm__(".byte 181");})
#define OSC_AB182     ({__asm__(".byte 182");})
#define OSC_AB183     ({__asm__(".byte 183");})
#define OSC_AB184     ({__asm__(".byte 184");})
#define OSC_AB185     ({__asm__(".byte 185");})
#define OSC_AB186     ({__asm__(".byte 186");})
#define OSC_AB187     ({__asm__(".byte 187");})
#define OSC_AB188     ({__asm__(".byte 188");})
#define OSC_AB189     ({__asm__(".byte 189");})
#define OSC_AB190     ({__asm__(".byte 190");})
#define OSC_AB191     ({__asm__(".byte 191");})
#define OSC_AB192     ({__asm__(".byte 192");})
#define OSC_AB193     ({__asm__(".byte 193");})
#define OSC_AB194     ({__asm__(".byte 194");})
#define OSC_AB195     ({__asm__(".byte 195");})
#define OSC_AB196     ({__asm__(".byte 196");})
#define OSC_AB197     ({__asm__(".byte 197");})
#define OSC_AB198     ({__asm__(".byte 198");})
#define OSC_AB199     ({__asm__(".byte 199");})
#define OSC_AB200     ({__asm__(".byte 200");})
#define OSC_AB201     ({__asm__(".byte 201");})
#define OSC_AB202     ({__asm__(".byte 202");})
#define OSC_AB203     ({__asm__(".byte 203");})
#define OSC_AB204     ({__asm__(".byte 204");})
#define OSC_AB205     ({__asm__(".byte 205");})
#define OSC_AB206     ({__asm__(".byte 206");})
#define OSC_AB207     ({__asm__(".byte 207");})
#define OSC_AB208     ({__asm__(".byte 208");})
#define OSC_AB209     ({__asm__(".byte 209");})
#define OSC_AB210     ({__asm__(".byte 210");})
#define OSC_AB211     ({__asm__(".byte 211");})
#define OSC_AB212     ({__asm__(".byte 212");})
#define OSC_AB213     ({__asm__(".byte 213");})
#define OSC_AB214     ({__asm__(".byte 214");})
#define OSC_AB215     ({__asm__(".byte 215");})
#define OSC_AB216     ({__asm__(".byte 216");})
#define OSC_AB217     ({__asm__(".byte 217");})
#define OSC_AB218     ({__asm__(".byte 218");})
#define OSC_AB219     ({__asm__(".byte 219");})
#define OSC_AB220     ({__asm__(".byte 220");})
#define OSC_AB221     ({__asm__(".byte 221");})
#define OSC_AB222     ({__asm__(".byte 222");})
#define OSC_AB223     ({__asm__(".byte 223");})
#define OSC_AB224     ({__asm__(".byte 224");})
#define OSC_AB225     ({__asm__(".byte 225");})
#define OSC_AB226     ({__asm__(".byte 226");})
#define OSC_AB227     ({__asm__(".byte 227");})
#define OSC_AB228     ({__asm__(".byte 228");})
#define OSC_AB229     ({__asm__(".byte 229");})
#define OSC_AB230     ({__asm__(".byte 230");})
#define OSC_AB231     ({__asm__(".byte 231");})
#define OSC_AB232     ({__asm__(".byte 232");})
#define OSC_AB233     ({__asm__(".byte 233");})
#define OSC_AB234     ({__asm__(".byte 234");})
#define OSC_AB235     ({__asm__(".byte 235");})
#define OSC_AB236     ({__asm__(".byte 236");})
#define OSC_AB237     ({__asm__(".byte 237");})
#define OSC_AB238     ({__asm__(".byte 238");})
#define OSC_AB239     ({__asm__(".byte 239");})
#define OSC_AB240     ({__asm__(".byte 240");})
#define OSC_AB241     ({__asm__(".byte 241");})
#define OSC_AB242     ({__asm__(".byte 242");})
#define OSC_AB243     ({__asm__(".byte 243");})
#define OSC_AB244     ({__asm__(".byte 244");})
#define OSC_AB245     ({__asm__(".byte 245");})
#define OSC_AB246     ({__asm__(".byte 246");})
#define OSC_AB247     ({__asm__(".byte 247");})
#define OSC_AB248     ({__asm__(".byte 248");})
#define OSC_AB249     ({__asm__(".byte 249");})
#define OSC_AB250     ({__asm__(".byte 250");})
#define OSC_AB251     ({__asm__(".byte 251");})
#define OSC_AB252     ({__asm__(".byte 252");})
#define OSC_AB253     ({__asm__(".byte 253");})
#define OSC_AB254     ({__asm__(".byte 254");})
#define OSC_AB255     ({__asm__(".byte 255");})


/* Select the correct OSC_ABxxx instruction for a value of single byte */
#define OSC_ASMBYTE(sz) ((sz) & 0x80) ? (((sz) & 0x40) ? (((sz) & 0x20) ? (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB255 : OSC_AB254) : (((sz) & 0x1) ? OSC_AB253 : OSC_AB252)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB251 : OSC_AB250) : (((sz) & 0x1) ? OSC_AB249 : OSC_AB248))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB247 : OSC_AB246) : (((sz) & 0x1) ? OSC_AB245 : OSC_AB244)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB243 : OSC_AB242) : (((sz) & 0x1) ? OSC_AB241 : OSC_AB240)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB239 : OSC_AB238) : (((sz) & 0x1) ? OSC_AB237 : OSC_AB236)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB235 : OSC_AB234) : (((sz) & 0x1) ? OSC_AB233 : OSC_AB232))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB231 : OSC_AB230) : (((sz) & 0x1) ? OSC_AB229 : OSC_AB228)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB227 : OSC_AB226) : (((sz) & 0x1) ? OSC_AB225 : OSC_AB224))))) : (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB223 : OSC_AB222) : (((sz) & 0x1) ? OSC_AB221 : OSC_AB220)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB219 : OSC_AB218) : (((sz) & 0x1) ? OSC_AB217 : OSC_AB216))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB215 : OSC_AB214) : (((sz) & 0x1) ? OSC_AB213 : OSC_AB212)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB211 : OSC_AB210) : (((sz) & 0x1) ? OSC_AB209 : OSC_AB208)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB207 : OSC_AB206) : (((sz) & 0x1) ? OSC_AB205 : OSC_AB204)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB203 : OSC_AB202) : (((sz) & 0x1) ? OSC_AB201 : OSC_AB200))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB199 : OSC_AB198) : (((sz) & 0x1) ? OSC_AB197 : OSC_AB196)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB195 : OSC_AB194) : (((sz) & 0x1) ? OSC_AB193 : OSC_AB192)))))) : (((sz) & 0x20) ? (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB191 : OSC_AB190) : (((sz) & 0x1) ? OSC_AB189 : OSC_AB188)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB187 : OSC_AB186) : (((sz) & 0x1) ? OSC_AB185 : OSC_AB184))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB183 : OSC_AB182) : (((sz) & 0x1) ? OSC_AB181 : OSC_AB180)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB179 : OSC_AB178) : (((sz) & 0x1) ? OSC_AB177 : OSC_AB176)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB175 : OSC_AB174) : (((sz) & 0x1) ? OSC_AB173 : OSC_AB172)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB171 : OSC_AB170) : (((sz) & 0x1) ? OSC_AB169 : OSC_AB168))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB167 : OSC_AB166) : (((sz) & 0x1) ? OSC_AB165 : OSC_AB164)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB163 : OSC_AB162) : (((sz) & 0x1) ? OSC_AB161 : OSC_AB160))))) : (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB159 : OSC_AB158) : (((sz) & 0x1) ? OSC_AB157 : OSC_AB156)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB155 : OSC_AB154) : (((sz) & 0x1) ? OSC_AB153 : OSC_AB152))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB151 : OSC_AB150) : (((sz) & 0x1) ? OSC_AB149 : OSC_AB148)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB147 : OSC_AB146) : (((sz) & 0x1) ? OSC_AB145 : OSC_AB144)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB143 : OSC_AB142) : (((sz) & 0x1) ? OSC_AB141 : OSC_AB140)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB139 : OSC_AB138) : (((sz) & 0x1) ? OSC_AB137 : OSC_AB136))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB135 : OSC_AB134) : (((sz) & 0x1) ? OSC_AB133 : OSC_AB132)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB131 : OSC_AB130) : (((sz) & 0x1) ? OSC_AB129 : OSC_AB128))))))) : (((sz) & 0x40) ? (((sz) & 0x20) ? (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB127 : OSC_AB126) : (((sz) & 0x1) ? OSC_AB125 : OSC_AB124)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB123 : OSC_AB122) : (((sz) & 0x1) ? OSC_AB121 : OSC_AB120))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB119 : OSC_AB118) : (((sz) & 0x1) ? OSC_AB117 : OSC_AB116)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB115 : OSC_AB114) : (((sz) & 0x1) ? OSC_AB113 : OSC_AB112)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB111 : OSC_AB110) : (((sz) & 0x1) ? OSC_AB109 : OSC_AB108)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB107 : OSC_AB106) : (((sz) & 0x1) ? OSC_AB105 : OSC_AB104))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB103 : OSC_AB102) : (((sz) & 0x1) ? OSC_AB101 : OSC_AB100)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB99 : OSC_AB98) : (((sz) & 0x1) ? OSC_AB97 : OSC_AB96))))) : (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB95 : OSC_AB94) : (((sz) & 0x1) ? OSC_AB93 : OSC_AB92)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB91 : OSC_AB90) : (((sz) & 0x1) ? OSC_AB89 : OSC_AB88))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB87 : OSC_AB86) : (((sz) & 0x1) ? OSC_AB85 : OSC_AB84)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB83 : OSC_AB82) : (((sz) & 0x1) ? OSC_AB81 : OSC_AB80)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB79 : OSC_AB78) : (((sz) & 0x1) ? OSC_AB77 : OSC_AB76)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB75 : OSC_AB74) : (((sz) & 0x1) ? OSC_AB73 : OSC_AB72))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB71 : OSC_AB70) : (((sz) & 0x1) ? OSC_AB69 : OSC_AB68)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB67 : OSC_AB66) : (((sz) & 0x1) ? OSC_AB65 : OSC_AB64)))))) : (((sz) & 0x20) ? (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB63 : OSC_AB62) : (((sz) & 0x1) ? OSC_AB61 : OSC_AB60)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB59 : OSC_AB58) : (((sz) & 0x1) ? OSC_AB57 : OSC_AB56))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB55 : OSC_AB54) : (((sz) & 0x1) ? OSC_AB53 : OSC_AB52)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB51 : OSC_AB50) : (((sz) & 0x1) ? OSC_AB49 : OSC_AB48)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB47 : OSC_AB46) : (((sz) & 0x1) ? OSC_AB45 : OSC_AB44)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB43 : OSC_AB42) : (((sz) & 0x1) ? OSC_AB41 : OSC_AB40))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB39 : OSC_AB38) : (((sz) & 0x1) ? OSC_AB37 : OSC_AB36)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB35 : OSC_AB34) : (((sz) & 0x1) ? OSC_AB33 : OSC_AB32))))) : (((sz) & 0x10) ? (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB31 : OSC_AB30) : (((sz) & 0x1) ? OSC_AB29 : OSC_AB28)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB27 : OSC_AB26) : (((sz) & 0x1) ? OSC_AB25 : OSC_AB24))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB23 : OSC_AB22) : (((sz) & 0x1) ? OSC_AB21 : OSC_AB20)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB19 : OSC_AB18) : (((sz) & 0x1) ? OSC_AB17 : OSC_AB16)))) : (((sz) & 0x8) ? (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB15 : OSC_AB14) : (((sz) & 0x1) ? OSC_AB13 : OSC_AB12)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB11 : OSC_AB10) : (((sz) & 0x1) ? OSC_AB9 : OSC_AB8))) : (((sz) & 0x4) ? (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB7 : OSC_AB6) : (((sz) & 0x1) ? OSC_AB5 : OSC_AB4)) : (((sz) & 0x2) ? (((sz) & 0x1) ? OSC_AB3 : OSC_AB2) : (((sz) & 0x1) ? OSC_AB1 : OSC_AB0)))))))

/* Insert 8 bytes of buffer size */
#define OSC_DSTSIZE3(sz)  OSC_ASMBYTE((sz >> 56) & 0xFF), OSC_ASMBYTE((sz >> 48) & 0xFF), OSC_ASMBYTE((sz >> 40) & 0xFF), OSC_ASMBYTE((sz >> 32) & 0xFF), OSC_ASMBYTE((sz >> 24) & 0xFF), OSC_ASMBYTE((sz >> 16) & 0xFF), OSC_ASMBYTE((sz >> 8) & 0xFF), OSC_ASMBYTE(sz & 0xFF)

/* Cast to 8 bytes if not. Note sz can be -1 */
#define OSC_DSTSIZE2(sz) OSC_DSTSIZE3((sizeof(size_t)==8?((long long)sz):(sizeof(int)==sizeof(size_t)?((long long)(signed)sz):(sizeof(long)==sizeof(size_t)?((long long)(signed long)sz):(long long)sz))))

#define OSC_DSTSIZE_MAGIC ".byte 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee\n"
#define OSC_DSTSIZE_MAGIC2 ".byte 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xef\n"

/* The 8-byte buffer size is prefixed with 8-byte magic word, and suffixed with 8-byte magic word */
#define OSC_DSTSIZE(sz)  ({__asm__(OSC_JUMPOVER OSC_DSTSIZE_MAGIC);}), OSC_DSTSIZE2(sz), ({__asm__(OSC_DSTSIZE_MAGIC2 OSC_JUMPLABEL);}),

/* Destination buffer size and copy length */
#define OSC_DST_LEN_SIZE(sz, len)  ({__asm__(OSC_JUMPOVER OSC_DSTSIZE_MAGIC);}), OSC_DSTSIZE2(sz), OSC_DSTSIZE2(len), ({__asm__(OSC_DSTSIZE_MAGIC2 OSC_JUMPLABEL);}),

/* Destination buffer size, source buffer size, and copy length */
#define OSC_DST_SRC_LEN_SIZE(sz, src_sz, len)  ({__asm__(OSC_JUMPOVER OSC_DSTSIZE_MAGIC);}), OSC_DSTSIZE2(sz), OSC_DSTSIZE2(src_sz), OSC_DSTSIZE2(len), ({__asm__(OSC_DSTSIZE_MAGIC2 OSC_JUMPLABEL);}),

#endif /* (RTD_OSC_METRIC_METHOD == RTD_ASM_LOC_METHOD) */

#else

/* If this feature is not enabled, then the macro is empty */
#define OSC_DSTSIZE(sz)
#define OSC_DST_LEN_SIZE(sz, len)
#define OSC_DST_SRC_LEN_SIZE(sz, src_sz, len)

#endif  /* OPENOSC_METRIC_OBJSIZE_ENABLED */

#endif  /* __OPENOSC_METRIC_OBJSIZE_H__ */
