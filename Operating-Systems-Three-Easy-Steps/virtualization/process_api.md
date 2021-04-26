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
        Action: b forks c
        Action: c forks d
        Action: d EXITS
        Action: b forks e
        Action: c forks f
        Action: e forks g
        Action: f forks h
        Action: e forks i
        Action: e forks j
        Action: e EXITS
        Action: i forks k
        Action: j forks l
        Action: j forks m
        Action: k forks n
        Action: i EXITS
        Action: n forks o
        Action: g forks p
        Action: g forks q
        Action: b forks r
        Action: n forks s
        Action: o EXITS
        Action: a forks t
        Action: k forks u
        Action: r forks v
        Action: p forks w
        Action: g EXITS
        Action: m forks x
        Action: x forks y
        Action: y EXITS
        Action: x EXITS
        Action: w forks z
        Action: v forks A
        Action: s forks B
        Action: A forks C
        Action: q EXITS
        Action: s forks D
        Action: l forks E
        Action: h forks F
        Action: f forks G
        Action: c forks H
        Action: w forks I
        Action: E EXITS
        Action: C EXITS
        Action: t forks J
        Action: B forks K
        Action: K EXITS
        Action: j forks L
        Action: u EXITS
        Action: m EXITS
        Action: h forks M
        Action: w EXITS
        Action: I forks N
        Action: F EXITS
        Action: r EXITS
        Action: j forks O
        Action: z forks P
        Action: B EXITS
        Action: t forks Q
        Action: Q forks R
        Action: h forks S
        Action: f EXITS
        Action: M EXITS
        Action: b EXITS
        Action: A EXITS
        Action: G EXITS
        Action: l forks T
        Action: D EXITS
        Action: R EXITS
        Action: p forks U
        Action: s forks V
        Action: p EXITS
        Action: T EXITS
        Action: S forks W
        Action: s forks X
        Action: S forks Y
        Action: c EXITS
        Action: H EXITS
        Action: O forks Z
        Action: Q EXITS
        Action: k forks aa
        Action: j forks ab
        Action: j forks ac
        Action: W forks ad
        Action: I forks ae
        Action: V forks af
        Action: aa forks ag
        Action: S EXITS
        Action: I forks ah
        Action: J EXITS
        Action: Y forks ai
        Action: ad forks aj
        Action: P forks ak
        Action: n forks al
        Action: a forks am
        Action: k forks an
        Action: Y forks ao
        Action: ac EXITS
        Action: Z forks ap
        Action: aj forks aq
        
                                Final Process Tree:
                                       a
                                       ├── j
                                       │   ├── l
                                       │   ├── L
                                       │   ├── O
                                       │   │   └── Z
                                       │   │       └── ap
                                       │   └── ab
                                       ├── k
                                       │   ├── aa
                                       │   │   └── ag
                                       │   └── an
                                       ├── n
                                       │   ├── s
                                       │   │   ├── V
                                       │   │   │   └── af
                                       │   │   └── X
                                       │   └── al
                                       ├── t
                                       ├── z
                                       │   └── P
                                       │       └── ak
                                       ├── I
                                       │   ├── N
                                       │   ├── ae
                                       │   └── ah
                                       ├── v
                                       ├── h
                                       ├── U
                                       ├── W
                                       ├── ad
                                       │   └── aj
                                       │       └── aq
                                       ├── Y
                                       │   ├── ai
                                       │   └── ao
                                       └── am

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

1.  Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to some- thing (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
    
    ```C
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
    
        This is parent of 549173 (pid:549172), x = 102 
        This is child 549173 , x = 101 
    
    Both process can change the variable.

2.  Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
    
    ```C
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
    
        This is parent of 549180 (pid:549179)
        This is child (pid:549180)
    
    ```shell
    cat /tmp/2.txt
    ```
    
        parent: hello world
         child: hello world
         
    
    Both file can access the file descriptor

3.  Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

4.  Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
    
    ```C
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
    
        This is parent of 549189 (pid:549188)
        total 52
        -rwxrwxr-x 1 alfmunny alfmunny 12111 Apr 22 23:43 fork.py
        -rwxrwxr-x 1 alfmunny alfmunny 19859 Apr 22 23:43 generator.py
        -rw-rw-r-- 1 alfmunny alfmunny  4954 Apr 22 23:43 README-fork.md
        -rw-rw-r-- 1 alfmunny alfmunny  4996 Apr 22 23:43 README-generator.md
        -rw-rw-r-- 1 alfmunny alfmunny   448 Apr 22 23:43 README.md
    
    See all examples for different variants: [exec manual](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html).

5.  Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?
    
    ```C
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
        This is parent of 549196 (pid:549195)
        parent wait returns 549196
    
    wait() in parent returns the pid of child. wait() in child returns -1.

6.  Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
    
    ```C
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
    
        This is parent of 549203 (pid:549202)
        parent wait returns 0total 52
        -rwxrwxr-x 1 alfmunny alfmunny 12111 Apr 22 23:43 fork.py
        -rwxrwxr-x 1 alfmunny alfmunny 19859 Apr 22 23:43 generator.py
        -rw-rw-r-- 1 alfmunny alfmunny  4954 Apr 22 23:43 README-fork.md
        -rw-rw-r-- 1 alfmunny alfmunny  4996 Apr 22 23:43 README-generator.md
        -rw-rw-r-- 1 alfmunny alfmunny   448 Apr 22 23:43 README.md
    
    waitpid is able to not to block the parent.

7.  Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
    
    print nothing

8.  Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
    
    ```C
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
    
        This is child (pid:549210)
        This is parent of 549210 (pid:549209)
        This is child (pid:549211)
        child 2 read message from child 1.This is parent of 549210 (pid:549209)
        This is parent of 549211 (pid:549209)
