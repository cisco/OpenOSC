/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h> /* Definition of AT_* constants */
#include <limits.h>
#include <poll.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <wchar.h>
#include <errno.h>
#include <stdarg.h>
#include <assert.h>
#include "openosc_common.h"

/* uClibc does not support additional runtime check */
#define OPENOSC_NO_GLIBC_ADDITIONAL_CHK

/* Sanity check on some important data types */

/*
 * Anonymous struct like __sigset_t or __mbstate_t cannot be forward-declared.
 * OpenOSC is forced to define the exact same struct as the system header, and
 * define the *_defined flag to prevent later redefinition in system header.
 * The below _openosc_* type must be the exact same definition as what is
 * defined in openosc_fortify_extern.h header file. And static_assert will
 * make sure that the size of two structs be the same. More complicate
 * assertion may be possible, but we feel struct size comparison should be
 * sufficient for our need.
 */

/* A `sigset_t' has a bit for each signal.  */

# define _OPENOSC_SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct
  {
    unsigned long int __val[_OPENOSC_SIGSET_NWORDS];
  } _openosc__sigset_t;

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
} _openosc__mbstate_t;

#ifdef static_assert
static_assert( sizeof(struct pollfd) == (sizeof(int) + sizeof(short) + sizeof(short)),
               "poll() overflow detection relies on struct pollfd size being equal to "
               "int+short+short, please check struct pollfd definition of your system." );
static_assert( sizeof(_openosc__sigset_t) == sizeof(__sigset_t),
               "OpenOSC must provide the exact sigset_t definition as your system.");
static_assert( sizeof(_openosc__mbstate_t) == sizeof(__mbstate_t),
               "OpenOSC must provide the exact mbstate_t definition as your system.");
#else

/* The below is copied from http://www.pixelbeat.org/programming/gcc/static_assert.html */
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
  #define STATIC_ASSERT(e,m) \
    ;enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(int)(!!(e)) }
#else
  /* This can't be used twice on the same line so ensure if using in headers
   * that the headers are not included twice (by wrapping in #ifndef...#endif)
   * Note it doesn't cause an issue when used on same line of separate modules
   * compiled with gcc -combine -fwhole-program.  */
  #define STATIC_ASSERT(e,m) \
    ;enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(int)(!!(e)) }
#endif

STATIC_ASSERT( sizeof(struct pollfd) == (sizeof(int) + sizeof(short) + sizeof(short)),
               "poll() overflow detection relies on struct pollfd size being equal to "
               "int+short+short, please check struct pollfd definition of your system." );
STATIC_ASSERT( sizeof(_openosc__sigset_t) == sizeof(__sigset_t),
               "OpenOSC must provide the exact sigset_t definition as your system.");
STATIC_ASSERT( sizeof(_openosc__mbstate_t) == sizeof(__mbstate_t),
               "OpenOSC must provide the exact mbstate_t definition as your system.");

#endif /* static_assert */

/* End of Sanity check on some important data types */


/* Mapping for confstr */

size_t 
__openosc_confstr_to_buf (size_t dest_len, int name, char *buf, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("confstr", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef confstr

    return (confstr(name, buf, len));
}


/* Mapping for fgets */

extern char *
__fgets_chk (char *buf, size_t size, int n, FILE *fp);

char *
__openosc_fgets_to_buf (size_t dest_len, int additional_chk, char *s, int n, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    /* Same negative check as in glibc */
    if (n <= 0) {
        return NULL;
    }

    if ((size_t)n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fgets", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef fgets

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fgets_chk(s, dest_len, n, stream));
#else
        return (fgets(s, n, stream));
#endif
    } else {
        return (fgets(s, n, stream));
    }
}


/* Mapping for fgets_unlocked */

extern char *fgets_unlocked(char *s, int n, FILE *stream);
extern char *
__fgets_unlocked_chk (char *buf, size_t size, int n, FILE *fp);

char *
__openosc_fgets_unlocked_to_buf (size_t dest_len, int additional_chk, char *s, int n, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    /* Same negative check as in glibc */
    if (n <= 0) {
        return NULL;
    }

    if ((size_t)n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fgets_unlocked", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef fgets_unlocked

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fgets_unlocked_chk(s, dest_len, n, stream));
#else
        return (fgets_unlocked(s, n, stream));
#endif
    } else {
        return (fgets_unlocked(s, n, stream));
    }
}

/*
 * Note: For all functions with wchar_t * destination buffer,
 * dest_len parameter is always number of wchar_t, not char.
 */

