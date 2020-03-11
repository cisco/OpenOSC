/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_SAFEC_MAP_H__
#define __OPENOSC_SAFEC_MAP_H__

/* osc_safec_map.h and osc_safec_nomap.h are mutually exclusive */
#ifndef __OPENOSC_SAFEC_NOMAP_H__

#include "openosc_safec_map_metric.h"
#include "openosc_extern.h"

/*
 * Define Runtime check macros
 */
#if (OSC_RUNTIME_CHK == OSC_RUNTIME_USE_LIBOSC)
#define OSC_RUNTIME_CHECK_memcmp_s() (__openosc_memcmp_s_to_buf(_sz, s1, s1max, s2, n, diff))
#define OSC_RUNTIME_CHECK_memcpy_s() (__openosc_memcpy_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strcat_s() (__openosc_strcat_s_to_buf(_sz, dest, dmax, src))
#define OSC_RUNTIME_CHECK_strcmp_s() (__openosc_strcmp_s_to_buf(_sz, s1, s1max, s2, indicator))
#define OSC_RUNTIME_CHECK_strcpy_s() (__openosc_strcpy_s_to_buf(_sz, dest, dmax, src))
#define OSC_RUNTIME_CHECK_strncat_s()(__openosc_strncat_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strncpy_s()(__openosc_strncpy_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strnlen_s()(__openosc_strnlen_s_to_buf(_sz, s, maxsize))
#define OSC_RUNTIME_CHECK_strstr_s() (__openosc_strstr_s_to_buf(_sz, s1, s1max, s2, s2max, substring))
#else
#define OSC_RUNTIME_CHECK_memcmp_s() (memcmp_s(s1, s1max, s2, n, diff))
#define OSC_RUNTIME_CHECK_memcpy_s() (memcpy_s(dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strcat_s() (strcat_s(dest, dmax, src))
#define OSC_RUNTIME_CHECK_strcmp_s() (strcmp_s(s1, s1max, s2, indicator))
#define OSC_RUNTIME_CHECK_strcpy_s() (strcpy_s(dest, dmax, src))
#define OSC_RUNTIME_CHECK_strncat_s()(strncat_s(dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strncpy_s()(strncpy_s(dest, dmax, src, n))
#define OSC_RUNTIME_CHECK_strnlen_s()(strnlen_s(s, maxsize))
#define OSC_RUNTIME_CHECK_strstr_s() (strstr_s(s1, s1max, s2, s2max, substring))
#endif /* OSC_RUNTIME_CHK */

/*
 * Define compile-time static assert to report buffer overflow
 * detected by OSC
 *
 * Since support for compile-time error reporting are compiler dependent,
 * there will be multiple definitions of these macros. To select a specific
 * implemetaton, define the appropriate flag within this header file. For
 * the build enviroment that use multiple compilers, the flag can be defined
 * on the command line using the "-D" switch.
 *
 * Note: OSC_ASSERT_USE_BUILTIN should only be used for compile-time check
 * only. It must NOT be used in release code or a risk of abort() call get
 * inserted into production image by the compiler.
 */
#if (OSC_COMPILE_CHK == OSC_ASSERT_USE_ERR_ATTR)
extern int __attribute__((error("Compiler Assertion: memcmp_s s1max indexes beyond s1"))) \
 osc_compile_check_memcmp_s(void);
#define OSC_ASSERT_memcmp_s() ({osc_compile_check_memcmp_s(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: memcpy_s dmax could overflow dest"))) \
 osc_compile_check_memcpy_s(void);
#define OSC_ASSERT_memcpy_s() ({osc_compile_check_memcpy_s(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strcat_s dmax could overflow dest"))) \
 osc_compile_check_strcat_s(void);
#define OSC_ASSERT_strcat_s() ({osc_compile_check_strcat_s(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strcmp_s s1max indexes beyond s1"))) \
 osc_compile_check_strcmp_s(void);
