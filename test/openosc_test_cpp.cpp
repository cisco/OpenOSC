/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

#define OPENOSC_TEST_RAND_RANGE 20

int openosc_test_memcpy(void) {
    int len = 8;
    char dst[5];
    char src[20] = "I am the source";
    memcpy(dst, src, 4);          /* case 1 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    cout << "Line " << __LINE__ << ", func " << __FUNCTION__ << ", dst is: " << dst << endl;
#if 1
/* comment out to avoid compile-time error */
    memcpy(dst, src, 7);          /* case 2 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, 8);          /* case 2 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    memcpy(dst, src, rand()%10);  /* case 3 */
    memcpy(dst, src, (dst[3]-dst[2])/20);  /* case 3 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(dst, src, (dst[3]-dst[2])/5 + 5);  /* case 3 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy(&len+2, src, 1);           /* case 4 */
    //printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    memcpy((void *)((char *)&len - rand()%10), src, 2);          /* case 4 */
    cout << "End of testing memcpy!" << endl;
    return 0;
}

int openosc_test_mempcpy(void) {
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const char src[20] = "I am the source";
    int n = 4;
    mempcpy(dest, src, n);          /* case 1 */
#if  1 /* comment out to avoid compile-time error */
    n = 7;
    mempcpy(dest, src, n);          /* case 2 */
    n = 15;
    mempcpy(dest, src, n);          /* case 2 */
#endif
    //volatile int n2 = 9;
    mempcpy(dest, src, rand()%10);          /* case 3 */
    //n = (src[18]-dest[2])/20;
    //mempcpy(dest, src, n);          /* case 3 */
    //n = (*((char *)&mylen - src[18] * 8))/20;
    //mempcpy(dest, src, n);          /* case 3 */
    n = 1;
    mempcpy((void *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    mempcpy((void *)((char *)&mylen - rand()%10), src, n);          /* case 4 */
    cout << "End of testing mempcpy" << endl;
    return 0;
}

int main(void) {
    srand(time(NULL));
    (void)openosc_test_memcpy();
    (void)openosc_test_mempcpy();
    return 0;
}
