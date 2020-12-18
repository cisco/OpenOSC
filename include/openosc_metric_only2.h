/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_METRIC_ONLY2_H__
#define __OPENOSC_METRIC_ONLY2_H__

/* if OSC metric feature is disabled, we can completely exclude this header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#ifndef _FORTIFY_SOURCE
#include "openosc_fortify_extern.h"
#endif
#include "openosc_fortify_nomap_metric.h"
#include "openosc_fortify_map_metric.h"

#ifndef OPENOSC_NOT_GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS
#include <stdio.h>
#endif
#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS
#include <wchar.h>
#endif
#ifndef OPENOSC_DISABLE_UNISTD_H_FUNCS
#include <unistd.h>
#endif
#ifndef OPENOSC_DISABLE_STDLIB_H_FUNCS
#include <stdlib.h>
#endif
#ifndef OPENOSC_DISABLE_POLL_H_FUNCS
#include <poll.h>
#endif
#ifndef OPENOSC_DISABLE_SOCKET_H_FUNCS
#include <sys/types.h>
#include <sys/socket.h>
#endif

#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS
#ifndef OPENOSC_VALIST_NOSUPPORT

#ifdef __va_arg_pack

#ifndef OPENOSC_ASPRINTF_DISABLE

/* Mapping for asprintf */

static inline __attribute__ ((always_inline))
int
openosc_asprintf (char **strp, const char *fmt, ...)
{
    return (ASPRINTF_NOMAP_CASE asprintf(strp, fmt, __va_arg_pack ()));
}

#undef asprintf
#define asprintf		openosc_asprintf

#endif /* OPENOSC_ASPRINTF_DISABLE */


/* Mapping for dprintf */

static inline __attribute__ ((always_inline))
int
openosc_dprintf (int fd, const char *format, ...)
{
    return (DPRINTF_NOMAP_CASE dprintf(fd, format, __va_arg_pack ()));
}

#undef dprintf
#define dprintf		openosc_dprintf


/* Mapping for fprintf */

static inline __attribute__ ((always_inline))
int
openosc_fprintf (FILE *stream, const char *format, ...)
{
    return (FPRINTF_NOMAP_CASE fprintf(stream, format, __va_arg_pack ()));
}

#undef fprintf
#define fprintf		openosc_fprintf


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for fwprintf */

static inline __attribute__ ((always_inline))
int
openosc_fwprintf (FILE *stream, const wchar_t *format, ...)
{
    return (FWPRINTF_NOMAP_CASE fwprintf(stream, format, __va_arg_pack ()));
}

#undef fwprintf
#define fwprintf		openosc_fwprintf

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */


/* Mapping for printf */

static inline __attribute__ ((always_inline))
int
openosc_printf (const char *format, ...)
{
    return (PRINTF_NOMAP_CASE printf(format, __va_arg_pack ()));
}

#undef printf
#define printf		openosc_printf


/* Mapping for snprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_snprintf (char *str, size_t size, const char *format, ...)
{
    return (SNPRINTF_NOMAP_CASE snprintf(str, size, format, __va_arg_pack ()));
}

#else

static inline __attribute__ ((always_inline))
int
openosc_snprintf (char *s, size_t maxlen, const char *format, ...)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(maxlen);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= maxlen)
                  ? (SNPRINTF_CASE1 snprintf(s, maxlen, format, __va_arg_pack ()))
                  : (SNPRINTF_CASE2 snprintf(s, maxlen, format, __va_arg_pack ())))
               : (SNPRINTF_CASE3 snprintf(s, maxlen, format, __va_arg_pack ())))
            : (SNPRINTF_CASE4 snprintf(s, maxlen, format, __va_arg_pack ())));
}
#endif

#undef snprintf
#define snprintf		openosc_snprintf


/* Mapping for sprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_sprintf (char *str, const char *format, ...)
{
    return (SPRINTF_NOMAP_CASE sprintf(str, format, __va_arg_pack ()));
}

#else

static inline __attribute__ ((always_inline))
int
openosc_sprintf (char *s, const char *format, ...)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
           ? (SPRINTF_CASE3 sprintf(s, format, __va_arg_pack ()))
           : (SPRINTF_CASE4 sprintf(s, format, __va_arg_pack ())));
}
#endif

#undef sprintf
#define sprintf		openosc_sprintf


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for swprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_swprintf (wchar_t *wcs, size_t maxlen, const wchar_t *format, ...)
  OSC_THROW
{
    return (SWPRINTF_NOMAP_CASE swprintf(wcs, maxlen, format, __va_arg_pack ()));
}

#else

static inline __attribute__ ((always_inline))
int
openosc_swprintf (wchar_t *s, size_t n, const wchar_t *format, ...)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (SWPRINTF_CASE1 swprintf(s, n, format, __va_arg_pack ()))
                  : (SWPRINTF_CASE2 swprintf(s, n, format, __va_arg_pack ())))
               : (SWPRINTF_CASE3 swprintf(s, n, format, __va_arg_pack ())))
            : (SWPRINTF_CASE4 swprintf(s, n, format, __va_arg_pack ())));
}
#endif

#undef swprintf
#define swprintf		openosc_swprintf


/* Mapping for wprintf */

static inline __attribute__ ((always_inline))
int
openosc_wprintf (const wchar_t *format, ...)
{
    return (WPRINTF_NOMAP_CASE wprintf(format, __va_arg_pack ()));
}

