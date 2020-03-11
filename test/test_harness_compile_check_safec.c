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
#include "test_harness_bosc.h"

extern char th_dst[STATIC_BUF_SIZE];            /* Destination buffer */
extern char th_src[STATIC_BUF_SIZE];            /* Source buffer */

/* For memcmp_s () */
void
test_memcmp_s_dst_size_minus_1_NO_compile_error (void)
{
    int diff;

    /* Expect no compile time error */
    memcmp_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE, &diff);
}

void
test_memcmp_s_dst_size_NO_compile_error (void)
{
    int diff;

    /* Expect no compile time error */
    memcmp_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE, &diff);
}

void
test_memcmp_s_dst_size_plus_1_compile_error (void)
{
    int diff;

    /* Expect compile time error */
    memcmp_s(th_dst, STATIC_BUF_SIZE + 1, th_src, STATIC_BUF_SIZE , &diff);
}

/* For memcpy_s () */
void
test_memcpy_s_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    memcpy_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE);
}

void
test_memcpy_s_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    memcpy_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE);
}

void
test_memcpy_s_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    memcpy_s(th_dst, STATIC_BUF_SIZE + 1, th_src, STATIC_BUF_SIZE);
}

/* For strcat_s () */
void
test_strcat_s_dst_size_minus_1_NO_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcat_s(th_dst, STATIC_BUF_SIZE - 1, th_src);
}

void
test_strcat_s_dst_size_NO_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcat_s(th_dst, STATIC_BUF_SIZE, th_src);
}

void
test_strcat_s_dst_size_plus_1_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcat_s(th_dst, STATIC_BUF_SIZE + 1, th_src);
}

/* For strcmp_s () */
void
test_strcmp_s_dst_size_minus_1_NO_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcmp_s(th_dst, STATIC_BUF_SIZE - 1, th_src, &indicator);
}

void
test_strcmp_s_dst_size_NO_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcmp_s(th_dst, STATIC_BUF_SIZE, th_src, &indicator);
}

void
test_strcmp_s_dst_size_plus_1_compile_error (void)
{
    int indicator;

    /* Expect no compile time error */
    strcmp_s(th_dst, STATIC_BUF_SIZE + 1, th_src, &indicator);
}

/* For strcpy_s () */
void
test_strcpy_s_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    strcpy_s(th_dst, STATIC_BUF_SIZE - 1, th_src);
}

void
test_strcpy_s_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    strcpy_s(th_dst, STATIC_BUF_SIZE, th_src);
}

void
test_strcpy_s_dst_size_plus_1_compile_error (void)
{

    /* Expect no compile time error */
    strcpy_s(th_dst, STATIC_BUF_SIZE + 1, th_src);
}

/* For strncat_s () */
void
test_strncat_s_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncat_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE);
}

void
test_strncat_s_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncat_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE);
}

void
test_strncat_s_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    strncat_s(th_dst, STATIC_BUF_SIZE + 1, th_src, STATIC_BUF_SIZE);
}

void
test_strncat_s_slen_plus_1_compile_error (void)
{

    /* Expect compile time error */
    strncat_s(th_dst, STATIC_BUF_SIZE , th_src, STATIC_BUF_SIZE + 1);
}

/* For strncpy () */
void
test_strncpy_s_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncpy_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE - 2);
}

void
test_strncpy_s_slen_same_as_dest_bufsize_compile_error (void)
{

    /* Expect compile time error to the below cases */
//    strncpy_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE);
    strncpy_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE);
}

void
test_strncpy_s_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncpy_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE - 1);
}

void
test_strncpy_s_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    strncpy_s(th_dst, STATIC_BUF_SIZE + 1, th_src, STATIC_BUF_SIZE - 1);
}


/* For strnlen_s () */
void
test_strnlen_s_src_size_minus_1_NO_compile_error (void)
{
    /* Expect compile time error */
    strnlen_s(th_src, STATIC_BUF_SIZE - 1);
}

void
test_strnlen_s_src_size_NO_compile_error (void)
{
    /* Expect compile time error */
    strnlen_s(th_src, STATIC_BUF_SIZE);
}

void
test_strnlen_s_src_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    strnlen_s(th_src, STATIC_BUF_SIZE + 1);
}

/* For strstr_s () */
void
test_strstr_s_dst_size_minus_1_NO_compile_error (void)
{
    char *substr;

    /* Expect no compile time error */
    strstr_s(th_dst, STATIC_BUF_SIZE - 1, th_src, STATIC_BUF_SIZE, &substr);
}

void
test_strstr_s_dst_size_NO_compile_error (void)
{
    char *substr = NULL;

    /* Expect no compile time error */
    strstr_s(th_dst, STATIC_BUF_SIZE, th_src, STATIC_BUF_SIZE, &substr);
}

void
test_strstr_s_dst_size_plus_1_compile_error (void)
{
    char *substr = NULL;

    /* Expect compile time error */
    strstr_s(th_dst, STATIC_BUF_SIZE + 1, th_src, STATIC_BUF_SIZE, &substr);
}