/* Mapping for fgetws */

extern wchar_t *
__fgetws_chk (wchar_t *buf, size_t size, int n, FILE *fp);

wchar_t *
__openosc_fgetws_to_buf (size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    /* Same negative check as in glibc */
    if (n <= 0) {
        return NULL;
    }

    if ((size_t)n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fgetws", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef fgetws

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fgetws_chk(ws, dest_len, n, stream));
#else
        return (fgetws(ws, n, stream));
#endif
    } else {
        return (fgetws(ws, n, stream));
    }
}


/* Mapping for fgetws_unlocked */

extern wchar_t *fgetws_unlocked(wchar_t *ws, int n, FILE *stream);
extern wchar_t *
__fgetws_unlocked_chk (wchar_t *buf, size_t size, int n, FILE *fp);

wchar_t *
__openosc_fgetws_unlocked_to_buf (size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    /* Same negative check as in glibc */
    if (n <= 0) {
        return NULL;
    }

    if ((size_t)n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fgetws_unlocked", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef fgetws_unlocked

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fgetws_unlocked_chk(ws, dest_len, n, stream));
#else
        return (fgetws_unlocked(ws, n, stream));
#endif
    } else {
        return (fgetws_unlocked(ws, n, stream));
    }
}


/* Mapping for fread */

extern size_t
__fread_chk (void *__restrict ptr, size_t ptrlen,
             size_t size, size_t n, FILE *__restrict stream);

size_t 
__openosc_fread_to_buf (size_t dest_len, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if ((size * nmemb) > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fread", dest_len, (size * nmemb));
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            nmemb = dest_len/size;
        }
    }
#undef fread

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fread_chk(ptr, dest_len, size, nmemb, stream));
#else
        return (fread(ptr, size, nmemb, stream));
#endif
    } else {
        return (fread(ptr, size, nmemb, stream));
    }
}


/* Mapping for fread_unlocked */

#ifndef fread_unlocked
extern size_t fread_unlocked(void *ptr, size_t size, size_t n,
                             FILE *stream);
#endif
extern size_t
__fread_unlocked_chk (void *__restrict ptr, size_t ptrlen,
                      size_t size, size_t n, FILE *__restrict stream);

size_t 
__openosc_fread_unlocked_to_buf (size_t dest_len, int additional_chk, void *ptr,
                         size_t size, size_t n, FILE *stream)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("fread_unlocked", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len/size;
        }
    }
#undef fread_unlocked

    if (additional_chk) {
        /* Calling glibc _chk function for additional buffer overflow check */
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__fread_unlocked_chk(ptr, dest_len, size, n, stream));
#else
        return (fread_unlocked(ptr, size, n, stream));
#endif
    } else {
        return (fread_unlocked(ptr, size, n, stream));
    }
}


/* Mapping for getcwd */

char *
__openosc_getcwd_to_buf (size_t dest_len, char *buf, size_t size)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (size > dest_len) {
        if (openosc_log) {
            openosc_danger_error("getcwd", dest_len, size);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            size = dest_len;
        }
    }
#undef getcwd

    return (getcwd(buf, size));
}


/* Mapping for getdomainname */

int 
__openosc_getdomainname_to_buf (size_t dest_len, char *name, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("getdomainname", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef getdomainname

    return (getdomainname(name, len));
}


/* Mapping for getgroups */

int 
__openosc_getgroups_to_buf (size_t dest_len, int size, gid_t list[])
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    /* If size is 0, then list is not modified */
    if (size <= 0) {
        return (getgroups(size, list));
    }

    if ((size * sizeof(gid_t)) > dest_len) {
        if (openosc_log) {
            openosc_danger_error("getgroups", dest_len, size * sizeof(gid_t));
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            size = dest_len/sizeof(gid_t);
        }
    }
#undef getgroups

    return (getgroups(size, list));
}


/* Mapping for gethostname */

