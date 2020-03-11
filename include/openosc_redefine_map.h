/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_REDEFINE_MAP_H__
#define __OPENOSC_REDEFINE_MAP_H__

/* openosc_redefine_map.h and openosc_redefine_nomap.h are mutually exclusive */
#ifndef __OPENOSC_REDEFINE_NOMAP_H__

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_extern.h"

/*
 * Define Runtime check macros
 */
#if (OSC_RUNTIME_CHK == OSC_RUNTIME_USE_LIBOSC)
#define OSC_RUNTIME_CHECK_memcpy(_sz, _src_sz, dst, src, len) (__openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_RUNTIME_CHECK_memmove(_sz, _src_sz, dst, src, len) (__openosc_memmove_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_RUNTIME_CHECK_memset() (__openosc_memset_to_buf(_sz, dst, c, len))
#define OSC_RUNTIME_CHECK_bcopy(_sz, _src_sz, src, dst, len) (__openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len))
#define OSC_RUNTIME_CHECK_bzero() (__openosc_bzero_to_buf(_sz, dst, len))
#define OSC_RUNTIME_CHECK_strcpy() (__openosc_strcpy_to_buf(_sz, dst, src))
#define OSC_RUNTIME_CHECK_strncpy() (__openosc_strncpy_to_buf(_sz, dst, src, len))
#define OSC_RUNTIME_CHECK_strcat() (__openosc_strcat_to_buf(_sz, dst, src))
#define OSC_RUNTIME_CHECK_strncat() (__openosc_strncat_to_buf(_sz, dst, src, len))
#define OSC_RUNTIME_CHECK_strnlen() (__openosc_strnlen_from_buf(_sz, s, len))
#define OSC_RUNTIME_CHECK_vsnprintf() (__openosc_vsnprintf_to_buf(_sz, str, len, fmt, ap))
#else
#define OSC_RUNTIME_CHECK_memcpy(_sz, _src_sz, dst, src, len) (memcpy(dst, src, len))
#define OSC_RUNTIME_CHECK_memmove(_sz, _src_sz, dst, src, len) (memmove(dst, src, len))
#define OSC_RUNTIME_CHECK_memset() (memset(dst, c, len))
#define OSC_RUNTIME_CHECK_bcopy(_sz, _src_sz, src, dst, len) (bcopy(src, dst, len))
#define OSC_RUNTIME_CHECK_bzero() (bzero(dst, len))
#define OSC_RUNTIME_CHECK_strcpy() (strcpy(dst, src))
#define OSC_RUNTIME_CHECK_strncpy() (strncpy(dst, src, len))
#define OSC_RUNTIME_CHECK_strcat() (strcat(dst, src))
#define OSC_RUNTIME_CHECK_strncat() (strncat(dst, src, len))
#define OSC_RUNTIME_CHECK_strnlen() (strnlen(s, len))
#define OSC_RUNTIME_CHECK_vsnprintf() (vsnprintf(str, len, fmt, ap))
#endif /* OSC_RUNTIME_CHK */

