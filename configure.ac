AC_PREREQ([2.69])
AC_INIT([openosc], [m4_esyscmd_s(cat VERSION)], [yonhan@cisco.com])
AC_CONFIG_AUX_DIR([build-tools])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_ARG_ENABLE([safec],
    AS_HELP_STRING([--disable-safec], [Disable feature SafeC]))
AS_IF([test "x$enable_safec" != "xno"],
 [AC_MSG_NOTICE([The safec feature is not disabled])],
 [AC_MSG_NOTICE([The safec feature is disabled])])
AC_CHECK_LIB([dl], [dladdr])
AC_CHECK_LIB([ciscosafec], [memcpy_s])
AC_CHECK_HEADERS([safe_lib.h])
AC_CHECK_HEADERS([safec/safe_lib.h])
AM_CONDITIONAL([OPENOSC_TEST_CXX_PROG], [test "x$ac_cv_prog_cxx_g" = xyes])
AM_COND_IF([OPENOSC_TEST_CXX_PROG],
 [AC_MSG_NOTICE([The unit-test C++ code coverage is ON])],
 [AC_MSG_NOTICE([The unit-test C++ code coverage is OFF])])
AM_CONDITIONAL([HAS_SAFEC], [test "x$enable_safec" != xno -a "x$ac_cv_lib_ciscosafec_memcpy_s" = xyes -a "x$ac_cv_header_safe_lib_h" = xyes -o "x$ac_cv_lib_ciscosafec_memcpy_s" = xyes -a "x$ac_cv_header_safec_safe_lib_h" = xyes])
AM_COND_IF([HAS_SAFEC],
 [AC_MSG_NOTICE([The safec coverage is ON])],
 [AC_MSG_NOTICE([The safec coverage is OFF])])
AM_CONDITIONAL([OPENOSC_TEST_HARNESS_WANT_COMPILE_TIME_CHECK], [test a = b])
LT_INIT
LT_VERSION_NUMBER="0:0:0"
AC_SUBST(LT_VERSION_NUMBER)
#AC_SUBST(OPENOSC_CFLAGS, [-fsanitize=address])
AC_SUBST(OPENOSC_CFLAGS, ["-Wsign-compare -U_FORTIFY_SOURCE -fno-stack-protector"])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 test/Makefile
 tools/Makefile
])
AC_OUTPUT
