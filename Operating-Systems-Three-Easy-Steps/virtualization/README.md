# Vitualization


# Table of Contents

-   [Vitualization](#org972bc8b)
    -   [The Abstraction: The Process](#org299c2f6)
        -   [A Process](#org1400b60)
        -   [Process API](#org0f77ccf)
        -   [Process Creation](#orga38f0f1)
        -   [Process States](#org84c7674)
        -   [Data Sctructures](#org56061a9)
        -   [Homework](#org5531342)
    -   [Interlude: Process API](#orge3fece7)
        -   [fork()](#orgecb0174)
        -   [wait()](#orgf1b27a7)
        -   [exec()](#org1e92772)
        -   [Why?](#org1fb6cb0)
        -   [Process Control And Users](#orgbabd768)
        -   [Tools](#org7dd1705)
        -   [Homework(Simulation)](#org6bc9e4c)
        -   [Homework(code)](#org74386cb)
    -   [Mechanism: Limit Direct Execution](#orgf3d1b98)
        -   [Problem 1: Restricted Operations](#org3d7d896)
        -   [Problem 2: Switching Between Processes](#org30973b1)
        -   [Saving and Restoring Context](#orgdf74f82)
        -   [Homework (Measurement)](#org21636af)
    -   [Scheduling: Introduction](#orgda5a67f)
        -   [Workload Assumption](#org2c17b26)
        -   [First In, First Out(FIFO)](#org0396032)
        -   [Shortest Job First (SJF)](#org5271d83)
        -   [Shortest Time-to-Completion First (STCF)](#orgceb3055)
        -   [A new Metric: Response Time](#org0d6a2ca)
        -   [Round Robin](#org8b89fe2)
        -   [Incorporating I/O](#org7d6e2a4)
        -   [No More Oracle](#org9bae6d1)
        -   [Homework(Simulation)](#org3046d63)
    -   [Scheduling: Multi-Level Feedback Queue](#org74a84b1)
        -   [Basic Rules](#org89bfe02)
        -   [Attempt #1: How to Change Priority](#orga6d31c4)
        -   [Attempt #2: The Priority Boost](#orgaec8c0f)
        -   [Attempt #3: Better Accounting](#org7756f17)
        -   [Tuning MLFQ And Other Issues](#org5f9cf39)
        -   [Homework (Simulation)](#orgd867e08)
    -   [The Abstraction: Address Spaces](#orga288f02)
        -   [Multiprogramming and Time Sharing](#org2d2263a)
        -   [The Address Space](#org8606fbf)
        -   [Goals](#org1b3bb7d)
        -   [Homework(Code)](#orgeff2a20)

## The Abstraction: The Process


### A Process

-   absctration of a running program
-   can be described by state:
    -   contents of memory in its address space
    -   contents of CPU registers
    -   information about I/O

### Process API

-   Create
-   Destory
-   Wait
-   Miscellaneous Control (kill, wait, suspend, resume)
-   Status

### Process Creation

1.  Loading process:
    -   eagerly
    -   lazily: paging and swapping -> virtualization of memory
2.  Memory allocation:
    -   stack: local variables, function parameters, and return addresses
    -   heap: linked lists, hash tables, trees, and ohter interesting data structures
        -   small at first,, via malloc() more memory can be allocated to satisfy such calls
3.  Start the program at the entry point, main()

### Process States

-   Running
-   Ready
-   Blocked
    
    Ready -> scheduled -> Running
    
    Running -> descheduled -> Ready
    
    Running -> IO initiated -> Blocked -> IO done -> Ready
    
    The transition decision is made by the **scheduler**

### Data Sctructures

-   **process list:** track which process is currenly running, ready or blocked. (and also zombie state and -> examine the return, wait for child or kill)
-   **register context:** hold for stopped process, the contents of its registers.
-   **context switch:** by restorig these resigters, the OS can resume running the process.

### Homework

1.  Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
    
    ```shell
    ./process-run.py -l 5:100,5:100 -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2        RUN:cpu         READY             1          
          3        RUN:cpu         READY             1          
          4        RUN:cpu         READY             1          
          5        RUN:cpu         READY             1          
          6           DONE       RUN:cpu             1          
          7           DONE       RUN:cpu             1          
          8           DONE       RUN:cpu             1          
          9           DONE       RUN:cpu             1          
         10           DONE       RUN:cpu             1          
        
        Stats: Total Time 10
        Stats: CPU Busy 10 (100.00%)
        Stats: IO Busy  0 (0.00%)

2.  Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
    
    ```shell
    ./process-run.py -l 4:100,1:0 -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2        RUN:cpu         READY             1          
          3        RUN:cpu         READY             1          
          4        RUN:cpu         READY             1          
          5           DONE        RUN:io             1          
          6           DONE       WAITING                           1
          7           DONE       WAITING                           1
          8           DONE       WAITING                           1
          9           DONE       WAITING                           1
         10           DONE       WAITING                           1
         11*          DONE   RUN:io_done             1          
        
        Stats: Total Time 11
        Stats: CPU Busy 6 (54.55%)
        Stats: IO Busy  5 (45.45%)

3.  Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)
    
    ```shell
    ./process-run.py -l 1:0,4:100 -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        WAITING       RUN:cpu             1             1
          3        WAITING       RUN:cpu             1             1
          4        WAITING       RUN:cpu             1             1
          5        WAITING       RUN:cpu             1             1
          6        WAITING          DONE                           1
          7*   RUN:io_done          DONE             1          
        
        Stats: Total Time 7
        Stats: CPU Busy 6 (85.71%)
        Stats: IO Busy  5 (71.43%)

4.  We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (`-l 1:0,4:100 -c -S SWITCH_ON _END`), one doing I/O and the other doing CPU work?
    
    ```shell
    ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        WAITING         READY                           1
          3        WAITING         READY                           1
          4        WAITING         READY                           1
          5        WAITING         READY                           1
          6        WAITING         READY                           1
          7*   RUN:io_done         READY             1          
          8           DONE       RUN:cpu             1          
          9           DONE       RUN:cpu             1          
         10           DONE       RUN:cpu             1          
         11           DONE       RUN:cpu             1

5.  Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.
    
    ```shell
    ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1         RUN:io         READY             1          
          2        WAITING       RUN:cpu             1             1
          3        WAITING       RUN:cpu             1             1
          4        WAITING       RUN:cpu             1             1
          5        WAITING       RUN:cpu             1             1
          6        WAITING          DONE                           1
          7*   RUN:io_done          DONE             1          
        
        Stats: Total Time 7
        Stats: CPU Busy 6 (85.71%)
        Stats: IO Busy  5 (71.43%)

6.  One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized?
    
    ```shell
    ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
    ```
    
        Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
          1         RUN:io         READY         READY         READY             1          
          2        WAITING       RUN:cpu         READY         READY             1             1
          3        WAITING       RUN:cpu         READY         READY             1             1
          4        WAITING       RUN:cpu         READY         READY             1             1
          5        WAITING       RUN:cpu         READY         READY             1             1
          6        WAITING       RUN:cpu         READY         READY             1             1
          7*         READY          DONE       RUN:cpu         READY             1          
          8          READY          DONE       RUN:cpu         READY             1          
          9          READY          DONE       RUN:cpu         READY             1          
         10          READY          DONE       RUN:cpu         READY             1          
         11          READY          DONE       RUN:cpu         READY             1          
         12          READY          DONE          DONE       RUN:cpu             1          
         13          READY          DONE          DONE       RUN:cpu             1          
         14          READY          DONE          DONE       RUN:cpu             1          
         15          READY          DONE          DONE       RUN:cpu             1          
         16          READY          DONE          DONE       RUN:cpu             1          
         17    RUN:io_done          DONE          DONE          DONE             1          
         18         RUN:io          DONE          DONE          DONE             1          
         19        WAITING          DONE          DONE          DONE                           1
         20        WAITING          DONE          DONE          DONE                           1
         21        WAITING          DONE          DONE          DONE                           1
         22        WAITING          DONE          DONE          DONE                           1
         23        WAITING          DONE          DONE          DONE                           1
         24*   RUN:io_done          DONE          DONE          DONE             1          
         25         RUN:io          DONE          DONE          DONE             1          
         26        WAITING          DONE          DONE          DONE                           1
         27        WAITING          DONE          DONE          DONE                           1
         28        WAITING          DONE          DONE          DONE                           1
         29        WAITING          DONE          DONE          DONE                           1
         30        WAITING          DONE          DONE          DONE                           1
         31*   RUN:io_done          DONE          DONE          DONE             1          
        
        Stats: Total Time 31
        Stats: CPU Busy 21 (67.74%)
        Stats: IO Busy  15 (48.39%)

7.  Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?
    
    ```shell
    ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
    ```
    
        Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
          1         RUN:io         READY         READY         READY             1          
          2        WAITING       RUN:cpu         READY         READY             1             1
          3        WAITING       RUN:cpu         READY         READY             1             1
          4        WAITING       RUN:cpu         READY         READY             1             1
          5        WAITING       RUN:cpu         READY         READY             1             1
          6        WAITING       RUN:cpu         READY         READY             1             1
          7*   RUN:io_done          DONE         READY         READY             1          
          8         RUN:io          DONE         READY         READY             1          
          9        WAITING          DONE       RUN:cpu         READY             1             1
         10        WAITING          DONE       RUN:cpu         READY             1             1
         11        WAITING          DONE       RUN:cpu         READY             1             1
         12        WAITING          DONE       RUN:cpu         READY             1             1
         13        WAITING          DONE       RUN:cpu         READY             1             1
         14*   RUN:io_done          DONE          DONE         READY             1          
         15         RUN:io          DONE          DONE         READY             1          
         16        WAITING          DONE          DONE       RUN:cpu             1             1
         17        WAITING          DONE          DONE       RUN:cpu             1             1
         18        WAITING          DONE          DONE       RUN:cpu             1             1
         19        WAITING          DONE          DONE       RUN:cpu             1             1
         20        WAITING          DONE          DONE       RUN:cpu             1             1
         21*   RUN:io_done          DONE          DONE          DONE             1          
        
        Stats: Total Time 21
        Stats: CPU Busy 21 (100.00%)
        Stats: IO Busy  15 (71.43%)

8.  Now run with some randomly generated processes: -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,3:50. See if you can predict how the trace will turn out. What happens when you use the flag -I IO RUN IMMEDIATE vs. -I IO RUN LATER? What happens when you use -S SWITCH ON IO vs. -S SWITCH ON END?
    
    Seed 1:
    
    ```shell
    ./process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2         RUN:io         READY             1          
          3        WAITING       RUN:cpu             1             1
          4        WAITING       RUN:cpu             1             1
          5        WAITING       RUN:cpu             1             1
          6        WAITING          DONE                           1
          7        WAITING          DONE                           1
          8*   RUN:io_done          DONE             1          
          9         RUN:io          DONE             1          
         10        WAITING          DONE                           1
         11        WAITING          DONE                           1
         12        WAITING          DONE                           1
         13        WAITING          DONE                           1
         14        WAITING          DONE                           1
         15*   RUN:io_done          DONE             1          
        
        Stats: Total Time 15
        Stats: CPU Busy 8 (53.33%)
        Stats: IO Busy  10 (66.67%)
    
    ```shell
    ./process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE -c -p
    ```
    
        Time        PID: 0        PID: 1           CPU           IOs
          1        RUN:cpu         READY             1          
          2         RUN:io         READY             1          
          3        WAITING         READY                           1
          4        WAITING         READY                           1
          5        WAITING         READY                           1
          6        WAITING         READY                           1
          7        WAITING         READY                           1
          8*   RUN:io_done         READY             1          
          9         RUN:io         READY             1          
         10        WAITING         READY                           1
         11        WAITING         READY                           1
         12        WAITING         READY                           1
         13        WAITING         READY                           1
         14        WAITING         READY                           1
         15*   RUN:io_done         READY             1          
         16           DONE       RUN:cpu             1          
         17           DONE       RUN:cpu             1          
         18           DONE       RUN:cpu             1          
        
        Stats: Total Time 18
        Stats: CPU Busy 8 (44.44%)
        Stats: IO Busy  10 (55.56%)

```shell
./process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1        RUN:cpu         READY             1          
      2         RUN:io         READY             1          
      3        WAITING       RUN:cpu             1             1
      4        WAITING       RUN:cpu             1             1
      5        WAITING       RUN:cpu             1             1
      6        WAITING          DONE                           1
      7        WAITING          DONE                           1
      8*   RUN:io_done          DONE             1          
      9         RUN:io          DONE             1          
     10        WAITING          DONE                           1
     11        WAITING          DONE                           1
     12        WAITING          DONE                           1
     13        WAITING          DONE                           1
     14        WAITING          DONE                           1
     15*   RUN:io_done          DONE             1          
    
    Stats: Total Time 15
    Stats: CPU Busy 8 (53.33%)
    Stats: IO Busy  10 (66.67%)

```shell
./process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_LATER -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1        RUN:cpu         READY             1          
      2         RUN:io         READY             1          
      3        WAITING         READY                           1
      4        WAITING         READY                           1
      5        WAITING         READY                           1
      6        WAITING         READY                           1
      7        WAITING         READY                           1
      8*   RUN:io_done         READY             1          
      9         RUN:io         READY             1          
     10        WAITING         READY                           1
     11        WAITING         READY                           1
     12        WAITING         READY                           1
     13        WAITING         READY                           1
     14        WAITING         READY                           1
     15*   RUN:io_done         READY             1          
     16           DONE       RUN:cpu             1          
     17           DONE       RUN:cpu             1          
     18           DONE       RUN:cpu             1          
    
    Stats: Total Time 18
    Stats: CPU Busy 8 (44.44%)
    Stats: IO Busy  10 (55.56%)

Seed 2:

```shell
./process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1         RUN:io         READY             1          
      2        WAITING       RUN:cpu             1             1
      3        WAITING        RUN:io             1             1
      4        WAITING       WAITING                           2
      5        WAITING       WAITING                           2
      6        WAITING       WAITING                           2
      7*   RUN:io_done       WAITING             1             1
      8         RUN:io       WAITING             1             1
      9*       WAITING   RUN:io_done             1             1
     10        WAITING        RUN:io             1             1
     11        WAITING       WAITING                           2
     12        WAITING       WAITING                           2
     13        WAITING       WAITING                           2
     14*   RUN:io_done       WAITING             1             1
     15        RUN:cpu       WAITING             1             1
     16*          DONE   RUN:io_done             1          
    
    Stats: Total Time 16
    Stats: CPU Busy 10 (62.50%)
    Stats: IO Busy  14 (87.50%)

```shell
./process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1         RUN:io         READY             1          
      2        WAITING       RUN:cpu             1             1
      3        WAITING        RUN:io             1             1
      4        WAITING       WAITING                           2
      5        WAITING       WAITING                           2
      6        WAITING       WAITING                           2
      7*   RUN:io_done       WAITING             1             1
      8         RUN:io       WAITING             1             1
      9*       WAITING   RUN:io_done             1             1
     10        WAITING        RUN:io             1             1
     11        WAITING       WAITING                           2
     12        WAITING       WAITING                           2
     13        WAITING       WAITING                           2
     14*   RUN:io_done       WAITING             1             1
     15        RUN:cpu       WAITING             1             1
     16*          DONE   RUN:io_done             1          
    
    Stats: Total Time 16
    Stats: CPU Busy 10 (62.50%)
    Stats: IO Busy  14 (87.50%)

Seed 3:

```shell
./process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1        RUN:cpu         READY             1          
      2         RUN:io         READY             1          
      3        WAITING        RUN:io             1             1
      4        WAITING       WAITING                           2
      5        WAITING       WAITING                           2
      6        WAITING       WAITING                           2
      7        WAITING       WAITING                           2
      8*   RUN:io_done       WAITING             1             1
      9*         READY   RUN:io_done             1          
     10          READY        RUN:io             1          
     11        RUN:cpu       WAITING             1             1
     12           DONE       WAITING                           1
     13           DONE       WAITING                           1
     14           DONE       WAITING                           1
     15           DONE       WAITING                           1
     16*          DONE   RUN:io_done             1          
     17           DONE       RUN:cpu             1          
    
    Stats: Total Time 17
    Stats: CPU Busy 9 (52.94%)
    Stats: IO Busy  11 (64.71%)

```shell
./process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
```

    Time        PID: 0        PID: 1           CPU           IOs
      1        RUN:cpu         READY             1          
      2         RUN:io         READY             1          
      3        WAITING        RUN:io             1             1
      4        WAITING       WAITING                           2
      5        WAITING       WAITING                           2
      6        WAITING       WAITING                           2
      7        WAITING       WAITING                           2
      8*   RUN:io_done       WAITING             1             1
      9*       RUN:cpu         READY             1          
     10           DONE   RUN:io_done             1          
     11           DONE        RUN:io             1          
     12           DONE       WAITING                           1
     13           DONE       WAITING                           1
     14           DONE       WAITING                           1
     15           DONE       WAITING                           1
     16           DONE       WAITING                           1
     17*          DONE   RUN:io_done             1          
     18           DONE       RUN:cpu             1          
    
    Stats: Total Time 18
    Stats: CPU Busy 9 (50.00%)
    Stats: IO Busy  11 (61.11%)

## Interlude: Process API

Unix way to create a new process with a pair of system calls: `fork()` and `exec()`. `wait()` can be used to wait for a created process to complete.

### fork()

-   Create a new process
-   Create an exact copy of the calling process
    -   Both are about to return from the fork()
    -   They have different return values of fork()
        -   The parent receives the the PID of the child
        -   The child receives zero
    -   The child has its own address space, own registers, own PC, and so forth.
-   Output is not deterministic

### wait()

-   The parent process calls wait() to delay its execution.
-   When the child is done, wait() returns to the parent.
-   The output is deterministic.

### exec()

-   Run a program that is different from the calling program.
-   What it does:
    -   Loads code from that executable and overwrites its current code segment
    -   The heap and stack and other parts of the memory space are reinitialized.
    -   OS runs that program.

### Why?

-   Separation of `fork()` and `exec()`
    -   Lets the shell run code after `fork()` and before `exec()`
    -   Like redirection in shell
    -   pipe

### Process Control And Users

-   `kill()`
-   `SIGINT`
-   `SIGTSTP`
-   `signal()` to catch various signals
-   User generally can only control their own processes.

### Tools

`top` and `ps`

### Homework(Simulation)

1.  Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it
    
    ```shell
    ./fork.py -s 10 -c
    ```
    
        
        ARG seed 10
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree False
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True
        
                                   Process Tree:
                                       a
        
        Action: a forks b
                                       a
                                       └── b
        Action: a forks c
                                       a
                                       ├── b
                                       └── c
        Action: c EXITS
                                       a
                                       └── b
        Action: a forks d
                                       a
                                       ├── b
                                       └── d
        Action: a forks e
                                       a
                                       ├── b
                                       ├── d
                                       └── e

2.  One control the simluator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and very the fork percentage from 0.1 to 0.9. What you thik the resulting final process trees will look like as the percetage changes? check your answer with -c.

3.  Now, switch the output by using the -t flag (e.g., run ./fork.py -t). Given a set of process trees, can you tell which actions were taken?
    
    ```shell
    ./fork.py -s 5 -t -a 10
    ```
    
        
        ARG seed 5
        ARG fork_percentage 0.7
        ARG actions 10
        ARG action_list 
        ARG show_tree True
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False
        
                                   Process Tree:
                                       a
        
        Action?
                                       a
                                       └── b
        Action?
                                       a
        Action?
                                       a
                                       └── c
        Action?
                                       a
        Action?
                                       a
                                       └── d
        Action?
                                       a
                                       └── d
                                           └── e
        Action?
                                       a
                                       ├── d
                                       │   └── e
                                       └── f
        Action?
                                       a
                                       ├── d
                                       │   └── e
                                       └── f
                                           └── g
        Action?
                                       a
                                       ├── d
                                       │   └── e
                                       ├── f
                                       │   └── g
                                       └── h
        Action?
                                       a
                                       ├── d
                                       │   └── e
                                       ├── f
                                       │   └── g
                                       └── h
                                           └── i
    
    a forks b, b exits, a forks c, c exits, a forks d, d forks e, a forks f, f forks g, a forks h, h forks i
4.  One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: ./fork.py -A a+b,b+c,c+d,c+e,c-. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned pro- cesses on your own to add more context.
    
    ```shell
    ./fork.py -A a+b,b+c,c+d,c+e,c- -c
    ```
    
        
        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list a+b,b+c,c+d,c+e,c-
        ARG show_tree False
        ARG just_final False
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True
        
                                   Process Tree:
                                       a
        
        Action: a forks b
                                       a
                                       └── b
        Action: b forks c
                                       a
                                       └── b
                                           └── c
        Action: c forks d
                                       a
                                       └── b
                                           └── c
                                               └── d
        Action: c forks e
                                       a
                                       └── b
                                           └── c
                                               ├── d
                                               └── e
        Action: c EXITS
                                       a
                                       ├── b
                                       ├── d
                                       └── e

5.  One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.
    
    ```shell
    ./fork.py -a 100 -c -F
    ```
    
        
        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 100
        ARG action_list 
        ARG show_tree False
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True
        
                                   Process Tree:
                                       a
        
        Action: a forks b
        Action: a forks c
        Action: b EXITS
        Action: c forks d
        Action: d forks e
        Action: c forks f
        Action: c forks g
        Action: d forks h
        Action: g forks i
        Action: d forks j
        Action: h forks k
        Action: d forks l
        Action: g forks m
        Action: j EXITS
        Action: h EXITS
        Action: k EXITS
        Action: l forks n
        Action: l EXITS
        Action: e forks o
        Action: n forks p
        Action: n forks q
        Action: q forks r
        Action: f EXITS
        Action: d forks s
        Action: a forks t
        Action: m EXITS
        Action: g EXITS
        Action: o forks u
        Action: s forks v
        Action: a forks w
        Action: u forks x
        Action: w forks y
        Action: o EXITS
        Action: x forks z
        Action: x forks A
        Action: e forks B
        Action: a forks C
        Action: c forks D
        Action: v forks E
        Action: x EXITS
        Action: B forks F
        Action: z EXITS
        Action: w forks G
        Action: B EXITS
        Action: p forks H
        Action: D forks I
        Action: s forks J
        Action: u forks K
        Action: w forks L
        Action: a forks M
        Action: s EXITS
        Action: E EXITS
        Action: D forks N
        Action: H EXITS
        Action: L forks O
        Action: e forks P
        Action: A EXITS
        Action: u EXITS
        Action: r forks Q
        Action: w forks R
        Action: p forks S
        Action: I forks T
        Action: v EXITS
        Action: L forks U
        Action: T EXITS
        Action: J forks V
        Action: R forks W
        Action: U forks X
        Action: S forks Y
        Action: Q forks Z
        Action: M EXITS
        Action: n forks aa
        Action: e EXITS
        Action: p forks ab
        Action: c EXITS
        Action: q forks ac
        Action: I forks ad
        Action: Q forks ae
        Action: J EXITS
        Action: R forks af
        Action: d EXITS
        Action: a forks ag
        Action: U forks ah
        Action: I EXITS
        Action: D forks ai
        Action: F forks aj
        Action: t forks ak
        Action: y forks al
        Action: ai forks am
        Action: U forks an
        Action: aa forks ao
        Action: am forks ap
        Action: Q forks aq
        Action: aq forks ar
        Action: ag EXITS
        Action: ac forks as
        Action: aq forks at
        Action: ac forks au
        Action: O EXITS
        Action: ao EXITS
        
                                Final Process Tree:
                                       a
                                       ├── n
                                       │   ├── p
                                       │   │   ├── S
                                       │   │   │   └── Y
                                       │   │   └── ab
                                       │   ├── q
                                       │   │   ├── r
                                       │   │   │   └── Q
                                       │   │   │       ├── Z
                                       │   │   │       ├── ae
                                       │   │   │       └── aq
                                       │   │   │           ├── ar
                                       │   │   │           └── at
                                       │   │   └── ac
                                       │   │       ├── as
                                       │   │       └── au
                                       │   └── aa
                                       ├── t
                                       │   └── ak
                                       ├── i
                                       ├── w
                                       │   ├── y
                                       │   │   └── al
                                       │   ├── G
                                       │   ├── L
                                       │   │   └── U
                                       │   │       ├── X
                                       │   │       ├── ah
                                       │   │       └── an
                                       │   └── R
                                       │       ├── W
                                       │       └── af
                                       ├── C
                                       ├── F
                                       │   └── aj
                                       ├── K
                                       ├── P
                                       ├── D
                                       │   └── ai
                                       │       └── am
                                       │           └── ap
                                       ├── N
                                       ├── V
                                       └── ad

6.  Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By look- ing at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some dif- ferent random seeds to delve into this question.
    
    ```shell
    ./fork.py -t -F -s 20
    ```
    
        
        ARG seed 20
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list 
        ARG show_tree True
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve False
        
                                   Process Tree:
                                       a
        
        Action?
        Action?
        Action?
        Action?
        Action?
        
                                Final Process Tree:
                                       a
                                       ├── c
                                       │   └── d
                                       └── e
    
    Solution 1: a+b,b+e,a+c,c+d,b-
    
    ```shell
    ./fork.py -A a+b,b+e,a+c,c+d,b- -c -F
    ```
    
        
        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list a+b,b+e,a+c,c+d,b-
        ARG show_tree False
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True
        
                                   Process Tree:
                                       a
        
        Action: a forks b
        Action: b forks e
        Action: a forks c
        Action: c forks d
        Action: b EXITS
        
                                Final Process Tree:
                                       a
                                       ├── c
                                       │   └── d
                                       └── e
    
    Solution 2: a+b,b-,a+c,c+d,a+e
    
    ```shell
    ./fork.py -A a+b,b-,a+c,c+d,a+e -c -F
    ```
    
        
        ARG seed -1
        ARG fork_percentage 0.7
        ARG actions 5
        ARG action_list a+b,b-,a+c,c+d,a+e
        ARG show_tree False
        ARG just_final True
        ARG leaf_only False
        ARG local_reparent False
        ARG print_style fancy
        ARG solve True
        
                                   Process Tree:
                                       a
        
        Action: a forks b
        Action: b EXITS
        Action: a forks c
        Action: c forks d
        Action: a forks e
        
                                Final Process Tree:
                                       a
                                       ├── c
                                       │   └── d
                                       └── e

### Homework(code)

1.  Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to some- thing (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
    
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    int main(int argc, char *argv[]) {
      int x = 100;
      int rc = fork();
      if (rc < 0) {
        printf("fork failed\n");
        exit(1);
      } else if (rc == 0) {
        x = 101;
        printf("This is child %d , x = %d \n", (int) getpid(), x);
      } else {
        x = 102;
        printf("This is parent of %d (pid:%d), x = %d \n", rc, (int) getpid(), x);
      }
      return 0;
    }
    ```
    
        This is parent of 534497 (pid:534496), x = 102 
        This is child 534497 , x = 101 
    
    Both process can change the variable.

2.  Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
    
    ```c
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
        int rc = write(fd, "child: hello world\n", 20);
        assert(rc == 20);
      } else {
        printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
        int rc = write(fd, "parent: hello world\n", 21);
        assert(rc == 21);
      }
      return 0;
    }
    ```
    
        This is parent of 539125 (pid:539124)
        This is child (pid:539125)
    
    ```shell
    cat /tmp/2.txt
    ```
    
    Both file can access the file descriptor

3.  Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

4.  Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
    
    ```c
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
        execl("/bin/ls", "ls", "-l", (char*) NULL);
      } else {
        printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
      }
      return 0;
    }
    ```
    
        This is parent of 542888 (pid:542887)
        total 52
        -rwxrwxr-x 1 alfmunny alfmunny 12111 Apr 22 23:43 fork.py
        -rwxrwxr-x 1 alfmunny alfmunny 19859 Apr 22 23:43 generator.py
        -rw-rw-r-- 1 alfmunny alfmunny  4954 Apr 22 23:43 README-fork.md
        -rw-rw-r-- 1 alfmunny alfmunny  4996 Apr 22 23:43 README-generator.md
        -rw-rw-r-- 1 alfmunny alfmunny   448 Apr 22 23:43 README.md
    
    See all examples for different variants: [exec manual](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html).

5.  Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?
    
    ```c
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
        int w = wait(NULL);
        printf("child wait returns %d\n", w);
    
        // search PATH environment for ls
        printf("execlp:\n");
        execlp("ls", "ls", "-l", (char*) NULL);
      } else {
        printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
        int w = wait(NULL);
        printf("parent wait returns %d", w);
      }
      return 0;
    }
    ```
    
        total 52
        -rwxrwxr-x 1 alfmunny alfmunny 12111 Apr 22 23:43 fork.py
        -rwxrwxr-x 1 alfmunny alfmunny 19859 Apr 22 23:43 generator.py
        -rw-rw-r-- 1 alfmunny alfmunny  4954 Apr 22 23:43 README-fork.md
        -rw-rw-r-- 1 alfmunny alfmunny  4996 Apr 22 23:43 README-generator.md
        -rw-rw-r-- 1 alfmunny alfmunny   448 Apr 22 23:43 README.md
        This is parent of 545955 (pid:545954)
        parent wait returns 545955
    
    wait() in parent returns the pid of child. wait() in child returns -1.

6.  Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
    
    ```c
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
        int w = wait(NULL);
        printf("child wait returns %d\n", w);
    
        // search PATH environment for ls
        printf("execlp:\n");
        execlp("ls", "ls", "-l", (char*) NULL);
      } else {
        printf("This is parent of %d (pid:%d)\n", rc, (int) getpid());
        int w = waitpid(-1, NULL, WNOHANG);
        printf("parent wait returns %d", w);
      }
      return 0;
    }
    ```
    
    waitpid is able to not to block the parent.

7.  Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
    
    print nothing

8.  Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
    
    ```c
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
        close(fd[1]);
        read(fd[0], buf, 100);
        printf("child 2 read %s", buf);
      } else {
        printf("This is parent of %d (pid:%d)\n", rc2, (int) getpid());
        wait(NULL);
      }
      return 0;
    }
    ```
    
        This is child (pid:548896)
        This is parent of 548896 (pid:548895)
        This is child (pid:548897)
        child 2 read message from child 1.This is parent of 548896 (pid:548895)
        This is parent of 548897 (pid:548895)

## Mechanism: Limit Direct Execution

-   Basic Idea: **time sharing**
    
    Run one process for a little while, then run another one.

-   Challenges:
    -   Performance: without adding excessive overhead
    -   Control: how can we run processes efficiently while retaining control over the CPU

### Problem 1: Restricted Operations

-   user mode
-   kernel mode
    -   perfom a system call
    -   execute a special trap instruction
    -   **return-from-trap** instruction back to user mode
    -   kernel stack

-   trap-table
    -   remember address of syscall handler
    -   when boots up, tell the hardware waht code to run when certain exceptinal events occur.

### Problem 2: Switching Between Processes

-   A cooperative Apporach: wait for system calls
    -   not ideal: inifinite loop and never makes a system call

-   A non-cooperative Approach: the OS takes control
    -   a timer interurpt
    -   at boot time, the OS inform the hardware which code to run when te timer interrupt occurs
    -   start the timer during the boot sequence
    -   save enough of the sate of the program

### Saving and Restoring Context

-   schedular
-   context switch
-   what happend if a interrupt during handling one interrupt
    -   disable interrupt
    -   locking

### Homework (Measurement)

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

Context switching measurement using lmbench

<p class="verse">
Context switching - times in microseconds - smaller is better<br />
--------------------------------------------------------------------&#x2013;&#x2014;<br />
Host                 OS  2p/0K 2p/16K 2p/64K 8p/16K 8p/64K 16p/16K 16p/64K<br />
&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;&#xa0;ctxsw  ctxsw  ctxsw ctxsw  ctxsw   ctxsw   ctxsw<br />
----&#x2013;&#x2014; --------&#x2013;&#x2014; -&#x2013;&#x2014; -&#x2013;&#x2014; -&#x2013;&#x2014; -&#x2013;&#x2014; -&#x2013;&#x2014; --&#x2013;&#x2014; --&#x2013;&#x2014;<br />
</p>

## Scheduling: Introduction

-   **scheduling metrics:** turnaround time.
    -   the turnaround time of a job is defined as the time at which the job completes minus the time at which the job arrived in the system.

### Workload Assumption

1.  Each job runs for the same amount of time.
2.  All jobs arrive at the same time.
3.  Once started, each job runs to completion.
4.  All jobs only use the CPU (i.e., they perform no I/O)
5.  The run-time of each job is known.

### First In, First Out(FIFO)

Simple and easy to implement.

### Shortest Job First (SJF)

Relax assumption 1:

What if no longer assume that each job runs for the same amount of time.

Solution: SJF

### Shortest Time-to-Completion First (STCF)

Relax assumption 2:

jobs can arrive at any time instead of all at once.

To address this concern, we need to relax assumption 3:

jobs does not run to completion.

Solution: STCF

Any time a new job enters the system, the STCF scheduler determines which of the remaining jobs has the least time left, and schedules that one.

### A new Metric: Response Time

-   **Response Time:** the time from when the job arrives in a system to the first time it is scheduled

How can we build a scheduler that is sensitive to response time?

### Round Robin

-   **Round-Robin:** instead of running jobs to completion, RR runs a job for a time slice (sometimes called a scheduling quantum) and then switches to the next job in the run queue. It repeatedly does so until the jobs are finished. For this reason, RR is sometimes called time-slicing.

The shorter the time-slice is, the better the performance of RR under the response-time metric.

-   Problem (trade-off)
    -   cost of context switching
    -   turnaround time is awful

### Incorporating I/O

Relax assumption 4

While interactive jobs are performing I/O, other CPU-intensive jobs run, thua better utilizing the processor.

### No More Oracle

Relax assumption 5

Building a scheduler that uses the recent past to predict the future.

### Homework(Simulation)

1.  Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
    
    SJF:
    
    ```shell
    ./scheduler.py -p SJF -l 200,200,200 -c 
    ```
    
        ARG policy SJF
        ARG jlist 200,200,200
        
        Here is the job list, with the run time of each job: 
          Job 0 ( length = 200.0 )
          Job 1 ( length = 200.0 )
          Job 2 ( length = 200.0 )
        
        
        ** Solutions **
        
        Execution trace:
          [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
          [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
          [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )
        
        Final statistics:
          Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
          Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
          Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00
        
          Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
    
    FIFO:
    
    ```shell
    ./scheduler.py -p FIFO -l 200,200,200 -c 
    ```
    
        ARG policy FIFO
        ARG jlist 200,200,200
        
        Here is the job list, with the run time of each job: 
          Job 0 ( length = 200.0 )
          Job 1 ( length = 200.0 )
          Job 2 ( length = 200.0 )
        
        
        ** Solutions **
        
        Execution trace:
          [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
          [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
          [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )
        
        Final statistics:
          Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
          Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
          Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00
        
          Average -- Response: 200.00  Turnaround 400.00  Wait 200.00

2.  Now do the same but with jobs of different lengths: 100, 200, and 300.
    
    ```shell
    ./scheduler.py -p SJF -l 200,100,300 -c 
    ```
    
        ARG policy SJF
        ARG jlist 200,100,300
        
        Here is the job list, with the run time of each job: 
          Job 0 ( length = 200.0 )
          Job 1 ( length = 100.0 )
          Job 2 ( length = 300.0 )
        
        
        ** Solutions **
        
        Execution trace:
          [ time   0 ] Run job 1 for 100.00 secs ( DONE at 100.00 )
          [ time 100 ] Run job 0 for 200.00 secs ( DONE at 300.00 )
          [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )
        
        Final statistics:
          Job   1 -- Response: 0.00  Turnaround 100.00  Wait 0.00
          Job   0 -- Response: 100.00  Turnaround 300.00  Wait 100.00
          Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00
        
          Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
    
    ```shell
    ./scheduler.py -p FIFO -l 200,100,300 -c 
    ```
    
        ARG policy FIFO
        ARG jlist 200,100,300
        
        Here is the job list, with the run time of each job: 
          Job 0 ( length = 200.0 )
          Job 1 ( length = 100.0 )
          Job 2 ( length = 300.0 )
        
        
        ** Solutions **
        
        Execution trace:
          [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
          [ time 200 ] Run job 1 for 100.00 secs ( DONE at 300.00 )
          [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )
        
        Final statistics:
          Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
          Job   1 -- Response: 200.00  Turnaround 300.00  Wait 200.00
          Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00
        
          Average -- Response: 166.67  Turnaround 366.67  Wait 166.67

3.  Now do the same, but also with the RR scheduler and a time-slice of 1.
    
    ```shell
    ./scheduler.py -p RR -l 200,100,300 -c 
    ```
    
        ARG policy RR
        ARG jlist 200,100,300
        
        Here is the job list, with the run time of each job: 
          Job 0 ( length = 200.0 )
          Job 1 ( length = 100.0 )
          Job 2 ( length = 300.0 )
        
        
        ** Solutions **
        
        Execution trace:
          [ time   0 ] Run job   0 for 1.00 secs
          [ time   1 ] Run job   1 for 1.00 secs
          [ time   2 ] Run job   2 for 1.00 secs
          [ time   3 ] Run job   0 for 1.00 secs
          [ time   4 ] Run job   1 for 1.00 secs
          [ time   5 ] Run job   2 for 1.00 secs
          [ time   6 ] Run job   0 for 1.00 secs
          [ time   7 ] Run job   1 for 1.00 secs
          [ time   8 ] Run job   2 for 1.00 secs
          [ time   9 ] Run job   0 for 1.00 secs
          [ time  10 ] Run job   1 for 1.00 secs
          [ time  11 ] Run job   2 for 1.00 secs
          [ time  12 ] Run job   0 for 1.00 secs
          [ time  13 ] Run job   1 for 1.00 secs
          [ time  14 ] Run job   2 for 1.00 secs
          [ time  15 ] Run job   0 for 1.00 secs
          [ time  16 ] Run job   1 for 1.00 secs
          [ time  17 ] Run job   2 for 1.00 secs
          [ time  18 ] Run job   0 for 1.00 secs
          [ time  19 ] Run job   1 for 1.00 secs
          [ time  20 ] Run job   2 for 1.00 secs
          [ time  21 ] Run job   0 for 1.00 secs
          [ time  22 ] Run job   1 for 1.00 secs
          [ time  23 ] Run job   2 for 1.00 secs
          [ time  24 ] Run job   0 for 1.00 secs
          [ time  25 ] Run job   1 for 1.00 secs
          [ time  26 ] Run job   2 for 1.00 secs
          [ time  27 ] Run job   0 for 1.00 secs
          [ time  28 ] Run job   1 for 1.00 secs
          [ time  29 ] Run job   2 for 1.00 secs
          [ time  30 ] Run job   0 for 1.00 secs
          [ time  31 ] Run job   1 for 1.00 secs
          [ time  32 ] Run job   2 for 1.00 secs
          [ time  33 ] Run job   0 for 1.00 secs
          [ time  34 ] Run job   1 for 1.00 secs
          [ time  35 ] Run job   2 for 1.00 secs
          [ time  36 ] Run job   0 for 1.00 secs
          [ time  37 ] Run job   1 for 1.00 secs
          [ time  38 ] Run job   2 for 1.00 secs
          [ time  39 ] Run job   0 for 1.00 secs
          [ time  40 ] Run job   1 for 1.00 secs
          [ time  41 ] Run job   2 for 1.00 secs
          [ time  42 ] Run job   0 for 1.00 secs
          [ time  43 ] Run job   1 for 1.00 secs
          [ time  44 ] Run job   2 for 1.00 secs
          [ time  45 ] Run job   0 for 1.00 secs
          [ time  46 ] Run job   1 for 1.00 secs
          [ time  47 ] Run job   2 for 1.00 secs
          [ time  48 ] Run job   0 for 1.00 secs
          [ time  49 ] Run job   1 for 1.00 secs
          [ time  50 ] Run job   2 for 1.00 secs
          [ time  51 ] Run job   0 for 1.00 secs
          [ time  52 ] Run job   1 for 1.00 secs
          [ time  53 ] Run job   2 for 1.00 secs
          [ time  54 ] Run job   0 for 1.00 secs
          [ time  55 ] Run job   1 for 1.00 secs
          [ time  56 ] Run job   2 for 1.00 secs
          [ time  57 ] Run job   0 for 1.00 secs
          [ time  58 ] Run job   1 for 1.00 secs
          [ time  59 ] Run job   2 for 1.00 secs
          [ time  60 ] Run job   0 for 1.00 secs
          [ time  61 ] Run job   1 for 1.00 secs
          [ time  62 ] Run job   2 for 1.00 secs
          [ time  63 ] Run job   0 for 1.00 secs
          [ time  64 ] Run job   1 for 1.00 secs
          [ time  65 ] Run job   2 for 1.00 secs
          [ time  66 ] Run job   0 for 1.00 secs
          [ time  67 ] Run job   1 for 1.00 secs
          [ time  68 ] Run job   2 for 1.00 secs
          [ time  69 ] Run job   0 for 1.00 secs
          [ time  70 ] Run job   1 for 1.00 secs
          [ time  71 ] Run job   2 for 1.00 secs
          [ time  72 ] Run job   0 for 1.00 secs
          [ time  73 ] Run job   1 for 1.00 secs
          [ time  74 ] Run job   2 for 1.00 secs
          [ time  75 ] Run job   0 for 1.00 secs
          [ time  76 ] Run job   1 for 1.00 secs
          [ time  77 ] Run job   2 for 1.00 secs
          [ time  78 ] Run job   0 for 1.00 secs
          [ time  79 ] Run job   1 for 1.00 secs
          [ time  80 ] Run job   2 for 1.00 secs
          [ time  81 ] Run job   0 for 1.00 secs
          [ time  82 ] Run job   1 for 1.00 secs
          [ time  83 ] Run job   2 for 1.00 secs
          [ time  84 ] Run job   0 for 1.00 secs
          [ time  85 ] Run job   1 for 1.00 secs
          [ time  86 ] Run job   2 for 1.00 secs
          [ time  87 ] Run job   0 for 1.00 secs
          [ time  88 ] Run job   1 for 1.00 secs
          [ time  89 ] Run job   2 for 1.00 secs
          [ time  90 ] Run job   0 for 1.00 secs
          [ time  91 ] Run job   1 for 1.00 secs
          [ time  92 ] Run job   2 for 1.00 secs
          [ time  93 ] Run job   0 for 1.00 secs
          [ time  94 ] Run job   1 for 1.00 secs
          [ time  95 ] Run job   2 for 1.00 secs
          [ time  96 ] Run job   0 for 1.00 secs
          [ time  97 ] Run job   1 for 1.00 secs
          [ time  98 ] Run job   2 for 1.00 secs
          [ time  99 ] Run job   0 for 1.00 secs
          [ time 100 ] Run job   1 for 1.00 secs
          [ time 101 ] Run job   2 for 1.00 secs
          [ time 102 ] Run job   0 for 1.00 secs
          [ time 103 ] Run job   1 for 1.00 secs
          [ time 104 ] Run job   2 for 1.00 secs
          [ time 105 ] Run job   0 for 1.00 secs
          [ time 106 ] Run job   1 for 1.00 secs
          [ time 107 ] Run job   2 for 1.00 secs
          [ time 108 ] Run job   0 for 1.00 secs
          [ time 109 ] Run job   1 for 1.00 secs
          [ time 110 ] Run job   2 for 1.00 secs
          [ time 111 ] Run job   0 for 1.00 secs
          [ time 112 ] Run job   1 for 1.00 secs
          [ time 113 ] Run job   2 for 1.00 secs
          [ time 114 ] Run job   0 for 1.00 secs
          [ time 115 ] Run job   1 for 1.00 secs
          [ time 116 ] Run job   2 for 1.00 secs
          [ time 117 ] Run job   0 for 1.00 secs
          [ time 118 ] Run job   1 for 1.00 secs
          [ time 119 ] Run job   2 for 1.00 secs
          [ time 120 ] Run job   0 for 1.00 secs
          [ time 121 ] Run job   1 for 1.00 secs
          [ time 122 ] Run job   2 for 1.00 secs
          [ time 123 ] Run job   0 for 1.00 secs
          [ time 124 ] Run job   1 for 1.00 secs
          [ time 125 ] Run job   2 for 1.00 secs
          [ time 126 ] Run job   0 for 1.00 secs
          [ time 127 ] Run job   1 for 1.00 secs
          [ time 128 ] Run job   2 for 1.00 secs
          [ time 129 ] Run job   0 for 1.00 secs
          [ time 130 ] Run job   1 for 1.00 secs
          [ time 131 ] Run job   2 for 1.00 secs
          [ time 132 ] Run job   0 for 1.00 secs
          [ time 133 ] Run job   1 for 1.00 secs
          [ time 134 ] Run job   2 for 1.00 secs
          [ time 135 ] Run job   0 for 1.00 secs
          [ time 136 ] Run job   1 for 1.00 secs
          [ time 137 ] Run job   2 for 1.00 secs
          [ time 138 ] Run job   0 for 1.00 secs
          [ time 139 ] Run job   1 for 1.00 secs
          [ time 140 ] Run job   2 for 1.00 secs
          [ time 141 ] Run job   0 for 1.00 secs
          [ time 142 ] Run job   1 for 1.00 secs
          [ time 143 ] Run job   2 for 1.00 secs
          [ time 144 ] Run job   0 for 1.00 secs
          [ time 145 ] Run job   1 for 1.00 secs
          [ time 146 ] Run job   2 for 1.00 secs
          [ time 147 ] Run job   0 for 1.00 secs
          [ time 148 ] Run job   1 for 1.00 secs
          [ time 149 ] Run job   2 for 1.00 secs
          [ time 150 ] Run job   0 for 1.00 secs
          [ time 151 ] Run job   1 for 1.00 secs
          [ time 152 ] Run job   2 for 1.00 secs
          [ time 153 ] Run job   0 for 1.00 secs
          [ time 154 ] Run job   1 for 1.00 secs
          [ time 155 ] Run job   2 for 1.00 secs
          [ time 156 ] Run job   0 for 1.00 secs
          [ time 157 ] Run job   1 for 1.00 secs
          [ time 158 ] Run job   2 for 1.00 secs
          [ time 159 ] Run job   0 for 1.00 secs
          [ time 160 ] Run job   1 for 1.00 secs
          [ time 161 ] Run job   2 for 1.00 secs
          [ time 162 ] Run job   0 for 1.00 secs
          [ time 163 ] Run job   1 for 1.00 secs
          [ time 164 ] Run job   2 for 1.00 secs
          [ time 165 ] Run job   0 for 1.00 secs
          [ time 166 ] Run job   1 for 1.00 secs
          [ time 167 ] Run job   2 for 1.00 secs
          [ time 168 ] Run job   0 for 1.00 secs
          [ time 169 ] Run job   1 for 1.00 secs
          [ time 170 ] Run job   2 for 1.00 secs
          [ time 171 ] Run job   0 for 1.00 secs
          [ time 172 ] Run job   1 for 1.00 secs
          [ time 173 ] Run job   2 for 1.00 secs
          [ time 174 ] Run job   0 for 1.00 secs
          [ time 175 ] Run job   1 for 1.00 secs
          [ time 176 ] Run job   2 for 1.00 secs
          [ time 177 ] Run job   0 for 1.00 secs
          [ time 178 ] Run job   1 for 1.00 secs
          [ time 179 ] Run job   2 for 1.00 secs
          [ time 180 ] Run job   0 for 1.00 secs
          [ time 181 ] Run job   1 for 1.00 secs
          [ time 182 ] Run job   2 for 1.00 secs
          [ time 183 ] Run job   0 for 1.00 secs
          [ time 184 ] Run job   1 for 1.00 secs
          [ time 185 ] Run job   2 for 1.00 secs
          [ time 186 ] Run job   0 for 1.00 secs
          [ time 187 ] Run job   1 for 1.00 secs
          [ time 188 ] Run job   2 for 1.00 secs
          [ time 189 ] Run job   0 for 1.00 secs
          [ time 190 ] Run job   1 for 1.00 secs
          [ time 191 ] Run job   2 for 1.00 secs
          [ time 192 ] Run job   0 for 1.00 secs
          [ time 193 ] Run job   1 for 1.00 secs
          [ time 194 ] Run job   2 for 1.00 secs
          [ time 195 ] Run job   0 for 1.00 secs
          [ time 196 ] Run job   1 for 1.00 secs
          [ time 197 ] Run job   2 for 1.00 secs
          [ time 198 ] Run job   0 for 1.00 secs
          [ time 199 ] Run job   1 for 1.00 secs
          [ time 200 ] Run job   2 for 1.00 secs
          [ time 201 ] Run job   0 for 1.00 secs
          [ time 202 ] Run job   1 for 1.00 secs
          [ time 203 ] Run job   2 for 1.00 secs
          [ time 204 ] Run job   0 for 1.00 secs
          [ time 205 ] Run job   1 for 1.00 secs
          [ time 206 ] Run job   2 for 1.00 secs
          [ time 207 ] Run job   0 for 1.00 secs
          [ time 208 ] Run job   1 for 1.00 secs
          [ time 209 ] Run job   2 for 1.00 secs
          [ time 210 ] Run job   0 for 1.00 secs
          [ time 211 ] Run job   1 for 1.00 secs
          [ time 212 ] Run job   2 for 1.00 secs
          [ time 213 ] Run job   0 for 1.00 secs
          [ time 214 ] Run job   1 for 1.00 secs
          [ time 215 ] Run job   2 for 1.00 secs
          [ time 216 ] Run job   0 for 1.00 secs
          [ time 217 ] Run job   1 for 1.00 secs
          [ time 218 ] Run job   2 for 1.00 secs
          [ time 219 ] Run job   0 for 1.00 secs
          [ time 220 ] Run job   1 for 1.00 secs
          [ time 221 ] Run job   2 for 1.00 secs
          [ time 222 ] Run job   0 for 1.00 secs
          [ time 223 ] Run job   1 for 1.00 secs
          [ time 224 ] Run job   2 for 1.00 secs
          [ time 225 ] Run job   0 for 1.00 secs
          [ time 226 ] Run job   1 for 1.00 secs
          [ time 227 ] Run job   2 for 1.00 secs
          [ time 228 ] Run job   0 for 1.00 secs
          [ time 229 ] Run job   1 for 1.00 secs
          [ time 230 ] Run job   2 for 1.00 secs
          [ time 231 ] Run job   0 for 1.00 secs
          [ time 232 ] Run job   1 for 1.00 secs
          [ time 233 ] Run job   2 for 1.00 secs
          [ time 234 ] Run job   0 for 1.00 secs
          [ time 235 ] Run job   1 for 1.00 secs
          [ time 236 ] Run job   2 for 1.00 secs
          [ time 237 ] Run job   0 for 1.00 secs
          [ time 238 ] Run job   1 for 1.00 secs
          [ time 239 ] Run job   2 for 1.00 secs
          [ time 240 ] Run job   0 for 1.00 secs
          [ time 241 ] Run job   1 for 1.00 secs
          [ time 242 ] Run job   2 for 1.00 secs
          [ time 243 ] Run job   0 for 1.00 secs
          [ time 244 ] Run job   1 for 1.00 secs
          [ time 245 ] Run job   2 for 1.00 secs
          [ time 246 ] Run job   0 for 1.00 secs
          [ time 247 ] Run job   1 for 1.00 secs
          [ time 248 ] Run job   2 for 1.00 secs
          [ time 249 ] Run job   0 for 1.00 secs
          [ time 250 ] Run job   1 for 1.00 secs
          [ time 251 ] Run job   2 for 1.00 secs
          [ time 252 ] Run job   0 for 1.00 secs
          [ time 253 ] Run job   1 for 1.00 secs
          [ time 254 ] Run job   2 for 1.00 secs
          [ time 255 ] Run job   0 for 1.00 secs
          [ time 256 ] Run job   1 for 1.00 secs
          [ time 257 ] Run job   2 for 1.00 secs
          [ time 258 ] Run job   0 for 1.00 secs
          [ time 259 ] Run job   1 for 1.00 secs
          [ time 260 ] Run job   2 for 1.00 secs
          [ time 261 ] Run job   0 for 1.00 secs
          [ time 262 ] Run job   1 for 1.00 secs
          [ time 263 ] Run job   2 for 1.00 secs
          [ time 264 ] Run job   0 for 1.00 secs
          [ time 265 ] Run job   1 for 1.00 secs
          [ time 266 ] Run job   2 for 1.00 secs
          [ time 267 ] Run job   0 for 1.00 secs
          [ time 268 ] Run job   1 for 1.00 secs
          [ time 269 ] Run job   2 for 1.00 secs
          [ time 270 ] Run job   0 for 1.00 secs
          [ time 271 ] Run job   1 for 1.00 secs
          [ time 272 ] Run job   2 for 1.00 secs
          [ time 273 ] Run job   0 for 1.00 secs
          [ time 274 ] Run job   1 for 1.00 secs
          [ time 275 ] Run job   2 for 1.00 secs
          [ time 276 ] Run job   0 for 1.00 secs
          [ time 277 ] Run job   1 for 1.00 secs
          [ time 278 ] Run job   2 for 1.00 secs
          [ time 279 ] Run job   0 for 1.00 secs
          [ time 280 ] Run job   1 for 1.00 secs
          [ time 281 ] Run job   2 for 1.00 secs
          [ time 282 ] Run job   0 for 1.00 secs
          [ time 283 ] Run job   1 for 1.00 secs
          [ time 284 ] Run job   2 for 1.00 secs
          [ time 285 ] Run job   0 for 1.00 secs
          [ time 286 ] Run job   1 for 1.00 secs
          [ time 287 ] Run job   2 for 1.00 secs
          [ time 288 ] Run job   0 for 1.00 secs
          [ time 289 ] Run job   1 for 1.00 secs
          [ time 290 ] Run job   2 for 1.00 secs
          [ time 291 ] Run job   0 for 1.00 secs
          [ time 292 ] Run job   1 for 1.00 secs
          [ time 293 ] Run job   2 for 1.00 secs
          [ time 294 ] Run job   0 for 1.00 secs
          [ time 295 ] Run job   1 for 1.00 secs
          [ time 296 ] Run job   2 for 1.00 secs
          [ time 297 ] Run job   0 for 1.00 secs
          [ time 298 ] Run job   1 for 1.00 secs ( DONE at 299.00 )
          [ time 299 ] Run job   2 for 1.00 secs
          [ time 300 ] Run job   0 for 1.00 secs
          [ time 301 ] Run job   2 for 1.00 secs
          [ time 302 ] Run job   0 for 1.00 secs
          [ time 303 ] Run job   2 for 1.00 secs
          [ time 304 ] Run job   0 for 1.00 secs
          [ time 305 ] Run job   2 for 1.00 secs
          [ time 306 ] Run job   0 for 1.00 secs
          [ time 307 ] Run job   2 for 1.00 secs
          [ time 308 ] Run job   0 for 1.00 secs
          [ time 309 ] Run job   2 for 1.00 secs
          [ time 310 ] Run job   0 for 1.00 secs
          [ time 311 ] Run job   2 for 1.00 secs
          [ time 312 ] Run job   0 for 1.00 secs
          [ time 313 ] Run job   2 for 1.00 secs
          [ time 314 ] Run job   0 for 1.00 secs
          [ time 315 ] Run job   2 for 1.00 secs
          [ time 316 ] Run job   0 for 1.00 secs
          [ time 317 ] Run job   2 for 1.00 secs
          [ time 318 ] Run job   0 for 1.00 secs
          [ time 319 ] Run job   2 for 1.00 secs
          [ time 320 ] Run job   0 for 1.00 secs
          [ time 321 ] Run job   2 for 1.00 secs
          [ time 322 ] Run job   0 for 1.00 secs
          [ time 323 ] Run job   2 for 1.00 secs
          [ time 324 ] Run job   0 for 1.00 secs
          [ time 325 ] Run job   2 for 1.00 secs
          [ time 326 ] Run job   0 for 1.00 secs
          [ time 327 ] Run job   2 for 1.00 secs
          [ time 328 ] Run job   0 for 1.00 secs
          [ time 329 ] Run job   2 for 1.00 secs
          [ time 330 ] Run job   0 for 1.00 secs
          [ time 331 ] Run job   2 for 1.00 secs
          [ time 332 ] Run job   0 for 1.00 secs
          [ time 333 ] Run job   2 for 1.00 secs
          [ time 334 ] Run job   0 for 1.00 secs
          [ time 335 ] Run job   2 for 1.00 secs
          [ time 336 ] Run job   0 for 1.00 secs
          [ time 337 ] Run job   2 for 1.00 secs
          [ time 338 ] Run job   0 for 1.00 secs
          [ time 339 ] Run job   2 for 1.00 secs
          [ time 340 ] Run job   0 for 1.00 secs
          [ time 341 ] Run job   2 for 1.00 secs
          [ time 342 ] Run job   0 for 1.00 secs
          [ time 343 ] Run job   2 for 1.00 secs
          [ time 344 ] Run job   0 for 1.00 secs
          [ time 345 ] Run job   2 for 1.00 secs
          [ time 346 ] Run job   0 for 1.00 secs
          [ time 347 ] Run job   2 for 1.00 secs
          [ time 348 ] Run job   0 for 1.00 secs
          [ time 349 ] Run job   2 for 1.00 secs
          [ time 350 ] Run job   0 for 1.00 secs
          [ time 351 ] Run job   2 for 1.00 secs
          [ time 352 ] Run job   0 for 1.00 secs
          [ time 353 ] Run job   2 for 1.00 secs
          [ time 354 ] Run job   0 for 1.00 secs
          [ time 355 ] Run job   2 for 1.00 secs
          [ time 356 ] Run job   0 for 1.00 secs
          [ time 357 ] Run job   2 for 1.00 secs
          [ time 358 ] Run job   0 for 1.00 secs
          [ time 359 ] Run job   2 for 1.00 secs
          [ time 360 ] Run job   0 for 1.00 secs
          [ time 361 ] Run job   2 for 1.00 secs
          [ time 362 ] Run job   0 for 1.00 secs
          [ time 363 ] Run job   2 for 1.00 secs
          [ time 364 ] Run job   0 for 1.00 secs
          [ time 365 ] Run job   2 for 1.00 secs
          [ time 366 ] Run job   0 for 1.00 secs
          [ time 367 ] Run job   2 for 1.00 secs
          [ time 368 ] Run job   0 for 1.00 secs
          [ time 369 ] Run job   2 for 1.00 secs
          [ time 370 ] Run job   0 for 1.00 secs
          [ time 371 ] Run job   2 for 1.00 secs
          [ time 372 ] Run job   0 for 1.00 secs
          [ time 373 ] Run job   2 for 1.00 secs
          [ time 374 ] Run job   0 for 1.00 secs
          [ time 375 ] Run job   2 for 1.00 secs
          [ time 376 ] Run job   0 for 1.00 secs
          [ time 377 ] Run job   2 for 1.00 secs
          [ time 378 ] Run job   0 for 1.00 secs
          [ time 379 ] Run job   2 for 1.00 secs
          [ time 380 ] Run job   0 for 1.00 secs
          [ time 381 ] Run job   2 for 1.00 secs
          [ time 382 ] Run job   0 for 1.00 secs
          [ time 383 ] Run job   2 for 1.00 secs
          [ time 384 ] Run job   0 for 1.00 secs
          [ time 385 ] Run job   2 for 1.00 secs
          [ time 386 ] Run job   0 for 1.00 secs
          [ time 387 ] Run job   2 for 1.00 secs
          [ time 388 ] Run job   0 for 1.00 secs
          [ time 389 ] Run job   2 for 1.00 secs
          [ time 390 ] Run job   0 for 1.00 secs
          [ time 391 ] Run job   2 for 1.00 secs
          [ time 392 ] Run job   0 for 1.00 secs
          [ time 393 ] Run job   2 for 1.00 secs
          [ time 394 ] Run job   0 for 1.00 secs
          [ time 395 ] Run job   2 for 1.00 secs
          [ time 396 ] Run job   0 for 1.00 secs
          [ time 397 ] Run job   2 for 1.00 secs
          [ time 398 ] Run job   0 for 1.00 secs
          [ time 399 ] Run job   2 for 1.00 secs
          [ time 400 ] Run job   0 for 1.00 secs
          [ time 401 ] Run job   2 for 1.00 secs
          [ time 402 ] Run job   0 for 1.00 secs
          [ time 403 ] Run job   2 for 1.00 secs
          [ time 404 ] Run job   0 for 1.00 secs
          [ time 405 ] Run job   2 for 1.00 secs
          [ time 406 ] Run job   0 for 1.00 secs
          [ time 407 ] Run job   2 for 1.00 secs
          [ time 408 ] Run job   0 for 1.00 secs
          [ time 409 ] Run job   2 for 1.00 secs
          [ time 410 ] Run job   0 for 1.00 secs
          [ time 411 ] Run job   2 for 1.00 secs
          [ time 412 ] Run job   0 for 1.00 secs
          [ time 413 ] Run job   2 for 1.00 secs
          [ time 414 ] Run job   0 for 1.00 secs
          [ time 415 ] Run job   2 for 1.00 secs
          [ time 416 ] Run job   0 for 1.00 secs
          [ time 417 ] Run job   2 for 1.00 secs
          [ time 418 ] Run job   0 for 1.00 secs
          [ time 419 ] Run job   2 for 1.00 secs
          [ time 420 ] Run job   0 for 1.00 secs
          [ time 421 ] Run job   2 for 1.00 secs
          [ time 422 ] Run job   0 for 1.00 secs
          [ time 423 ] Run job   2 for 1.00 secs
          [ time 424 ] Run job   0 for 1.00 secs
          [ time 425 ] Run job   2 for 1.00 secs
          [ time 426 ] Run job   0 for 1.00 secs
          [ time 427 ] Run job   2 for 1.00 secs
          [ time 428 ] Run job   0 for 1.00 secs
          [ time 429 ] Run job   2 for 1.00 secs
          [ time 430 ] Run job   0 for 1.00 secs
          [ time 431 ] Run job   2 for 1.00 secs
          [ time 432 ] Run job   0 for 1.00 secs
          [ time 433 ] Run job   2 for 1.00 secs
          [ time 434 ] Run job   0 for 1.00 secs
          [ time 435 ] Run job   2 for 1.00 secs
          [ time 436 ] Run job   0 for 1.00 secs
          [ time 437 ] Run job   2 for 1.00 secs
          [ time 438 ] Run job   0 for 1.00 secs
          [ time 439 ] Run job   2 for 1.00 secs
          [ time 440 ] Run job   0 for 1.00 secs
          [ time 441 ] Run job   2 for 1.00 secs
          [ time 442 ] Run job   0 for 1.00 secs
          [ time 443 ] Run job   2 for 1.00 secs
          [ time 444 ] Run job   0 for 1.00 secs
          [ time 445 ] Run job   2 for 1.00 secs
          [ time 446 ] Run job   0 for 1.00 secs
          [ time 447 ] Run job   2 for 1.00 secs
          [ time 448 ] Run job   0 for 1.00 secs
          [ time 449 ] Run job   2 for 1.00 secs
          [ time 450 ] Run job   0 for 1.00 secs
          [ time 451 ] Run job   2 for 1.00 secs
          [ time 452 ] Run job   0 for 1.00 secs
          [ time 453 ] Run job   2 for 1.00 secs
          [ time 454 ] Run job   0 for 1.00 secs
          [ time 455 ] Run job   2 for 1.00 secs
          [ time 456 ] Run job   0 for 1.00 secs
          [ time 457 ] Run job   2 for 1.00 secs
          [ time 458 ] Run job   0 for 1.00 secs
          [ time 459 ] Run job   2 for 1.00 secs
          [ time 460 ] Run job   0 for 1.00 secs
          [ time 461 ] Run job   2 for 1.00 secs
          [ time 462 ] Run job   0 for 1.00 secs
          [ time 463 ] Run job   2 for 1.00 secs
          [ time 464 ] Run job   0 for 1.00 secs
          [ time 465 ] Run job   2 for 1.00 secs
          [ time 466 ] Run job   0 for 1.00 secs
          [ time 467 ] Run job   2 for 1.00 secs
          [ time 468 ] Run job   0 for 1.00 secs
          [ time 469 ] Run job   2 for 1.00 secs
          [ time 470 ] Run job   0 for 1.00 secs
          [ time 471 ] Run job   2 for 1.00 secs
          [ time 472 ] Run job   0 for 1.00 secs
          [ time 473 ] Run job   2 for 1.00 secs
          [ time 474 ] Run job   0 for 1.00 secs
          [ time 475 ] Run job   2 for 1.00 secs
          [ time 476 ] Run job   0 for 1.00 secs
          [ time 477 ] Run job   2 for 1.00 secs
          [ time 478 ] Run job   0 for 1.00 secs
          [ time 479 ] Run job   2 for 1.00 secs
          [ time 480 ] Run job   0 for 1.00 secs
          [ time 481 ] Run job   2 for 1.00 secs
          [ time 482 ] Run job   0 for 1.00 secs
          [ time 483 ] Run job   2 for 1.00 secs
          [ time 484 ] Run job   0 for 1.00 secs
          [ time 485 ] Run job   2 for 1.00 secs
          [ time 486 ] Run job   0 for 1.00 secs
          [ time 487 ] Run job   2 for 1.00 secs
          [ time 488 ] Run job   0 for 1.00 secs
          [ time 489 ] Run job   2 for 1.00 secs
          [ time 490 ] Run job   0 for 1.00 secs
          [ time 491 ] Run job   2 for 1.00 secs
          [ time 492 ] Run job   0 for 1.00 secs
          [ time 493 ] Run job   2 for 1.00 secs
          [ time 494 ] Run job   0 for 1.00 secs
          [ time 495 ] Run job   2 for 1.00 secs
          [ time 496 ] Run job   0 for 1.00 secs
          [ time 497 ] Run job   2 for 1.00 secs
          [ time 498 ] Run job   0 for 1.00 secs ( DONE at 499.00 )
          [ time 499 ] Run job   2 for 1.00 secs
          [ time 500 ] Run job   2 for 1.00 secs
          [ time 501 ] Run job   2 for 1.00 secs
          [ time 502 ] Run job   2 for 1.00 secs
          [ time 503 ] Run job   2 for 1.00 secs
          [ time 504 ] Run job   2 for 1.00 secs
          [ time 505 ] Run job   2 for 1.00 secs
          [ time 506 ] Run job   2 for 1.00 secs
          [ time 507 ] Run job   2 for 1.00 secs
          [ time 508 ] Run job   2 for 1.00 secs
          [ time 509 ] Run job   2 for 1.00 secs
          [ time 510 ] Run job   2 for 1.00 secs
          [ time 511 ] Run job   2 for 1.00 secs
          [ time 512 ] Run job   2 for 1.00 secs
          [ time 513 ] Run job   2 for 1.00 secs
          [ time 514 ] Run job   2 for 1.00 secs
          [ time 515 ] Run job   2 for 1.00 secs
          [ time 516 ] Run job   2 for 1.00 secs
          [ time 517 ] Run job   2 for 1.00 secs
          [ time 518 ] Run job   2 for 1.00 secs
          [ time 519 ] Run job   2 for 1.00 secs
          [ time 520 ] Run job   2 for 1.00 secs
          [ time 521 ] Run job   2 for 1.00 secs
          [ time 522 ] Run job   2 for 1.00 secs
          [ time 523 ] Run job   2 for 1.00 secs
          [ time 524 ] Run job   2 for 1.00 secs
          [ time 525 ] Run job   2 for 1.00 secs
          [ time 526 ] Run job   2 for 1.00 secs
          [ time 527 ] Run job   2 for 1.00 secs
          [ time 528 ] Run job   2 for 1.00 secs
          [ time 529 ] Run job   2 for 1.00 secs
          [ time 530 ] Run job   2 for 1.00 secs
          [ time 531 ] Run job   2 for 1.00 secs
          [ time 532 ] Run job   2 for 1.00 secs
          [ time 533 ] Run job   2 for 1.00 secs
          [ time 534 ] Run job   2 for 1.00 secs
          [ time 535 ] Run job   2 for 1.00 secs
          [ time 536 ] Run job   2 for 1.00 secs
          [ time 537 ] Run job   2 for 1.00 secs
          [ time 538 ] Run job   2 for 1.00 secs
          [ time 539 ] Run job   2 for 1.00 secs
          [ time 540 ] Run job   2 for 1.00 secs
          [ time 541 ] Run job   2 for 1.00 secs
          [ time 542 ] Run job   2 for 1.00 secs
          [ time 543 ] Run job   2 for 1.00 secs
          [ time 544 ] Run job   2 for 1.00 secs
          [ time 545 ] Run job   2 for 1.00 secs
          [ time 546 ] Run job   2 for 1.00 secs
          [ time 547 ] Run job   2 for 1.00 secs
          [ time 548 ] Run job   2 for 1.00 secs
          [ time 549 ] Run job   2 for 1.00 secs
          [ time 550 ] Run job   2 for 1.00 secs
          [ time 551 ] Run job   2 for 1.00 secs
          [ time 552 ] Run job   2 for 1.00 secs
          [ time 553 ] Run job   2 for 1.00 secs
          [ time 554 ] Run job   2 for 1.00 secs
          [ time 555 ] Run job   2 for 1.00 secs
          [ time 556 ] Run job   2 for 1.00 secs
          [ time 557 ] Run job   2 for 1.00 secs
          [ time 558 ] Run job   2 for 1.00 secs
          [ time 559 ] Run job   2 for 1.00 secs
          [ time 560 ] Run job   2 for 1.00 secs
          [ time 561 ] Run job   2 for 1.00 secs
          [ time 562 ] Run job   2 for 1.00 secs
          [ time 563 ] Run job   2 for 1.00 secs
          [ time 564 ] Run job   2 for 1.00 secs
          [ time 565 ] Run job   2 for 1.00 secs
          [ time 566 ] Run job   2 for 1.00 secs
          [ time 567 ] Run job   2 for 1.00 secs
          [ time 568 ] Run job   2 for 1.00 secs
          [ time 569 ] Run job   2 for 1.00 secs
          [ time 570 ] Run job   2 for 1.00 secs
          [ time 571 ] Run job   2 for 1.00 secs
          [ time 572 ] Run job   2 for 1.00 secs
          [ time 573 ] Run job   2 for 1.00 secs
          [ time 574 ] Run job   2 for 1.00 secs
          [ time 575 ] Run job   2 for 1.00 secs
          [ time 576 ] Run job   2 for 1.00 secs
          [ time 577 ] Run job   2 for 1.00 secs
          [ time 578 ] Run job   2 for 1.00 secs
          [ time 579 ] Run job   2 for 1.00 secs
          [ time 580 ] Run job   2 for 1.00 secs
          [ time 581 ] Run job   2 for 1.00 secs
          [ time 582 ] Run job   2 for 1.00 secs
          [ time 583 ] Run job   2 for 1.00 secs
          [ time 584 ] Run job   2 for 1.00 secs
          [ time 585 ] Run job   2 for 1.00 secs
          [ time 586 ] Run job   2 for 1.00 secs
          [ time 587 ] Run job   2 for 1.00 secs
          [ time 588 ] Run job   2 for 1.00 secs
          [ time 589 ] Run job   2 for 1.00 secs
          [ time 590 ] Run job   2 for 1.00 secs
          [ time 591 ] Run job   2 for 1.00 secs
          [ time 592 ] Run job   2 for 1.00 secs
          [ time 593 ] Run job   2 for 1.00 secs
          [ time 594 ] Run job   2 for 1.00 secs
          [ time 595 ] Run job   2 for 1.00 secs
          [ time 596 ] Run job   2 for 1.00 secs
          [ time 597 ] Run job   2 for 1.00 secs
          [ time 598 ] Run job   2 for 1.00 secs
          [ time 599 ] Run job   2 for 1.00 secs ( DONE at 600.00 )
        
        Final statistics:
          Job   0 -- Response: 0.00  Turnaround 499.00  Wait 299.00
          Job   1 -- Response: 1.00  Turnaround 299.00  Wait 199.00
          Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00
        
          Average -- Response: 1.00  Turnaround 466.00  Wait 266.00

4.  For what types of workloads does SJF deliver the same turnaround times as FIFO?
    
    Each job runs for same amount of time

5.  For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
    
    very short run time of jobs, same as quantum length
6.  What happens to response time with SJF as job lengths increase?
    
    response time increases

7.  What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
    
    response time increases with quantum lengths
    
    Worst case of response time = N \* quantum lengths

## Scheduling: Multi-Level Feedback Queue

-   Multi-Level Feedback Queue (MLFQ)
    -   Optimize turnaround time
    -   minimize response time

How can the scheduler learn, as the system runs, the characteristics of the jobs it is running, and thus make better scheduling decisions?

How can we design a scheduler that both minimizes response time for interactive jobs while also minimizing turnaround time without a priori knowledge of job length?

### Basic Rules

-   has a number of distinct queues
-   each queue assigned a different priority level
-   a job with higher priority is chosen to run
-   same priority, use round-robin

-   **Rule 1:** If Priority(A) > Priority(B), A runs (B doesn't)
-   **Rule 2:** If Priority(A) = Priority(B), A && B run in RR

### Attempt #1: How to Change Priority

-   **Rule 3:** When a job enters the system, it is placed at the highest priority
-   **Rule 4a:** If a job uses up an entire time slice while running ,its priority is reduced (it moves down one queue).
-   **Rule 4b:** If a job gives up the CPU before the time slice is up, it stays at the same priority level

-   **goals of the algorithm:** because it doesn't know whether a job will be a short job or a long-running job, it first assumes it might be a short job, thus giving the job high priority. If it actually is a short job, it will run quickly and complete; if it is not a short job, it will slowly move down the queues, and thus soon prove itself to be a long-running more batch-like process. In this manner, MLFQ approximates SJF.

-   Problems
    -   **Starvation:** if there are "too many" interactive jobs in the system, they will combine to consume all CPU time, and thus long running jobs will never receive any CPU time (they starve).
    -   **Game the scheduler:** trick the scheduler, issue an I/O operation allows you to remain in the same queue

### Attempt #2: The Priority Boost

How to solve the starvation?

-   **Rule 5:** After some time period S, move all the jobs in the system to the topmost queue.

-   Question: what should S be set to? (voo-doo constants)
    -   too high: long-running jobs could starve
    -   too low: interactive jobs may not get a proper share of the CPU

### Attempt #3: Better Accounting

How to solve the "gaming"?

-   **Rule 4:** Once a job uses up its time allotment at a given level(regardless of how many times it has given up the CPU), its priority is reduced

### Tuning MLFQ And Other Issues

-   Parameterize a scheduler
    -   how many queues
    -   how big the time slice per queue (for round-robin)
    -   how often to boost the priority
    -   &#x2026;

Some solutions:

-   Allow for varying time-slice length across different queues
-   Solaris MLFQ: provides a set of tables to determine the parameters
-   FreeBSD: uses a formula to calculate the current priority level of a job
-   Reserve the highest priority levels for OS work
-   Allow some user advice to help set priorities, utility `nice`, see man page

### Homework (Simulation)

1.  Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.
    
    ```shell
    ./mlfq.py
    ```
    
        Here is the list of inputs:
        OPTIONS jobs 3
        OPTIONS queues 3
        OPTIONS allotments for queue  2 is   1
        OPTIONS quantum length for queue  2 is  10
        OPTIONS allotments for queue  1 is   1
        OPTIONS quantum length for queue  1 is  10
        OPTIONS allotments for queue  0 is   1
        OPTIONS quantum length for queue  0 is  10
        OPTIONS boost 0
        OPTIONS ioTime 5
        OPTIONS stayAfterIO False
        OPTIONS iobump False
        
        
        For each job, three defining characteristics are given:
          startTime : at what time does the job enter the system
          runTime   : the total CPU time needed by the job to finish
          ioFreq    : every ioFreq time units, the job issues an I/O
                      (the I/O takes ioTime units to complete)
        
        Job List:
          Job  0: startTime   0 - runTime  84 - ioFreq   7
          Job  1: startTime   0 - runTime  42 - ioFreq   3
          Job  2: startTime   0 - runTime  51 - ioFreq   4
        
        Compute the execution trace for the given workloads.
        If you would like, also compute the response and turnaround
        times for each of the jobs.
        
        Use the -c flag to get the exact results when you are finished.

2.  How would you run the scheduler to reproduce each of the examples in the chapter?
    
    ```shell
    ./mlfq.py -c
    ```
    
        Here is the list of inputs:
        OPTIONS jobs 3
        OPTIONS queues 3
        OPTIONS allotments for queue  2 is   1
        OPTIONS quantum length for queue  2 is  10
        OPTIONS allotments for queue  1 is   1
        OPTIONS quantum length for queue  1 is  10
        OPTIONS allotments for queue  0 is   1
        OPTIONS quantum length for queue  0 is  10
        OPTIONS boost 0
        OPTIONS ioTime 5
        OPTIONS stayAfterIO False
        OPTIONS iobump False
        
        
        For each job, three defining characteristics are given:
          startTime : at what time does the job enter the system
          runTime   : the total CPU time needed by the job to finish
          ioFreq    : every ioFreq time units, the job issues an I/O
                      (the I/O takes ioTime units to complete)
        
        Job List:
          Job  0: startTime   0 - runTime  84 - ioFreq   7
          Job  1: startTime   0 - runTime  42 - ioFreq   3
          Job  2: startTime   0 - runTime  51 - ioFreq   4
        
        
        Execution Trace:
        
        [ time 0 ] JOB BEGINS by JOB 0
        [ time 0 ] JOB BEGINS by JOB 1
        [ time 0 ] JOB BEGINS by JOB 2
        [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 83 (of 84) ]
        [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 82 (of 84) ]
        [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 81 (of 84) ]
        [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 80 (of 84) ]
        [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 79 (of 84) ]
        [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 78 (of 84) ]
        [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 77 (of 84) ]
        [ time 7 ] IO_START by JOB 0
        IO DONE
        [ time 7 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
        [ time 8 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
        [ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
        [ time 10 ] IO_START by JOB 1
        IO DONE
        [ time 10 ] Run JOB 2 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 50 (of 51) ]
        [ time 11 ] Run JOB 2 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 49 (of 51) ]
        [ time 12 ] IO_DONE by JOB 0
        [ time 12 ] Run JOB 2 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 48 (of 51) ]
        [ time 13 ] Run JOB 2 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 47 (of 51) ]
        [ time 14 ] IO_START by JOB 2
        IO DONE
        [ time 14 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 76 (of 84) ]
        [ time 15 ] IO_DONE by JOB 1
        [ time 15 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 75 (of 84) ]
        [ time 16 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 74 (of 84) ]
        [ time 17 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 38 (of 42) ]
        [ time 18 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 37 (of 42) ]
        [ time 19 ] IO_DONE by JOB 2
        [ time 19 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 36 (of 42) ]
        [ time 20 ] IO_START by JOB 1
        IO DONE
        [ time 20 ] Run JOB 2 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 46 (of 51) ]
        [ time 21 ] Run JOB 2 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 45 (of 51) ]
        [ time 22 ] Run JOB 2 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 44 (of 51) ]
        [ time 23 ] Run JOB 2 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 43 (of 51) ]
        [ time 24 ] IO_START by JOB 2
        IO DONE
        [ time 24 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 73 (of 84) ]
        [ time 25 ] IO_DONE by JOB 1
        [ time 25 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 35 (of 42) ]
        [ time 26 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 34 (of 42) ]
        [ time 27 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 33 (of 42) ]
        [ time 28 ] IO_START by JOB 1
        IO DONE
        [ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 72 (of 84) ]
        [ time 29 ] IO_DONE by JOB 2
        [ time 29 ] Run JOB 2 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 42 (of 51) ]
        [ time 30 ] Run JOB 2 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 41 (of 51) ]
        [ time 31 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 71 (of 84) ]
        [ time 32 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 70 (of 84) ]
        [ time 33 ] IO_START by JOB 0
        IO DONE
        [ time 33 ] IO_DONE by JOB 1
        [ time 33 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 32 (of 42) ]
        [ time 34 ] Run JOB 2 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 40 (of 51) ]
        [ time 35 ] Run JOB 2 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 39 (of 51) ]
        [ time 36 ] IO_START by JOB 2
        IO DONE
        [ time 36 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 31 (of 42) ]
        [ time 37 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 30 (of 42) ]
        [ time 38 ] IO_START by JOB 1
        IO DONE
        [ time 38 ] IO_DONE by JOB 0
        [ time 38 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 69 (of 84) ]
        [ time 39 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 68 (of 84) ]
        [ time 40 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 67 (of 84) ]
        [ time 41 ] IO_DONE by JOB 2
        [ time 41 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 66 (of 84) ]
        [ time 42 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 65 (of 84) ]
        [ time 43 ] IO_DONE by JOB 1
        [ time 43 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 64 (of 84) ]
        [ time 44 ] Run JOB 2 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 38 (of 51) ]
        [ time 45 ] Run JOB 2 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 37 (of 51) ]
        [ time 46 ] Run JOB 2 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 36 (of 51) ]
        [ time 47 ] Run JOB 2 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 35 (of 51) ]
        [ time 48 ] IO_START by JOB 2
        IO DONE
        [ time 48 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 29 (of 42) ]
        [ time 49 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 28 (of 42) ]
        [ time 50 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 27 (of 42) ]
        [ time 51 ] IO_START by JOB 1
        IO DONE
        [ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 63 (of 84) ]
        [ time 52 ] IO_START by JOB 0
        IO DONE
        [ time 52 ] IDLE
        [ time 53 ] IO_DONE by JOB 2
        [ time 53 ] Run JOB 2 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 34 (of 51) ]
        [ time 54 ] Run JOB 2 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 33 (of 51) ]
        [ time 55 ] Run JOB 2 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 32 (of 51) ]
        [ time 56 ] IO_DONE by JOB 1
        [ time 56 ] Run JOB 2 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 31 (of 51) ]
        [ time 57 ] IO_START by JOB 2
        IO DONE
        [ time 57 ] IO_DONE by JOB 0
        [ time 57 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 26 (of 42) ]
        [ time 58 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 25 (of 42) ]
        [ time 59 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 24 (of 42) ]
        [ time 60 ] IO_START by JOB 1
        IO DONE
        [ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 62 (of 84) ]
        [ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 61 (of 84) ]
        [ time 62 ] IO_DONE by JOB 2
        [ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 60 (of 84) ]
        [ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 59 (of 84) ]
        [ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 58 (of 84) ]
        [ time 65 ] IO_DONE by JOB 1
        [ time 65 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 23 (of 42) ]
        [ time 66 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 22 (of 42) ]
        [ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 57 (of 84) ]
        [ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 56 (of 84) ]
        [ time 69 ] IO_START by JOB 0
        IO DONE
        [ time 69 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 30 (of 51) ]
        [ time 70 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 29 (of 51) ]
        [ time 71 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 28 (of 51) ]
        [ time 72 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 27 (of 51) ]
        [ time 73 ] IO_START by JOB 2
        IO DONE
        [ time 73 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 21 (of 42) ]
        [ time 74 ] IO_START by JOB 1
        IO DONE
        [ time 74 ] IO_DONE by JOB 0
        [ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 55 (of 84) ]
        [ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 54 (of 84) ]
        [ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 53 (of 84) ]
        [ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 52 (of 84) ]
        [ time 78 ] IO_DONE by JOB 2
        [ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 51 (of 84) ]
        [ time 79 ] IO_DONE by JOB 1
        [ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 50 (of 84) ]
        [ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 49 (of 84) ]
        [ time 81 ] IO_START by JOB 0
        IO DONE
        [ time 81 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 26 (of 51) ]
        [ time 82 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 25 (of 51) ]
        [ time 83 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 24 (of 51) ]
        [ time 84 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 23 (of 51) ]
        [ time 85 ] IO_START by JOB 2
        IO DONE
        [ time 85 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 20 (of 42) ]
        [ time 86 ] IO_DONE by JOB 0
        [ time 86 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 19 (of 42) ]
        [ time 87 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 18 (of 42) ]
        [ time 88 ] IO_START by JOB 1
        IO DONE
        [ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 48 (of 84) ]
        [ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 47 (of 84) ]
        [ time 90 ] IO_DONE by JOB 2
        [ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 46 (of 84) ]
        [ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 45 (of 84) ]
        [ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 44 (of 84) ]
        [ time 93 ] IO_DONE by JOB 1
        [ time 93 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 22 (of 51) ]
        [ time 94 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 21 (of 51) ]
        [ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 43 (of 84) ]
        [ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 42 (of 84) ]
        [ time 97 ] IO_START by JOB 0
        IO DONE
        [ time 97 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 17 (of 42) ]
        [ time 98 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 16 (of 42) ]
        [ time 99 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 15 (of 42) ]
        [ time 100 ] IO_START by JOB 1
        IO DONE
        [ time 100 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 20 (of 51) ]
        [ time 101 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 19 (of 51) ]
        [ time 102 ] IO_START by JOB 2
        IO DONE
        [ time 102 ] IO_DONE by JOB 0
        [ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 41 (of 84) ]
        [ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 40 (of 84) ]
        [ time 104 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 39 (of 84) ]
        [ time 105 ] IO_DONE by JOB 1
        [ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 38 (of 84) ]
        [ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 37 (of 84) ]
        [ time 107 ] IO_DONE by JOB 2
        [ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 36 (of 84) ]
        [ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 35 (of 84) ]
        [ time 109 ] IO_START by JOB 0
        IO DONE
        [ time 109 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 14 (of 42) ]
        [ time 110 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 13 (of 42) ]
        [ time 111 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 12 (of 42) ]
        [ time 112 ] IO_START by JOB 1
        IO DONE
        [ time 112 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 18 (of 51) ]
        [ time 113 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 17 (of 51) ]
        [ time 114 ] IO_DONE by JOB 0
        [ time 114 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 16 (of 51) ]
        [ time 115 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 15 (of 51) ]
        [ time 116 ] IO_START by JOB 2
        IO DONE
        [ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 34 (of 84) ]
        [ time 117 ] IO_DONE by JOB 1
        [ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 33 (of 84) ]
        [ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 32 (of 84) ]
        [ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 31 (of 84) ]
        [ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 30 (of 84) ]
        [ time 121 ] IO_DONE by JOB 2
        [ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 29 (of 84) ]
        [ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 28 (of 84) ]
        [ time 123 ] IO_START by JOB 0
        IO DONE
        [ time 123 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 11 (of 42) ]
        [ time 124 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 10 (of 42) ]
        [ time 125 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 9 (of 42) ]
        [ time 126 ] IO_START by JOB 1
        IO DONE
        [ time 126 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 14 (of 51) ]
        [ time 127 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 13 (of 51) ]
        [ time 128 ] IO_DONE by JOB 0
        [ time 128 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 12 (of 51) ]
        [ time 129 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 11 (of 51) ]
        [ time 130 ] IO_START by JOB 2
        IO DONE
        [ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 27 (of 84) ]
        [ time 131 ] IO_DONE by JOB 1
        [ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 26 (of 84) ]
        [ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 25 (of 84) ]
        [ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 24 (of 84) ]
        [ time 134 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 8 (of 42) ]
        [ time 135 ] IO_DONE by JOB 2
        [ time 135 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 7 (of 42) ]
        [ time 136 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 6 (of 42) ]
        [ time 137 ] IO_START by JOB 1
        IO DONE
        [ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 23 (of 84) ]
        [ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 22 (of 84) ]
        [ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 21 (of 84) ]
        [ time 140 ] IO_START by JOB 0
        IO DONE
        [ time 140 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 10 (of 51) ]
        [ time 141 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 9 (of 51) ]
        [ time 142 ] IO_DONE by JOB 1
        [ time 142 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 8 (of 51) ]
        [ time 143 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 7 (of 51) ]
        [ time 144 ] IO_START by JOB 2
        IO DONE
        [ time 144 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 5 (of 42) ]
        [ time 145 ] IO_DONE by JOB 0
        [ time 145 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 4 (of 42) ]
        [ time 146 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 3 (of 42) ]
        [ time 147 ] IO_START by JOB 1
        IO DONE
        [ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 20 (of 84) ]
        [ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 19 (of 84) ]
        [ time 149 ] IO_DONE by JOB 2
        [ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 18 (of 84) ]
        [ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 17 (of 84) ]
        [ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 16 (of 84) ]
        [ time 152 ] IO_DONE by JOB 1
        [ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 15 (of 84) ]
        [ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 14 (of 84) ]
        [ time 154 ] IO_START by JOB 0
        IO DONE
        [ time 154 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 6 (of 51) ]
        [ time 155 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 5 (of 51) ]
        [ time 156 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 4 (of 51) ]
        [ time 157 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 3 (of 51) ]
        [ time 158 ] IO_START by JOB 2
        IO DONE
        [ time 158 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 2 (of 42) ]
        [ time 159 ] IO_DONE by JOB 0
        [ time 159 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 1 (of 42) ]
        [ time 160 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 0 (of 42) ]
        [ time 161 ] FINISHED JOB 1
        [ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 13 (of 84) ]
        [ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 12 (of 84) ]
        [ time 163 ] IO_DONE by JOB 2
        [ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 11 (of 84) ]
        [ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 10 (of 84) ]
        [ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 9 (of 84) ]
        [ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 8 (of 84) ]
        [ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 7 (of 84) ]
        [ time 168 ] IO_START by JOB 0
        IO DONE
        [ time 168 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 2 (of 51) ]
        [ time 169 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 1 (of 51) ]
        [ time 170 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 0 (of 51) ]
        [ time 171 ] FINISHED JOB 2
        [ time 171 ] IDLE
        [ time 172 ] IDLE
        [ time 173 ] IO_DONE by JOB 0
        [ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 6 (of 84) ]
        [ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 5 (of 84) ]
        [ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 4 (of 84) ]
        [ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 3 (of 84) ]
        [ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 2 (of 84) ]
        [ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 1 (of 84) ]
        [ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 0 (of 84) ]
        [ time 180 ] FINISHED JOB 0
        
        Final statistics:
          Job  0: startTime   0 - response   0 - turnaround 180
          Job  1: startTime   0 - response   7 - turnaround 161
          Job  2: startTime   0 - response  10 - turnaround 171
        
          Avg  2: startTime n/a - response 5.67 - turnaround 170.67

3.  How would you configure the scheduler parameters to behave just like a round-robin scheduler?
4.  Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.
5.  Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long- running (and potentially-starving) job gets at least 5% of the CPU?
6.  One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

## The Abstraction: Address Spaces


### Multiprogramming and Time Sharing

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

### The Address Space

Address space is a abstraction:

-   **code:** static, put on the top of the address space.
-   **stack:** allocate local variables and pass parameters and return values to and from routines. starts at bottom grows upward.
-   **heap:** dynamically-allocated, user-managed memory. starts just after the code and grows downward

Stack and heap just have to grow in opposite directions.

### Goals

-   **transparency:** program shouldn't be aware of the fact that memory is virtualized.
-   **efficiency:** efficient in time and space; rely on hardware support, including hardware features such as TLBs.
-   **protection:** protection access or affect the memory contents of any other processes and the OS itself. The principle of isolation.

### Homework(Code)

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
