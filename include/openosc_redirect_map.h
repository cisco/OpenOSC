/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#ifndef __OPENOSC_REDIRECT_MAP_H__
#define __OPENOSC_REDIRECT_MAP_H__

/* openosc_redirect_map.h and openosc_redirect_nomap.h are mutually exclusive */
#ifndef __OPENOSC_REDIRECT_NOMAP_H__

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_extern.h"


#ifdef OPENOSC_EXTRA_LEVEL_INLINE_FUNC
#define _OPENOSC_MEMCPY_FUNC openosc_memcpy
#else
#define _OPENOSC_MEMCPY_FUNC memcpy
#endif

/* Mapping for memcpy */

extern void *
__openosc_memcpy_to_buf(size_t dest_len, size_t src_len,
                void *dst, const void *src, size_t len);
extern void *__REDIRECT_NTH (__openosc_memcpy_alias,
                             (void *dst, const void *src, size_t len), memcpy);

#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("memcpy"))
void *
openosc_memcpy_chk_warn (size_t _sz, size_t _src_sz, void *dst, const void *src, size_t len)
{
    return __openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len);
}
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
static __attribute__((noinline))
     __warn_or_error_attr (__src_overread_msg("memcpy"))
void *
openosc_memcpy_src_chk_warn (size_t _sz, size_t _src_sz, void *dst, const void *src, size_t len)
{
    return __openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len);
}
#endif
#else
extern void *__REDIRECT_NTH (openosc_memcpy_chk_warn,
                             (size_t dest_len, size_t src_len, void *dst, const void *src, size_t n),
                             __openosc_memcpy_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("memcpy"));
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
extern void *__REDIRECT_NTH (openosc_memcpy_src_chk_warn,
                             (size_t dest_len, size_t src_len, void *dst, const void *src, size_t n),
                             __openosc_memcpy_to_buf)
     __warn_or_error_attr (__src_overread_msg("memcpy"));
#endif
#endif

__openosc_fortify_function void *
__NTH (_OPENOSC_MEMCPY_FUNC (void *__restrict __pass_objsize0 dst, const void *__restrict __pass_objsize0 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos0, dst, len), __dst_overflow_msg("memcpy"))
__clang_warn_or_error_if(__size_too_small (__bos0, src, len), __src_overread_msg("memcpy"))
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
			? (MEMCPY_CASE7 __openosc_memcpy_alias(dst, src, len))
			: (MEMCPY_CASE8 openosc_memcpy_src_chk_warn(_sz, _src_sz, dst, src, len)))
		     : (MEMCPY_CASE1 __openosc_memcpy_alias(dst, src, len)))
		  : (MEMCPY_CASE2 openosc_memcpy_chk_warn(_sz, _src_sz, dst, src, len)))
	       : (MEMCPY_CASE3 __openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len)))
	    : ((_src_sz != (size_t) -1)
	       ? (is_len_constant
		  ? ((_src_sz >= len)
		     ? (MEMCPY_CASEa __openosc_memcpy_alias(dst, src, len))
		     : (MEMCPY_CASEb openosc_memcpy_src_chk_warn(_sz, _src_sz, dst, src, len)))
		  : (MEMCPY_CASE9 __openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len)))
	       : (MEMCPY_CASE4 __openosc_memcpy_alias(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMCPY_CASE1 __openosc_memcpy_alias(dst, src, len))
                  : (MEMCPY_CASE2 openosc_memcpy_chk_warn(_sz, _src_sz, dst, src, len)))
               : (MEMCPY_CASE3 __openosc_memcpy_to_buf(_sz, _src_sz, dst, src, len)))
            : (MEMCPY_CASE4 __openosc_memcpy_alias(dst, src, len)));
#endif
}

