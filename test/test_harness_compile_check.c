/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */
#include <stdio.h>
#include <string.h>
#include "test_harness_bosc.h"

char th_dst[STATIC_BUF_SIZE];            /* Destination buffer */
char th_src[STATIC_BUF_SIZE];            /* Source buffer */
char th_src_one_less[STATIC_BUF_SIZE-1]; /* Smaller than dest buffer */
char th_src_one_more[STATIC_BUF_SIZE+1]; /* Larger than dest buffer */


/*
 * This file should cause compilation to fail.  Build with make break.
 * OSC remap compilation testing
 */
void
test_memcpy_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    memcpy(th_dst, th_src, STATIC_BUF_SIZE - 1);
}

void
test_memcpy_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    memcpy(th_dst, th_src, STATIC_BUF_SIZE);
}

void
test_memcpy_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    memcpy(th_dst, th_src, STATIC_BUF_SIZE + 1);
}

// memmove checker functions added below
void
test_memmove_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    memmove(th_dst, th_src, STATIC_BUF_SIZE - 1);
}

void
test_memmove_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    memmove(th_dst, th_src, STATIC_BUF_SIZE);
}

void
test_memmove_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    memmove(th_dst, th_src, STATIC_BUF_SIZE + 1);
}

// memset checker functions added below
void
test_memset_dst_size_minus_1_NO_compile_error (void)
{
    /* Expect no compile time error */
    memset(th_dst, '\0', STATIC_BUF_SIZE - 1);
}

void
test_memset_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    memset(th_dst, '\0', STATIC_BUF_SIZE);
}

void
test_memset_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    memset(th_dst, '\0', STATIC_BUF_SIZE+1);
}

//bcopy checker functions added below
void
test_bcopy_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    bcopy(th_src, th_dst, STATIC_BUF_SIZE - 1);
}

void
test_bcopy_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    bcopy(th_src, th_dst, STATIC_BUF_SIZE);
}

void
test_bcopy_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    bcopy(th_src, th_dst, STATIC_BUF_SIZE + 1);
}

//bzero checker functions added below
void
test_bzero_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    bzero(th_dst, STATIC_BUF_SIZE - 1);
}

void
test_bzero_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    bzero(th_dst, STATIC_BUF_SIZE);
}

void
test_bzero_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error */
    bzero(th_dst, STATIC_BUF_SIZE + 1);
}

//strcpy checker functions added below
void
test_strcpy_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    strcpy(th_dst, th_src_one_less);
}

void
test_strcpy_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    strcpy(th_dst, th_src);
}

void
test_strcpy_dst_size_plus_1_compile_error (void)
{
    char dst[6] = "Hello";
    char src[12] = "Hello World";

    /* Expect compile time error */
    strcpy(dst, src);
}

//strncpy checker functions added below
void
test_strncpy_dst_size_minus_1_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncpy(th_dst, th_src, STATIC_BUF_SIZE - 1);
}

void
test_strncpy_dst_size_NO_compile_error (void)
{

    /* Expect no compile time error */
    strncpy(th_dst, th_src, STATIC_BUF_SIZE);
}

void
test_strncpy_dst_size_plus_1_compile_error (void)
{

    /* Expect compile time error, dst is less than the src */
    strncpy(th_dst, th_src_one_more, STATIC_BUF_SIZE + 1);
}

void
test_strncpy_beyond_src_size_compile_error (void)
{

    /* Expect compile time error, copying data beyond the
    limit of src */
    strncpy(th_dst, th_src, STATIC_BUF_SIZE + 1);
}

//strcat checker functions added below
void
test_strcat_dst_size_minus_1_NO_compile_error (void)
{
    char dst[13] = "Hello";
    char src[7] = " world";

    /* Expect no compile time error */
    strcat(dst, src);
}

void
test_strcat_dst_size_NO_compile_error (void)
{
    char dst[12] = "Hello";
    char src[7] = " world";

    /* Expect no compile time error */
    strcat(dst, src);
}

void
test_strcat_dst_size_plus_1_compile_error (void)
{
    char dst[11] = "Hello";
    char src[7] = " world";

    /* Expect compile time error, not enough
    space to store '\0' character*/
    strcat(dst, src);
}

//strncat checker functions added below
void
test_strncat_dst_size_minus_1_NO_compile_error (void)
{
    char dst[13] = "Hello";
    char src[7] = " world";

    /* Expect no compile time error */
    strncat(dst, src, 7);
}

void
test_strncat_dst_size_NO_compile_error (void)
{
    char dst[12] = "Hello";
    char src[7] = " world";

    /* Expect no compile time error */
    strncat(dst, src, 7);
}

