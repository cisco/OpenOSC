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

/* Test code for Address Sanitier, which can be enabled by adding -fsanitize=address */

int g_var = 10;
char g_dst[10] = "";

int openosc_test_stack_overflow(int n) {
    int stack_array[10];
    stack_array[1] = 0;
    printf("Entering %s: n: %d\n", __FUNCTION__, n);
    return stack_array[n + 10];
}

int openosc_test_stack_overflow2(int n) {
    int i;
    int len = 5;
    char *p_var = (char *)&g_var + 1;
    char dst[10];
    char src[] = "I am source";
    for (i=0; i<5; i++) {
        memcpy(dst, src, 4);    /* case 1 */
    }
    printf("Entering %s: n: %d &i: %p &g_var: %p\n", __FUNCTION__, n, &i, &g_var);
    //memcpy(p_var+1, src, n+5);      /* CASE 4 */
    printf("Leaving %s: n: %d\n", __FUNCTION__, n);
    return 0;
}

int openosc_test_stack_overflow3(int n) {
    int len = 5;
    char *p_var = (char *)&g_var + 1;
    char *dst = (char *)malloc(n);
    char src[] = "I am source";
    printf("Entering %s: n: %d dst: %p &g_var: %p\n", __FUNCTION__, n, dst, &g_var);
    //memcpy(dst+1, src, 2+n);      /* CASE 4 */
    printf("Leaving %s: n: %d\n", __FUNCTION__, n);
    return 0;
}

int main(void) {
    int a = openosc_test_stack_overflow(1);
    a = openosc_test_stack_overflow2(3);
    return openosc_test_stack_overflow3(5);
}


