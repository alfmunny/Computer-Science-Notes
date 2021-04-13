  - [Operating Systems Three Easy Steps](#sec-1)
    - [Virtualization](#sec-1-1)
      - [The Process](#sec-1-1-1)
      - [Interlude: Process API](#sec-1-1-2)
      - [Mechanism: Limit Direct Execution](#sec-1-1-3)

# TODO Operating Systems Three Easy Steps<a id="sec-1"></a>

## Virtualization<a id="sec-1-1"></a>

### The Process<a id="sec-1-1-1"></a>


1.  Process

    -   absctration of a running program
    -   can be described by state:
        -   contents of memory in its address space
        -   contents of CPU registers
        -   information about I/O

2.  Process API

    -   Create
    -   Destory
    -   Wait
    -   Miscellaneous Control (kill, wait, suspend, resume)
    -   Status

3.  Process Creation

    1.  Loading process:
        -   eagerly
        -   lazily: paging and swapping -> virtualization of memory
    2.  Memory allocation:
        -   stack: local variables, function parameters, and return addresses
        -   heap: linked lists, hash tables, trees, and ohter interesting data structures
            -   small at first,, via malloc() more memory can be allocated to satisfy such calls
    3.  Start the program at the entry point, main()

4.  Process States

    -   Running
    -   Ready
    -   Blocked
        
        Ready -> scheduled -> Running
        
        Running -> descheduled -> Ready
        
        Running -> IO initiated -> Blocked -> IO done -> Ready
        
        The transition decision is made by the **scheduler**

5.  Data Sctructures

    -   **process list:** track which process is currenly running, ready or blocked. (and also zombie state and -> examine the return, wait for child or kill)
    -   **register context:** hold for stopped process, the contents of its registers.
    -   **context switch:** by restorig these resigters, the OS can resume running the process.

6.  Homework

    1.  Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
        
        ```shell
        ./process-run.py -l 5:100,5:100 -c -p
        ```
    
    2.  Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
        
        ```shell
        ./process-run.py -l 4:100,1:0 -c -p
        ```
    
    3 Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)
    
    ```shell
    ./process-run.py -l 1:0,4:100 -c -p
    ```
    
    1.  We’ll now explore some of the other flags. One important flag is
    
    -S, which determines how the system reacts when a process is- sues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, in- stead waiting until the process is completely finished. What hap- pens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?
    
    1.  Now, run the same processes, but with the switching behavior set
    
    to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.
    
    1.  One other important behavior is what to do when an I/O com-
    
    pletes. With -I IO RUN LATER, when an I/O completes, the pro- cess that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized?
    
    1.  Now run the same processes, but with -I IO RUN IMMEDIATE set,
    
    which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just com- pleted an I/O again be a good idea?

### Interlude: Process API<a id="sec-1-1-2"></a>

### Mechanism: Limit Direct Execution<a id="sec-1-1-3"></a>
