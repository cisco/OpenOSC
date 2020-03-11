/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */
#include <stdio.h>
#include <stdlib.h>
#include "test_harness_defs.h"
#include "test_harness_aux.h"

int is_large_size = 1;

/*
 * The entry point to run all of the test harness's functions (defined below)
 */
void
bosc_th_run_tests (void)
{
    printf("BOSC_TH_VERSION %.2f\n", (float)BOSC_TH_VERSION);
    printf("COMPILER_VERSION: %s\n\n", BOSC_TH_COMPILER_VERSION);

    bosc_th_test_char();
    bosc_th_call_aux_fns();

    /* Extra OSC remap testing */
    bosc_th_test_osc_remap();
#ifdef HAS_SAFEC
    bosc_th_test_osc_safec_remap();
#endif
    /* OSC logging testing */
    bosc_th_test_osc_logging();

    /* OSC truncation testing */
    bosc_th_test_osc_truncation();

    /* OSC thread safe testing */
    bosc_th_test_osc_thread_safe();
}

/*
 * This function tests how object size checkers deal with objects whose size can
 * vary between fixed values at run-time.
 */
static size_t
static_bosc_th_test_flow_char (int flag)
{
    char *cptr;
    char char_buf1[STATIC_BUF_SIZE];
    char char_buf2[LARGER_BUF_SIZE];
    if (flag) {
	cptr = char_buf1;
    } else {
	cptr = char_buf2;
    }
    return __builtin_object_size(cptr, TH_SIZE_CHECK_1);
}

/*
 * For outputting results
 */
void
bosc_th_show_result (const char *test_name, int size, int correct_size)
{
    printf("%32s: Expected size %2d Detected %2d %s\n",
	   test_name, correct_size, size,
	   (correct_size == size) ? "" : "(FAILED)");
}

void *
bosc_th_malloc_fn (size_t size)
{
    if (is_large_size) {
       return (malloc(size));
    } else {
	return NULL;
    }
}

void *
bosc_th_malloc (size_t size)
{
    return (bosc_th_malloc_fn(size));
}

/*
 * A series of tests on buffers
 */
