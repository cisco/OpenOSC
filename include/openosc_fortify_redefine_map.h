/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_REDEFINE_MAP_H__
#define __OPENOSC_FORTIFY_REDEFINE_MAP_H__

/* openosc_fortify_redefine_map.h and openosc_fortify_redefine_nomap.h are mutually exclusive */
#ifndef __OPENOSC_FORTIFY_REDEFINE_NOMAP_H__

#ifndef OPENOSC_USE_FORTIFY_LEVEL
#define OPENOSC_USE_FORTIFY_LEVEL 2
#endif


/*
 * Define Runtime check macros
 */
#if (OSC_RUNTIME_CHK == OSC_RUNTIME_USE_LIBOSC)

#define OSC_RUNTIME_CHECK_confstr()		__openosc_confstr_to_buf(_sz, name, buf, len)
#define OSC_RUNTIME_CHECK_fgets(chk)		__openosc_fgets_to_buf(_sz, chk, s, size, stream)
#define OSC_RUNTIME_CHECK_fgets_unlocked(chk)		__openosc_fgets_unlocked_to_buf(_sz, chk, s, n, stream)
#define OSC_RUNTIME_CHECK_fgetws(chk)		__openosc_fgetws_to_buf(_sz, chk, ws, n, stream)
#define OSC_RUNTIME_CHECK_fgetws_unlocked(chk)		__openosc_fgetws_unlocked_to_buf(_sz, chk, ws, n, stream)
#define OSC_RUNTIME_CHECK_fread(chk)		__openosc_fread_to_buf(_sz, chk, ptr, size, nmemb, stream)
#define OSC_RUNTIME_CHECK_fread_unlocked(chk)		__openosc_fread_unlocked_to_buf(_sz, chk, ptr, size, n, stream)
#define OSC_RUNTIME_CHECK_getcwd()		__openosc_getcwd_to_buf(_sz, buf, size)
#define OSC_RUNTIME_CHECK_getdomainname()		__openosc_getdomainname_to_buf(_sz, name, len)
#define OSC_RUNTIME_CHECK_getgroups(_sz)		__openosc_getgroups_to_buf(_sz, size, list)
#define OSC_RUNTIME_CHECK_gethostname()		__openosc_gethostname_to_buf(_sz, name, len)
#define OSC_RUNTIME_CHECK_gets()		__openosc_gets_to_buf(_sz, s)
#define OSC_RUNTIME_CHECK_getwd()		__openosc_getwd_to_buf(_sz, buf)
#define OSC_RUNTIME_CHECK_mbsnrtowcs()		__openosc_mbsnrtowcs_to_buf(_sz, dest, src, nms, len, ps)
#define OSC_RUNTIME_CHECK_mbsrtowcs()		__openosc_mbsrtowcs_to_buf(_sz, dest, src, len, ps)
#define OSC_RUNTIME_CHECK_mbstowcs()		__openosc_mbstowcs_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_mempcpy()		__openosc_mempcpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_poll()		__openosc_poll_to_buf(_sz, fds, nfds, timeout)
#define OSC_RUNTIME_CHECK_ppoll()		__openosc_ppoll_to_buf(_sz, fds, nfds, timeout_ts, sigmask)
#define OSC_RUNTIME_CHECK_pread()		__openosc_pread_to_buf(_sz, fd, buf, count, offset)
#define OSC_RUNTIME_CHECK_read()		__openosc_read_to_buf(_sz, fd, buf, count)
#define OSC_RUNTIME_CHECK_readlinkat()		__openosc_readlinkat_to_buf(_sz, dirfd, pathname, buf, bufsiz)
#define OSC_RUNTIME_CHECK_readlink()		__openosc_readlink_to_buf(_sz, path, buf, bufsiz)
#define OSC_RUNTIME_CHECK_realpath()		__openosc_realpath_to_buf(_sz, path, resolved_path)
#define OSC_RUNTIME_CHECK_recv()		__openosc_recv_to_buf(_sz, sockfd, buf, len, flags)
#define OSC_RUNTIME_CHECK_recvfrom()		__openosc_recvfrom_to_buf(_sz, sockfd, buf, len, flags, src_addr, addrlen)
#define OSC_RUNTIME_CHECK_stpcpy()		__openosc_stpcpy_to_buf(_sz, dest, src)
#define OSC_RUNTIME_CHECK_stpncpy()		__openosc_stpncpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_ttyname_r()		__openosc_ttyname_r_to_buf(_sz, fd, buf, buflen)
#define OSC_RUNTIME_CHECK_vasprintf()		__openosc_vasprintf_to_buf(_sz, strp, fmt, ap)
#define OSC_RUNTIME_CHECK_vdprintf()		__openosc_vdprintf_to_buf(_sz, fd, format, ap)
#define OSC_RUNTIME_CHECK_vfprintf()		__openosc_vfprintf_to_buf(_sz, stream, format, ap)
#define OSC_RUNTIME_CHECK_vfwprintf()		__openosc_vfwprintf_to_buf(_sz, stream, format, args)
#define OSC_RUNTIME_CHECK_vprintf()		__openosc_vprintf_to_buf(_sz, format, ap)
#define OSC_RUNTIME_CHECK_vsprintf()		__openosc_vsprintf_to_buf(_sz, str, format, ap)
#define OSC_RUNTIME_CHECK_vswprintf(chk)	__openosc_vswprintf_to_buf(_sz, chk, wcs, maxlen, format, args)
#define OSC_RUNTIME_CHECK_vwprintf()		__openosc_vwprintf_to_buf(_sz, format, args)
#define OSC_RUNTIME_CHECK_wcpcpy()		__openosc_wcpcpy_to_buf(_sz, dest, src)
#define OSC_RUNTIME_CHECK_wcpncpy()		__openosc_wcpncpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wcrtomb()		__openosc_wcrtomb_to_buf(_sz, s, wc, ps)
#define OSC_RUNTIME_CHECK_wcscat()		__openosc_wcscat_to_buf(_sz, dest, src)
#define OSC_RUNTIME_CHECK_wcscpy()		__openosc_wcscpy_to_buf(_sz, dest, src)
#define OSC_RUNTIME_CHECK_wcsncat()		__openosc_wcsncat_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wcsncpy()		__openosc_wcsncpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wcsnrtombs()		__openosc_wcsnrtombs_to_buf(_sz, dest, src, nwc, len, ps)
#define OSC_RUNTIME_CHECK_wcsrtombs()		__openosc_wcsrtombs_to_buf(_sz, dest, src, len, ps)
#define OSC_RUNTIME_CHECK_wcstombs()		__openosc_wcstombs_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wctomb()		__openosc_wctomb_to_buf(_sz, s, wc)
#define OSC_RUNTIME_CHECK_wmemcpy()		__openosc_wmemcpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wmemmove()		__openosc_wmemmove_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wmempcpy()		__openosc_wmempcpy_to_buf(_sz, dest, src, n)
#define OSC_RUNTIME_CHECK_wmemset()		__openosc_wmemset_to_buf(_sz, wcs, wc, n)

#else  /* OSC_RUNTIME_CHK != OSC_RUNTIME_USE_LIBOSC */

#define OSC_RUNTIME_CHECK_confstr()		confstr(name, buf, len)
#define OSC_RUNTIME_CHECK_fgets(chk)		fgets(s, size, stream)
#define OSC_RUNTIME_CHECK_fgets_unlocked(chk)		fgets_unlocked(s, n, stream)
#define OSC_RUNTIME_CHECK_fgetws(chk)		fgetws(ws, n, stream)
#define OSC_RUNTIME_CHECK_fgetws_unlocked(chk)		fgetws_unlocked(ws, n, stream)
#define OSC_RUNTIME_CHECK_fread(chk)		fread(ptr, size, nmemb, stream)
#define OSC_RUNTIME_CHECK_fread_unlocked(chk)		fread_unlocked(ptr, size, n, stream)
#define OSC_RUNTIME_CHECK_getcwd()		getcwd(buf, size)
#define OSC_RUNTIME_CHECK_getdomainname()		getdomainname(name, len)
#define OSC_RUNTIME_CHECK_getgroups(_sz)		getgroups(size, list)
#define OSC_RUNTIME_CHECK_gethostname()		gethostname(name, len)
#define OSC_RUNTIME_CHECK_gets()		gets(s)
#define OSC_RUNTIME_CHECK_getwd()		getwd(buf)
#define OSC_RUNTIME_CHECK_mbsnrtowcs()		mbsnrtowcs(dest, src, nms, len, ps)
#define OSC_RUNTIME_CHECK_mbsrtowcs()		mbsrtowcs(dest, src, len, ps)
#define OSC_RUNTIME_CHECK_mbstowcs()		mbstowcs(dest, src, n)
#define OSC_RUNTIME_CHECK_mempcpy()		mempcpy(dest, src, n)
#define OSC_RUNTIME_CHECK_poll()		poll(fds, nfds, timeout)
#define OSC_RUNTIME_CHECK_ppoll()		ppoll(fds, nfds, timeout_ts, sigmask)
#define OSC_RUNTIME_CHECK_pread()		pread(fd, buf, count, offset)
#define OSC_RUNTIME_CHECK_read()		read(fd, buf, count)
#define OSC_RUNTIME_CHECK_readlinkat()		readlinkat(dirfd, pathname, buf, bufsiz)
#define OSC_RUNTIME_CHECK_readlink()		readlink(path, buf, bufsiz)
#define OSC_RUNTIME_CHECK_realpath()		realpath(path, resolved_path)
#define OSC_RUNTIME_CHECK_recv()		recv(sockfd, buf, len, flags)
#define OSC_RUNTIME_CHECK_recvfrom()		recvfrom(sockfd, buf, len, flags, src_addr, addrlen)
#define OSC_RUNTIME_CHECK_stpcpy()		stpcpy(dest, src)
#define OSC_RUNTIME_CHECK_stpncpy()		stpncpy(dest, src, n)
#define OSC_RUNTIME_CHECK_ttyname_r()		ttyname_r(fd, buf, buflen)
#define OSC_RUNTIME_CHECK_vasprintf()		vasprintf(strp, fmt, ap)
#define OSC_RUNTIME_CHECK_vdprintf()		vdprintf(fd, format, ap)
#define OSC_RUNTIME_CHECK_vfprintf()		vfprintf(stream, format, ap)
#define OSC_RUNTIME_CHECK_vfwprintf()		vfwprintf(stream, format, args)
#define OSC_RUNTIME_CHECK_vprintf()		vprintf(format, ap)
#define OSC_RUNTIME_CHECK_vsprintf()		vsprintf(str, format, ap)
#define OSC_RUNTIME_CHECK_vswprintf(chk)	vswprintf(wcs, maxlen, format, args)
#define OSC_RUNTIME_CHECK_vwprintf()		vwprintf(format, args)
#define OSC_RUNTIME_CHECK_wcpcpy()		wcpcpy(dest, src)
#define OSC_RUNTIME_CHECK_wcpncpy()		wcpncpy(dest, src, n)
#define OSC_RUNTIME_CHECK_wcrtomb()		wcrtomb(s, wc, ps)
#define OSC_RUNTIME_CHECK_wcscat()		wcscat(dest, src)
#define OSC_RUNTIME_CHECK_wcscpy()		wcscpy(dest, src)
#define OSC_RUNTIME_CHECK_wcsncat()		wcsncat(dest, src, n)
#define OSC_RUNTIME_CHECK_wcsncpy()		wcsncpy(dest, src, n)
#define OSC_RUNTIME_CHECK_wcsnrtombs()		wcsnrtombs(dest, src, nwc, len, ps)
#define OSC_RUNTIME_CHECK_wcsrtombs()		wcsrtombs(dest, src, len, ps)
#define OSC_RUNTIME_CHECK_wcstombs()		wcstombs(dest, src, n)
#define OSC_RUNTIME_CHECK_wctomb()		wctomb(s, wc)
#define OSC_RUNTIME_CHECK_wmemcpy()		wmemcpy(dest, src, n)
#define OSC_RUNTIME_CHECK_wmemmove()		wmemmove(dest, src, n)
#define OSC_RUNTIME_CHECK_wmempcpy()		wmempcpy(dest, src, n)
#define OSC_RUNTIME_CHECK_wmemset()		wmemset(wcs, wc, n)