#ifdef OPENOSC_EXTRA_LEVEL_INLINE_FUNC
/*
 * A false positive is reported by Clang in the following scenario:
 * static inline void * func1(struct foo *p) { do_something; }
 * static inline void * func2(struct foo *p) { func1(p); return p->m; }
 * memcpy(p->dst, func2(p), 6);  // dst-overflow false postive
 * Adding one more level of inline function fixes this false-positive issue.
 */
__openosc_fortify_function void *
__NTH (memcpy (void *__restrict __pass_objsize0 dst, const void *__restrict __pass_objsize0 src, size_t len))
{
    void *__restrict pdst  = dst;
    const void *__restrict psrc = src;
    return openosc_memcpy(pdst, psrc, len);
}
#endif


 /* Mapping for memmove */

extern void *
__openosc_memmove_to_buf(size_t dest_len, size_t src_len, void *dst, const void *src, size_t len);
extern void *__REDIRECT_NTH (__openosc_memmove_alias,
                             (void *dst, const void *src, size_t len), memmove);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("memmove"))
void *
openosc_memmove_chk_warn (size_t _sz, size_t _src_sz, void *dst, const void *src, size_t len)
{
    return __openosc_memmove_to_buf(_sz, _src_sz, dst, src, len);
}
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
static __attribute__((noinline))
     __warn_or_error_attr (__src_overread_msg("memmove"))
void *
openosc_memmove_src_chk_warn (size_t _sz, size_t _src_sz, void *dst, const void *src, size_t len)
{
    return __openosc_memmove_to_buf(_sz, _src_sz, dst, src, len);
}
#endif
#else
extern void *__REDIRECT_NTH (openosc_memmove_chk_warn,
                             (size_t dest_len, size_t src_len, void *dst, const void *src, size_t n),
                             __openosc_memmove_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("memmove"));
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
extern void *__REDIRECT_NTH (openosc_memmove_src_chk_warn,
                             (size_t dest_len, size_t src_len, void *dst, const void *src, size_t n),
                             __openosc_memmove_to_buf)
     __warn_or_error_attr (__src_overread_msg("memmove"));
#endif
#endif

__openosc_fortify_function void *
__NTH (memmove (void *__restrict __pass_objsize0 dst, const void *__restrict __pass_objsize0 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos0, dst, len), __dst_overflow_msg("memmove"))
__clang_warn_or_error_if(__size_too_small (__bos0, src, len), __src_overread_msg("memmove"))
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
			? (MEMMOVE_CASE7 __openosc_memmove_alias(dst, src, len))
			: (MEMMOVE_CASE8 openosc_memmove_src_chk_warn(_sz, _src_sz, dst, src, len)))
		     : (MEMMOVE_CASE1 __openosc_memmove_alias(dst, src, len)))
		  : (MEMMOVE_CASE2 openosc_memmove_chk_warn(_sz, _src_sz, dst, src, len)))
	       : (MEMMOVE_CASE3 __openosc_memmove_to_buf(_sz, _src_sz, dst, src, len)))
	    : ((_src_sz != (size_t) -1)
	       ? (is_len_constant
		  ? ((_src_sz >= len)
		     ? (MEMMOVE_CASEa __openosc_memmove_alias(dst, src, len))
		     : (MEMMOVE_CASEb openosc_memmove_src_chk_warn(_sz, _src_sz, dst, src, len)))
		  : (MEMMOVE_CASE9 __openosc_memmove_to_buf(_sz, _src_sz, dst, src, len)))
	       : (MEMMOVE_CASE4 __openosc_memmove_alias(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMMOVE_CASE1 __openosc_memmove_alias(dst, src, len))
                  : (MEMMOVE_CASE2 openosc_memmove_chk_warn(_sz, _src_sz, dst, src, len)))
               : (MEMMOVE_CASE3 __openosc_memmove_to_buf(_sz, _src_sz, dst, src, len)))
            : (MEMMOVE_CASE4 __openosc_memmove_alias(dst, src, len)));
#endif
}


/* Mapping for memset */

