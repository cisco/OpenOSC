/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_REDEFINE_NOMAP_H__
#define __OPENOSC_FORTIFY_REDEFINE_NOMAP_H__

/* openosc_fortify_redefine_map.h and openosc_fortify_redefine_nomap.h are mutually exclusive */
#ifndef __OPENOSC_FORTIFY_REDEFINE_MAP_H__

/* if OSC metric feature is disabled, we can completely exclude this osc_nomap.h header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

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


/* Mapping for fwprintf */

static inline __attribute__ ((always_inline))
int 
openosc_fwprintf (FILE *stream, const wchar_t *format, ...)
{
    return (FWPRINTF_NOMAP_CASE fwprintf(stream, format, __va_arg_pack ()));
}

#undef fwprintf
#define fwprintf		openosc_fwprintf


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

static inline __attribute__ ((always_inline))
int 
openosc_snprintf (char *str, size_t size, const char *format, ...)
{
    return (SNPRINTF_NOMAP_CASE snprintf(str, size, format, __va_arg_pack ()));
}

#undef snprintf
#define snprintf		openosc_snprintf


/* Mapping for sprintf */

static inline __attribute__ ((always_inline))
int 
openosc_sprintf (char *str, const char *format, ...)
{
    return (SPRINTF_NOMAP_CASE sprintf(str, format, __va_arg_pack ()));
}

#undef sprintf
#define sprintf		openosc_sprintf


/* Mapping for swprintf */

static inline __attribute__ ((always_inline))
int 
openosc_swprintf (wchar_t *wcs, size_t maxlen, const wchar_t *format, ...)
  OSC_THROW
{
    return (SWPRINTF_NOMAP_CASE swprintf(wcs, maxlen, format, __va_arg_pack ()));
}

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

#endif /* __va_arg_pack */

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for confstr */

static inline __attribute__ ((always_inline))
size_t 
openosc_confstr (int name, char *buf, size_t len)
  OSC_THROW
{
    return (CONFSTR_NOMAP_CASE confstr(name, buf, len));
}

#undef confstr
#define confstr(name, buf, len)		openosc_confstr(name, buf, len)


#ifndef OPENOSC_FGETS_DISABLE

/* Mapping for fgets */

static inline __attribute__ ((always_inline))
char *
openosc_fgets (char *s, int size, FILE *stream)
{
    return (FGETS_NOMAP_CASE fgets(s, size, stream));
}

#undef fgets
#define fgets(s, size, stream)		openosc_fgets(s, size, stream)

#endif /* OPENOSC_FGETS_DISABLE */


/* Mapping for fgets_unlocked */

static inline __attribute__ ((always_inline))
char *
openosc_fgets_unlocked (char *s, int n, FILE *stream)
{
    return (FGETS_UNLOCKED_NOMAP_CASE fgets_unlocked(s, n, stream));
}

#undef fgets_unlocked
#define fgets_unlocked(s, n, stream)		openosc_fgets_unlocked(s, n, stream)


/* Mapping for fgetws */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_fgetws (wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_NOMAP_CASE fgetws(ws, n, stream));
}

#undef fgetws
#define fgetws(ws, n, stream)		openosc_fgetws(ws, n, stream)


/* Mapping for fgetws_unlocked */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_fgetws_unlocked (wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_UNLOCKED_NOMAP_CASE fgetws_unlocked(ws, n, stream));
}

#undef fgetws_unlocked
#define fgetws_unlocked(ws, n, stream)		openosc_fgetws_unlocked(ws, n, stream)


/* Mapping for fread */

static inline __attribute__ ((always_inline))
size_t 
openosc_fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return (FREAD_NOMAP_CASE fread(ptr, size, nmemb, stream));
}

#undef fread
#define fread(ptr, size, nmemb, stream)		openosc_fread(ptr, size, nmemb, stream)


#ifndef fread_unlocked

/* Mapping for fread_unlocked */

static inline __attribute__ ((always_inline))
size_t 
openosc_fread_unlocked (void *ptr, size_t size, size_t n, FILE *stream)
{
    return (FREAD_UNLOCKED_NOMAP_CASE fread_unlocked(ptr, size, n, stream));
}

#undef fread_unlocked
#define fread_unlocked(ptr, size, n, stream)		openosc_fread_unlocked(ptr, size, n, stream)

#endif /* fread_unlocked */


#ifndef OPENOSC_GETCWD_DISABLE

/* Mapping for getcwd */

static inline __attribute__ ((always_inline))
char *
openosc_getcwd (char *buf, size_t size)
  OSC_THROW
{
    return (GETCWD_NOMAP_CASE getcwd(buf, size));
}

#undef getcwd
#define getcwd(buf, size)		openosc_getcwd(buf, size)

