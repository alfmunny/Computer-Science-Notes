#include <stdio.h> //fread, fopen, fclose
#include <stdlib.h> //exit
#include <unistd.h> //fork
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
    //printf("execl:\n");
    //execl("/bin/ls", "ls", "-l", (char*) NULL);
    int w = wait(NULL);
    printf("child wait returns %d\n", w);

    printf("execlp:\n");
    // search PATH environment for ls
    execlp("ls", "ls", "-l", (char*) NULL);
  } else {
    printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
    int w = waitpid(-1, NULL, WNOHANG);
    printf("parent wait returns %d\n", w);
  }
  return 0;
}