#undef wprintf
#define wprintf		openosc_wprintf

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */

#endif /* __va_arg_pack */

#endif /* OPENOSC_VALIST_NOSUPPORT */
#endif /* OPENOSC_DISABLE_STDIO_H_FUNCS */


#ifndef OPENOSC_DISABLE_UNISTD_H_FUNCS

/* Mapping for confstr */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_confstr (int name, char *buf, size_t len)
  OSC_THROW
{
    return (CONFSTR_NOMAP_CASE confstr(name, buf, len));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_confstr (int name, char *buf, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (CONFSTR_CASE1 confstr(name, buf, len))
                  : (CONFSTR_CASE2 confstr(name, buf, len)))
               : (CONFSTR_CASE3 confstr(name, buf, len)))
            : (CONFSTR_CASE4 confstr(name, buf, len)));
}
#endif

#undef confstr
#define confstr(name, buf, len)		openosc_confstr(name, buf, len)

#endif /* OPENOSC_DISABLE_UNISTD_H_FUNCS */


#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS
#ifndef OPENOSC_FGETS_DISABLE

/* Mapping for fgets */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_fgets (char *s, int size, FILE *stream)
{
    return (FGETS_NOMAP_CASE fgets(s, size, stream));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_fgets (char *s, int size, FILE *stream)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((size>0 && _sz >= (size_t)size)
                  ? (FGETS_CASE1 fgets(s, size, stream))
                  : (FGETS_CASE2 fgets(s, size, stream)))
               : (FGETS_CASE3 fgets(s, size, stream)))
            : (FGETS_CASE4 fgets(s, size, stream)));
}
#endif

#undef fgets
#define fgets(s, size, stream)		openosc_fgets(s, size, stream)

#endif /* OPENOSC_FGETS_DISABLE */


/* Mapping for fgets_unlocked */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_fgets_unlocked (char *s, int n, FILE *stream)
{
    return (FGETS_UNLOCKED_NOMAP_CASE fgets_unlocked(s, n, stream));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_fgets_unlocked (char *s, int n, FILE *stream)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
                  ? (FGETS_UNLOCKED_CASE1 fgets_unlocked(s, n, stream))
                  : (FGETS_UNLOCKED_CASE2 fgets_unlocked(s, n, stream)))
               : (FGETS_UNLOCKED_CASE3 fgets_unlocked(s, n, stream)))
            : (FGETS_UNLOCKED_CASE4 fgets_unlocked(s, n, stream)));
}
#endif

#undef fgets_unlocked
#define fgets_unlocked(s, n, stream)		openosc_fgets_unlocked(s, n, stream)

#endif /* OPENOSC_DISABLE_STDIO_H_FUNCS */


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for fgetws */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_fgetws (wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_NOMAP_CASE fgetws(ws, n, stream));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_fgetws (wchar_t *ws, int n, FILE *stream)
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
                  ? (FGETWS_CASE1 fgetws(ws, n, stream))
                  : (FGETWS_CASE2 fgetws(ws, n, stream)))
               : (FGETWS_CASE3 fgetws(ws, n, stream)))
            : (FGETWS_CASE4 fgetws(ws, n, stream)));
}
#endif

#undef fgetws
#define fgetws(ws, n, stream)		openosc_fgetws(ws, n, stream)


/* Mapping for fgetws_unlocked */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_fgetws_unlocked (wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_UNLOCKED_NOMAP_CASE fgetws_unlocked(ws, n, stream));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_fgetws_unlocked (wchar_t *ws, int n, FILE *stream)
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
                  ? (FGETWS_UNLOCKED_CASE1 fgetws_unlocked(ws, n, stream))
                  : (FGETWS_UNLOCKED_CASE2 fgetws_unlocked(ws, n, stream)))
               : (FGETWS_UNLOCKED_CASE3 fgetws_unlocked(ws, n, stream)))
            : (FGETWS_UNLOCKED_CASE4 fgetws_unlocked(ws, n, stream)));
}
#endif

#undef fgetws_unlocked
#define fgetws_unlocked(ws, n, stream)		openosc_fgetws_unlocked(ws, n, stream)

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */


#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS

/* Mapping for fread */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return (FREAD_NOMAP_CASE fread(ptr, size, nmemb, stream));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && __builtin_constant_p(nmemb)
               ? ((_sz >= size * nmemb)
                  ? (FREAD_CASE1 fread(ptr, size, nmemb, stream))
                  : (FREAD_CASE2 fread(ptr, size, nmemb, stream)))
               : (FREAD_CASE3 fread(ptr, size, nmemb, stream)))
            : (FREAD_CASE4 fread(ptr, size, nmemb, stream)));
}
#endif

#undef fread
#define fread(ptr, size, nmemb, stream)		openosc_fread(ptr, size, nmemb, stream)


#ifndef fread_unlocked

/* Mapping for fread_unlocked */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_fread_unlocked (void *ptr, size_t size, size_t n, FILE *stream)
{
    return (FREAD_UNLOCKED_NOMAP_CASE fread_unlocked(ptr, size, n, stream));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_fread_unlocked (void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && __builtin_constant_p(size)
               ? ((_sz >= n * size)
                  ? (FREAD_UNLOCKED_CASE1 fread_unlocked(ptr, size, n, stream))
                  : (FREAD_UNLOCKED_CASE2 fread_unlocked(ptr, size, n, stream)))
               : (FREAD_UNLOCKED_CASE3 fread_unlocked(ptr, size, n, stream)))
            : (FREAD_UNLOCKED_CASE4 fread_unlocked(ptr, size, n, stream)));
}
#endif

