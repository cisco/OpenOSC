/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_H__
#define __OPENOSC_FORTIFY_H__

/* The below macro is copied from include/features.h */
/* Convenience macro to test the version of gcc.
   Use like this:
   #if __GNUC_PREREQ (2,8)
   ... code requiring gcc 2.8 or later ...
   #endif
   Note: only works for GCC 2.0 and later, because __GNUC_MINOR__ was
   added in 2.0.  */
#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

/* All the below macros are copied from misc/sys/cdefs.h */
#ifdef __GNUC__

/* All functions, except those with callbacks or those that
   synchronize memory, are leaf functions.  */
# if __GNUC_PREREQ (4, 6) && !defined _LIBC
#  define __LEAF , __leaf__
#  define __LEAF_ATTR __attribute__ ((__leaf__))
# else
#  define __LEAF
#  define __LEAF_ATTR
# endif

/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  For gcc 3.2 and up we even mark C functions
   as non-throwing using a function attribute since programs can use
   the -fexceptions options for C code as well.  */
# if !defined __cplusplus && __GNUC_PREREQ (3, 3)
#  define __THROW	__attribute__ ((__nothrow__ __LEAF))
#  define __THROWNL	__attribute__ ((__nothrow__))
#  define __NTH(fct)	__attribute__ ((__nothrow__ __LEAF)) fct
#  define __NTHNL(fct)  __attribute__ ((__nothrow__)) fct
# else
#  if defined __cplusplus && __GNUC_PREREQ (2,8)
#   define __THROW	throw ()
#   define __THROWNL	throw ()
#   define __NTH(fct)	__LEAF_ATTR fct throw ()
#   define __NTHNL(fct) fct throw ()
#  else
#   define __THROW
#   define __THROWNL
#   define __NTH(fct)	fct
#   define __NTHNL(fct) fct
#  endif
# endif

#else	/* Not GCC.  */

# if (defined __cplusplus						\
      || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L))
#  define __inline	inline
# else
#  define __inline		/* No inline functions.  */
# endif

# define __THROW
# define __THROWNL
# define __NTH(fct)	fct

#endif	/* GCC.  */

#define __CONCAT(x,y)   x ## y
#define __STRING(x)     #x

#if __GNUC_PREREQ (4,3)
# define __warndecl(name, msg) \
  extern void name (void) __attribute__((__warning__ (msg)))
# define __warnattr(msg) __attribute__((__warning__ (msg)))
# define __errorattr(msg) __attribute__((__error__ (msg)))
# define __errordecl(name, msg) \
  extern void name (void) __attribute__((__error__ (msg)))
#else
# define __warndecl(name, msg) extern void name (void)
# define __warnattr(msg)
# define __errorattr(msg)
# define __errordecl(name, msg) extern void name (void)
#endif 


/* __asm__ ("xyz") is used throughout the headers to rename functions
   at the assembly language level.  This is wrapped by the __REDIRECT
   macro, in order to support compilers that can do this some other
   way.  When compilers don't support asm-names at all, we have to do
   preprocessor tricks instead (which don't have exactly the right
   semantics, but it's the best we can do).

   Example:
   int __REDIRECT(setpgrp, (__pid_t pid, __pid_t pgrp), setpgid); */

#if defined __GNUC__ && __GNUC__ >= 2

