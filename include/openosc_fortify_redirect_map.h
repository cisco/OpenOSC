/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_REDIRECT_MAP_H__
#define __OPENOSC_FORTIFY_REDIRECT_MAP_H__

/* openosc_fortify_redirect_map.h and openosc_fortify_redirect_nomap.h are mutually exclusive */
#ifndef __OPENOSC_FORTIFY_REDIRECT_NOMAP_H__

#ifndef OPENOSC_USE_FORTIFY_LEVEL
#define OPENOSC_USE_FORTIFY_LEVEL 2
#endif

#ifndef OPENOSC_VALIST_NOSUPPORT

#ifdef __va_arg_pack

/* Mapping for asprintf */

extern int __asprintf_chk (char **result_ptr, int flags, const char *format, ...); 
extern int __REDIRECT_NTH (__openosc_asprintf_alias,
                              (char **result_ptr, const char *format, ...), asprintf);

__openosc_fortify_function int
__NTH (asprintf (char **result_ptr, const char *format, ...))
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (ASPRINTF_CASE4 __asprintf_chk(result_ptr, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (ASPRINTF_CASE4 __openosc_asprintf_alias(result_ptr, format, __va_arg_pack ()));
#endif
}


/* Mapping for dprintf */

extern int __dprintf_chk (int d, int flags, const char *format, ...); 
extern int __REDIRECT (__openosc_dprintf_alias,
                              (int d, const char *format, ...), dprintf);

__openosc_fortify_function int
dprintf (int d, const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (DPRINTF_CASE4 __dprintf_chk(d, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (DPRINTF_CASE4 __openosc_dprintf_alias(d, format, __va_arg_pack ()));
#endif
}


/* Mapping for fprintf */

extern int __fprintf_chk (FILE *fp, int flag, const char *format, ...); 
extern int __REDIRECT (__openosc_fprintf_alias,
                              (FILE *fp, const char *format, ...), fprintf);

__openosc_fortify_function int
fprintf (FILE *fp, const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (FPRINTF_CASE4 __fprintf_chk(fp, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (FPRINTF_CASE4 __openosc_fprintf_alias(fp, format, __va_arg_pack ()));
#endif
}


/* Mapping for fwprintf */

extern int __fwprintf_chk (FILE *fp, int flag, const wchar_t *format, ...); 
extern int __REDIRECT (__openosc_fwprintf_alias,
                              (FILE *fp, const wchar_t *format, ...), fwprintf);

__openosc_fortify_function int
fwprintf (FILE *fp, const wchar_t *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (FWPRINTF_CASE4 __fwprintf_chk(fp, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (FWPRINTF_CASE4 __openosc_fwprintf_alias(fp, format, __va_arg_pack ()));
#endif
}


/* Mapping for printf */

extern int __printf_chk (int flag, const char *format, ...); 
extern int __REDIRECT (__openosc_printf_alias,
                              (const char *format, ...), printf);

__openosc_fortify_function int
printf (const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (PRINTF_CASE4 __printf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (PRINTF_CASE4 __openosc_printf_alias(format, __va_arg_pack ()));
#endif
}


/* Mapping for snprintf */

extern int __snprintf_chk (char *s, size_t maxlen, int flags, size_t slen, const char *format, ...); 
extern int __openosc_snprintf_to_buf (size_t dest_len, int additional_chk, char *s, size_t maxlen, const char *format, ...); 
extern int __REDIRECT_NTH (__openosc_snprintf_alias,
                              (char *s, size_t maxlen, const char *format, ...), snprintf);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("snprintf"))
int
openosc_snprintf_chk_warn (size_t _sz, int additional_chk, char *s, size_t maxlen, const char *format, ...)
{
    return __openosc_snprintf_to_buf(_sz, additional_chk, s, maxlen, __va_arg_pack ());
}
#else
extern int __REDIRECT_NTH (openosc_snprintf_chk_warn,
                              (size_t dest_len, int additional_chk, char *s, size_t maxlen, const char *format, ...), __openosc_snprintf_to_buf)
       __warn_or_error_attr ("snprintf caller with bigger length than size of destination buffer");
#endif


__openosc_fortify_function int
__NTH (snprintf (char * __pass_objsize1 s, size_t maxlen, const char *format, ...))
__clang_warn_or_error_if(__size_too_small (__bos1, s, maxlen), __dst_overflow_msg("snprintf"))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(maxlen);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= maxlen)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (SNPRINTF_CASE1 __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
                  : (SNPRINTF_CASE2 openosc_snprintf_chk_warn(_sz, 1, s, maxlen, format, __va_arg_pack ())))
               : (SNPRINTF_CASE3 __openosc_snprintf_to_buf(_sz, 1, s, maxlen, format, __va_arg_pack ())))
            : (SNPRINTF_CASE4 __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
                  ? (SNPRINTF_CASE1 __openosc_snprintf_alias(s, maxlen, format, __va_arg_pack ()))
                  : (SNPRINTF_CASE2 openosc_snprintf_chk_warn(_sz, 0, s, maxlen, format, __va_arg_pack ())))
               : (SNPRINTF_CASE3 __openosc_snprintf_to_buf(_sz, 0, s, maxlen, format, __va_arg_pack ())))
            : (SNPRINTF_CASE4 __openosc_snprintf_alias(s, maxlen, format, __va_arg_pack ())));
#endif
}


/* Mapping for sprintf */

extern int __sprintf_chk (char *s, int flags, size_t slen, const char *format, ...); 
extern int __REDIRECT_NTH (__openosc_sprintf_alias,
                              (char *s, const char *format, ...), sprintf);


__openosc_fortify_function int
__NTH (sprintf (char * __pass_objsize0 s, const char *format, ...))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
           ? (SPRINTF_CASE3 __sprintf_chk(s, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
           : (SPRINTF_CASE4 __sprintf_chk(s, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
           ? (SPRINTF_CASE3 __openosc_sprintf_alias(s, format, __va_arg_pack ()))
           : (SPRINTF_CASE4 __openosc_sprintf_alias(s, format, __va_arg_pack ())));
#endif
}


/* Mapping for swprintf */

extern int __swprintf_chk (wchar_t *s, size_t n, int flag, size_t s_len, const wchar_t *format, ...); 
extern int __openosc_swprintf_to_buf (size_t dest_len, int additional_chk, wchar_t *s, size_t n, const wchar_t *format, ...); 
extern int __REDIRECT_NTH (__openosc_swprintf_alias,
                              (wchar_t *s, size_t n, const wchar_t *format, ...), swprintf);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("swprintf"))
int
openosc_swprintf_chk_warn (size_t _sz, int additional_chk, wchar_t *s, size_t maxlen, const wchar_t *format, ...)
{
    return __openosc_swprintf_to_buf(_sz, additional_chk, s, maxlen, __va_arg_pack ());
}
#else
extern int __REDIRECT_NTH (openosc_swprintf_chk_warn,
                              (size_t dest_len, int additional_chk, wchar_t *s, size_t n, const wchar_t *format, ...), __openosc_swprintf_to_buf)
       __warn_or_error_attr ("swprintf caller with bigger length than size of destination buffer");
#endif


__openosc_fortify_function int
__NTH (swprintf (wchar_t * __pass_objsize1 s, size_t n, const wchar_t *format, ...))
__clang_warn_or_error_if(__size_too_small (__bos1, s, n * sizeof(wchar_t)), __dst_overflow_msg("swprintf"))
{
    size_t _sz_bytes = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (SWPRINTF_CASE1 __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
                  : (SWPRINTF_CASE2 openosc_swprintf_chk_warn(_sz, 1, s, n, format, __va_arg_pack ())))
               : (SWPRINTF_CASE3 __openosc_swprintf_to_buf(_sz, 1, s, n, format, __va_arg_pack ())))
            : (SWPRINTF_CASE4 __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
                  ? (SWPRINTF_CASE1 __openosc_swprintf_alias(s, n, format, __va_arg_pack ()))
                  : (SWPRINTF_CASE2 openosc_swprintf_chk_warn(_sz, 0, s, n, format, __va_arg_pack ())))
               : (SWPRINTF_CASE3 __openosc_swprintf_to_buf(_sz, 0, s, n, format, __va_arg_pack ())))
            : (SWPRINTF_CASE4 __openosc_swprintf_alias(s, n, format, __va_arg_pack ())));
#endif
}


/* Mapping for wprintf */

extern int __wprintf_chk (int flag, const wchar_t *format, ...); 
extern int __REDIRECT (__openosc_wprintf_alias,
                              (const wchar_t *format, ...), wprintf);

__openosc_fortify_function int
wprintf (const wchar_t *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (WPRINTF_CASE4 __wprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (WPRINTF_CASE4 __openosc_wprintf_alias(format, __va_arg_pack ()));
#endif
}

#endif /* __va_arg_pack */

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for confstr */

extern size_t 
__openosc_confstr_to_buf(size_t dest_len, int name, char *buf, size_t len);
extern size_t  __REDIRECT_NTH (__openosc_confstr_alias,
                              (int name, char *buf, size_t len), confstr);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("confstr"))