/*
 * Define compile-time static asserts to report buffer overflow
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
extern int __attribute__((error("Compiler Assertion: memcpy len will always overflow dst"))) \
 osc_compile_check_memcpy_dst(void);
#define OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len) ({osc_compile_check_memcpy_dst(), (void *)0;})

extern int __attribute__((error("Compiler Assertion: memcpy len will cause src overread"))) \
 osc_compile_check_memcpy_src(void);
#define OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len) ({osc_compile_check_memcpy_src(), (void *)0;})

extern int __attribute__((error("Compiler Assertion: memmove len will always overflow dst"))) \
 osc_compile_check_memmove_dst(void);
#define OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len) ({osc_compile_check_memmove_dst(), (void *)0;})

extern int __attribute__((error("Compiler Assertion: memmove len will cause src overread"))) \
 osc_compile_check_memmove_src(void);
#define OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len) ({osc_compile_check_memmove_src(), (void *)0;})

extern int __attribute__((error("Compiler Assertion: memset len will always overflow dst"))) \
 osc_compile_check_memset(void);
#define OSC_ASSERT_memset() ({osc_compile_check_memset(), (void *)0;})

extern void __attribute__((error("Compiler Assertion: bcopy len will always overflow dst"))) \
 osc_compile_check_bcopy_dst(void);
#define OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len) ({osc_compile_check_bcopy_dst();})

extern void __attribute__((error("Compiler Assertion: bcopy len will cause src overread"))) \
 osc_compile_check_bcopy_src(void);
#define OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len) ({osc_compile_check_bcopy_src();})

extern void __attribute__((error("Compiler Assertion: bzero len will always overflow dst"))) \
 osc_compile_check_bzero(void);
#define OSC_ASSERT_bzero() ({osc_compile_check_bzero();})

extern int __attribute__((error("Compiler Assertion: strcpy len will always overflow dst"))) \
 osc_compile_check_strcpy(void);
#define OSC_ASSERT_strcpy() ({osc_compile_check_strcpy(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: strncpy len will always overflow dst"))) \
 osc_compile_check_strncpy(void);
#define OSC_ASSERT_strncpy() ({osc_compile_check_strncpy(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: strcat len will always overflow dst"))) \
 osc_compile_check_strcat(void);
#define OSC_ASSERT_strcat() ({osc_compile_check_strcat(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: strncat len will always overflow dst"))) \
 osc_compile_check_strncat(void);
#define OSC_ASSERT_strncat() ({osc_compile_check_strncat(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: strnlen maxlen indexes beyond s"))) \
 osc_compile_check_strnlen(void);
#define OSC_ASSERT_strnlen() ({osc_compile_check_strnlen(), (size_t)0;})

extern int __attribute__((error("Compiler Assertion: vsnprintf len indexes beyond str"))) \
 osc_compile_check_vsnprintf(void);
#define OSC_ASSERT_vsnprintf() ({osc_compile_check_vsnprintf(), (int)0;})
#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_BUILTIN)
/* DO NOT USE FOR RELEASE CODE */
#define OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len)    (__builtin___memcpy_chk(dst, src, len, _sz))
#define OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len)    (__builtin___memcpy_chk(dst, src, len, _src_sz))
#define OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len)   (__builtin___memmove_chk(dst, src, len, _sz))
#define OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len)   (__builtin___memmove_chk(dst, src, len, _src_sz))
#define OSC_ASSERT_memset()        (__builtin___memset_chk(dst, c, len, _sz))
#define OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len)     (__builtin___bcopy_chk(src, dst, len, _sz))
#define OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len)     (__builtin___bcopy_chk(src, dst, len, _src_sz))
#define OSC_ASSERT_bzero()         (__builtin___memset_chk(dst, 0, len, _sz))
#define OSC_ASSERT_strcpy()       (__builtin___strcpy_chk(dst, src, _sz))
#define OSC_ASSERT_strncpy()       (__builtin___strncpy_chk(dst, src, len, _sz))
#define OSC_ASSERT_strcat()       (__builtin___strcat_chk (dst, src, _sz))
#define OSC_ASSERT_strncat()       (__builtin___strncat_chk (dst, src, len, _sz))
#define OSC_ASSERT_strnlen()       (__openosc_strnlen_from_buf(_sz, s, len))
#define OSC_ASSERT_vsnprintf()     (__openosc_vsnprintf_to_buf(_sz, str, len, fmt, ap))
#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_RUNTIME_CHK)
/* No compile time check, use OSC runtime check */
#define OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len)    (__openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len)    (__openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len)   (__openosc_memmove_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len)   (__openosc_memmove_to_buf(_sz, _src_sz, dst, src, len))
#define OSC_ASSERT_memset()    (__openosc_memset_to_buf(_sz, dst, c, len))
#define OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len)     (__openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len))
#define OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len)     (__openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len))
#define OSC_ASSERT_bzero()     (__openosc_bzero_to_buf(_sz, dst, len))
#define OSC_ASSERT_strcpy()   (__openosc_strcpy_to_buf(_sz, dst, src))
#define OSC_ASSERT_strncpy()   (__openosc_strncpy_to_buf(_sz, dst, src, len))
#define OSC_ASSERT_strcat()   (__openosc_strcat_to_buf(_sz, dst, src))
#define OSC_ASSERT_strncat()   (__openosc_strncat_to_buf(_sz, dst, src, len))
#define OSC_ASSERT_strnlen()   (__openosc_strnlen_from_buf(_sz, s, len))
#define OSC_ASSERT_vsnprintf() (__openosc_vsnprintf_to_buf(_sz, str, len, fmt, ap))
#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_NONE)
/* No compile time check, use original libc/safec function */
#define OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len)   (memcpy(dst, src, len))
#define OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len)   (memcpy(dst, src, len))
#define OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len)   (memmove(dst, src, len))
#define OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len)   (memmove(dst, src, len))
#define OSC_ASSERT_memset()       (memset(dst, c, len))
#define OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len)    (bcopy(src, dst, len))
#define OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len)    (bcopy(src, dst, len))
#define OSC_ASSERT_bzero()        (bzero(dst, len))
#define OSC_ASSERT_strcpy()      (strcpy(dst, src))
#define OSC_ASSERT_strncpy()      (strncpy(dst, src, len))
#define OSC_ASSERT_strcat()      (strcat(dst, src))
#define OSC_ASSERT_strncat()      (strncat(dst, src, len))
#define OSC_ASSERT_strnlen()      (strnlen(s, len))
#define OSC_ASSERT_vsnprintf()    (vsnprintf(str, len, fmt, ap))
#pragma message ("No compile time OSC checking, use original libc/safec function")
#else
#pragma message ("No compile time OSC checking method selected, contact jaguars-dev alias for guidance")
#endif