#endif /* OPENOSC_GETCWD_DISABLE */


/* Mapping for getdomainname */

static inline __attribute__ ((always_inline))
int 
openosc_getdomainname (char *name, size_t len)
  OSC_THROW
{
    return (GETDOMAINNAME_NOMAP_CASE getdomainname(name, len));
}

#undef getdomainname
#define getdomainname(name, len)		openosc_getdomainname(name, len)


/* Mapping for getgroups */

static inline __attribute__ ((always_inline))
int 
openosc_getgroups (int size, gid_t list[])
  OSC_THROW
{
    return (GETGROUPS_NOMAP_CASE getgroups(size, list));
}

#undef getgroups
#define getgroups(size, list)		openosc_getgroups(size, list)


/* Mapping for gethostname */

static inline __attribute__ ((always_inline))
int 
openosc_gethostname (char *name, size_t len)
  OSC_THROW
{
    return (GETHOSTNAME_NOMAP_CASE gethostname(name, len));
}

#undef gethostname
#define gethostname(name, len)		openosc_gethostname(name, len)


#ifndef OPENOSC_GETS_DISABLE

/* Mapping for gets */

static inline __attribute__ ((always_inline))
char *
openosc_gets (char *s)
{
    return (GETS_NOMAP_CASE gets(s));
}

#undef gets
#define gets(s)		openosc_gets(s)

#endif /* OPENOSC_GETS_DISABLE */


/* Mapping for getwd */

static inline __attribute__ ((always_inline))
char *
openosc_getwd (char *buf)
  OSC_THROW
{
    return (GETWD_NOMAP_CASE getwd(buf));
}

#undef getwd
#define getwd(buf)		openosc_getwd(buf)


/* Mapping for mbsnrtowcs */

static inline __attribute__ ((always_inline))
size_t 
openosc_mbsnrtowcs (wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (MBSNRTOWCS_NOMAP_CASE mbsnrtowcs(dest, src, nms, len, ps));
}

#undef mbsnrtowcs
#define mbsnrtowcs(dest, src, nms, len, ps)		openosc_mbsnrtowcs(dest, src, nms, len, ps)


/* Mapping for mbsrtowcs */

static inline __attribute__ ((always_inline))
size_t 
openosc_mbsrtowcs (wchar_t *dest, const char **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (MBSRTOWCS_NOMAP_CASE mbsrtowcs(dest, src, len, ps));
}

#undef mbsrtowcs
#define mbsrtowcs(dest, src, len, ps)		openosc_mbsrtowcs(dest, src, len, ps)


/* Mapping for mbstowcs */

static inline __attribute__ ((always_inline))
size_t 
openosc_mbstowcs (wchar_t *dest, const char *src, size_t n)
  OSC_THROW
{
    return (MBSTOWCS_NOMAP_CASE mbstowcs(dest, src, n));
}

#undef mbstowcs
#define mbstowcs(dest, src, n)		openosc_mbstowcs(dest, src, n)


#ifndef OPENOSC_MEMPCPY_DISABLE

/* Mapping for mempcpy */

static inline __attribute__ ((always_inline))
void *
openosc_mempcpy (void *dest, const void *src, size_t n)
  OSC_THROW
{
    return (MEMPCPY_NOMAP_CASE mempcpy(dest, src, n));
}

#undef mempcpy
#define mempcpy(dest, src, n)		openosc_mempcpy(dest, src, n)

#endif /* OPENOSC_MEMPCPY_DISABLE */


#ifndef OPENOSC_POLL_DISABLE

/* Mapping for poll */

static inline __attribute__ ((always_inline))
int 
openosc_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
    return (POLL_NOMAP_CASE poll(fds, nfds, timeout));
}

#undef poll
#define poll(fds, nfds, timeout)		openosc_poll(fds, nfds, timeout)

#endif /* OPENOSC_POLL_DISABLE */


#ifndef OPENOSC_PPOLL_DISABLE

/* Mapping for ppoll */

static inline __attribute__ ((always_inline))
int 
openosc_ppoll (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    return (PPOLL_NOMAP_CASE ppoll(fds, nfds, timeout_ts, sigmask));
}

#undef ppoll
#define ppoll(fds, nfds, timeout_ts, sigmask)		openosc_ppoll(fds, nfds, timeout_ts, sigmask)

#endif /* OPENOSC_PPOLL_DISABLE */


#ifndef OPENOSC_PREAD_DISABLE

/* Mapping for pread */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_pread (int fd, void *buf, size_t count, off_t offset)
{
    return (PREAD_NOMAP_CASE pread(fd, buf, count, offset));
}

#undef pread
#define pread(fd, buf, count, offset)		openosc_pread(fd, buf, count, offset)

#endif /* OPENOSC_PREAD_DISABLE */