size_t
openosc_confstr_chk_warn (size_t _sz, int name, char *buf, size_t len)
{
    return __openosc_confstr_to_buf(_sz, name, buf, len);
}
#else
extern size_t  __REDIRECT_NTH (openosc_confstr_chk_warn,
                              (size_t dest_len, int name, char *buf, size_t len), __openosc_confstr_to_buf)
       __warn_or_error_attr ("confstr caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (confstr (int name, char * __pass_objsize1 buf, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, buf, len), __dst_overflow_msg("confstr"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (CONFSTR_CASE1 __openosc_confstr_alias(name, buf, len))
                  : (CONFSTR_CASE2 openosc_confstr_chk_warn(_sz, name, buf, len)))
               : (CONFSTR_CASE3 __openosc_confstr_to_buf(_sz, name, buf, len)))
            : (CONFSTR_CASE4 __openosc_confstr_alias(name, buf, len)));
}


#ifndef OPENOSC_FGETS_DISABLE

/* Mapping for fgets */

extern char *
__fgets_chk (char *buf, size_t size, int n, FILE *fp);
extern char *
__openosc_fgets_to_buf(size_t dest_len, int additional_chk, char *s, int size, FILE *stream);
extern char * __REDIRECT (__openosc_fgets_alias,
                              (char *s, int size, FILE *stream), fgets);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fgets"))
char *
openosc_fgets_chk_warn (size_t _sz, int additional_chk, char *s, int size, FILE *stream)
{
    return __openosc_fgets_to_buf(_sz, additional_chk, s, size, stream);
}
#else
extern char * __REDIRECT (openosc_fgets_chk_warn,
                              (size_t dest_len, int additional_chk, char *s, int size, FILE *stream), __openosc_fgets_to_buf)
       __warn_or_error_attr ("fgets caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
fgets (char * __pass_objsize1 s, int size, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos1, s, size), __dst_overflow_msg("fgets"))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((size>0 && _sz >= (size_t)size)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETS_CASE1 __fgets_chk(s, _sz, size, stream))
                  : (FGETS_CASE2 openosc_fgets_chk_warn(_sz, 1, s, size, stream)))
               : (FGETS_CASE3 __openosc_fgets_to_buf(_sz, 1, s, size, stream)))
            : (FGETS_CASE4 __fgets_chk(s, _sz, size, stream)));
#else
                  ? (FGETS_CASE1 __openosc_fgets_alias(s, size, stream))
                  : (FGETS_CASE2 openosc_fgets_chk_warn(_sz, 0, s, size, stream)))
               : (FGETS_CASE3 __openosc_fgets_to_buf(_sz, 0, s, size, stream)))
            : (FGETS_CASE4 __openosc_fgets_alias(s, size, stream)));
#endif
}

#endif /* OPENOSC_FGETS_DISABLE */


/* Mapping for fgets_unlocked */

extern char *
__fgets_unlocked_chk (char *buf, size_t size, int n, FILE *fp);
extern char *
__openosc_fgets_unlocked_to_buf(size_t dest_len, int additional_chk, char *s, int n, FILE *stream);
extern char * __REDIRECT (__openosc_fgets_unlocked_alias,
                              (char *s, int n, FILE *stream), fgets_unlocked);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fgets_unlocked"))
char *
openosc_fgets_unlocked_chk_warn (size_t _sz, int additional_chk, char *s, int n, FILE *stream)
{
    return __openosc_fgets_unlocked_to_buf(_sz, additional_chk, s, n, stream);
}
#else
extern char * __REDIRECT (openosc_fgets_unlocked_chk_warn,
                              (size_t dest_len, int additional_chk, char *s, int n, FILE *stream), __openosc_fgets_unlocked_to_buf)
       __warn_or_error_attr ("fgets_unlocked caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
fgets_unlocked (char * __pass_objsize1 s, int n, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos1, s, n), __dst_overflow_msg("fgets_unlocked"))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETS_UNLOCKED_CASE1 __fgets_unlocked_chk(s, _sz, n, stream))
                  : (FGETS_UNLOCKED_CASE2 openosc_fgets_unlocked_chk_warn(_sz, 1, s, n, stream)))
               : (FGETS_UNLOCKED_CASE3 __openosc_fgets_unlocked_to_buf(_sz, 1, s, n, stream)))
            : (FGETS_UNLOCKED_CASE4 __fgets_unlocked_chk(s, _sz, n, stream)));
#else
                  ? (FGETS_UNLOCKED_CASE1 __openosc_fgets_unlocked_alias(s, n, stream))
                  : (FGETS_UNLOCKED_CASE2 openosc_fgets_unlocked_chk_warn(_sz, 0, s, n, stream)))
               : (FGETS_UNLOCKED_CASE3 __openosc_fgets_unlocked_to_buf(_sz, 0, s, n, stream)))
            : (FGETS_UNLOCKED_CASE4 __openosc_fgets_unlocked_alias(s, n, stream)));
#endif
}


/* Mapping for fgetws */

extern wchar_t *
__fgetws_chk (wchar_t *buf, size_t size, int n, FILE *fp);
extern wchar_t *
__openosc_fgetws_to_buf(size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream);
extern wchar_t * __REDIRECT (__openosc_fgetws_alias,
                              (wchar_t *ws, int n, FILE *stream), fgetws);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fgetws"))
wchar_t *
openosc_fgetws_chk_warn (size_t _sz, int additional_chk, wchar_t *ws, int n, FILE *stream)
{
    return __openosc_fgetws_to_buf(_sz, additional_chk, ws, n, stream);
}
#else
extern wchar_t * __REDIRECT (openosc_fgetws_chk_warn,
                              (size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream), __openosc_fgetws_to_buf)
       __warn_or_error_attr ("fgetws caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
fgetws (wchar_t * __pass_objsize1 ws, int n, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos1, ws, n * sizeof(wchar_t)), __dst_overflow_msg("fgetws"))
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETWS_CASE1 __fgetws_chk(ws, _sz, n, stream))
                  : (FGETWS_CASE2 openosc_fgetws_chk_warn(_sz, 1, ws, n, stream)))
               : (FGETWS_CASE3 __openosc_fgetws_to_buf(_sz, 1, ws, n, stream)))
            : (FGETWS_CASE4 __fgetws_chk(ws, _sz, n, stream)));
#else
                  ? (FGETWS_CASE1 __openosc_fgetws_alias(ws, n, stream))
                  : (FGETWS_CASE2 openosc_fgetws_chk_warn(_sz, 0, ws, n, stream)))
               : (FGETWS_CASE3 __openosc_fgetws_to_buf(_sz, 0, ws, n, stream)))
            : (FGETWS_CASE4 __openosc_fgetws_alias(ws, n, stream)));
#endif
}


/* Mapping for fgetws_unlocked */

extern wchar_t *
__fgetws_unlocked_chk (wchar_t *buf, size_t size, int n, FILE *fp);
extern wchar_t *
__openosc_fgetws_unlocked_to_buf(size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream);
extern wchar_t * __REDIRECT (__openosc_fgetws_unlocked_alias,
                              (wchar_t *ws, int n, FILE *stream), fgetws_unlocked);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fgetws_unlocked"))
wchar_t *
openosc_fgetws_unlocked_chk_warn (size_t _sz, int additional_chk, wchar_t *ws, int n, FILE *stream)
{
    return __openosc_fgetws_unlocked_to_buf(_sz, additional_chk, ws, n, stream);
}
#else
extern wchar_t * __REDIRECT (openosc_fgetws_unlocked_chk_warn,
                              (size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream), __openosc_fgetws_unlocked_to_buf)
       __warn_or_error_attr ("fgetws_unlocked caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
fgetws_unlocked (wchar_t * __pass_objsize1 ws, int n, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos1, ws, n * sizeof(wchar_t)), __dst_overflow_msg("fgetws_unlocked"))
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETWS_UNLOCKED_CASE1 __fgetws_unlocked_chk(ws, _sz, n, stream))
                  : (FGETWS_UNLOCKED_CASE2 openosc_fgetws_unlocked_chk_warn(_sz, 1, ws, n, stream)))
               : (FGETWS_UNLOCKED_CASE3 __openosc_fgetws_unlocked_to_buf(_sz, 1, ws, n, stream)))
            : (FGETWS_UNLOCKED_CASE4 __fgetws_unlocked_chk(ws, _sz, n, stream)));
#else
                  ? (FGETWS_UNLOCKED_CASE1 __openosc_fgetws_unlocked_alias(ws, n, stream))
                  : (FGETWS_UNLOCKED_CASE2 openosc_fgetws_unlocked_chk_warn(_sz, 0, ws, n, stream)))
               : (FGETWS_UNLOCKED_CASE3 __openosc_fgetws_unlocked_to_buf(_sz, 0, ws, n, stream)))
            : (FGETWS_UNLOCKED_CASE4 __openosc_fgetws_unlocked_alias(ws, n, stream)));
#endif
}


/* Mapping for fread */

extern size_t
__fread_chk (void *__restrict ptr, size_t ptrlen,
             size_t size, size_t n, FILE *__restrict stream);
extern size_t 
__openosc_fread_to_buf(size_t dest_len, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream);
extern size_t  __REDIRECT (__openosc_fread_alias,
                              (void *ptr, size_t size, size_t nmemb, FILE *stream), fread);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fread"))
