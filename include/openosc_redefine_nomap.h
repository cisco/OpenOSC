/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_REDEFINE_NOMAP_H__
#define __OPENOSC_REDEFINE_NOMAP_H__

/* openosc_redefine_map.h and openosc_redefine_nomap.h are mutually exclusive */
#ifndef __OPENOSC_REDEFINE_MAP_H__

/* if OSC metric feature is disabled, we can completely exclude this osc_nomap.h header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_extern.h"


/* Mapping for memcpy */

static inline __attribute__ ((always_inline)) void *
openosc_memcpy (void *dst, const void *src, size_t len)
  OSC_THROW
{
    return (MEMCPY_NOMAP_CASE memcpy(dst, src, len));
}

#undef memcpy
#define memcpy(dest, src, len) \
        openosc_memcpy(dest, src, len)

/* Mapping for memmove */

static inline __attribute__ ((always_inline)) void *
openosc_memmove (void *dst, const void *src, size_t len)
  OSC_THROW
{
    return (MEMMOVE_NOMAP_CASE memmove(dst, src, len));
}

#undef memmove
#define memmove(dest, src, len) \
        openosc_memmove(dest, src, len)

/* Mapping for memset */

static inline __attribute__ ((always_inline)) void *
openosc_memset (void *dst, int c, size_t len)
  OSC_THROW
{
    return (MEMSET_NOMAP_CASE memset(dst, c, len));
}

#undef memset
#define memset(dst, c, len) \
        openosc_memset(dst, c, len)

/* Mapping for bcopy */

static inline __attribute__ ((always_inline)) void
openosc_bcopy (const void *src, void *dst, size_t len)
  OSC_THROW
{
    return (BCOPY_NOMAP_CASE bcopy(src, dst, len));
}

#undef bcopy
#define bcopy(src, dst, len) \
        openosc_bcopy(src, dst, len)

/* Mapping for bzero */

static inline __attribute__ ((always_inline)) void
openosc_bzero (void *dst, size_t len)
  OSC_THROW
{
    return (BZERO_NOMAP_CASE bzero(dst, len));
}

#undef bzero
#define bzero(dst, len) \
        openosc_bzero(dst, len)

/* Mapping for strcpy */

static inline __attribute__ ((always_inline)) char *
openosc_strcpy (char *dst, const char *src)
  OSC_THROW
{
    return (STRCPY_NOMAP_CASE strcpy(dst, src));
}

#undef strcpy
#define strcpy(dst, src) \
        openosc_strcpy(dst, src)


/* Mapping for strncpy */
#define _HAVE_STRING_ARCH_strncpy 1

static inline __attribute__ ((always_inline)) char *
openosc_strncpy (char *dst, const char *src, size_t len)
  OSC_THROW
{
    return (STRNCPY_NOMAP_CASE strncpy(dst, src, len));
}

#undef strncpy
#define strncpy(dest, src, len) \
        openosc_strncpy(dest, src, len)

/* Mapping for strcat */

static inline __attribute__ ((always_inline)) char *
openosc_strcat (char *dst, const char *src)
  OSC_THROW
{
    return (STRCAT_NOMAP_CASE strcat(dst, src));
}

#undef strcat
#define strcat(dst, src) \
        openosc_strcat(dst, src)

/* Mapping for strncat */
#define _HAVE_STRING_ARCH_strncat 1

static inline __attribute__ ((always_inline)) char *
openosc_strncat (char *dst, const char *src, size_t len)
  OSC_THROW
{
    return (STRNCAT_NOMAP_CASE strncat(dst, src, len));
}

#undef strncat
#define strncat(dst, src, len) \
         openosc_strncat(dst, src, len)

/* Mapping for strnlen */

#define HAVE_STRNLEN 1

static inline __attribute__ ((always_inline)) size_t
openosc_strnlen (const char *s, size_t maxlen)
  OSC_THROW
{
    return (STRNLEN_NOMAP_CASE strnlen(s, maxlen));
}

#undef strnlen
#define strnlen(s, maxlen)  \
        openosc_strnlen(s, maxlen)

#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vsnprintf */

static inline __attribute__ ((always_inline)) int
openosc_vsnprintf (char *str, size_t len,
           const char *fmt, va_list ap)
  OSC_THROW
{
    return (VSNPRINTF_NOMAP_CASE vsnprintf(str, len, fmt, ap));
}

#undef vsnprintf
#define vsnprintf(str, len, format, ap)  \
        openosc_vsnprintf(str, len, format, ap)

/* avoid redefinition */
#define HAVE_VSNPRINTF 1

#endif /* OPENOSC_VALIST_NOSUPPORT */

#ifdef HAS_SAFEC
#include "openosc_safec_nomap.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif /* ifndef __OPENOSC_REDEFINE_MAP_H__ */

#endif /* __OPENOSC_REDEFINE_NOMAP_H__ */

