/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#include <stdio.h>

extern void *
__openosc_memcpy_to_buf(size_t dest_len, size_t src_len, void *dst, const void *src, size_t len);

/* Testing OpenOSC runtime check code */

int openosc_test_memcpy(void) {
    int len = 8;
    char dst[5];
    char src[20] = "I am the source";
    __openosc_memcpy_to_buf(5, 4, dst, src, 4);          /* case 1 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#if 1
    __openosc_memcpy_to_buf(5, 7, dst, src, 7);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    __openosc_memcpy_to_buf(5, 8, dst, src, 8);          /* case 2 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
#endif
    len = (dst[3]-dst[2])/20 ;
    __openosc_memcpy_to_buf(5, len, dst, src, len);  /* case 3 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    __openosc_memcpy_to_buf(5, 1, &len-1, src, 1);           /* case 4 */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    __openosc_memcpy_to_buf(5, 3, dst, src, 4);          /* src over-read */
    printf("Line %d, func %s, dst is: %s\n", __LINE__, __FUNCTION__, dst);
    printf("End of testing memcpy!\n");
    return 0;
}

int main(void) {
    return openosc_test_memcpy();
}


