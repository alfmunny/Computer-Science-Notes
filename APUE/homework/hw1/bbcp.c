/* Create by alfmunny on 07.Aug.2022 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFSIZE 1024

/* Notes
 * 1. Use a small bufsize and read and write the whole content in a while loop
 * 2. Use the st_mode of the source to set the target's permission
 * 3. openat() for open a file in another directory
 * 4. open() a file like "dir/" will cause EISDIR error
 */

int 
main(int argc, char** argv) {

    int fd_source;
    int fd_target;
    char buf[BUFSIZE];

    DIR *dp;
    struct dirent *dirp;

    if (argc != 3) {
        fprintf(stderr, "Usage: copy from to\n");
        exit(EXIT_FAILURE);
    }

    if ((fd_source = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Get the permission of the source file, in order to set to the new file
    struct stat fs;
    int r;
    if ((r = lstat(argv[1], &fs)) < 0) {
        fprintf(stderr, "Unable to stat %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    if ((dp = opendir(argv[2])) == NULL) {
        if ((fd_target = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, fs.st_mode)) < 0 ) {
            if (errno == EISDIR) {
                fprintf(stderr, "Unable to copy to %s: Directory not found\n", argv[2]); 
            }
            else {
                fprintf(stderr, "Unable to copy to %s: %s\n", argv[2], strerror(errno)); 
            }
            exit(EXIT_FAILURE); }
    } 
    else {
        // openat() can be used here as well, without change the dir with chdir()
        if ((fd_target = openat(dirfd(dp), argv[1], O_WRONLY | O_CREAT | O_APPEND, fs.st_mode)) < 0 ) {
            fprintf(stderr, "Unable to copy to directory: %s\n", 
                    strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    int n;

    while(1) {
        if ((n = read(fd_source, buf, BUFSIZE)) > 0)  {
            if((write(fd_target, buf, n)) != n) {
                fprintf(stderr, "Unable to write: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else if (n < 0){
            fprintf(stderr, "Unable to read: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else 
        {
            break;
        }
    }

    (void)close(fd_source);
    (void)close(fd_target);

    return EXIT_SUCCESS;
}
