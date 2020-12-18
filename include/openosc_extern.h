/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_EXTERN_H__
#define __OPENOSC_EXTERN_H__

/* import size_t definition only */
#define __need_size_t
#include <stddef.h>

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

/* libC APIs */
extern void *memcpy(void *dst, const void *src, size_t len) OSC_THROW;
extern void *memmove(void *dst, const void *src, size_t len) OSC_THROW;
extern void *memset(void *dst, int c, size_t len) OSC_THROW;
extern void bcopy(const void *src, void *dst, size_t len) OSC_THROW;
extern void bzero(void *dst, size_t len) OSC_THROW;
extern char *strcpy(char *dst, const char *src) OSC_THROW;
extern char *strncpy(char *dst, const char *src, size_t len) OSC_THROW;
extern char *strcat(char *dst, const char *src) OSC_THROW;
extern char *strncat(char *dst, const char *src, size_t len) OSC_THROW;
extern size_t strlen(const char *src) OSC_THROW;
extern size_t strnlen(const char *src, size_t maxlen) OSC_THROW;
extern int vsnprintf(char *str, size_t len, const char *fmt, va_list ap) OSC_THROW;

/* safeC APIs */
#ifdef HAS_SAFEC

/* Defining rsize_t type */
#ifndef rsize_t_type
#define rsize_t_type
typedef __typeof__ (sizeof 0) rsize_t;
#endif

#ifndef errno_t_type
#define errno_t_type
typedef int errno_t;
#endif

extern errno_t memcmp_s(const void *s1, rsize_t s1max,
			const void *s2, rsize_t n, int *diff);
extern errno_t memcpy_s(void *dest, rsize_t dmax,
                        const void * src, rsize_t n);
extern errno_t strcat_s(char *dest, rsize_t dmax, const char *src);
extern errno_t strcmp_s(const char *s1, rsize_t s1max, 
			const char *s2, int *indicator);
extern errno_t strcpy_s(char *dest, rsize_t dmax, const char *src);
extern errno_t strncat_s(char *dest, rsize_t dmax, 
			 const char *src, rsize_t n);
extern errno_t strncpy_s(char *dest, rsize_t dmax, 
			 const char *src, rsize_t n);
extern size_t strnlen_s(const char *s, size_t maxsize);
extern errno_t strstr_s(char *s1, rsize_t s1max, const char *s2,
			rsize_t s2max, char **substring);

#endif /* HAS_SAFEC */

#endif /* __OPENOSC_EXTERN_H__ */
