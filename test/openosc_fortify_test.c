/*
 * Copyright (c) 2020, Cisco Systems, Inc.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/cisco/openosc/LICENSE
 */

/* For some compilers like clang, recvfrom prototype in the below socket.h
 * header is affected if enabling _GNU_SOURCE. Specifically, __SOCKADDR_ARG
 * will get a different type definition than struct sockaddr * pointer.
 */
#include <sys/socket.h>
#define _GNU_SOURCE
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <poll.h>
#include <string.h>
#include <fcntl.h> /* Definition of AT_* constants */
#include <sys/types.h>
#include <stdio.h>
#include <wchar.h>
/* For rand() and time() system calls */
#include <stdlib.h>
#include <time.h>

#define OPENOSC_TEST_RAND_RANGE 5


int openosc_test_asprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    asprintf((char **) pmydstbuf , "%s", "abc");          /* function invocation */
    printf("End of testing asprintf\n");
    return 0;
}


int openosc_test_confstr(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    confstr(mylen, (char *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing confstr\n");
    return 0;
}


int openosc_test_dprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    dprintf(mylen, "%s", "abc");          /* function invocation */
    printf("End of testing dprintf\n");
    return 0;
}


int openosc_test_fgets(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fgets((char *) mydstbuf , mylen, (FILE *) mydstbuf );          /* function invocation */
    printf("End of testing fgets\n");
    return 0;
}


int openosc_test_fgets_unlocked(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fgets_unlocked((char *) mydstbuf , mylen, (FILE *) mydstbuf );          /* function invocation */
    printf("End of testing fgets_unlocked\n");
    return 0;
}


int openosc_test_fgetws(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fgetws((wchar_t *) mydstbuf , mylen, (FILE *) mydstbuf );          /* function invocation */
    printf("End of testing fgetws\n");
    return 0;
}


int openosc_test_fgetws_unlocked(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fgetws_unlocked((wchar_t *) mydstbuf , mylen, (FILE *) mydstbuf );          /* function invocation */
    printf("End of testing fgetws_unlocked\n");
    return 0;
}


int openosc_test_fprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fprintf((FILE *) mydstbuf , "%s", "abc");          /* function invocation */
    printf("End of testing fprintf\n");
    return 0;
}


int openosc_test_fread(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fread((void *) mydstbuf , mylen, 1, (FILE *) mydstbuf );          /* function invocation */
    //fread((void *) mydstbuf , mylen, 2, (FILE *) mydstbuf );          /* CASE2 */
    printf("End of testing fread\n");
    return 0;
}


int openosc_test_fread_unlocked(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fread_unlocked((void *) mydstbuf , mylen, 1, (FILE *) mydstbuf );          /* function invocation */
    printf("End of testing fread_unlocked\n");
    return 0;
}


int openosc_test_fwprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    fwprintf((FILE *) mydstbuf , L"%s", L"abc");          /* function invocation */
    printf("End of testing fwprintf\n");
    return 0;
}


