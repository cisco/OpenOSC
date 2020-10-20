/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_HEADER_METRIC_H__
#define __OPENOSC_HEADER_METRIC_H__

/* OSC is not applicable to assembly language .S files */
#ifndef __ASSEMBLER__

/*
 * !!!WARNING!!!
 * Uncommenting the below line will turn on OSC-METRIC feature.
 * This feature inserts magic words into binary files for OSC function calls.
 * Make sure you understand the impact before enabling this feature.
 */
/* #define OPENOSC_METRIC_FEATURE_ENABLED */

/*
 * !!!WARNING!!!
 * Uncommenting the below line will turn on OSC-METRIC-ONLY mode.
 * This will insert magic words without any real OSC function remappings.
 * This mode helps quick image build on a new platform to get OSC Metrics.
 */
/* #define OPENOSC_METRIC_ONLY_MODE */
#ifdef OPENOSC_METRIC_ONLY_MODE
#define OPENOSC_METRIC_FEATURE_ENABLED
#endif

/* Always enable OSC Header Metric unless explicitly disabled */
#ifndef OPENOSC_HEADER_METRIC_FEATURE_DISABLE
#define OPENOSC_HEADER_METRIC_FEATURE_ENABLED
#endif

#ifdef OPENOSC_HEADER_METRIC_FEATURE_ENABLED
/*
 * There are two OSC metric methods:
 *  1. ASM(".byte 0x80 0x81") approach. this is also called embedded watermarks.
 *  2. ASM(".loc 1 0x8081") approach. this uses DWARF debugging.
 * The DWARF .loc method is the default.
 * New OSC-METRICS method can be added in future as necessary.
 */
#define RTD_ASM_BYTE_METHOD 1
#define RTD_ASM_LOC_METHOD 2

/* -DOPENOSC_METRIC_METHOD=x can be used by a component to pick the method */
/* #define OPENOSC_METRIC_METHOD RTD_ASM_BYTE_METHOD */
#ifdef OPENOSC_METRIC_METHOD
#define RTD_OSC_METRIC_METHOD OPENOSC_METRIC_METHOD
#else
#define RTD_OSC_METRIC_METHOD RTD_ASM_LOC_METHOD
#endif

#if (RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD)

/* Automatically set appropriate architecture based on predefined flags */
#if defined __x86_64__ || defined __i386__ || defined __amd64__ || defined __X86__ || defined __X86_64__
#define OSC_ARCH_X86
#elif defined __arm__ || defined __aarch64__ || defined __arm || defined _M_ARM
#define OSC_ARCH_ARM
#elif defined __mips__ || defined mips || defined __MIPS__ || defined __mips
#define OSC_ARCH_MIPS
#elif defined __ppc__ || defined __PPC__ || defined __PPC || defined _ARCH_PPC || defined __powerpc__ || defined __ppc64__ || defined __powerpc64__
#define OSC_ARCH_PPC
#endif

/* OSC_ARCH_* needs to be defined to get working binary file */

#ifdef OSC_ARCH_X86
/* for x86 32bit and 64bit arch */
#define OSC_JUMPOVER  "jmp 0f\n"
#define OSC_JUMPLABEL  "0:\n"
#elif defined(OSC_ARCH_X86_32)
/* for x86 32bit arch */
#define OSC_JUMPOVER  ".byte 0xeb, 0x08\n"
#define OSC_JUMPLABEL
#elif defined(OSC_ARCH_ARM)
/* for ARM 32bit and 64bit arch */
#define OSC_JUMPOVER  "b 0f\n"
#define OSC_JUMPLABEL  "0:\n"
#elif defined(OSC_ARCH_MIPS)
/* for MIPS 32bit and 64bit arch */
#define OSC_JUMPOVER  "b 0f\n"
#define OSC_JUMPLABEL  "0:\n"
#elif defined(OSC_ARCH_PPC)
/* for PowerPC 32bit and 64bit arch */
#define OSC_JUMPOVER  "b 0f\n"
#define OSC_JUMPLABEL  "0:\n"
#else
/* for unknown arch or unsupported arch */
#define OSC_JUMPOVER
#define OSC_JUMPLABEL
#endif

#endif   /* RTD_OSC_METRIC_METHOD == RTD_ASM_BYTE_METHOD */


/* always insert a magic word if osc_header.h is included */
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_HEADER_H_INCLUDED 0x80818d8e80818d8e
#else
#define MAGIC_OSC_HEADER_H_INCLUDED 0x8e8d81808e8d8180
#endif
long long int __attribute__((weak)) rtd_osc_header_h_included_int = MAGIC_OSC_HEADER_H_INCLUDED;

/*
 * The below useful info can be inserted into binary file.
 * If you don't need them or concerned with file size, then you can comment the below.
 */
#ifndef OPENOSC_METRIC_USEFUL_INFO_DISABLE
#define OPENOSC_METRIC_USEFUL_INFO
#endif

#ifdef OPENOSC_METRIC_USEFUL_INFO

#if __ICC
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_COMPILER 0x97cfa25a9fb39d01
#else
#define MAGIC_OSC_COMPILER 0x019db39f5aa2cf97
#endif
#elif __clang__
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_COMPILER 0x97cfa25a9fb39d02
#else
#define MAGIC_OSC_COMPILER 0x029db39f5aa2cf97
#endif
#elif __GNUC__
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_COMPILER 0x97cfa25a9fb39d03
#else
#define MAGIC_OSC_COMPILER 0x039db39f5aa2cf97
#endif
#else
#if defined __BIG_ENDIAN__ || defined __BIG_ENDIAN || (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MAGIC_OSC_COMPILER 0x97cfa25a9fb39d04
#else
#define MAGIC_OSC_COMPILER 0x049db39f5aa2cf97
#endif
#endif

/* Which compiler gcc/icc/clang, etc */
long long int __attribute__((weak)) rtd_osc_compiler_int = MAGIC_OSC_COMPILER;

#ifdef OPENOSC_METRIC_COMPILER_CCVERSION
/* Compiler version can be very useful */
const char __attribute__((weak)) *rtd_osc_metric_cc_ver = "OSCMETRIC_CCVER_BEG:" __VERSION__ ":OSCMETRIC_CCVER_END" ;
#endif

#endif  /* OPENOSC_METRIC_USEFUL_INFO */

#endif    /* OPENOSC_HEADER_METRIC_FEATURE_ENABLED */

#endif /* __ASSEMBLER__ */

#endif  /* __OPENOSC_HEADER_METRIC_H__ */