size_t
openosc_fread_chk_warn (size_t _sz, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return __openosc_fread_to_buf(_sz, additional_chk, ptr, size, nmemb, stream);
}
#else
extern size_t  __REDIRECT (openosc_fread_chk_warn,
                              (size_t dest_len, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream), __openosc_fread_to_buf)
       __warn_or_error_attr ("fread caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
fread (void * __pass_objsize0 ptr, size_t size, size_t nmemb, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos0, ptr, size * nmemb), __dst_overflow_msg("fread"))
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nmemb);
    int is_size_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && is_size_constant
               ? ((_sz >= size * nmemb)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FREAD_CASE1 __fread_chk(ptr, _sz, size, nmemb, stream))
                  : (FREAD_CASE2 openosc_fread_chk_warn(_sz, 1, ptr, size, nmemb, stream)))
               : (FREAD_CASE3 __openosc_fread_to_buf(_sz, 1, ptr, size, nmemb, stream)))
            : (FREAD_CASE4 __fread_chk(ptr, _sz, size, nmemb, stream)));
#else
                  ? (FREAD_CASE1 __openosc_fread_alias(ptr, size, nmemb, stream))
                  : (FREAD_CASE2 openosc_fread_chk_warn(_sz, 0, ptr, size, nmemb, stream)))
               : (FREAD_CASE3 __openosc_fread_to_buf(_sz, 0, ptr, size, nmemb, stream)))
            : (FREAD_CASE4 __openosc_fread_alias(ptr, size, nmemb, stream)));
#endif
}


#ifndef fread_unlocked

/* Mapping for fread_unlocked */

extern size_t
__fread_unlocked_chk (void *__restrict ptr, size_t ptrlen,
                      size_t size, size_t n, FILE *__restrict stream);
extern size_t 
__openosc_fread_unlocked_to_buf(size_t dest_len, int additional_chk, void *ptr, size_t size, size_t n, FILE *stream);
extern size_t  __REDIRECT (__openosc_fread_unlocked_alias,
                              (void *ptr, size_t size, size_t n, FILE *stream), fread_unlocked);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("fread_unlocked"))
size_t
openosc_fread_unlocked_chk_warn (size_t _sz, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return __openosc_fread_unlocked_to_buf(_sz, additional_chk, ptr, size, nmemb, stream);
}
#else
extern size_t  __REDIRECT (openosc_fread_unlocked_chk_warn,
                              (size_t dest_len, int additional_chk, void *ptr, size_t size, size_t n, FILE *stream), __openosc_fread_unlocked_to_buf)
       __warn_or_error_attr ("fread_unlocked caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
fread_unlocked (void * __pass_objsize0 ptr, size_t size, size_t n, FILE *stream)
__clang_warn_or_error_if(__size_too_small (__bos0, ptr, size * n), __dst_overflow_msg("fread_unlocked"))
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(n);
    int is_size_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && is_size_constant
               ? ((_sz >= n * size)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FREAD_UNLOCKED_CASE1 __fread_unlocked_chk(ptr, _sz, size, n, stream))
                  : (FREAD_UNLOCKED_CASE2 openosc_fread_unlocked_chk_warn(_sz, 1, ptr, size, n, stream)))
               : (FREAD_UNLOCKED_CASE3 __openosc_fread_unlocked_to_buf(_sz, 1, ptr, size, n, stream)))
            : (FREAD_UNLOCKED_CASE4 _fread_unlocked_chk(ptr, _sz, size, n, stream)));
#else
                  ? (FREAD_UNLOCKED_CASE1 __openosc_fread_unlocked_alias(ptr, size, n, stream))
                  : (FREAD_UNLOCKED_CASE2 openosc_fread_unlocked_chk_warn(_sz, 0, ptr, size, n, stream)))
               : (FREAD_UNLOCKED_CASE3 __openosc_fread_unlocked_to_buf(_sz, 0, ptr, size, n, stream)))
            : (FREAD_UNLOCKED_CASE4 __openosc_fread_unlocked_alias(ptr, size, n, stream)));
#endif
}

#endif /* fread_unlocked */


#ifndef OPENOSC_GETCWD_DISABLE

/* Mapping for getcwd */

extern char *
__openosc_getcwd_to_buf(size_t dest_len, char *buf, size_t size);
extern char * __REDIRECT_NTH (__openosc_getcwd_alias,
                              (char *buf, size_t size), getcwd);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("getcwd"))
char *
openosc_getcwd_chk_warn (size_t _sz, char *buf, size_t size)
{
    return __openosc_getcwd_to_buf(_sz, buf, size);
}
#else
extern char * __REDIRECT_NTH (openosc_getcwd_chk_warn,
                              (size_t dest_len, char *buf, size_t size), __openosc_getcwd_to_buf)
       __warn_or_error_attr ("getcwd caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
__NTH (getcwd (char * __pass_objsize1 buf, size_t size))
__clang_warn_or_error_if(__size_too_small (__bos1, buf, size), __dst_overflow_msg("get_cwd"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= size)
                  ? (GETCWD_CASE1 __openosc_getcwd_alias(buf, size))
                  : (GETCWD_CASE2 openosc_getcwd_chk_warn(_sz, buf, size)))
               : (GETCWD_CASE3 __openosc_getcwd_to_buf(_sz, buf, size)))
            : (GETCWD_CASE4 __openosc_getcwd_alias(buf, size)));
}

#endif /* OPENOSC_GETCWD_DISABLE */


/* Mapping for getdomainname */

extern int 
__openosc_getdomainname_to_buf(size_t dest_len, char *name, size_t len);
extern int  __REDIRECT_NTH (__openosc_getdomainname_alias,
                              (char *name, size_t len), getdomainname);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("getdomainname"))
int
openosc_getdomainname_chk_warn (size_t _sz, char *name, size_t len)
{
    return __openosc_getdomainname_to_buf(_sz, name, len);
}
#else
extern int  __REDIRECT_NTH (openosc_getdomainname_chk_warn,
                              (size_t dest_len, char *name, size_t len), __openosc_getdomainname_to_buf)
       __warn_or_error_attr ("getdomainname caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
__NTH (getdomainname (char * __pass_objsize1 name, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, name, len), __dst_overflow_msg("getdomainname"))
{
    size_t _sz = __builtin_object_size(name, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (GETDOMAINNAME_CASE1 __openosc_getdomainname_alias(name, len))
                  : (GETDOMAINNAME_CASE2 openosc_getdomainname_chk_warn(_sz, name, len)))
               : (GETDOMAINNAME_CASE3 __openosc_getdomainname_to_buf(_sz, name, len)))
            : (GETDOMAINNAME_CASE4 __openosc_getdomainname_alias(name, len)));
}


/* Mapping for getgroups */

extern int 
__openosc_getgroups_to_buf(size_t dest_len, int size, gid_t list[]);
extern int  __REDIRECT_NTH (__openosc_getgroups_alias,
                              (int size, gid_t list[]), getgroups);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("getgroups"))
int
openosc_getgroups_chk_warn (size_t _sz, int size, gid_t list[])
{
    return __openosc_getgroups_to_buf(_sz, size, list);
}
#else
extern int  __REDIRECT_NTH (openosc_getgroups_chk_warn,
                              (size_t dest_len, int size, gid_t list[]), __openosc_getgroups_to_buf)
       __warn_or_error_attr ("getgroups caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
__NTH (getgroups (int size, gid_t * __pass_objsize0 list))
__clang_warn_or_error_if(__size_too_small (__bos1, list, size * sizeof(gid_t)), __dst_overflow_msg("getgroups"))
{
    size_t _sz = __builtin_object_size(list, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? (((int)(_sz/sizeof(gid_t)) >= size || size == 0)  /* size can be 0, which is valid */
                  ? (GETGROUPS_CASE1 __openosc_getgroups_alias(size, list))
                  : (GETGROUPS_CASE2 openosc_getgroups_chk_warn(_sz/sizeof(gid_t), size, list)))
               : (GETGROUPS_CASE3 __openosc_getgroups_to_buf(_sz/sizeof(gid_t), size, list)))
            : (GETGROUPS_CASE4 __openosc_getgroups_alias(size, list)));
}


/* Mapping for gethostname */

extern int 
__openosc_gethostname_to_buf(size_t dest_len, char *name, size_t len);
extern int  __REDIRECT_NTH (__openosc_gethostname_alias,
                              (char *name, size_t len), gethostname);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("gethostname"))
int
openosc_gethostname_chk_warn (size_t _sz, char *name, size_t len)
{
    return __openosc_gethostname_to_buf(_sz, name, len);
}
#else
extern int  __REDIRECT_NTH (openosc_gethostname_chk_warn,
                              (size_t dest_len, char *name, size_t len), __openosc_gethostname_to_buf)
       __warn_or_error_attr ("gethostname caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
__NTH (gethostname (char * __pass_objsize1 name, size_t len))
__clang_warn_or_error_if(__size_too_small (__bos1, name, len), __dst_overflow_msg("gethostname"))
{
    size_t _sz = __builtin_object_size(name, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (GETHOSTNAME_CASE1 __openosc_gethostname_alias(name, len))
                  : (GETHOSTNAME_CASE2 openosc_gethostname_chk_warn(_sz, name, len)))
               : (GETHOSTNAME_CASE3 __openosc_gethostname_to_buf(_sz, name, len)))
            : (GETHOSTNAME_CASE4 __openosc_gethostname_alias(name, len)));
}