#ifndef OPENOSC_READ_DISABLE

#ifndef __cplusplus
/* Mapping for read */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_read (int fd, void *buf, size_t count)
{
    return (READ_NOMAP_CASE read(fd, buf, count));
}

#undef read
#define read(fd, buf, count)		openosc_read(fd, buf, count)
#endif /* __cplusplus */

#endif /* OPENOSC_READ_DISABLE */


/* Mapping for readlinkat */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_readlinkat (int dirfd, const char *pathname, char *buf, size_t bufsiz)
  OSC_THROW
{
    return (READLINKAT_NOMAP_CASE readlinkat(dirfd, pathname, buf, bufsiz));
}

#undef readlinkat
#define readlinkat(dirfd, pathname, buf, bufsiz)		openosc_readlinkat(dirfd, pathname, buf, bufsiz)


/* Mapping for readlink */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_readlink (const char *path, char *buf, size_t bufsiz)
  OSC_THROW
{
    return (READLINK_NOMAP_CASE readlink(path, buf, bufsiz));
}

#undef readlink
#define readlink(path, buf, bufsiz)		openosc_readlink(path, buf, bufsiz)


/* Mapping for realpath */

static inline __attribute__ ((always_inline))
char *
openosc_realpath (const char *path, char *resolved_path)
  OSC_THROW
{
    return (REALPATH_NOMAP_CASE realpath(path, resolved_path));
}

#undef realpath
#define realpath(path, resolved_path)		openosc_realpath(path, resolved_path)


#ifndef OPENOSC_RECV_DISABLE

/* Mapping for recv */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_recv (int sockfd, void *buf, size_t len, int flags)
{
    return (RECV_NOMAP_CASE recv(sockfd, buf, len, flags));
}

#undef recv
#define recv(sockfd, buf, len, flags)		openosc_recv(sockfd, buf, len, flags)

#endif /* OPENOSC_RECV_DISABLE */


#ifndef OPENOSC_RECVFROM_DISABLE

/* Mapping for recvfrom */

static inline __attribute__ ((always_inline))
ssize_t 
openosc_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    return (RECVFROM_NOMAP_CASE recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}

#undef recvfrom
#define recvfrom(sockfd, buf, len, flags, src_addr, addrlen)		openosc_recvfrom(sockfd, buf, len, flags, src_addr, addrlen)

#endif /* OPENOSC_RECVFROM_DISABLE */


/* Mapping for stpcpy */

static inline __attribute__ ((always_inline))
char *
openosc_stpcpy (char *dest, const char *src)
  OSC_THROW
{
    return (STPCPY_NOMAP_CASE stpcpy(dest, src));
}

#undef stpcpy
#define stpcpy(dest, src)		openosc_stpcpy(dest, src)


/* Mapping for stpncpy */

static inline __attribute__ ((always_inline))
char *
openosc_stpncpy (char *dest, const char *src, size_t n)
  OSC_THROW
{
    return (STPNCPY_NOMAP_CASE stpncpy(dest, src, n));
}

#undef stpncpy
#define stpncpy(dest, src, n)		openosc_stpncpy(dest, src, n)


/* Mapping for ttyname_r */

static inline __attribute__ ((always_inline))
int 
openosc_ttyname_r (int fd, char *buf, size_t buflen)
  OSC_THROW
{
    return (TTYNAME_R_NOMAP_CASE ttyname_r(fd, buf, buflen));
}

#undef ttyname_r
#define ttyname_r(fd, buf, buflen)		openosc_ttyname_r(fd, buf, buflen)


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


/* Mapping for vfwprintf */

static inline __attribute__ ((always_inline))
int 
openosc_vfwprintf (FILE *stream, const wchar_t *format, va_list args)
{
    return (VFWPRINTF_NOMAP_CASE vfwprintf(stream, format, args));
}

#undef vfwprintf
#define vfwprintf(stream, format, args)		openosc_vfwprintf(stream, format, args)


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


/* Mapping for vsprintf */

static inline __attribute__ ((always_inline))
int 
openosc_vsprintf (char *str, const char *format, va_list ap)
  OSC_THROW
{
    return (VSPRINTF_NOMAP_CASE vsprintf(str, format, ap));
}

#undef vsprintf
#define vsprintf(str, format, ap)		openosc_vsprintf(str, format, ap)


/* Mapping for vswprintf */

static inline __attribute__ ((always_inline))
int 
openosc_vswprintf (wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args)
  OSC_THROW
{
    return (VSWPRINTF_NOMAP_CASE vswprintf(wcs, maxlen, format, args));
}

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

#endif /* OPENOSC_VALIST_NOSUPPORT */

