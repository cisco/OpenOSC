/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


/* Uncomment the below line to do the real MSAN test for clang */
//#include "../include/openosc.h"
#include <stdio.h>
#include <string.h>

/* Test code for Memory Sanitier, which can be enabled via -fsanitize=memory. */
/* Note that memory sanitizer is only available with clang, not yet with gcc */
int main()
{
    char text[100];
    printf("Entering msan test\n");
    sprintf(text, "hello");
    printf("text len: %lu\n", strlen(text));
    return 0;
}