extern void *
__openosc_memset_to_buf(size_t dest_len, void *dst, int c, size_t len);
extern void *__REDIRECT_NTH (__openosc_memset_alias,
                             (void *dst, int c, size_t len), memset);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("memset"))
void *
openosc_memset_chk_warn (size_t _sz, void *dst, int c, size_t len)
{
    return __openosc_memset_to_buf(_sz, dst, c, len);
}
#else
extern void *__REDIRECT_NTH (openosc_memset_chk_warn,
                             (size_t dest_len, void *dst, int c, size_t n),
                             __openosc_memset_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("memset"));
#endif

__openosc_fortify_function void *
__NTH (memset (void *__restrict __pass_objsize0 dst, int c, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos0, dst, len), __dst_overflow_msg("memset"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMSET_CASE1 __openosc_memset_alias(dst, c, len))
                  : (MEMSET_CASE2 openosc_memset_chk_warn(_sz, dst, c, len)))
               : (MEMSET_CASE3 __openosc_memset_to_buf(_sz, dst, c, len)))
            : (MEMSET_CASE4 __openosc_memset_alias(dst, c, len)));
}


/* Mapping for bcopy */

extern void
__openosc_bcopy_to_buf(size_t dest_len, size_t src_len, const void *src, void *dst, size_t len);
extern void __REDIRECT_NTH (__openosc_bcopy_alias,
                             (const void *src, void *dst, size_t len), bcopy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("bcopy"))
void
openosc_bcopy_chk_warn (size_t _sz, size_t _src_sz, const void *src, void *dst, size_t len)
{
    __openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len);
}
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
static __attribute__((noinline))
     __warn_or_error_attr (__src_overread_msg("bcopy"))
void
openosc_bcopy_src_chk_warn (size_t _sz, size_t _src_sz, const void *src, void *dst, size_t len)
{
    __openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len);
}
#endif
#else
extern void __REDIRECT_NTH (openosc_bcopy_chk_warn,
                             (size_t dest_len, size_t src_len, const void *src, void *dst, size_t n),
                             __openosc_bcopy_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("bcopy"));
#ifdef _OPENOSC_SRC_OVERREAD_ENABLED
extern void __REDIRECT_NTH (openosc_bcopy_src_chk_warn,
                             (size_t dest_len, size_t src_len, const void *src, void *dst, size_t n),
                             __openosc_bcopy_to_buf)
     __warn_or_error_attr (__src_overread_msg("bcopy"));
#endif
#endif

__openosc_fortify_function void
__NTH (bcopy (const void *__restrict __pass_objsize0 src, void *__restrict __pass_objsize0 dst, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos0, dst, len), __dst_overflow_msg("bcopy"))
__clang_warn_or_error_if(__size_too_small (__bos0, src, len), __src_overread_msg("bcopy"))
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
			? (BCOPY_CASE7 __openosc_bcopy_alias(src, dst, len))
			: (BCOPY_CASE8 openosc_bcopy_src_chk_warn(_sz, _src_sz, src, dst, len)))
		     : (BCOPY_CASE1 __openosc_bcopy_alias(src, dst, len)))
		  : (BCOPY_CASE2 openosc_bcopy_chk_warn(_sz, _src_sz, src, dst, len)))
	       : (BCOPY_CASE3 __openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len)))
	    : ((_src_sz != (size_t) -1)
	       ? (is_len_constant
		  ? ((_src_sz >= len)
		     ? (BCOPY_CASEa __openosc_bcopy_alias(src, dst, len))
		     : (BCOPY_CASEb openosc_bcopy_src_chk_warn(_sz, _src_sz, src, dst, len)))
		  : (BCOPY_CASE9 __openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len)))
	       : (BCOPY_CASE4 __openosc_bcopy_alias(src, dst, len))));
