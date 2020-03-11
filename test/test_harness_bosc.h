/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef _TEST_HARNESS_BOSC_H_
#define _TEST_HARNESS_BOSC_H_

#include "test_harness_defs.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  (!FALSE)
#endif

/* Number of tests in th_testcase array */
#define TH_NUM_TEST  5
#define TH_NUM_TEST_SAFEC 9 

/* Number of tests in th_strcat_test array */
#define TH_NUM_STRCAT_TEST  3

#define TH_RESULT_NO_DCDI 0
#define TH_RESULT_DCDI (!TH_RESULT_NO_DCDI)

#define TH_TEST_START_STR "*** Begin Executing Test ***\n"
#define TH_TEST_END_STR "*** Execution Complete ***\n"

/*
 * Length of dst string including the terminating null used in strcat()
 * and strncat() test
 */
#define TH_STRCAT_DST_LEN 5

typedef enum _th_fill_type {
    TH_FILL_ZERO, /* Fill buffer with all zero */
    TH_FILL_ONE,  /* Fill buffer with all one */
    TH_FILL_SEQ,  /* Fill buffer with increment values starting from 1 */
    TH_FILL_STR   /* Fill buffer with sequential character starting from 'a'
		   * and terminate the last character of the string with NULL
		   */
} th_fill_type;

typedef enum _th_pass_criteria {
    TH_PASS_EQU,      /* Test pass if 2 buffers are the same */
    TH_PASS_NOT_EQU,  /* Test pass if 2 buffers are NOT the same */
    TH_PASS_EOK = 0, 
    TH_PASS_NOT_EOK, 
} th_pass_criteria;

/* Test parameters and expected results for each test case */
typedef struct _th_test_data {
    char *desc;                /* Test description */
    int size;                  /* Input size parameter for the remap API */
    int expect_dcdi;           /* Expect DCDI error msg or not */
    th_pass_criteria criteria; /* Pass/fail criteria */
} th_test_data;

/* Test parameters and expected results for each safec test cases */
typedef struct _th_test_safec_data {
    char *desc;                /* Test description */
    int dmax;                  /* Input size dmax parameter */
    int slen;                  /* Input size slen parameter */
    int expect_dcdi;           /* Expect DCDI error msg or not */
    th_pass_criteria criteria; /* Pass/fail criteria */
} th_test_safec_data;

/* Test parameter description and value */
typedef struct _th_test_param {
    char *name;                /* Parameter name */
    int value;                 /* Parameter value */
} th_test_param;

/* Macro to setup various test buffers */
#define TH_SETUP_ZERO_DST_BUF() \
    bosc_th_setup_buffer(th_dst, STATIC_BUF_SIZE, TH_FILL_ZERO)
#define TH_SETUP_ZERO_SRC_BUF() \
    bosc_th_setup_buffer(th_src, STATIC_BUF_SIZE, TH_FILL_ZERO)
#define TH_SETUP_ONE_DST_BUF() \
    bosc_th_setup_buffer(th_dst, STATIC_BUF_SIZE, TH_FILL_ONE)
#define TH_SETUP_ONE_SRC_BUF() \
    bosc_th_setup_buffer(th_src, STATIC_BUF_SIZE, TH_FILL_ONE)
#define TH_SETUP_SEQ_SRC_BUF() \
    bosc_th_setup_buffer(th_src, STATIC_BUF_SIZE, TH_FILL_SEQ)
#define TH_SETUP_STR_DST_BUF(n) \
    bosc_th_setup_buffer(th_dst, n, TH_FILL_STR)
#define TH_SETUP_STR_SRC_BUF(n) \
    bosc_th_setup_buffer(th_src, n, TH_FILL_STR)

/* Macro to print the entire th_dst and th_src buffer */
#define TH_PRINT_DST() ({			 \
    printf("Content of Destination buffer:\n");	 \
    bosc_th_print_mem(th_dst, STATIC_BUF_SIZE);})
#define TH_PRINT_SRC() ({			 \
    printf("Content of Source buffer:\n");	 \
    bosc_th_print_mem(th_src, STATIC_BUF_SIZE);})

/* Macro to print the first n bytes of th_dst and th_src buffer */
#define TH_PRINT_N_DST(n) ({ if (n) {			  \
    printf("First %i bytes of Destination buffer:\n", n); \
    bosc_th_print_mem(th_dst, n);}})
#define TH_PRINT_N_SRC(n) ({ if (n) {		     \
    printf("First %i bytes of Source buffer:\n", n); \
    bosc_th_print_mem(th_src, n);}})

/* test_harness_bosc_utils.c */
void bosc_th_print_test_conditions (char *api_name, char *desc,
				    int num_param, th_test_param params[],
				    int expect_dcdi);
int bosc_th_setup_buffer (char *buf, int size, th_fill_type fill_type);
int bosc_th_print_mem (char *buf, int size);
int bosc_th_print_result (const void *buf1, const void *buf2, size_t size,
			  th_pass_criteria criteria);
void bosc_th_print_result_safec (int result, int criteria);

/* test_harness_bosc.c */
void bosc_th_setup_3arg_test (char *api_name, int testcase_idx);

#endif /* _TEST_HARNESS_BOSC_H_ */