#endif  /* OSC_RUNTIME_CHK */


/*
 * Define compile-time static asserts to report buffer overflow
 * detected by OSC
 *
 * Since support for compile-time error reporting are compiler dependent,
 * there will be multiple definitions of these macros. To select a specific
 * implemetaton, define the appropriate flag within this header file. For
 * the build enviroment that use multiple compilers, the flag can be defined
 * on the command line using the "-D" switch.
 *
 * Note: OSC_ASSERT_USE_BUILTIN should only be used for compile-time check
 * only. It must NOT be used in release code or a risk of abort() call get
 * inserted into production image by the compiler.
 */
#if (OSC_COMPILE_CHK == OSC_ASSERT_USE_ERR_ATTR)

extern int __attribute__((error("Compiler Assertion: confstr len will always overflow dst"))) \
 osc_compile_check_confstr(void);
#define OSC_ASSERT_confstr() ({osc_compile_check_confstr(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: fgets len will always overflow dst"))) \
 osc_compile_check_fgets(void);
#define OSC_ASSERT_fgets(chk) ({osc_compile_check_fgets(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: fgets_unlocked len will always overflow dst"))) \
 osc_compile_check_fgets_unlocked(void);
#define OSC_ASSERT_fgets_unlocked(chk) ({osc_compile_check_fgets_unlocked(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: fgetws len will always overflow dst"))) \
 osc_compile_check_fgetws(void);
#define OSC_ASSERT_fgetws(chk) ({osc_compile_check_fgetws(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: fgetws_unlocked len will always overflow dst"))) \
 osc_compile_check_fgetws_unlocked(void);
#define OSC_ASSERT_fgetws_unlocked(chk) ({osc_compile_check_fgetws_unlocked(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: fread len will always overflow dst"))) \
 osc_compile_check_fread(void);
#define OSC_ASSERT_fread(chk) ({osc_compile_check_fread(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: fread_unlocked len will always overflow dst"))) \
 osc_compile_check_fread_unlocked(void);
#define OSC_ASSERT_fread_unlocked(chk) ({osc_compile_check_fread_unlocked(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: getcwd len will always overflow dst"))) \
 osc_compile_check_getcwd(void);
#define OSC_ASSERT_getcwd() ({osc_compile_check_getcwd(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: getdomainname len will always overflow dst"))) \
 osc_compile_check_getdomainname(void);
#define OSC_ASSERT_getdomainname() ({osc_compile_check_getdomainname(), (int )0;})

extern int __attribute__((error("Compiler Assertion: getgroups len will always overflow dst"))) \
 osc_compile_check_getgroups(void);
#define OSC_ASSERT_getgroups() ({osc_compile_check_getgroups(), (int )0;})

extern int __attribute__((error("Compiler Assertion: gethostname len will always overflow dst"))) \
 osc_compile_check_gethostname(void);
#define OSC_ASSERT_gethostname() ({osc_compile_check_gethostname(), (int )0;})

extern int __attribute__((error("Compiler Assertion: gets len will always overflow dst"))) \
 osc_compile_check_gets(void);
#define OSC_ASSERT_gets() ({osc_compile_check_gets(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: getwd len will always overflow dst"))) \
 osc_compile_check_getwd(void);
#define OSC_ASSERT_getwd() ({osc_compile_check_getwd(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: mbsnrtowcs len will always overflow dst"))) \
 osc_compile_check_mbsnrtowcs(void);
#define OSC_ASSERT_mbsnrtowcs() ({osc_compile_check_mbsnrtowcs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: mbsrtowcs len will always overflow dst"))) \
 osc_compile_check_mbsrtowcs(void);
#define OSC_ASSERT_mbsrtowcs() ({osc_compile_check_mbsrtowcs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: mbstowcs len will always overflow dst"))) \
 osc_compile_check_mbstowcs(void);
#define OSC_ASSERT_mbstowcs() ({osc_compile_check_mbstowcs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: mempcpy len will always overflow dst"))) \
 osc_compile_check_mempcpy(void);
#define OSC_ASSERT_mempcpy() ({osc_compile_check_mempcpy(), (void *)0;})

extern int __attribute__((error("Compiler Assertion: poll len will always overflow dst"))) \
 osc_compile_check_poll(void);
#define OSC_ASSERT_poll() ({osc_compile_check_poll(), (int )0;})

extern int __attribute__((error("Compiler Assertion: ppoll len will always overflow dst"))) \
 osc_compile_check_ppoll(void);
#define OSC_ASSERT_ppoll() ({osc_compile_check_ppoll(), (int )0;})

extern int __attribute__((error("Compiler Assertion: pread len will always overflow dst"))) \
 osc_compile_check_pread(void);
#define OSC_ASSERT_pread() ({osc_compile_check_pread(), (ssize_t )0;})

extern int __attribute__((error("Compiler Assertion: read len will always overflow dst"))) \
 osc_compile_check_read(void);
#define OSC_ASSERT_read() ({osc_compile_check_read(), (ssize_t )0;})

extern int __attribute__((error("Compiler Assertion: readlinkat len will always overflow dst"))) \
 osc_compile_check_readlinkat(void);
#define OSC_ASSERT_readlinkat() ({osc_compile_check_readlinkat(), (int )0;})

extern int __attribute__((error("Compiler Assertion: readlink len will always overflow dst"))) \
 osc_compile_check_readlink(void);
#define OSC_ASSERT_readlink() ({osc_compile_check_readlink(), (ssize_t )0;})

extern int __attribute__((error("Compiler Assertion: realpath len will always overflow dst"))) \
 osc_compile_check_realpath(void);
#define OSC_ASSERT_realpath() ({osc_compile_check_realpath(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: recv len will always overflow dst"))) \
 osc_compile_check_recv(void);
#define OSC_ASSERT_recv() ({osc_compile_check_recv(), (ssize_t )0;})

extern int __attribute__((error("Compiler Assertion: recvfrom len will always overflow dst"))) \
 osc_compile_check_recvfrom(void);
#define OSC_ASSERT_recvfrom() ({osc_compile_check_recvfrom(), (ssize_t )0;})

extern int __attribute__((error("Compiler Assertion: stpcpy len will always overflow dst"))) \
 osc_compile_check_stpcpy(void);
#define OSC_ASSERT_stpcpy() ({osc_compile_check_stpcpy(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: stpncpy len will always overflow dst"))) \
 osc_compile_check_stpncpy(void);
#define OSC_ASSERT_stpncpy() ({osc_compile_check_stpncpy(), (char *)0;})

extern int __attribute__((error("Compiler Assertion: ttyname_r len will always overflow dst"))) \
 osc_compile_check_ttyname_r(void);
#define OSC_ASSERT_ttyname_r() ({osc_compile_check_ttyname_r(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vasprintf len will always overflow dst"))) \
 osc_compile_check_vasprintf(void);
#define OSC_ASSERT_vasprintf() ({osc_compile_check_vasprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vdprintf len will always overflow dst"))) \
 osc_compile_check_vdprintf(void);
#define OSC_ASSERT_vdprintf() ({osc_compile_check_vdprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vfprintf len will always overflow dst"))) \
 osc_compile_check_vfprintf(void);
#define OSC_ASSERT_vfprintf() ({osc_compile_check_vfprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vfwprintf len will always overflow dst"))) \
 osc_compile_check_vfwprintf(void);
#define OSC_ASSERT_vfwprintf() ({osc_compile_check_vfwprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vprintf len will always overflow dst"))) \
 osc_compile_check_vprintf(void);
#define OSC_ASSERT_vprintf() ({osc_compile_check_vprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vsprintf len will always overflow dst"))) \
 osc_compile_check_vsprintf(void);
#define OSC_ASSERT_vsprintf() ({osc_compile_check_vsprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vswprintf len will always overflow dst"))) \
 osc_compile_check_vswprintf(void);
#define OSC_ASSERT_vswprintf(chk) ({osc_compile_check_vswprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: vwprintf len will always overflow dst"))) \
 osc_compile_check_vwprintf(void);
#define OSC_ASSERT_vwprintf() ({osc_compile_check_vwprintf(), (int )0;})

extern int __attribute__((error("Compiler Assertion: wcpcpy len will always overflow dst"))) \
 osc_compile_check_wcpcpy(void);
#define OSC_ASSERT_wcpcpy() ({osc_compile_check_wcpcpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcpncpy len will always overflow dst"))) \
 osc_compile_check_wcpncpy(void);
