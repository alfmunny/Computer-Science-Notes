# Interprocess Communication II

## socketpair

For bi-directional communication, instead of creating two pipes, we can use `socketpair`.

### Read [socketpair.c](./apue-code/08/socketpair.c)

```c
#define DATA1 "In Xanadu, did Kublai Khan . . ."
#define DATA2 "A stately pleasure dome decree . . ."

int main()
{
	int sockets[2], child;
	char buf[BUFSIZ];

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
		perror("opening stream socket pair");
		exit(1);
	}

	/* Note: Execution order of parent/child is not guaranteed! Hence,
	 * order of data being sent/read is entirely undefined.  Do not
	 * rely on any order, even if you repeatedly observe it to follow
	 * what you perceive as a pattern. */

	if ((child = fork()) == -1)
		perror("fork");
	else if (child) {	/* This is the parent. */
		close(sockets[0]);
		printf("Parent (%d) --> sending: %s\n", getpid(), DATA1);
		if (write(sockets[1], DATA1, sizeof(DATA1)) < 0)
			perror("writing stream message");
		if (read(sockets[1], buf, BUFSIZ) < 0)
			perror("reading stream message");
		printf("Parent (%d) --> reading: %s\n", getpid(), buf);
		close(sockets[1]);
	} else {		/* This is the child. */
		close(sockets[1]);
		printf("Child (%d) --> sending: %s\n", getpid(), DATA2);
		if (write(sockets[0], DATA2, sizeof(DATA2)) < 0)
			perror("writing stream message");
		if (read(sockets[0], buf, BUFSIZ) < 0)
			perror("reading stream message");
		printf("Child (%d) --> reading: %s\n", getpid(), buf);
		close(sockets[0]);
	}
	return 0;
}

```

### Run `socketpair`

```
./socketpair
Child (142510) --> sending: A stately pleasure dome decree . . .
Child (142510) --> reading: In Xanadu, did Kublai Khan . . .
Parent (142508) --> sending: In Xanadu, did Kublai Khan . . .
Parent (142508) --> reading: A stately pleasure dome decree . . .
```

### Question 

- Can you change pipe1.c from our previous segment to allow bi-directional communication using two pipes?

- What happens if you change the type and/or protocol in the socketpair(2) call
 
    SOCK_DGRAM is also working. 

- Can you change socketpair.c to read/write from both ends?
    
    Yes, we can. But we have to mind the order of read and write from parent and child.

- Waht happends if you change the order of the read(2) and write(2) calls in both the parent and child?
    
    It will block forever. Because both read will block, and no one is sending any data to unblock the other one.

## socket

```c
int socket(int domain, int type, int protocol);
```

- domain: selects the address- or name space of the socket, which selects the protocol family
- type: selects the semantics of communication 
- protocol: selects specific rules/formats for this type. In practice, selecting the default protocol by specifying 0 is generally sufficient

Common domains:

| Domain   | Description             |
| -------  | ----------------------- |
| PF_LOCAL | local domain protocols  |
| PF_INET  | ARPA inetnet protocols  |
| PF_INET6 | IPv6 protocols          |


Common types:


| Type        | Description                                                                     |
| -------     | -----------------------------------------------------------                     |
| SOCK_STREAM | sequenced, reliable, two-way connection based byte streams                      |
| SOCK_DGRAM  | connectionless, unreliable messages of a fixed (typically small) maximum length |
| SOCK_RAW    | access to internal network protocols and interfaces                             |

### PF_LOCAL
Read [udgramread.c](./apue-code/09/udgramread.c)

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/*
 * In the included file <sys/un.h> a sockaddr_un is defined as follows
 * struct sockaddr_un {
 *	short	sun_family;
 *	char	sun_path[108];
 * };
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "socket"

/*
 * This program creates a UNIX domain datagram socket, binds a name to it,
 * then reads from the socket.
 */
int main()
{
	int sock;
	struct sockaddr_un name;
	char buf[BUFSIZ];

	if ((sock = socket(PF_LOCAL, SOCK_DGRAM, 0)) < 0) {
		perror("opening datagram socket");
		exit(EXIT_FAILURE);
	}

	name.sun_family = PF_LOCAL;
	(void)strncpy(name.sun_path, NAME, sizeof(name.sun_path));
	if (bind(sock, (struct sockaddr *)&name, sizeof(struct sockaddr_un))) {
		perror("binding name to datagram socket");
		exit(EXIT_FAILURE);
	}
	(void)printf("socket --> %s\n", NAME);

	if (read(sock, buf, BUFSIZ) < 0)
		perror("reading from socket");
	(void)printf("--> %s\n", buf);
	(void)close(sock);

	/* A UNIX domain datagram socket is a 'file'.  If you don't unlink
	 * it, it will remain in the file system. */
	(void)unlink(NAME);
	return EXIT_SUCCESS;
}
```

Read [udpgramread.c](./apue-code/09/udgramsend.c)

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 'Dover Beach' by Matthew Arnold -- look it up. */
#define DATA "The sea is calm tonight, the tide is full . . ."

/*
 * Here I send a datagram to a receiver whose name I get from the command
 * line arguments.  The form of the command line is udgramsend pathname
 */

int
main(int argc, char **argv)
{
	int sock;
	struct sockaddr_un name;

	if (argc != 2) {
		perror("usage: send <socket>");
		exit(EXIT_FAILURE);
	}

	if ((sock = socket(PF_LOCAL, SOCK_DGRAM, 0)) < 0) {
		perror("opening datagram socket");
		exit(EXIT_FAILURE);
	}

	name.sun_family = PF_LOCAL;
	(void)strncpy(name.sun_path, argv[1], sizeof(name.sun_path));

	if (sendto(sock, DATA, sizeof(DATA), 0,
	    (struct sockaddr *)&name, sizeof(struct sockaddr_un)) < 0) {
		perror("sending datagram message");
	}
	(void)close(sock);
	return EXIT_SUCCESS;
}

```

