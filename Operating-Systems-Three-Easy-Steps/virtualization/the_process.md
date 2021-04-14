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

4.  We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, in- stead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?

5.  Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.

6.  One other important behavior is what to do when an I/O com- pletes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized?

7.  Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?
