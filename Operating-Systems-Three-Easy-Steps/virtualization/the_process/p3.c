#include <stdio.h> //fread, fopen, fclose
#include <stdlib.h> //exit
#include <unistd.h> //fork
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
    //printf("execl:\n");
    //execl("/bin/ls", "ls", "-l", (char*) NULL);

    printf("execlp:\n");
    // search PATH environment for ls
    execlp("ls", "ls", "-l", (char*) NULL);
  } else {
    printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
  }
  return 0;
}

