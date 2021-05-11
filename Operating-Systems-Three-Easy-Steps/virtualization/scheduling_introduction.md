# Scheduling: Introduction

-   **scheduling metrics:** turnaround time.
    -   the turnaround time of a job is defined as the time at which the job completes minus the time at which the job arrived in the system.

## Workload Assumption

1.  Each job runs for the same amount of time.
2.  All jobs arrive at the same time.
3.  Once started, each job runs to completion.
4.  All jobs only use the CPU (i.e., they perform no I/O)
5.  The run-time of each job is known.

## First In, First Out(FIFO)

Simple and easy to implement.

## Shortest Job First (SJF)

Relax assumption 1:

What if no longer assume that each job runs for the same amount of time.

Solution: SJF

## Shortest Time-to-Completion First (STCF)

Relax assumption 2:

jobs can arrive at any time instead of all at once.

To address this concern, we need to relax assumption 3:

jobs does not run to completion.

Solution: STCF

Any time a new job enters the system, the STCF scheduler determines which of the remaining jobs has the least time left, and schedules that one.

## A new Metric: Response Time

-   **Response Time:** the time from when the job arrives in a system to the first time it is scheduled

How can we build a scheduler that is sensitive to response time?

## Round Robin

-   **Round-Robin:** instead of running jobs to completion, RR runs a job for a time slice (sometimes called a scheduling quantum) and then switches to the next job in the run queue. It repeatedly does so until the jobs are finished. For this reason, RR is sometimes called time-slicing.

The shorter the time-slice is, the better the performance of RR under the response-time metric.

-   Problem (trade-off)
    -   cost of context switching
    -   turnaround time is awful

## Incorporating I/O

Relax assumption 4

While interactive jobs are performing I/O, other CPU-intensive jobs run, thua better utilizing the processor.

## No More Oracle

Relax assumption 5

Building a scheduler that uses the recent past to predict the future.

## Homework(Simulation)
