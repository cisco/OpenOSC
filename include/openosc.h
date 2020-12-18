/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#ifndef __OPENOSC_H__
#define __OPENOSC_H__

#include "openosc_header_metric.h"

/* define the object size checking type in builtin function */
#define OSC_OBJECT_SIZE_CHECK_0 0
#define OSC_OBJECT_SIZE_CHECK_1 1

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Source over-read is enabled by default, but can be disabled */
#ifndef OPENOSC_SRC_OVERREAD_DISABLE
#define _OPENOSC_SRC_OVERREAD_ENABLED
#endif

/*
 * There are two methods to remap a function to openosc_* function:
 *   1. The function redirect via ASM-label mechanism.
 *   2. The function macro redefine method.
 * The ASM-label redirect method is the default.
 * New mapping method can be added in future as necessary.
 */
#define OPENOSC_ASM_LABEL_REDIRECT_METHOD    1
#define OPENOSC_FUNC_MACRO_REDEFINE_METHOD   2

/* -DOPENOSC_MM=x can be used by a component to pick the mapping method */
/* #define OPENOSC_MM OPENOSC_FUNC_MACRO_REDEFINE_METHOD */
#ifdef OPENOSC_MM
#define OPENOSC_MAPPING_METHOD OPENOSC_MM
#else
#define OPENOSC_MAPPING_METHOD OPENOSC_ASM_LABEL_REDIRECT_METHOD
#endif

/**
 * If the below flag is defined, then all function remapping code will be disabled.
 * However, file-level magic words in openosc_header_metric.h and openosc_nomap_metric.h are kept.
 */
#ifdef OPENOSC_FUNCTION_MAPPING_DISABLE
#undef OPENOSC_METRIC_FEATURE_ENABLED
#define NO_OBJECT_SIZE_CHECKING
#endif

#ifdef OPENOSC_SKIP_CSTRING_HEADER
#ifdef __cplusplus
#if OPENOSC_MAPPING_METHOD == OPENOSC_FUNC_MACRO_REDEFINE_METHOD || defined OPENOSC_METRIC_ONLY_MODE
/* define the below macro to avoid including <cstring> header, which #undef >10 memcpy/strcpy functions */
#ifndef _GLIBCXX_CSTRING
#define _GLIBCXX_CSTRING 2
#endif
#endif
#endif
#endif


#ifdef NO_OBJECT_SIZE_CHECKING
#pragma message ("OSC-WARN-DISABLED: OpenOSC disabled due to NO_OBJECT_SIZE_CHECKING, contact OpenOSC package owner for guidance")
#elif defined __ASSEMBLER__
#pragma message ("OSC-WARN-ASM: OpenOSC disabled due to __ASSEMBLER__, contact OpenOSC package owner for guidance")
#elif defined OPENOSC_METRIC_ONLY_MODE
#pragma message ("OSC-WARN-METRICONLY: OpenOSC disabled due to METRIC_ONLY_MODE, contact OpenOSC package owner for guidance")
#include "openosc_metric_only.h"
#elif !defined  __OPTIMIZE__
/* #error "OSC-ERR-NOOPT: OpenOSC disabled due to NO OPTIMIZATION, contact OpenOSC package owner for guidance" */
#pragma message ("OSC-ERR-NOOPT: OpenOSC disabled due to NO OPTIMIZATION, contact OpenOSC package owner for guidance")
#include "openosc_nomap.h"
#elif defined __NO_INLINE__
#pragma message ("OSC-WARN-NOINLINE: OpenOSC disabled due to __NO_INLINE__, contact OpenOSC package owner for guidance")
#include "openosc_nomap.h"
#elif defined _FORTIFY_SOURCE && !defined OPENOSC_FORTIFY_SOURCE_FORCE_OFF
#pragma message ("OSC-WARN-FORTIFY: OpenOSC disabled due to _FORTIFY_SOURCE, contact OpenOSC package owner for guidance")
#include "openosc_nomap.h"
#elif defined OSC_ASM
#pragma message ("OSC-WARN-ASM: OpenOSC disabled due to OSC_ASM, contact OpenOSC package owner for guidance")
#include "openosc_nomap.h"
#elif defined __STRICT_ANSI__ && !defined OPENOSC_STRICT_ANSI_FORCE_ON
#pragma message ("OSC-WARN-ANSI: OpenOSC disabled due to __STRICT_ANSI__, contact OpenOSC package owner for guidance")
#include "openosc_nomap.h"
#else

