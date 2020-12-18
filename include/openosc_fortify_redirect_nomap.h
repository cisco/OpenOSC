/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_REDIRECT_NOMAP_H__
#define __OPENOSC_FORTIFY_REDIRECT_NOMAP_H__

/* openosc_fortify_redirect_map.h and openosc_fortify_redirect_nomap.h are mutually exclusive */
#ifndef __OPENOSC_FORTIFY_REDIRECT_MAP_H__

/* if OSC metric feature is disabled, we can completely exclude this osc_nomap.h header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#ifndef OPENOSC_VALIST_NOSUPPORT

#ifdef __va_arg_pack

/* Mapping for asprintf */

extern int  __REDIRECT_NTH (__openosc_asprintf_alias,
       (char **strp, const char *fmt, ...), asprintf);

__openosc_fortify_function int 
__NTH (asprintf(char **strp, const char *fmt, ...))
{
    return (ASPRINTF_NOMAP_CASE __openosc_asprintf_alias(strp, fmt, __va_arg_pack ()));
}


/* Mapping for dprintf */

extern int  __REDIRECT (__openosc_dprintf_alias,
       (int fd, const char *format, ...), dprintf);

__openosc_fortify_function int 
dprintf(int fd, const char *format, ...)
{
    return (DPRINTF_NOMAP_CASE __openosc_dprintf_alias(fd, format, __va_arg_pack ()));
}


/* Mapping for fprintf */

extern int  __REDIRECT (__openosc_fprintf_alias,
       (FILE *stream, const char *format, ...), fprintf);

__openosc_fortify_function int 
fprintf(FILE *stream, const char *format, ...)
{
    return (FPRINTF_NOMAP_CASE __openosc_fprintf_alias(stream, format, __va_arg_pack ()));
}


/* Mapping for fwprintf */

extern int  __REDIRECT (__openosc_fwprintf_alias,
       (FILE *stream, const wchar_t *format, ...), fwprintf);

__openosc_fortify_function int 
fwprintf(FILE *stream, const wchar_t *format, ...)
{
    return (FWPRINTF_NOMAP_CASE __openosc_fwprintf_alias(stream, format, __va_arg_pack ()));
}


/* Mapping for printf */

extern int  __REDIRECT (__openosc_printf_alias,
       (const char *format, ...), printf);

__openosc_fortify_function int 
printf(const char *format, ...)
{
    return (PRINTF_NOMAP_CASE __openosc_printf_alias(format, __va_arg_pack ()));
}


/* Mapping for snprintf */

extern int  __REDIRECT_NTH (__openosc_snprintf_alias,
       (char *str, size_t size, const char *format, ...), snprintf);

__openosc_fortify_function int 
__NTH (snprintf(char *str, size_t size, const char *format, ...))
{
    return (SNPRINTF_NOMAP_CASE __openosc_snprintf_alias(str, size, format, __va_arg_pack ()));
}


/* Mapping for sprintf */

extern int  __REDIRECT_NTH (__openosc_sprintf_alias,
       (char *str, const char *format, ...), sprintf);

__openosc_fortify_function int 
__NTH (sprintf(char *str, const char *format, ...))
{
    return (SPRINTF_NOMAP_CASE __openosc_sprintf_alias(str, format, __va_arg_pack ()));
}


/* Mapping for swprintf */

extern int  __REDIRECT_NTH (__openosc_swprintf_alias,
       (wchar_t *wcs, size_t maxlen, const wchar_t *format, ...), swprintf);

__openosc_fortify_function int 
__NTH (swprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, ...))
{
    return (SWPRINTF_NOMAP_CASE __openosc_swprintf_alias(wcs, maxlen, format, __va_arg_pack ()));
}


/* Mapping for wprintf */

extern int  __REDIRECT (__openosc_wprintf_alias,
       (const wchar_t *format, ...), wprintf);

__openosc_fortify_function int 
wprintf(const wchar_t *format, ...)
{
    return (WPRINTF_NOMAP_CASE __openosc_wprintf_alias(format, __va_arg_pack ()));
}

#endif /* __va_arg_pack */

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for confstr */

extern size_t  __REDIRECT_NTH (__openosc_confstr_alias,
       (int name, char *buf, size_t len), confstr);

