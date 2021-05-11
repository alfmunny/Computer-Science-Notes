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
