#include <sys/time.h>
#include <sys/select.h>

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */
#include "tlpi_hdr.h"

static void usageError(const char *progName) 
{
    fprintf(stderr, "Usage: %s {timeout|-} fd-num[rw]...\n", progName);
    fprintf(stderr, "    - means infinite timeout; \n");
    fprintf(stderr, "    r = monitor for read; \n");
    fprintf(stderr, "    w = monitor for write; \n\n");
    fprintf(stderr, "    e.g.: %s - Orw 1w\n", progName);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[]) 
{
    fd_set readfds, writefds;
    int ready, nfds, fd, numRead, j;
    struct timeval timeout;
    struct timeval *pto;
    char buf[10];

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageError(argv[0]);

    if (strcmp(argv[1], "-") == 0 ) {
        pto = NULL;
    } else {
        pto = &timeout;
        timeout.tv_sec = getLong(argv[1], 0, "timeout");
        timeout.tv_usec = 0;
    }

    nfds = 0;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    for (j = 2; j < argc; j++) {
        numRead = sscanf(argv[j], "%d%2[rw]", &fd, buf);

        if (numRead != 2) 
            usageError(argv[0]);

        if (fd >= FD_SETSIZE)
            cmdLineErr("file descriptor exceeds limit (%d)\n", FD_SETSIZE);

        if (fd >= nfds)
            nfds = fd + 1;
        if (strchr(buf, 'r') != NULL) 
            FD_SET(fd, &readfds);
        if (strchr(buf, 'w') != NULL)
            FD_SET(fd, &writefds);
    }
    ready = select(nfds, &readfds, &writefds, NULL, pto);

    if (ready == -1) {
        errExit("select");
    }

    printf("ready = %d\n", ready);

    for (fd = 0; fd < nfds; fd++)
        printf("%d: %s%s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "", FD_ISSET(fd, &writefds) ? "w": "");

    if (pto != NULL)
        printf("timeout after select(): %ld.%03ld\n",
                (long) timeout.tv_sec, (long) timeout.tv_usec / 10000);
    
    exit(EXIT_SUCCESS);
}
