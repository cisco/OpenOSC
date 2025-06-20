/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

/*
 * Needed early so that we can get Dl_info.
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <execinfo.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <syslog.h>
#include "openosc_support_priv.h"
#include "openosc_common.h"

#define OPENOSC_PACKAGE_STR openosc_get_package_string()
#define OPENOSC_VERSION openosc_get_package_version()

#ifdef OSC_FINAL
/*
 * openosc_get_process_name
 *
 * Get the process name
 *   name: buffer to hold the process name
 *   name_len: maximum number of characters the name buffer can hold
 *
 * Return Value
 *    TRUE on success
 *    FALSE on failure and content of name is unknown
 */
static int
openosc_get_process_name(char *name, int name_len)
{
    char path[OSC_PROC_PATH_MAX];
    FILE* fd;

    if (!name)
	return FALSE;

    snprintf(path, OSC_PROC_PATH_MAX, "/proc/%d/cmdline", getpid());
    fd = fopen(path, "r");
    if (fd != NULL) {
        size_t size = fread((void *)name, sizeof(char), name_len, fd);
	if (size > 0) {
	    name[size-1]='\0';
	}
	fclose(fd);
        return TRUE;
    }
    return FALSE;
}

/*
 * openosc_bt2str_offset
 *
 * ### This implementation is for RELEASE image only ###
 *
 * Convert array of backtrace addresses to a string of
 * library name + offset from base address.
 *   bt:     array of addresses
 *   frames: number of addresses in bt
 *   bt_str: pointer to the memory to write the backtrace string to
 *   bt_str_max: max bytes in bt_str
 *
 * Return Value
 *    TRUE on success
 *    FALSE on failure and content of bt_str is unknown
 */
static int
openosc_bt2str_offset (void *bt[], int frames, char *bt_str,
		   unsigned int bt_str_max)
{
    Dl_info info;
    char *bname;
    int f;
    unsigned int s;
    char process_name[OSC_BT_STR_MAX];

    /*
     * Need a minimum of 2 bytes in case we don't have enough room,
     * we can write "*" and NULL character to indicate the backtrace
     * string was truncated
     */
    if ((!bt_str) || (bt_str_max < 2))
	return FALSE;

    /* Get process name */
    if (FALSE == openosc_get_process_name(bt_str, bt_str_max)) {
	return FALSE;
    }

    strncpy(process_name, bt_str, OSC_BT_STR_MAX - 1);
    process_name[OSC_BT_STR_MAX - 1] = '\0';

    /* Add a space after process name */
    if (strlen(bt_str) < (bt_str_max - 1))
	strcat(bt_str, " ");

    s = strlen(bt_str);

    for(f = 0; f < frames; f++) {
        if (dladdr(bt[f], &info)) {
            /*
             * Make sure we have enough space
             */
            if (s >= bt_str_max ) {
                bt_str[bt_str_max - 2] = '*';
                bt_str[bt_str_max - 1] = '\0';
                break;
            }
            if (strcmp(info.dli_fname, process_name) == 0) {
                /*
                 * If the symbol is in us, just print the offset
                 */
                s += snprintf(&bt_str[s], (bt_str_max - s), "+%p ",
			      (void *)((char *)bt[f] - (char *)info.dli_fbase));
            } else {
                bname = basename(info.dli_fname);
                /*
                 * Otherwise print library+offset
                 */
                s += snprintf(&bt_str[s], (bt_str_max - s), "%s+%p ",
                              bname, (void *)((char *)bt[f] - (char *)info.dli_fbase));
	    }
        }
    }

    if (s >= bt_str_max) {
        bt_str[bt_str_max - 2] = '*';
        bt_str[bt_str_max - 1] = '\0';
    }

    return TRUE;
}
#else
/*
 * openosc_bt2str_symbol
 *
 * ### This implementation is for NON-RELEASE image only ###
 *
 * Convert array of backtrace addresses to a string of
 * function names.
 *   bt:     array of addresses
 *   frames: number of addresses in bt
 *   bt_str: pointer to the memory to write the backtrace string to
 *   bt_str_max: max bytes in bt_str
 *
 * Return Value
 *    TRUE on success
 *    FALSE on failure and content of bt_str is unknown
 */