#define OSC_ASSERT_strcmp_s() ({osc_compile_check_strcmp_s(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strcpy_s dmax could overflow dest"))) \
 osc_compile_check_strcpy_s(void);
#define OSC_ASSERT_strcpy_s() ({osc_compile_check_strcpy_s(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncat_s n indexes beyond dest"))) \
 osc_compile_check_strncat_s1(void);
#define OSC_ASSERT_strncat_s1() ({osc_compile_check_strncat_s1(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncat_s dmax could overflow dest"))) \
 osc_compile_check_strncat_s2(void);
#define OSC_ASSERT_strncat_s2() ({osc_compile_check_strncat_s2(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncat_s dmax equal to n"))) \
 safec_compile_check_strncat_s_equal(void);
#define  SAFEC_ASSERT_strncat_s_equal() ({safec_compile_check_strncat_s_equal(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncat_s dmax less than n"))) \
 safec_compile_check_strncat_s_less(void);
#define  SAFEC_ASSERT_strncat_s_less() ({safec_compile_check_strncat_s_less(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncpy_s n indexes beyond dest"))) \
 osc_compile_check_strncpy_s1(void);
#define OSC_ASSERT_strncpy_s1() ({osc_compile_check_strncpy_s1(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncpy_s dmax could overflow dest"))) \
 osc_compile_check_strncpy_s2(void);
#define OSC_ASSERT_strncpy_s2() ({osc_compile_check_strncpy_s2(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncpy_s dmax equal to n"))) \
 safec_compile_check_strncpy_s_equal(void);
#define  SAFEC_ASSERT_strncpy_s_equal() ({safec_compile_check_strncpy_s_equal(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strncpy_s dmax less than n"))) \
 safec_compile_check_strncpy_s_less(void);
#define  SAFEC_ASSERT_strncpy_s_less() ({safec_compile_check_strncpy_s_less(), (errno_t)0;})

extern int __attribute__((error("Compiler Assertion: strnlen_s maxsize indexes beyond s"))) \
 osc_compile_check_strnlen_s(void);
#define OSC_ASSERT_strnlen_s() ({osc_compile_check_strnlen_s(), (size_t)0;})

extern int __attribute__((error("Compiler Assertion: strstr_s s1max indexes beyond s1"))) \
 osc_compile_check_strstr_s(void);
#define OSC_ASSERT_strstr_s() ({osc_compile_check_strstr_s(), (errno_t)0;})
#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_BUILTIN) || (OSC_COMPILE_CHK == OSC_ASSERT_USE_RUNTIME_CHK)
/*
 * For safeC, there is no compiler built-in check so if OSC_COMPILE_CHK is set
 * to OSC_ASSERT_USE_BUILTIN, just use the runtime check
 */