#undef fread_unlocked
#define fread_unlocked(ptr, size, n, stream)		openosc_fread_unlocked(ptr, size, n, stream)

#endif /* fread_unlocked */

#endif /* OPENOSC_DISABLE_STDIO_H_FUNCS */


#ifndef OPENOSC_DISABLE_UNISTD_H_FUNCS

#ifndef OPENOSC_GETCWD_DISABLE

/* Mapping for getcwd */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_getcwd (char *buf, size_t size)
  OSC_THROW
{
    return (GETCWD_NOMAP_CASE getcwd(buf, size));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_getcwd (char *buf, size_t size)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= size)
                  ? (GETCWD_CASE1 getcwd(buf, size))
                  : (GETCWD_CASE2 getcwd(buf, size)))
               : (GETCWD_CASE3 getcwd(buf, size)))
            : (GETCWD_CASE4 getcwd(buf, size)));
}
#endif

#undef getcwd
#define getcwd(buf, size)		openosc_getcwd(buf, size)

#endif /* OPENOSC_GETCWD_DISABLE */


/* Mapping for getdomainname */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_getdomainname (char *name, size_t len)
  OSC_THROW
{
    return (GETDOMAINNAME_NOMAP_CASE getdomainname(name, len));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_getdomainname (char *name, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(name, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (GETDOMAINNAME_CASE1 getdomainname(name, len))
                  : (GETDOMAINNAME_CASE2 getdomainname(name, len)))
               : (GETDOMAINNAME_CASE3 getdomainname(name, len)))
            : (GETDOMAINNAME_CASE4 getdomainname(name, len)));
}
#endif

#undef getdomainname
#define getdomainname(name, len)		openosc_getdomainname(name, len)


/* Mapping for getgroups */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_getgroups (int size, gid_t list[])
  OSC_THROW
{
    return (GETGROUPS_NOMAP_CASE getgroups(size, list));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_getgroups (int size, gid_t list[])
  OSC_THROW
{
    size_t _sz = __builtin_object_size(list, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? (((int)(_sz/sizeof(gid_t)) >= size || size == 0)  /* size can be 0, which is valid */
                  ? (GETGROUPS_CASE1 getgroups(size, list))
                  : (GETGROUPS_CASE2 getgroups(size, list)))
               : (GETGROUPS_CASE3 getgroups(size, list)))
            : (GETGROUPS_CASE4 getgroups(size, list)));
}
#endif

#undef getgroups
#define getgroups(size, list)		openosc_getgroups(size, list)


/* Mapping for gethostname */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_gethostname (char *name, size_t len)
  OSC_THROW
{
    return (GETHOSTNAME_NOMAP_CASE gethostname(name, len));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_gethostname (char *name, size_t len)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(name, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (GETHOSTNAME_CASE1 gethostname(name, len))
                  : (GETHOSTNAME_CASE2 gethostname(name, len)))
               : (GETHOSTNAME_CASE3 gethostname(name, len)))
            : (GETHOSTNAME_CASE4 gethostname(name, len)));
}
#endif

#undef gethostname
#define gethostname(name, len)		openosc_gethostname(name, len)

#endif /* OPENOSC_DISABLE_UNISTD_H_FUNCS */


#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS
#ifndef OPENOSC_GETS_DISABLE

#ifndef __cplusplus
/* Mapping for gets */

extern char *gets(char *s);

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_gets (char *s)
{
    return (GETS_NOMAP_CASE gets(s));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_gets (char *s)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (GETS_CASE3 gets(s))
            : (GETS_CASE4 gets(s)));
}
#endif

#undef gets
#define gets(s)		openosc_gets(s)

#endif
#endif /* OPENOSC_GETS_DISABLE */
#endif /* OPENOSC_DISABLE_STDIO_H_FUNCS */


#ifdef OPENOSC_COVER_DEPRECATED_FUNCS
/* getwd has been deprecated */

/* Mapping for getwd */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_getwd (char *buf)
  OSC_THROW
{
    return (GETWD_NOMAP_CASE getwd(buf));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_getwd (char *buf)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (GETWD_CASE3 getwd(buf))
            : (GETWD_CASE4 getwd(buf)));
}
#endif

#undef getwd
#define getwd(buf)		openosc_getwd(buf)

#endif /* OPENOSC_COVER_DEPRECATED_FUNCS */


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for mbsnrtowcs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_mbsnrtowcs (wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (MBSNRTOWCS_NOMAP_CASE mbsnrtowcs(dest, src, nms, len, ps));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_mbsnrtowcs (wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MBSNRTOWCS_CASE1 mbsnrtowcs(dest, src, nms, len, ps))
                  : (MBSNRTOWCS_CASE2 mbsnrtowcs(dest, src, nms, len, ps)))
               : (MBSNRTOWCS_CASE3 mbsnrtowcs(dest, src, nms, len, ps)))
            : (MBSNRTOWCS_CASE4 mbsnrtowcs(dest, src, nms, len, ps)));
}
#endif