/* Mapping for memcpy */

extern void *__openosc_memcpy_to_buf(size_t dest_len, size_t src_len,
			     void *dst, const void *src, size_t len);

static inline __attribute__ ((always_inline)) void *
openosc_memcpy (void *dst, const void *src, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    size_t _src_sz = __builtin_object_size(src, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
    return ((_sz != (size_t) -1)
	    ? (is_len_constant
	       ? ((_sz >= len)
		  ? ((_src_sz != (size_t) -1)
		     ? ((_src_sz >= len)
			? (MEMCPY_CASE7 memcpy(dst, src, len))
			: (MEMCPY_CASE8 OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len)))
		     : (MEMCPY_CASE1 memcpy(dst, src, len)))
		  : (MEMCPY_CASE2 OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len)))
	       : (MEMCPY_CASE3 OSC_RUNTIME_CHECK_memcpy(_sz, _src_sz, dst, src, len)))
	    : ((_src_sz != (size_t) -1)
	       ? (is_len_constant
		  ? ((_src_sz >= len)
		     ? (MEMCPY_CASEa memcpy(dst, src, len))
		     : (MEMCPY_CASEb OSC_ASSERT_memcpy_src(_src_sz, _sz, dst, src, len)))
		  : (MEMCPY_CASE9 OSC_RUNTIME_CHECK_memcpy(_sz, _src_sz, dst, src, len)))
	       : (MEMCPY_CASE4 memcpy(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMCPY_CASE1 memcpy(dst, src, len))
                  : (MEMCPY_CASE2 OSC_ASSERT_memcpy_dst(_sz, _src_sz, dst, src, len)))
               : (MEMCPY_CASE3 OSC_RUNTIME_CHECK_memcpy(_sz, _src_sz, dst, src, len)))
            : (MEMCPY_CASE4 memcpy(dst, src, len)));
#endif
}

#undef memcpy
#define memcpy(dest, src, len) \
        openosc_memcpy(dest, src, len)

 /* Mapping for memmove */

extern void *__openosc_memmove_to_buf(size_t dest_len, size_t src_len,
				void *dst, const void *src, size_t len);

static inline __attribute__ ((always_inline)) void *
openosc_memmove (void *dst, const void *src, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    size_t _src_sz = __builtin_object_size(src, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
		  ? ((_src_sz != (size_t) -1)
		     ? ((_src_sz >= len)
			? (MEMMOVE_CASE7 memmove(dst, src, len))
			: (MEMMOVE_CASE8 OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len)))
		     : (MEMMOVE_CASE1 memmove(dst, src, len)))
		  : (MEMMOVE_CASE2 OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len)))
	       : (MEMMOVE_CASE3 OSC_RUNTIME_CHECK_memmove(_sz, _src_sz, dst, src, len)))
	    : ((_src_sz != (size_t) -1)
	       ? (is_len_constant
		  ? ((_src_sz >= len)
		     ? (MEMMOVE_CASEa memmove(dst, src, len))
		     : (MEMMOVE_CASEb OSC_ASSERT_memmove_src(_src_sz, _sz, dst, src, len)))
		  : (MEMMOVE_CASE9 OSC_RUNTIME_CHECK_memmove(_sz, _src_sz, dst, src, len)))
	       : (MEMMOVE_CASE4 memmove(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMMOVE_CASE1 memmove(dst, src, len))
                  : (MEMMOVE_CASE2 OSC_ASSERT_memmove_dst(_sz, _src_sz, dst, src, len)))
               : (MEMMOVE_CASE3 OSC_RUNTIME_CHECK_memmove(_sz, _src_sz, dst, src, len)))
            : (MEMMOVE_CASE4 memmove(dst, src, len)));
