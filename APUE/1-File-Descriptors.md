# File Descriptors

## Definition

See `man stdio(3)`

> a small, non-genative integer which identifies a file to the kernel.

- stdin (0, STDIN_FILENO)
- stdout (1, STDOUT_FILENO)
- stderr (2, STDERR_FILENO)

## Limits

There are several ways to get the current limit of max open files in current process.

- OPENMAX
- getconf
	- `getconf OPEN_MAX`
- sysconf
	- `sysconf(_SC_OPEN_MAX)`
- getrlimit
	- `getrlimit(RLIMIT_NOFILE, &rlp)`

Run `openmax.c`

```
OPEN_MAX is defined as 10240.
'getconf OPEN_MAX' says: 256
sysconf(3) says this process can open 256 files.
getrlimit(2) says this process can open 256 files.
Which one is it?

Currently open: fd #0 (inode 1985)
Currently open: fd #1 (inode 1985)
Currently open: fd #2 (inode 1985)
Currently open files: 3
Opened 253 additional files, then failed: Too many open files (24)
```

`ulimit -n` get the current limit in shell.

`ulimit -n 64` set the current limit.

Run `openmax.c` again to check which numbers are affected.

```
OPEN_MAX is defined as 10240.
'getconf OPEN_MAX' says: 64
sysconf(3) says this process can open 64 files.
getrlimit(2) says this process can open 64 files.
Which one is it?

Currently open: fd #0 (inode 1985)
Currently open: fd #1 (inode 1985)
Currently open: fd #2 (inode 1985)
Currently open files: 3
Opened 61 additional files, then failed: Too many open files (24)
```

What is `_POSIX_OPEN_MAX`:

You can have at least `_POSIX_OPEN_MAX` number of files opened in one process.

## Standard I/O
```
open(2)
close(2)
read(2)
write(2)
lseek(2)

```

`create(2)` is same as:
`open(path, O_CREATE | O_TRUNC | O_WRONLY, mode);`

`open(2)`

```
O_RDONLY        open for reading only
O_WRONLY        open for writing only
O_RDWR          open for reading and writing

O_NONBLOCK      do not block on open or for data to become available
O_APPEND        append on each write
O_CREAT         create file if it does not exist
O_TRUNC         truncate size to 0
O_EXCL          error if O_CREAT and the file exists
 ```
		   
		   
`write(2)`
	
`lseek(2)`
	
```
SEEK_SET beginning of the file
SEEK_CUR current file position
SEEK_END end of the file
```
	
 `lseek` can create sparse file by skipping positions in the file. 
 ```c
#define BIGNUM 10240000
if (lseek(fd, BIGNUM, SEEK_CUR) == -1) {
	perror("lseek error");
	return EXIT_FAILURE;
}
 ```
 But the file system must support sparse file. And `copy` a sparse file may also differ on different systems. You can check it with `man copy`.
 
`read(2)` Increasing BUFSIZE infinitely will not boost the performance of reading anymore, because the block size of a file in the file system has its limit. You can use `stat` to get the block size.

```
stat -f "%k" ./lseek.c
```


## File Sharing

`dup` Duplicate a file descriptor which points to the same file table.

```c
dup2(STDOUT_FILENO, STDERR_FILENO)
```

`fcntl` Control file descriptors.


```
if((flags = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) {
	perror("Can't get file descriptor flags");
	exit(EXIT_FAILURE);
}

flags |= O_SYNC;

if(fcntl(STDOUT_FILENO, F_SETFL, flags) < 0) {
	perror("Cant' set file descriptor flags");
}
fcntl(STDOUT_FILENO, F_GETFL, 0)
```

`O_SYNC`: flush I/O on every call. It slows down the performance but make the writing synchronously.

`dev/fd`

```
❯  ls -l /dev/std*
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stderr -> fd/2
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stdin -> fd/0
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stdout -> fd/1
```

We can use `/dev/std*` to catch the stdin, stdout or stderr.

```
❯ echo one > first
❯ echo third > third
❯ echo two | cat first /dev/stdin third
one
two
third
```

