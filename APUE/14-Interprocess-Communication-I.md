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