#else
    ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (BCOPY_CASE1 __openosc_bcopy_alias(src, dst, len))
                  : (BCOPY_CASE2 openosc_bcopy_chk_warn(_sz, _src_sz, src, dst, len)))
               : (BCOPY_CASE3 __openosc_bcopy_to_buf(_sz, _src_sz, src, dst, len)))
            : (BCOPY_CASE4 __openosc_bcopy_alias(src, dst, len)));
#endif
}


/* Mapping for bzero */

extern void
__openosc_bzero_to_buf(size_t dest_len, void *dst, size_t len);
extern void __REDIRECT_NTH (__openosc_bzero_alias,
                             (void *dst, size_t len), bzero);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("bzero"))
void
openosc_bzero_chk_warn (size_t _sz, void *dst, size_t len)
{
    __openosc_bzero_to_buf(_sz, dst, len);
}
#else
extern void __REDIRECT_NTH (openosc_bzero_chk_warn,
                             (size_t dest_len, void *dst, size_t n),
                             __openosc_bzero_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("bzero"));
#endif

__openosc_fortify_function void
__NTH (bzero (void *__restrict __pass_objsize0 dst, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos0, dst, len), __dst_overflow_msg("bzero"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (BZERO_CASE1 __openosc_bzero_alias(dst, len))
                  : (BZERO_CASE2 openosc_bzero_chk_warn(_sz, dst, len)))
               : (BZERO_CASE3 __openosc_bzero_to_buf(_sz, dst, len)))
            : (BZERO_CASE4 __openosc_bzero_alias(dst, len)));
}


/* Mapping for strcpy */

extern char *
__openosc_strcpy_to_buf(size_t dest_len, char *dst, const char *src);
extern char *__REDIRECT_NTH (__openosc_strcpy_alias,
                             (char *dst, const char *src), strcpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("strcpy"))
char *
openosc_strcpy_chk_warn (size_t _sz, char *dst, const char *src)
{
    return __openosc_strcpy_to_buf(_sz, dst, src);
}
#else
extern char *__REDIRECT_NTH (openosc_strcpy_chk_warn,
                             (size_t dest_len, char *dst, const char *src),
                             __openosc_strcpy_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("strcpy"));
#endif

__openosc_fortify_function char *
__NTH (strcpy (char *__restrict __pass_objsize1 dst, const char *__restrict src))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, strlen(src)), __dst_overflow_msg("strcpy"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(strlen(src));
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > strlen(src))
                  ? (STRCPY_CASE1 __openosc_strcpy_alias(dst, src))
                  : (STRCPY_CASE2 openosc_strcpy_chk_warn(_sz, dst, src)))
               : (STRCPY_CASE3 __openosc_strcpy_to_buf(_sz, dst, src)))
            : (STRCPY_CASE4 __openosc_strcpy_alias(dst, src)));
}


/* Mapping for strncpy */

extern char *
__openosc_strncpy_to_buf(size_t dest_len, char *dst,
		 const char *src, size_t len);
extern char *__REDIRECT_NTH (__openosc_strncpy_alias,
                             (char *dst, const char *src, size_t len), strncpy);

#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("strncpy"))
char *
openosc_strncpy_chk_warn (size_t _sz, char *dst, const char *src, size_t len)
{
    return __openosc_strncpy_to_buf(_sz, dst, src, len);
}
#else
extern char *__REDIRECT_NTH (openosc_strncpy_chk_warn,
                             (size_t dest_len, char *dst, const char *src, size_t n),
                             __openosc_strncpy_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("strncpy"));
#endif

__openosc_fortify_function char *
__NTH (strncpy (char *__restrict __pass_objsize1 dst, const char *__restrict src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, len), __dst_overflow_msg("strncpy"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (STRNCPY_CASE1 __openosc_strncpy_alias(dst, src, len))
                  : (STRNCPY_CASE2 openosc_strncpy_chk_warn(_sz, dst, src, len)))
               : (STRNCPY_CASE3 __openosc_strncpy_to_buf(_sz, dst, src, len)))
            : (STRNCPY_CASE4 __openosc_strncpy_alias(dst, src, len)));
}