void
bosc_th_test_char (void)
{
    int i;
    int test_size, intvar;
    void *vptr;
    char charvar, *cptr;
    char char_buf[STATIC_BUF_SIZE];
    char char_2d_array[NUMBER_OF_BUFS][STATIC_BUF_SIZE];
    char **cptrptr;
    short short_buf[STATIC_BUF_SIZE], shortvar;
    int int_buf[STATIC_BUF_SIZE];
    struct1 s1;
    struct1 *s4;
    struct3 s3;
    union1 u1;

    /* Basic tests with type short */
    test_size = __builtin_object_size(&shortvar, TH_SIZE_CHECK_1);
    bosc_th_show_result("SHORT_ADDR_SIZE", test_size, sizeof(short));
    test_size = __builtin_object_size(short_buf, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_SHORT", test_size, sizeof(short_buf));
    test_size = __builtin_object_size(short_buf + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_SHORT_OFFSET", test_size,
			sizeof(short_buf) - 5 * sizeof(short));

    /* Basic tests with type int */
    test_size = __builtin_object_size(&intvar, TH_SIZE_CHECK_1);
    bosc_th_show_result("INT_ADDR_SIZE", test_size, sizeof(int));
    test_size = __builtin_object_size(int_buf, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_INT", test_size, sizeof(int_buf));
    test_size = __builtin_object_size(int_buf + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_INT_OFFSET", test_size,
			sizeof(int_buf) - 5 * sizeof(int));

    /* Basic tests with type char */
    test_size = __builtin_object_size(&charvar, TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_ADDR_SIZE", test_size, sizeof(char));
    test_size = __builtin_object_size(char_buf, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_CHAR", test_size, STATIC_BUF_SIZE);
    test_size = __builtin_object_size(char_buf + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_CHAR_OFFSET", test_size,
			STATIC_BUF_SIZE - 5);

    /* Basic tests with type void * */
    test_size = __builtin_object_size(&charvar, TH_SIZE_CHECK_1);
    bosc_th_show_result("VOID_ADDR_SIZE", test_size, sizeof(char));
    test_size = __builtin_object_size(char_buf, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_VOID", test_size, STATIC_BUF_SIZE);
    test_size = __builtin_object_size(char_buf + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_VOID_OFFSET", test_size,
			STATIC_BUF_SIZE - 5);

    /* 2D array tests */
    test_size = __builtin_object_size(char_2d_array, TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_2D_ARRAY_TOTAL", test_size,
                        sizeof(char_2d_array));
    test_size = __builtin_object_size(char_2d_array[0], TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_2D_ARRAY_FIRST", test_size,
                        sizeof(char_2d_array[0]));
    test_size = __builtin_object_size(char_2d_array[1], TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_2D_ARRAY_SECOND", test_size,
                        sizeof(char_2d_array[1]));
    test_size = __builtin_object_size(char_2d_array[NUMBER_OF_BUFS  - 1],
				      TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_2D_ARRAY_LAST", test_size, 
                        sizeof(char_2d_array[NUMBER_OF_BUFS  - 1]));
    /* char ** tests */
    cptrptr = (char **) malloc(sizeof(char *) * NUMBER_OF_BUFS);
    for (i = 0; i < NUMBER_OF_BUFS; i++) {
        cptrptr[i] = (char *) malloc(sizeof(char) * STATIC_BUF_SIZE);
    }
    test_size = __builtin_object_size(cptrptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_PTR_PTR_TOTAL", test_size,
                        sizeof(char *) * NUMBER_OF_BUFS);
    test_size = __builtin_object_size(cptrptr[0], TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_PTR_PTR_FIRST", test_size,
                        STATIC_BUF_SIZE);
    test_size = __builtin_object_size(cptrptr[1], TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_PTR_PTR_SECOND", test_size,
                        STATIC_BUF_SIZE);
    test_size = __builtin_object_size(cptrptr[NUMBER_OF_BUFS  - 1], TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_PTR_PTR_LAST", test_size, 
                        STATIC_BUF_SIZE);

    /* Pointer assignment of fixed sized buffer */
    vptr = char_buf;
    test_size = __builtin_object_size(vptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_CHAR_CAST_VOID", test_size,
			STATIC_BUF_SIZE);
    cptr = char_buf;
    test_size = __builtin_object_size(cptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_CHAR_CAST_PTR", test_size,
			STATIC_BUF_SIZE);
    cptr = char_buf;
    test_size = __builtin_object_size(cptr + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_SIZE_CHAR_CAST_PTR_OFFSET", test_size,
			STATIC_BUF_SIZE - 5);


    /* Tests with malloc'ed buffer, size known at compile time */
    cptr = malloc(sizeof(char) * MALLOC_BUF_SIZE);
    test_size = __builtin_object_size(cptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("SIZE_ONCE_REMOVED_CHAR", test_size, MALLOC_BUF_SIZE);
    test_size = __builtin_object_size(cptr + 5, TH_SIZE_CHECK_1);
    bosc_th_show_result("SIZE_ONCE_REMOVED_CHAR_OFFSET", test_size,
			MALLOC_BUF_SIZE - 5);
    test_size = (int)__builtin_object_size(++cptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("SIZE_ONCE_REMOVED_CHAR_INCR", test_size,
			MALLOC_BUF_SIZE - 1);

    /* Allocation of known structure size */
    s4 = malloc(sizeof(struct1));
    test_size = __builtin_object_size(s4, TH_SIZE_CHECK_1);
    bosc_th_show_result("ALLOCATED_STRUCT_SIZE", test_size,
                        sizeof(struct1));
    s4 = bosc_th_malloc(sizeof(struct1));
    test_size = __builtin_object_size(s4, TH_SIZE_CHECK_1);
    bosc_th_show_result("INDIRECTLY_ALLOCATED_STRUCT_SIZE", test_size,
                        sizeof(struct1));

    /* Pointer assignment with malloc'ed buffer, size known at compile time */
    cptr--;
    vptr = cptr;
    test_size = __builtin_object_size(vptr, TH_SIZE_CHECK_1);
    bosc_th_show_result("CHAR_PTR_CAST_VOID", test_size, MALLOC_BUF_SIZE);

    /* Tests with struct types, buffers in structs */
    test_size = __builtin_object_size(&s1, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_STRUCT_SIZE", test_size, sizeof(struct1));
    test_size = __builtin_object_size(&s1, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_STRUCT_SIZE_VOID", test_size, sizeof(struct1));
    test_size = __builtin_object_size(s1.char_buf_first, TH_SIZE_CHECK_1);
    bosc_th_show_result("STRUCT_STATIC_CHAR_FIRST_SIZE", test_size,
			STATIC_BUF_SIZE);
    test_size = __builtin_object_size(s1.char_buf_mid, TH_SIZE_CHECK_1);
    bosc_th_show_result("STRUCT_STATIC_CHAR_MID_SIZE", test_size,
			STATIC_BUF_SIZE);
    test_size = __builtin_object_size(s1.char_buf_last, TH_SIZE_CHECK_1);
    bosc_th_show_result("STRUCT_STATIC_CHAR_LAST_SIZE", test_size,
			STATIC_BUF_SIZE);
    test_size = __builtin_object_size(s3.s1.char_buf_mid, TH_SIZE_CHECK_1);
    bosc_th_show_result("NESTED_STRUCT_CHAR_SIZE", test_size, STATIC_BUF_SIZE);

    /* Tests with union types of structs and buffers */
    test_size = __builtin_object_size(&u1, TH_SIZE_CHECK_1);
    bosc_th_show_result("STATIC_UNION_SIZE", test_size, sizeof(union1));
    test_size = __builtin_object_size(&u1.structvar, TH_SIZE_CHECK_1);
    bosc_th_show_result("UNION_STATIC_CHAR_SIZE", test_size, sizeof(struct1));
    test_size = __builtin_object_size(u1.char_buf, TH_SIZE_CHECK_1);
    bosc_th_show_result("UNION_STATIC_CHAR_SIZE", test_size,
			STATIC_BUF_SIZE * 2);

    /* Size varying check within file */
    test_size = static_bosc_th_test_flow_char(0);
    bosc_th_show_result("STATIC_FLOW_CHAR_FALSE", test_size, LARGER_BUF_SIZE);
    test_size = static_bosc_th_test_flow_char(1);
    bosc_th_show_result("STATIC_FLOW_CHAR_TRUE", test_size, STATIC_BUF_SIZE);
}

/*
 * A series of tests across object file boundaries
 */
void
bosc_th_call_aux_fns (void)
{
    int test_size;
    char char_buf[STATIC_BUF_SIZE];
    struct1 s1;
    struct2 s2;

    /* Basic buffer size test across boundary */
    test_size = bosc_th_test_aux_char(char_buf);
    bosc_th_show_result("STATIC_SIZE_CHAR_AUX", test_size, STATIC_BUF_SIZE);

    /* Size varying check across boundary */
    test_size = bosc_th_test_aux_flow_char(0);
    bosc_th_show_result("FLOW_CHAR_AUX_FALSE", test_size, LARGER_BUF_SIZE);
    test_size = bosc_th_test_aux_flow_char(1);
    bosc_th_show_result("FLOW_CHAR_AUX_TRUE", test_size, STATIC_BUF_SIZE);

    /* Basic struct size test across boundary */
    s2.s1ptr = &s1;
    test_size = bosc_th_test_aux_struct_ptr(&s2);
    bosc_th_show_result("STRUCT_PTR_STRUCT_CHAR_SIZE", test_size,
			STATIC_BUF_SIZE);
}

int
main (int argc, char *argv[])
{
    bosc_th_run_tests();
    return 0;
}