#if defined _FORTIFY_SOURCE && defined OPENOSC_FORTIFY_SOURCE_FORCE_OFF
#undef _FORTIFY_SOURCE
#ifndef _OPENOSC_FORCEENABLE_EMIT_WARNING_DISABLE
#pragma message ("OSC-WARN-FORTIFY: OpenOSC is forced to be enabled and _FORTIFY_SOURCE is disabled when _FORTIFY_SOURCE is defined, contact OpenOSC package owner for guidance")
#endif
#endif

#if defined __STRICT_ANSI__ && defined OPENOSC_STRICT_ANSI_FORCE_ON
#ifndef _OPENOSC_FORCEENABLE_EMIT_WARNING_DISABLE
#pragma message ("OSC-WARN-ANSI: OpenOSC is forced to be enabled when __STRICT_ANSI__ is defined, contact OpenOSC package owner for guidance")
#endif
#endif

/* This define shows OSC enabled */
#define OSC_OBJECT_SIZE_CHECK 1

/*
 * Flags to select compile-time check method
 * 
 * Different compilers support different way to report error at compiling time.
 * OSC_ASSERT_USE_ERR_ATTR:
 *   Use __attribute__ error to report error
 * OSC_ASSERT_USE_BUILTIN:
 *   Use __builtin___xxx_chk to report error. This method MUST not be used in
 *   final production code as it introduce abort() call into the code. It can
 *   be used for the initial finding of static buffer overflow if the compiler
 *   doesn't support OSC_ASSERT_USE_ERR_ATTR
 * OSC_ASSERT_USE_RUNTIME_CHK:
 *   Use runtime check for buffer overflow only. This method will NOT catch
 *   any static buffer overflow at compile time.
 * OSC_ASSERT_USE_NONE:
 *   Use the original libc/safec functions. This method will NOT catch
 *   any static buffer overflow at compile time.
 */
#define OSC_ASSERT_USE_ERR_ATTR    0
#define OSC_ASSERT_USE_BUILTIN     1 /* DO NOT use in production */
#define OSC_ASSERT_USE_RUNTIME_CHK 2
#define OSC_ASSERT_USE_NONE        3 /* DO NOT use in production */

/*
 * Flags to select run-time check method
 */ 
#define OSC_RUNTIME_USE_LIBOSC     0 /* Default Runtime check */
#define OSC_RUNTIME_NO_LIBOSC      1 /* Use libc/safec when libosc is unavailable */

/**********************************************************************************
 **********************************************************************************
 * DO NOT CHANGE OSC_COMPILE_CHK OR OSC_RUNTIME_CHK flags
 * Please contact csdl-rtd-dev@cisco.com for any questions regarding these settings
 **********************************************************************************/
/*
 * OPENOSC_METRIC_ONLY_MODE is a special mode which disables OSC remapping.
 */
#ifdef OPENOSC_METRIC_ONLY_MODE

#define OSC_COMPILE_CHK OSC_ASSERT_USE_NONE
#define OSC_RUNTIME_CHK OSC_RUNTIME_NO_LIBOSC

#else

/*
 * Detect the compiler and select the best compile-time check method.
 */
#if __ICC
#define OSC_COMPILE_CHK OSC_ASSERT_USE_RUNTIME_CHK
#elif __clang__
#define OSC_COMPILE_CHK OSC_ASSERT_USE_ERR_ATTR
#elif __GNUC__
#define OSC_COMPILE_CHK OSC_ASSERT_USE_ERR_ATTR
#else
#error "Unsupported compiler detected, contact OpenOSC package owner for guidance"
#endif

/*
 * Runtime check should always be using libosc
 */
#define OSC_RUNTIME_CHK OSC_RUNTIME_USE_LIBOSC

#endif /* OPENOSC_METRIC_ONLY_MODE */

/**********************************************************************************
 * DO NOT CHANGE OSC_COMPILE_CHK OR OSC_RUNTIME_CHK flags
 * Please contact csdl-rtd-dev@cisco.com for any questions regarding these settings
 **********************************************************************************
 **********************************************************************************/

#include "openosc_map.h"

#ifdef HAS_SAFEC
#include "openosc_safec_map.h"
#endif

#endif /* NO_OBJECT_SIZE_CHECKING */

/*
 * Let's pretend that we never include features.h header 
 * so that users can still define their features by themselves.
 */
#undef _FEATURES_H

#endif /* __OPEOSC_H__ */