#endif
}

#undef memmove
#define memmove(dest, src, len) \
        openosc_memmove(dest, src, len)

/* Mapping for memset */

extern void *
__openosc_memset_to_buf(size_t dest_len, void *dst, int c, size_t len);

static inline __attribute__ ((always_inline)) void *
openosc_memset (void *dst, int c, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMSET_CASE1 memset(dst, c, len))
                  : (MEMSET_CASE2 OSC_ASSERT_memset()))
               : (MEMSET_CASE3 OSC_RUNTIME_CHECK_memset()))
            : (MEMSET_CASE4 memset(dst, c, len)));
}

#undef memset
#define memset(dst, c, len) \
        openosc_memset(dst, c, len)

/* Mapping for bcopy */

extern void __openosc_bcopy_to_buf(size_t dest_len, size_t src_len,
			   const void *src, void *dst, size_t len);

static inline __attribute__ ((always_inline)) void
openosc_bcopy (const void *src, void *dst, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    size_t _src_sz = __builtin_object_size(src, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
    ((_sz != (size_t) -1)
          ? (is_len_constant
             ? ((_sz >= len)
		? ((_src_sz != (size_t) -1)
		   ? ((_src_sz >= len)
		      ? (BCOPY_CASE7 bcopy(src, dst, len))
		      : (BCOPY_CASE8 OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len)))
		   : (BCOPY_CASE1 bcopy(src, dst, len)))
		: (BCOPY_CASE2 OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len)))
	     : (BCOPY_CASE3 OSC_RUNTIME_CHECK_bcopy(_sz, _src_sz, src, dst, len)))
	  : ((_src_sz != (size_t) -1)
	     ? (is_len_constant
		? ((_src_sz >= len)
		   ? (BCOPY_CASEa bcopy(src, dst, len))
		   : (BCOPY_CASEb OSC_ASSERT_bcopy_src(_src_sz, _sz, src, dst, len)))
		: (BCOPY_CASE9 OSC_RUNTIME_CHECK_bcopy(_sz, _src_sz, src, dst, len)))
	     : (BCOPY_CASE4 bcopy(src, dst, len))));
#else
    ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (BCOPY_CASE1 bcopy(src, dst, len))
                  : (BCOPY_CASE2 OSC_ASSERT_bcopy_dst(_sz, _src_sz, src, dst, len)))
               : (BCOPY_CASE3 OSC_RUNTIME_CHECK_bcopy(_sz, _src_sz, src, dst, len)))
            : (BCOPY_CASE4 bcopy(src, dst, len)));
#endif
}

#undef bcopy
#define bcopy(src, dst, len) \
        openosc_bcopy(src, dst, len)

/* Mapping for bzero */

extern void
__openosc_bzero_to_buf(size_t dest_len, void *dst, size_t len);

static inline __attribute__ ((always_inline)) void
openosc_bzero (void *dst, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    ((_sz != (size_t) -1)
          ? (is_len_constant
             ? ((_sz >= len)
                ? (BZERO_CASE1 bzero(dst, len))
                : (BZERO_CASE2 OSC_ASSERT_bzero()))
             : (BZERO_CASE3 OSC_RUNTIME_CHECK_bzero()))
          : (BZERO_CASE4 bzero(dst, len)));
}

#undef bzero
#define bzero(dst, len) \
        openosc_bzero(dst, len)

/* Mapping for strcpy */

extern char *
__openosc_strcpy_to_buf(size_t dest_len, char *dst, const char *src);

static inline __attribute__ ((always_inline)) char *
openosc_strcpy (char *dst, const char *src)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(strlen(src));
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > strlen(src))
                  ? (STRCPY_CASE1 strcpy(dst, src))
                  : (STRCPY_CASE2 OSC_ASSERT_strcpy()))
               : (STRCPY_CASE3 OSC_RUNTIME_CHECK_strcpy()))
            : (STRCPY_CASE4 strcpy(dst, src)));
}

#undef strcpy
#define strcpy(dst, src) \
        openosc_strcpy(dst, src)


