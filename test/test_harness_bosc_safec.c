/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#include <stdio.h>
#include "test_harness_bosc.h"
#include "openosc_safec_map.h"

extern char th_dst[STATIC_BUF_SIZE];            /* Destination buffer */
extern char th_src[STATIC_BUF_SIZE];            /* Source buffer */
extern th_test_data th_testcase[TH_NUM_TEST];

/*
 * Different sizes used as test input parameter into the remap safeC 
 * APIs and the expected result
 */
th_test_safec_data th_safec_testcase[TH_NUM_TEST_SAFEC] = {
    /* Test Description
     * dmax,		slen, 		expect_dcdi,     criteria  */
    { "'dmax' is -1 and 'slen' is equal to dest buffer size", 	-1,
	STATIC_BUF_SIZE,	TH_RESULT_DCDI,    TH_PASS_NOT_EOK }, 
    { "'dmax' is 0 and 'slen' is equal to dest buffer size", 	0,
	STATIC_BUF_SIZE,	TH_RESULT_NO_DCDI,    TH_PASS_EOK }, 
    { "'dmax' is 1 less than dest buffer's size and 'slen' is equal to dest buffer size ",
      	STATIC_BUF_SIZE - 1,	STATIC_BUF_SIZE, TH_RESULT_NO_DCDI, TH_PASS_EOK },
    { "'dmax' is equal to dest buffer's size and 'slen' is equal to dest buffer size",
      STATIC_BUF_SIZE, STATIC_BUF_SIZE, TH_RESULT_NO_DCDI, TH_PASS_EOK },
    { "'dmax' is 1 more than dest buffer size and 'slen' is equal to dest buffer size",
      STATIC_BUF_SIZE + 1, STATIC_BUF_SIZE, TH_RESULT_DCDI, TH_PASS_NOT_EOK },
    { "'dmax' is equal to dest buffer size and 'slen' is 1 less than dest buffer size",
      STATIC_BUF_SIZE, STATIC_BUF_SIZE - 1, TH_RESULT_NO_DCDI, TH_PASS_EOK },
    { "'dmax' is equal to dest buffer size and 'slen' is 1 more than dest buffer size",
      STATIC_BUF_SIZE, STATIC_BUF_SIZE + 1, TH_RESULT_NO_DCDI, TH_PASS_EOK },
    { "'dmax' is equal to dest buffer size and 'slen' is 0",
      STATIC_BUF_SIZE, 0, TH_RESULT_NO_DCDI, TH_PASS_EOK },
    { "'dmax' is equal to dest buffer size and 'slen' is -1",
      STATIC_BUF_SIZE, -1, TH_RESULT_NO_DCDI, TH_PASS_EOK },
};

/*
 * bosc_th_setup_safec_test
 *
 * Common setup function to test safec functions. This function will 
 * initialize the global th_dst and th_src to well known  values and
 * print out the pre-test information
 */

void
bosc_th_setup_safec_test (char *api_name, int testcase_idx)
{
    char testname[80];
    th_test_param params[] = {{"dest size", STATIC_BUF_SIZE}, {"dmax", 0},
			      {"src size", STATIC_BUF_SIZE}, {"slen", 0}};

    /* Create testname from test api and testcase index */
    sprintf(testname, "%s_test_case_%d", api_name, testcase_idx);

    /* Initalize dest and src buffers */
    TH_SETUP_ZERO_DST_BUF();
    TH_SETUP_SEQ_SRC_BUF();

    params[1].value = th_safec_testcase[testcase_idx].dmax;
    params[3].value = th_safec_testcase[testcase_idx].slen;
    /* Display Pre-test conditions */
    bosc_th_print_test_conditions(testname, th_safec_testcase[testcase_idx].desc, 4,
                                  params, th_safec_testcase[testcase_idx].expect_dcdi);
    TH_PRINT_DST();
    TH_PRINT_SRC();
    printf("\n");
}