#define OSC_ASSERT_wcpncpy() ({osc_compile_check_wcpncpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcrtomb len will always overflow dst"))) \
 osc_compile_check_wcrtomb(void);
#define OSC_ASSERT_wcrtomb() ({osc_compile_check_wcrtomb(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: wcscat len will always overflow dst"))) \
 osc_compile_check_wcscat(void);
#define OSC_ASSERT_wcscat() ({osc_compile_check_wcscat(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcscpy len will always overflow dst"))) \
 osc_compile_check_wcscpy(void);
#define OSC_ASSERT_wcscpy() ({osc_compile_check_wcscpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcsncat len will always overflow dst"))) \
 osc_compile_check_wcsncat(void);
#define OSC_ASSERT_wcsncat() ({osc_compile_check_wcsncat(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcsncpy len will always overflow dst"))) \
 osc_compile_check_wcsncpy(void);
#define OSC_ASSERT_wcsncpy() ({osc_compile_check_wcsncpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wcsnrtombs len will always overflow dst"))) \
 osc_compile_check_wcsnrtombs(void);
#define OSC_ASSERT_wcsnrtombs() ({osc_compile_check_wcsnrtombs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: wcsrtombs len will always overflow dst"))) \
 osc_compile_check_wcsrtombs(void);
#define OSC_ASSERT_wcsrtombs() ({osc_compile_check_wcsrtombs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: wcstombs len will always overflow dst"))) \
 osc_compile_check_wcstombs(void);
#define OSC_ASSERT_wcstombs() ({osc_compile_check_wcstombs(), (size_t )0;})

extern int __attribute__((error("Compiler Assertion: wctomb len will always overflow dst"))) \
 osc_compile_check_wctomb(void);
#define OSC_ASSERT_wctomb() ({osc_compile_check_wctomb(), (int )0;})

extern int __attribute__((error("Compiler Assertion: wmemcpy len will always overflow dst"))) \
 osc_compile_check_wmemcpy(void);
#define OSC_ASSERT_wmemcpy() ({osc_compile_check_wmemcpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wmemmove len will always overflow dst"))) \
 osc_compile_check_wmemmove(void);
#define OSC_ASSERT_wmemmove() ({osc_compile_check_wmemmove(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wmempcpy len will always overflow dst"))) \
 osc_compile_check_wmempcpy(void);
#define OSC_ASSERT_wmempcpy() ({osc_compile_check_wmempcpy(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: wmemset len will always overflow dst"))) \
 osc_compile_check_wmemset(void);
#define OSC_ASSERT_wmemset() ({osc_compile_check_wmemset(), (wchar_t *)0;})

extern int __attribute__((error("Compiler Assertion: snprintf len will always overflow dst"))) \
 osc_compile_check_snprintf(void);
#define OSC_ASSERT_snprintf(chk) ({osc_compile_check_snprintf(), (int)0;})

extern int __attribute__((error("Compiler Assertion: swprintf len will always overflow dst"))) \
 osc_compile_check_swprintf(void);
#define OSC_ASSERT_swprintf(chk) ({osc_compile_check_swprintf(), (int)0;})


#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_BUILTIN)

#define OSC_ASSERT_confstr() __confstr_chk(name, buf, len, _sz)
#define OSC_ASSERT_fgets(chk) __fgets_chk(s, size, stream, _sz)
#define OSC_ASSERT_fgets_unlocked(chk) __fgets_unlocked_chk(s, n, stream, _sz)
#define OSC_ASSERT_fgetws(chk) __fgetws_chk(ws, n, stream, _sz)
#define OSC_ASSERT_fgetws_unlocked(chk) __fgetws_unlocked_chk(ws, n, stream, _sz)
#define OSC_ASSERT_fread(chk) __fread_chk(ptr, size, nmemb, stream, _sz)
#define OSC_ASSERT_fread_unlocked(chk) __fread_unlocked_chk(ptr, size, n, stream, _sz)
#define OSC_ASSERT_getcwd() __getcwd_chk(buf, size, _sz)
#define OSC_ASSERT_getdomainname() __getdomainname_chk(name, len, _sz)
#define OSC_ASSERT_getgroups() __getgroups_chk(size, list, _sz)
#define OSC_ASSERT_gethostname() __gethostname_chk(name, len, _sz)
#define OSC_ASSERT_gets() __gets_chk(s, _sz)
#define OSC_ASSERT_getwd() __getwd_chk(buf, _sz)
#define OSC_ASSERT_mbsnrtowcs() __mbsnrtowcs_chk(dest, src, nms, len, ps, _sz)
#define OSC_ASSERT_mbsrtowcs() __mbsrtowcs_chk(dest, src, len, ps, _sz)
#define OSC_ASSERT_mbstowcs() __mbstowcs_chk(dest, src, n, _sz)
#define OSC_ASSERT_mempcpy() __mempcpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_poll() __poll_chk(fds, nfds, timeout, _sz)
#define OSC_ASSERT_ppoll() __ppoll_chk(fds, nfds, timeout_ts, sigmask, _sz)
#define OSC_ASSERT_pread() __pread_chk(fd, buf, count, offset, _sz)
#define OSC_ASSERT_read() __read_chk(fd, buf, count, _sz)
#define OSC_ASSERT_readlinkat() __readlinkat_chk(dirfd, pathname, buf, bufsiz, _sz)
#define OSC_ASSERT_readlink() __readlink_chk(path, buf, bufsiz, _sz)
#define OSC_ASSERT_realpath() __realpath_chk(path, resolved_path, _sz)
#define OSC_ASSERT_recv() __recv_chk(sockfd, buf, len, flags, _sz)
#define OSC_ASSERT_recvfrom() __recvfrom_chk(sockfd, buf, len, flags, src_addr, addrlen, _sz)
#define OSC_ASSERT_stpcpy() __stpcpy_chk(dest, src, _sz)
#define OSC_ASSERT_stpncpy() __stpncpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_ttyname_r() __ttyname_r_chk(fd, buf, buflen, _sz)
#define OSC_ASSERT_vasprintf() __vasprintf_chk(strp, fmt, ap, _sz)
#define OSC_ASSERT_vdprintf() __vdprintf_chk(fd, format, ap, _sz)
#define OSC_ASSERT_vfprintf() __vfprintf_chk(stream, format, ap, _sz)
#define OSC_ASSERT_vfwprintf() __vfwprintf_chk(stream, format, args, _sz)
#define OSC_ASSERT_vprintf() __vprintf_chk(format, ap, _sz)
#define OSC_ASSERT_vsprintf() __vsprintf_chk(str, format, ap, _sz)
#define OSC_ASSERT_vswprintf(chk) __vswprintf_chk(wcs, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, args)
#define OSC_ASSERT_vwprintf() __vwprintf_chk(format, args, _sz)
#define OSC_ASSERT_wcpcpy() __wcpcpy_chk(dest, src, _sz)
#define OSC_ASSERT_wcpncpy() __wcpncpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_wcrtomb() __wcrtomb_chk(s, wc, ps, _sz)
#define OSC_ASSERT_wcscat() __wcscat_chk(dest, src, _sz)
#define OSC_ASSERT_wcscpy() __wcscpy_chk(dest, src, _sz)
#define OSC_ASSERT_wcsncat() __wcsncat_chk(dest, src, n, _sz)
#define OSC_ASSERT_wcsncpy() __wcsncpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_wcsnrtombs() __wcsnrtombs_chk(dest, src, nwc, len, ps, _sz)
#define OSC_ASSERT_wcsrtombs() __wcsrtombs_chk(dest, src, len, ps, _sz)
#define OSC_ASSERT_wcstombs() __wcstombs_chk(dest, src, n, _sz)
#define OSC_ASSERT_wctomb() __wctomb_chk(s, wc, _sz)
#define OSC_ASSERT_wmemcpy() __wmemcpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_wmemmove() __wmemmove_chk(dest, src, n, _sz)
#define OSC_ASSERT_wmempcpy() __wmempcpy_chk(dest, src, n, _sz)
#define OSC_ASSERT_wmemset() __wmemset_chk(wcs, wc, n, _sz)
#ifdef __va_arg_pack
#define OSC_ASSERT_snprintf(chk) __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())
#define OSC_ASSERT_swprintf(chk) __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())
#else
#define OSC_ASSERT_snprintf(chk) __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1), __VA_ARGS__)
#define OSC_ASSERT_swprintf(chk) __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1)/sizeof(wchar_t), __VA_ARGS__)
#endif

#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_RUNTIME_CHK)