#ifndef OPENOSC_GETS_DISABLE

/* Mapping for gets */

extern char *
__gets_chk (char *buf, size_t size);
extern char * __REDIRECT (__openosc_gets_alias,
                              (char *s), gets);

__openosc_fortify_function char *
gets (char * __pass_objsize1 s)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
            ? (GETS_CASE3 __gets_chk(s, _sz))
            : (GETS_CASE4 __gets_chk(s, _sz)));
#else
            ? (GETS_CASE3 __openosc_gets_alias(s))
            : (GETS_CASE4 __openosc_gets_alias(s)));
#endif
}

#endif /* OPENOSC_GETS_DISABLE */


/* Mapping for getwd */

extern char *
__openosc_getwd_to_buf(size_t dest_len, char *buf);
extern char * __REDIRECT_NTH (__openosc_getwd_alias,
                              (char *buf), getwd);
extern char * __REDIRECT_NTH (openosc_getwd_chk_warn,
                              (size_t dest_len, char *buf), __openosc_getwd_to_buf)
       __warn_or_error_attr ("getwd caller with bigger length than size of destination buffer");

__openosc_fortify_function char *
__NTH (getwd (char * __pass_objsize1 buf))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (GETWD_CASE3 __openosc_getwd_to_buf(_sz, buf))
            : (GETWD_CASE4 __openosc_getwd_alias(buf)));
}


/* Mapping for mbsnrtowcs */

extern size_t 
__openosc_mbsnrtowcs_to_buf(size_t dest_len, wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps);
extern size_t  __REDIRECT_NTH (__openosc_mbsnrtowcs_alias,
                              (wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps), mbsnrtowcs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("mbsnrtowcs"))
size_t
openosc_mbsnrtowcs_chk_warn (size_t _sz, wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps)
{
    return __openosc_mbsnrtowcs_to_buf(_sz, dest, src, nms, len, ps);
}
#else
extern size_t  __REDIRECT_NTH (openosc_mbsnrtowcs_chk_warn,
                              (size_t dest_len, wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps), __openosc_mbsnrtowcs_to_buf)
       __warn_or_error_attr ("mbsnrtowcs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (mbsnrtowcs (wchar_t * __pass_objsize1 dest, const char **src, size_t nms, size_t len, mbstate_t *ps))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, len * sizeof(wchar_t)), __dst_overflow_msg("mbsnrtowcs"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MBSNRTOWCS_CASE1 __openosc_mbsnrtowcs_alias(dest, src, nms, len, ps))
                  : (MBSNRTOWCS_CASE2 openosc_mbsnrtowcs_chk_warn(_sz, dest, src, nms, len, ps)))
               : (MBSNRTOWCS_CASE3 __openosc_mbsnrtowcs_to_buf(_sz, dest, src, nms, len, ps)))
            : (MBSNRTOWCS_CASE4 __openosc_mbsnrtowcs_alias(dest, src, nms, len, ps)));
}


/* Mapping for mbsrtowcs */

extern size_t 
__openosc_mbsrtowcs_to_buf(size_t dest_len, wchar_t *dest, const char **src, size_t len, mbstate_t *ps);
extern size_t  __REDIRECT_NTH (__openosc_mbsrtowcs_alias,
                              (wchar_t *dest, const char **src, size_t len, mbstate_t *ps), mbsrtowcs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("mbsrtowcs"))
size_t
openosc_mbsrtowcs_chk_warn (size_t _sz, wchar_t *dest, const char **src, size_t len, mbstate_t *ps)
{
    return __openosc_mbsrtowcs_to_buf(_sz, dest, src, len, ps);
}
#else
extern size_t  __REDIRECT_NTH (openosc_mbsrtowcs_chk_warn,
                              (size_t dest_len, wchar_t *dest, const char **src, size_t len, mbstate_t *ps), __openosc_mbsrtowcs_to_buf)
       __warn_or_error_attr ("mbsrtowcs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (mbsrtowcs (wchar_t * __pass_objsize1 dest, const char **src, size_t len, mbstate_t *ps))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, len * sizeof(wchar_t)), __dst_overflow_msg("mbsrtowcs"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (MBSRTOWCS_CASE1 __openosc_mbsrtowcs_alias(dest, src, len, ps))
                  : (MBSRTOWCS_CASE2 openosc_mbsrtowcs_chk_warn(_sz, dest, src, len, ps)))
               : (MBSRTOWCS_CASE3 __openosc_mbsrtowcs_to_buf(_sz, dest, src, len, ps)))
            : (MBSRTOWCS_CASE4 __openosc_mbsrtowcs_alias(dest, src, len, ps)));
}


/* Mapping for mbstowcs */

extern size_t 
__openosc_mbstowcs_to_buf(size_t dest_len, wchar_t *dest, const char *src, size_t n);
extern size_t  __REDIRECT_NTH (__openosc_mbstowcs_alias,
                              (wchar_t *dest, const char *src, size_t n), mbstowcs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("mbstowcs"))
size_t
openosc_mbstowcs_chk_warn (size_t _sz, wchar_t *dest, const char *src, size_t n)
{
    return __openosc_mbstowcs_to_buf(_sz, dest, src, n);
}
#else
extern size_t  __REDIRECT_NTH (openosc_mbstowcs_chk_warn,
                              (size_t dest_len, wchar_t *dest, const char *src, size_t n), __openosc_mbstowcs_to_buf)
       __warn_or_error_attr ("mbstowcs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (mbstowcs (wchar_t * __pass_objsize1 dest, const char *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n * sizeof(wchar_t)), __dst_overflow_msg("mbstowcs"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (MBSTOWCS_CASE1 __openosc_mbstowcs_alias(dest, src, n))
                  : (MBSTOWCS_CASE2 openosc_mbstowcs_chk_warn(_sz, dest, src, n)))
               : (MBSTOWCS_CASE3 __openosc_mbstowcs_to_buf(_sz, dest, src, n)))
            : (MBSTOWCS_CASE4 __openosc_mbstowcs_alias(dest, src, n)));
}


/* Mapping for mempcpy */

extern void *
__openosc_mempcpy_to_buf(size_t dest_len, void *dest, const void *src, size_t n);
extern void * __REDIRECT_NTH (__openosc_mempcpy_alias,
                              (void *dest, const void *src, size_t n), mempcpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("mempcpy"))
void *
openosc_mempcpy_chk_warn (size_t _sz, void *dest, const void *src, size_t n)
{
    return __openosc_mempcpy_to_buf(_sz, dest, src, n);
}
#else
extern void * __REDIRECT_NTH (openosc_mempcpy_chk_warn,
                              (size_t dest_len, void *dest, const void *src, size_t n), __openosc_mempcpy_to_buf)
       __warn_or_error_attr ("mempcpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function void *
__NTH (mempcpy (void * __pass_objsize0 dest, const void *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos0, dest, n), __dst_overflow_msg("mempcpy"))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (MEMPCPY_CASE1 __openosc_mempcpy_alias(dest, src, n))
                  : (MEMPCPY_CASE2 openosc_mempcpy_chk_warn(_sz, dest, src, n)))
               : (MEMPCPY_CASE3 __openosc_mempcpy_to_buf(_sz, dest, src, n)))
            : (MEMPCPY_CASE4 __openosc_mempcpy_alias(dest, src, n)));
}


#ifndef OPENOSC_POLL_DISABLE

/* Mapping for poll */

extern int 
__openosc_poll_to_buf(size_t dest_len, struct pollfd *fds, nfds_t nfds, int timeout);
extern int  __REDIRECT (__openosc_poll_alias,
                          (struct pollfd *fds, nfds_t nfds, int timeout), poll);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("poll"))
int
openosc_poll_chk_warn (size_t _sz, struct pollfd *fds, nfds_t nfds, int timeout)
{
    return __openosc_poll_to_buf(_sz, fds, nfds, timeout);
}
#else
extern int  __REDIRECT (openosc_poll_chk_warn,
                          (size_t dest_len, struct pollfd *fds, nfds_t nfds, int timeout), __openosc_poll_to_buf)
       __warn_or_error_attr ("poll caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
poll (struct pollfd * __pass_objsize0 fds, nfds_t nfds, int timeout)
__clang_warn_or_error_if(__size_too_small (__bos0, fds, nfds * (sizeof(int) + sizeof(short) + sizeof(short))), __dst_overflow_msg("poll"))
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (POLL_CASE1 __openosc_poll_alias(fds, nfds, timeout))
                  : (POLL_CASE2 openosc_poll_chk_warn(_sz, fds, nfds, timeout)))
               : (POLL_CASE3 __openosc_poll_to_buf(_sz, fds, nfds, timeout)))
            : (POLL_CASE4 __openosc_poll_alias(fds, nfds, timeout)));
}

#endif /* OPENOSC_POLL_DISABLE */


#ifndef OPENOSC_PPOLL_DISABLE

/* Mapping for ppoll */

extern int 
__openosc_ppoll_to_buf(size_t dest_len, struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask);
extern int  __REDIRECT (__openosc_ppoll_alias,
                          (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask), ppoll);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("ppoll"))