int 
__openosc_gethostname_to_buf (size_t dest_len, char *name, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("gethostname", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef gethostname

    return (gethostname(name, len));
}


/* Mapping for gets: runtime check not needed in this library */


/* Mapping for getwd */

char *
__openosc_getwd_to_buf (size_t dest_len, char *buf)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    char *res = getcwd(buf, dest_len);
    if (res == NULL && errno == ERANGE) {
        if (openosc_log) {
            openosc_danger_error("gethostname", dest_len, dest_len + 5);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        //if (openosc_truncate) {
            /* Well, we cannot do truncate here, so do nothing */
        //}
    }
    return res;
}


/* Mapping for longjmp: runtime check not needed in this library */


/* Mapping for mbsnrtowcs */

size_t 
__openosc_mbsnrtowcs_to_buf (size_t dest_len, wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("mbsnrtowcs", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef mbsnrtowcs

    return (mbsnrtowcs(dest, src, nms, len, ps));
}


/* Mapping for mbsrtowcs */

size_t 
__openosc_mbsrtowcs_to_buf (size_t dest_len, wchar_t *dest, const char **src, size_t len, mbstate_t *ps)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("mbsrtowcs", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef mbsrtowcs

    return (mbsrtowcs(dest, src, len, ps));
}


/* Mapping for mbstowcs */

size_t 
__openosc_mbstowcs_to_buf (size_t dest_len, wchar_t *dest, const char *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("mbstowcs", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef mbstowcs

    return (mbstowcs(dest, src, n));
}


/* Mapping for mempcpy */

extern void *mempcpy(void *dest, const void *src, size_t n);

void *
__openosc_mempcpy_to_buf (size_t dest_len, void *dest, const void *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("mempcpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef mempcpy

    return (mempcpy(dest, src, n));
}


/* Mapping for poll */

int 
__openosc_poll_to_buf (size_t dest_len, struct pollfd *fds, nfds_t nfds, int timeout)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (sizeof(struct pollfd *) * nfds > dest_len) {
        if (openosc_log) {
            openosc_danger_error("poll", dest_len, sizeof(struct pollfd *) * nfds);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        /* Well, is it good to truncate the fds array? Some fds will not be monitored! */
        if (openosc_truncate) {
            nfds = dest_len/sizeof(struct pollfd *);
        }
    }
#undef poll

    return (poll(fds, nfds, timeout));
}


/* Mapping for ppoll */

int 
__openosc_ppoll_to_buf (size_t dest_len, struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (sizeof(struct pollfd *) * nfds > dest_len) {
        if (openosc_log) {
            openosc_danger_error("ppoll", dest_len, sizeof(struct pollfd *) * nfds);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        /* Well, is it good to truncate the fds array? Some fds will not be monitored! */
        if (openosc_truncate) {
            nfds = dest_len/sizeof(struct pollfd *);
        }
    }
#undef ppoll

    return (ppoll(fds, nfds, timeout_ts, sigmask));
}


/* Mapping for pread */

ssize_t 
__openosc_pread_to_buf (size_t dest_len, int fd, void *buf, size_t count, off_t offset)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (count > dest_len) {
        if (openosc_log) {
            openosc_danger_error("pread", dest_len, count);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            count = dest_len;
        }
    }
#undef pread

    return (pread(fd, buf, count, offset));
}


/* Mapping for read */

ssize_t 
__openosc_read_to_buf (size_t dest_len, int fd, void *buf, size_t count)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (count > dest_len) {
        if (openosc_log) {
            openosc_danger_error("read", dest_len, count);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            count = dest_len;
        }
    }
#undef read

    return (read(fd, buf, count));
}


/* Mapping for readlinkat */

ssize_t
__openosc_readlinkat_to_buf (size_t dest_len, int dirfd, const char *pathname, char *buf, size_t bufsiz)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (bufsiz > dest_len) {
        if (openosc_log) {
            openosc_danger_error("readlinkat", dest_len, bufsiz);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            bufsiz = dest_len;
        }
    }
#undef readlinkat

    return (readlinkat(dirfd, pathname, buf, bufsiz));
}


/* Mapping for readlink */

ssize_t 
__openosc_readlink_to_buf (size_t dest_len, const char *path, char *buf, size_t bufsiz)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (bufsiz > dest_len) {
        if (openosc_log) {
            openosc_danger_error("readlink", dest_len, bufsiz);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            bufsiz = dest_len;
        }
    }
#undef readlink

    return (readlink(path, buf, bufsiz));
}


/* Mapping for realpath */

extern char *
__openosc_realpath_chk (const char *buf, char *resolved, size_t resolvedlen);

char *
__openosc_realpath_to_buf (size_t dest_len, const char *path, char *resolved_path)
{
#undef realpath
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    size_t actlen;
    char *res = realpath(path, NULL);
    if (res == NULL) {
        return res;
    }

    actlen = strlen(res) + 1;
    if (actlen > dest_len) {
        if (openosc_log) {
            openosc_danger_error("realpath", dest_len, actlen);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            actlen = dest_len;
        }
    }

    memcpy(resolved_path, res, actlen);
    free(res);
    return resolved_path;
}


/* Mapping for recv */

ssize_t 
__openosc_recv_to_buf (size_t dest_len, int sockfd, void *buf, size_t len, int flags)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("recv", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef recv

    return (recv(sockfd, buf, len, flags));
}


/* Mapping for recvfrom */

ssize_t 
__openosc_recvfrom_to_buf (size_t dest_len, int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("recvfrom", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef recvfrom

    return (recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}


/* Mapping for stpcpy */

char *
__openosc_stpcpy_to_buf (size_t dest_len, char *dest, const char *src)
{
    size_t len = strlen(src);
    char *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
  
    if ((len + 1) > dest_len) {
        if (openosc_log) {
            openosc_danger_error("stpcpy", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len - 1;
        }
    }
#undef stpcpy
    rstr = strncpy(dest, src, len);
    *(rstr + len) = '\0';
    return (rstr + len);
}


/* Mapping for stpncpy */

char *
__openosc_stpncpy_to_buf (size_t dest_len, char *dest, const char *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("stpncpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef stpncpy

    return (stpncpy(dest, src, n));
}


/* Mapping for ttyname_r */

int 
__openosc_ttyname_r_to_buf (size_t dest_len, int fd, char *buf, size_t buflen)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (buflen > dest_len) {
        if (openosc_log) {
            openosc_danger_error("ttyname_r", dest_len, buflen);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            buflen = dest_len;
        }
    }
#undef ttyname_r

    return (ttyname_r(fd, buf, buflen));
}


#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for snprintf */

extern int
__openosc_vsnprintf_chk (char *s, size_t maxlen, int flags, size_t slen,
                  const char *format, va_list args);
extern int
__openosc_snprintf_chk (char *s, size_t maxlen, int flags, size_t slen,
                 const char *format, ...);

int 
__openosc_snprintf_to_buf (size_t dest_len, int additional_chk, char *str,
                   size_t size, const char *format, ...)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    va_list arg;
    int done;

    if (size > dest_len) {
        if (openosc_log) {
            openosc_danger_error("snprintf", dest_len, size);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            size = dest_len;
        }
    }
#undef snprintf

    va_start(arg, format);
    if (additional_chk) {
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        done = __vsnprintf_chk (str, size, 1, dest_len, format, arg);
#else
        done = vsnprintf(str, size, format, arg);
#endif
    } else {
        done = vsnprintf(str, size, format, arg);
    }
    va_end(arg);

    return done;
}


/* Mapping for vswprintf */

extern int
__openosc_vswprintf_chk (wchar_t *s, size_t maxlen, int flags, size_t slen,
                 const wchar_t *format, va_list args);

int 
__openosc_vswprintf_to_buf (size_t dest_len, int additional_chk, wchar_t *wcs,
                    size_t maxlen, const wchar_t *format, va_list args)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (maxlen > dest_len) {
        if (openosc_log) {
            openosc_danger_error("vswprintf", dest_len, maxlen);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            maxlen = dest_len;
        }
    }
#undef vswprintf

    if (additional_chk) {
#ifndef OPENOSC_NO_GLIBC_ADDITIONAL_CHK
        return (__vswprintf_chk(wcs, maxlen, 1, dest_len, format, args));
#else
        return (vswprintf(wcs, maxlen, format, args));
#endif
    } else {
        return (vswprintf(wcs, maxlen, format, args));
    }
}

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for wcpcpy */

wchar_t *
__openosc_wcpcpy_to_buf (size_t dest_len, wchar_t *dst, const wchar_t *src)
{
    size_t len = wcslen(src);
    wchar_t *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
  
    if ((len + 1) > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcpcpy", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len - 1;
        }
    }
#undef wcpcpy
    rstr = wcpncpy(dst, src, len);
    *rstr = L'\0';
    return (rstr);
}


/* Mapping for wcpncpy */

wchar_t *
__openosc_wcpncpy_to_buf (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcpncpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wcpncpy

    return (wcpncpy(dest, src, n));
}


/* Mapping for wcrtomb */

size_t 
__openosc_wcrtomb_to_buf (size_t dest_len, char *s, wchar_t wc, mbstate_t *ps)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (MB_CUR_MAX > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcrtomb", dest_len, MB_CUR_MAX);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        //if (openosc_truncate) {
            /* Well, we cannot do truncate here, so do nothing */
        //}
    }
#undef wcrtomb

    return (wcrtomb(s, wc, ps));
}