__openosc_fortify_function size_t 
__NTH (confstr(int name, char *buf, size_t len))
{
    return (CONFSTR_NOMAP_CASE __openosc_confstr_alias(name, buf, len));
}


#ifndef OPENOSC_FGETS_DISABLE

/* Mapping for fgets */

extern char * __REDIRECT (__openosc_fgets_alias,
       (char *s, int size, FILE *stream), fgets);

__openosc_fortify_function char *
fgets(char *s, int size, FILE *stream)
{
    return (FGETS_NOMAP_CASE __openosc_fgets_alias(s, size, stream));
}

#endif /* OPENOSC_FGETS_DISABLE */


/* Mapping for fgets_unlocked */

extern char * __REDIRECT (__openosc_fgets_unlocked_alias,
       (char *s, int n, FILE *stream), fgets_unlocked);

__openosc_fortify_function char *
fgets_unlocked(char *s, int n, FILE *stream)
{
    return (FGETS_UNLOCKED_NOMAP_CASE __openosc_fgets_unlocked_alias(s, n, stream));
}


/* Mapping for fgetws */

extern wchar_t * __REDIRECT (__openosc_fgetws_alias,
       (wchar_t *ws, int n, FILE *stream), fgetws);

__openosc_fortify_function wchar_t *
fgetws(wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_NOMAP_CASE __openosc_fgetws_alias(ws, n, stream));
}


/* Mapping for fgetws_unlocked */

extern wchar_t * __REDIRECT (__openosc_fgetws_unlocked_alias,
       (wchar_t *ws, int n, FILE *stream), fgetws_unlocked);

__openosc_fortify_function wchar_t *
fgetws_unlocked(wchar_t *ws, int n, FILE *stream)
{
    return (FGETWS_UNLOCKED_NOMAP_CASE __openosc_fgetws_unlocked_alias(ws, n, stream));
}


/* Mapping for fread */

extern size_t  __REDIRECT (__openosc_fread_alias,
       (void *ptr, size_t size, size_t nmemb, FILE *stream), fread);

__openosc_fortify_function size_t 
fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return (FREAD_NOMAP_CASE __openosc_fread_alias(ptr, size, nmemb, stream));
}


#ifndef fread_unlocked

/* Mapping for fread_unlocked */

extern size_t  __REDIRECT (__openosc_fread_unlocked_alias,
       (void *ptr, size_t size, size_t n, FILE *stream), fread_unlocked);

__openosc_fortify_function size_t 
fread_unlocked(void *ptr, size_t size, size_t n, FILE *stream)
{
    return (FREAD_UNLOCKED_NOMAP_CASE __openosc_fread_unlocked_alias(ptr, size, n, stream));
}

#endif /* fread_unlocked */


#ifndef OPENOSC_GETCWD_DISABLE

/* Mapping for getcwd */

extern char * __REDIRECT_NTH (__openosc_getcwd_alias,
       (char *buf, size_t size), getcwd);

__openosc_fortify_function char *
__NTH (getcwd(char *buf, size_t size))
{
    return (GETCWD_NOMAP_CASE __openosc_getcwd_alias(buf, size));
}

#endif /* OPENOSC_GETCWD_DISABLE */


/* Mapping for getdomainname */

extern int  __REDIRECT_NTH (__openosc_getdomainname_alias,
       (char *name, size_t len), getdomainname);

__openosc_fortify_function int 
__NTH (getdomainname(char *name, size_t len))
{
    return (GETDOMAINNAME_NOMAP_CASE __openosc_getdomainname_alias(name, len));
}


/* Mapping for getgroups */

extern int  __REDIRECT_NTH (__openosc_getgroups_alias,
       (int size, gid_t list[]), getgroups);

__openosc_fortify_function int 
__NTH (getgroups(int size, gid_t list[]))
{
    return (GETGROUPS_NOMAP_CASE __openosc_getgroups_alias(size, list));
}


/* Mapping for gethostname */

extern int  __REDIRECT_NTH (__openosc_gethostname_alias,
       (char *name, size_t len), gethostname);

