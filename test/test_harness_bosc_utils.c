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
#include <strings.h>
#include "test_harness_defs.h"
#include "test_harness_bosc.h"

void
bosc_th_print_test_conditions (char *testname, char *desc,
			       int num_param, th_test_param params[],
			       int expect_dcdi)
{
    int i;

    printf("\n========================================\n");
    printf("Test Name: %s \n", testname);
    printf("Test Description:\n    %s\n", desc);
    printf("Test Parameters:\n");
    for (i = 0; i < num_param; i++)
	printf("    %s = %i\n", params[i].name, params[i].value);
    printf("Expected Outcome:\n    %sDCDI error message\n",
	   expect_dcdi ? "" : "No ");
}

/*
 * bosc_th_setup_buffer
 *
 * Fill size bytes of buffer buf according to the fill_type
 *
 * Return FALSE on error, TRUE otherwise
 */
int
bosc_th_setup_buffer (char *buf, int size, th_fill_type fill_type)
{
    int i;

    if (!buf)
	return FALSE;

    switch (fill_type) {
    case TH_FILL_ZERO:
	bzero(buf, size);
	break;

    case TH_FILL_ONE:
	memset(buf, 0xff, size);
	break;

    case TH_FILL_SEQ:
	for (i = 0; i < size; i++)
	    buf[i] = (unsigned char)(i + 1);
	break;

    case TH_FILL_STR:
	for (i = 0; i < size-1; i++)
	    buf[i] = (unsigned char)(i + 'a');
	buf[size-1] = '\0';
	break;

    default:
	return FALSE;
    }

    return TRUE;
}

/*
 * bosc_th_print_mem
 *
 * print size bytes of buffer buf
 *
 * Return FALSE on error, TRUE otherwise
 */
int
bosc_th_print_mem (char *buf, int size)
{
    int i;

    if (!buf)
	return FALSE;

    printf("    ");
    for (i = 0; i < size; i++) {
	printf("0x%02x ", ((int)buf[i] != -1) ? buf[i] : 255);

	/* Print up to 16 bytes on a single line */
	if (15 == (i % 16))
	    printf ("\n    ");
    }
    printf("\n");
    return TRUE;
}

/*
 * bosc_th_print_result
 *
 * Perform memory comparision between two given buffers for the
 * specified size and print the test result based on pass_if_equal
 * condition. If pass_if_equal is TRUE and buf1 is the same as buf2
 * then a pass message is printed. Otherwise, fail message is printed.
 *
 * Return FALSE on error, TRUE otherwise
 */
int
bosc_th_print_result (const void *buf1, const void *buf2, size_t size,
		      th_pass_criteria criteria)
{
    int equal;

    equal = !memcmp(buf1, buf2, size);

    if ((criteria == TH_PASS_EQU && equal ) || (criteria == TH_PASS_EQU && !equal )) {
    	printf("\nMemory Comparison Passed\n");
    } else {
    	printf("\nMemory Comparison Failed\n");
    }
    return TRUE;
}

/*
 * bosc_th_print_result_safec
 *
 * This function will print the status of each function. safeC
 * API get passed, when expected outcome is No DCDI Error and 
 * the respective safec returns as EOK. Otherwise failure case. 
 */

void
bosc_th_print_result_safec(int result, int criteria)
{
    if (result == criteria) {
        printf ("safeC API Passed\n");
    } else {
        printf ("safeC API Failed\n");
    }
}

