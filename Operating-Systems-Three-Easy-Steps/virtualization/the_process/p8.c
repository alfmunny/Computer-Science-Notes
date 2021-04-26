#include <stdio.h> //fread, fopen, fclose
#include <stdlib.h> //exit
#include <unistd.h> //fork
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int fd[2];
  char buf[100];

  if (pipe(fd) < 0) {
    exit(0);
  }

  pid_t rc1 = fork();

  if (rc1 < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc1 == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
    //printf("execl:\n");
    //execl("/bin/ls", "ls", "-l", (char*) NULL);
    strcpy(buf, "message from child 1.");
    close(fd[0]);
    write(fd[1], buf, sizeof(buf));
    exit(0);
  } else {
    printf("This is parent of %d (pid:%d)\n", rc1, (int) getpid());
    wait(NULL);
  }

  pid_t rc2 = fork();

  if (rc2 < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc2 == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
    //printf("execl:\n");
    //execl("/bin/ls", "ls", "-l", (char*) NULL);
    close(fd[1]);
    read(fd[0], buf, 100);
    printf("child 2 read %s", buf);
  } else {
    printf("This is parent of %d (pid:%d)\n", rc2, (int) getpid());
    wait(NULL);
  }
  return 0;
}

