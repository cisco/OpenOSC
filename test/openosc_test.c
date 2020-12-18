/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

//#include "../include/openosc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Testing OpenOSC public header for all 4 mapping cases. */

int openosc_test_memcpy(char *buf) {
    /* volatile so the compiler can’t know the value */
    volatile int len = 8;
    char dst[5];
    char src[20] = "I am the source";
    memcpy(dst, (void *)(&len+2), 4);  /* case 1, actually src over-read CASE8 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 4);          /* case 1, actually src over-read CASE1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#if 0
    void *ret = memcpy(dst, src, 14);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    len = time(NULL)%7;
    memcpy(dst, src, len);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(buf, src, 10);  /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, buf);
    memcpy(buf, src, 21);  /* case 4, actually src over-read CASEb */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, buf);
    printf("End of testing memcpy!\n");
    return 0;
}

int openosc_test_strncpy(char *buf) {
    /* volatile so the compiler can’t know the value */
    volatile int len = 8;
    char dst[5];
    char src[20] = "I am the source";
    strncpy(dst, (void *)(&len+2), 4);          /* case 1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    strncpy(dst, src, 4);          /* case 1, actually src over-read CASE1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#if 0
    strncpy(dst, src, 14);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    len = time(NULL)%5;
    strncpy(dst, src, len);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    strncpy(buf, src, 21);  /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, buf);
    printf("End of testing memcpy!\n");
    return 0;
}

int main(void) {
    srand(time(NULL));
    char *buf = malloc(25);
    (void)openosc_test_memcpy(buf);
    return openosc_test_strncpy(buf);
}