int
openosc_ppoll_chk_warn (size_t _sz, struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    return __openosc_ppoll_to_buf(_sz, fds, nfds, timeout_ts, sigmask);
}
#else
extern int  __REDIRECT (openosc_ppoll_chk_warn,
                          (size_t dest_len, struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask), __openosc_ppoll_to_buf)
       __warn_or_error_attr ("ppoll caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
ppoll (struct pollfd * __pass_objsize0 fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
__clang_warn_or_error_if(__size_too_small (__bos0, fds, nfds * (sizeof(int) + sizeof(short) + sizeof(short))), __dst_overflow_msg("ppoll"))
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (PPOLL_CASE1 __openosc_ppoll_alias(fds, nfds, timeout_ts, sigmask))
                  : (PPOLL_CASE2 openosc_ppoll_chk_warn(_sz, fds, nfds, timeout_ts, sigmask)))
               : (PPOLL_CASE3 __openosc_ppoll_to_buf(_sz, fds, nfds, timeout_ts, sigmask)))
            : (PPOLL_CASE4 __openosc_ppoll_alias(fds, nfds, timeout_ts, sigmask)));
}

#endif /* OPENOSC_PPOLL_DISABLE */


#ifndef OPENOSC_PREAD_DISABLE

/* Mapping for pread */

extern ssize_t 
__openosc_pread_to_buf(size_t dest_len, int fd, void *buf, size_t count, off_t offset);
extern ssize_t  __REDIRECT (__openosc_pread_alias,
                              (int fd, void *buf, size_t count, off_t offset), pread);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("pread"))
size_t
openosc_pread_chk_warn (size_t _sz, int fd, void *buf, size_t count, off_t offset)
{
    return __openosc_pread_to_buf(_sz, fd, buf, count, offset);
}
#else
extern ssize_t  __REDIRECT (openosc_pread_chk_warn,
                              (size_t dest_len, int fd, void *buf, size_t count, off_t offset), __openosc_pread_to_buf)
       __warn_or_error_attr ("pread caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t 
pread (int fd, void * __pass_objsize0 buf, size_t count, off_t offset)
__clang_warn_or_error_if(__size_too_small (__bos0, buf, count), __dst_overflow_msg("pread"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (PREAD_CASE1 __openosc_pread_alias(fd, buf, count, offset))
                  : (PREAD_CASE2 openosc_pread_chk_warn(_sz, fd, buf, count, offset)))
               : (PREAD_CASE3 __openosc_pread_to_buf(_sz, fd, buf, count, offset)))
            : (PREAD_CASE4 __openosc_pread_alias(fd, buf, count, offset)));
}

#endif /* OPENOSC_PREAD_DISABLE */


#ifndef OPENOSC_READ_DISABLE

/* Mapping for read */

extern ssize_t 
__openosc_read_to_buf(size_t dest_len, int fd, void *buf, size_t count);
extern ssize_t  __REDIRECT (__openosc_read_alias,
                              (int fd, void *buf, size_t count), read);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("read"))
size_t
openosc_read_chk_warn (size_t _sz, int fd, void *buf, size_t count)
{
    return __openosc_read_to_buf(_sz, fd, buf, count);
}
#else
extern ssize_t  __REDIRECT (openosc_read_chk_warn,
                              (size_t dest_len, int fd, void *buf, size_t count), __openosc_read_to_buf)
       __warn_or_error_attr ("read caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t 
read (int fd, void * __pass_objsize0 buf, size_t count)
__clang_warn_or_error_if(__size_too_small (__bos0, buf, count), __dst_overflow_msg("read"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (READ_CASE1 __openosc_read_alias(fd, buf, count))
                  : (READ_CASE2 openosc_read_chk_warn(_sz, fd, buf, count)))
               : (READ_CASE3 __openosc_read_to_buf(_sz, fd, buf, count)))
            : (READ_CASE4 __openosc_read_alias(fd, buf, count)));
}

#endif /* OPENOSC_READ_DISABLE */


/* Mapping for readlinkat */

extern int 
__openosc_readlinkat_to_buf(size_t dest_len, int dirfd, const char *pathname, char *buf, size_t bufsiz);
extern ssize_t  __REDIRECT_NTH (__openosc_readlinkat_alias,
                              (int dirfd, const char *pathname, char *buf, size_t bufsiz), readlinkat);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("readlinkat"))
ssize_t
openosc_readlinkat_chk_warn (size_t _sz, int dirfd, const char *pathname, char *buf, size_t bufsiz)
{
    return __openosc_readlinkat_to_buf(_sz, dirfd, pathname, buf, bufsiz);
}
#else
extern ssize_t  __REDIRECT_NTH (openosc_readlinkat_chk_warn,
                              (size_t dest_len, int dirfd, const char *pathname, char *buf, size_t bufsiz), __openosc_readlinkat_to_buf)
       __warn_or_error_attr ("readlinkat caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t
__NTH (readlinkat (int dirfd, const char *pathname, char * __pass_objsize1 buf, size_t bufsiz))
__clang_warn_or_error_if(__size_too_small (__bos1, buf, bufsiz), __dst_overflow_msg("readlinkat"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(bufsiz);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= bufsiz)
                  ? (READLINKAT_CASE1 __openosc_readlinkat_alias(dirfd, pathname, buf, bufsiz))
                  : (READLINKAT_CASE2 openosc_readlinkat_chk_warn(_sz, dirfd, pathname, buf, bufsiz)))
               : (READLINKAT_CASE3 __openosc_readlinkat_to_buf(_sz, dirfd, pathname, buf, bufsiz)))
            : (READLINKAT_CASE4 __openosc_readlinkat_alias(dirfd, pathname, buf, bufsiz)));
}


/* Mapping for readlink */

extern ssize_t 
__openosc_readlink_to_buf(size_t dest_len, const char *path, char *buf, size_t bufsiz);
extern ssize_t  __REDIRECT_NTH (__openosc_readlink_alias,
                              (const char *path, char *buf, size_t bufsiz), readlink);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("readlink"))
ssize_t
openosc_readlink_chk_warn (size_t _sz, const char *path, char *buf, size_t bufsiz)
{
    return __openosc_readlink_to_buf(_sz, path, buf, bufsiz);
}
#else
extern ssize_t  __REDIRECT_NTH (openosc_readlink_chk_warn,
                              (size_t dest_len, const char *path, char *buf, size_t bufsiz), __openosc_readlink_to_buf)
       __warn_or_error_attr ("readlink caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t 
__NTH (readlink (const char *path, char * __pass_objsize1 buf, size_t bufsiz))
__clang_warn_or_error_if(__size_too_small (__bos1, buf, bufsiz), __dst_overflow_msg("readlink"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(bufsiz);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= bufsiz)
                  ? (READLINK_CASE1 __openosc_readlink_alias(path, buf, bufsiz))
                  : (READLINK_CASE2 openosc_readlink_chk_warn(_sz, path, buf, bufsiz)))
               : (READLINK_CASE3 __openosc_readlink_to_buf(_sz, path, buf, bufsiz)))
            : (READLINK_CASE4 __openosc_readlink_alias(path, buf, bufsiz)));
}


/* Mapping for realpath */

extern char *
__openosc_realpath_to_buf(size_t dest_len, const char *path, char *resolved_path);
extern char * __REDIRECT_NTH (__openosc_realpath_alias,
                              (const char *path, char *resolved_path), realpath);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("realpath"))
char *
openosc_realpath_chk_warn (size_t _sz, const char *path, char *resolved_path)
{
    return __openosc_realpath_to_buf(_sz, path, resolved_path);
}
#else
extern char * __REDIRECT_NTH (openosc_realpath_chk_warn,
                              (size_t dest_len, const char *path, char *resolved_path), __openosc_realpath_to_buf)
       __warn_or_error_attr ("realpath caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
__NTH (realpath (const char *path, char * __pass_objsize1 resolved_path))
{
    size_t _sz = __builtin_object_size(resolved_path, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (REALPATH_CASE3 __openosc_realpath_to_buf(_sz, path, resolved_path))
            : (REALPATH_CASE4 __openosc_realpath_alias(path, resolved_path)));
}


#ifndef OPENOSC_RECV_DISABLE

/* Mapping for recv */

extern ssize_t 
__openosc_recv_to_buf(size_t dest_len, int sockfd, void *buf, size_t len, int flags);
extern ssize_t  __REDIRECT (__openosc_recv_alias,
                              (int sockfd, void *buf, size_t len, int flags), recv);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("recv"))
ssize_t
openosc_recv_chk_warn (size_t _sz, int sockfd, void *buf, size_t len, int flags)
{
    return __openosc_recv_to_buf(_sz, sockfd, buf, len, flags);
}
#else
extern ssize_t  __REDIRECT (openosc_recv_chk_warn,
                              (size_t dest_len, int sockfd, void *buf, size_t len, int flags), __openosc_recv_to_buf)
       __warn_or_error_attr ("recv caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t 
recv (int sockfd, void * __pass_objsize0 buf, size_t len, int flags)
__clang_warn_or_error_if(__size_too_small (__bos0, buf, len), __dst_overflow_msg("recv"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECV_CASE1 __openosc_recv_alias(sockfd, buf, len, flags))
                  : (RECV_CASE2 openosc_recv_chk_warn(_sz, sockfd, buf, len, flags)))
               : (RECV_CASE3 __openosc_recv_to_buf(_sz, sockfd, buf, len, flags)))
            : (RECV_CASE4 __openosc_recv_alias(sockfd, buf, len, flags)));
}