__openosc_fortify_function int 
__NTH (gethostname(char *name, size_t len))
{
    return (GETHOSTNAME_NOMAP_CASE __openosc_gethostname_alias(name, len));
}


#ifndef OPENOSC_GETS_DISABLE

/* Mapping for gets */

extern char * __REDIRECT (__openosc_gets_alias,
       (char *s), gets);

__openosc_fortify_function char *
gets(char *s)
{
    return (GETS_NOMAP_CASE __openosc_gets_alias(s));
}

#endif /* OPENOSC_GETS_DISABLE */


/* Mapping for getwd */

extern char * __REDIRECT_NTH (__openosc_getwd_alias,
       (char *buf), getwd);

__openosc_fortify_function char *
__NTH (getwd(char *buf))
{
    return (GETWD_NOMAP_CASE __openosc_getwd_alias(buf));
}


/* Mapping for mbsnrtowcs */

extern size_t  __REDIRECT_NTH (__openosc_mbsnrtowcs_alias,
       (wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps), mbsnrtowcs);

__openosc_fortify_function size_t 
__NTH (mbsnrtowcs(wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps))
{
    return (MBSNRTOWCS_NOMAP_CASE __openosc_mbsnrtowcs_alias(dest, src, nms, len, ps));
}


/* Mapping for mbsrtowcs */

extern size_t  __REDIRECT_NTH (__openosc_mbsrtowcs_alias,
       (wchar_t *dest, const char **src, size_t len, mbstate_t *ps), mbsrtowcs);

__openosc_fortify_function size_t 
__NTH (mbsrtowcs(wchar_t *dest, const char **src, size_t len, mbstate_t *ps))
{
    return (MBSRTOWCS_NOMAP_CASE __openosc_mbsrtowcs_alias(dest, src, len, ps));
}


/* Mapping for mbstowcs */

extern size_t  __REDIRECT_NTH (__openosc_mbstowcs_alias,
       (wchar_t *dest, const char *src, size_t n), mbstowcs);

__openosc_fortify_function size_t 
__NTH (mbstowcs(wchar_t *dest, const char *src, size_t n))
{
    return (MBSTOWCS_NOMAP_CASE __openosc_mbstowcs_alias(dest, src, n));
}


/* Mapping for mempcpy */

extern void * __REDIRECT_NTH (__openosc_mempcpy_alias,
       (void *dest, const void *src, size_t n), mempcpy);

__openosc_fortify_function void *
__NTH (mempcpy(void *dest, const void *src, size_t n))
{
    return (MEMPCPY_NOMAP_CASE __openosc_mempcpy_alias(dest, src, n));
}


#ifndef OPENOSC_POLL_DISABLE

/* Mapping for poll */

extern int  __REDIRECT (__openosc_poll_alias,
       (struct pollfd *fds, nfds_t nfds, int timeout), poll);

__openosc_fortify_function int 
poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    return (POLL_NOMAP_CASE __openosc_poll_alias(fds, nfds, timeout));
}

#endif /* OPENOSC_POLL_DISABLE */


#ifndef OPENOSC_PPOLL_DISABLE

/* Mapping for ppoll */

extern int  __REDIRECT (__openosc_ppoll_alias,
       (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask), ppoll);

__openosc_fortify_function int 
ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    return (PPOLL_NOMAP_CASE __openosc_ppoll_alias(fds, nfds, timeout_ts, sigmask));
}

#endif /* OPENOSC_PPOLL_DISABLE */


#ifndef OPENOSC_PREAD_DISABLE

/* Mapping for pread */

extern ssize_t  __REDIRECT (__openosc_pread_alias,
       (int fd, void *buf, size_t count, off_t offset), pread);

__openosc_fortify_function ssize_t 
pread(int fd, void *buf, size_t count, off_t offset)
{
    return (PREAD_NOMAP_CASE __openosc_pread_alias(fd, buf, count, offset));
}

#endif /* OPENOSC_PREAD_DISABLE */


#ifndef OPENOSC_READ_DISABLE

/* Mapping for read */

extern ssize_t  __REDIRECT (__openosc_read_alias,
       (int fd, void *buf, size_t count), read);

