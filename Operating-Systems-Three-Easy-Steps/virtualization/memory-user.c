#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int n_mb = atoi(argv[1]);
  printf("%d\n megabyte...", n_mb);
  int n_int = n_mb / 4 * 1024 * 1024;
  int* arr = malloc(n_int * sizeof(int));
  while (1) {
    for (int i = 0; i < n_int; ++i) {
      arr[i] = i;
    }
  }
  return 0;
}