void
test_strncat_dst_size_plus_1_compile_error (void)
{
    char dst[11] = "Hello";
    char src[7] = " world";

    /* Expect compile time error, due to concatenating 
    src size is greater than dst*/
    strncat(dst, src, 12);
}

void
test_strncat_src_not_null_terminated_compile_error (void)
{
    char dst[12] = "Hello";
    char src[6] = " world";

    /* Expect compile time error, no '\0' character
    in first 6 bytes of src*/
    strncat(dst, src, 6);
}

//strlen checker functions added below
int
test_strlen_dst_size_minus_1_NO_compile_error (void)
{
    char dst[13] = "Hello World";

    /* Expect no compile time error */
    return strlen(dst);
}

int
test_strlen_dst_size_NO_compile_error (void)
{
    char dst[12] = "Hello World";

    /* Expect no compile time error */
    return strlen(dst);
}

int
test_strlen_dst_size_plus_1_compile_error (void)
{
    char dst[12] = "Hello World.";

    /* Expect compile time error, no space to 
    store null character */
    return strlen(dst);
}

//strnlen checker functions added below
int
test_strnlen_dst_size_minus_1_NO_compile_error (void)
{
    char dst[13] = "Hello World";

    /* Expect no compile time error */
    return strnlen(dst, 13);
}

int
test_strnlen_dst_size_NO_compile_error (void)
{
    char dst[12] = "Hello World";

    /* Expect no compile time error */
    return strnlen(dst, 12);
}

int
test_strnlen_dst_size_plus_1_compile_error (void)
{
    char dst[12] = "Hello World.";

    /* Expect compile time error, no space to 
    store null character */
    return strnlen(dst, 12);
}

// Global buffer to fill by vsprint anf vsnprintf functions
char buffer[STATIC_BUF_SIZE];

// Generic driver function for vsprintf
int
vsdriver_func(char *format, ...)
{
    va_list vptr;
    int ret;

    va_start(vptr, format); 
    /* write the content to buffer */
    ret = vsprintf(buffer, format, vptr);
    va_end(vptr);

    return ret;
}

// vsprintf checker functions added below
void
test_vsprintf_dst_size_minus_1_NO_compile_error(void)
{
    char str[STATIC_BUF_SIZE-1] = "ABCDEFGH";

    /* Expect NO compile time error */
    vsdriver_func("%s", str);
}

void
test_vsprintf_dst_size_NO_compile_error(void)
{
    char str[STATIC_BUF_SIZE] = "ABCDEFGHI";

    /* Expect NO compile time error */
    vsdriver_func("%s", str);
}

void
test_vsprintf_dst_size_plus_1_compile_error(void)
{
    char str[STATIC_BUF_SIZE+1] = "ABCDEFGHIJ";

    /* Expect compile time error */
    vsdriver_func("%s", str);
}

// Generic driver function for vsnprintf
int
vsndriver_func(size_t size, char *format, ...)
{
    va_list vptr;
    int ret;

    va_start(vptr, format); 
    /* write the content to buffer */
    ret = vsnprintf(buffer, size, format,  vptr);
    va_end(vptr);

    return ret;
}

// vsnprintf checker functions added below
void
test_vsnprintf_dst_size_minus_1_NO_compile_error(void)
{
    char str[STATIC_BUF_SIZE-1] = "ABCDEFGH";

    /* Expect NO compile time error */
    vsndriver_func(STATIC_BUF_SIZE, "%s", str);
}

void
test_vsnprintf_dst_size_NO_compile_error(void)
{
    char str[STATIC_BUF_SIZE] = "ABCDEFGHI";

    /* Expect NO compile time error */
    vsndriver_func(STATIC_BUF_SIZE, "%s", str);
}

void
test_vsnprintf_dst_size_plus_1_compile_error(void)
{
    char str[STATIC_BUF_SIZE+1] = "ABCDEFGHIJ";

    /* Expect compile time error */
    vsndriver_func(STATIC_BUF_SIZE, "%s", str);
}

void
test_vsnprintf_dst_size_beyond_compile_error(void)
{
    char str[STATIC_BUF_SIZE+1] = "ABCDEFGHIJ";

    /* Expect compile time error */
    vsndriver_func(STATIC_BUF_SIZE + 4, "%s", str);
}

/*
 * This main function is here to allow "make break" to work in
 * the case OSC_COMPILE_CHK is set to OSC_ASSERT_USE_RUNTIME_CHK
 */
int main(void)
{
    /* No op */
    return 1;
}