__openosc_fortify_function ssize_t 
read(int fd, void *buf, size_t count)
{
    return (READ_NOMAP_CASE __openosc_read_alias(fd, buf, count));
}

#endif /* OPENOSC_READ_DISABLE */


/* Mapping for readlinkat */

extern ssize_t  __REDIRECT_NTH (__openosc_readlinkat_alias,
       (int dirfd, const char *pathname, char *buf, size_t bufsiz), readlinkat);

__openosc_fortify_function ssize_t
__NTH (readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz))
{
    return (READLINKAT_NOMAP_CASE __openosc_readlinkat_alias(dirfd, pathname, buf, bufsiz));
}


/* Mapping for readlink */

extern ssize_t  __REDIRECT_NTH (__openosc_readlink_alias,
       (const char *path, char *buf, size_t bufsiz), readlink);

__openosc_fortify_function ssize_t 
__NTH (readlink(const char *path, char *buf, size_t bufsiz))
{
    return (READLINK_NOMAP_CASE __openosc_readlink_alias(path, buf, bufsiz));
}


/* Mapping for realpath */

extern char * __REDIRECT_NTH (__openosc_realpath_alias,
       (const char *path, char *resolved_path), realpath);

__openosc_fortify_function char *
__NTH (realpath(const char *path, char *resolved_path))
{
    return (REALPATH_NOMAP_CASE __openosc_realpath_alias(path, resolved_path));
}


#ifndef OPENOSC_RECV_DISABLE

/* Mapping for recv */

extern ssize_t  __REDIRECT (__openosc_recv_alias,
       (int sockfd, void *buf, size_t len, int flags), recv);

__openosc_fortify_function ssize_t 
recv(int sockfd, void *buf, size_t len, int flags)
{
    return (RECV_NOMAP_CASE __openosc_recv_alias(sockfd, buf, len, flags));
}

#endif /* OPENOSC_RECV_DISABLE */


#ifndef OPENOSC_RECVFROM_DISABLE

/* Mapping for recvfrom */

extern ssize_t  __REDIRECT (__openosc_recvfrom_alias,
       (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen), recvfrom);

__openosc_fortify_function ssize_t 
recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    return (RECVFROM_NOMAP_CASE __openosc_recvfrom_alias(sockfd, buf, len, flags, src_addr, addrlen));
}

#endif /* OPENOSC_RECVFROM_DISABLE */


/* Mapping for stpcpy */

extern char * __REDIRECT_NTH (__openosc_stpcpy_alias,
       (char *dest, const char *src), stpcpy);

__openosc_fortify_function char *
__NTH (stpcpy(char *dest, const char *src))
{
    return (STPCPY_NOMAP_CASE __openosc_stpcpy_alias(dest, src));
}


/* Mapping for stpncpy */

extern char * __REDIRECT_NTH (__openosc_stpncpy_alias,
       (char *dest, const char *src, size_t n), stpncpy);

__openosc_fortify_function char *
__NTH (stpncpy(char *dest, const char *src, size_t n))
{
    return (STPNCPY_NOMAP_CASE __openosc_stpncpy_alias(dest, src, n));
}


/* Mapping for ttyname_r */

extern int  __REDIRECT_NTH (__openosc_ttyname_r_alias,
       (int fd, char *buf, size_t buflen), ttyname_r);

__openosc_fortify_function int 
__NTH (ttyname_r(int fd, char *buf, size_t buflen))
{
    return (TTYNAME_R_NOMAP_CASE __openosc_ttyname_r_alias(fd, buf, buflen));
}


#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vasprintf */

extern int  __REDIRECT_NTH (__openosc_vasprintf_alias,
       (char **strp, const char *fmt, va_list ap), vasprintf);

__openosc_fortify_function int 
__NTH (vasprintf(char **strp, const char *fmt, va_list ap))
{
    return (VASPRINTF_NOMAP_CASE __openosc_vasprintf_alias(strp, fmt, ap));
}


/* Mapping for vdprintf */

extern int  __REDIRECT (__openosc_vdprintf_alias,
       (int fd, const char *format, va_list ap), vdprintf);

__openosc_fortify_function int 
vdprintf(int fd, const char *format, va_list ap)
{
    return (VDPRINTF_NOMAP_CASE __openosc_vdprintf_alias(fd, format, ap));
}