static int
openosc_bt2str_symbol (void *bt[], int frames, char *bt_str,
		   unsigned int bt_str_max)
{
    int i, buf_bytes, snp_bytes;
    char **name_arr = NULL;

    if ((!bt_str) || (!bt_str_max))
	return FALSE;

    /* Convert array of backtrace addresses to function names */
    name_arr = backtrace_symbols(bt, frames);
    if (NULL == name_arr) {
	return FALSE;
    }

    buf_bytes = 0;
    for (i = 0; i < frames; i++) {
	snp_bytes = snprintf(&bt_str[buf_bytes], bt_str_max - buf_bytes,
			     " %s", name_arr[i]);
	/*
	 * If not enough room and the output was truncated, removed
	 * the last write and discard the rest of the backtrace
	 */
	if (buf_bytes + snp_bytes >= bt_str_max) {
	    bt_str[buf_bytes] = '\0';
	    break;
	}
	buf_bytes += snp_bytes;
    }

    free(name_arr);

    return TRUE;
}
#endif /* OSC_FINAL */

/*
 * openosc_get_backtrace
 *
 * Description
 *    Return a pointer to a NULL terminated backtrace string in backtrace_str.
 *    The string should be freed by calling osc_free_backtrace() API.
 *
 * Return Value
 *    1 for success getting a backtrace
 *    0 for failure, backtrace_str set to NULL
 */
static int openosc_get_backtrace (char **backtrace_str)
{
    void *bt[OSC_BT_FRAMES];
    int frames, status;
    
    if (!backtrace_str)
	return FALSE;

    /* Allocate buffer to hold the backtrace string */
    *backtrace_str = malloc(OSC_BT_STR_MAX);
    if (NULL == *backtrace_str)
	return FALSE;

    /* Get the backtrace */
    frames = backtrace(bt, OSC_BT_FRAMES);
    if (frames <= OSC_FRAMES_TO_SKIP) {
	free(*backtrace_str);
	*backtrace_str = NULL;
        return FALSE;
    }

    /*
     * Convert backtrace frames to string
     *
     * Skip first OSC_FRAMES_TO_SKIP frames to get to the real function
     * that cause the overflow. Don't want to see this function and its
     * caller in every backtrace.
     */
    status = OPENOSC_BT_TO_STR(&bt[OSC_FRAMES_TO_SKIP],
			   frames - OSC_FRAMES_TO_SKIP,
			   *backtrace_str, OSC_BT_STR_MAX);

    if (FALSE == status) {
        free(*backtrace_str);
	*backtrace_str = NULL;
    }

    return status;
}

/*
 * osc_free_backtrace
 *
 * Description
 *    Free the backtrace string memory allocated by osc_get_backtrace()
 */
static void openosc_free_backtrace (char *backtrace_str)
{
    if (backtrace_str)
	free(backtrace_str);
}

/*
 * openosc_danger_error
 *
 * Description
 *    Output a data corruption, data inconsistency syslog message
 */
void openosc_danger_error (const char *func, size_t true_len, size_t len)
{
    char *backtrace_str;

    /* Get backtrace string */
    if (openosc_get_backtrace(&backtrace_str) != TRUE) {
	syslog(LOG_CRIT, "LIB-OPENOSC: Error getting backtrace\n");
        return;
    }

#ifdef OSC_FINAL
    syslog(LOG_CRIT, "DATACORRUPTION-DATAINCONSISTENCY: %s "
	   "Copy error -Traceback= %s\n", OPENOSC_PACKAGE_STR, backtrace_str);
#else
    syslog(LOG_CRIT, "DATACORRUPTION-DATAINCONSISTENCY: %s "
	   "Attempt to %s %zu bytes should have been %zu bytes, -Traceback= %s\n",
	   OPENOSC_PACKAGE_STR, func, len, true_len, backtrace_str);
#endif

    /* Free the backtrace string */
    openosc_free_backtrace(backtrace_str);
}

