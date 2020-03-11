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
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include "test_harness_defs.h"
#include "test_harness_bosc.h"
//#include "osc_map.h"

/*
 * Various test buffers with different sizes
 *
 * Surrounding source and destination buffers with extra memory
 * to avoid overwriting or reading out of bound during test
 */
char th_red_zone_1[STATIC_BUF_SIZE];     /* Protection region */
char th_dst[STATIC_BUF_SIZE];            /* Destination buffer */
char th_red_zone_2[STATIC_BUF_SIZE];     /* Protection region */
char th_src[STATIC_BUF_SIZE];            /* Source buffer */
char th_src_null[1] = {'\0'};            /* Empty string */
char th_src_one_less[STATIC_BUF_SIZE-1]; /* Smaller than dest buffer */
char th_src_one_more[STATIC_BUF_SIZE+1]; /* Larger than dest buffer */
char th_red_zone_3[STATIC_BUF_SIZE];     /* Protection region */

/*
 * Different sizes used as test input parameter into the remap APIs
 * and the expected result
 */
th_test_data th_testcase[TH_NUM_TEST] = {
    /* Test Description
     * Size,              expect_dcdi,        criteria */
    { "Third parameter 'n' is a negative value",
      /* -1 */ 0,          TH_RESULT_NO_DCDI, TH_PASS_EQU },
    { "Third parameter 'n' is 0",
      0,                   TH_RESULT_NO_DCDI, TH_PASS_EQU },
    { "Third parameter 'n' is 1 less than destination buffer's size",
      STATIC_BUF_SIZE - 1, TH_RESULT_NO_DCDI, TH_PASS_EQU },
    { "Third parameter 'n' is equal destination buffer's size",
      STATIC_BUF_SIZE,     TH_RESULT_NO_DCDI, TH_PASS_EQU },
    { "Third parameter 'n' is 1 more than destination buffer's size",
      STATIC_BUF_SIZE + 1, TH_RESULT_DCDI,    TH_PASS_NOT_EQU },
};

/*
 * Different sizes used as test input parameter into strcat remap APIs
> * and the expected result.
 *
 * Notice: size field is used as source buffer size including the null
 * character
 */
th_test_data th_strcat_test[TH_NUM_STRCAT_TEST] = {
    /* Test Description
     * Size of src string including null,
     * expect_dcdi,        criteria */
    { "Final string is one byte less than the dest size",
      STATIC_BUF_SIZE - TH_STRCAT_DST_LEN,
      TH_RESULT_NO_DCDI, TH_PASS_NOT_EQU },
    { "Final string is equal the dest size",
      STATIC_BUF_SIZE - TH_STRCAT_DST_LEN + 1,
      TH_RESULT_NO_DCDI, TH_PASS_NOT_EQU },
    { "Final string is one byte more than the dest size",
      STATIC_BUF_SIZE - TH_STRCAT_DST_LEN + 2,
      TH_RESULT_DCDI, TH_PASS_NOT_EQU },
};

/*
 * bosc_th_setup_3arg_test
 *
 * Common setup function to test memcpy(), memmove(), memset(), bcopy()
 * strncpy() and strncat(). This function will initialize the global
 * th_dst and th_src to well known values and print out the pre-test
 * information
 */
void
bosc_th_setup_3arg_test (char *api_name, int testcase_idx)
{
    char testname[80];
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"n", 0}};

    /* Create testname from test api and testcase index */
    sprintf(testname, "%s_test_case_%d", api_name, testcase_idx);

    /* Initalize dest and src buffers */
    TH_SETUP_ZERO_DST_BUF();
    TH_SETUP_SEQ_SRC_BUF();

    /* Display Pre-test conditions */
    params[1].value = th_testcase[testcase_idx].size;
    bosc_th_print_test_conditions(testname, th_testcase[testcase_idx].desc, 2,
				  params, th_testcase[testcase_idx].expect_dcdi);
    TH_PRINT_DST();
    TH_PRINT_SRC();
    printf("\n");
}

/*
 * bosc_th_dump_mem
 *
 * Print partial and full content of th_dst and th_src buffers
 */
void
bosc_th_dump_mem (int size)
{
    TH_PRINT_N_DST(size);
    TH_PRINT_N_SRC(size);
    TH_PRINT_DST();
    TH_PRINT_SRC();
}

