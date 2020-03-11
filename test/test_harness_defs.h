/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef TEST_HARNESS_DEFS_H
#define TEST_HARNESS_DEFS_H

/*
 * Type and macro definitions for the test suite
 */

#define BOSC_TH_VERSION 3.0
#define STATIC_BUF_SIZE 10
#define MALLOC_BUF_SIZE 15
#define LARGER_BUF_SIZE 30
#define NUMBER_OF_BUFS  3
#define TH_SIZE_CHECK_0 0
#define TH_SIZE_CHECK_1 1

void bosc_th_show_result(const char *, int, int);
void bosc_th_test_char(void);
void bosc_th_call_aux_fns(void);
void bosc_th_test_osc_remap(void);
void bosc_th_test_osc_safec_remap(void);
void bosc_th_test_osc_logging(void);
void bosc_th_test_osc_truncation(void);
void bosc_th_test_osc_thread_safe(void);
void bosc_th_run_tests(void);

struct struct1 {
    char char_buf_first[STATIC_BUF_SIZE];
    int intvar;
    char char_buf_mid[STATIC_BUF_SIZE];
    char charvar1;
    char charvar2;
    char char_buf_last[STATIC_BUF_SIZE];
};
typedef struct struct1 struct1;

struct struct2 {
    struct1 *s1ptr;
};
typedef struct struct2 struct2;

struct struct3 {
    struct1 s1;
};
typedef struct struct3 struct3;

union union1 {
    struct1 structvar;
    char char_buf[STATIC_BUF_SIZE*2];
};
typedef union union1 union1;

#endif
