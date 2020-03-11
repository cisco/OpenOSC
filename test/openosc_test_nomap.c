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

/* Testing for OpenOSC nomap functionality */

int openosc_test_memcpy(void) {
    int len = 8;
    char dst[5] = "";
    char src[20] = "I am the source";
    memcpy(dst, src, 4);          /* case 1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
/* Below code may cause SSP (Stack Smashing Protector) to abort the process */
#if 0
    memcpy(dst, src, 7);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 8);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    memcpy(dst, src, (dst[3]-dst[2])/20);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(&len-1, src, 1);           /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    printf("End of testing memcpy!\n");
    return 0;
}

int openosc_test_memset(void) {
    int len = 8;
    char dst[5];
    char src[20] = "I am the source";
    memset(dst, 0, 4);          /* case 1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
/* Below code may cause SSP (Stack Smashing Protector) to abort the process */
#if 0
    memset(dst, 0, 7);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memset(dst, 0, 8);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    memset(dst, src[0], (dst[3]-dst[2])/20);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memset(&len-1, 0, 1);           /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    printf("End of testing memset!\n");
    return 0;
}

int main(void) {
    openosc_test_memcpy();
    return openosc_test_memset();
}


