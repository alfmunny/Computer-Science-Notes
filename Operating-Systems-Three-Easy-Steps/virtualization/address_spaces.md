# The Abstraction: Address Spaces


## Multiprogramming and Time Sharing

-   effective utilization of CPU
-   interactivity, many users might be concurrently using a machine
    -   run one process for short while
    -   giving it full access to all memory
    -   stop it, save all of its state to some kind of disk
    -   load some other process's state
    -   run it for a while

-   A big problem: too slow. Saving the entire contents of memory to disk is brutally non-performant
    
    What we would do is
    
    -   Leave processes ****in memory**** while switching between them
    -   ****protection**** is important, don't write some other process's memory.

## The Address Space

Address space is a abstraction:

-   **code:** static, put on the top of the address space.
-   **stack:** allocate local variables and pass parameters and return values to and from routines. starts at bottom grows upward.
-   **heap:** dynamically-allocated, user-managed memory. starts just after the code and grows downward

Stack and heap just have to grow in opposite directions.

## Goals

-   **transparency:** program shouldn't be aware of the fact that memory is virtualized.
-   **efficiency:** efficient in time and space; rely on hardware support, including hardware features such as TLBs.
-   **protection:** protection access or affect the memory contents of any other processes and the OS itself. The principle of isolation.

## Homework(Code)

`free` and `pmap`

```C
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
```