### bind(2)

bind(2) assigns a name to an unnamed socket.

```c
bind(sock, (struct sockaddr *)&name, sizeof(struct sockaddr_un))
```

### send(2) and recv(2)

- send(2): use for socket with a connection 
- sendto(2): use for connectionless socket 

- recv(2): use for socket with a connection 
- recvfrom(2): use for connectionless socket 

### Questions

- Change the program to become a generic "socket cat", a program that reads data from stdin and sends it into the specified socket, one line at a time
- Experiment with the permissions on the socket after the server called bind(2), Confirm or deny that they are honored on different operating systems as well as that binding the socket non orrs your umask.

- Can you have multiple processes using the same socket to send data to a single reader?
- Our example uses sockets of type SOCK_DGRAM; can we use sock_stream or any other type? What happens if the reader uses on type and the sender another?

### PF_INET

dgramread.c

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * In the included file <netinet/in.h> a sockaddr_in is defined as follows:
 * struct sockaddr_in {
 *	short	sin_family;
 *	u_short	sin_port;
 *	struct in_addr sin_addr;
 *	char	sin_zero[8];
 * };
 *
 * This program creates a datagram socket, binds a name to it, then reads
 * from the socket.
 */
int main()
{
	int sock;
	socklen_t length;
	struct sockaddr_in name;
	char buf[BUFSIZ];

	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("opening datagram socket");
		exit(EXIT_FAILURE);
	}

	name.sin_family = PF_INET;
	name.sin_addr.s_addr = INADDR_ANY;
	name.sin_port = 0;
	if (bind(sock, (struct sockaddr *)&name, sizeof(name)) < 0) {
		perror("binding datagram socket");
		exit(EXIT_FAILURE);
	}

	/* Find assigned port value and print it out. */
	length = sizeof(name);
	if (getsockname(sock, (struct sockaddr *)&name, &length) < 0) {
		perror("getting socket name");
		exit(EXIT_FAILURE);
	}
	(void)printf("Socket has port #%d\n", ntohs(name.sin_port));
	if (read(sock, buf, BUFSIZ) < 0)
		perror("receiving datagram packet");
	(void)printf("-->%s\n", buf);
	(void)close(sock);
	return EXIT_SUCCESS;
}

```

dgramsend.c
```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 'Dover Beach' by Matthew Arnold -- look it up. */
#define DATA "The sea is calm tonight, the tide is full . . ."

/*
 * Here I send a datagram to a receiver whose name I get from the command
 * line arguments.  The form of the command line is dgramsend hostname
 * portnumber
 */

int main(int argc, char **argv)
{
	int sock, port;
	struct sockaddr_in name;
	struct hostent *hp;

	if (argc != 3) {
		(void)printf("Usage: %s hostname port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = atoi(argv[2]);
	if ((port < 1) || (port > 65536)) {
		(void)fprintf(stderr, "Invalid port: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("opening datagram socket");
		exit(EXIT_FAILURE);
	}

	/*
	 * Construct name, with no wildcards, of the socket to send to.
	 * getnostbyname() returns a structure including the network address
	 * of the specified host.  The port number is taken from the command
	 * line.
	 */
	if ((hp = gethostbyname(argv[1])) == 0) {
		(void)fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	bcopy(hp->h_addr, &name.sin_addr, hp->h_length);
	name.sin_family = PF_INET;
	name.sin_port = htons(port);

	if (sendto(sock, DATA, sizeof(DATA), 0,
	    (struct sockaddr *)&name, sizeof(name)) < 0) {
		perror("sending datagram message");
	}
	(void)close(sock);
	return EXIT_SUCCESS;
}

```

Start `read`
```bash
./read
Socket has port #42236
```

Start `send`

```bash
./send serenity-02 35904
```

```bash
sudo tcpdump -X -n host serenity-02 -i lo
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on lo, link-type EN10MB (Ethernet), capture size 262144 bytes
15:43:49.590351 IP 127.0.0.1.35904 > 127.0.1.1.42236: UDP, length 48
        0x0000:  4500 004c 828f 4000 4011 b90f 7f00 0001  E..L..@.@.......
        0x0010:  7f00 0101 8c40 a4fc 0038 ff4b 5468 6520  .....@...8.KThe.
        0x0020:  7365 6120 6973 2063 616c 6d20 746f 6e69  sea.is.calm.toni
        0x0030:  6768 742c 2074 6865 2074 6964 6520 6973  ght,.the.tide.is
        0x0040:  2066 756c 6c20 2e20 2e20 2e00            .full.......

```

We can decode the message with "printf"

```bash
# source address
printf  "%d.%d.%d.%d\n" 0x7f 0x00 0x00 0x01
127.0.0.1

# destination address
printf  "%d.%d.%d.%d\n" 0x7f 0x00 0x01 0x01
127.0.1.1

# source port
printf  "%d\n" 0x8c40
35904

# destination port
printf  "%d\n" 0xa4fc
42236

# the actual message
printf "%x54\x68\x65\x20\n"
The
```

### recap

- The local machine address for a socket can be any valid network address of the machine, or it can be the wildcard value INADDR_ANY
- request any ephemeral port by calling bind(2) with a port number of 0
- convert between network byte order and host byte order using htons(3) and ntohs(3)
- determine used port number using getsockname(2)