#define OSC_ASSERT_memcmp_s() (__openosc_memcmp_s_to_buf(_sz, s1, s1max, s2, n, diff))
#define OSC_ASSERT_memcpy_s() (__openosc_memcpy_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_ASSERT_strcat_s() (__openosc_strcat_s_to_buf(_sz, dest, dmax, src))
#define OSC_ASSERT_strcmp_s() (__openosc_strcmp_s_to_buf(_sz, s1, s1max, s2, indicator))
#define OSC_ASSERT_strcpy_s() (__openosc_strcpy_s_to_buf(_sz, dest, dmax, src))
#define OSC_ASSERT_strncat_s1() (__openosc_strncat_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_ASSERT_strncat_s2() (__openosc_strncat_s_to_buf(_sz, dest, dmax, src, n))
#define SAFEC_ASSERT_strncat_s_equal() (__openosc_strncat_s_to_buf(_sz, dest, dmax, src, n))
#define SAFEC_ASSERT_strncat_s_less() (__openosc_strncat_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_ASSERT_strncpy_s1() (__openosc_strncpy_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_ASSERT_strncpy_s2() (__openosc_strncpy_s_to_buf(_sz, dest, dmax, src, n))
#define SAFEC_ASSERT_strncpy_s_equal() (__openosc_strncpy_s_to_buf(_sz, dest, dmax, src, n))
#define SAFEC_ASSERT_strncpy_s_less() (__openosc_strncpy_s_to_buf(_sz, dest, dmax, src, n))
#define OSC_ASSERT_strnlen_s() (__openosc_strnlen_s_to_buf(_sz, s, maxsize))
#define OSC_ASSERT_strstr_s() (__openosc_strstr_s_to_buf(_sz, s1, s1max, s2, s2max, substring))
#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_NONE)
/* No compile time check, use original libc/safec function */
#define OSC_ASSERT_memcmp_s()   (memcmp_s(s1, s1max, s2, n, diff))
#define OSC_ASSERT_memcpy_s()   (memcpy_s(dest, dmax, src, n))
#define OSC_ASSERT_strcat_s()   (strcat_s(dest, dmax, src))
#define OSC_ASSERT_strcmp_s()   (strcmp_s(s1, s1max, s2, indicator))
#define OSC_ASSERT_strcpy_s()   (strcpy_s(dest, dmax, src))
#define OSC_ASSERT_strncat_s1() (strncat_s(dest, dmax, src, n))
#define OSC_ASSERT_strncat_s2() (strncat_s(dest, dmax, src, n))
#define SAFEC_ASSERT_strncat_s_equal() (strncat_s(dest, dmax, src, n))
#define SAFEC_ASSERT_strncat_s_less() (strncat_s(dest, dmax, src, n))
#define OSC_ASSERT_strncpy_s1() (strncpy_s(dest, dmax, src, n))
#define OSC_ASSERT_strncpy_s2() (strncpy_s(dest, dmax, src, n))
#define SAFEC_ASSERT_strncpy_s_equal() (strncpy_s(dest, dmax, src, n))
#define SAFEC_ASSERT_strncpy_s_less() (strncpy_s(dest, dmax, src, n))
#define OSC_ASSERT_strnlen_s()  (strnlen_s(s, maxsize))
#define OSC_ASSERT_strstr_s()   (strstr_s(s1, s1max, s2, s2max, substring))
#pragma message ("No compile time OSC checking, use original libc/safec function")
#else
#pragma message ("No compile time OSC checking method selected, contact jaguars-dev alias for guidance")
#endif

/* Mapping for memcmp_s */

extern errno_t
__openosc_memcmp_s_to_buf (size_t s1_len,
                   const void *s1, rsize_t s1max,
                   const void *s2,  rsize_t n, int *diff);

static inline __attribute__ ((always_inline)) errno_t
osc_memcmp_s (const void *s1, rsize_t s1max,
	      const void *s2,  rsize_t n, int *diff)
{
    size_t _sz = __builtin_object_size(s1, OSC_OBJECT_SIZE_CHECK_0);
    int is_s1max_constant = __builtin_constant_p(s1max);
    return ((_sz != (size_t) -1)
	    ? (is_s1max_constant
	       ? ((_sz >= s1max)
		  ? (MEMCMP_S_CASE1 memcmp_s(s1, s1max, s2, n, diff))
		  : (MEMCMP_S_CASE2 OSC_ASSERT_memcmp_s()))
	       : (MEMCMP_S_CASE3 OSC_RUNTIME_CHECK_memcmp_s()))
	    : (MEMCMP_S_CASE4 memcmp_s(s1, s1max, s2, n, diff)));
}

#undef memcmp_s
#define memcmp_s(s1, s1max, s2, n, diff) \
    osc_memcmp_s (s1, s1max, s2, n, diff)

/* Mapping for memcpy_s */

extern errno_t
__openosc_memcpy_s_to_buf (size_t dest_len,
                   void *dest, rsize_t dmax, const void *src, rsize_t n);

