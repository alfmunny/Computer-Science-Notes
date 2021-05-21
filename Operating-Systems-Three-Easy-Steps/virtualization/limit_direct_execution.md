# Mechanism: Limit Direct Execution

-   Basic Idea: ****time sharing****
    
    Run one process for a little while, then run another one.

-   Challenges:
    -   Performance: without adding excessive overhead
    -   Control: how can we run processes efficiently while retaining control over the CPU

## Problem 1: Restricted Operations

-   user mode
-   kernel mode
    -   perfom a system call
    -   execute a special trap instruction
    -   ****return-from-trap**** instruction back to user mode
    -   kernel stack

-   trap-table
    -   remember address of syscall handler
    -   when boots up, tell the hardware waht code to run when certain exceptinal events occur.

## Problem 2: Switching Between Processes

-   A cooperative Apporach: wait for system calls
    -   not ideal: inifinite loop and never makes a system call

-   A non-cooperative Approach: the OS takes control
    -   a timer interurpt
    -   at boot time, the OS inform the hardware which code to run when te timer interrupt occurs
    -   start the timer during the boot sequence
    -   save enough of the sate of the program

## Saving and Restoring Context

-   schedular
-   context switch
-   what happend if a interrupt during handling one interrupt
    -   disable interrupt
    -   locking

## Homework (Measurement)

How to measure time cost of system call?

-   call zero byte `read()` multiple times
-   use `gettimeofday()` to measure time cost
-   calculate the average time cost for each call

```C
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
```