#endif /* OPENOSC_RECV_DISABLE */


#ifndef OPENOSC_RECVFROM_DISABLE

/* Mapping for recvfrom */

extern ssize_t 
__openosc_recvfrom_to_buf(size_t dest_len, int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
extern ssize_t  __REDIRECT (__openosc_recvfrom_alias,
                              (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen), recvfrom);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("recvfrom"))
ssize_t
openosc_recvfrom_chk_warn (size_t _sz, int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    return __openosc_recvfrom_to_buf(_sz, sockfd, buf, len, flags, src_addr, addrlen);
}
#else
extern ssize_t  __REDIRECT (openosc_recvfrom_chk_warn,
                              (size_t dest_len, int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen), __openosc_recvfrom_to_buf)
       __warn_or_error_attr ("recvfrom caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function ssize_t 
recvfrom (int sockfd, void * __pass_objsize0 buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
__clang_warn_or_error_if(__size_too_small (__bos0, buf, len), __dst_overflow_msg("recvfrom"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECVFROM_CASE1 __openosc_recvfrom_alias(sockfd, buf, len, flags, src_addr, addrlen))
                  : (RECVFROM_CASE2 openosc_recvfrom_chk_warn(_sz, sockfd, buf, len, flags, src_addr, addrlen)))
               : (RECVFROM_CASE3 __openosc_recvfrom_to_buf(_sz, sockfd, buf, len, flags, src_addr, addrlen)))
            : (RECVFROM_CASE4 __openosc_recvfrom_alias(sockfd, buf, len, flags, src_addr, addrlen)));
}

#endif /* OPENOSC_RECVFROM_DISABLE */


/* Mapping for stpcpy */

extern char *
__openosc_stpcpy_to_buf(size_t dest_len, char *dest, const char *src);
extern char * __REDIRECT_NTH (__openosc_stpcpy_alias,
                              (char *dest, const char *src), stpcpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("stpcpy"))
char *
openosc_stpcpy_chk_warn (size_t _sz, char *dest, const char *src)
{
    return __openosc_stpcpy_to_buf(_sz, dest, src);
}
#else
extern char * __REDIRECT_NTH (openosc_stpcpy_chk_warn,
                              (size_t dest_len, char *dest, const char *src), __openosc_stpcpy_to_buf)
       __warn_or_error_attr ("stpcpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
__NTH (stpcpy (char * __pass_objsize1 dest, const char *src))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (STPCPY_CASE3 __openosc_stpcpy_to_buf(_sz, dest, src))
            : (STPCPY_CASE4 __openosc_stpcpy_alias(dest, src)));
}


/* Mapping for stpncpy */

extern char *
__openosc_stpncpy_to_buf(size_t dest_len, char *dest, const char *src, size_t n);
extern char * __REDIRECT_NTH (__openosc_stpncpy_alias,
                              (char *dest, const char *src, size_t n), stpncpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("stpncpy"))
char *
openosc_stpncpy_chk_warn (size_t _sz, char *dest, const char *src, size_t n)
{
    return __openosc_stpncpy_to_buf(_sz, dest, src, n);
}
#else
extern char * __REDIRECT_NTH (openosc_stpncpy_chk_warn,
                              (size_t dest_len, char *dest, const char *src, size_t n), __openosc_stpncpy_to_buf)
       __warn_or_error_attr ("stpncpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function char *
__NTH (stpncpy (char * __pass_objsize1 dest, const char *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n), __dst_overflow_msg("stpncpy"))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (STPNCPY_CASE1 __openosc_stpncpy_alias(dest, src, n))
                  : (STPNCPY_CASE2 openosc_stpncpy_chk_warn(_sz, dest, src, n)))
               : (STPNCPY_CASE3 __openosc_stpncpy_to_buf(_sz, dest, src, n)))
            : (STPNCPY_CASE4 __openosc_stpncpy_alias(dest, src, n)));
}


/* Mapping for ttyname_r */

extern int 
__openosc_ttyname_r_to_buf(size_t dest_len, int fd, char *buf, size_t buflen);
extern int  __REDIRECT_NTH (__openosc_ttyname_r_alias,
                              (int fd, char *buf, size_t buflen), ttyname_r);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("ttyname_r"))
int
openosc_ttyname_r_chk_warn (size_t _sz, int fd, char *buf, size_t buflen)
{
    return __openosc_ttyname_r_to_buf(_sz, fd, buf, buflen);
}
#else
extern int  __REDIRECT_NTH (openosc_ttyname_r_chk_warn,
                              (size_t dest_len, int fd, char *buf, size_t buflen), __openosc_ttyname_r_to_buf)
       __warn_or_error_attr ("ttyname_r caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
__NTH (ttyname_r (int fd, char * __pass_objsize1 buf, size_t buflen))
__clang_warn_or_error_if(__size_too_small (__bos1, buf, buflen), __dst_overflow_msg("ttyname_r"))
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(buflen);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= buflen)
                  ? (TTYNAME_R_CASE1 __openosc_ttyname_r_alias(fd, buf, buflen))
                  : (TTYNAME_R_CASE2 openosc_ttyname_r_chk_warn(_sz, fd, buf, buflen)))
               : (TTYNAME_R_CASE3 __openosc_ttyname_r_to_buf(_sz, fd, buf, buflen)))
            : (TTYNAME_R_CASE4 __openosc_ttyname_r_alias(fd, buf, buflen)));
}


#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vasprintf */

extern int
__vasprintf_chk (char **result_ptr, int flags, const char *format,
                 va_list args);
extern int  __REDIRECT_NTH (__openosc_vasprintf_alias,
                              (char **strp, const char *fmt, va_list ap), vasprintf);

__openosc_fortify_function int 
__NTH (vasprintf (char **strp, const char *fmt, va_list ap))
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VASPRINTF_CASE4 __vasprintf_chk(strp, OPENOSC_USE_FORTIFY_LEVEL - 1, fmt, ap));
#else
    return (VASPRINTF_CASE4 __openosc_vasprintf_alias(strp, fmt, ap));
#endif
}


/* Mapping for vdprintf */

extern int
__vdprintf_chk (int d, int flags, const char *format, va_list arg);
extern int  __REDIRECT (__openosc_vdprintf_alias,
                              (int fd, const char *format, va_list ap), vdprintf);

__openosc_fortify_function int 
vdprintf (int fd, const char *format, va_list ap)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VDPRINTF_CASE4 __vdprintf_chk(fd, OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VDPRINTF_CASE4 __openosc_vdprintf_alias(fd, format, ap));
#endif
}


/* Mapping for vfprintf */

extern int
__vfprintf_chk (FILE *fp, int flag, const char *format, va_list ap);
extern int  __REDIRECT (__openosc_vfprintf_alias,
                              (FILE *stream, const char *format, va_list ap), vfprintf);

__openosc_fortify_function int 
vfprintf (FILE *stream, const char *format, va_list ap)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VFPRINTF_CASE4 __vfprintf_chk(stream, OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VFPRINTF_CASE4 __openosc_vfprintf_alias(stream, format, ap));
#endif
}


/* Mapping for vfwprintf */

extern int
__vfwprintf_chk (FILE *fp, int flag, const wchar_t *format, va_list ap);
extern int  __REDIRECT (__openosc_vfwprintf_alias,
                              (FILE *stream, const wchar_t *format, va_list args), vfwprintf);

__openosc_fortify_function int 
vfwprintf (FILE *stream, const wchar_t *format, va_list args)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VFWPRINTF_CASE4 __vfwprintf_chk(stream, OPENOSC_USE_FORTIFY_LEVEL - 1, format, args));
#else
    return (VFWPRINTF_CASE4 __openosc_vfwprintf_alias(stream, format, args));
#endif
}


#ifndef OPENOSC_VPRINTF_DISABLE

/* bits/stdio.h:36 has a define for vprintf, causing redefinition error */
#ifndef __USE_EXTERN_INLINES

/* Mapping for vprintf */

extern int
__vprintf_chk (int flag, const char *format, va_list ap);
extern int  __REDIRECT_NTH (__openosc_vprintf_alias,
                              (const char *format, va_list ap), vprintf);

__openosc_fortify_function int 
__NTH (vprintf (const char *format, va_list ap))
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VPRINTF_CASE4 __vprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VPRINTF_CASE4 __openosc_vprintf_alias(format, ap));
#endif
}

#endif /* __USE_EXTERN_INLINES */

#endif /* OPENOSC_VPRINTF_DISABLE */


/* Mapping for vsprintf */

extern int
__vsprintf_chk (char *s, int flags, size_t slen, const char *format,
                va_list args);
extern int  __REDIRECT_NTH (__openosc_vsprintf_alias,
                              (char *str, const char *format, va_list ap), vsprintf);

__openosc_fortify_function int 
__NTH (vsprintf (char * __pass_objsize1 str, const char *format, va_list ap))
{
    size_t _sz = __builtin_object_size(str, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
            ? (VSPRINTF_CASE3 __vsprintf_chk(str, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, ap))
            : (VSPRINTF_CASE4 __vsprintf_chk(str, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, ap)));
#else
            ? (VSPRINTF_CASE3 __openosc_vsprintf_alias(str, format, ap))
            : (VSPRINTF_CASE4 __openosc_vsprintf_alias(str, format, ap)));
