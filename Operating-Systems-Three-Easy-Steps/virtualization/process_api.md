# Interlude: Process API

Unix way to create a new process with a pair of system calls: `fork()` and `exec()`. `wait()` can be used to wait for a created process to complete.

## fork()

-   Create a new process
-   Create an exact copy of the calling process
    -   Both are about to return from the fork()
    -   They have different return values of fork()
        -   The parent receives the the PID of the child
        -   The child receives zero
    -   The child has its own address space, own registers, own PC, and so forth.
-   Output is not deterministic

## wait()

-   The parent process calls wait() to delay its execution.
-   When the child is done, wait() returns to the parent.
-   The output is deterministic.

## exec()

-   Run a program that is different from the calling program.
-   What it does:
    -   Loads code from that executable and overwrites its current code segment
    -   The heap and stack and other parts of the memory space are reinitialized.
    -   OS runs that program.

## Why?

-   Separation of `fork()` and `exec()`
    -   Lets the shell run code after `fork()` and before `exec()`
    -   Like redirection in shell
    -   pipe

## Process Control And Users

-   `kill()`
-   `SIGINT`
-   `SIGTSTP`
-   `signal()` to catch various signals
-   User generally can only control their own processes.

## Tools

`top` and `ps`

## Homework(Simulation)

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
    
    ```shell
    
    ```

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
        Action: c forks d
        Action: c forks e
        Action: e forks f
        Action: c forks g
        Action: d forks h
        Action: b EXITS
        Action: h forks i
        Action: c forks j
        Action: j forks k
        Action: j forks l
        Action: h forks m
        Action: h forks n
        Action: c forks o
        Action: h forks p
        Action: i EXITS
        Action: k forks q
        Action: q forks r
        Action: n EXITS
        Action: o forks s
        Action: g forks t
        Action: k EXITS
        Action: s forks u
        Action: q forks v
        Action: o forks w
        Action: r forks x
        Action: v forks y
        Action: w EXITS
        Action: m EXITS
        Action: e forks z
        Action: q EXITS
        Action: y forks A
        Action: g forks B
        Action: A EXITS
        Action: e EXITS
        Action: a forks C
        Action: h forks D
        Action: s forks E
        Action: t forks F
        Action: D forks G
        Action: G EXITS
        Action: s forks H
        Action: f forks I
        Action: j forks J
        Action: H forks K
        Action: I forks L
        Action: B forks M
        Action: M forks N
        Action: M forks O
        Action: O forks P
        Action: z forks Q
        Action: E forks R
        Action: h EXITS
        Action: j forks S
        Action: c EXITS
        Action: O forks T
        Action: l forks U
        Action: U forks V
        Action: x forks W
        Action: J forks X
        Action: M forks Y
        Action: t forks Z
        Action: I forks aa
        Action: V forks ab
        Action: U forks ac
        Action: j EXITS
        Action: L forks ad
        Action: D EXITS
        Action: X EXITS
        Action: E EXITS
        Action: Y forks ae
        Action: F EXITS
        Action: C forks af
        Action: N forks ag
        Action: U forks ah
        Action: R forks ai
        Action: Y forks aj
        Action: Q EXITS
        Action: d forks ak
        Action: r EXITS
        Action: ad forks al
        Action: ad forks am
        Action: y forks an
        Action: C EXITS
        Action: ab forks ao
        Action: ad forks ap
        Action: ag forks aq
        Action: an EXITS
        Action: O forks ar
        Action: K forks as
        Action: M forks at
        Action: V forks au
        Action: S forks av
        Action: d forks aw
        Action: u forks ax
        Action: I forks ay
        Action: au forks az
        Action: M forks aA
        Action: u forks aB
        
                                Final Process Tree:
                                       a
                                       ├── v
                                       ├── y
                                       ├── f
                                       │   └── I
                                       │       ├── L
                                       │       │   └── ad
                                       │       │       ├── al
                                       │       │       ├── am
                                       │       │       └── ap
                                       │       ├── aa
                                       │       └── ay
                                       ├── z
                                       ├── p
                                       ├── d
                                       │   ├── ak
                                       │   └── aw
                                       ├── g
                                       ├── t
                                       │   └── Z
                                       ├── B
                                       ├── M
                                       │   ├── Y
                                       │   │   ├── ae
                                       │   │   └── aj
                                       │   ├── at
                                       │   └── aA
                                       ├── N
                                       │   └── ag
                                       │       └── aq
                                       ├── O
                                       │   ├── T
                                       │   └── ar
                                       ├── P
                                       ├── l
                                       │   └── U
                                       │       ├── V
                                       │       │   ├── ab
                                       │       │   │   └── ao
                                       │       │   └── au
                                       │       │       └── az
                                       │       ├── ac
                                       │       └── ah
                                       ├── J
                                       ├── S
                                       │   └── av
                                       ├── o
                                       ├── s
                                       ├── u
                                       │   ├── ax
                                       │   └── aB
                                       ├── R
                                       │   └── ai
                                       ├── H
                                       ├── K
                                       │   └── as
                                       ├── x
                                       ├── W
                                       └── af

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

## Homework(code)

```C
int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int) getpid());
  int f = fork();
  if (f < 0) {
    printf("fork failed\n");
    exit(1);
  } else if (f == 0){
    printf("This is child (pid:%d)\n", (int) getpid());
  } else {
    printf("This is parent of %d (pid:%d)\n", f, (int) getpid());
  }
  return 0;
}
```

    hello world (pid:484758)
    This is parent of 484759 (pid:484758)
    hello world (pid:484758)
    This is child (pid:484759)