#define OSC_ASSERT_confstr() __openosc_confstr_to_buf(_sz, name, buf, len)
#define OSC_ASSERT_fgets(chk) __openosc_fgets_to_buf(_sz, chk, s, size, stream)
#define OSC_ASSERT_fgets_unlocked(chk) __openosc_fgets_unlocked_to_buf(_sz, chk, s, n, stream)
#define OSC_ASSERT_fgetws(chk) __openosc_fgetws_to_buf(_sz, chk, ws, n, stream)
#define OSC_ASSERT_fgetws_unlocked(chk) __openosc_fgetws_unlocked_to_buf(_sz, chk, ws, n, stream)
#define OSC_ASSERT_fread(chk) __openosc_fread_to_buf(_sz, chk, ptr, size, nmemb, stream)
#define OSC_ASSERT_fread_unlocked(chk) __openosc_fread_unlocked_to_buf(_sz, chk, ptr, size, n, stream)
#define OSC_ASSERT_getcwd() __openosc_getcwd_to_buf(_sz, buf, size)
#define OSC_ASSERT_getdomainname() __openosc_getdomainname_to_buf(_sz, name, len)
#define OSC_ASSERT_getgroups() __openosc_getgroups_to_buf(_sz, size, list)
#define OSC_ASSERT_gethostname() __openosc_gethostname_to_buf(_sz, name, len)
#define OSC_ASSERT_gets() __openosc_gets_to_buf(_sz, s)
#define OSC_ASSERT_getwd() __openosc_getwd_to_buf(_sz, buf)
#define OSC_ASSERT_mbsnrtowcs() __openosc_mbsnrtowcs_to_buf(_sz, dest, src, nms, len, ps)
#define OSC_ASSERT_mbsrtowcs() __openosc_mbsrtowcs_to_buf(_sz, dest, src, len, ps)
#define OSC_ASSERT_mbstowcs() __openosc_mbstowcs_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_mempcpy() __openosc_mempcpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_poll() __openosc_poll_to_buf(_sz, fds, nfds, timeout)
#define OSC_ASSERT_ppoll() __openosc_ppoll_to_buf(_sz, fds, nfds, timeout_ts, sigmask)
#define OSC_ASSERT_pread() __openosc_pread_to_buf(_sz, fd, buf, count, offset)
#define OSC_ASSERT_read() __openosc_read_to_buf(_sz, fd, buf, count)
#define OSC_ASSERT_readlinkat() __openosc_readlinkat_to_buf(_sz, dirfd, pathname, buf, bufsiz)
#define OSC_ASSERT_readlink() __openosc_readlink_to_buf(_sz, path, buf, bufsiz)
#define OSC_ASSERT_realpath() __openosc_realpath_to_buf(_sz, path, resolved_path)
#define OSC_ASSERT_recv() __openosc_recv_to_buf(_sz, sockfd, buf, len, flags)
#define OSC_ASSERT_recvfrom() __openosc_recvfrom_to_buf(_sz, sockfd, buf, len, flags, src_addr, addrlen)
#define OSC_ASSERT_stpcpy() __openosc_stpcpy_to_buf(_sz, dest, src)
#define OSC_ASSERT_stpncpy() __openosc_stpncpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_ttyname_r() __openosc_ttyname_r_to_buf(_sz, fd, buf, buflen)
#define OSC_ASSERT_vasprintf() __openosc_vasprintf_to_buf(_sz, strp, fmt, ap)
#define OSC_ASSERT_vdprintf() __openosc_vdprintf_to_buf(_sz, fd, format, ap)
#define OSC_ASSERT_vfprintf() __openosc_vfprintf_to_buf(_sz, stream, format, ap)
#define OSC_ASSERT_vfwprintf() __openosc_vfwprintf_to_buf(_sz, stream, format, args)
#define OSC_ASSERT_vprintf() __openosc_vprintf_to_buf(_sz, format, ap)
#define OSC_ASSERT_vsprintf() __openosc_vsprintf_to_buf(_sz, str, format, ap)
#define OSC_ASSERT_vswprintf(chk) __openosc_vswprintf_to_buf(_sz, chk, wcs, maxlen, format, args)
#define OSC_ASSERT_vwprintf() __openosc_vwprintf_to_buf(_sz, format, args)
#define OSC_ASSERT_wcpcpy() __openosc_wcpcpy_to_buf(_sz, dest, src)
#define OSC_ASSERT_wcpncpy() __openosc_wcpncpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wcrtomb() __openosc_wcrtomb_to_buf(_sz, s, wc, ps)
#define OSC_ASSERT_wcscat() __openosc_wcscat_to_buf(_sz, dest, src)
#define OSC_ASSERT_wcscpy() __openosc_wcscpy_to_buf(_sz, dest, src)
#define OSC_ASSERT_wcsncat() __openosc_wcsncat_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wcsncpy() __openosc_wcsncpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wcsnrtombs() __openosc_wcsnrtombs_to_buf(_sz, dest, src, nwc, len, ps)
#define OSC_ASSERT_wcsrtombs() __openosc_wcsrtombs_to_buf(_sz, dest, src, len, ps)
#define OSC_ASSERT_wcstombs() __openosc_wcstombs_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wctomb() __openosc_wctomb_to_buf(_sz, s, wc)
#define OSC_ASSERT_wmemcpy() __openosc_wmemcpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wmemmove() __openosc_wmemmove_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wmempcpy() __openosc_wmempcpy_to_buf(_sz, dest, src, n)
#define OSC_ASSERT_wmemset() __openosc_wmemset_to_buf(_sz, wcs, wc, n)
#ifdef __va_arg_pack
#define OSC_ASSERT_snprintf(chk) __openosc_snprintf_to_buf(_sz, chk, s, maxlen, format, __va_arg_pack ())
#define OSC_ASSERT_swprintf(chk) __openosc_swprintf_to_buf(_sz, chk, s, n, format, __va_arg_pack ())
#else
#define OSC_ASSERT_snprintf(chk) __openosc_snprintf_to_buf(__builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1), chk, s, maxlen, __VA_ARGS__)
#define OSC_ASSERT_swprintf(chk) __openosc_swprintf_to_buf(__builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1)/sizeof(wchar_t), chk, s, n, __VA_ARGS__)
#endif

#elif (OSC_COMPILE_CHK == OSC_ASSERT_USE_NONE)

#define OSC_ASSERT_confstr() confstr(name, buf, len)
#define OSC_ASSERT_fgets(chk) fgets(s, size, stream)
#define OSC_ASSERT_fgets_unlocked(chk) fgets_unlocked(s, n, stream)
#define OSC_ASSERT_fgetws(chk) fgetws(ws, n, stream)
#define OSC_ASSERT_fgetws_unlocked(chk) fgetws_unlocked(ws, n, stream)
#define OSC_ASSERT_fread(chk) fread(ptr, size, nmemb, stream)
#define OSC_ASSERT_fread_unlocked(chk) fread_unlocked(ptr, size, n, stream)
#define OSC_ASSERT_getcwd() getcwd(buf, size)
#define OSC_ASSERT_getdomainname() getdomainname(name, len)
#define OSC_ASSERT_getgroups() getgroups(size, list)
#define OSC_ASSERT_gethostname() gethostname(name, len)
#define OSC_ASSERT_gets() gets(s)
#define OSC_ASSERT_getwd() getwd(buf)
#define OSC_ASSERT_mbsnrtowcs() mbsnrtowcs(dest, src, nms, len, ps)
#define OSC_ASSERT_mbsrtowcs() mbsrtowcs(dest, src, len, ps)
#define OSC_ASSERT_mbstowcs() mbstowcs(dest, src, n)
#define OSC_ASSERT_mempcpy() mempcpy(dest, src, n)
#define OSC_ASSERT_poll() poll(fds, nfds, timeout)
#define OSC_ASSERT_ppoll() ppoll(fds, nfds, timeout_ts, sigmask)
#define OSC_ASSERT_pread() pread(fd, buf, count, offset)
#define OSC_ASSERT_read() read(fd, buf, count)
#define OSC_ASSERT_readlinkat() readlinkat(dirfd, pathname, buf, bufsiz)
#define OSC_ASSERT_readlink() readlink(path, buf, bufsiz)
#define OSC_ASSERT_realpath() realpath(path, resolved_path)
#define OSC_ASSERT_recv() recv(sockfd, buf, len, flags)
#define OSC_ASSERT_recvfrom() recvfrom(sockfd, buf, len, flags, src_addr, addrlen)
#define OSC_ASSERT_stpcpy() stpcpy(dest, src)
#define OSC_ASSERT_stpncpy() stpncpy(dest, src, n)
#define OSC_ASSERT_ttyname_r() ttyname_r(fd, buf, buflen)
#define OSC_ASSERT_vasprintf() vasprintf(strp, fmt, ap)
#define OSC_ASSERT_vdprintf() vdprintf(fd, format, ap)
#define OSC_ASSERT_vfprintf() vfprintf(stream, format, ap)
#define OSC_ASSERT_vfwprintf() vfwprintf(stream, format, args)
#define OSC_ASSERT_vprintf() vprintf(format, ap)
#define OSC_ASSERT_vsprintf() vsprintf(str, format, ap)
#define OSC_ASSERT_vswprintf(chk) vswprintf(wcs, maxlen, format, args)
#define OSC_ASSERT_vwprintf() vwprintf(format, args)
#define OSC_ASSERT_wcpcpy() wcpcpy(dest, src)
#define OSC_ASSERT_wcpncpy() wcpncpy(dest, src, n)
#define OSC_ASSERT_wcrtomb() wcrtomb(s, wc, ps)
#define OSC_ASSERT_wcscat() wcscat(dest, src)
#define OSC_ASSERT_wcscpy() wcscpy(dest, src)
#define OSC_ASSERT_wcsncat() wcsncat(dest, src, n)
#define OSC_ASSERT_wcsncpy() wcsncpy(dest, src, n)
#define OSC_ASSERT_wcsnrtombs() wcsnrtombs(dest, src, nwc, len, ps)
#define OSC_ASSERT_wcsrtombs() wcsrtombs(dest, src, len, ps)
#define OSC_ASSERT_wcstombs() wcstombs(dest, src, n)
#define OSC_ASSERT_wctomb() wctomb(s, wc)
#define OSC_ASSERT_wmemcpy() wmemcpy(dest, src, n)
#define OSC_ASSERT_wmemmove() wmemmove(dest, src, n)
#define OSC_ASSERT_wmempcpy() wmempcpy(dest, src, n)
#define OSC_ASSERT_wmemset() wmemset(wcs, wc, n)
#ifdef __va_arg_pack
#define OSC_ASSERT_snprintf(chk) snprintf(s, maxlen, format, __va_arg_pack ())
#define OSC_ASSERT_swprintf(chk) swprintf(s, n, format, __va_arg_pack ())
#else
#define OSC_ASSERT_snprintf(chk) snprintf(s, maxlen, __VA_ARGS__)
#define OSC_ASSERT_swprintf(chk) swprintf(s, n, __VA_ARGS__)
#endif

#else
#pragma message ("No compile time OSC checking method selected, contact jaguars-dev alias for guidance")
#endif


#ifndef OPENOSC_VALIST_NOSUPPORT

#ifdef __va_arg_pack

#ifndef OPENOSC_ASPRINTF_DISABLE

/* Mapping for asprintf */