void
bosc_th_test_osc_memcpy (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("memcpy", i);

	/* Start test */
	printf(TH_TEST_START_STR);
	memcpy(th_dst, th_src, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_memmove (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("memmove", i);

	/* Start test */
	printf(TH_TEST_START_STR);
	memmove(th_dst, th_src, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_memset (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("memset", i);

	/* Start test */
	printf("\n"TH_TEST_START_STR);
	memset(th_dst, 1, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_bcopy (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("bcopy", i);

	/* Start test */
	printf("\n"TH_TEST_START_STR);
	bcopy(th_src, th_dst, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_bzero (void)
{
    int i, size;
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"n", 0}};

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;
	params[1].value = size;

	/* Initialize dest buffer */
	bosc_th_setup_buffer(th_dst, STATIC_BUF_SIZE, TH_FILL_SEQ);

	/* Display Pre-test conditions */
	bosc_th_print_test_conditions("bzero", th_testcase[i].desc, 2,
				      params, th_testcase[i].expect_dcdi);
	TH_PRINT_DST();

	/* Start test */
	printf("\n"TH_TEST_START_STR);
	bzero(th_dst, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test result */
	TH_PRINT_N_DST(size);
	TH_PRINT_DST();
    }
}

void
bosc_th_test_osc_strcpy (void)
{
    int size;
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"src size", 0}};

    /*********************************************************
     * Verify empty source string is handled correctly
     * no DCDI error message
     ********************************************************/
    /* Setup and display Pre-test conditions */
    TH_SETUP_ZERO_DST_BUF();
    params[1].value = sizeof(th_src_null);
    bosc_th_print_test_conditions("strcpy", "Empty source string", 2,
				  params, TH_RESULT_NO_DCDI);
    TH_PRINT_DST();

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src_null);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();

    /*********************************************************
     * Verify source string's size is one less than destination's is
     * handled correctly, no DCDI error message
     ********************************************************/
    /* Setup and display Pre-test conditions */
    size = sizeof(th_src_one_less);
    TH_SETUP_ZERO_DST_BUF();
    bosc_th_setup_buffer(th_src_one_less, size, TH_FILL_SEQ);
    params[1].value = size;
    bosc_th_print_test_conditions("strcpy", "Source string is 1 less than "
				  "destination buffer's size", 2, params,
				  TH_RESULT_NO_DCDI);
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_less, size);

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src_one_less);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_less, size);

    /*********************************************************
     * Verify source string's size is the same as destination's is
     * handled correctly, no DCDI error message
     ********************************************************/
    /* Setup and display Pre-test conditions */
    TH_SETUP_ZERO_DST_BUF();
    TH_SETUP_SEQ_SRC_BUF();
    params[1].value = STATIC_BUF_SIZE;
    bosc_th_print_test_conditions("strcpy", "Source string is equal "
				  "destination buffer's size", 2,
				  params, TH_RESULT_NO_DCDI);
    TH_PRINT_DST();
    TH_PRINT_SRC();

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();
    TH_PRINT_SRC();

    /*********************************************************
     * Verify source string's size is one more than destination's is
     * handled correctly, EXPECT DCDI error message
     ********************************************************/
    /* Setup and display Pre-test conditions */
    size = sizeof(th_src_one_more);
    TH_SETUP_ZERO_DST_BUF();
    bosc_th_setup_buffer(th_src_one_more, size, TH_FILL_SEQ);
    params[1].value = size;
    bosc_th_print_test_conditions("strcpy", "Source string is 1 more than "
				  "destination buffer's size", 2,
				  params, TH_RESULT_DCDI);
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src_one_more);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);
}

