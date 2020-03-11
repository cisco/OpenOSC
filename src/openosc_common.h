/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef _OPENOSC_COMMON_H_
#define _OPENOSC_COMMON_H_

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef boolean
typedef int boolean;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MIN(a,b) ((a) < (b) ? a : b)

/* Default OSC logging, truncate and abort state */
#define OPENOSC_DEF_LOG_STATE      TRUE
#define OPENOSC_DEF_TRUNCATE_STATE TRUE
#define OPENOSC_DEF_ABORT_STATE    FALSE

#ifdef OPENOSC_RUNTIME_LOGGING_DISABLE
#define openosc_log FALSE
#else
#define openosc_log OPENOSC_DEF_LOG_STATE
#endif

#ifdef OPENOSC_RUNTIME_TRUNCATE_DISABLE
#define openosc_truncate FALSE
#else
#define openosc_truncate OPENOSC_DEF_TRUNCATE_STATE
#endif

#ifdef OPENOSC_RUNTIME_CONFIG_FILE
#define _OPENOSC_RUNTIME_CONFIG_FILE OPENOSC_RUNTIME_CONFIG_FILE
#else
#define _OPENOSC_RUNTIME_CONFIG_FILE "/etc/openosc.conf"
#endif

static inline void
openosc_get_config (unsigned int *abort_flag)
{
    int fd = 0;
    char c = 0;

    fd = open(_OPENOSC_RUNTIME_CONFIG_FILE, O_RDONLY);
    if (fd > 0) {
        (void)pread(fd, &c, 1, 0);
        if (c == '0' || c == 0) {
            *abort_flag = FALSE;
        } else {
            *abort_flag = TRUE;
        }
	close(fd);
    }
    return;
}

const char * openosc_get_package_string (void);
const char * openosc_get_package_name (void);
const char * openosc_get_package_version (void);
extern void openosc_danger_error (const char *func, size_t true_len, size_t len);

#endif /* _OPENOSC_COMMON_H_ */