static inline __attribute__ ((always_inline)) errno_t
openosc_memcpy_s (void *dest, rsize_t dmax, const void *src, rsize_t n)
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    int is_dmax_constant = __builtin_constant_p(dmax);
    return ((_sz != (size_t) -1)
	    ? (is_dmax_constant
	       ? ((_sz >= dmax)
		  ? (MEMCPY_S_CASE1 memcpy_s(dest, dmax, src, n))
		  : (MEMCPY_S_CASE2 OSC_ASSERT_memcpy_s()))
	       : (MEMCPY_S_CASE3 OSC_RUNTIME_CHECK_memcpy_s()))
	    : (MEMCPY_S_CASE4 memcpy_s(dest, dmax, src, n)));
}

#undef memcpy_s
#define memcpy_s(dest, dmax, src, smax) \
    openosc_memcpy_s (dest, dmax, src, smax)

/* Mapping for strcat_s */

extern errno_t
__openosc_strcat_s_to_buf (size_t dest_len,
                   char *dest, rsize_t dmax, const char *src);

static inline __attribute__ ((always_inline)) errno_t
openosc_strcat_s (char *dest, rsize_t dmax, const char *src)
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_dmax_constant = __builtin_constant_p(dmax);
    return ((_sz != (size_t) -1)
            ? (is_dmax_constant
               ? ((_sz >= dmax)
                  ? (STRCAT_S_CASE1 strcat_s(dest, dmax, src))
                  : (STRCAT_S_CASE2 OSC_ASSERT_strcat_s()))
               : (STRCAT_S_CASE3 OSC_RUNTIME_CHECK_strcat_s()))
            : (STRCAT_S_CASE4 strcat_s(dest, dmax, src)));
}

#undef strcat_s
#define strcat_s(dest, dmax, src) \
    openosc_strcat_s (dest, dmax, src)

/* Mapping for strcmp_s */

extern errno_t
__openosc_strcmp_s_to_buf (size_t s1_len,
                   const char *s1, rsize_t s1max,
                   const char *s2, int *indicator);

static inline __attribute__ ((always_inline)) errno_t
openosc_strcmp_s (const char *s1, rsize_t s1max,
	      const char *s2, int *indicator)
{
    size_t _sz = __builtin_object_size(s1, OSC_OBJECT_SIZE_CHECK_1);
    int is_s1max_constant = __builtin_constant_p(s1max);
    return ((_sz != (size_t) -1)
	    ? (is_s1max_constant
	       ? ((_sz >= s1max)
		  ? (STRCMP_S_CASE1 strcmp_s(s1, s1max, s2, indicator))
		  : (STRCMP_S_CASE2 OSC_ASSERT_strcmp_s()))
	       : (STRCMP_S_CASE3 OSC_RUNTIME_CHECK_strcmp_s()))
	    : (STRCMP_S_CASE4 strcmp_s(s1, s1max, s2, indicator)));
}

#undef strcmp_s
#define strcmp_s(s1, slmax, s2, indicator)	\
    openosc_strcmp_s (s1, slmax, s2, indicator)

/* Mapping for strcpy_s */

extern errno_t
__openosc_strcpy_s_to_buf (size_t dest_len,
                   char *dest, rsize_t dmax, const char *src);

static inline __attribute__ ((always_inline)) errno_t
openosc_strcpy_s (char *dest, rsize_t dmax, const char *src)
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_dmax_constant = __builtin_constant_p(dmax);
    return ((_sz != (size_t) -1)
            ? (is_dmax_constant
               ? ((_sz >= dmax)
                  ? (STRCPY_S_CASE1 strcpy_s(dest, dmax, src))
                  : (STRCPY_S_CASE2 OSC_ASSERT_strcpy_s()))
               : (STRCPY_S_CASE3 OSC_RUNTIME_CHECK_strcpy_s()))
            : (STRCPY_S_CASE4 strcpy_s(dest, dmax, src)));
}

#undef strcpy_s
#define strcpy_s(dest, dmax, src) \
    openosc_strcpy_s (dest, dmax, src)

/* Mapping for strncat_s */

extern errno_t
__openosc_strncat_s_to_buf (size_t dest_len,
		    char *dest, rsize_t dmax, const char *src, rsize_t n);