#undef mbsnrtowcs
#define mbsnrtowcs(dest, src, nms, len, ps)		openosc_mbsnrtowcs(dest, src, nms, len, ps)


/* Mapping for mbsrtowcs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_mbsrtowcs (wchar_t *dest, const char **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (MBSRTOWCS_NOMAP_CASE mbsrtowcs(dest, src, len, ps));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_mbsrtowcs (wchar_t *dest, const char **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MBSRTOWCS_CASE1 mbsrtowcs(dest, src, len, ps))
                  : (MBSRTOWCS_CASE2 mbsrtowcs(dest, src, len, ps)))
               : (MBSRTOWCS_CASE3 mbsrtowcs(dest, src, len, ps)))
            : (MBSRTOWCS_CASE4 mbsrtowcs(dest, src, len, ps)));
}
#endif

#undef mbsrtowcs
#define mbsrtowcs(dest, src, len, ps)		openosc_mbsrtowcs(dest, src, len, ps)


#ifndef OPENOSC_DISABLE_STDLIB_H_FUNCS

/* Mapping for mbstowcs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_mbstowcs (wchar_t *dest, const char *src, size_t n)
  OSC_THROW
{
    return (MBSTOWCS_NOMAP_CASE mbstowcs(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_mbstowcs (wchar_t *dest, const char *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (MBSTOWCS_CASE1 mbstowcs(dest, src, n))
                  : (MBSTOWCS_CASE2 mbstowcs(dest, src, n)))
               : (MBSTOWCS_CASE3 mbstowcs(dest, src, n)))
            : (MBSTOWCS_CASE4 mbstowcs(dest, src, n)));
}
#endif

#undef mbstowcs
#define mbstowcs(dest, src, n)		openosc_mbstowcs(dest, src, n)

#endif /* OPENOSC_DISABLE_STDLIB_H_FUNCS */
#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */


#ifndef OPENOSC_DISABLE_STRING_H_FUNCS
#ifndef OPENOSC_MEMPCPY_DISABLE

/* Mapping for mempcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
void *
openosc_mempcpy (void *dest, const void *src, size_t n)
  OSC_THROW
{
    return (MEMPCPY_NOMAP_CASE mempcpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) void *
openosc_mempcpy (void *dest, const void *src, size_t n)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (MEMPCPY_CASE1 mempcpy(dest, src, n))
                  : (MEMPCPY_CASE2 mempcpy(dest, src, n)))
               : (MEMPCPY_CASE3 mempcpy(dest, src, n)))
            : (MEMPCPY_CASE4 mempcpy(dest, src, n)));
}
#endif

#undef mempcpy
#define mempcpy(dest, src, n)		openosc_mempcpy(dest, src, n)

#endif /* OPENOSC_MEMPCPY_DISABLE */
#endif /* OPENOSC_DISABLE_STRING_H_FUNCS */


#ifndef OPENOSC_DISABLE_POLL_H_FUNCS
#ifndef OPENOSC_POLL_DISABLE

/* Mapping for poll */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
    return (POLL_NOMAP_CASE poll(fds, nfds, timeout));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (POLL_CASE1 poll(fds, nfds, timeout))
                  : (POLL_CASE2 poll(fds, nfds, timeout)))
               : (POLL_CASE3 poll(fds, nfds, timeout)))
            : (POLL_CASE4 poll(fds, nfds, timeout)));
}
#endif

#undef poll
#define poll(fds, nfds, timeout)		openosc_poll(fds, nfds, timeout)

#endif /* OPENOSC_POLL_DISABLE */


#ifndef OPENOSC_PPOLL_DISABLE

/* Mapping for ppoll */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_ppoll (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    return (PPOLL_NOMAP_CASE ppoll(fds, nfds, timeout_ts, sigmask));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_ppoll (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (PPOLL_CASE1 ppoll(fds, nfds, timeout_ts, sigmask))
                  : (PPOLL_CASE2 ppoll(fds, nfds, timeout_ts, sigmask)))
               : (PPOLL_CASE3 ppoll(fds, nfds, timeout_ts, sigmask)))
            : (PPOLL_CASE4 ppoll(fds, nfds, timeout_ts, sigmask)));
}
#endif

#undef ppoll
#define ppoll(fds, nfds, timeout_ts, sigmask)		openosc_ppoll(fds, nfds, timeout_ts, sigmask)

#endif /* OPENOSC_PPOLL_DISABLE */
#endif /* OPENOSC_DISABLE_POLL_H_FUNCS */


#ifndef OPENOSC_DISABLE_UNISTD_H_FUNCS
#ifndef OPENOSC_PREAD_DISABLE

/* Mapping for pread */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_pread (int fd, void *buf, size_t count, off_t offset)
{
    return (PREAD_NOMAP_CASE pread(fd, buf, count, offset));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_pread (int fd, void *buf, size_t count, off_t offset)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (PREAD_CASE1 pread(fd, buf, count, offset))
                  : (PREAD_CASE2 pread(fd, buf, count, offset)))
               : (PREAD_CASE3 pread(fd, buf, count, offset)))
            : (PREAD_CASE4 pread(fd, buf, count, offset)));
}
#endif

#undef pread
#define pread(fd, buf, count, offset)		openosc_pread(fd, buf, count, offset)