extern int __asprintf_chk (char **result_ptr, int flags, const char *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_asprintf (char **result_ptr, const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (ASPRINTF_CASE4 __asprintf_chk(result_ptr, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (ASPRINTF_CASE4 asprintf(result_ptr, format, __va_arg_pack ()));
#endif
}

#undef asprintf
#define asprintf		openosc_asprintf

#endif /* OPENOSC_ASPRINTF_DISABLE */


/* Mapping for dprintf */

extern int __dprintf_chk (int d, int flags, const char *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_dprintf (int d, const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (DPRINTF_CASE4 __dprintf_chk(d, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (DPRINTF_CASE4 dprintf(d, format, __va_arg_pack ()));
#endif
}

#undef dprintf
#define dprintf		openosc_dprintf


/* Mapping for fprintf */

extern int __fprintf_chk (FILE *fp, int flag, const char *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_fprintf (FILE *fp, const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (FPRINTF_CASE4 __fprintf_chk(fp, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (FPRINTF_CASE4 fprintf(fp, format, __va_arg_pack ()));
#endif
}

#undef fprintf
#define fprintf		openosc_fprintf


/* Mapping for fwprintf */

extern int __fwprintf_chk (FILE *fp, int flag, const wchar_t *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_fwprintf (FILE *fp, const wchar_t *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (FWPRINTF_CASE4 __fwprintf_chk(fp, OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (FWPRINTF_CASE4 fwprintf(fp, format, __va_arg_pack ()));
#endif
}

#undef fwprintf
#define fwprintf		openosc_fwprintf


/* Mapping for printf */

extern int __printf_chk (int flag, const char *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_printf (const char *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (PRINTF_CASE4 __printf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (PRINTF_CASE4 printf(format, __va_arg_pack ()));
#endif
}

#undef printf
#define printf		openosc_printf


/* Mapping for snprintf */

extern int __snprintf_chk (char *s, size_t maxlen, int flags, size_t slen, const char *format, ...);
extern int __openosc_snprintf_to_buf (size_t destlen, int additional_chk, char *s, size_t maxlen, const char *format, ...);

static inline __attribute__ ((always_inline))
int 
openosc_snprintf (char *s, size_t maxlen, const char *format, ...)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(maxlen);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= maxlen)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (SNPRINTF_CASE1 __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
                  : (SNPRINTF_CASE2 OSC_ASSERT_snprintf(1)))
               : (SNPRINTF_CASE3 __openosc_snprintf_to_buf(_sz, 1, s, maxlen, format, __va_arg_pack ())))
            : (SNPRINTF_CASE4 __snprintf_chk(s, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
                  ? (SNPRINTF_CASE1 snprintf(s, maxlen, format, __va_arg_pack ()))
                  : (SNPRINTF_CASE2 OSC_ASSERT_snprintf(0)))
               : (SNPRINTF_CASE3 __openosc_snprintf_to_buf(_sz, 0, s, maxlen, format, __va_arg_pack ())))
            : (SNPRINTF_CASE4 snprintf(s, maxlen, format, __va_arg_pack ())));
#endif
}

#undef snprintf
#define snprintf		openosc_snprintf


/* Mapping for sprintf */

extern int __sprintf_chk (char *s, int flags, size_t slen, const char *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_sprintf (char *s, const char *format, ...)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
           ? (SPRINTF_CASE3 __sprintf_chk(s, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
           : (SPRINTF_CASE4 __sprintf_chk(s, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
           ? (SPRINTF_CASE3 sprintf(s, format, __va_arg_pack ()))
           : (SPRINTF_CASE4 sprintf(s, format, __va_arg_pack ())));
#endif
}

#undef sprintf
#define sprintf		openosc_sprintf


/* Mapping for swprintf */

extern int __swprintf_chk (wchar_t *s, size_t n, int flag, size_t s_len, const wchar_t *format, ...);
extern int __openosc_swprintf_to_buf (size_t destlen, int additional_chk, wchar_t *s, size_t n, const wchar_t *format, ...);

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
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (SWPRINTF_CASE1 __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ()))
                  : (SWPRINTF_CASE2 OSC_ASSERT_swprintf(1)))
               : (SWPRINTF_CASE3 __openosc_swprintf_to_buf(_sz, 1, s, n, format, __va_arg_pack ())))
            : (SWPRINTF_CASE4 __swprintf_chk(s, n, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, __va_arg_pack ())));
#else
                  ? (SWPRINTF_CASE1 swprintf(s, n, format, __va_arg_pack ()))
                  : (SWPRINTF_CASE2 OSC_ASSERT_swprintf(0)))
               : (SWPRINTF_CASE3 __openosc_swprintf_to_buf(_sz, 0, s, n, format, __va_arg_pack ())))
            : (SWPRINTF_CASE4 swprintf(s, n, format, __va_arg_pack ())));
#endif
}

#undef swprintf
#define swprintf		openosc_swprintf


/* Mapping for wprintf */

extern int __wprintf_chk (int flag, const wchar_t *format, ...); 

static inline __attribute__ ((always_inline))
int 
openosc_wprintf (const wchar_t *format, ...)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (WPRINTF_CASE4 __wprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, __va_arg_pack ()));
#else
    return (WPRINTF_CASE4 wprintf(format, __va_arg_pack ()));
#endif
}

#undef wprintf
#define wprintf		openosc_wprintf

#endif /* __va_arg_pack */

#endif /* OPENOSC_VALIST_NOSUPPORT */


/* Mapping for confstr */

extern size_t 
__openosc_confstr_to_buf(size_t dest_len, int name, char *buf, size_t len);

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
                  : (CONFSTR_CASE2 OSC_ASSERT_confstr()))
               : (CONFSTR_CASE3 OSC_RUNTIME_CHECK_confstr()))
            : (CONFSTR_CASE4 confstr(name, buf, len)));
}

#undef confstr
#define confstr(name, buf, len)		openosc_confstr(name, buf, len)


#ifndef OPENOSC_FGETS_DISABLE

/* Mapping for fgets */

extern char *
__fgets_chk (char *buf, size_t size, int n, FILE *fp);
extern char *
__openosc_fgets_to_buf(size_t dest_len, int additional_chk, char *s, int size, FILE *stream);

static inline __attribute__ ((always_inline)) char *
openosc_fgets (char *s, int size, FILE *stream)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((size>0 && _sz >= (size_t)size)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETS_CASE1 __fgets_chk(s, _sz, size, stream))
                  : (FGETS_CASE2 OSC_ASSERT_fgets(1)))
               : (FGETS_CASE3 OSC_RUNTIME_CHECK_fgets(1)))
            : (FGETS_CASE4 __fgets_chk(s, _sz, size, stream)));
#else
                  ? (FGETS_CASE1 fgets(s, size, stream))
                  : (FGETS_CASE2 OSC_ASSERT_fgets(0)))
               : (FGETS_CASE3 OSC_RUNTIME_CHECK_fgets(0)))
            : (FGETS_CASE4 fgets(s, size, stream)));
#endif
}

#undef fgets
#define fgets(s, size, stream)		openosc_fgets(s, size, stream)

#endif /* OPENOSC_FGETS_DISABLE */


/* Mapping for fgets_unlocked */

extern char *
__fgets_unlocked_chk (char *buf, size_t size, int n, FILE *fp);
extern char *
__openosc_fgets_unlocked_to_buf(size_t dest_len, int additional_chk, char *s, int n, FILE *stream);

static inline __attribute__ ((always_inline)) char *
openosc_fgets_unlocked (char *s, int n, FILE *stream)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETS_UNLOCKED_CASE1 __fgets_unlocked_chk(s, _sz, n, stream))
                  : (FGETS_UNLOCKED_CASE2 OSC_ASSERT_fgets_unlocked(1)))
               : (FGETS_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fgets_unlocked(1)))
            : (FGETS_UNLOCKED_CASE4 __fgets_unlocked_chk(s, _sz, n, stream)));
#else
                  ? (FGETS_UNLOCKED_CASE1 fgets_unlocked(s, n, stream))
                  : (FGETS_UNLOCKED_CASE2 OSC_ASSERT_fgets_unlocked(0)))
               : (FGETS_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fgets_unlocked(0)))
            : (FGETS_UNLOCKED_CASE4 fgets_unlocked(s, n, stream)));
#endif
}

#undef fgets_unlocked
#define fgets_unlocked(s, n, stream)		openosc_fgets_unlocked(s, n, stream)


/* Mapping for fgetws */

extern wchar_t *
__fgetws_chk (wchar_t *buf, size_t size, int n, FILE *fp);
extern wchar_t *
__openosc_fgetws_to_buf(size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream);

static inline __attribute__ ((always_inline)) wchar_t *
openosc_fgetws (wchar_t *ws, int n, FILE *stream)
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETWS_CASE1 __fgetws_chk(ws, _sz, n, stream))
                  : (FGETWS_CASE2 OSC_ASSERT_fgetws(1)))
               : (FGETWS_CASE3 OSC_RUNTIME_CHECK_fgetws(1)))
            : (FGETWS_CASE4 __fgetws_chk(ws, _sz, n, stream)));
#else
                  ? (FGETWS_CASE1 fgetws(ws, n, stream))
                  : (FGETWS_CASE2 OSC_ASSERT_fgetws(0)))
               : (FGETWS_CASE3 OSC_RUNTIME_CHECK_fgetws(0)))
            : (FGETWS_CASE4 fgetws(ws, n, stream)));
#endif
}

#undef fgetws
#define fgetws(ws, n, stream)		openosc_fgetws(ws, n, stream)


/* Mapping for fgetws_unlocked */

extern wchar_t *
__fgetws_unlocked_chk (wchar_t *buf, size_t size, int n, FILE *fp);
extern wchar_t *
__openosc_fgetws_unlocked_to_buf(size_t dest_len, int additional_chk, wchar_t *ws, int n, FILE *stream);

static inline __attribute__ ((always_inline)) wchar_t *
openosc_fgetws_unlocked (wchar_t *ws, int n, FILE *stream)
{
    size_t _sz_bytes = __builtin_object_size(ws, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz_bytes != (size_t) -1)
            ? (is_len_constant
               ? ((n>0 && _sz >= (size_t)n)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FGETWS_UNLOCKED_CASE1 __fgetws_unlocked_chk(ws, _sz, n, stream))
                  : (FGETWS_UNLOCKED_CASE2 OSC_ASSERT_fgetws_unlocked(1)))
               : (FGETWS_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fgetws_unlocked(1)))
            : (FGETWS_UNLOCKED_CASE4 __fgetws_unlocked_chk(ws, _sz, n, stream)));
#else
                  ? (FGETWS_UNLOCKED_CASE1 fgetws_unlocked(ws, n, stream))
                  : (FGETWS_UNLOCKED_CASE2 OSC_ASSERT_fgetws_unlocked(0)))
               : (FGETWS_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fgetws_unlocked(0)))
            : (FGETWS_UNLOCKED_CASE4 fgetws_unlocked(ws, n, stream)));
#endif
}

#undef fgetws_unlocked
#define fgetws_unlocked(ws, n, stream)		openosc_fgetws_unlocked(ws, n, stream)


/* Mapping for fread */

extern size_t
__fread_chk (void *__restrict ptr, size_t ptrlen,
             size_t size, size_t n, FILE *__restrict stream);
extern size_t 
__openosc_fread_to_buf(size_t dest_len, int additional_chk, void *ptr, size_t size, size_t nmemb, FILE *stream);

