/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "openosc_common.h"

/* Mapping for memcpy */

void *
__openosc_memcpy_to_buf(size_t dest_len, size_t src_len, void *dst, const void *src, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if ((dest_len != (size_t) -1) && (dest_len != 0) && (len > dest_len)) {
        if (openosc_log) {
	    openosc_danger_error("memcpy destination", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }

    if ((src_len != (size_t) -1) && (src_len != 0) && (len > src_len)) {
        if (openosc_log) {
	    openosc_danger_error("memcpy source", src_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    if (dest_len <= 0) {
	        len = src_len;
	    } else {
	        len = MIN(src_len, dest_len);
	    }
	}
    }

#undef memcpy
    return (memcpy(dst, src, len));
}

/* Mapping for memmove */

void *
__openosc_memmove_to_buf(size_t dest_len, size_t src_len, void *dst, const void *src, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if ((dest_len != (size_t) -1) && (dest_len != 0) && (len > dest_len)) {
        if (openosc_log) {
	    openosc_danger_error("memmove destination", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }

    if ((src_len != (size_t) -1) && (src_len != 0) && (len > src_len)) {
        if (openosc_log) {
	    openosc_danger_error("memmove source", src_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    if (dest_len <= 0) {
	        len = src_len;
	    } else {
	        len = MIN(src_len, dest_len);
	    }
	}
    }

#undef memmove
    return (memmove(dst, src, len));
}

/* Mapping for memset */

void *
__openosc_memset_to_buf(size_t dest_len, void *dst, int c, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("memset", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }
#undef memset
    return (memset(dst, c, len));
}

/* Mapping for bcopy */

void
__openosc_bcopy_to_buf(size_t dest_len, size_t src_len, const void *src, void *dst, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if ((dest_len != (size_t) -1) && (dest_len != 0) && (len > dest_len)) {
	if (openosc_log) {
	    openosc_danger_error("bcopy destination", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }

    if ((src_len != (size_t) -1) && (src_len != 0) && (len > src_len)) {
        if (openosc_log) {
	    openosc_danger_error("bcopy source", src_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    if (dest_len <= 0) {
	        len = src_len;
	    } else {
	        len = MIN(src_len, dest_len);
	    }
	}
    }

#undef bcopy
    bcopy(src, dst, len);
}

/* Mapping for bzero */

void
__openosc_bzero_to_buf(size_t dest_len, void *dst, size_t len)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("bzero", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }
#undef bzero
    bzero(dst, len);
}

/* Mapping for strcpy */

char *
__openosc_strcpy_to_buf (size_t dest_len, char *dst, const char *src)
{
    size_t len = strlen(src);
    char *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    
    if ((len + 1) > dest_len) {
        if (openosc_log) {
	    openosc_danger_error("strcpy", dest_len, len);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len - 1;
	}
    }
#undef strcpy
    rstr = strncpy(dst, src, len);
    *(rstr + len) = '\0';
    return (rstr);
}

/* Mapping for strncpy */

char *
__openosc_strncpy_to_buf (size_t dest_len, char *dst,
		  const char *src, size_t len)
{
    char *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
	    openosc_danger_error("strncpy", dest_len, len);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    rstr = strncpy(dst, src, dest_len);
	    dst[dest_len - 1] = '\0';
	    return (rstr);
	}
    }
#undef strncpy
    rstr = strncpy(dst, src, len);
    return (rstr);
}

/* Mapping for strcat */

char *
__openosc_strcat_to_buf (size_t dest_len, char *dst, const char *src)
{
    size_t len = strlen(src);
    size_t dst_len_to_null = strlen(dst);
    char *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dest_len < (len + dst_len_to_null + 1)) {
        if (openosc_log) {
	    openosc_danger_error("strcat", dest_len, len);
        }
        if ((dst_len_to_null + 1) >= dest_len) {
            return (dst);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len - dst_len_to_null - 1;
	}
    }
#undef strcat
    rstr = strncat(dst, src, len);
    return (rstr);
}

/* Mapping for strncat */

char *
__openosc_strncat_to_buf (size_t dest_len, char *dst,
		  const char *src, size_t len)
{
    size_t dst_len_to_null = strlen(dst);
    char *rstr;
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dest_len < (MIN(strlen(src), len) + dst_len_to_null + 1)) {
        if (openosc_log) {
	    openosc_danger_error("strncat", dest_len, len);
        }
        if ((dst_len_to_null + 1) >= dest_len) {
            return (dst);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len - dst_len_to_null - 1;
	}
    }
#undef strncat
    rstr = strncat(dst, src, len);
    return (rstr);
}

/* Mapping for strnlen */

size_t
__openosc_strnlen_from_buf(size_t len, const char *src, size_t maxlen)
{
    if (maxlen > len) {
	if (openosc_log) {
	    openosc_danger_error("strnlen", len, maxlen);
	}
    }
#undef strnlen
    return strnlen(src, maxlen);
}

/* Mapping for vsnprintf */

int
__openosc_vsnprintf_to_buf (size_t dest_len, char *str, size_t len,
		    const char *fmt, va_list ap)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (len > dest_len) {
        if (openosc_log) {
	    openosc_danger_error("vsnprintf", dest_len, len);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
	    abort();
	}
	if (openosc_truncate) {
	    len = dest_len;
	}
    }
#undef vsnprintf
    return (vsnprintf(str, len, fmt, ap));
}