void
bosc_th_test_osc_strncpy (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("strncpy", i);

	/* Start test */
	printf(TH_TEST_START_STR);
	strncpy(th_dst, th_src, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

/*
 * bosc_th_setup_str_cat_test
 *
 * Common setup function to test strcat() and strncat(). This function will
 * initialize the global th_dst and th_src to well known values and print out
 * the pre-test information
 */
void
bosc_th_setup_str_cat_test (char *api_name, int testcase_idx)
{
    th_test_param params[] = {
	{"dst buffer size", STATIC_BUF_SIZE},
	{"dst string length (including NULL)", TH_STRCAT_DST_LEN},
	{"src string length (including NULL)", 0}};

    /*
     * Fill dest and src buffers with all 1s. This is so we can easily
     * see where the NULL character is when we dump the memory
     */
    TH_SETUP_ONE_DST_BUF();
    TH_SETUP_ONE_SRC_BUF();

    /* Initalize dest and src buffers */
    TH_SETUP_STR_DST_BUF(TH_STRCAT_DST_LEN);
    TH_SETUP_STR_SRC_BUF(th_strcat_test[testcase_idx].size);

    /* Display Pre-test conditions */
    params[2].value = th_strcat_test[testcase_idx].size;
    bosc_th_print_test_conditions(api_name, th_strcat_test[testcase_idx].desc, 3,
				  params, th_strcat_test[testcase_idx].expect_dcdi);
    TH_PRINT_DST();
    TH_PRINT_SRC();
    printf("\n");
}

void
bosc_th_test_osc_strcat (void)
{
    int i;

    for (i = 0; i < TH_NUM_STRCAT_TEST; i++) {
	/* Setup and display Pre-test conditions */
	bosc_th_setup_str_cat_test("strcat", i);

	/* Start test */
	printf("\n"TH_TEST_START_STR);
	strcat(th_dst, th_src);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(STATIC_BUF_SIZE);

	/* Analyze memory and print result */
	// bosc_th_print_result(th_dst, th_src, STATIC_BUF_SIZE, th_strcat_test[i].criteria);
    }
}

void
bosc_th_test_osc_strncat (void)
{
    int i, size;

    for (i = 0; i < TH_NUM_TEST; i++) {
	/* Get test size */
	size = th_testcase[i].size;

	/* Setup and display Pre-test conditions */
	bosc_th_setup_3arg_test("strncat", i);

	/* Start test */
	printf("\n"TH_TEST_START_STR);
	strncat(th_dst, th_src, size);
	printf(TH_TEST_END_STR"\n");

	/* Display Post-test memory */
	bosc_th_dump_mem(size);

	/* Analyze memory and print result */
	bosc_th_print_result(th_dst, th_src, size, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_strnlen (void)
{
}

void
bosc_th_test_osc_vsprintf (void)
{
}

void
bosc_th_test_osc_vsnprintf (void)
{
}

void
bosc_th_test_osc_remap (void)
{
    printf("\n\n  BOSC Remap API Tests\n");
    bosc_th_test_osc_memcpy();
    bosc_th_test_osc_memmove();
    bosc_th_test_osc_memset();

    bosc_th_test_osc_bcopy();
    bosc_th_test_osc_bzero();

    bosc_th_test_osc_strcpy();
    bosc_th_test_osc_strncpy();
    bosc_th_test_osc_strcat();
    bosc_th_test_osc_strncat();
    bosc_th_test_osc_strnlen();

    //bosc_th_test_osc_vsprintf();
    bosc_th_test_osc_vsnprintf();
}

void
bosc_th_test_dcdi_filter (void)
{
    int size, i;

    printf("\n========================================\n");
    printf("Test Name: DCDI filter\n");
    printf("Test Description:\n");
    printf("    Generate 10 identical tracebacks using strcpy(). "
	   "Verify only a single DCDI "
	   "error message is logged per unique traceback\n");
    printf("Expected Outcome:\n");
    printf("    Only see a single DCDI error message\n\n");

    /* Setup test conditions */
    size = sizeof(th_src_one_more);
    TH_SETUP_ZERO_DST_BUF();
    bosc_th_setup_buffer(th_src_one_more, size, TH_FILL_SEQ);

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    for (i = 0; i < 10; i++) {
	printf("Calling strcpy() #%d\n", i);
	strcpy(th_dst, th_src_one_more);
    }
    printf(TH_TEST_END_STR"\n");
}

void
bosc_th_test_osc_logging (void)
{
    printf("\n\n  BOSC DCDI Logging Tests\n");
    bosc_th_test_dcdi_filter();
    
}

void
bosc_th_test_osc_truncation (void)
{
    char th_tr_src[STATIC_BUF_SIZE];
    char th_tr_dst[STATIC_BUF_SIZE/2];
    int size;

    size = (rand() % 5) + STATIC_BUF_SIZE/2;
    printf("\n\n BOSC Truncation Tests");
    printf("\n=========================\n");
    printf("Test Name: Truncation \n");
    printf("Test Description:\n");
    printf("    Verify buffer overflow is truncated. \n");
    printf("Test Parameters:\n");
    printf("    dest size = 5\n");
    printf("    n = %i\n", size);

    /* Setup and display Pre-test conditions */
    bosc_th_setup_buffer(th_tr_dst, STATIC_BUF_SIZE/2, TH_FILL_ZERO);
    bosc_th_setup_buffer(th_tr_src, STATIC_BUF_SIZE, TH_FILL_SEQ);

    printf("Content of Destination buffer:\n");
    bosc_th_print_mem(th_tr_dst, STATIC_BUF_SIZE/2);
    printf("Display %i bytes starting from start of destination buffer:\n", size);
    bosc_th_print_mem(th_tr_dst, size);
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_tr_src, STATIC_BUF_SIZE);
    printf("\n");

    /* Start test */
    printf(TH_TEST_START_STR);
    printf("Trying to copy %i bytes to destination buffer...\n", size);
    memcpy(th_tr_dst, th_tr_src, size);
    printf(TH_TEST_END_STR"\n");
    printf("\n");

    /* Display Post-test result */
    printf("Content of Destination buffer:\n");
    bosc_th_print_mem(th_tr_dst, STATIC_BUF_SIZE/2);
    printf("Display %i bytes starting from start of destination buffer:\n", size);
    bosc_th_print_mem(th_tr_dst, size);
}

/*
 * Thread one main. Generate DCDI when using memcpy()
 */
void *
bosc_th_thread_1_main (void *arg)
{
    int size;
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"src size", 0}};

    /* Setup and display Pre-test conditions */
    size = sizeof(th_src_one_more);
    TH_SETUP_ZERO_DST_BUF();
    bosc_th_setup_buffer(th_src_one_more, size, TH_FILL_SEQ);
    params[1].value = size;
    printf("\nFROM THREAD 1\n");
    bosc_th_print_test_conditions("strcpy", "Source string is 1 more than "
				  "destination buffer's size", 2,
				  params, TH_RESULT_DCDI);
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src_one_more);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);

    return 0;
}