/* Mapping for vfprintf */

extern int  __REDIRECT (__openosc_vfprintf_alias,
       (FILE *stream, const char *format, va_list ap), vfprintf);

__openosc_fortify_function int 
vfprintf(FILE *stream, const char *format, va_list ap)
{
    return (VFPRINTF_NOMAP_CASE __openosc_vfprintf_alias(stream, format, ap));
}


/* Mapping for vfwprintf */

extern int  __REDIRECT (__openosc_vfwprintf_alias,
       (FILE *stream, const wchar_t *format, va_list args), vfwprintf);

__openosc_fortify_function int 
vfwprintf(FILE *stream, const wchar_t *format, va_list args)
{
    return (VFWPRINTF_NOMAP_CASE __openosc_vfwprintf_alias(stream, format, args));
}


/* bits/stdio.h:36 has a define for vprintf, causing redefinition error */
#ifndef __USE_EXTERN_INLINES

#ifndef OPENOSC_VPRINTF_DISABLE

/* Mapping for vprintf */

extern int  __REDIRECT (__openosc_vprintf_alias,
       (const char *format, va_list ap), vprintf);

__openosc_fortify_function int 
vprintf(const char *format, va_list ap)
{
    return (VPRINTF_NOMAP_CASE __openosc_vprintf_alias(format, ap));
}

#endif /* OPENOSC_VPRINTF_DISABLE */

#endif /* __USE_EXTERN_INLINES */


/* Mapping for vsprintf */

extern int  __REDIRECT_NTH (__openosc_vsprintf_alias,
       (char *str, const char *format, va_list ap), vsprintf);

__openosc_fortify_function int 
__NTH (vsprintf(char *str, const char *format, va_list ap))
{
    return (VSPRINTF_NOMAP_CASE __openosc_vsprintf_alias(str, format, ap));
}


/* Mapping for vswprintf */

extern int  __REDIRECT_NTH (__openosc_vswprintf_alias,
       (wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args), vswprintf);

__openosc_fortify_function int 
__NTH (vswprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args))
{
    return (VSWPRINTF_NOMAP_CASE __openosc_vswprintf_alias(wcs, maxlen, format, args));
}


/* Mapping for vwprintf */

extern int  __REDIRECT (__openosc_vwprintf_alias,
       (const wchar_t *format, va_list args), vwprintf);

__openosc_fortify_function int 
vwprintf(const wchar_t *format, va_list args)
{
    return (VWPRINTF_NOMAP_CASE __openosc_vwprintf_alias(format, args));
}

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for wcpcpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wcpcpy_alias,
       (wchar_t *dest, const wchar_t *src), wcpcpy);

__openosc_fortify_function wchar_t *
__NTH (wcpcpy(wchar_t *dest, const wchar_t *src))
{
    return (WCPCPY_NOMAP_CASE __openosc_wcpcpy_alias(dest, src));
}


/* Mapping for wcpncpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wcpncpy_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wcpncpy);

__openosc_fortify_function wchar_t *
__NTH (wcpncpy(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WCPNCPY_NOMAP_CASE __openosc_wcpncpy_alias(dest, src, n));
}


/* Mapping for wcrtomb */

extern size_t  __REDIRECT_NTH (__openosc_wcrtomb_alias,
       (char *s, wchar_t wc, mbstate_t *ps), wcrtomb);

__openosc_fortify_function size_t 
__NTH (wcrtomb(char *s, wchar_t wc, mbstate_t *ps))
{
    return (WCRTOMB_NOMAP_CASE __openosc_wcrtomb_alias(s, wc, ps));
}


/* Mapping for wcscat */

extern wchar_t * __REDIRECT_NTH (__openosc_wcscat_alias,
       (wchar_t *dest, const wchar_t *src), wcscat);

__openosc_fortify_function wchar_t *
__NTH (wcscat(wchar_t *dest, const wchar_t *src))
{
    return (WCSCAT_NOMAP_CASE __openosc_wcscat_alias(dest, src));
}


