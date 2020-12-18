/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_METRIC_ONLY_H__
#define __OPENOSC_METRIC_ONLY_H__

/* if OSC metric feature is disabled, we can completely exclude this header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#if !defined  __OPTIMIZE__
#ifndef OPENOSC_NOMAP_METRIC_ONLY
#define OPENOSC_NOMAP_METRIC_ONLY
#endif
#endif

#ifdef _FORTIFY_SOURCE
#if __clang__
#warning "The OSC-METRICS feature suppresses fortify-source buffer-overflow warnings for clang"
#else
#warning "The OSC-METRICS feature suppresses some function-attribute warnings, like -Wunused-result/-Wnonnull"
#endif
#endif


#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif


#include "openosc_extern.h"
#include "openosc_fortify.h"

#include "openosc_nomap_metric.h"
#include "openosc_map_metric.h"

#ifndef OPENOSC_NOT_GNU_SOURCE
/* by default, extra GNU functions are supported */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#ifndef OPENOSC_DISABLE_STRING_H_FUNCS
#include "string.h"
#endif /* OPENOSC_DISABLE_STRING_H_FUNCS */


#ifndef OPENOSC_DISABLE_STRING_H_FUNCS

/* Mapping for memcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) void *
openosc_memcpy (void *dst, const void *src, size_t len)
  OSC_THROW
{
    return (MEMCPY_NOMAP_CASE memcpy(dst, src, len));
}

#else

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
                        : (MEMCPY_CASE8 memcpy(dst, src, len)))
                     : (MEMCPY_CASE1 memcpy(dst, src, len)))
                  : (MEMCPY_CASE2 memcpy(dst, src, len)))
               : (MEMCPY_CASE3 memcpy(dst, src, len)))
            : ((_src_sz != (size_t) -1)
               ? (is_len_constant
                  ? ((_src_sz >= len)
                     ? (MEMCPY_CASEa memcpy(dst, src, len))
                     : (MEMCPY_CASEb memcpy(dst, src, len)))
                  : (MEMCPY_CASE9 memcpy(dst, src, len)))
               : (MEMCPY_CASE4 memcpy(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMCPY_CASE1 memcpy(dst, src, len))
                  : (MEMCPY_CASE2 memcpy(dst, src, len)))
               : (MEMCPY_CASE3 memcpy(dst, src, len)))
            : (MEMCPY_CASE4 memcpy(dst, src, len)));
#endif
}
#endif

#undef memcpy
#define memcpy(dest, src, len) \
        openosc_memcpy(dest, src, len)


/* Mapping for memmove */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) void *
openosc_memmove (void *dst, const void *src, size_t len)
  OSC_THROW
{
    return (MEMMOVE_NOMAP_CASE memmove(dst, src, len));
}

#else

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
                        : (MEMMOVE_CASE8 memmove(dst, src, len)))
                     : (MEMMOVE_CASE1 memmove(dst, src, len)))
                  : (MEMMOVE_CASE2 memmove(dst, src, len)))
               : (MEMMOVE_CASE3 memmove(dst, src, len)))
            : ((_src_sz != (size_t) -1)
               ? (is_len_constant
                  ? ((_src_sz >= len)
                     ? (MEMMOVE_CASEa memmove(dst, src, len))
                     : (MEMMOVE_CASEb memmove(dst, src, len)))
                  : (MEMMOVE_CASE9 memmove(dst, src, len)))
               : (MEMMOVE_CASE4 memmove(dst, src, len))));
#else
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MEMMOVE_CASE1 memmove(dst, src, len))
                  : (MEMMOVE_CASE2 memmove(dst, src, len)))
               : (MEMMOVE_CASE3 memmove(dst, src, len)))
            : (MEMMOVE_CASE4 memmove(dst, src, len)));
#endif
}
#endif

#undef memmove
#define memmove(dest, src, len) \
        openosc_memmove(dest, src, len)

/* Mapping for memset */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) void *
openosc_memset (void *dst, int c, size_t len)
  OSC_THROW
{
    return (MEMSET_NOMAP_CASE memset(dst, c, len));
}

#else

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
                  : (MEMSET_CASE2 memset(dst, c, len)))
               : (MEMSET_CASE3 memset(dst, c, len)))
            : (MEMSET_CASE4 memset(dst, c, len)));
}
#endif

#undef memset
#define memset(dst, c, len) \
        openosc_memset(dst, c, len)


