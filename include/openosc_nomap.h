/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */


#ifndef __OPENOSC_NOMAP_H__
#define __OPENOSC_NOMAP_H__

#include "openosc_nomap_metric.h"

#ifndef _FORTIFY_SOURCE

#include "openosc_fortify.h"

#if (OPENOSC_MAPPING_METHOD == OPENOSC_ASM_LABEL_REDIRECT_METHOD)
#include "openosc_redirect_nomap.h"
#else
#include "openosc_redefine_nomap.h"
#endif

#ifndef OPENOSC_FORTIFY_FUNCTIONS_DISABLE
#include "openosc_fortify_nomap.h"
#endif

#endif

#endif /*  __OPENOSC_NOMAP_H__ */