static inline __attribute__ ((always_inline)) size_t 
openosc_fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(size);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && __builtin_constant_p(nmemb)
               ? ((_sz >= size * nmemb)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FREAD_CASE1 __fread_chk(ptr, _sz, size, nmemb, stream))
                  : (FREAD_CASE2 OSC_ASSERT_fread(1)))
               : (FREAD_CASE3 OSC_RUNTIME_CHECK_fread(1)))
            : (FREAD_CASE4 __fread_chk(ptr, _sz, size, nmemb, stream)));
#else
                  ? (FREAD_CASE1 fread(ptr, size, nmemb, stream))
                  : (FREAD_CASE2 OSC_ASSERT_fread(0)))
               : (FREAD_CASE3 OSC_RUNTIME_CHECK_fread(0)))
            : (FREAD_CASE4 fread(ptr, size, nmemb, stream)));
#endif
}

#undef fread
#define fread(ptr, size, nmemb, stream)		openosc_fread(ptr, size, nmemb, stream)


#ifndef fread_unlocked

/* Mapping for fread_unlocked */

size_t
__fread_unlocked_chk (void *__restrict ptr, size_t ptrlen,
                      size_t size, size_t n, FILE *__restrict stream);
extern size_t 
__openosc_fread_unlocked_to_buf(size_t dest_len, int additional_chk, void *ptr, size_t size, size_t n, FILE *stream);

static inline __attribute__ ((always_inline)) size_t 
openosc_fread_unlocked (void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t _sz = __builtin_object_size(ptr, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(n);
    return ((_sz != (size_t) -1)
            ? (is_len_constant && __builtin_constant_p(size)
               ? ((_sz >= n * size)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (FREAD_UNLOCKED_CASE1 __fread_unlocked_chk(ptr, _sz, size, n, stream))
                  : (FREAD_UNLOCKED_CASE2 OSC_ASSERT_fread_unlocked(1)))
               : (FREAD_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fread_unlocked(1)))
            : (FREAD_UNLOCKED_CASE4 __fread_unlocked_chk(ptr, _sz, size, n, stream)));
#else
                  ? (FREAD_UNLOCKED_CASE1 fread_unlocked(ptr, size, n, stream))
                  : (FREAD_UNLOCKED_CASE2 OSC_ASSERT_fread_unlocked(0)))
               : (FREAD_UNLOCKED_CASE3 OSC_RUNTIME_CHECK_fread_unlocked(0)))
            : (FREAD_UNLOCKED_CASE4 fread_unlocked(ptr, size, n, stream)));
#endif
}

#undef fread_unlocked
#define fread_unlocked(ptr, size, n, stream)		openosc_fread_unlocked(ptr, size, n, stream)

#endif /* fread_unlocked */


#ifndef OPENOSC_GETCWD_DISABLE

/* Mapping for getcwd */

extern char *
__openosc_getcwd_to_buf(size_t dest_len, char *buf, size_t size);

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
                  : (GETCWD_CASE2 OSC_ASSERT_getcwd()))
               : (GETCWD_CASE3 OSC_RUNTIME_CHECK_getcwd()))
            : (GETCWD_CASE4 getcwd(buf, size)));
}

#undef getcwd
#define getcwd(buf, size)		openosc_getcwd(buf, size)

#endif /* OPENOSC_GETCWD_DISABLE */


/* Mapping for getdomainname */

extern int 
__openosc_getdomainname_to_buf(size_t dest_len, char *name, size_t len);

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
                  : (GETDOMAINNAME_CASE2 OSC_ASSERT_getdomainname()))
               : (GETDOMAINNAME_CASE3 OSC_RUNTIME_CHECK_getdomainname()))
            : (GETDOMAINNAME_CASE4 getdomainname(name, len)));
}

#undef getdomainname
#define getdomainname(name, len)		openosc_getdomainname(name, len)


/* Mapping for getgroups */

extern int 
__openosc_getgroups_to_buf(size_t dest_len, int size, gid_t list[]);

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
                  : (GETGROUPS_CASE2 OSC_ASSERT_getgroups()))
               : (GETGROUPS_CASE3 OSC_RUNTIME_CHECK_getgroups(_sz/sizeof(gid_t))))
            : (GETGROUPS_CASE4 getgroups(size, list)));
}

#undef getgroups
#define getgroups(size, list)		openosc_getgroups(size, list)


/* Mapping for gethostname */

extern int 
__openosc_gethostname_to_buf(size_t dest_len, char *name, size_t len);

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
                  : (GETHOSTNAME_CASE2 OSC_ASSERT_gethostname()))
               : (GETHOSTNAME_CASE3 OSC_RUNTIME_CHECK_gethostname()))
            : (GETHOSTNAME_CASE4 gethostname(name, len)));
}

#undef gethostname
#define gethostname(name, len)		openosc_gethostname(name, len)


#ifndef OPENOSC_GETS_DISABLE

#ifndef __cplusplus
/* Mapping for gets */

extern char *
__gets_chk (char *buf, size_t size);

static inline __attribute__ ((always_inline)) char *
openosc_gets (char *s)
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
            ? (GETS_CASE3 __gets_chk(s, _sz))
            : (GETS_CASE4 __gets_chk(s, _sz)));
#else
            ? (GETS_CASE3 gets(s))
            : (GETS_CASE4 gets(s)));
#endif
}

#undef gets
#define gets(s)		openosc_gets(s)
#endif /* __cplusplus */

#endif /* OPENOSC_GETS_DISABLE */


/* Mapping for getwd */

extern char *
__openosc_getwd_to_buf(size_t dest_len, char *buf);

static inline __attribute__ ((always_inline)) char *
openosc_getwd (char *buf)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (GETWD_CASE3 OSC_RUNTIME_CHECK_getwd())
            : (GETWD_CASE4 getwd(buf)));
}

#undef getwd
#define getwd(buf)		openosc_getwd(buf)


/* Mapping for mbsnrtowcs */

extern size_t 
__openosc_mbsnrtowcs_to_buf(size_t dest_len, wchar_t *dest, const char **src, size_t nms, size_t len, mbstate_t *ps);

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
                  : (MBSNRTOWCS_CASE2 OSC_ASSERT_mbsnrtowcs()))
               : (MBSNRTOWCS_CASE3 OSC_RUNTIME_CHECK_mbsnrtowcs()))
            : (MBSNRTOWCS_CASE4 mbsnrtowcs(dest, src, nms, len, ps)));
}

#undef mbsnrtowcs
#define mbsnrtowcs(dest, src, nms, len, ps)		openosc_mbsnrtowcs(dest, src, nms, len, ps)


/* Mapping for mbsrtowcs */

extern size_t 
__openosc_mbsrtowcs_to_buf(size_t dest_len, wchar_t *dest, const char **src, size_t len, mbstate_t *ps);

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
                  : (MBSRTOWCS_CASE2 OSC_ASSERT_mbsrtowcs()))
               : (MBSRTOWCS_CASE3 OSC_RUNTIME_CHECK_mbsrtowcs()))
            : (MBSRTOWCS_CASE4 mbsrtowcs(dest, src, len, ps)));
}

#undef mbsrtowcs
#define mbsrtowcs(dest, src, len, ps)		openosc_mbsrtowcs(dest, src, len, ps)


/* Mapping for mbstowcs */

extern size_t 
__openosc_mbstowcs_to_buf(size_t dest_len, wchar_t *dest, const char *src, size_t n);

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
                  : (MBSTOWCS_CASE2 OSC_ASSERT_mbstowcs()))
               : (MBSTOWCS_CASE3 OSC_RUNTIME_CHECK_mbstowcs()))
            : (MBSTOWCS_CASE4 mbstowcs(dest, src, n)));
}

#undef mbstowcs
#define mbstowcs(dest, src, n)		openosc_mbstowcs(dest, src, n)


#ifndef OPENOSC_MEMPCPY_DISABLE

/* Mapping for mempcpy */

extern void *
__openosc_mempcpy_to_buf(size_t dest_len, void *dest, const void *src, size_t n);

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
                  : (MEMPCPY_CASE2 OSC_ASSERT_mempcpy()))
               : (MEMPCPY_CASE3 OSC_RUNTIME_CHECK_mempcpy()))
            : (MEMPCPY_CASE4 mempcpy(dest, src, n)));
}

#undef mempcpy
#define mempcpy(dest, src, n)		openosc_mempcpy(dest, src, n)

#endif /* OPENOSC_MEMPCPY_DISABLE */


#ifndef OPENOSC_POLL_DISABLE

/* Mapping for poll */

extern int 
__openosc_poll_to_buf(size_t dest_len, struct pollfd *fds, nfds_t nfds, int timeout);

static inline __attribute__ ((always_inline)) int 
openosc_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (POLL_CASE1 poll(fds, nfds, timeout))
                  : (POLL_CASE2 OSC_ASSERT_poll()))
               : (POLL_CASE3 OSC_RUNTIME_CHECK_poll()))
            : (POLL_CASE4 poll(fds, nfds, timeout)));
}

#undef poll
#define poll(fds, nfds, timeout)		openosc_poll(fds, nfds, timeout)

#endif /* OPENOSC_POLL_DISABLE */


#ifndef OPENOSC_PPOLL_DISABLE

/* Mapping for ppoll */

extern int 
__openosc_ppoll_to_buf(size_t dest_len, struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask);

static inline __attribute__ ((always_inline)) int 
openosc_ppoll (struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    size_t _sz = __builtin_object_size(fds, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(nfds);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= nfds * (sizeof(int) + sizeof(short) + sizeof(short)))
                  ? (PPOLL_CASE1 ppoll(fds, nfds, timeout_ts, sigmask))
                  : (PPOLL_CASE2 OSC_ASSERT_ppoll()))
               : (PPOLL_CASE3 OSC_RUNTIME_CHECK_ppoll()))
            : (PPOLL_CASE4 ppoll(fds, nfds, timeout_ts, sigmask)));
}

#undef ppoll
#define ppoll(fds, nfds, timeout_ts, sigmask)		openosc_ppoll(fds, nfds, timeout_ts, sigmask)

#endif /* OPENOSC_PPOLL_DISABLE */


#ifndef OPENOSC_PREAD_DISABLE

/* Mapping for pread */

extern ssize_t 
__openosc_pread_to_buf(size_t dest_len, int fd, void *buf, size_t count, off_t offset);

