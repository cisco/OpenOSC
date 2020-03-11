/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */
#include <stdio.h>
#include "test_harness_defs.h"
#include "test_harness_aux.h"

/*
 * This file tests object size checking across .o boundaries
 */

/*
 * The next two functions are simple cross object size checks
 */
size_t
bosc_th_test_aux_char (char *cptr)
{
    return __builtin_object_size(cptr, TH_SIZE_CHECK_1);
}

size_t
bosc_th_test_aux_struct_ptr (struct2 *s2ptr)
{
    return __builtin_object_size(s2ptr->s1ptr->char_buf_mid, TH_SIZE_CHECK_1);
}

/*
 * This function tests how object size checkers deal with objects whose size can
 * vary between fixed values at run-time.
 */
size_t
bosc_th_test_aux_flow_char (int flag)
{
    char *cptr;
    char char_buf1[STATIC_BUF_SIZE];
    char char_buf2[LARGER_BUF_SIZE];
    if (flag) {
	cptr = char_buf1;
    } else {
	cptr = char_buf2;
    }
    return __builtin_object_size(cptr, TH_SIZE_CHECK_1);
}