/* Mapping for bcopy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) void
openosc_bcopy (const void *src, void *dst, size_t len)
  OSC_THROW
{
    return (BCOPY_NOMAP_CASE bcopy(src, dst, len));
}

#else

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
                      : (BCOPY_CASE8 bcopy(src, dst, len)))
                   : (BCOPY_CASE1 bcopy(src, dst, len))) 
                : (BCOPY_CASE2 bcopy(src, dst, len)))
             : (BCOPY_CASE3 bcopy(src, dst, len)))
          : ((_src_sz != (size_t) -1)
             ? (is_len_constant
                ? ((_src_sz >= len)
                   ? (BCOPY_CASEa bcopy(src, dst, len))
                   : (BCOPY_CASEb bcopy(src, dst, len)))
                : (BCOPY_CASE9 bcopy(src, dst, len)))
             : (BCOPY_CASE4 bcopy(src, dst, len))));
#else
    ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (BCOPY_CASE1 bcopy(src, dst, len))
                  : (BCOPY_CASE2 bcopy(src, dst, len)))
               : (BCOPY_CASE3 bcopy(src, dst, len)))
            : (BCOPY_CASE4 bcopy(src, dst, len)));
#endif
}
#endif

#undef bcopy
#define bcopy(src, dst, len) \
        openosc_bcopy(src, dst, len)

/* Mapping for bzero */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) void
openosc_bzero (void *dst, size_t len)
  OSC_THROW
{
    return (BZERO_NOMAP_CASE bzero(dst, len));
}

#else

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
                : (BZERO_CASE2 bzero(dst, len)))
             : (BZERO_CASE3 bzero(dst, len)))
          : (BZERO_CASE4 bzero(dst, len)));
}
#endif

#undef bzero
#define bzero(dst, len) \
        openosc_bzero(dst, len)


/* Mapping for strcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) char *
openosc_strcpy (char *dst, const char *src)
  OSC_THROW
{
    return (STRCPY_NOMAP_CASE strcpy(dst, src));
}

#else

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
                  : (STRCPY_CASE2 strcpy(dst, src)))
               : (STRCPY_CASE3 strcpy(dst, src)))
            : (STRCPY_CASE4 strcpy(dst, src)));
}
#endif

#undef strcpy
#define strcpy(dst, src) \
        openosc_strcpy(dst, src)


/* Mapping for strncpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) char *
openosc_strncpy (char *dst, const char *src, size_t len)
  OSC_THROW
{
    return (STRNCPY_NOMAP_CASE strncpy(dst, src, len));
}

#else

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
                  : (STRNCPY_CASE2 strncpy(dst, src, len)))
               : (STRNCPY_CASE3 strncpy(dst, src, len)))
            : (STRNCPY_CASE4 strncpy(dst, src, len)));
}
#endif

#undef strncpy
#define strncpy(dest, src, len) \
        openosc_strncpy(dest, src, len)

/* Mapping for strcat */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) char *
openosc_strcat (char *dst, const char *src)
  OSC_THROW
{
    return (STRCAT_NOMAP_CASE strcat(dst, src));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_strcat (char *dst, const char *src)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(strlen(src));
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > strlen(src))
                  ? (STRCAT_CASE1 strcat(dst, src))
                  : (STRCAT_CASE2 strcat(dst, src)))
               : (STRCAT_CASE3 strcat(dst, src)))
            : (STRCAT_CASE4 strcat(dst, src)));
}
#endif

#undef strcat
#define strcat(dst, src) \
        openosc_strcat(dst, src)

/* Mapping for strncat */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) char *
openosc_strncat (char *dst, const char *src, size_t len)
  OSC_THROW
{
    return (STRNCAT_NOMAP_CASE strncat(dst, src, len));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_strncat (char *dst, const char *src, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dst, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz > len)
                  ? (STRNCAT_CASE1 strncat(dst, src, len))
                  : (STRNCAT_CASE2 strncat(dst, src, len)))
               : (STRNCAT_CASE3 strncat(dst, src, len)))
            : (STRNCAT_CASE4 strncat(dst, src, len)));
}
#endif

#undef strncat
#define strncat(dst, src, len) \
         openosc_strncat(dst, src, len)

/* Mapping for strnlen */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) size_t
openosc_strnlen (const char *s, size_t maxlen)
  OSC_THROW
{
    return (STRNLEN_NOMAP_CASE strnlen(s, maxlen));
}

#else

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
                : (STRNLEN_CASE2 strnlen(s, len)))
             : (STRNLEN_CASE3 strnlen(s, len)))
          : (STRNLEN_CASE4 strnlen(s, len)));
}
#endif

#undef strnlen
#define strnlen(s, maxlen)  \
        openosc_strnlen(s, maxlen)

#endif /* OPENOSC_DISABLE_STRING_H_FUNCS */

#ifdef HAS_SAFEC
#include "openosc_safec_nomap.h"
#endif

#ifndef OPENOSC_FORTIFY_FUNCTIONS_DISABLE
#include "openosc_metric_only2.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif /* __OPENOSC_METRIC_ONLY_H__ */

