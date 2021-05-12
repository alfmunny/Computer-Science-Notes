# Scheduling: Multi-Level Feedback Queue

-   Multi-Level Feedback Queue (MLFQ)
    -   Optimize turnaround time
    -   minimize response time

How can the scheduler learn, as the system runs, the characteristics of the jobs it is running, and thus make better scheduling decisions?

How can we design a scheduler that both minimizes response time for interactive jobs while also minimizing turnaround time without a priori knowledge of job length?

## Basic Rules

-   has a number of distinct queues
-   each queue assigned a different priority level
-   a job with higher priority is chosen to run
-   same priority, use round-robin

-   **Rule 1:** If Priority(A) > Priority(B), A runs (B doesn't)
-   **Rule 2:** If Priority(A) = Priority(B), A && B run in RR

## Attempt #1: How to Change Priority

-   **Rule 3:** When a job enters the system, it is placed at the highest priority
-   **Rule 4a:** If a job uses up an entire time slice while running ,its priority is reduced (it moves down one queue).
-   **Rule 4b:** If a job gives up the CPU before the time slice is up, it stays at the same priority level

-   **goals of the algorithm:** because it doesn't know whether a job will be a short job or a long-running job, it first assumes it might be a short job, thus giving the job high priority. If it actually is a short job, it will run quickly and complete; if it is not a short job, it will slowly move down the queues, and thus soon prove itself to be a long-running more batch-like process. In this manner, MLFQ approximates SJF.

-   Problems
    -   **Starvation:** if there are "too many" interactive jobs in the system, they will combine to consume all CPU time, and thus long running jobs will never receive any CPU time (they starve).
    -   **Game the scheduler:** trick the scheduler, issue an I/O operation allows you to remain in the same queue

## Attempt #2: The Priority Boost

How to solve the starvation?

-   **Rule 5:** After some time period S, move all the jobs in the system to the topmost queue.

-   Question: what should S be set to? (voo-doo constants)
    -   too high: long-running jobs could starve
    -   too low: interactive jobs may not get a proper share of the CPU

## Attempt #3: Better Accounting

How to solve the "gaming"?

-   **Rule 4:** Once a job uses up its time allotment at a given level(regardless of how many times it has given up the CPU), its priority is reduced

## Tuning MLFQ And Other Issues

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

## Homework (Simulation)

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

2.  How would you run the scheduler to reproduce each of the exam- ples in the chapter?
3.  How would you configure the scheduler parameters to behave just like a round-robin scheduler?
4.  Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.
5.  Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long- running (and potentially-starving) job gets at least 5% of the CPU?
6.  One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.
