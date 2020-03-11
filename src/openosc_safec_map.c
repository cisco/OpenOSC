/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

#include <stdlib.h>
#include "config.h"
#ifdef HAVE_SAFEC_SAFE_LIB_H
#include <safec/safe_lib.h>
#else
#include <safe_lib.h>
#endif
#include "openosc_common.h"

extern size_t strlen (__const char *__s);

/* Mapping for memcmp_s */

errno_t
__openosc_memcmp_s_to_buf (size_t s1_len,
                   const void *s1, rsize_t s1max,
                   const void *s2,  rsize_t n, int *diff)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (s1max > s1_len) {
	if (openosc_log) {
	    openosc_danger_error("memcmp_s", s1_len, s1max);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            s1max = s1_len;
        }
    }
#undef memcmp_s
    return (memcmp_s(s1, s1max, s2, n, diff));
}

/* Mapping for memcpy_s */

errno_t
__openosc_memcpy_s_to_buf (size_t dest_len,
                   void *dest, rsize_t dmax, const void *src, rsize_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dmax > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("memcpy_s", dest_len, dmax);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            dmax = dest_len;
        }
    }
#undef memcpy_s
    return (memcpy_s(dest, dmax, src, n));
}

/* Mapping for strcat_s */

errno_t
__openosc_strcat_s_to_buf (size_t dest_len,
                   char *dest, rsize_t dmax, const char *src)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    size_t len = strlen(src);
    size_t dest_len_to_null = strlen(dest);

    if (dmax > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strcat_s dest", dest_len, dmax);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            dmax = dest_len;
        }
    }
    if (dest_len < (len + dest_len_to_null + 1)) {
        if (openosc_log) {
	    openosc_danger_error("strcat_s", dest_len, (len + dest_len_to_null + 1));
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            dmax = dest_len;
        }
    }
#undef strcat_s
    return (strcat_s(dest, dmax, src));
}

/* Mapping for strcmp_s */

errno_t
__openosc_strcmp_s_to_buf (size_t s1_len,
                   const char *s1, rsize_t s1max,
                   const char *s2, int *indicator)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (s1max > s1_len) {
	if (openosc_log) {
	    openosc_danger_error("strcmp_s", s1_len, s1max);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            s1max = s1_len;
        }
    }
    /*
     * may add later for checking
     * if (dmax > src buffer size) causes src reading overflow
     */
#undef strcmp_s
    return (strcmp_s(s1, s1max, s2, indicator));
}

/* Mapping for strcpy_s */

errno_t
__openosc_strcpy_s_to_buf (size_t dest_len,
                   char *dest, rsize_t dmax, const char *src)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dmax > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strcpy_s", dest_len, dmax);
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
	    dmax = dest_len;
	}
    }
#undef strcpy_s
    return (strcpy_s(dest, dmax, src));
}

/* Mapping for strncat_s */

errno_t
__openosc_strncat_s_to_buf (size_t dest_len,
		    char *dest, rsize_t dmax, const char *src, rsize_t n)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;
    size_t dest_len_to_null = strlen(dest);
    if (dmax > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strncat_s dest", dest_len, dmax);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            dmax = dest_len;
        }
    }
    if ((dest_len_to_null + n + 1) > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strncat_s src", dest_len, (dest_len_to_null + n + 1));
	}
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            n = dest_len - dest_len_to_null - 1;
        }
    }
#undef strncat_s
    return (strncat_s(dest, dmax, src, n));
}

/* Mapping for strncpy_s */

errno_t
__openosc_strncpy_s_to_buf (size_t dest_len,
		    char *dest, rsize_t dmax, const char *src, rsize_t slen)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (dmax > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strncpy_s dest", dest_len, dmax);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            dmax = dest_len;
        }
    }
    if (slen > dest_len) {
	if (openosc_log) {
	    openosc_danger_error("strncpy_s src", dest_len, slen);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            slen = dest_len;
        }
    }
#undef strncpy_s
    return (strncpy_s(dest, dmax, src, slen));
}

/* Mapping for strnlen_s */

size_t
__openosc_strnlen_s_to_buf (size_t s_len,
		    const char *s, size_t maxsize)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (maxsize > s_len) {
	if (openosc_log) {
	    openosc_danger_error("strnlen_s", s_len, maxsize);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            maxsize = s_len;
        }
    }
#undef strnlen_s
    return (strnlen_s(s, maxsize));
}

/* Mapping for strstr_s */

errno_t
__openosc_strstr_s_to_buf (size_t s1_len,
		   char *s1, rsize_t s1max,
		   const char *s2, rsize_t s2max, char **substring)
{
    unsigned int openosc_abort = OPENOSC_DEF_ABORT_STATE;

    if (s1max > s1_len) {
	if (openosc_log) {
	    openosc_danger_error("strstr_s", s1_len, s1max);
        }
	openosc_get_config(&openosc_abort);
	if (openosc_abort) {
            abort();
	}
	if (openosc_truncate) {
            s1max = s1_len;
        }
    }
#undef strstr_s
    return (strstr_s(s1, s1max, s2, s2max, substring));
}
