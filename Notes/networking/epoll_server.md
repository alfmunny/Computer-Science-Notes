[Basic usage in snippets](./epoll_server.cc)

- socket for listen and socket for accept is not the same one

Compile and run

```shell
g++ epoll_server.cc -o epoll_server
./epoll_server
```

Connect to server

```shell
nc -v 127.0.0.1 3000
```

Try Edge-Triggered and Level-Triggered in source code 
and see the difference by sending the characters
