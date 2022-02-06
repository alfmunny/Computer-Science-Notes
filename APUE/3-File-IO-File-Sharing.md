# File IO and File Descriptors

## File Descriptors

> a small, non-negative integer which identifies a file to the kernel. -- `man stdio(3)`

Every process has it's local file descriptors in a process table. 
They will point the files in the file table of the kernel.

- stdin (0, STDIN_FILENO)
- stdout (1, STDOUT_FILENO)
- stderr (2, STDERR_FILENO)

![File table](Pasted%20image%2020220205202006.png)

## Limits

There are several ways to get the current limit of max open files in current process.

- OPENMAX
- getconf
	- `getconf OPEN_MAX`
- sysconf
	- `sysconf(_SC_OPEN_MAX)`
- getrlimit
	- `getrlimit(RLIMIT_NOFILE, &rlp)`

Run [openmax.c](./apue-code/02/openmax.c)

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

`creat(2)` is same as:
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
O_EXCL          error if O_CREATE and the file exists
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

### Atomic Operations

> What if another process did write to the same file using lseek(fd, 0, SEEK_END)?

`lseek` and then `write` is not an atomic operation. It can be interrupted after `lseek`, and therefore `write` may happen after the file has been changed. It will write from the same offset using the original file size, and overwrite the data which the other file has already written.

`O_APPEND` will solve the case for writing to the end. It's atomic.

`pread` and `pwrite` can write to any offset atomically, it will seek first and then write.

```
ssize_t pread(int fd, void *buf, size_t num, off_t offset);
ssize_t pwrite(int fd, void *buf, size_t num, off_t offset);
```

Shell examples `O_APPEND`

```bash
# Suppose we have already created a `file`.
ls -l file /nowhere /does-not-exist 
ls: /does-not-exist: No such file or directory
ls: /nowhere: No such file or directory
-rw-r--r--  1 alfmunny  staff  138  5 Feb 23:25 file

ls -l /nowhere /does-not-exist file 
ls: /does-not-exist: No such file or directory
ls: /nowhere: No such file or directory
-rw-r--r--  1 alfmunny  staff  138  5 Feb 23:25 file
```

> Why `stderr` is always prior to `stdout`? 

Because `stderr` is unbuffered, and `stdout` is buffered. 
Please see [manual](https://linux.die.net/man/3/stderr).


Test `>` and `>>` in shell

`>` means write to file with `O_TRUNC`.
`>>` means write to file with `O_APPEND`

```bash
ls -l file /nowhere /does-not-exist >file 2>file
cat file
# stdout overwrites stderr, because they both write with O_TRUNC
-rw-r--r--  1 alfmunny  staff  0  5 Feb 23:23 file
/nowhere: No such file or directory

ls -l file /nowhere /does-not-exist >file 2>>file
cat file
# stdout overwrites stderr, because stderr write first with O_APPEND, and then stdout write with O_TRUNC.
-rw-r--r--  1 alfmunny  staff  0  5 Feb 23:24 file
/nowhere: No such file or directory

ls -l file /nowhere /does-not-exist >>file 2>file
cat file
# All good now.
ls: /does-not-exist: No such file or directory
ls: /nowhere: No such file or directory
-rw-r--r--  1 alfmunny  staff  0  5 Feb 23:25 file

# There is a better ways to let stderr always go to where the stdout is
ls -l file /nowhere /does-not-exist >file 2>&1
cat file
ls: /does-not-exist: No such file or directory
ls: /nowhere: No such file or directory
-rw-r--r--  1 alfmunny  staff  0  5 Feb 23:40 file
```

### Duplicate

> How do we open whatever stdout is?

`dup` Duplicate a file descriptor which points to the same file table.

`redir.c`
```c
void
writeBoth(const char *mark) {
	int len, marklen;

	marklen = strlen(mark);
	if (write(STDOUT_FILENO, mark, marklen) != marklen) {
		perror("unable to write marker to stdout");
		exit(EXIT_FAILURE);
	}

	len = strlen(STDOUT_MSG);
	if (write(STDOUT_FILENO, STDOUT_MSG, len) != len) {
		perror("unable to write to stdout");
		exit(EXIT_FAILURE);
	}

	if (write(STDERR_FILENO, STDERR_MSG, len) != len) {
		perror("unable to write to stdout");
		exit(EXIT_FAILURE);
	}
}

int
main() {
	writeBoth("before dup2\n");

	if (dup2(STDOUT_FILENO, STDERR_FILENO) < 0) {
		perror("Unable to redirect stderr to stdout");
		exit(EXIT_FAILURE);
	}

	writeBoth("after dup2\n");
}
```

### Shell examples for dup2

```bash
./apue-code/02/redir.out 
before dup2
A message to stdout.
A message to stderr.
after dup2
A message to stdout.
A message to stderr.

# stderr goes to wherever stdout is after dup2
./apue-code/02/redir.out 2>/dev/null
before dup2
A message to stdout.
after dup2
A message to stdout.
A message to stderr.

./apue-code/02/redir.out >file
A message to stderr.
cat file
before dup2
A message to stdout.
after dup2
A message to stdout.
A message to stderr.
```
### `fcntl` Control file descriptors.

```c
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

`O_SYNC`: flush I/O to disk on every call. It slows down the performance but make the writing synchronously.

Shell examples for `O_SYNC`.

```bash
# create a 10MB file
dd if=/dev/zero of=file bs=$((1024 * 1024)) count=10
10+0 records in
10+0 records out
10485760 bytes transferred in 0.001990 secs (5269014629 bytes/sec)

du -h file
10.0M	file

# with O_SYNC
time ./apue-code/02/sync-cat.out <file >out
real	0m0.461s
user	0m0.004s
sys	0m0.205s

# comment out O_SYNC
time ./apue-code/02/sync-cat.out <file >out
real	0m0.041s
user	0m0.003s
sys	0m0.033s
```

With `O_SYNC` we have huge performance penalty, but it guarantee its writing flushed to disk synchronously.


`dev/fd`

```bash
ls -l /dev/std*
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stderr -> fd/2
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stdin -> fd/0
lr-xr-xr-x  1 root  wheel  0 Sep 25 13:13 /dev/stdout -> fd/1
```

We can use `/dev/std*` to catch the stdin, stdout or stderr.

```bash
echo one > first
echo third > third
echo two | cat first /dev/stdin third # here stdin reads from pipe
one
two
third
```
