# Advanced Programming in the Unix Environment

## Resources

- [Book](https://www.amazon.de/Programming-Environment-Addison-Wesley-Professional-Computing/dp/0321637739)
- [Course](https://stevens.netmeister.org/631/)
- [Videos](https://www.youtube.com/playlist?list=PL0qfF8MrJ-jxMfirAdxDs9zIiBg2Wug0z)

## Learning Process

### Week 1

Notes:
- [ ] [1. Introduction, Unix History, Basics](1-Introduction-Unix-History.md)
- [ ] [2. Basics](2-Basics.md)

Reading:

- [ ] [Unix history and basic features](./reading/02-unix-2.pdf)

Homework:

- [X] [Warmup exercise](https://stevens.netmeister.org/631/fixme-exercise.html)
    - [welcome.c](./homework/hw1/welcome.c)
- [ ] [Compare Code Exercise](https://stevens.netmeister.org/631/compare-code-exercise.html)

Resources:

- [src/bin code of NetBSD](http://cvsweb.netbsd.org/bsdweb.cgi/src/bin/)
- [coreutils code of Linux](https://ftp.gnu.org/gnu/coreutils/)

### Week 2

Notes:
- [X] [3. File Descriptors, File IO, File Sharing](./3-File-Descriptor-File-IO-File-Sharing.md)

Reading:
- [X] Videos
- [ ] APUE: Chapter 3

Slides: [fds.pdf](./slides/02-fds.pdf),  [open-close.pdf](./slides/02-open-close.pdf), [read-write-lseek](./slides/02-read-write-lseek.pdf), [file-sharing](./slides/02-file-sharing.pdf)

Homework:

- [X] [File Descriptors Warmup Exercise](https://stevens.netmeister.org/631/fd-exercise.html)
    - [Notes](./homework/lecture02/README.md)
    - [Code](./homework/lecture02/print-fileno.c)

- [ ] [Implement `bbcp`](./homework/bbcp.1.pdf), [Hints](https://stevens.netmeister.org/631/f21-hw1.html)


### Week 3

Notes:
- [ ] [File and Directories](4-File-and-Directories.md)

### Week 4

### Week 5

### Week 6

Notes: 
- [ ] [Process Environment](7-Process-Environment.md)
- [ ] [Process Control](8-Process-Control.md)

### Week 7 

### Week 8 

Notes:
- [X] [Interprocess Communication I](14-Interprocess-Communication-I.md)

Homework:
- [ ] [Implement 'command(3)'](https://stevens.netmeister.org/631/f21-hw2.html)

Resources:

- [ ] [Beej's Guid to Unix IPC](https://beej.us/guide/bgipc/html/single/bgipc.html)
- [ ] [Shared Memory Introduction](https://web.archive.org/web/20160507131726/http://www.kohala.com/start/unpv22e/unpv22e.chap12.pdf)
- [ ] [Semaphores in Linux](https://web.archive.org/web/20180316204322/http://www.linuxdevcenter.com/pub/a/linux/2007/05/24/semaphores-in-linux.html)
- [ ] [Interprocess communication using POSIX message queues in Linux](https://www.softprayog.in/programming/interprocess-communication-using-posix-message-queues-in-linux)

Checkpoint:

- Provide three examples of IPC that allows for asynchronous communication between unrelated processes.
- What is an advantage of using Shared Memory over a pipe? What's a disadvantage?
- What is an advantage of using Message Queues over Shared Memory? What's a disadvantage?
- What's the difference between a FIFO and a pipe?
- popen(3) makes it easy to set up IPC with a new process. What is a risk in using this library function?


### Week 9 Interprocess Communication II

Notes:
- [X] [Interprocess Communication II](14-Interprocess-Communication-II.md)

### Week 10 Daemon Processes
### Week 11 Shared Libraries
### Week 12 Advanced I/O
### Week 13 Containers
