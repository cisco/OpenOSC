/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */
#include "config.h"

/*
 * This function returns the package string
 */
const char * openosc_get_package_string (void)
{

    return (PACKAGE_STRING);

}

/*
 * This function returns the package name string
 */
const char * openosc_get_package_name (void)
{

    return (PACKAGE_NAME);

}

/*
 * This function returns the package versionstring
 */
const char * openosc_get_package_version (void)
{

    return (PACKAGE_VERSION);

}

