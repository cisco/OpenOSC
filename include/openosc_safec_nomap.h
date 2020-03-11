/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_SAFEC_NOMAP_H__
#define __OPENOSC_SAFEC_NOMAP_H__

/* osc_safec_map.h and osc_safec_nomap.h are mutually exclusive */
#ifndef __OPENOSC_SAFEC_MAP_H__

/* if OSC metric feature is disabled, we can completely exclude this header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#include "openosc_safec_nomap_metric.h"
#include "openosc_extern.h"

/* Mapping for memcmp_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_memcmp_s (const void *s1, rsize_t s1max,
	      const void *s2,  rsize_t n, int *diff)
{
    return (MEMCMP_S_NOMAP_CASE memcmp_s(s1, s1max, s2, n, diff));
}

#undef memcmp_s
#define memcmp_s(s1, s1max, s2, n, diff) \
    openosc_memcmp_s (s1, s1max, s2, n, diff)

/* Mapping for memcpy_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_memcpy_s (void *dest, rsize_t dmax, const void *src, rsize_t n)
{
    return (MEMCPY_S_NOMAP_CASE memcpy_s(dest, dmax, src, n));
}

#undef memcpy_s
#define memcpy_s(dest, dmax, src, n) \
    openosc_memcpy_s (dest, dmax, src, n)

/* Mapping for strcat_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strcat_s (char *dest, rsize_t dmax, const char *src)
{
    return (STRCAT_S_NOMAP_CASE strcat_s(dest, dmax, src));
}

#undef strcat_s
#define strcat_s(dest, dmax, src) \
    openosc_strcat_s (dest, dmax, src)

/* Mapping for strcmp_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strcmp_s (const char *s1, rsize_t s1max,
	      const char *s2, int *indicator)
{
    return (STRCMP_S_NOMAP_CASE strcmp_s(s1, s1max, s2, indicator));
}

#undef strcmp_s
#define strcmp_s(s1, slmax, s2, indicator)	\
    openosc_strcmp_s (s1, slmax, s2, indicator)

/* Mapping for strcpy_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strcpy_s (char *dest, rsize_t dmax, const char *src)
{
    return (STRCPY_S_NOMAP_CASE strcpy_s(dest, dmax, src));
}

#undef strcpy_s
#define strcpy_s(dest, dmax, src) \
    openosc_strcpy_s (dest, dmax, src)

/* Mapping for strncat_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strncat_s (char *dest, rsize_t dmax, const char *src, rsize_t n)
{
    return (STRNCAT_S_NOMAP_CASE strncat_s(dest, dmax, src, n));
}

#undef strncat_s
#define strncat_s(dest, dmax, src, n) \
    openosc_strncat_s (dest, dmax, src, n)

/* Mapping for strncpy_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strncpy_s (char *dest, rsize_t dmax, const char *src, rsize_t n)
{
    return (STRNCPY_S_NOMAP_CASE strncpy_s(dest, dmax, src, n));
}

#undef strncpy_s
#define strncpy_s(dest, dmax, src, n) \
    openosc_strncpy_s (dest, dmax, src, n)

/* Mapping for strnlen_s */

static inline __attribute__ ((always_inline)) size_t
openosc_strnlen_s (const char *s, size_t maxsize)
{
    return (STRNLEN_S_NOMAP_CASE strnlen_s(s, maxsize));
}

#undef strnlen_s
#define strnlen_s(s, maxsize) \
    openosc_strnlen_s (s, maxsize)

/* Mapping for strstr_s */

static inline __attribute__ ((always_inline)) errno_t
openosc_strstr_s (char *s1, rsize_t s1max,
	      const char *s2, rsize_t s2max, char **substring)
{
    return (STRSTR_S_NOMAP_CASE strstr_s(s1, s1max, s2, s2max, substring));
}

#undef strstr_s
#define strstr_s(s1, s1max, s2, s2max, substring) \
    openosc_strstr_s (s1, s1max, s2, s2max, substring)

#endif /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif /* ifndef __OPENOSC_SAFEC_MAP_H__ */

#endif /* __OPENOSC_SAFEC_NOMAP_H__ */

