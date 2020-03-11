/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_NOMAP_H__
#define __OPENOSC_FORTIFY_NOMAP_H__

/* if OSC metric feature is disabled, we can completely exclude this osc_nomap.h header */
#ifdef OPENOSC_METRIC_FEATURE_ENABLED

#include "openosc_fortify_nomap_metric.h"


#ifndef _FORTIFY_SOURCE

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_fortify_extern.h"

#if (OPENOSC_MAPPING_METHOD == OPENOSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_fortify_redirect_nomap.h"
#else
#include "openosc_fortify_redefine_nomap.h"
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif /* OPENOSC_METRIC_FEATURE_ENABLED */

#endif  /* __OPENOSC_FORTIFY_NOMAP_H__ */
