/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#ifndef __OPENOSC_MAP_H__
#define __OPENOSC_MAP_H__

#include "openosc_map_metric.h"

#ifndef _FORTIFY_SOURCE

#include "openosc_fortify.h"

#if (OPENOSC_MAPPING_METHOD == OPENOSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_redirect_map.h"
#else
#include "openosc_redefine_map.h"
#endif

#ifndef OPENOSC_FORTIFY_FUNCTIONS_DISABLE
#include "openosc_fortify_map.h"
#endif

#endif

#endif /* __OPENOSC_MAP_H__ */