static inline __attribute__ ((always_inline)) ssize_t 
openosc_pread (int fd, void *buf, size_t count, off_t offset)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (PREAD_CASE1 pread(fd, buf, count, offset))
                  : (PREAD_CASE2 OSC_ASSERT_pread()))
               : (PREAD_CASE3 OSC_RUNTIME_CHECK_pread()))
            : (PREAD_CASE4 pread(fd, buf, count, offset)));
}

#undef pread
#define pread(fd, buf, count, offset)		openosc_pread(fd, buf, count, offset)

#endif /* OPENOSC_PREAD_DISABLE */


#ifndef OPENOSC_READ_DISABLE

#ifndef __cplusplus
/* Mapping for read */

extern ssize_t 
__openosc_read_to_buf(size_t dest_len, int fd, void *buf, size_t count);

static inline __attribute__ ((always_inline)) ssize_t 
openosc_read (int fd, void *buf, size_t count)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(count);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= count)
                  ? (READ_CASE1 read(fd, buf, count))
                  : (READ_CASE2 OSC_ASSERT_read()))
               : (READ_CASE3 OSC_RUNTIME_CHECK_read()))
            : (READ_CASE4 read(fd, buf, count)));
}

#undef read
#define read(fd, buf, count)		openosc_read(fd, buf, count)
#endif /* __cplusplus */

#endif /* OPENOSC_READ_DISABLE */


/* Mapping for readlinkat */

extern ssize_t
__openosc_readlinkat_to_buf(size_t dest_len, int dirfd, const char *pathname, char *buf, size_t bufsiz);

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
                  : (READLINKAT_CASE2 OSC_ASSERT_readlinkat()))
               : (READLINKAT_CASE3 OSC_RUNTIME_CHECK_readlinkat()))
            : (READLINKAT_CASE4 readlinkat(dirfd, pathname, buf, bufsiz)));
}

#undef readlinkat
#define readlinkat(dirfd, pathname, buf, bufsiz)		openosc_readlinkat(dirfd, pathname, buf, bufsiz)


/* Mapping for readlink */

extern ssize_t 
__openosc_readlink_to_buf(size_t dest_len, const char *path, char *buf, size_t bufsiz);

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
                  : (READLINK_CASE2 OSC_ASSERT_readlink()))
               : (READLINK_CASE3 OSC_RUNTIME_CHECK_readlink()))
            : (READLINK_CASE4 readlink(path, buf, bufsiz)));
}

#undef readlink
#define readlink(path, buf, bufsiz)		openosc_readlink(path, buf, bufsiz)


/* Mapping for realpath */

extern char *
__openosc_realpath_to_buf(size_t dest_len, const char *path, char *resolved_path);

static inline __attribute__ ((always_inline)) char *
openosc_realpath (const char *path, char *resolved_path)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(resolved_path, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (REALPATH_CASE3 OSC_RUNTIME_CHECK_realpath())
            : (REALPATH_CASE4 realpath(path, resolved_path)));
}

#undef realpath
#define realpath(path, resolved_path)		openosc_realpath(path, resolved_path)


#ifndef OPENOSC_RECV_DISABLE

/* Mapping for recv */

extern ssize_t 
__openosc_recv_to_buf(size_t dest_len, int sockfd, void *buf, size_t len, int flags);

static inline __attribute__ ((always_inline)) ssize_t 
openosc_recv (int sockfd, void *buf, size_t len, int flags)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECV_CASE1 recv(sockfd, buf, len, flags))
                  : (RECV_CASE2 OSC_ASSERT_recv()))
               : (RECV_CASE3 OSC_RUNTIME_CHECK_recv()))
            : (RECV_CASE4 recv(sockfd, buf, len, flags)));
}

#undef recv
#define recv(sockfd, buf, len, flags)		openosc_recv(sockfd, buf, len, flags)

#endif /* OPENOSC_RECV_DISABLE */


#ifndef OPENOSC_RECVFROM_DISABLE

/* Mapping for recvfrom */

extern ssize_t 
__openosc_recvfrom_to_buf(size_t dest_len, int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

static inline __attribute__ ((always_inline)) ssize_t 
openosc_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    size_t _sz = __builtin_object_size(buf, OSC_OBJECT_SIZE_CHECK_0);
    int is_len_constant = __builtin_constant_p(len);
    return ((_sz != (size_t) -1)
            ? (is_len_constant
               ? ((_sz >= len)
                  ? (RECVFROM_CASE1 recvfrom(sockfd, buf, len, flags, src_addr, addrlen))
                  : (RECVFROM_CASE2 OSC_ASSERT_recvfrom()))
               : (RECVFROM_CASE3 OSC_RUNTIME_CHECK_recvfrom()))
            : (RECVFROM_CASE4 recvfrom(sockfd, buf, len, flags, src_addr, addrlen)));
}

#undef recvfrom
#define recvfrom(sockfd, buf, len, flags, src_addr, addrlen)		openosc_recvfrom(sockfd, buf, len, flags, src_addr, addrlen)

#endif /* OPENOSC_RECVFROM_DISABLE */


/* Mapping for stpcpy */

extern char *
__openosc_stpcpy_to_buf(size_t dest_len, char *dest, const char *src);

static inline __attribute__ ((always_inline)) char *
openosc_stpcpy (char *dest, const char *src)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (STPCPY_CASE3 OSC_RUNTIME_CHECK_stpcpy())
            : (STPCPY_CASE4 stpcpy(dest, src)));
}

#undef stpcpy
#define stpcpy(dest, src)		openosc_stpcpy(dest, src)


/* Mapping for stpncpy */

extern char *
__openosc_stpncpy_to_buf(size_t dest_len, char *dest, const char *src, size_t n);

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
                  : (STPNCPY_CASE2 OSC_ASSERT_stpncpy()))
               : (STPNCPY_CASE3 OSC_RUNTIME_CHECK_stpncpy()))
            : (STPNCPY_CASE4 stpncpy(dest, src, n)));
}

#undef stpncpy
#define stpncpy(dest, src, n)		openosc_stpncpy(dest, src, n)


/* Mapping for ttyname_r */

extern int 
__openosc_ttyname_r_to_buf(size_t dest_len, int fd, char *buf, size_t buflen);

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
                  : (TTYNAME_R_CASE2 OSC_ASSERT_ttyname_r()))
               : (TTYNAME_R_CASE3 OSC_RUNTIME_CHECK_ttyname_r()))
            : (TTYNAME_R_CASE4 ttyname_r(fd, buf, buflen)));
}

#undef ttyname_r
#define ttyname_r(fd, buf, buflen)		openosc_ttyname_r(fd, buf, buflen)


#ifndef OPENOSC_VALIST_NOSUPPORT

/* Mapping for vasprintf */

extern int
__vasprintf_chk (char **result_ptr, int flags, const char *format,
                 va_list args);

static inline __attribute__ ((always_inline)) int 
openosc_vasprintf (char **strp, const char *fmt, va_list ap)
  OSC_THROW
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VASPRINTF_CASE4 __vasprintf_chk(strp, OPENOSC_USE_FORTIFY_LEVEL - 1, fmt, ap));
#else
    return (VASPRINTF_CASE4 vasprintf(strp, fmt, ap));
#endif
}

#undef vasprintf
#define vasprintf(strp, fmt, ap)		openosc_vasprintf(strp, fmt, ap)


/* Mapping for vdprintf */

extern int
__vdprintf_chk (int d, int flags, const char *format, va_list arg);

static inline __attribute__ ((always_inline)) int 
openosc_vdprintf (int fd, const char *format, va_list ap)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VDPRINTF_CASE4 __vdprintf_chk(fd, OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VDPRINTF_CASE4 vdprintf(fd, format, ap));
#endif
}

#undef vdprintf
#define vdprintf(fd, format, ap)		openosc_vdprintf(fd, format, ap)


/* Mapping for vfwprintf */

extern int
__vfwprintf_chk (FILE *fp, int flag, const wchar_t *format, va_list ap);

static inline __attribute__ ((always_inline)) int 
openosc_vfwprintf (FILE *stream, const wchar_t *format, va_list args)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VFWPRINTF_CASE4 __vfwprintf_chk(stream, OPENOSC_USE_FORTIFY_LEVEL - 1, format, args));
#else
    return (VFWPRINTF_CASE4 vfwprintf(stream, format, args));
#endif
}

#undef vfwprintf
#define vfwprintf(stream, format, args)		openosc_vfwprintf(stream, format, args)


/* bits/stdio.h:36 has a define for vprintf, causing redefinition error */
#ifndef __USE_EXTERN_INLINES

#ifndef OPENOSC_VPRINTF_DISABLE

/* Mapping for vprintf */

extern int
__vprintf_chk (int flag, const char *format, va_list ap);

static inline __attribute__ ((always_inline)) int 
openosc_vprintf (const char *format, va_list ap)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VPRINTF_CASE4 __vprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VPRINTF_CASE4 vprintf(format, ap));
#endif
}

#undef vprintf
#define vprintf(format, ap)		openosc_vprintf(format, ap)

#endif /* OPENOSC_VPRINTF_DISABLE */


/* Mapping for vfprintf */

extern int
__vfprintf_chk (FILE *fp, int flag, const char *format, va_list ap);

static inline __attribute__ ((always_inline)) int 
openosc_vfprintf (FILE *stream, const char *format, va_list ap)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VFPRINTF_CASE4 __vfprintf_chk(stream, OPENOSC_USE_FORTIFY_LEVEL - 1, format, ap));
#else
    return (VFPRINTF_CASE4 vfprintf(stream, format, ap));
#endif
}

#undef vfprintf
#define vfprintf(stream, format, ap)		openosc_vfprintf(stream, format, ap)

#endif  /* __USE_EXTERN_INLINES */


/* Mapping for vsprintf */

extern int
__vsprintf_chk (char *s, int flags, size_t slen, const char *format,
                va_list args);

static inline __attribute__ ((always_inline)) int 
openosc_vsprintf (char *str, const char *format, va_list ap)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(str, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
            ? (VSPRINTF_CASE3 __vsprintf_chk(str, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, ap))
            : (VSPRINTF_CASE4 __vsprintf_chk(str, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, ap)));
#else
            ? (VSPRINTF_CASE3 vsprintf(str, format, ap))
            : (VSPRINTF_CASE4 vsprintf(str, format, ap)));
#endif
}

