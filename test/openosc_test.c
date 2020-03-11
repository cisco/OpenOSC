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
#include <string.h>

/* Testing OpenOSC public header for all 4 mapping cases. */

static void openosc_test_strcpy(void) {
    char dst4[20] = "dst4"; char src4[15] = "src4";
    //memcpy(dst4, src4, 22);  /* overflow */
    //memcpy(dst4, src4, 18);  /* overread */
    strncpy(dst4, src4, 4);
    strcpy(dst4, src4);
    printf("Line %d, func %s, dst4 is: %s\n", __LINE__, __FUNCTION__, dst4);
    strncat(dst4, src4, 4);
    printf("Line %d, func %s, dst4 is: %s\n", __LINE__, __FUNCTION__, dst4);
    strncpy(dst4, src4, strnlen(dst4, 5));
}

int openosc_test_memcpy(void) {
    /* volatile so the compiler can’t know the value */
    volatile int len = 8;
    char dst[5];
    char src[20] = "I am the source";
#if 0
/* comment out to avoid compile-time error */
    char dst2[30];
    volatile char *mydst = dst2;
    memcpy(dst2, src, 25);          /* src over-read CASE 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    len = 26;
    memcpy(dst2, src, len);          /* src over-read CASE 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy((void *)(&len+2), src, len);       /* src over-read CASE 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 7);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 8);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy((void *)(&len+2), src, 21);           /* case 4, actually src over-read CASE2 ???? */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    memcpy(dst, (void *)(&len+2), 4);          /* case 1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 4);          /* case 1, actually src over-read CASE1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    len = (dst[3]-dst[2])/20 ;
    memcpy(dst, src, len);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    len = (dst[3]-dst[2])/5 + 5 ;
    memcpy(dst, src, len);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#if 0
    memcpy((void *)(&len+2), (void *)(&len+3), 1);           /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy((void *)(&len+2), src, 1);           /* case 4, actually src over-read CASE1 ???? */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    printf("End of testing memcpy!\n");
    return 0;
}

int main(void) {
    openosc_test_strcpy();
    return openosc_test_memcpy();
}