/*
 * correct usage of strncat_s destination size, dmax and n is:
 *     Strict Check Mode (default)     Relax Constraint Mode
 *          _sz >= dmax                    _sz >= dmax
 *     AND  _sz >= n                   AND _sz >= n 
 *     AND dmax > n 
 */
static inline __attribute__ ((always_inline)) errno_t
openosc_strncat_s (char *dest, rsize_t dmax, const char *src, rsize_t n)
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_dmax_constant = __builtin_constant_p(dmax);
    int is_n_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
	    ? (is_dmax_constant
	       ? ((_sz >= dmax)
		  ? (is_n_constant
#ifdef OSC_SAFEC_RELAX_CONSTRAINT
		     ? ((_sz >= n)
			? (STRNCAT_S_CASE1 strncat_s(dest, dmax, src, n))
			: (STRNCAT_S_CASE2 OSC_ASSERT_strncat_s1()))
#else
                     ? ((_sz >= n)
                        ? ((dmax > n)
                           ? (STRNCAT_S_CASE1 strncat_s(dest, dmax, src, n))
                           : ((dmax == n)
                              ? (STRNCAT_S_CASE_SAFECequal SAFEC_ASSERT_strncat_s_equal())
                              : (STRNCAT_S_CASE_SAFECless SAFEC_ASSERT_strncat_s_less())))
			: (STRNCAT_S_CASE2 OSC_ASSERT_strncat_s1()))
#endif
		     : (STRNCAT_S_CASE3 OSC_RUNTIME_CHECK_strncat_s()))
		  : (STRNCAT_S_CASE2 OSC_ASSERT_strncat_s2()))
	       : (STRNCAT_S_CASE3 OSC_RUNTIME_CHECK_strncat_s()))
#ifdef OSC_SAFEC_RELAX_CONSTRAINT
	    : (STRNCAT_S_CASE4 strncat_s(dest, dmax, src, n)));
#else
            : ((is_dmax_constant && is_n_constant)
               ? ((dmax > n)
                  ? (STRNCAT_S_CASE4 strncat_s(dest, dmax, src, n))
                  : ((dmax == n)
                     ? (STRNCAT_S_CASE_SAFECequal SAFEC_ASSERT_strncat_s_equal())
                     : (STRNCAT_S_CASE_SAFECless SAFEC_ASSERT_strncat_s_less())))
               : (STRNCAT_S_CASE4 strncat_s(dest, dmax, src, n))));
#endif
}

#undef strncat_s
#define strncat_s(dest, dmax, src, n) \
    openosc_strncat_s (dest, dmax, src, n)

/* Mapping for strncpy_s */

extern errno_t
__openosc_strncpy_s_to_buf (size_t dest_len,
		    char *dest, rsize_t dmax, const char *src, rsize_t n);

/*
 * correct usage of strncpy_s destination size, dmax and n is:
 *     Strict Check Mode (default)     Relax Constraint Mode
 *          _sz >= dmax                    _sz >= dmax
 *     AND  _sz > n                    AND _sz >= n 
 *     AND dmax > n 
 */
static inline __attribute__ ((always_inline)) errno_t
openosc_strncpy_s (char *dest, rsize_t dmax, const char *src, rsize_t n)
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_dmax_constant = __builtin_constant_p(dmax);
    int is_n_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
	    ? (is_dmax_constant
	       ? ((_sz >= dmax)
		  ? (is_n_constant
#ifdef OSC_SAFEC_RELAX_CONSTRAINT
		     ? ((_sz >= n)
			? (STRNCPY_S_CASE1 strncpy_s(dest, dmax, src, n))
			: (STRNCPY_S_CASE2 OSC_ASSERT_strncpy_s1()))
#else
                     ? ((_sz > n)
                        ? ((dmax > n)
                           ? (STRNCPY_S_CASE1 strncpy_s(dest, dmax, src, n))
                           : ((dmax == n)
                              ? (STRNCPY_S_CASE_SAFECequal SAFEC_ASSERT_strncpy_s_equal())
                              : (STRNCPY_S_CASE_SAFECless SAFEC_ASSERT_strncpy_s_less())))
			: (STRNCPY_S_CASE2 OSC_ASSERT_strncpy_s1()))
#endif
		     : (STRNCPY_S_CASE3 OSC_RUNTIME_CHECK_strncpy_s()))
		  : (STRNCPY_S_CASE2 OSC_ASSERT_strncpy_s2()))
	       : (STRNCPY_S_CASE3 OSC_RUNTIME_CHECK_strncpy_s()))