# define __REDIRECT(name, proto, alias) name proto __asm__ (__ASMNAME (#alias))
# ifdef __cplusplus
#  define __REDIRECT_NTH(name, proto, alias) \
     name proto __THROW __asm__ (__ASMNAME (#alias))
#  define __REDIRECT_NTHNL(name, proto, alias) \
     name proto __THROWNL __asm__ (__ASMNAME (#alias))
# else
#  define __REDIRECT_NTH(name, proto, alias) \
     name proto __asm__ (__ASMNAME (#alias)) __THROW
#  define __REDIRECT_NTHNL(name, proto, alias) \
     name proto __asm__ (__ASMNAME (#alias)) __THROWNL
# endif
# define __ASMNAME(cname)  __ASMNAME2 (__USER_LABEL_PREFIX__, cname)
# define __ASMNAME2(prefix, cname) __STRING (prefix) cname

/*
#elif __SOME_OTHER_COMPILER__

# define __REDIRECT(name, proto, alias) name proto; \
        _Pragma("let " #name " = " #alias)
*/
#endif

/* The nonull function attribute allows to mark pointer parameters which
   must not be NULL.  */
#if __GNUC_PREREQ (3,3)
# define __nonnull(params) __attribute__ ((__nonnull__ params))
#else
# define __nonnull(params)
#endif

/* If fortification mode, we warn about unused results of certain
   function calls which can lead to problems.  */
#if __GNUC_PREREQ (3,4)
# define __attribute_warn_unused_result__ \
   __attribute__ ((__warn_unused_result__))
# if __USE_FORTIFY_LEVEL > 0
#  define __wur __attribute_warn_unused_result__
# endif
#else
# define __attribute_warn_unused_result__ /* empty */
#endif
#ifndef __wur
# define __wur /* Ignore */
#endif

/* Forces a function to be always inlined.  */
#if __GNUC_PREREQ (3,2)
/* The Linux kernel defines __always_inline in stddef.h (283d7573), and
   it conflicts with this definition.  Therefore undefine it first to
   allow either header to be included first.  */
# undef __always_inline
# define __always_inline __inline __attribute__ ((__always_inline__))
#else
# undef __always_inline
# define __always_inline __inline
#endif

/* Associate error messages with the source location of the call site rather
   than with the source location inside the function.  */
#if __GNUC_PREREQ (4,3)
# define __attribute_artificial__ __attribute__ ((__artificial__))
#else
# define __attribute_artificial__ /* Ignore */
#endif

/* GCC 4.3 and above with -std=c99 or -std=gnu99 implements ISO C99
   inline semantics, unless -fgnu89-inline is used.  Using __GNUC_STDC_INLINE__
   or __GNUC_GNU_INLINE is not a good enough check for gcc because gcc versions
   older than 4.3 may define these macros and still not guarantee GNU inlining
   semantics.

   clang++ identifies itself as gcc-4.2, but has support for GNU inlining
   semantics, that can be checked fot by using the __GNUC_STDC_INLINE_ and
   __GNUC_GNU_INLINE__ macro definitions.  */
#if (!defined __cplusplus || __GNUC_PREREQ (4,3) \
     || (defined __clang__ && (defined __GNUC_STDC_INLINE__ \
			       || defined __GNUC_GNU_INLINE__)))
# if defined __GNUC_STDC_INLINE__ || defined __cplusplus
#  define __extern_inline extern __inline __attribute__ ((__gnu_inline__))
#  define __extern_always_inline \
  extern __always_inline __attribute__ ((__gnu_inline__))
# else
#  define __extern_inline extern __inline
#  define __extern_always_inline extern __always_inline
# endif
#endif

#ifdef __extern_always_inline
# define __fortify_function __extern_always_inline __attribute_artificial__
#endif

/* GCC 4.3 and above allow passing all anonymous arguments of an
   __extern_always_inline function to some other vararg function.  */
#if __GNUC_PREREQ (4,3)
# define __va_arg_pack() __builtin_va_arg_pack ()
# define __va_arg_pack_len() __builtin_va_arg_pack_len ()
#endif


/* Errors are reported at compile-time unless you disable it explicitly */
#ifndef OPENOSC_OVERFLOW_ERROR_OUT_DISABLE
/* Do we want to error out at compile-time when detecting overflow/overread */
/* Also fow now, this flag only affects the ASM-redirect method */
#define OPENOSC_ERROR_OUT_ON_COMPILE_TIME_DETECTION_OVERFLOW
#endif

#define __dst_overflow_msg(func) func " caller with bigger length than size of destination buffer"
#define __src_overread_msg(func) func " caller with bigger length than size of source buffer, will cause src overread"

#define __OPENOSC_CLANG_CC  (__clang__ && __clang_major__ >= 5)

/* For clang compiler support */
#if __clang__

#define __bos0(ptr) __builtin_object_size (ptr, 0)
#define __bos1(ptr) __builtin_object_size (ptr, 1)
#define __size_too_small(bos, dest, len) \
        (bos (dest) != (size_t) -1 && bos (dest) != (size_t) 0 && bos (dest) < len)

#define __always_enabled  __attribute__ ((enable_if (1, "")))
#define __attribute_overloadable__ __attribute__((overloadable))

/* No support if clang version is less than 5.0 */
#if __clang_major__ < 5
#define __clang_error_if(c, m)
#define __clang_warning_if(c, m)
#define __pass_objsize0
#define __pass_objsize1
#define __openosc_fortify_function __fortify_function
#else
#define __clang_error_if(c, m) __attribute__ ((__diagnose_if__ ((c), (m), "error")))
#define __clang_warning_if(c, m) __attribute__ ((__diagnose_if__ ((c), (m), "warning")))
#define __pass_objsize0 const __attribute__((pass_object_size(0)))
#define __pass_objsize1 const __attribute__((pass_object_size(1)))
#define __openosc_fortify_function static __always_inline __attribute_artificial__ __always_enabled __attribute_overloadable__
#endif

#ifdef _OPENOSC_EMIT_NOTHING_ON_COMPILE_TIME_DETECTION_OVERFLOW
#define __warn_or_error_attr(m)
#define __clang_warn_or_error_if(c, m)
#else

#if defined(OPENOSC_ERROR_OUT_ON_COMPILE_TIME_DETECTION_OVERFLOW) \
       && __has_attribute(error)
#define __warn_or_error_attr(m) __attribute__((__error__ (m)))
#elif __has_attribute(warning)
#define __warn_or_error_attr(m) __attribute__((__warning__ (m)))
#else
#define __warn_or_error_attr(m)
#endif

#ifdef OPENOSC_ERROR_OUT_ON_COMPILE_TIME_DETECTION_OVERFLOW
#if __has_attribute(error)
/* Avoid duplicate error message if function error attribute is available */
#define __clang_warn_or_error_if(c, m)
#else
#define __clang_warn_or_error_if(c, m) __clang_error_if(c, m)
#endif
#else
#if __has_attribute(warning)
/* Avoid duplicate warn message if function warning attribute is available */
#define __clang_warn_or_error_if(c, m)
#else
#define __clang_warn_or_error_if(c, m) __clang_warning_if(c, m)
#endif
#endif

#endif  /* _OPENOSC_EMIT_NOTHING_ON_COMPILE_TIME_DETECTION_OVERFLOW */

#else  /* not clang compiler */

#define __pass_objsize0
#define __pass_objsize1
#define __openosc_fortify_function __fortify_function

#define __clang_warn_or_error_if(c, m)
#ifdef _OPENOSC_EMIT_NOTHING_ON_COMPILE_TIME_DETECTION_OVERFLOW
#define __warn_or_error_attr(m)
#else
#ifdef OPENOSC_ERROR_OUT_ON_COMPILE_TIME_DETECTION_OVERFLOW
#define __warn_or_error_attr(m) __errorattr(m)
#else
#define __warn_or_error_attr(m) __warnattr(m)
#endif
#endif

#endif  /* __clang__ */

#endif  /* __OPENOSC_FORTIFY_H__ */

