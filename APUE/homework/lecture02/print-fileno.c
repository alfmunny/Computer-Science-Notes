#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFSIZE 512

int 
main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "%s: print fileno for stdin, stdout, stderr and two files\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("STDOUT_FILENO: %d\n", STDOUT_FILENO);
    printf("STDERR_FILENO: %d\n", STDERR_FILENO);
    printf("stdin fileno: %d\n", fileno(stdin));
    printf("stdout fileno: %d\n", fileno(stdout));
    printf("stderr fileno: %d\n", fileno(stderr));

    int fd1;
    FILE *f1;

    if ((fd1 = open(argv[1], O_RDWR | O_TRUNC)) < 0) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("fileno for %s: %d\n", argv[1], fd1);

    if ((f1 = fopen(argv[2], "r+")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("fileno for %s: %d\n", argv[2], fileno(f1));

    // What happens when you open the same file multiple times with or without closing it again in between?
    int fd2;
    FILE *f2;

    if ((fd2 = open(argv[1], O_RDWR | O_APPEND)) < 0) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        printf("Succeed to open %s again with fileno: %d\n", argv[1], fd2);
    }

    if ((f2 = fopen(argv[1], "r+")) < 0) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        printf("Succeed to open %s again with fileno: %d\n", argv[2], fileno(f2));
    }


    // Try opening the same file twice, then writing different data to each file descriptor (via write(2)) - what happens?
    char buf1[] = "abcdefg to first fd";
    char buf2[] = "ABCDEFG to second fd";

    if (write(fd1, buf1, strlen(buf1)) != sizeof(buf1) - 1) {
        fprintf(stderr, "Unable to write to %s, fileno %d: %s\n", 
                argv[1], fd1, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (write(fd2, buf2, strlen(buf2)) != sizeof(buf2) - 1) {
        fprintf(stderr, "Unable to write to %s, fileno %d: %s\n", 
                argv[1], fd2, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Open an existing file that contains some data - perform alternate read(2) and write(2)s on that file descriptor. 
    // What does that tell you about the position in the file as you perform these operations? How would you go about replacing a specific word in a file?
    //

    printf("Try alternate read() and write() on the same file\n");
    int fd3;
    char buf3[BUFFSIZE];
    char buf4[] = "Write after read from file";
    int n;
    char file[] = "read_write.txt";

    if ((fd3 = open(file, O_RDWR)) < 0 ) {
        fprintf(stderr, "Unable to open %s\n", file);
        exit(EXIT_FAILURE);
    }

    if ((n = read(fd3, buf3, BUFFSIZE)) > 0) {
        printf("Read from %s, fileno %d\n", file, fd3);
        if (write(STDOUT_FILENO, buf3, n) != n) {
            fprintf(stderr, "Unable to write: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    if (n < 0) {
        fprintf(stderr, "Unable to read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (write(fd3, buf4, strlen(buf4)) != sizeof(buf4) - 1) {
        fprintf(stderr, "Unable to write to file %d: %s\n", fd3, strerror(errno));
        exit(EXIT_FAILURE);
    }


    (void)close(fd1);
    (void)close(fd2);
    return EXIT_SUCCESS;
}