/* Mapping for strncpy */
#define _HAVE_STRING_ARCH_strncpy 1

extern char *
__openosc_strncpy_to_buf(size_t dest_len, char *dst,
		 const char *src, size_t len);

static inline __attribute__ ((always_inline)) char *
openosc_strncpy (char *dst, const char *src, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
	    ? (is_len_constant
	       ? ((_sz >= len)
		  ? (STRNCPY_CASE1 strncpy(dst, src, len))
		  : (STRNCPY_CASE2 OSC_ASSERT_strncpy()))
	       : (STRNCPY_CASE3 OSC_RUNTIME_CHECK_strncpy()))
	    : (STRNCPY_CASE4 strncpy(dst, src, len)));
}

#undef strncpy
#define strncpy(dest, src, len) \
        openosc_strncpy(dest, src, len)

/* Mapping for strcat */

extern char *
__openosc_strcat_to_buf(size_t dest_len, char *dst, const char *src);

static inline __attribute__ ((always_inline)) char *
openosc_strcat (char *dst, const char *src)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(strlen(src));
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > strlen(src))
                  ? (STRCAT_CASE1 OSC_RUNTIME_CHECK_strcat())
                  : (STRCAT_CASE2 OSC_ASSERT_strcat()))
               : (STRCAT_CASE3 OSC_RUNTIME_CHECK_strcat()))
            : (STRCAT_CASE4 strcat(dst, src)));
}

#undef strcat
#define strcat(dst, src) \
        openosc_strcat(dst, src)

/* Mapping for strncat */
#define _HAVE_STRING_ARCH_strncat 1

extern char *
__openosc_strncat_to_buf(size_t dest_len, char *dst,
		 const char *src, size_t len);

static inline __attribute__ ((always_inline)) char *
openosc_strncat (char *dst, const char *src, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
	    ? (is_len_constant
	       ? ((_sz > len)
		  ? (STRNCAT_CASE1 OSC_RUNTIME_CHECK_strncat())
		  : (STRNCAT_CASE2 OSC_ASSERT_strncat()))
	       : (STRNCAT_CASE3 OSC_RUNTIME_CHECK_strncat()))
	    : (STRNCAT_CASE4 strncat(dst, src, len)));
}

#undef strncat
#define strncat(dst, src, len) \
         openosc_strncat(dst, src, len)

/* Mapping for strnlen */

#define HAVE_STRNLEN 1

extern size_t
__openosc_strnlen_from_buf(size_t len, const char * src, size_t maxlen);

static inline __attribute__ ((always_inline)) size_t
openosc_strnlen (const char *s, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
          ? (is_len_constant
             ? ((_sz >= len)
		? (STRNLEN_CASE1 strnlen(s, len))
		: (STRNLEN_CASE2 OSC_ASSERT_strnlen()))
             : (STRNLEN_CASE3 OSC_RUNTIME_CHECK_strnlen()))
          : (STRNLEN_CASE4 strnlen(s, len)));
}

#undef strnlen
#define strnlen(s, maxlen)  \
        openosc_strnlen(s, maxlen)

#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vsnprintf */

extern int
__openosc_vsnprintf_to_buf(size_t dest_len, char *str, size_t len,
		   const char *fmt, va_list ap);

static inline __attribute__ ((always_inline)) int
openosc_vsnprintf (char *str, size_t len,
	       const char *fmt, va_list ap)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(str, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
	    ? (is_len_constant
	       ? ((_sz >= len)
		  ? (VSNPRINTF_CASE1 vsnprintf(str, len, fmt, ap))
		  : (VSNPRINTF_CASE2 OSC_ASSERT_vsnprintf()))
	       : (VSNPRINTF_CASE3 OSC_RUNTIME_CHECK_vsnprintf()))
	    : (VSNPRINTF_CASE4 vsnprintf(str, len, fmt, ap)));
}

#undef vsnprintf
#define vsnprintf(str, len, format, ap)  \
        openosc_vsnprintf(str, len, format, ap)

/* avoid redefinition */
#define HAVE_VSNPRINTF 1

#endif /* OPENOSC_VALIST_NOSUPPORT */

#ifdef __cplusplus
}
#endif

#endif  /* ifndef __OPENOSC_REDEFINE_NOMAP_H__ */

#endif /* __OPENOSC_REDEFINE_MAP_H__ */
