/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#ifndef __OPENOSC_REDIRECT_NOMAP_H__
#define __OPENOSC_REDIRECT_NOMAP_H__

/* openosc_redirct_map.h and openosc_redirect_nomap.h are mutually exclusive */
#ifndef __OPENOSC_REDIRECT_MAP_H__

/* if OSC metric feature is disabled, we can completely exclude this osc_nomap.h header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_extern.h"


/* Mapping for memcpy */

extern void *__REDIRECT_NTH (__openosc_memcpy_alias,
                             (void *dst, const void *src, size_t len), memcpy);

__openosc_fortify_function void *
__NTH (memcpy (void *__restrict dst, const void *__restrict src, size_t len))
{
    return (MEMCPY_NOMAP_CASE __openosc_memcpy_alias(dst, src, len));
}

/* Mapping for memmove */

extern void *__REDIRECT_NTH (__openosc_memmove_alias,
                             (void *dst, const void *src, size_t len), memmove);

__openosc_fortify_function void *
__NTH (memmove (void *__restrict dst, const void *__restrict src, size_t len))
{
    return (MEMMOVE_NOMAP_CASE __openosc_memmove_alias(dst, src, len));
}

/* Mapping for memset */

extern void *__REDIRECT_NTH (__openosc_memset_alias,
                             (void *dst, int c, size_t len), memset);

__openosc_fortify_function void *
__NTH (memset (void *__restrict dst, int c, size_t len))
{
    return (MEMSET_NOMAP_CASE __openosc_memset_alias(dst, c, len));
}

/* Mapping for bcopy */

extern void __REDIRECT_NTH (__openosc_bcopy_alias,
                             (const void *src, void *dst, size_t len), bcopy);

__openosc_fortify_function void
__NTH (bcopy (const void *__restrict src, void *__restrict dst, size_t len))
{
    (BCOPY_NOMAP_CASE __openosc_bcopy_alias(src, dst, len));
}

/* Mapping for bzero */

extern void __REDIRECT_NTH (__openosc_bzero_alias,
                             (void *dst, size_t len), bzero);

__openosc_fortify_function void
__NTH (bzero (void *__restrict dst, size_t len))
{
    (BZERO_NOMAP_CASE __openosc_bzero_alias(dst, len));
}

/* Mapping for strcpy */

extern char *__REDIRECT_NTH (__openosc_strcpy_alias,
                             (char *dst, const char *src), strcpy);

__openosc_fortify_function char *
__NTH (strcpy (char *__restrict dst, const char *__restrict src))
{
    return (STRCPY_NOMAP_CASE __openosc_strcpy_alias(dst, src));
}

/* Mapping for strncpy */

extern char *__REDIRECT_NTH (__openosc_strncpy_alias,
                             (char *dst, const char *src, size_t len), strncpy);

__openosc_fortify_function char *
__NTH (strncpy (char *__restrict dst, const char *__restrict src, size_t len))
{
    return (STRNCPY_NOMAP_CASE __openosc_strncpy_alias(dst, src, len));
}

/* Mapping for strcat */

extern char *__REDIRECT_NTH (__openosc_strcat_alias,
                             (char *dst, const char *src), strcat);

__openosc_fortify_function char *
__NTH (strcat (char *__restrict dst, const char *__restrict src))
{
    return (STRCAT_NOMAP_CASE __openosc_strcat_alias(dst, src));
}

/* Mapping for strncat */

extern char *__REDIRECT_NTH (__openosc_strncat_alias,
                             (char *dst, const char *src, size_t len), strncat);

__openosc_fortify_function char *
__NTH (strncat (char *__restrict dst, const char *__restrict src, size_t len))
{
    return (STRNCAT_NOMAP_CASE __openosc_strncat_alias(dst, src, len));
}

/* Mapping for strnlen */

extern size_t __REDIRECT_NTH (__openosc_strnlen_alias,
                              (const char *s, size_t maxlen), strnlen);

__openosc_fortify_function size_t
__NTH (strnlen (const char *__restrict s, size_t maxlen))
{
    return (STRNLEN_NOMAP_CASE __openosc_strnlen_alias(s, maxlen));
}

#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vsnprintf */

extern int __REDIRECT_NTH (__openosc_vsnprintf_alias,
                           (char *str, size_t len, const char *fmt, va_list ap), vsnprintf);

__openosc_fortify_function int
__NTH (vsnprintf (char *__restrict str, size_t len, const char *__restrict fmt, va_list ap))
{
    return (VSNPRINTF_NOMAP_CASE __openosc_vsnprintf_alias(str, len, fmt, ap));
}

#endif /* OPENOSC_VALIST_NOSUPPORT */

#ifdef HAS_SAFEC
#include "openosc_safec_nomap.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif /* ifndef __OPENOSC_REDIRECT_MAP_H__ */

#endif /* __OPENOSC_REDIRECT_NOMAP_H__ */