/*
 * When <string.h> is included, clang will replace strncpy with __builtin_strncpy in C preprocessing.
 * When <string.h> is not included, clang will keep strncpy in C preprocessing. Not sure why.
 * However, openosc.h is included before any other header file, we never know if <string.h> is included or not,
 * so we cannot conditionally use strncpy or __builtin_strncpy. But it does not hurt to define both of them.
 * Therefore, we decided to define both of them, and this works well.
 * Same thing has been done for strncat function.
 */
__openosc_fortify_function char *
__NTH (__builtin_strncpy (char *__restrict __pass_objsize1 dst, const char *__restrict __pass_objsize1 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, len), __dst_overflow_msg("strncpy"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (STRNCPY_CASE1 __openosc_strncpy_alias(dst, src, len))
                  : (STRNCPY_CASE2 openosc_strncpy_chk_warn(_sz, dst, src, len)))
               : (STRNCPY_CASE3 __openosc_strncpy_to_buf(_sz, dst, src, len)))
            : (STRNCPY_CASE4 __openosc_strncpy_alias(dst, src, len)));
}


/* Mapping for strcat */

extern char *
__openosc_strcat_to_buf(size_t dest_len, char *dst, const char *src);
extern char *__REDIRECT_NTH (__openosc_strcat_alias,
                             (char *dst, const char *src), strcat);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("strcat"))
char *
openosc_strcat_chk_warn (size_t _sz, char *dst, const char *src)
{
    return __openosc_strcat_to_buf(_sz, dst, src);
}
#else
extern char *__REDIRECT_NTH (openosc_strcat_chk_warn,
                             (size_t dest_len, char *dst, const char *src),
                             __openosc_strcat_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("strcat"));
#endif

__openosc_fortify_function char *
__NTH (strcat (char *__restrict __pass_objsize1 dst, const char *__restrict src))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, strlen(src)), __dst_overflow_msg("strcat"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(strlen(src));
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > strlen(src))
                  ? (STRCAT_CASE1 __openosc_strcat_to_buf(_sz, dst, src))
                  : (STRCAT_CASE2 openosc_strcat_chk_warn(_sz, dst, src)))
               : (STRCAT_CASE3 __openosc_strcat_to_buf(_sz, dst, src)))
            : (STRCAT_CASE4 __openosc_strcat_alias(dst, src)));
}


/* Mapping for strncat */

extern char *
__openosc_strncat_to_buf(size_t dest_len, char *dst,
		 const char *src, size_t len);
extern char *__REDIRECT_NTH (__openosc_strncat_alias,
                             (char *dst, const char *src, size_t len), strncat);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("strncat"))
char *
openosc_strncat_chk_warn (size_t _sz, char *dst, const char *src, size_t len)
{
    return __openosc_strncat_to_buf(_sz, dst, src, len);
}
#else
extern char *__REDIRECT_NTH (openosc_strncat_chk_warn,
                             (size_t dest_len, char *dst, const char *src, size_t n),
                             __openosc_strncat_to_buf)
     __warn_or_error_attr (__dst_overflow_msg("strncat"));
#endif

__openosc_fortify_function char *
__NTH (strncat (char *__restrict __pass_objsize1 dst, const char *__restrict __pass_objsize1 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, len), __dst_overflow_msg("strncat"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (STRNCAT_CASE1 __openosc_strncat_alias(dst, src, len))
                  : (STRNCAT_CASE2 openosc_strncat_chk_warn(_sz, dst, src, len)))
               : (STRNCAT_CASE3 __openosc_strncat_to_buf(_sz, dst, src, len)))
            : (STRNCAT_CASE4 __openosc_strncat_alias(dst, src, len)));
}