/* Mapping for wcscat */

wchar_t *
__openosc_wcscat_to_buf (size_t dest_len, wchar_t *dst, const wchar_t *src)
{
    size_t len = wcslen(src);
    size_t dst_len_to_null = wcslen(dst);
    wchar_t *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dest_len < (len + dst_len_to_null + 1)) {
        if (openosc_log) {
            openosc_danger_error("wcscat", dest_len, len);
        }
        if ((dst_len_to_null + 1) >= dest_len) {
            return (dst);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len - dst_len_to_null - 1;
        }
    }
#undef wcscat
    rstr = wcsncat(dst, src, len);
    return (rstr);
}


/* Mapping for wcscpy */

wchar_t *
__openosc_wcscpy_to_buf (size_t dest_len, wchar_t *dst, const wchar_t *src)
{
    size_t len = wcslen(src);
    wchar_t *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
  
    if ((len + 1) > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcscpy", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len - 1;
        }
    }
#undef wcscpy
    rstr = wcsncpy(dst, src, len);
    *(rstr + len) = L'\0';
    return (rstr);
}


/* Mapping for wcsncat */

wchar_t *
__openosc_wcsncat_to_buf (size_t dest_len, wchar_t *dst, const wchar_t *src, size_t len)
{
    size_t dst_len_to_null = wcslen(dst);
    wchar_t *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dest_len < (MIN(wcslen(src), len) + dst_len_to_null + 1)) {
        if (openosc_log) {
            openosc_danger_error("wcsncat", dest_len, len);
        }
        if ((dst_len_to_null + 1) >= dest_len) {
            return (dst);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len - dst_len_to_null - 1;
        }
    }
