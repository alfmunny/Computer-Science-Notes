#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long get_microseconds(struct timeval current_time) {
  long time;
  time = current_time.tv_sec * 1e6 + current_time.tv_usec;
  return time;
}

void print_time(long time) {
  printf("micro seconds: %ld\n", time);
}

int main() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  long start = get_microseconds(current_time);
  print_time(start);
  long n_calls = 10000000;

  for (int i = 0; i < n_calls; i++) read(0, NULL, 0);

  gettimeofday(&current_time, NULL);
  long end = get_microseconds(current_time);
  print_time(end);

  printf("average time cost of system call: %f micro seconds", (end - start) / ((float) n_calls));
  return 0;
}