__openosc_fortify_function char *
__NTH (__builtin_strncat (char *__restrict __pass_objsize1 dst, const char *__restrict __pass_objsize1 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, len), __dst_overflow_msg("strncat"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (STRNCAT_CASE1 __openosc_strncat_alias(dst, src, len))
                  : (STRNCAT_CASE2 openosc_strncat_chk_warn(_sz, dst, src, len)))
               : (STRNCAT_CASE3 __openosc_strncat_to_buf(_sz, dst, src, len)))
            : (STRNCAT_CASE4 __openosc_strncat_alias(dst, src, len)));
}


/* Mapping for strnlen */

extern size_t
__openosc_strnlen_from_buf(size_t len, const char * src, size_t maxlen);
extern size_t __REDIRECT_NTH (__openosc_strnlen_alias,
                             (const char *src, size_t len), strnlen);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("strnlen"))
size_t
openosc_strnlen_chk_warn (size_t _sz, const char *src, size_t len)
{
    return __openosc_strnlen_from_buf(_sz, src, len);
}
#else
extern size_t __REDIRECT_NTH (openosc_strnlen_chk_warn,
                             (size_t dest_len, const char *src, size_t n),
                             __openosc_strnlen_from_buf)
     __warn_or_error_attr ("strnlen caller with bigger length than size of "
                       "source buffer");
#endif

__openosc_fortify_function size_t
__NTH (strnlen (const char *__restrict __pass_objsize1 src, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, src, len),
           "strnlen caller with bigger length than size of source buffer")
{
    size_t _sz = __builtin_object_size(src, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (STRNLEN_CASE1 __openosc_strnlen_alias(src, len))
                  : (STRNLEN_CASE2 openosc_strnlen_chk_warn(_sz, src, len)))
               : (STRNLEN_CASE3 __openosc_strnlen_from_buf(_sz, src, len)))
            : (STRNLEN_CASE4 __openosc_strnlen_alias(src, len)));
}

#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vsnprintf */

extern int
__openosc_vsnprintf_to_buf(size_t dest_len, char *str, size_t len,
		   const char *fmt, va_list ap);
extern int __REDIRECT_NTH (__openosc_vsnprintf_alias,
                             (char *str, size_t len, const char *fmt, va_list ap), vsnprintf);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("vsnprintf"))
int
openosc_vsnprintf_chk_warn (size_t _sz, char *str, size_t len, const char *fmt, va_list ap)
{
    return __openosc_vsnprintf_to_buf(_sz, str, len, fmt, ap);
}
#else
extern int __REDIRECT_NTH (openosc_vsnprintf_chk_warn,
                             (size_t dest_len, char *str, size_t len, const char *fmt, va_list ap),
                             __openosc_vsnprintf_to_buf)
     __warn_or_error_attr ("vsnprintf caller with bigger length than size of "
                       "destination buffer");
#endif

__openosc_fortify_function int
__NTH (vsnprintf (char *__restrict __pass_objsize1 dst, size_t len, const char *__restrict fmt, va_list ap))
__clang_warn_or_error_if(__size_too_small (__bos1, dst, len), __dst_overflow_msg("vsnprintf"))
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (VSNPRINTF_CASE1 __openosc_vsnprintf_alias(dst, len, fmt, ap))
                  : (VSNPRINTF_CASE2 openosc_vsnprintf_chk_warn(_sz, dst, len, fmt, ap)))
               : (VSNPRINTF_CASE3 __openosc_vsnprintf_to_buf(_sz, dst, len, fmt, ap)))
            : (VSNPRINTF_CASE4 __openosc_vsnprintf_alias(dst, len, fmt, ap)));
}

#endif /* OPENOSC_VALIST_NOSUPPORT */

#ifdef __cplusplus
}
#endif

#endif  /* ifndef __OPENOSC_REDIRECT_NOMAP_H__ */

#endif /* __OPENOSC_REDIRECT_MAP_H__ */