#endif /* OPENOSC_PREAD_DISABLE */


#ifndef OPENOSC_READ_DISABLE

#ifndef __cplusplus
/* Mapping for read */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_read (int fd, void *buf, size_t count)
{
    return (READ_NOMAP_CASE read(fd, buf, count));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_read (int fd, void *buf, size_t count)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (READ_CASE1 read(fd, buf, count))
                  : (READ_CASE2 read(fd, buf, count)))
               : (READ_CASE3 read(fd, buf, count)))
            : (READ_CASE4 read(fd, buf, count)));
}
#endif

#undef read
#define read(fd, buf, count)		openosc_read(fd, buf, count)
#endif /* __cplusplus */

#endif /* OPENOSC_READ_DISABLE */


/* Mapping for readlinkat */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_readlinkat (int dirfd, const char *pathname, char *buf, size_t bufsiz)
  OSC_THROW
{
    return (READLINKAT_NOMAP_CASE readlinkat(dirfd, pathname, buf, bufsiz));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_readlinkat (int dirfd, const char *pathname, char *buf, size_t bufsiz)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(bufsiz);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= bufsiz)
                  ? (READLINKAT_CASE1 readlinkat(dirfd, pathname, buf, bufsiz))
                  : (READLINKAT_CASE2 readlinkat(dirfd, pathname, buf, bufsiz)))
               : (READLINKAT_CASE3 readlinkat(dirfd, pathname, buf, bufsiz)))
            : (READLINKAT_CASE4 readlinkat(dirfd, pathname, buf, bufsiz)));
}
#endif

#undef readlinkat
#define readlinkat(dirfd, pathname, buf, bufsiz)		openosc_readlinkat(dirfd, pathname, buf, bufsiz)


/* Mapping for readlink */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_readlink (const char *path, char *buf, size_t bufsiz)
  OSC_THROW
{
    return (READLINK_NOMAP_CASE readlink(path, buf, bufsiz));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_readlink (const char *path, char *buf, size_t bufsiz)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(bufsiz);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= bufsiz)
                  ? (READLINK_CASE1 readlink(path, buf, bufsiz))
                  : (READLINK_CASE2 readlink(path, buf, bufsiz)))
               : (READLINK_CASE3 readlink(path, buf, bufsiz)))
            : (READLINK_CASE4 readlink(path, buf, bufsiz)));
}
#endif

#undef readlink
#define readlink(path, buf, bufsiz)		openosc_readlink(path, buf, bufsiz)

#endif /* OPENOSC_DISABLE_UNISTD_H_FUNCS */


#ifndef OPENOSC_DISABLE_STDLIB_H_FUNCS

/* Mapping for realpath */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_realpath (const char *path, char *resolved_path)
  OSC_THROW
{
    return (REALPATH_NOMAP_CASE realpath(path, resolved_path));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_realpath (const char *path, char *resolved_path)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(resolved_path, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (REALPATH_CASE3 realpath(path, resolved_path))
            : (REALPATH_CASE4 realpath(path, resolved_path)));
}
#endif

#undef realpath
#define realpath(path, resolved_path)		openosc_realpath(path, resolved_path)

#endif /* OPENOSC_DISABLE_STDLIB_H_FUNCS */


#ifndef OPENOSC_DISABLE_SOCKET_H_FUNCS
#ifndef OPENOSC_RECV_DISABLE

/* Mapping for recv */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_recv (int sockfd, void *buf, size_t len, int flags)
{
    return (RECV_NOMAP_CASE recv(sockfd, buf, len, flags));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_recv (int sockfd, void *buf, size_t len, int flags)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECV_CASE1 recv(sockfd, buf, len, flags))
                  : (RECV_CASE2 recv(sockfd, buf, len, flags)))
               : (RECV_CASE3 recv(sockfd, buf, len, flags)))
            : (RECV_CASE4 recv(sockfd, buf, len, flags)));
}
#endif

#undef recv
#define recv(sockfd, buf, len, flags)		openosc_recv(sockfd, buf, len, flags)

#endif /* OPENOSC_RECV_DISABLE */


#ifndef OPENOSC_RECVFROM_DISABLE

/* Mapping for recvfrom */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
ssize_t
openosc_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    return (RECVFROM_NOMAP_CASE recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}

#else

static inline __attribute__ ((always_inline)) ssize_t
openosc_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECVFROM_CASE1 recvfrom(sockfd, buf, len, flags, src_addr, addrlen))
                  : (RECVFROM_CASE2 recvfrom(sockfd, buf, len, flags, src_addr, addrlen)))
               : (RECVFROM_CASE3 recvfrom(sockfd, buf, len, flags, src_addr, addrlen)))
            : (RECVFROM_CASE4 recvfrom(sockfd, buf, len, flags, src_addr, addrlen)));
}
#endif

#undef recvfrom
#define recvfrom(sockfd, buf, len, flags, src_addr, addrlen)		openosc_recvfrom(sockfd, buf, len, flags, src_addr, addrlen)

#endif /* OPENOSC_RECVFROM_DISABLE */
#endif /* OPENOSC_DISABLE_SOCKET_H_FUNCS */


#ifndef OPENOSC_DISABLE_STRING_H_FUNCS

