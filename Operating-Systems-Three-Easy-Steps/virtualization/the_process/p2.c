#include <stdio.h> //fread, fopen, fclose
#include <stdlib.h> //exit
#include <unistd.h> //fork
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  int fd = open("/tmp/2.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  assert(fd > -1);
  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
    char str[] = "child: hello world\n";
    int n = write(fd, str, sizeof(str));
    assert(n == sizeof(str));
  } else {
    printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
    char str[] = "parent: hello world\n";
    int n = write(fd, str, sizeof(str));
    assert(n == sizeof(str));
  }
  return 0;
}