void
bosc_th_test_osc_memcmp_s (void)
{
    int i,  diff, res;

    for (i = 0; i < TH_NUM_TEST_SAFEC; i++) {

        /* Setup and display Pre-test conditions */
        bosc_th_setup_safec_test("memcmp_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = memcmp_s (th_dst, th_safec_testcase[i].dmax, th_src, 
			th_safec_testcase[i].slen, &diff);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_safec_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_memcpy_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST_SAFEC; i++) {

        /* Setup and display Pre-test conditions */
        bosc_th_setup_safec_test("memcpy_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = memcpy_s (th_dst, th_safec_testcase[i].dmax,
			th_src, th_safec_testcase[i].slen);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_safec_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_strcat_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST; i++) {
	if (i != 4) {
	    th_testcase[i].expect_dcdi = TH_RESULT_DCDI;    
	    th_testcase[i].criteria = TH_PASS_NOT_EQU; 
	}

        /* Setup and display Pre-test conditions */
        bosc_th_setup_3arg_test("strcat_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strcat_s (th_dst, th_testcase[i].size, th_src);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_testcase[i].criteria);
        /* revert back to the original */
	if (i != 4) {
	    th_testcase[i].expect_dcdi = TH_RESULT_NO_DCDI;    
	    th_testcase[i].criteria = TH_PASS_EQU; 
	}
    }
}

void
bosc_th_test_osc_strcmp_s (void)
{
    int i,  diff, res;

    for (i = 0; i < TH_NUM_TEST; i++) {

        /* Setup and display Pre-test conditions */
        bosc_th_setup_3arg_test("strcmp_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strcmp_s (th_dst, th_testcase[i].size, th_src, &diff);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_testcase[i].criteria);
    }
}

void bosc_th_test_osc_strcpy_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST; i++) {

        /* Setup and display Pre-test conditions */
        bosc_th_setup_3arg_test("strcpy_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strcpy_s (th_dst, th_testcase[i].size, th_src);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_strncat_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST_SAFEC; i++) {

	/* except the below cases, the 'slen' is equal to dest
	 * buffer's size. So will get DCDI error (because dest
	 * buffer should accomodate the existing content of dest 
	 * and no. of char(s) to concatenate into dest with null).
	 */
	if (i == 1 || i == 2 || i == 3 || i == 6) {
	    th_safec_testcase[i].expect_dcdi = TH_RESULT_DCDI; 	
	    th_safec_testcase[i].criteria = TH_PASS_NOT_EOK;	
	}
 
        /* Setup and display Pre-test conditions */
        bosc_th_setup_safec_test("strncat_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strncat_s (th_dst, th_safec_testcase[i].dmax, 
			th_src, th_safec_testcase[i].slen);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_safec_testcase[i].criteria);
	
	/* revert back */
	if (i == 1 || i == 2 || i == 3 || i == 6) {
	    th_safec_testcase[i].expect_dcdi = TH_RESULT_NO_DCDI; 	
	    th_safec_testcase[i].criteria = TH_PASS_EOK;	
	}
    }
}

void
bosc_th_test_osc_strncpy_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST_SAFEC; i++) {

        /* 'slen' should be less than or equal to dest buffer size */
	if (i == 6 || i == 8) {
	    th_safec_testcase[i].expect_dcdi = TH_RESULT_DCDI; 	
	    th_safec_testcase[i].criteria = TH_PASS_NOT_EOK;	
	}
	
        /* Setup and display Pre-test conditions */
        bosc_th_setup_safec_test("strncpy_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strncpy_s (th_dst, th_safec_testcase[i].dmax,
			 th_src, th_safec_testcase[i].slen);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_safec_testcase[i].criteria);

	/* revert back */
	if (i == 6 || i == 8) {
	    th_safec_testcase[i].expect_dcdi = TH_RESULT_NO_DCDI; 	
	    th_safec_testcase[i].criteria = TH_PASS_EOK;	
	}
    }
}

void bosc_th_test_osc_strnlen_s (void)
{
    int i,  res;

    for (i = 0; i < TH_NUM_TEST; i++) {

        /* Setup and display Pre-test conditions */
        bosc_th_setup_3arg_test("strnlen_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strnlen_s (th_src, th_testcase[i].size);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_testcase[i].criteria);
    }
}

void
bosc_th_test_osc_strstr_s (void)
{
    int i,  res;
    char *substr = NULL;
    char testname[80];

    for (i = 0; i < TH_NUM_TEST_SAFEC; i++) {
	/* Get testname for each case */
	sprintf(testname, "strstr_s-test_case-%d", i);
        /* Setup and display Pre-test conditions */
        bosc_th_setup_safec_test("strstr_s", i);

        /* Start test */
        printf(TH_TEST_START_STR);
        res = strstr_s (th_dst, th_safec_testcase[i].dmax,
			th_src, th_safec_testcase[i].slen, &substr);
        printf(TH_TEST_END_STR"\n");

	/* print the result */
	bosc_th_print_result_safec(res, th_safec_testcase[i].criteria);
    }
}

/*
 * series of tests for some safec APIs
 */

void
bosc_th_test_osc_safec_remap (void)
{
    printf("\n\n  BOSC Remap API Tests for safeC\n");

    bosc_th_test_osc_strcat_s ();
    bosc_th_test_osc_memcmp_s ();
    bosc_th_test_osc_memcpy_s ();
//    bosc_th_test_osc_strcat_s ();
    bosc_th_test_osc_strcmp_s ();
    bosc_th_test_osc_strcpy_s ();
    bosc_th_test_osc_strncat_s ();
    bosc_th_test_osc_strncpy_s ();
    bosc_th_test_osc_strnlen_s ();
    bosc_th_test_osc_strstr_s ();

}