#endif
}


/* Mapping for vswprintf */

extern int
__vswprintf_chk (wchar_t *s, size_t maxlen, int flags, size_t slen,
                 const wchar_t *format, va_list args);
extern int 
__openosc_vswprintf_to_buf(size_t dest_len, int additional_chk, wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args);
extern int  __REDIRECT_NTH (__openosc_vswprintf_alias,
                              (wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args), vswprintf);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("vswprintf"))
int
openosc_vswprintf_chk_warn (size_t _sz, int additional_chk, wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args)
{
    return __openosc_vswprintf_to_buf(_sz, additional_chk, wcs, maxlen, format, args);
}
#else
extern int  __REDIRECT_NTH (openosc_vswprintf_chk_warn,
                              (size_t dest_len, int additional_chk, wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args), __openosc_vswprintf_to_buf)
       __warn_or_error_attr ("vswprintf caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function int 
__NTH (vswprintf (wchar_t * __pass_objsize1 wcs, size_t maxlen, const wchar_t *format, va_list args))
__clang_warn_or_error_if(__size_too_small (__bos1, wcs, maxlen * sizeof(wchar_t)), __dst_overflow_msg("vswprintf"))
{
    size_t _sz_bytes = __builtin_object_size(wcs, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(maxlen);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= maxlen)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (VSWPRINTF_CASE1 __vswprintf_chk(wcs, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, args))
                  : (VSWPRINTF_CASE2 openosc_vswprintf_chk_warn(_sz, 1, wcs, maxlen, format, args)))
               : (VSWPRINTF_CASE3 __openosc_vswprintf_to_buf(_sz, 1, wcs, maxlen, format, args)))
            : (VSWPRINTF_CASE4 __vswprintf_chk(wcs, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, args)));
#else
                  ? (VSWPRINTF_CASE1 __openosc_vswprintf_alias(wcs, maxlen, format, args))
                  : (VSWPRINTF_CASE2 openosc_vswprintf_chk_warn(_sz, 0, wcs, maxlen, format, args)))
               : (VSWPRINTF_CASE3 __openosc_vswprintf_to_buf(_sz, 0, wcs, maxlen, format, args)))
            : (VSWPRINTF_CASE4 __openosc_vswprintf_alias(wcs, maxlen, format, args)));
#endif
}


/* Mapping for vwprintf */

extern int
__vwprintf_chk (int flag, const wchar_t *format, va_list ap);
extern int  __REDIRECT (__openosc_vwprintf_alias,
                              (const wchar_t *format, va_list args), vwprintf);

__openosc_fortify_function int 
vwprintf (const wchar_t *format, va_list args)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VWPRINTF_CASE4 __vwprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, args));
#else
    return (VWPRINTF_CASE4 __openosc_vwprintf_alias(format, args));
#endif
}

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for wcpcpy */

extern wchar_t *
__openosc_wcpcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);
extern wchar_t * __REDIRECT_NTH (__openosc_wcpcpy_alias,
                              (wchar_t *dest, const wchar_t *src), wcpcpy);
extern wchar_t * __REDIRECT_NTH (openosc_wcpcpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src), __openosc_wcpcpy_to_buf)
       __warn_or_error_attr ("wcpcpy caller with bigger length than size of destination buffer");

__openosc_fortify_function wchar_t *
__NTH (wcpcpy (wchar_t * __pass_objsize1 dest, const wchar_t *src))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCPCPY_CASE3 __openosc_wcpcpy_to_buf(_sz, dest, src))
            : (WCPCPY_CASE4 __openosc_wcpcpy_alias(dest, src)));
}


/* Mapping for wcpncpy */

extern wchar_t *
__openosc_wcpncpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wcpncpy_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wcpncpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcpncpy"))
wchar_t *
openosc_wcpncpy_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wcpncpy_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wcpncpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wcpncpy_to_buf)
       __warn_or_error_attr ("wcpncpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wcpncpy (wchar_t * __pass_objsize1 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wcpncpy"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCPNCPY_CASE1 __openosc_wcpncpy_alias(dest, src, n))
                  : (WCPNCPY_CASE2 openosc_wcpncpy_chk_warn(_sz, dest, src, n)))
               : (WCPNCPY_CASE3 __openosc_wcpncpy_to_buf(_sz, dest, src, n)))
            : (WCPNCPY_CASE4 __openosc_wcpncpy_alias(dest, src, n)));
}


/* Mapping for wcrtomb */

extern size_t 
__openosc_wcrtomb_to_buf(size_t dest_len, char *s, wchar_t wc, mbstate_t *ps);
extern size_t  __REDIRECT_NTH (__openosc_wcrtomb_alias,
                              (char *s, wchar_t wc, mbstate_t *ps), wcrtomb);
extern size_t  __REDIRECT_NTH (openosc_wcrtomb_chk_warn,
                              (size_t dest_len, char *s, wchar_t wc, mbstate_t *ps), __openosc_wcrtomb_to_buf)
       __warn_or_error_attr ("wcrtomb caller with bigger length than size of destination buffer");

__openosc_fortify_function size_t 
__NTH (wcrtomb (char * __pass_objsize1 s, wchar_t wc, mbstate_t *ps))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCRTOMB_CASE3 __openosc_wcrtomb_to_buf(_sz, s, wc, ps))
            : (WCRTOMB_CASE4 __openosc_wcrtomb_alias(s, wc, ps)));
}


/* Mapping for wcscat */

extern wchar_t *
__openosc_wcscat_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);
extern wchar_t * __REDIRECT_NTH (__openosc_wcscat_alias,
                              (wchar_t *dest, const wchar_t *src), wcscat);
extern wchar_t * __REDIRECT_NTH (openosc_wcscat_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src), __openosc_wcscat_to_buf)
       __warn_or_error_attr ("wcscat caller with bigger length than size of destination buffer");

__openosc_fortify_function wchar_t *
__NTH (wcscat (wchar_t * __pass_objsize1 dest, const wchar_t *src))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCAT_CASE3 __openosc_wcscat_to_buf(_sz, dest, src))
            : (WCSCAT_CASE4 __openosc_wcscat_alias(dest, src)));
}


/* Mapping for wcscpy */

extern wchar_t *
__openosc_wcscpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);
extern wchar_t * __REDIRECT_NTH (__openosc_wcscpy_alias,
                              (wchar_t *dest, const wchar_t *src), wcscpy);
extern wchar_t * __REDIRECT_NTH (openosc_wcscpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src), __openosc_wcscpy_to_buf)
       __warn_or_error_attr ("wcscpy caller with bigger length than size of destination buffer");

__openosc_fortify_function wchar_t *
__NTH (wcscpy (wchar_t * __pass_objsize1 dest, const wchar_t *src))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCPY_CASE3 __openosc_wcscpy_to_buf(_sz, dest, src))
            : (WCSCPY_CASE4 __openosc_wcscpy_alias(dest, src)));
}


/* Mapping for wcsncat */

extern wchar_t *
__openosc_wcsncat_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wcsncat_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wcsncat);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcsncat"))
wchar_t *
openosc_wcsncat_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wcsncat_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wcsncat_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wcsncat_to_buf)
       __warn_or_error_attr ("wcsncat caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wcsncat (wchar_t * __pass_objsize1 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wcsncat"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSNCAT_CASE1 __openosc_wcsncat_alias(dest, src, n))
                  : (WCSNCAT_CASE2 openosc_wcsncat_chk_warn(_sz, dest, src, n)))
               : (WCSNCAT_CASE3 __openosc_wcsncat_to_buf(_sz, dest, src, n)))
            : (WCSNCAT_CASE4 __openosc_wcsncat_alias(dest, src, n)));
}


/* Mapping for wcsncpy */

extern wchar_t *
__openosc_wcsncpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wcsncpy_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wcsncpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcsncpy"))
wchar_t *
openosc_wcsncpy_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wcsncpy_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wcsncpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wcsncpy_to_buf)
       __warn_or_error_attr ("wcsncpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wcsncpy (wchar_t * __pass_objsize1 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wcsncpy"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSNCPY_CASE1 __openosc_wcsncpy_alias(dest, src, n))
                  : (WCSNCPY_CASE2 openosc_wcsncpy_chk_warn(_sz, dest, src, n)))
               : (WCSNCPY_CASE3 __openosc_wcsncpy_to_buf(_sz, dest, src, n)))
            : (WCSNCPY_CASE4 __openosc_wcsncpy_alias(dest, src, n)));
}


/* Mapping for wcsnrtombs */

extern size_t 
__openosc_wcsnrtombs_to_buf(size_t dest_len, char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps);
extern size_t  __REDIRECT_NTH (__openosc_wcsnrtombs_alias,
                              (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps), wcsnrtombs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcsnrtombs"))
size_t
openosc_wcsnrtombs_chk_warn (size_t _sz, char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)
{
    return __openosc_wcsnrtombs_to_buf(_sz, dest, src, nwc, len, ps);
}
#else
extern size_t  __REDIRECT_NTH (openosc_wcsnrtombs_chk_warn,
                              (size_t dest_len, char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps), __openosc_wcsnrtombs_to_buf)
       __warn_or_error_attr ("wcsnrtombs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (wcsnrtombs (char * __pass_objsize1 dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, len), __dst_overflow_msg("wcsnrtombs"))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (WCSNRTOMBS_CASE1 __openosc_wcsnrtombs_alias(dest, src, nwc, len, ps))
                  : (WCSNRTOMBS_CASE2 openosc_wcsnrtombs_chk_warn(_sz, dest, src, nwc, len, ps)))
               : (WCSNRTOMBS_CASE3 __openosc_wcsnrtombs_to_buf(_sz, dest, src, nwc, len, ps)))
            : (WCSNRTOMBS_CASE4 __openosc_wcsnrtombs_alias(dest, src, nwc, len, ps)));
}