/* Mapping for stpcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_stpcpy (char *dest, const char *src)
  OSC_THROW
{
    return (STPCPY_NOMAP_CASE stpcpy(dest, src));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_stpcpy (char *dest, const char *src)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (STPCPY_CASE3 stpcpy(dest, src))
            : (STPCPY_CASE4 stpcpy(dest, src)));
}
#endif

#undef stpcpy
#define stpcpy(dest, src)		openosc_stpcpy(dest, src)


/* Mapping for stpncpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
char *
openosc_stpncpy (char *dest, const char *src, size_t n)
  OSC_THROW
{
    return (STPNCPY_NOMAP_CASE stpncpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) char *
openosc_stpncpy (char *dest, const char *src, size_t n)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (STPNCPY_CASE1 stpncpy(dest, src, n))
                  : (STPNCPY_CASE2 stpncpy(dest, src, n)))
               : (STPNCPY_CASE3 stpncpy(dest, src, n)))
            : (STPNCPY_CASE4 stpncpy(dest, src, n)));
}
#endif

#undef stpncpy
#define stpncpy(dest, src, n)		openosc_stpncpy(dest, src, n)

#endif /* OPENOSC_DISABLE_STRING_H_FUNCS */


#ifndef OPENOSC_DISABLE_UNISTD_H_FUNCS

/* Mapping for ttyname_r */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_ttyname_r (int fd, char *buf, size_t buflen)
  OSC_THROW
{
    return (TTYNAME_R_NOMAP_CASE ttyname_r(fd, buf, buflen));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_ttyname_r (int fd, char *buf, size_t buflen)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(buflen);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= buflen)
                  ? (TTYNAME_R_CASE1 ttyname_r(fd, buf, buflen))
                  : (TTYNAME_R_CASE2 ttyname_r(fd, buf, buflen)))
               : (TTYNAME_R_CASE3 ttyname_r(fd, buf, buflen)))
            : (TTYNAME_R_CASE4 ttyname_r(fd, buf, buflen)));
}
#endif

#undef ttyname_r
#define ttyname_r(fd, buf, buflen)		openosc_ttyname_r(fd, buf, buflen)

#endif /* OPENOSC_DISABLE_UNISTD_H_FUNCS */


#ifndef OPENOSC_DISABLE_STDIO_H_FUNCS
#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vasprintf */

static inline __attribute__ ((always_inline))
int
openosc_vasprintf (char **strp, const char *fmt, va_list ap)
  OSC_THROW
{
    return (VASPRINTF_NOMAP_CASE vasprintf(strp, fmt, ap));
}

#undef vasprintf
#define vasprintf(strp, fmt, ap)		openosc_vasprintf(strp, fmt, ap)


/* Mapping for vdprintf */

static inline __attribute__ ((always_inline))
int
openosc_vdprintf (int fd, const char *format, va_list ap)
{
    return (VDPRINTF_NOMAP_CASE vdprintf(fd, format, ap));
}

#undef vdprintf
#define vdprintf(fd, format, ap)		openosc_vdprintf(fd, format, ap)


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for vfwprintf */

static inline __attribute__ ((always_inline))
int
openosc_vfwprintf (FILE *stream, const wchar_t *format, va_list args)
{
    return (VFWPRINTF_NOMAP_CASE vfwprintf(stream, format, args));
}

#undef vfwprintf
#define vfwprintf(stream, format, args)		openosc_vfwprintf(stream, format, args)

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */


/* bits/stdio.h:36 has a define for vprintf, causing redefinition error */
#ifndef __USE_EXTERN_INLINES

#ifndef OPENOSC_VPRINTF_DISABLE

/* Mapping for vprintf */

static inline __attribute__ ((always_inline))
int
openosc_vprintf (const char *format, va_list ap)
{
    return (VPRINTF_NOMAP_CASE vprintf(format, ap));
}

#undef vprintf
#define vprintf(format, ap)		openosc_vprintf(format, ap)

#endif /* OPENOSC_VPRINTF_DISABLE */


/* Mapping for vfprintf */

static inline __attribute__ ((always_inline))
int
openosc_vfprintf (FILE *stream, const char *format, va_list ap)
{
    return (VFPRINTF_NOMAP_CASE vfprintf(stream, format, ap));
}

#undef vfprintf
#define vfprintf(stream, format, ap)		openosc_vfprintf(stream, format, ap)

#endif  /* __USE_EXTERN_INLINES */


/* Mapping for vsnprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline)) int
openosc_vsnprintf (char *str, size_t len,
           const char *fmt, va_list ap)
  OSC_THROW
{
    return (VSNPRINTF_NOMAP_CASE vsnprintf(str, len, fmt, ap));
}

#else

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
                  : (VSNPRINTF_CASE2 vsnprintf(str, len, fmt, ap)))
               : (VSNPRINTF_CASE3 vsnprintf(str, len, fmt, ap)))
            : (VSNPRINTF_CASE4 vsnprintf(str, len, fmt, ap)));
}
#endif

#undef vsnprintf
#define vsnprintf(str, len, format, ap)  \
        openosc_vsnprintf(str, len, format, ap)

/* avoid redefinition */
//#define HAVE_VSNPRINTF 1


