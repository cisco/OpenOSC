/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#ifndef __OPENOSC_FORTIFY_MAP_H__
#define __OPENOSC_FORTIFY_MAP_H__


#include "openosc_fortify_map_metric.h"


#ifndef _FORTIFY_SOURCE

#ifdef __cplusplus
#include <features.h>
extern "C"
{
#endif

#include "openosc_fortify_extern.h"

#if (OPENOSC_MAPPING_METHOD == OPENOSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_fortify_redirect_map.h"
#else
#include "openosc_fortify_redefine_map.h"
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif  /* __OPENOSC_FORTIFY_MAP_H__ */
