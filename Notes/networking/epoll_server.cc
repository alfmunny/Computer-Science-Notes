#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>

int main() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        return -1;
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on));

    int of = fcntl(listenfd, F_GETFL, 0);
    int nf = of | O_NONBLOCK;

    if (fcntl(listenfd, F_SETFL, nf) == -1) {
        perror("set nonblock failed");
        close(listenfd);
        return -1;
    }

    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);

    if (bind(listenfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) == -1) {
        perror("bind failed");
        close(listenfd);
        return -1;
    }

    if (listen(listenfd, SOMAXCONN) == -1) {
        perror("listen failed");
        close(listenfd);
        return -1;
    }

    int epollfd = epoll_create(1);

    if (epollfd == -1)
    {
        perror("epoll_create failed");
        return -1;
    }

    epoll_event listen_fd_event;
    listen_fd_event.data.fd = listenfd;
    listen_fd_event.events = EPOLLIN;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &listen_fd_event) == -1) {
        perror("epoll_ctl EPOLL_CTL_ADD failed");
        return -1;
    }

    int n;
    int MAX_EVENTS = 1024;
    std::cout << "server start ..." << std::endl;
    while (true) {
        epoll_event epoll_events[1024];
        n = epoll_wait(epollfd, epoll_events, MAX_EVENTS, 1000);

        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
        else if (n == 0)  {
            continue;
        }

        for (size_t i = 0; i < n; ++i) {
            if (epoll_events[i].events & EPOLLIN) {
                if (epoll_events[i].data.fd == listenfd) {
                    struct sockaddr_in clientaddr;
                    socklen_t clientaddrlen = sizeof(clientaddr);
                    int clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientaddrlen);

                    if (clientfd != -1) {
                        int of = fcntl(clientfd, F_GETFL, 0);
                        int nf = of | O_NONBLOCK;
                        if (fcntl(clientfd, F_SETFL, nf) == -1) {
                            close(clientfd);
                            continue;
                        }

                        epoll_event client_fd_event;
                        client_fd_event.data.fd = clientfd;
                        client_fd_event.events = EPOLLIN | EPOLLOUT;
                        // Enable or disable this to see the difference
                        client_fd_event.events |= EPOLLET;
                        //
                        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &client_fd_event) != -1) {
                            std::cout << "new client accepted, client fd:" << clientfd << std::endl;
                        }
                        else {
                            std::cout << "add client fd to epollfd failed" << std::endl;
                            close(clientfd);
                        }
                    }
                }
                else {
                    std::cout << "client fd: " << epoll_events[i].data.fd << std::endl;

                    // Only read on char each time
                    // Try LT and ET to see the difference
                    // char ch;

                    // If Edge-Triggered, we should read all data to the buffer;
                    std::stringstream ss;
                    char buf[10];
                    int m = read(epoll_events[i].data.fd, buf, sizeof(buf));
                    ss << buf;

                    if (m == 0) {
                        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, NULL) == -1) {
                            std::cout << "client disconnected, client fd:" << epoll_events[i].data.fd << std::endl;
                        }
                        close(epoll_events[i].data.fd);
                    }
                    else if (m < 0){
                        if (errno != EWOULDBLOCK & errno != EINTR) {
                            if (epoll_ctl(epollfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, NULL) == -1) {
                                std::cout << "client disconnected, client fd:" << epoll_events[i].data.fd << std::endl;
                            }
                            close(epoll_events[i].data.fd);
                            
                        }
                    }
                    else {
                        for (;;) {
                            int n = read(epoll_events[i].data.fd, buf, sizeof(buf));
                            if (n <= 0) {
                                break;
                            }
                            std::cout << buf << std::endl;
                            ss << buf;
                        }
                        std::cout << "recv from client" << epoll_events[i].data.fd << ", message: " << ss.str() << std::endl;
                    }
                }
            }
            else if (epoll_events[i].events & EPOLLOUT) {
                if (epoll_events[i].data.fd != listenfd) {
                    std::cout << "EPOLLOUT triggered, client fd: " << epoll_events[i].data.fd << std::endl;
                }
            }
            else if (epoll_events[i].events & EPOLLERR) {
                perror("EPOLLERR");
            }
        }
    }


    close(listenfd);
    return 0;
}