/* Mapping for wcscpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wcscpy_alias,
       (wchar_t *dest, const wchar_t *src), wcscpy);

__openosc_fortify_function wchar_t *
__NTH (wcscpy(wchar_t *dest, const wchar_t *src))
{
    return (WCSCPY_NOMAP_CASE __openosc_wcscpy_alias(dest, src));
}


/* Mapping for wcsncat */

extern wchar_t * __REDIRECT_NTH (__openosc_wcsncat_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wcsncat);

__openosc_fortify_function wchar_t *
__NTH (wcsncat(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WCSNCAT_NOMAP_CASE __openosc_wcsncat_alias(dest, src, n));
}


/* Mapping for wcsncpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wcsncpy_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wcsncpy);

__openosc_fortify_function wchar_t *
__NTH (wcsncpy(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WCSNCPY_NOMAP_CASE __openosc_wcsncpy_alias(dest, src, n));
}


/* Mapping for wcsnrtombs */

extern size_t  __REDIRECT_NTH (__openosc_wcsnrtombs_alias,
       (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps), wcsnrtombs);

__openosc_fortify_function size_t 
__NTH (wcsnrtombs(char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps))
{
    return (WCSNRTOMBS_NOMAP_CASE __openosc_wcsnrtombs_alias(dest, src, nwc, len, ps));
}


/* Mapping for wcsrtombs */

extern size_t  __REDIRECT_NTH (__openosc_wcsrtombs_alias,
       (char *dest, const wchar_t **src, size_t len, mbstate_t *ps), wcsrtombs);

__openosc_fortify_function size_t 
__NTH (wcsrtombs(char *dest, const wchar_t **src, size_t len, mbstate_t *ps))
{
    return (WCSRTOMBS_NOMAP_CASE __openosc_wcsrtombs_alias(dest, src, len, ps));
}


/* Mapping for wcstombs */

extern size_t  __REDIRECT_NTH (__openosc_wcstombs_alias,
       (char *dest, const wchar_t *src, size_t n), wcstombs);

__openosc_fortify_function size_t 
__NTH (wcstombs(char *dest, const wchar_t *src, size_t n))
{
    return (WCSTOMBS_NOMAP_CASE __openosc_wcstombs_alias(dest, src, n));
}


/* Mapping for wctomb */

extern int  __REDIRECT_NTH (__openosc_wctomb_alias,
       (char *s, wchar_t wc), wctomb);

__openosc_fortify_function int 
__NTH (wctomb(char *s, wchar_t wc))
{
    return (WCTOMB_NOMAP_CASE __openosc_wctomb_alias(s, wc));
}


/* Mapping for wmemcpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wmemcpy_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wmemcpy);

__openosc_fortify_function wchar_t *
__NTH (wmemcpy(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WMEMCPY_NOMAP_CASE __openosc_wmemcpy_alias(dest, src, n));
}


/* Mapping for wmemmove */

extern wchar_t * __REDIRECT_NTH (__openosc_wmemmove_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wmemmove);

__openosc_fortify_function wchar_t *
__NTH (wmemmove(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WMEMMOVE_NOMAP_CASE __openosc_wmemmove_alias(dest, src, n));
}


/* Mapping for wmempcpy */

extern wchar_t * __REDIRECT_NTH (__openosc_wmempcpy_alias,
       (wchar_t *dest, const wchar_t *src, size_t n), wmempcpy);

__openosc_fortify_function wchar_t *
__NTH (wmempcpy(wchar_t *dest, const wchar_t *src, size_t n))
{
    return (WMEMPCPY_NOMAP_CASE __openosc_wmempcpy_alias(dest, src, n));
}


/* Mapping for wmemset */

extern wchar_t * __REDIRECT_NTH (__openosc_wmemset_alias,
       (wchar_t *wcs, wchar_t wc, size_t n), wmemset);

__openosc_fortify_function wchar_t *
__NTH (wmemset(wchar_t *wcs, wchar_t wc, size_t n))
{
    return (WMEMSET_NOMAP_CASE __openosc_wmemset_alias(wcs, wc, n));
}

#endif  /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /* ifndef __OPENOSC_FORTIFY_REDIRECT_MAP_H__ */

#endif  /* __OPENOSC_FORTIFY_REDIRECT_NOMAP_H__ */