/*
 * Thread two main. Generate DCDI when using memmove()
 */
void *
bosc_th_thread_2_main (void *arg)
{
    int size;
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"src size", 0}};

    /* Setup and display Pre-test conditions */
    size = sizeof(th_src_one_more);
    TH_SETUP_ZERO_DST_BUF();
    bosc_th_setup_buffer(th_src_one_more, size, TH_FILL_SEQ);
    params[1].value = size;
    printf("\nFROM THREAD 2\n");
    bosc_th_print_test_conditions("strcpy", "Source string is 1 more than "
				  "destination buffer's size", 2,
				  params, TH_RESULT_DCDI);
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);

    /* Start test */
    printf("\n"TH_TEST_START_STR);
    strcpy(th_dst, th_src_one_more);
    printf(TH_TEST_END_STR"\n");

    /* Display Post-test result */
    TH_PRINT_DST();
    printf("Content of Source buffer:\n");
    bosc_th_print_mem(th_src_one_more, size);

    return 0;
}

/*
 * This function creates two threads and verifies that libciscoosc is thread-safe
 */ 
void
bosc_th_test_osc_thread_safe (void)
{
    pthread_t       thr_id_1, thr_id_2;

    printf("\n========================================\n");
    printf("Test Name: Thread-safe\n");
    printf("Test Description:\n");
    printf("    Verify the library is thread-safe, create two threads, both call strcpy()\n");
    printf("Expected Outcome:\n");
    printf("    Only see a single DCDI error message\n\n");

    /* Start thread 1. Thread one should sleep after taking the mutex within libciscoosc */
    if (pthread_create(&thr_id_1, NULL, bosc_th_thread_1_main, NULL)) {
	return;
    }

    /* Start thread 2. Thread two should not generate any DCDI message */
    if (pthread_create(&thr_id_2, NULL, bosc_th_thread_2_main, NULL)) {
	return;
    }

    /* Sleep to let two test threads run */
    sleep(30);

    return;
}
