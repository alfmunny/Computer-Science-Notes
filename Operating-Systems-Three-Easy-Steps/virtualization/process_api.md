# Process API

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
        Action: b EXITS
        Action: d EXITS
        Action: c forks e
        Action: e forks f
        Action: c forks g
        Action: a forks h
        Action: f forks i
        Action: g forks j
        Action: j forks k
        Action: j EXITS
        Action: g forks l
        Action: e forks m
        Action: l EXITS
        Action: f forks n
        Action: f forks o
        Action: h EXITS
        Action: i forks p
        Action: i forks q
        Action: g forks r
        Action: p forks s
        Action: g EXITS
        Action: i EXITS
        Action: o forks t
        Action: q EXITS
        Action: k forks u
        Action: e EXITS
        Action: p forks v
        Action: r forks w
        Action: t EXITS
        Action: p forks x
        Action: c forks y
        Action: u forks z
        Action: m EXITS
        Action: u EXITS
        Action: s forks A
        Action: z EXITS
        Action: c forks B
        Action: y forks C
        Action: o EXITS
        Action: c forks D
        Action: n forks E
        Action: a forks F
        Action: s forks G
        Action: w EXITS
        Action: E EXITS
        Action: B EXITS
        Action: v forks H
        Action: y EXITS
        Action: r EXITS
        Action: A forks I
        Action: x forks J
        Action: v forks K
        Action: p forks L
        Action: K forks M
        Action: D forks N
        Action: C forks O
        Action: f forks P
        Action: c forks Q
        Action: P EXITS
        Action: v forks R
        Action: I forks S
        Action: f forks T
        Action: f forks U
        Action: F forks V
        Action: T forks W
        Action: A EXITS
        Action: x forks X
        Action: N forks Y
        Action: D forks Z
        Action: T forks aa
        Action: s EXITS
        Action: M forks ab
        Action: Q EXITS
        Action: L forks ac
        Action: x EXITS
        Action: S forks ad
        Action: L forks ae
        Action: K EXITS
        Action: c EXITS
        Action: a forks af
        Action: V EXITS
        Action: Z forks ag
        Action: H EXITS
        Action: ae forks ah
        Action: ad forks ai
        Action: aa EXITS
        Action: I EXITS
        Action: ah EXITS
        Action: ai forks aj
        Action: ag forks ak
        Action: C forks al
        Action: C EXITS
        Action: J forks am
        Action: ag forks an
        Action: Z forks ao
        Action: W forks ap
        Action: R forks aq
        
                                Final Process Tree:
                                       a
                                       ├── k
                                       ├── p
                                       │   ├── v
                                       │   │   └── R
                                       │   │       └── aq
                                       │   └── L
                                       │       ├── ac
                                       │       └── ae
                                       ├── f
                                       │   ├── T
                                       │   │   └── W
                                       │   │       └── ap
                                       │   └── U
                                       ├── n
                                       ├── F
                                       ├── S
                                       │   └── ad
                                       │       └── ai
                                       │           └── aj
                                       ├── G
                                       ├── J
                                       │   └── am
                                       ├── X
                                       ├── M
                                       ├── ab
                                       ├── D
                                       ├── N
                                       ├── Y
                                       ├── Z
                                       │   ├── ag
                                       │   │   ├── ak
                                       │   │   └── an
                                       │   └── ao
                                       ├── af
                                       ├── O
                                       └── al

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
    
        This is parent of 557964 (pid:557963), x = 102 
        This is child 557964 , x = 101 
    
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
    
        This is parent of 557971 (pid:557970)
        This is child (pid:557971)
    
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
    
        This is parent of 557980 (pid:557979)
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
        This is parent of 557987 (pid:557986)
        parent wait returns 557987
    
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
    
        This is parent of 557994 (pid:557993)
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
    
        This is child (pid:558001)
        This is parent of 558001 (pid:558000)
        This is child (pid:558002)
        child 2 read message from child 1.This is parent of 558001 (pid:558000)
        This is parent of 558002 (pid:558000)