int openosc_test_getcwd(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    getcwd((char *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing getcwd\n");
    return 0;
}


int openosc_test_getdomainname(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    getdomainname((char *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing getdomainname\n");
    return 0;
}


int openosc_test_getgroups(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    getgroups(mylen, (gid_t *) 0 );          /* function invocation */
    printf("End of testing getgroups\n");
    return 0;
}


int openosc_test_gethostname(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    gethostname((char *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing gethostname\n");
    return 0;
}


int openosc_test_gets(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    gets((char *) mydstbuf );          /* function invocation */
    printf("End of testing gets\n");
    return 0;
}


int openosc_test_getwd(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    getwd((char *) mydstbuf );          /* function invocation */
    printf("End of testing getwd\n");
    return 0;
}


/* No support for longjmp. */
#if 0
int openosc_test_longjmp(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    longjmp( 0 , mylen);          /* function invocation */
    printf("End of testing longjmp\n");
    return 0;
}
#endif


int openosc_test_mbsnrtowcs(void) {
    mbstate_t state;
    mbstate_t *ps = &state;
    size_t nms = 1;
    size_t nwc = 1;
    int mylen = 8;
    wchar_t dest[5];
    const char mysrcbuf[20] = "I am the source";
    const char ** src = (const char **)(&mysrcbuf);
    int len = 4;
    mbsnrtowcs(dest, src, nms, len, ps);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#if 0  /* comment out to avoid compile-time error */
    len = 7;
    mbsnrtowcs(dest, src, nms, len, ps);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#endif
    len = rand() % OPENOSC_TEST_RAND_RANGE;
    mbsnrtowcs(dest, src, nms, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (mysrcbuf[18]-dest[2])/1000000000;
    mbsnrtowcs(dest, src, nms, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (*((char *)&mylen - mysrcbuf[18] * 8))/1000000000;
    mbsnrtowcs(dest, src, nms, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = 1;
    mbsnrtowcs((wchar_t *)((char *)&mylen - dest[18] * 4), src, nms, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    mbsnrtowcs((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, nms, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    printf("End of testing mbsnrtowcs\n");
    return 0;
}


int openosc_test_mbsrtowcs(void) {
    mbstate_t state;
    mbstate_t *ps = &state;
    size_t nms = 1;
    size_t nwc = 1;
    int mylen = 8;
    wchar_t dest[5];
    const char mysrcbuf[20] = "I am the source";
    const char ** src = (const char **)(&mysrcbuf);
    int len = 4;
    mbsrtowcs(dest, src, len, ps);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#if 0  /* comment out to avoid compile-time error */
    len = 7;
    mbsrtowcs(dest, src, len, ps);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#endif
    len = rand() % OPENOSC_TEST_RAND_RANGE;
    mbsrtowcs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (mysrcbuf[18]-dest[2])/1000000000;
    mbsrtowcs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (*((char *)&mylen - mysrcbuf[18] * 8))/1000000000;
    mbsrtowcs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = 1;
    mbsrtowcs((wchar_t *)((char *)&mylen - dest[18] * 4), src, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    mbsrtowcs((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    printf("End of testing mbsrtowcs\n");
    return 0;
}


int openosc_test_mbstowcs(void) {
    int mylen = 8;
    wchar_t dest[5];
    const char src[20] = "I am the source";
    int n = 4;
    mbstowcs(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    mbstowcs(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    mbstowcs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    mbstowcs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    mbstowcs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    mbstowcs((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    mbstowcs((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing mbstowcs\n");
    return 0;
}


int openosc_test_mempcpy(void) {
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const char src[20] = "I am the source";
    int n = 4;
    mempcpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    mempcpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    mempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/20;
    mempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/20;
    mempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    mempcpy((void *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    mempcpy((void *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing mempcpy\n");
    return 0;
}


int openosc_test_poll(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    poll((struct pollfd *) mydstbuf , (nfds_t) 0 , mylen);          /* function invocation */
    printf("End of testing poll\n");
    return 0;
}


int openosc_test_ppoll(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    ppoll((struct pollfd *) mydstbuf , (nfds_t) 0 , (const struct timespec *) mysrcbuf , (const sigset_t *) mysrcbuf );          /* function invocation */
    printf("End of testing ppoll\n");
    return 0;
}


int openosc_test_pread(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    pread(mylen, (void *) mydstbuf , mylen, (off_t) 0 );          /* function invocation */
    printf("End of testing pread\n");
    return 0;
}


int openosc_test_printf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    printf("%s", "abc");          /* function invocation */
    printf("End of testing printf\n");
    return 0;
}


int openosc_test_read(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    read(mylen, (void *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing read\n");
    return 0;
}

#ifndef AT_FDCWD
#define AT_FDCWD -100
#endif

int openosc_test_readlinkat(void) {
    int dirfd = AT_FDCWD;
    int mylen = 8;
    char buf[5 * sizeof(char)];
    const char pathname[20] = "I am the source";
    int bufsiz = 4;
    readlinkat(dirfd, pathname, buf, bufsiz);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
#if 0  /* comment out to avoid compile-time error */
    bufsiz = 7;
    readlinkat(dirfd, pathname, buf, bufsiz);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
#endif
    bufsiz = rand() % OPENOSC_TEST_RAND_RANGE;
    readlinkat(dirfd, pathname, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = (pathname[18]-buf[2])/20;
    readlinkat(dirfd, pathname, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = (*((char *)&mylen - pathname[18] * 8))/20;
    readlinkat(dirfd, pathname, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = 1;
    readlinkat(dirfd, pathname, (char *)((char *)&mylen - buf[18] * 4), bufsiz);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    readlinkat(dirfd, pathname, (char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), bufsiz);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    printf("End of testing readlinkat\n");
    return 0;
}


int openosc_test_readlink(void) {
    int mylen = 8;
    char buf[5 * sizeof(char)];
    const char path[20] = "I am the source";
    int bufsiz = 4;
    readlink(path, buf, bufsiz);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
#if 0  /* comment out to avoid compile-time error */
    bufsiz = 7;
    readlink(path, buf, bufsiz);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
#endif
    bufsiz = rand() % OPENOSC_TEST_RAND_RANGE;
    readlink(path, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = (path[18]-buf[2])/20;
    readlink(path, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = (*((char *)&mylen - path[18] * 8))/20;
    readlink(path, buf, bufsiz);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    bufsiz = 1;
    readlink(path, (char *)((char *)&mylen - buf[18] * 4), bufsiz);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    readlink(path, (char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), bufsiz);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, bufsiz);
    printf("End of testing readlink\n");
    return 0;
}


int openosc_test_realpath(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    realpath((const char *) mysrcbuf , (char *) mydstbuf );          /* function invocation */
    printf("End of testing realpath\n");
    return 0;
}


int openosc_test_recv(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    recv(mylen, (void *) mydstbuf , mylen, mylen);          /* function invocation */
    printf("End of testing recv\n");
    return 0;
}


int openosc_test_recvfrom(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    recvfrom(mylen, (void *) mydstbuf , mylen, mylen, (struct sockaddr *) mydstbuf , (socklen_t *) mydstbuf );          /* function invocation */
    printf("End of testing recvfrom\n");
    return 0;
}


int openosc_test_snprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    snprintf((char *) mydstbuf , mylen, "%s", "abc");          /* function invocation */
    printf("End of testing snprintf\n");
    return 0;
}


int openosc_test_sprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    sprintf((char *) mydstbuf , "%s", "abc");          /* function invocation */
    printf("End of testing sprintf\n");
    return 0;
}


int openosc_test_stpcpy(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    stpcpy((char *) mydstbuf , (const char *) mysrcbuf );          /* function invocation */
    printf("End of testing stpcpy\n");
    return 0;
}


int openosc_test_stpncpy(void) {
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const char src[20] = "I am the source";
    int n = 4;
    stpncpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    stpncpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    stpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/20;
    stpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/20;
    stpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    stpncpy((char *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    stpncpy((char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing stpncpy\n");
    return 0;
}


int openosc_test_swprintf(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    swprintf((wchar_t *) mydstbuf , mylen, L"%s", L"abc");          /* function invocation */
    printf("End of testing swprintf\n");
    return 0;
}


int openosc_test_ttyname_r(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    ttyname_r(mylen, (char *) mydstbuf , mylen);          /* function invocation */
    printf("End of testing ttyname_r\n");
    return 0;
}


int openosc_test_vasprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vasprintf((char **) pmydstbuf , " ", myap);          /* function invocation */
    printf("End of testing vasprintf\n");
    return 0;
}


int openosc_test_vdprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vdprintf(mylen, " ", myap);          /* function invocation */
    printf("End of testing vdprintf\n");
    return 0;
}


int openosc_test_vfprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vfprintf((FILE *) mydstbuf , " ", myap);          /* function invocation */
    printf("End of testing vfprintf\n");
    return 0;
}


int openosc_test_vfwprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vfwprintf((FILE *) mydstbuf , L" ", myap);          /* function invocation */
    printf("End of testing vfwprintf\n");
    return 0;
}


int openosc_test_vprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vprintf(" ", myap);          /* function invocation */
    printf("End of testing vprintf\n");
    return 0;
}


int openosc_test_vsnprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vsnprintf((char *) mydstbuf , mylen, " ", myap);          /* function invocation */
    printf("End of testing vsnprintf\n");
    return 0;
}


int openosc_test_vsprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vsprintf((char *) mydstbuf , " ", myap);          /* function invocation */
    printf("End of testing vsprintf\n");
    return 0;
}


int openosc_test_vswprintf(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vswprintf((wchar_t *) mydstbuf , mylen, L" ", myap);          /* function invocation */
    printf("End of testing vswprintf\n");
    return 0;
}


int openosc_test_vwprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    va_list myap;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    vwprintf(L" ", myap);          /* function invocation */
    printf("End of testing vwprintf\n");
    return 0;
}


int openosc_test_wcpcpy(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const wchar_t mysrcbuf[20] = L"I am the source";
    const wchar_t **pmysrcbuf = (const wchar_t **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wcpcpy((wchar_t *) mydstbuf , (const wchar_t *) mysrcbuf );          /* function invocation */
    printf("End of testing wcpcpy\n");
    return 0;
}


int openosc_test_wcpncpy(void) {
    int mylen = 8;
    wchar_t dest[5];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wcpncpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wcpncpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wcpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wcpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wcpncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wcpncpy((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wcpncpy((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wcpncpy\n");
    return 0;
}


int openosc_test_wcrtomb(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    mbstate_t state;
    mbstate_t *ps = &state;
    size_t nms = 1;
    size_t nwc = 1;
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wcrtomb((char *) mydstbuf , (wchar_t) 0 , (mbstate_t *) mydstbuf );          /* function invocation */
    printf("End of testing wcrtomb\n");
    return 0;
}


int openosc_test_wcscat(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const wchar_t mysrcbuf[20] = L"I am the source";
    const wchar_t **pmysrcbuf = (const wchar_t **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wcscat((wchar_t *) mydstbuf , (const wchar_t *) mysrcbuf );          /* function invocation */
    printf("End of testing wcscat\n");
    return 0;
}


int openosc_test_wcscpy(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const wchar_t mysrcbuf[20] = L"I am the source";
    const wchar_t **pmysrcbuf = (const wchar_t **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wcscpy((wchar_t *) mydstbuf , (const wchar_t *) mysrcbuf );          /* function invocation */
    printf("End of testing wcscpy\n");
    return 0;
}


int openosc_test_wcsncat(void) {
    int mylen = 8;
    wchar_t dest[5];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wcsncat(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wcsncat(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wcsncat(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wcsncat(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wcsncat(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wcsncat((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wcsncat((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wcsncat\n");
    return 0;
}


int openosc_test_wcsncpy(void) {
    int mylen = 8;
    wchar_t dest[5 * sizeof(wchar_t)];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wcsncpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wcsncpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wcsncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wcsncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wcsncpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wcsncpy((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wcsncpy((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wcsncpy\n");
    return 0;
}


int openosc_test_wcsnrtombs(void) {
    mbstate_t state;
    mbstate_t *ps = &state;
    size_t nms = 1;
    size_t nwc = 1;
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const wchar_t mysrcbuf[20] = L"I am the source";
    const wchar_t ** src = (const wchar_t **)(&mysrcbuf);
    int len = 4;
    wcsnrtombs(dest, src, nwc, len, ps);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#if 0  /* comment out to avoid compile-time error */
    len = 7;
    wcsnrtombs(dest, src, nwc, len, ps);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#endif
    len = rand() % OPENOSC_TEST_RAND_RANGE;
    wcsnrtombs(dest, src, nwc, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (mysrcbuf[18]-dest[2])/20;
    wcsnrtombs(dest, src, nwc, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (*((char *)&mylen - mysrcbuf[18] * 8))/20;
    wcsnrtombs(dest, src, nwc, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = 1;
    wcsnrtombs((char *)((char *)&mylen - dest[18] * 4), src, nwc, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    wcsnrtombs((char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, nwc, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    printf("End of testing wcsnrtombs\n");
    return 0;
}


int openosc_test_wcsrtombs(void) {
    mbstate_t state;
    mbstate_t *ps = &state;
    size_t nms = 1;
    size_t nwc = 1;
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const wchar_t mysrcbuf[20] = L"I am the source";
    const wchar_t ** src = (const wchar_t **)(&mysrcbuf);
    int len = 4;
    wcsrtombs(dest, src, len, ps);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#if 0  /* comment out to avoid compile-time error */
    len = 7;
    wcsrtombs(dest, src, len, ps);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
#endif
    len = rand() % OPENOSC_TEST_RAND_RANGE;
    wcsrtombs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (mysrcbuf[18]-dest[2])/20;
    wcsrtombs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = (*((char *)&mylen - mysrcbuf[18] * 8))/20;
    wcsrtombs(dest, src, len, ps);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    len = 1;
    wcsrtombs((char *)((char *)&mylen - dest[18] * 4), src, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    wcsrtombs((char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, len, ps);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, len);
    printf("End of testing wcsrtombs\n");
    return 0;
}


int openosc_test_wcstombs(void) {
    int mylen = 8;
    char dest[5 * sizeof(char)];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wcstombs(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wcstombs(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wcstombs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/20;
    wcstombs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/20;
    wcstombs(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wcstombs((char *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wcstombs((char *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wcstombs\n");
    return 0;
}


int openosc_test_wctomb(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wctomb((char *) mydstbuf , (wchar_t) 0 );          /* function invocation */
    printf("End of testing wctomb\n");
    return 0;
}


int openosc_test_wmemcpy(void) {
    int mylen = 8;
    wchar_t dest[5];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wmemcpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wmemcpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wmemcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wmemcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wmemcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wmemcpy((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wmemcpy((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wmemcpy\n");
    return 0;
}


int openosc_test_wmemmove(void) {
    int mylen = 8;
    wchar_t dest[5];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wmemmove(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wmemmove(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wmemmove(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wmemmove(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wmemmove(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wmemmove((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wmemmove((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wmemmove\n");
    return 0;
}


int openosc_test_wmempcpy(void) {
    int mylen = 8;
    wchar_t dest[5];
    const wchar_t src[20] = L"I am the source";
    int n = 4;
    wmempcpy(dest, src, n);          /* case 1 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#if 0  /* comment out to avoid compile-time error */
    n = 7;
    wmempcpy(dest, src, n);          /* case 2 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
#endif
    n = rand() % OPENOSC_TEST_RAND_RANGE;
    wmempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (src[18]-dest[2])/1000000000;
    wmempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = (*((char *)&mylen - src[18] * 8))/1000000000;
    wmempcpy(dest, src, n);          /* case 3 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    n = 1;
    wmempcpy((wchar_t *)((char *)&mylen - dest[18] * 4), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    wmempcpy((wchar_t *)((char *)&mylen - rand() % OPENOSC_TEST_RAND_RANGE), src, n);          /* case 4 */
    printf("Line %d, func %s, copylen is: %d\n", __LINE__, __FUNCTION__, n);
    printf("End of testing wmempcpy\n");
    return 0;
}


int openosc_test_wmemset(void) {
    int mylen = 8;
    wchar_t mydstbuf[15 * sizeof(wchar_t)];
    wchar_t **pmydstbuf = (wchar_t **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wmemset((wchar_t *) mydstbuf , (wchar_t) 0 , mylen);          /* function invocation */
    printf("End of testing wmemset\n");
    return 0;
}


int openosc_test_wprintf(void) {
    int mylen = 8;
    char mydstbuf[15 * sizeof(char)];
    char **pmydstbuf = (char **)(&mydstbuf);
    const char mysrcbuf[20] = "I am the source";
    const char **pmysrcbuf = (const char **)(&mysrcbuf);
    printf("Line %d, func %s, mylen is: %d\n", __LINE__, __FUNCTION__, mylen);
    wprintf(L"%s", L"abc");          /* function invocation */
    printf("End of testing wprintf\n");
    return 0;
}

int main(void) {
    srand(time(NULL));
    (void)openosc_test_asprintf();
    (void)openosc_test_confstr();
    (void)openosc_test_dprintf();
    (void)openosc_test_fgets();
    (void)openosc_test_fgets_unlocked();
    (void)openosc_test_fgetws();
    (void)openosc_test_fgetws_unlocked();
    (void)openosc_test_fprintf();
    (void)openosc_test_fread();
    (void)openosc_test_fread_unlocked();
    (void)openosc_test_fwprintf();
    (void)openosc_test_getcwd();
    (void)openosc_test_getdomainname();
    (void)openosc_test_getgroups();
    (void)openosc_test_gethostname();
    (void)openosc_test_gets();
    (void)openosc_test_getwd();
    /* (void)openosc_test_longjmp(); */
    (void)openosc_test_mbsnrtowcs();
    (void)openosc_test_mbsrtowcs();
    (void)openosc_test_mbstowcs();
    (void)openosc_test_mempcpy();
    (void)openosc_test_poll();
    (void)openosc_test_ppoll();
    (void)openosc_test_pread();
    (void)openosc_test_printf();
    (void)openosc_test_read();
    (void)openosc_test_readlinkat();
    (void)openosc_test_readlink();
    (void)openosc_test_realpath();
    (void)openosc_test_recv();
    (void)openosc_test_recvfrom();
    (void)openosc_test_snprintf();
    (void)openosc_test_sprintf();
    (void)openosc_test_stpcpy();
    (void)openosc_test_stpncpy();
    (void)openosc_test_swprintf();
    (void)openosc_test_ttyname_r();
    (void)openosc_test_vasprintf();
    (void)openosc_test_vdprintf();
    (void)openosc_test_vfprintf();
    (void)openosc_test_vfwprintf();
    (void)openosc_test_vprintf();
    (void)openosc_test_vsprintf();
    (void)openosc_test_vswprintf();
    (void)openosc_test_vwprintf();
    (void)openosc_test_wcpcpy();
    (void)openosc_test_wcpncpy();
    (void)openosc_test_wcrtomb();
    (void)openosc_test_wcscat();
    (void)openosc_test_wcscpy();
    (void)openosc_test_wcsncat();
    (void)openosc_test_wcsncpy();
    (void)openosc_test_wcsnrtombs();
    (void)openosc_test_wcsrtombs();
    (void)openosc_test_wcstombs();
    (void)openosc_test_wctomb();
    (void)openosc_test_wmemcpy();
    (void)openosc_test_wmemmove();
    (void)openosc_test_wmempcpy();
    (void)openosc_test_wmemset();
    (void)openosc_test_wprintf();
    return 0;
}


