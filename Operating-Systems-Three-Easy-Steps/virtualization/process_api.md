    - [Interlude: Process API](#sec-1)
      - [fork()](#sec-1-1)
      - [wait()](#sec-1-2)
      - [exec()](#sec-1-3)
      - [Why?](#sec-1-4)
      - [Process Control And Users](#sec-1-5)
      - [Tools](#sec-1-6)
      - [Homework(Simulation)](#sec-1-7)
      - [Homework (Code)](#sec-1-8)

# Interlude: Process API<a id="sec-1"></a>

Unix way to create a new process with a pair of system calls: `fork()` and `exec()`. `wait()` can be used to wait for a created process to complete.

## fork()<a id="sec-1-1"></a>

-   Create a new process
-   Create an exact copy of the calling process
    -   Both are about to return from the fork()
    -   They have different return values of fork()
        -   The parent receives the the PID of the child
        -   The child receives zero
    -   The child has its own address space, own registers, own PC, and so forth.
-   Output is not deterministic

## wait()<a id="sec-1-2"></a>

-   The parent process calls wait() to delay its execution.
-   When the child is done, wait() returns to the parent.
-   The output is deterministic.

## exec()<a id="sec-1-3"></a>

-   Run a program that is different from the calling program.
-   What it does:
    -   Loads code from that executable and overwrites its current code segment
    -   The heap and stack and other parts of the memory space are reinitialized.
    -   OS runs that program.

## Why?<a id="sec-1-4"></a>

-   Separation of `fork()` and `exec()`
    -   Lets the shell run code after `fork()` and before `exec()`
    -   Like redirection in shell
    -   pipe

## Process Control And Users<a id="sec-1-5"></a>

-   `kill()`
-   `SIGINT`
-   `SIGTSTP`
-   `signal()` to catch various signals
-   User generally can only control their own processes.

## Tools<a id="sec-1-6"></a>

`top` and `ps`

## Homework(Simulation)<a id="sec-1-7"></a>

1.  Run ./fork.py -s 10 and see which actions are taken. Can you

predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it

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

## Homework (Code)<a id="sec-1-8"></a>
