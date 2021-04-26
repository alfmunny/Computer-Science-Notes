#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  int a = 0;
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0){
    a = 1;
    printf("This is child (pid:%d)\n", (int) getpid());
    printf("a in child: %d\n", a);
  } else {
    a = 2;
    printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
    printf("a in parent: %d\n", a);
  }
  return 0;
}