#undef vsprintf
#define vsprintf(str, format, ap)		openosc_vsprintf(str, format, ap)


/* Mapping for vswprintf */

extern int
__vswprintf_chk (wchar_t *s, size_t maxlen, int flags, size_t slen,
                 const wchar_t *format, va_list args);
extern int 
__openosc_vswprintf_to_buf(size_t dest_len, int additional_chk, wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args);

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
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
                  ? (VSWPRINTF_CASE1 __vswprintf_chk(wcs, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, args))
                  : (VSWPRINTF_CASE2 OSC_ASSERT_vswprintf(1)))
               : (VSWPRINTF_CASE3 OSC_RUNTIME_CHECK_vswprintf(1)))
            : (VSWPRINTF_CASE4 __vswprintf_chk(wcs, maxlen, OPENOSC_USE_FORTIFY_LEVEL - 1, _sz, format, args)));
#else
                  ? (VSWPRINTF_CASE1 vswprintf(wcs, maxlen, format, args))
                  : (VSWPRINTF_CASE2 OSC_ASSERT_vswprintf(0)))
               : (VSWPRINTF_CASE3 OSC_RUNTIME_CHECK_vswprintf(0)))
            : (VSWPRINTF_CASE4 vswprintf(wcs, maxlen, format, args)));
#endif
}

#undef vswprintf
#define vswprintf(wcs, maxlen, format, args)		openosc_vswprintf(wcs, maxlen, format, args)


/* Mapping for vwprintf */

extern int
__vwprintf_chk (int flag, const wchar_t *format, va_list ap);

static inline __attribute__ ((always_inline)) int 
openosc_vwprintf (const wchar_t *format, va_list args)
{
#ifdef OPENOSC_GLIBC_ADDITIONAL_CHK
    return (VWPRINTF_CASE4 __vwprintf_chk(OPENOSC_USE_FORTIFY_LEVEL - 1, format, args));
#else
    return (VWPRINTF_CASE4 vwprintf(format, args));
#endif
}

#undef vwprintf
#define vwprintf(format, args)		openosc_vwprintf(format, args)

#endif /* OPENOSC_VALIST_NOSUPPORT */

/* Mapping for wcpcpy */

extern wchar_t *
__openosc_wcpcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcpcpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCPCPY_CASE3 OSC_RUNTIME_CHECK_wcpcpy())
            : (WCPCPY_CASE4 wcpcpy(dest, src)));
}

#undef wcpcpy
#define wcpcpy(dest, src)		openosc_wcpcpy(dest, src)


/* Mapping for wcpncpy */

extern wchar_t *
__openosc_wcpncpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WCPNCPY_CASE2 OSC_ASSERT_wcpncpy()))
               : (WCPNCPY_CASE3 OSC_RUNTIME_CHECK_wcpncpy()))
            : (WCPNCPY_CASE4 wcpncpy(dest, src, n)));
}

#undef wcpncpy
#define wcpncpy(dest, src, n)		openosc_wcpncpy(dest, src, n)


/* Mapping for wcrtomb */

extern size_t 
__openosc_wcrtomb_to_buf(size_t dest_len, char *s, wchar_t wc, mbstate_t *ps);

static inline __attribute__ ((always_inline)) size_t 
openosc_wcrtomb (char *s, wchar_t wc, mbstate_t *ps)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCRTOMB_CASE3 OSC_RUNTIME_CHECK_wcrtomb())
            : (WCRTOMB_CASE4 wcrtomb(s, wc, ps)));
}

#undef wcrtomb
#define wcrtomb(s, wc, ps)		openosc_wcrtomb(s, wc, ps)


/* Mapping for wcscat */

extern wchar_t *
__openosc_wcscat_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcscat (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCAT_CASE3 OSC_RUNTIME_CHECK_wcscat())
            : (WCSCAT_CASE4 wcscat(dest, src)));
}

#undef wcscat
#define wcscat(dest, src)		openosc_wcscat(dest, src)


#ifndef OPENOSC_WCSCPY_DISABLE

/* Mapping for wcscpy */

extern wchar_t *
__openosc_wcscpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src);

static inline __attribute__ ((always_inline)) wchar_t *
openosc_wcscpy (wchar_t *dest, const wchar_t *src)
  OSC_THROW
{
    size_t _sz_bytes = __builtin_object_size(dest, OSC_OBJECT_SIZE_CHECK_1);
    size_t _sz = _sz_bytes / sizeof(wchar_t);
    return ((_sz_bytes != (size_t) -1)
            ? (WCSCPY_CASE3 OSC_RUNTIME_CHECK_wcscpy())
            : (WCSCPY_CASE4 wcscpy(dest, src)));
}

#undef wcscpy
#define wcscpy(dest, src)		openosc_wcscpy(dest, src)

#endif /* OPENOSC_WCSCPY_DISABLE */


/* Mapping for wcsncat */

extern wchar_t *
__openosc_wcsncat_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WCSNCAT_CASE2 OSC_ASSERT_wcsncat()))
               : (WCSNCAT_CASE3 OSC_RUNTIME_CHECK_wcsncat()))
            : (WCSNCAT_CASE4 wcsncat(dest, src, n)));
}

#undef wcsncat
#define wcsncat(dest, src, n)		openosc_wcsncat(dest, src, n)


/* Mapping for wcsncpy */

extern wchar_t *
__openosc_wcsncpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WCSNCPY_CASE2 OSC_ASSERT_wcsncpy()))
               : (WCSNCPY_CASE3 OSC_RUNTIME_CHECK_wcsncpy()))
            : (WCSNCPY_CASE4 wcsncpy(dest, src, n)));
}

#undef wcsncpy
#define wcsncpy(dest, src, n)		openosc_wcsncpy(dest, src, n)


/* Mapping for wcsnrtombs */

extern size_t 
__openosc_wcsnrtombs_to_buf(size_t dest_len, char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps);

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
                  : (WCSNRTOMBS_CASE2 OSC_ASSERT_wcsnrtombs()))
               : (WCSNRTOMBS_CASE3 OSC_RUNTIME_CHECK_wcsnrtombs()))
            : (WCSNRTOMBS_CASE4 wcsnrtombs(dest, src, nwc, len, ps)));
}

#undef wcsnrtombs
#define wcsnrtombs(dest, src, nwc, len, ps)		openosc_wcsnrtombs(dest, src, nwc, len, ps)


/* Mapping for wcsrtombs */

extern size_t 
__openosc_wcsrtombs_to_buf(size_t dest_len, char *dest, const wchar_t **src, size_t len, mbstate_t *ps);

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
                  : (WCSRTOMBS_CASE2 OSC_ASSERT_wcsrtombs()))
               : (WCSRTOMBS_CASE3 OSC_RUNTIME_CHECK_wcsrtombs()))
            : (WCSRTOMBS_CASE4 wcsrtombs(dest, src, len, ps)));
}

#undef wcsrtombs
#define wcsrtombs(dest, src, len, ps)		openosc_wcsrtombs(dest, src, len, ps)


/* Mapping for wcstombs */

extern size_t 
__openosc_wcstombs_to_buf(size_t dest_len, char *dest, const wchar_t *src, size_t n);

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
                  : (WCSTOMBS_CASE2 OSC_ASSERT_wcstombs()))
               : (WCSTOMBS_CASE3 OSC_RUNTIME_CHECK_wcstombs()))
            : (WCSTOMBS_CASE4 wcstombs(dest, src, n)));
}

#undef wcstombs
#define wcstombs(dest, src, n)		openosc_wcstombs(dest, src, n)


/* Mapping for wctomb */

extern int 
__openosc_wctomb_to_buf(size_t dest_len, char *s, wchar_t wc);

static inline __attribute__ ((always_inline)) int 
openosc_wctomb (char *s, wchar_t wc)
  OSC_THROW
{
    size_t _sz = __builtin_object_size(s, OSC_OBJECT_SIZE_CHECK_1);
    return ((_sz != (size_t) -1)
            ? (WCTOMB_CASE3 OSC_RUNTIME_CHECK_wctomb())
            : (WCTOMB_CASE4 wctomb(s, wc)));
}

#undef wctomb
#define wctomb(s, wc)		openosc_wctomb(s, wc)


/* Mapping for wmemcpy */

extern wchar_t *
__openosc_wmemcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WMEMCPY_CASE2 OSC_ASSERT_wmemcpy()))
               : (WMEMCPY_CASE3 OSC_RUNTIME_CHECK_wmemcpy()))
            : (WMEMCPY_CASE4 wmemcpy(dest, src, n)));
}

#undef wmemcpy
#define wmemcpy(dest, src, n)		openosc_wmemcpy(dest, src, n)


/* Mapping for wmemmove */

extern wchar_t *
__openosc_wmemmove_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WMEMMOVE_CASE2 OSC_ASSERT_wmemmove()))
               : (WMEMMOVE_CASE3 OSC_RUNTIME_CHECK_wmemmove()))
            : (WMEMMOVE_CASE4 wmemmove(dest, src, n)));
}

#undef wmemmove
#define wmemmove(dest, src, n)		openosc_wmemmove(dest, src, n)


/* Mapping for wmempcpy */

extern wchar_t *
__openosc_wmempcpy_to_buf(size_t dest_len, wchar_t *dest, const wchar_t *src, size_t n);

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
                  : (WMEMPCPY_CASE2 OSC_ASSERT_wmempcpy()))
               : (WMEMPCPY_CASE3 OSC_RUNTIME_CHECK_wmempcpy()))
            : (WMEMPCPY_CASE4 wmempcpy(dest, src, n)));
}

#undef wmempcpy
#define wmempcpy(dest, src, n)		openosc_wmempcpy(dest, src, n)


/* Mapping for wmemset */

extern wchar_t *
__openosc_wmemset_to_buf(size_t dest_len, wchar_t *wcs, wchar_t wc, size_t n);

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
                  : (WMEMSET_CASE2 OSC_ASSERT_wmemset()))
               : (WMEMSET_CASE3 OSC_RUNTIME_CHECK_wmemset()))
            : (WMEMSET_CASE4 wmemset(wcs, wc, n)));
}

#undef wmemset
#define wmemset(wcs, wc, n)		openosc_wmemset(wcs, wc, n)

#endif  /* ifndef __OPENOSC_FORTIFY_REDEFINE_NOMAP_H__ */

#endif  /* __OPENOSC_FORTIFY_REDEFINE_MAP_H__ */