#undef wcsncat
    rstr = wcsncat(dst, src, len);
    return (rstr);
}


/* Mapping for wcsncpy */

wchar_t *
__openosc_wcsncpy_to_buf (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcsncpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wcsncpy

    return (wcsncpy(dest, src, n));
}


/* Mapping for wcsnrtombs */

size_t 
__openosc_wcsnrtombs_to_buf (size_t dest_len, char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcsnrtombs", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef wcsnrtombs

    return (wcsnrtombs(dest, src, nwc, len, ps));
}


/* Mapping for wcsrtombs */

size_t 
__openosc_wcsrtombs_to_buf (size_t dest_len, char *dest, const wchar_t **src, size_t len, mbstate_t *ps)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (len > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcsrtombs", dest_len, len);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            len = dest_len;
        }
    }
#undef wcsrtombs

    return (wcsrtombs(dest, src, len, ps));
}


/* Mapping for wcstombs */

size_t 
__openosc_wcstombs_to_buf (size_t dest_len, char *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wcstombs", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wcstombs

    return (wcstombs(dest, src, n));
}


/* Mapping for wctomb */

int 
__openosc_wctomb_to_buf (size_t dest_len, char *s, wchar_t wc)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (MB_CUR_MAX > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wctomb", dest_len, MB_CUR_MAX);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        //if (openosc_truncate) {
            /* Well, we cannot do truncate here, so do nothing */
        //}
    }
#undef wctomb

    return (wctomb(s, wc));
}


/* Mapping for wmemcpy */

wchar_t *
__openosc_wmemcpy_to_buf (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wmemcpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wmemcpy

    return (wmemcpy(dest, src, n));
}


/* Mapping for wmemmove */

wchar_t *
__openosc_wmemmove_to_buf (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wmemmove", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wmemmove

    return (wmemmove(dest, src, n));
}


/* Mapping for wmempcpy */

extern wchar_t *wmempcpy(wchar_t *dest, const wchar_t *src, size_t n);

wchar_t *
__openosc_wmempcpy_to_buf (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wmempcpy", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wmempcpy

    return (wmempcpy(dest, src, n));
}


/* Mapping for wmemset */

wchar_t *
__openosc_wmemset_to_buf (size_t dest_len, wchar_t *wcs, wchar_t wc, size_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (n > dest_len) {
        if (openosc_log) {
            openosc_danger_error("wmemset", dest_len, n);
        }
        openosc_get_config(&openosc_abort);
        if (openosc_abort) {
            abort();
        }
        if (openosc_truncate) {
            n = dest_len;
        }
    }
#undef wmemset

    return (wmemset(wcs, wc, n));
}


