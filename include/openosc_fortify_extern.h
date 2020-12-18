/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_EXTERN_H__
#define __OPENOSC_FORTIFY_EXTERN_H__

/* for __WORDSIZE */
#include <bits/wordsize.h>

/* Define va_list */
#ifndef _VA_LIST
#define _VA_LIST
typedef __builtin_va_list va_list;
#endif

#ifndef OSC_THROW
#ifdef __cplusplus
#define OSC_THROW __THROW
#else
#define OSC_THROW
#endif
#endif


/* The below data type forward declarations are required */
#if __WORDSIZE == 32
typedef int __ssize_t;
#else
typedef long int __ssize_t;
#endif
typedef __ssize_t ssize_t;
typedef unsigned int __socklen_t;
typedef unsigned int __gid_t;
typedef __socklen_t socklen_t;
typedef __gid_t gid_t;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef unsigned long int nfds_t;
struct pollfd;
struct timespec;
struct sockaddr;
/* import size_t and wchar_t definition only */
#define __need_size_t
#define __need_wchar_t
#include <stddef.h>

/*
 * Anonymous struct like __sigset_t or __mbstate_t cannot be forward-declared.
 * OpenOSC is forced to define the exact same struct as the system header, and
 * define the *_defined flag to prevent later redefinition in system header.
 * The below _openosc_* type must be the exact same definition as what is
 * in openosc_fortify_map.c file, where static assertion is checked.
 */

#ifndef ____sigset_t_defined
#define ____sigset_t_defined

#ifndef _SIGSET_H_types
# define _SIGSET_H_types        1
#endif

typedef int __sig_atomic_t;

/* A `sigset_t' has a bit for each signal.  */

# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct
  {
    unsigned long int __val[_SIGSET_NWORDS];
  } __sigset_t;

#endif

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef __sigset_t sigset_t;
#endif

#ifndef ____mbstate_t_defined
#define ____mbstate_t_defined 1

/* Integral type unchanged by default argument promotions that can
   hold any value corresponding to members of the extended character
   set, as well as at least one value that does not correspond to any
   member of the extended character set.  */
#ifndef __WINT_TYPE__
# define __WINT_TYPE__ unsigned int
#endif

/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    __WINT_TYPE__ __wch;
    char __wchb[4];
  } __value;            /* Value so far.  */
} __mbstate_t;

#endif

#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
typedef __mbstate_t mbstate_t;
#endif

/* Need to disable vprintf because it is defined as a macro in stdio.h */
#define OPENOSC_VPRINTF_DISABLE

extern size_t confstr(int name, char *buf, size_t len) __THROW ;
extern char *fgets(char *s, int size, FILE *stream);
extern char *fgets_unlocked(char *s, int n, FILE *stream);
extern wchar_t *fgetws(wchar_t *ws, int n, FILE *stream);
extern wchar_t *fgetws_unlocked(wchar_t *ws, int n, FILE *stream);
extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
#ifndef fread_unlocked
extern size_t fread_unlocked(void *ptr, size_t size, size_t n, FILE *stream);
#endif
#ifndef OPENOSC_GETCWD_DISABLE
extern char *getcwd(char *buf, size_t size) __THROW ;
#endif
extern int getdomainname(char *name, size_t len) __THROW ;
extern int getgroups(int size, gid_t list[]) __THROW ;
extern int gethostname(char *name, size_t len) __THROW ;
extern char *gets(char *s);
extern char *getwd(char *buf) __THROW ;
extern size_t mbsnrtowcs(wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps) __THROW ; 
extern size_t mbsrtowcs(wchar_t *dest, const char **src, size_t len, mbstate_t *ps) __THROW ; 
extern size_t mbstowcs(wchar_t *dest, const char *src, size_t n) __THROW ;
extern void *mempcpy(void *dest, const void *src, size_t n) __THROW ;
#ifndef OPENOSC_POLL_DISABLE
extern int poll(struct pollfd *fds, nfds_t nfds, int timeout) ;
#endif
#ifndef OPENOSC_PPOLL_DISABLE
extern int ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask) ;
#endif
#ifndef OPENOSC_PREAD_DISABLE
typedef long int __off_t;
typedef __off_t off_t;
extern ssize_t pread(int fd, void *buf, size_t count, off_t offset) ;
#endif
#ifndef OPENOSC_READ_DISABLE
extern ssize_t read(int fd, void *buf, size_t count) ;
#endif
extern ssize_t readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz) __THROW ; 
extern ssize_t readlink(const char *path, char *buf, size_t bufsiz) __THROW ;
extern char *realpath(const char *path, char *resolved_path) __THROW ;
#ifndef OPENOSC_RECV_DISABLE
extern ssize_t recv(int sockfd, void *buf, size_t len, int flags) ;
#endif
#ifndef OPENOSC_RECVFROM_DISABLE
extern ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) ;
#endif
extern char *stpcpy(char *dest, const char *src) __THROW ;
extern char *stpncpy(char *dest, const char *src, size_t n) __THROW ;
extern int ttyname_r(int fd, char *buf, size_t buflen) __THROW ;
extern int vasprintf(char **strp, const char *fmt, va_list ap) __THROWNL;
extern int vdprintf(int fd, const char *format, va_list ap);
extern int vfprintf(FILE *stream, const char *format, va_list ap);
extern int vfwprintf(FILE *stream, const wchar_t *format, va_list args);
#ifndef OPENOSC_VPRINTF_DISABLE
extern int vprintf(const char *format, va_list ap);
#endif
extern int vsprintf(char *str, const char *format, va_list ap) __THROWNL;
extern int vswprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args) __THROW ; 
extern int vwprintf(const wchar_t *format, va_list args);
extern wchar_t *wcpcpy(wchar_t *dest, const wchar_t *src) __THROW ;
extern wchar_t *wcpncpy(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern size_t wcrtomb(char *s, wchar_t wc, mbstate_t *ps) __THROW ;
extern wchar_t *wcscat(wchar_t *dest, const wchar_t *src) __THROW ;
extern wchar_t *wcscpy(wchar_t *dest, const wchar_t *src) __THROW ;
extern wchar_t *wcsncat(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern wchar_t *wcsncpy(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern size_t wcsnrtombs(char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps) __THROW ; 
extern size_t wcsrtombs(char *dest, const wchar_t **src, size_t len, mbstate_t *ps) __THROW ; 
extern size_t wcstombs(char *dest, const wchar_t *src, size_t n) __THROW ;
extern int wctomb(char *s, wchar_t wc) __THROW ;
extern wchar_t *wmemcpy(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern wchar_t *wmempcpy(wchar_t *dest, const wchar_t *src, size_t n) __THROW ;
extern wchar_t *wmemset(wchar_t *wcs, wchar_t wc, size_t n) __THROW ;

#ifndef OPENOSC_ASPRINTF_DISABLE
extern int asprintf(char **strp, const char *fmt, ...) __THROWNL ;
#endif
extern int dprintf(int fd, const char *format, ...);
extern int fprintf(FILE *stream, const char *format, ...);
extern int fwprintf(FILE *stream, const wchar_t *format, ...);
extern int printf(const char *format, ...);
extern int snprintf(char *str, size_t size, const char *format, ...) __THROWNL;
extern int sprintf(char *str, const char *format, ...) __THROWNL ;
extern int swprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, ...) __THROW ; 
extern int wprintf(const wchar_t *format, ...);


#endif  /* __OPENOSC_FORTIFY_EXTERN_H__ */
