TESTS = openosc_test openosc_test_chk openosc_test_nomap openosc_test_asan openosc_test_msan
# test_harness takes longer time to complete, and openosc_fortify_test/openosc_test_cpp sometimes causes segmentation fault.
#TESTS = openosc_test openosc_test_chk openosc_test_nomap openosc_test_asan openosc_test_msan openosc_test_cpp test_harness openosc_fortify_test
check_PROGRAMS = openosc_test openosc_test_chk openosc_test_nomap openosc_test_asan openosc_test_msan test_harness openosc_fortify_test openosc_fortify_nomap_test
if OPENOSC_TEST_CXX_PROG
check_PROGRAMS += openosc_test_cpp
endif
if OPENOSC_TEST_HARNESS_WANT_COMPILE_TIME_CHECK
check_PROGRAMS += test_harness_break
endif

openosc_test_SOURCES = openosc_test.c
openosc_test_nomap_SOURCES = openosc_test_nomap.c
openosc_test_chk_SOURCES = openosc_test_chk.c
openosc_test_asan_SOURCES = openosc_test_asan.c
openosc_test_msan_SOURCES = openosc_test_msan.c
openosc_fortify_test_SOURCES = openosc_fortify_test.c
openosc_fortify_nomap_test_SOURCES = openosc_fortify_test.c
openosc_test_cpp_SOURCES = openosc_test_cpp.cpp
if HAS_SAFEC
test_harness_SOURCES = test_harness_aux.c  test_harness_bosc.c  test_harness_bosc_safec.c  test_harness_bosc_utils.c  test_harness.c   test_harness_aux.h  test_harness_bosc.h  test_harness_defs.h
test_harness_break_SOURCES = test_harness_compile_check.c test_harness_compile_check_safec.c  test_harness_aux.h  test_harness_bosc.h  test_harness_defs.h
test_harness_CFLAGS = -DHAS_SAFEC $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS) -DBOSC_TH_COMPILER_VERSION='"$(CC) CFLAGS=$(CFLAGS)"'
test_harness_break_CFLAGS = -DHAS_SAFEC $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
else
test_harness_SOURCES = test_harness_aux.c  test_harness_bosc.c  test_harness_bosc_utils.c  test_harness.c  test_harness_aux.h  test_harness_bosc.h  test_harness_defs.h
test_harness_break_SOURCES = test_harness_compile_check.c  test_harness_aux.h  test_harness_bosc.h  test_harness_defs.h
test_harness_CFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS) -DBOSC_TH_COMPILER_VERSION='"$(CC) CFLAGS=$(CFLAGS)"'
test_harness_break_CFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
endif

OPENOSCTEST_CFLAGS = -I../include -include ../include/openosc.h -DOPENOSC_OVERFLOW_ERROR_OUT_DISABLE
openosc_test_nomap_CFLAGS = -fno-inline $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
openosc_test_CFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
openosc_test_chk_CFLAGS = $(OPENOSC_CFLAGS)
openosc_test_asan_CFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
#openosc_test_asan_CFLAGS = $(OPENOSC_CFLAGS) -D_FORTIFY_SOURCE=2
#openosc_test_asan_CFLAGS = -fsanitize=address -D_FORTIFY_SOURCE=2
#openosc_test_msan_CFLAGS = $(OPENOSC_CFLAGS) -fsanitize=memory -D_FORTIFY_SOURCE=2
openosc_test_msan_CFLAGS = $(OPENOSC_CFLAGS) -D_FORTIFY_SOURCE=2
#test_harness_CFLAGS = $(OPENOSC_CFLAGS) -include ../include/openosc.h
openosc_fortify_test_CFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
openosc_fortify_nomap_test_CFLAGS = -fno-inline $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)
openosc_test_cpp_CXXFLAGS = $(OPENOSC_CFLAGS) $(OPENOSCTEST_CFLAGS)

openosc_fortify_test_LDFLAGS = -L../src/.libs -lopenosc
openosc_fortify_nomap_test_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_nomap_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_chk_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_asan_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_msan_LDFLAGS = -L../src/.libs -lopenosc
openosc_test_cpp_LDFLAGS = -L../src/.libs -lopenosc
test_harness_LDFLAGS = -L../src/.libs -lopenosc -lpthread -rdynamic
test_harness_break_LDFLAGS = -L../src/.libs -lopenosc -lpthread -rdynamic
