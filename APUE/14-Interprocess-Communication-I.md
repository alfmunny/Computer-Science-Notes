# Interprocess Communication I 

## Means of Interprocess Communications

- two processes reading from/writing to a file on a shared 
- Signals
- Semaphores
- Shared Memory
- Message Queues
- Pipes
- Fifos
- Socketpairs
- Sockets

## System V IPC

What is a [System V](https://en.wikipedia.org/wiki/UNIX_System_V)

### Semaphores

Please see [semdemo.c](./apue-code/08/semdemo.c).

Run two processes to check the locking.

```bash
ipcs -s # get ipc information, -s for semaphores

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x2a030ab0 0          alfmunny   666        1         

ipcrm -s 0 # remove semaphores

ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     

```

### Shared Memory

Fastest IPC. It avoids calling into kernal space.

Read and run [shmdemo.c](./apue-code/08/shmdemo.c)

```bash
./a.out "The cow says 'moo'"
75621: writing to segment: "The cow says 'moo'"

# It will retrieve information for shared memory
./a.out 
76076: segment contains: "The cow says 'moo'"

ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x2a030ab1 2          alfmunny   666        1024       0                       

ipcs -mi 2 

Shared memory Segment shmid=2
uid=1000	gid=1000	cuid=1000	cgid=1000
mode=0666	access_perms=0666
bytes=1024	lpid=75621	cpid=75294	nattch=0
att_time=Thu Feb 10 00:00:22 2022  
det_time=Thu Feb 10 00:00:22 2022  
change_time=Wed Feb  9 23:58:33 2022  

# delete the segement
ipcrm -m 2

ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

```

### Message Queue

- linked list of messages stored in kernel space
- create or open existing queue using msgget(2)
- add message at end of queue using msgsnd(2)
- receive messages from queue using msgrcv(2)
- control queue properties using msgctl(2)

The message itself is contained in a user-defined structure such asynchronous

```c
struct mymsg {
    long mtype      /* message type */
    char mtext[512] /* body of message */
}
```

Read [msgsend.c](./apue-code/08/msgsend.c) and [msgrecv.c](./apue-code/08/msgrecv.c)

`msgsend.c`

Create message queue
```c
// 0644 grants owner read and write, group read and others read permission
if ((msqid = msgget(key, IPC_CREAT | 0644)) < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
}
```

Send message 

```c
sbuf.mtype = 1;

(void)strncpy(sbuf.mtext, argv[2], MSGSZ);

len = strlen(sbuf.mtext) + 1;

// IPC_NOWAIT will return with ERROR immediately if insufficient space
if (msgsnd(msqid, &sbuf, len, IPC_NOWAIT) < 0) {
    (void)fprintf (stderr, "%d, %ld, %s, %d\n",
            msqid, sbuf.mtype, sbuf.mtext, (int)len);
    perror("msgsnd");
    exit(EXIT_FAILURE);
}
```

Receive message

```c
if ((msqid = msgget(key, 0)) < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
}

if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
}
```

Run `msgsend`

```bash
./msgsend 1 "hello alfmunny!"

ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x00000001 0          alfmunny   644        16           1           


./msgsend 1 "byebye!"

ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x00000001 0          alfmunny   644        24           2           

./msgrecv 1
hello alfmunny!

./msgrecv 2
msgget: No such file or directory

./msgrecv 1
byebye!

./msgrecv 1 # will block to wait on the message
```

### Recap

- asynchronous IPC between processes on the same system
- old, but not obsolete
- semaphores are useful to guard access to shared resources
- shared memory allows fast IPC
- message queues as a service are a popular way to implement "pub sub" models

## Pipes and FIFOs

### Pipes

Run [pipe1.c](./apue-code/08/pipe1.c) in terminal:

```bash
./a.out
P=> Parent process with pid 104006 (and its ppid 72664).
P=> Sending a message to the child process (pid 104007).
C=> Child process with pid 104007 (and its ppid 104006).
C=> Reading a message from the parent (pid 104006):
Hello child!  I'm your parent, pid 104006!
```
- Child will wait for parent to write.
- Parent will wait for child to exit.
- `write` is not buffered. `printf` is buffered.
- If the stdout is connected to the terminal, it is then line buffered.
- So every time a new line character `\n` is encountered, the `printf` will flush the data to the screen.

But if it is connected the a pipe, it will use it's full stdout buffer size, and flush at last.

```bash
./a.out | cat
Hello child!  I'm your parent, pid 103802!
C=> Child process with pid 103803 (and its ppid 103802).
C=> Reading a message from the parent (pid 103802):
P=> Parent process with pid 103802 (and its ppid 103801).
P=> Sending a message to the child process (pid 103803).
```

[What is `line buffere`, `fully buffered` and `unbufered`?](https://stackoverflow.com/questions/36573074/what-do-fully-buffered-line-buffered-and-unbuffered-mean-in-c)

> When a stream is unbuffered, characters are intended to appear from the source or at the destination as soon as possible. Otherwise characters may be accumulated and transmitted to or from the host environment as a block. When a stream is fully buffered, characters are intended to be transmitted to or from the host environment as a block when a buffer is filled. When a stream is line buffered, characters are intended to be transmitted to or from the host environment as a block when a new-line character is encountered. Furthermore, characters are intended to be transmitted as a block to the host environment when a buffer is filled, when input is requested on an unbuffered stream, or when input is requested on a line buffered stream that requires the transmission of characters from the host environment. Support for these characteristics is implementation-defined, and may be affected via the setbuf and setvbuf functions.


`popen` pipe stream to or from a process.

Read [popen.c](./apue-code/08/popen.c)

The command will be passed to /usr/sh with -c. It can run any commands. Because this vunalibity, it is a good practice to use `popenve` instead of`popen`.


### FIFOs

`mkfifo` create named pipe

### `tee` exmaple

`tee` can read from stdin and write to stdout and multiple files.

Prepare a `log.txt`.

```
cat log.txt
200 OK
200 OK
404 NOT OK
200 OK
200 OK
200 OK
404 NOT OK
200 OK
200 OK
200 OK
404 NOT OK
200 OK
200 OK
200 OK
404 NOT OK
```

```bash
mkfifo fifo
ls -l fifo
prw-rw-r-- 1 alfmunny alfmunny 0 Feb 15 15:36 fifo
grep "200" fifo > ok &
ps
    PID TTY          TIME CMD
  51972 pts/3    00:00:06 zsh
  51989 pts/3    00:00:00 zsh
  52260 pts/3    00:00:19 gitstatusd-linu
 102031 pts/3    00:04:04 vim
 111469 pts/3    00:00:00 sh
 111470 pts/3    00:00:00 ps
cat log.txt | tee fifo | grep -v "200" > not-ok

diff ok not-ok
1,11c1,4
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
< 200 OK
---
> 404 NOT OK
> 404 NOT OK
> 404 NOT OK
> 404 NOT OK

wc -lc *ok
  4  44 not-ok
 11  77 ok
 15 121 total
```

### Recap

pipe(2) and FIFOs

- Basis of the Unix Philosophy of building filters and operating on text streams
- pipes require a common ancesotr, FIFOs do not
- data wriiten into a pipe is no longer line buffered.

Behavior after closing one end

- read(2) from a pipe whose write end has been closed returns 0 after all data has been read
- write(2) to a pipe whose read end has been closed generates SIGPIPE; if caught or ignored, write(2) returns an error and sets errno to EPIPE.