/* Mapping for wcsrtombs */

extern size_t 
__openosc_wcsrtombs_to_buf(size_t dest_len, char *dest, const wchar_t **src, size_t len, mbstate_t *ps);
extern size_t  __REDIRECT_NTH (__openosc_wcsrtombs_alias,
                              (char *dest, const wchar_t **src, size_t len, mbstate_t *ps), wcsrtombs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcsrtombs"))
size_t
openosc_wcsrtombs_chk_warn (size_t _sz, char *dest, const wchar_t **src, size_t len, mbstate_t *ps)
{
    return __openosc_wcsrtombs_to_buf(_sz, dest, src, len, ps);
}
#else
extern size_t  __REDIRECT_NTH (openosc_wcsrtombs_chk_warn,
                              (size_t dest_len, char *dest, const wchar_t **src, size_t len, mbstate_t *ps), __openosc_wcsrtombs_to_buf)
       __warn_or_error_attr ("wcsrtombs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (wcsrtombs (char * __pass_objsize1 dest, const wchar_t **src, size_t len, mbstate_t *ps))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, len), __dst_overflow_msg("wcsrtombs"))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (WCSRTOMBS_CASE1 __openosc_wcsrtombs_alias(dest, src, len, ps))
                  : (WCSRTOMBS_CASE2 openosc_wcsrtombs_chk_warn(_sz, dest, src, len, ps)))
               : (WCSRTOMBS_CASE3 __openosc_wcsrtombs_to_buf(_sz, dest, src, len, ps)))
            : (WCSRTOMBS_CASE4 __openosc_wcsrtombs_alias(dest, src, len, ps)));
}


/* Mapping for wcstombs */

extern size_t 
__openosc_wcstombs_to_buf(size_t dest_len, char *dest, const wchar_t *src, size_t n);
extern size_t  __REDIRECT_NTH (__openosc_wcstombs_alias,
                              (char *dest, const wchar_t *src, size_t n), wcstombs);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wcstombs"))
size_t
openosc_wcstombs_chk_warn (size_t _sz, char *dest, const wchar_t *src, size_t n)
{
    return __openosc_wcstombs_to_buf(_sz, dest, src, n);
}
#else
extern size_t  __REDIRECT_NTH (openosc_wcstombs_chk_warn,
                              (size_t dest_len, char *dest, const wchar_t *src, size_t n), __openosc_wcstombs_to_buf)
       __warn_or_error_attr ("wcstombs caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function size_t 
__NTH (wcstombs (char * __pass_objsize1 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos1, dest, n), __dst_overflow_msg("wcstombs"))
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WCSTOMBS_CASE1 __openosc_wcstombs_alias(dest, src, n))
                  : (WCSTOMBS_CASE2 openosc_wcstombs_chk_warn(_sz, dest, src, n)))
               : (WCSTOMBS_CASE3 __openosc_wcstombs_to_buf(_sz, dest, src, n)))
            : (WCSTOMBS_CASE4 __openosc_wcstombs_alias(dest, src, n)));
}


/* Mapping for wctomb */

extern int 
__openosc_wctomb_to_buf(size_t dest_len, char *s, wchar_t wc);
extern int  __REDIRECT_NTH (__openosc_wctomb_alias,
                              (char *s, wchar_t wc), wctomb);
extern int  __REDIRECT_NTH (openosc_wctomb_chk_warn,
                              (size_t dest_len, char *s, wchar_t wc), __openosc_wctomb_to_buf)
       __warn_or_error_attr ("wctomb caller with bigger length than size of destination buffer");

__openosc_fortify_function int 
__NTH (wctomb (char * __pass_objsize1 s, wchar_t wc))
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCTOMB_CASE3 __openosc_wctomb_to_buf(_sz, s, wc))
            : (WCTOMB_CASE4 __openosc_wctomb_alias(s, wc)));
}


/* Mapping for wmemcpy */

extern wchar_t *
__openosc_wmemcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wmemcpy_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wmemcpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wmemcpy"))
wchar_t *
openosc_wmemcpy_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wmemcpy_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wmemcpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wmemcpy_to_buf)
       __warn_or_error_attr ("wmemcpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wmemcpy (wchar_t * __pass_objsize0 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos0, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wmemcpy"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMCPY_CASE1 __openosc_wmemcpy_alias(dest, src, n))
                  : (WMEMCPY_CASE2 openosc_wmemcpy_chk_warn(_sz, dest, src, n)))
               : (WMEMCPY_CASE3 __openosc_wmemcpy_to_buf(_sz, dest, src, n)))
            : (WMEMCPY_CASE4 __openosc_wmemcpy_alias(dest, src, n)));
}


/* Mapping for wmemmove */

extern wchar_t *
__openosc_wmemmove_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wmemmove_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wmemmove);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wmemmove"))
wchar_t *
openosc_wmemmove_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wmemmove_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wmemmove_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wmemmove_to_buf)
       __warn_or_error_attr ("wmemmove caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wmemmove (wchar_t * __pass_objsize0 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos0, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wmemmove"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMMOVE_CASE1 __openosc_wmemmove_alias(dest, src, n))
                  : (WMEMMOVE_CASE2 openosc_wmemmove_chk_warn(_sz, dest, src, n)))
               : (WMEMMOVE_CASE3 __openosc_wmemmove_to_buf(_sz, dest, src, n)))
            : (WMEMMOVE_CASE4 __openosc_wmemmove_alias(dest, src, n)));
}


/* Mapping for wmempcpy */

extern wchar_t *
__openosc_wmempcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wmempcpy_alias,
                              (wchar_t *dest, const wchar_t *src, size_t n), wmempcpy);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wmempcpy"))
wchar_t *
openosc_wmempcpy_chk_warn (size_t _sz, wchar_t *dest, const wchar_t *src, size_t n)
{
    return __openosc_wmempcpy_to_buf(_sz, dest, src, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wmempcpy_chk_warn,
                              (size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n), __openosc_wmempcpy_to_buf)
       __warn_or_error_attr ("wmempcpy caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wmempcpy (wchar_t * __pass_objsize0 dest, const wchar_t *src, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos0, dest, n * sizeof(wchar_t)), __dst_overflow_msg("wmempcpy"))
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMPCPY_CASE1 __openosc_wmempcpy_alias(dest, src, n))
                  : (WMEMPCPY_CASE2 openosc_wmempcpy_chk_warn(_sz, dest, src, n)))
               : (WMEMPCPY_CASE3 __openosc_wmempcpy_to_buf(_sz, dest, src, n)))
            : (WMEMPCPY_CASE4 __openosc_wmempcpy_alias(dest, src, n)));
}


/* Mapping for wmemset */

extern wchar_t *
__openosc_wmemset_to_buf(size_t dest_len, wchar_t *wcs, wchar_t wc, size_t n);
extern wchar_t * __REDIRECT_NTH (__openosc_wmemset_alias,
                              (wchar_t *wcs, wchar_t wc, size_t n), wmemset);
#if __OPENOSC_CLANG_CC
static __attribute__((noinline))
     __warn_or_error_attr (__dst_overflow_msg("wmemset"))
wchar_t *
openosc_wmemset_chk_warn (size_t _sz, wchar_t *wcs, wchar_t wc, size_t n)
{
    return __openosc_wmemset_to_buf(_sz, wcs, wc, n);
}
#else
extern wchar_t * __REDIRECT_NTH (openosc_wmemset_chk_warn,
                              (size_t dest_len, wchar_t *wcs, wchar_t wc, size_t n), __openosc_wmemset_to_buf)
       __warn_or_error_attr ("wmemset caller with bigger length than size of destination buffer");
#endif

__openosc_fortify_function wchar_t *
__NTH (wmemset (wchar_t * __pass_objsize0 wcs, wchar_t wc, size_t n))
__clang_warn_or_error_if(__size_too_small (__bos0, wcs, n * sizeof(wchar_t)), __dst_overflow_msg("wmemset"))
{
    size_t _sz_bytes = __builtin_object_size(wcs, OSC_OBJECT_SIZE_CHECK_0);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= n)
                  ? (WMEMSET_CASE1 __openosc_wmemset_alias(wcs, wc, n))
                  : (WMEMSET_CASE2 openosc_wmemset_chk_warn(_sz, wcs, wc, n)))
               : (WMEMSET_CASE3 __openosc_wmemset_to_buf(_sz, wcs, wc, n)))
            : (WMEMSET_CASE4 __openosc_wmemset_alias(wcs, wc, n)));
}

#endif  /* ifndef __OPENOSC_FORTIFY_REDIRECT_NOMAP_H__ */

#endif  /* __OPENOSC_FORTIFY_REDIRECT_MAP_H__ */
