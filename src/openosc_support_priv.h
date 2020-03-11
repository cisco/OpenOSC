/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef _OPENOSC_SUPPORT_PRIV_H_
#define _OPENOSC_SUPPORT_PRIV_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  (!FALSE)
#endif

/* Undefine this to get a non-release version of the backtrace */
#define OSC_FINAL 1

/* Max number of backtrace frames to work with */
#define OSC_BT_FRAMES   32

/* Number of backtrace frames to skip when returning the backtrace */
#define OSC_FRAMES_TO_SKIP 3

/* Backtrace string buffer size */
#define OSC_BT_STR_MAX 512

/* Logging buffer size */
#define OSC_LOG_STR_MAX 512

/* Max /proc path */
#define OSC_PROC_PATH_MAX 256


#ifdef OSC_FINAL
#define OPENOSC_BT_TO_STR(bt_array, bt_count, bt_str, bt_str_max)   \
    openosc_bt2str_offset(bt_array, bt_count, bt_str, bt_str_max)
#else
#define OPENOSC_BT_TO_STR(bt_array, bt_count, bt_str, bt_str_max)   \
    openosc_bt2str_symbol(bt_array, bt_count, bt_str, bt_str_max)
#endif

#endif /* _OPENOSC_SUPPORT_PRIV_H_ */