/* Mapping for wcpcpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcpcpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCPCPY_NOMAP_CASE wcpcpy(dest, src));
}

#undef wcpcpy
#define wcpcpy(dest, src)		openosc_wcpcpy(dest, src)


/* Mapping for wcpncpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcpncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCPNCPY_NOMAP_CASE wcpncpy(dest, src, n));
}

#undef wcpncpy
#define wcpncpy(dest, src, n)		openosc_wcpncpy(dest, src, n)


/* Mapping for wcrtomb */

static inline __attribute__ ((always_inline))
size_t 
openosc_wcrtomb (char *s, wchar_t wc, mbstate_t *ps)
  OSC_THROW
{
    return (WCRTOMB_NOMAP_CASE wcrtomb(s, wc, ps));
}

#undef wcrtomb
#define wcrtomb(s, wc, ps)		openosc_wcrtomb(s, wc, ps)


/* Mapping for wcscat */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcscat (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCSCAT_NOMAP_CASE wcscat(dest, src));
}

#undef wcscat
#define wcscat(dest, src)		openosc_wcscat(dest, src)


#ifndef OPENOSC_WCSCPY_DISABLE

/* Mapping for wcscpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcscpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    return (WCSCPY_NOMAP_CASE wcscpy(dest, src));
}

#undef wcscpy
#define wcscpy(dest, src)		openosc_wcscpy(dest, src)

#endif /* OPENOSC_WCSCPY_DISABLE */


/* Mapping for wcsncat */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcsncat (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSNCAT_NOMAP_CASE wcsncat(dest, src, n));
}

#undef wcsncat
#define wcsncat(dest, src, n)		openosc_wcsncat(dest, src, n)


/* Mapping for wcsncpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wcsncpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSNCPY_NOMAP_CASE wcsncpy(dest, src, n));
}

#undef wcsncpy
#define wcsncpy(dest, src, n)		openosc_wcsncpy(dest, src, n)


/* Mapping for wcsnrtombs */

static inline __attribute__ ((always_inline))
size_t 
openosc_wcsnrtombs (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (WCSNRTOMBS_NOMAP_CASE wcsnrtombs(dest, src, nwc, len, ps));
}

#undef wcsnrtombs
#define wcsnrtombs(dest, src, nwc, len, ps)		openosc_wcsnrtombs(dest, src, nwc, len, ps)


/* Mapping for wcsrtombs */

static inline __attribute__ ((always_inline))
size_t 
openosc_wcsrtombs (char *dest, const wchar_t **src, size_t len, mbstate_t *ps)
  OSC_THROW
{
    return (WCSRTOMBS_NOMAP_CASE wcsrtombs(dest, src, len, ps));
}

#undef wcsrtombs
#define wcsrtombs(dest, src, len, ps)		openosc_wcsrtombs(dest, src, len, ps)


/* Mapping for wcstombs */

static inline __attribute__ ((always_inline))
size_t 
openosc_wcstombs (char *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WCSTOMBS_NOMAP_CASE wcstombs(dest, src, n));
}

#undef wcstombs
#define wcstombs(dest, src, n)		openosc_wcstombs(dest, src, n)


/* Mapping for wctomb */

static inline __attribute__ ((always_inline))
int 
openosc_wctomb (char *s, wchar_t wc)
  OSC_THROW
{
    return (WCTOMB_NOMAP_CASE wctomb(s, wc));
}

#undef wctomb
#define wctomb(s, wc)		openosc_wctomb(s, wc)


/* Mapping for wmemcpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMCPY_NOMAP_CASE wmemcpy(dest, src, n));
}

#undef wmemcpy
#define wmemcpy(dest, src, n)		openosc_wmemcpy(dest, src, n)


/* Mapping for wmemmove */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemmove (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMMOVE_NOMAP_CASE wmemmove(dest, src, n));
}

#undef wmemmove
#define wmemmove(dest, src, n)		openosc_wmemmove(dest, src, n)


/* Mapping for wmempcpy */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmempcpy (wchar_t *dest, const wchar_t *src, size_t n)
  OSC_THROW
{
    return (WMEMPCPY_NOMAP_CASE wmempcpy(dest, src, n));
}

#undef wmempcpy
#define wmempcpy(dest, src, n)		openosc_wmempcpy(dest, src, n)


/* Mapping for wmemset */

static inline __attribute__ ((always_inline))
wchar_t *
openosc_wmemset (wchar_t *wcs, wchar_t wc, size_t n)
  OSC_THROW
{
    return (WMEMSET_NOMAP_CASE wmemset(wcs, wc, n));
}

#undef wmemset
#define wmemset(wcs, wc, n)		openosc_wmemset(wcs, wc, n)

#endif  /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /* ifndef __OPENOSC_FORTIFY_REDEFINE_MAP_H__ */

#endif  /* __OPENOSC_FORTIFY_REDEFINE_NOMAP_H__ */
