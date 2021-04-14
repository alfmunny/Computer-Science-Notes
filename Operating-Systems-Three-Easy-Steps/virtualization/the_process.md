      - [The Abstraction: The Process](#sec-1)
        - [A Process](#sec-1-1)
        - [Process API](#sec-1-2)
        - [Process Creation](#sec-1-3)
        - [Process States](#sec-1-4)
        - [Data Sctructures](#sec-1-5)
        - [Homework](#sec-1-6)

# The Abstraction: The Process<a id="sec-1"></a>


## A Process<a id="sec-1-1"></a>

-   absctration of a running program
-   can be described by state:
    -   contents of memory in its address space
    -   contents of CPU registers
    -   information about I/O

## Process API<a id="sec-1-2"></a>

-   Create
-   Destory
-   Wait
-   Miscellaneous Control (kill, wait, suspend, resume)
-   Status

## Process Creation<a id="sec-1-3"></a>

1.  Loading process:
    -   eagerly
    -   lazily: paging and swapping -> virtualization of memory
2.  Memory allocation:
    -   stack: local variables, function parameters, and return addresses
    -   heap: linked lists, hash tables, trees, and ohter interesting data structures
        -   small at first,, via malloc() more memory can be allocated to satisfy such calls
3.  Start the program at the entry point, main()

## Process States<a id="sec-1-4"></a>

-   Running
-   Ready
-   Blocked
    
    Ready -> scheduled -> Running
    
    Running -> descheduled -> Ready
    
    Running -> IO initiated -> Blocked -> IO done -> Ready
    
    The transition decision is made by the **scheduler**

## Data Sctructures<a id="sec-1-5"></a>

-   **process list:** track which process is currenly running, ready or blocked. (and also zombie state and -> examine the return, wait for child or kill)
-   **register context:** hold for stopped process, the contents of its registers.
-   **context switch:** by restorig these resigters, the OS can resume running the process.

## Homework<a id="sec-1-6"></a>

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