/* Mapping for vsprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_vsprintf (char *str, const char *format, va_list ap)
  OSC_THROW
{
    return (VSPRINTF_NOMAP_CASE vsprintf(str, format, ap));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_vsprintf (char *str, const char *format, va_list ap)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(str, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (VSPRINTF_CASE3 vsprintf(str, format, ap))
            : (VSPRINTF_CASE4 vsprintf(str, format, ap)));
}
#endif

#undef vsprintf
#define vsprintf(str, format, ap)		openosc_vsprintf(str, format, ap)


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for vswprintf */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_vswprintf (wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args)
  OSC_THROW
{
    return (VSWPRINTF_NOMAP_CASE vswprintf(wcs, maxlen, format, args));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_vswprintf (wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(wcs, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(maxlen);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= maxlen)
                  ? (VSWPRINTF_CASE1 vswprintf(wcs, maxlen, format, args))
                  : (VSWPRINTF_CASE2 vswprintf(wcs, maxlen, format, args)))
               : (VSWPRINTF_CASE3 vswprintf(wcs, maxlen, format, args)))
            : (VSWPRINTF_CASE4 vswprintf(wcs, maxlen, format, args)));
}
#endif

#undef vswprintf
#define vswprintf(wcs, maxlen, format, args)		openosc_vswprintf(wcs, maxlen, format, args)


/* Mapping for vwprintf */

static inline __attribute__ ((always_inline))
int
openosc_vwprintf (const wchar_t *format, va_list args)
{
    return (VWPRINTF_NOMAP_CASE vwprintf(format, args));
}

#undef vwprintf
#define vwprintf(format, args)		openosc_vwprintf(format, args)

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */

#endif /* OPENOSC_VALIST_NOSUPPORT */
#endif /* OPENOSC_DISABLE_STDIO_H_FUNCS */


#ifndef OPENOSC_DISABLE_WCHAR_H_FUNCS

/* Mapping for wcpcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcpcpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCPCPY_NOMAP_CASE wcpcpy(dest, src));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcpcpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCPCPY_CASE3 wcpcpy(dest, src))
            : (WCPCPY_CASE4 wcpcpy(dest, src)));
}
#endif

#undef wcpcpy
#define wcpcpy(dest, src)		openosc_wcpcpy(dest, src)


/* Mapping for wcpncpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcpncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCPNCPY_NOMAP_CASE wcpncpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcpncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCPNCPY_CASE1 wcpncpy(dest, src, n))
                  : (WCPNCPY_CASE2 wcpncpy(dest, src, n)))
               : (WCPNCPY_CASE3 wcpncpy(dest, src, n)))
            : (WCPNCPY_CASE4 wcpncpy(dest, src, n)));
}
#endif

#undef wcpncpy
#define wcpncpy(dest, src, n)		openosc_wcpncpy(dest, src, n)


/* Mapping for wcrtomb */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_wcrtomb (char *s, wchar_t wc, mbstate_t *ps)
  OSC_THROW
{
    return (WCRTOMB_NOMAP_CASE wcrtomb(s, wc, ps));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_wcrtomb (char *s, wchar_t wc, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCRTOMB_CASE3 wcrtomb(s, wc, ps))
            : (WCRTOMB_CASE4 wcrtomb(s, wc, ps)));
}
#endif

#undef wcrtomb
#define wcrtomb(s, wc, ps)		openosc_wcrtomb(s, wc, ps)


/* Mapping for wcscat */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcscat (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCSCAT_NOMAP_CASE wcscat(dest, src));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcscat (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCAT_CASE3 wcscat(dest, src))
            : (WCSCAT_CASE4 wcscat(dest, src)));
}
#endif

#undef wcscat
#define wcscat(dest, src)		openosc_wcscat(dest, src)


#ifndef OPENOSC_WCSCPY_DISABLE

/* Mapping for wcscpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcscpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCSCPY_NOMAP_CASE wcscpy(dest, src));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcscpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCPY_CASE3 wcscpy(dest, src))
            : (WCSCPY_CASE4 wcscpy(dest, src)));
}
#endif

#undef wcscpy
#define wcscpy(dest, src)		openosc_wcscpy(dest, src)

#endif /* OPENOSC_WCSCPY_DISABLE */


/* Mapping for wcsncat */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcsncat (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSNCAT_NOMAP_CASE wcsncat(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcsncat (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSNCAT_CASE1 wcsncat(dest, src, n))
                  : (WCSNCAT_CASE2 wcsncat(dest, src, n)))
               : (WCSNCAT_CASE3 wcsncat(dest, src, n)))
            : (WCSNCAT_CASE4 wcsncat(dest, src, n)));
}
#endif

#undef wcsncat
#define wcsncat(dest, src, n)		openosc_wcsncat(dest, src, n)