#ifdef OSC_SAFEC_RELAX_CONSTRAINT
	    : (STRNCPY_S_CASE4 strncpy_s(dest, dmax, src, n)));
#else
            : (is_dmax_constant
               ? (is_n_constant
                  ? ((dmax > n)
                     ? (STRNCPY_S_CASE4 strncpy_s(dest, dmax, src, n))
                     : ((dmax == n)
                        ? (STRNCPY_S_CASE_SAFECequal SAFEC_ASSERT_strncpy_s_equal())
                        : (STRNCPY_S_CASE_SAFECless SAFEC_ASSERT_strncpy_s_less())))
                  : (STRNCPY_S_CASE4 strncpy_s(dest, dmax, src, n)))
               : (STRNCPY_S_CASE4 strncpy_s(dest, dmax, src, n))));
#endif
}

#undef strncpy_s
#define strncpy_s(dest, dmax, src, n) \
    openosc_strncpy_s (dest, dmax, src, n)

/* Mapping for strnlen_s */

extern size_t
__openosc_strnlen_s_to_buf (size_t s_len,
		    const char *s, size_t maxsize);

static inline __attribute__ ((always_inline)) size_t
openosc_strnlen_s (const char *s, size_t maxsize)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_maxsize_constant = __builtin_constant_p(maxsize);
    return ((_sz != (size_t) -1)
	    ? (is_maxsize_constant
	       ? ((_sz >= maxsize)
		  ? (STRNLEN_S_CASE1 strnlen_s(s, maxsize))
		  : (STRNLEN_S_CASE2 OSC_ASSERT_strnlen_s()))
	       : (STRNLEN_S_CASE3 OSC_RUNTIME_CHECK_strnlen_s()))
	    : (STRNLEN_S_CASE4 strnlen_s(s, maxsize)));
}

#undef strnlen_s
#define strnlen_s(s, maxsize) \
    openosc_strnlen_s (s, maxsize)

/* Mapping for strstr_s */

extern errno_t
__openosc_strstr_s_to_buf (size_t s1_len,
		   char *s1, rsize_t s1max,
		   const char *s2, rsize_t s2max, char **substring);

static inline __attribute__ ((always_inline)) errno_t
openosc_strstr_s (char *s1, rsize_t s1max,
	      const char *s2, rsize_t s2max, char **substring)
{
    size_t _sz = __builtin_object_size(s1, OSC_OBJECT_SIZE_CHECK_1);
    int is_s1max_constant = __builtin_constant_p(s1max);
    return ((_sz != (size_t) -1)
	    ? (is_s1max_constant
	       ? ((_sz >= s1max)
		  ? (STRSTR_S_CASE1 strstr_s(s1, s1max, s2, s2max, substring))
		  :  (STRSTR_S_CASE2 OSC_ASSERT_strstr_s()))
	       : (STRSTR_S_CASE3 OSC_RUNTIME_CHECK_strstr_s()))
	    : (STRSTR_S_CASE4 strstr_s(s1, s1max, s2, s2max, substring)));
}

#undef strstr_s
#define strstr_s(s1, s1max, s2, s2max, substring) \
    openosc_strstr_s (s1, s1max, s2, s2max, substring)

#endif /* ifndef __OPENOSC_SAFEC_NOMAP_H__ */

#endif /* __OPENOSC_SAFEC_MAP_H__ */