/* Mapping for wcsncpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcsncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSNCPY_NOMAP_CASE wcsncpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcsncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSNCPY_CASE1 wcsncpy(dest, src, n))
                  : (WCSNCPY_CASE2 wcsncpy(dest, src, n)))
               : (WCSNCPY_CASE3 wcsncpy(dest, src, n)))
            : (WCSNCPY_CASE4 wcsncpy(dest, src, n)));
}
#endif

#undef wcsncpy
#define wcsncpy(dest, src, n)		openosc_wcsncpy(dest, src, n)


/* Mapping for wcsnrtombs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_wcsnrtombs (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (WCSNRTOMBS_NOMAP_CASE wcsnrtombs(dest, src, nwc, len, ps));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_wcsnrtombs (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (WCSNRTOMBS_CASE1 wcsnrtombs(dest, src, nwc, len, ps))
                  : (WCSNRTOMBS_CASE2 wcsnrtombs(dest, src, nwc, len, ps)))
               : (WCSNRTOMBS_CASE3 wcsnrtombs(dest, src, nwc, len, ps)))
            : (WCSNRTOMBS_CASE4 wcsnrtombs(dest, src, nwc, len, ps)));
}
#endif

#undef wcsnrtombs
#define wcsnrtombs(dest, src, nwc, len, ps)		openosc_wcsnrtombs(dest, src, nwc, len, ps)


/* Mapping for wcsrtombs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_wcsrtombs (char *dest, const wchar_t **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (WCSRTOMBS_NOMAP_CASE wcsrtombs(dest, src, len, ps));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_wcsrtombs (char *dest, const wchar_t **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (WCSRTOMBS_CASE1 wcsrtombs(dest, src, len, ps))
                  : (WCSRTOMBS_CASE2 wcsrtombs(dest, src, len, ps)))
               : (WCSRTOMBS_CASE3 wcsrtombs(dest, src, len, ps)))
            : (WCSRTOMBS_CASE4 wcsrtombs(dest, src, len, ps)));
}
#endif

#undef wcsrtombs
#define wcsrtombs(dest, src, len, ps)		openosc_wcsrtombs(dest, src, len, ps)


#ifndef OPENOSC_DISABLE_STDLIB_H_FUNCS

/* Mapping for wcstombs */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
size_t
openosc_wcstombs (char *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSTOMBS_NOMAP_CASE wcstombs(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) size_t
openosc_wcstombs (char *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSTOMBS_CASE1 wcstombs(dest, src, n))
                  : (WCSTOMBS_CASE2 wcstombs(dest, src, n)))
               : (WCSTOMBS_CASE3 wcstombs(dest, src, n)))
            : (WCSTOMBS_CASE4 wcstombs(dest, src, n)));
}
#endif

#undef wcstombs
#define wcstombs(dest, src, n)		openosc_wcstombs(dest, src, n)


/* Mapping for wctomb */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
int
openosc_wctomb (char *s, wchar_t wc)
  OSC_THROW
{
    return (WCTOMB_NOMAP_CASE wctomb(s, wc));
}

#else

static inline __attribute__ ((always_inline)) int
openosc_wctomb (char *s, wchar_t wc)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCTOMB_CASE3 wctomb(s, wc))
            : (WCTOMB_CASE4 wctomb(s, wc)));
}
#endif

#undef wctomb
#define wctomb(s, wc)		openosc_wctomb(s, wc)

#endif /* OPENOSC_DISABLE_STDLIB_H_FUNCS */


/* Mapping for wmemcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMCPY_NOMAP_CASE wmemcpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wmemcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMCPY_CASE1 wmemcpy(dest, src, n))
                  : (WMEMCPY_CASE2 wmemcpy(dest, src, n)))
               : (WMEMCPY_CASE3 wmemcpy(dest, src, n)))
            : (WMEMCPY_CASE4 wmemcpy(dest, src, n)));
}
#endif

#undef wmemcpy
#define wmemcpy(dest, src, n)		openosc_wmemcpy(dest, src, n)


/* Mapping for wmemmove */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemmove (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMMOVE_NOMAP_CASE wmemmove(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wmemmove (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMMOVE_CASE1 wmemmove(dest, src, n))
                  : (WMEMMOVE_CASE2 wmemmove(dest, src, n)))
               : (WMEMMOVE_CASE3 wmemmove(dest, src, n)))
            : (WMEMMOVE_CASE4 wmemmove(dest, src, n)));
}
#endif

#undef wmemmove
#define wmemmove(dest, src, n)		openosc_wmemmove(dest, src, n)


/* Mapping for wmempcpy */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmempcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMPCPY_NOMAP_CASE wmempcpy(dest, src, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wmempcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMPCPY_CASE1 wmempcpy(dest, src, n))
                  : (WMEMPCPY_CASE2 wmempcpy(dest, src, n)))
               : (WMEMPCPY_CASE3 wmempcpy(dest, src, n)))
            : (WMEMPCPY_CASE4 wmempcpy(dest, src, n)));
}
#endif

#undef wmempcpy
#define wmempcpy(dest, src, n)		openosc_wmempcpy(dest, src, n)


/* Mapping for wmemset */

#ifdef OPENOSC_NOMAP_METRIC_ONLY

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemset (wchar_t *wcs, wchar_t wc, size_t n)
  OSC_THROW
{
    return (WMEMSET_NOMAP_CASE wmemset(wcs, wc, n));
}

#else

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wmemset (wchar_t *wcs, wchar_t wc, size_t n)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(wcs, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMSET_CASE1 wmemset(wcs, wc, n))
                  : (WMEMSET_CASE2 wmemset(wcs, wc, n)))
               : (WMEMSET_CASE3 wmemset(wcs, wc, n)))
            : (WMEMSET_CASE4 wmemset(wcs, wc, n)));
}
#endif

#undef wmemset
#define wmemset(wcs, wc, n)		openosc_wmemset(wcs, wc, n)

#endif /* OPENOSC_DISABLE_WCHAR_H_FUNCS */

#endif  /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /* __OPENOSC_METRIC_ONLY2_H__ */
