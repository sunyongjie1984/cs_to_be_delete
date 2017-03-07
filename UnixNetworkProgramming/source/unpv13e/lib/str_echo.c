#include <iostream>
#include "unp.h"

// 从客户读入数据，并把数据回射给客户
void
str_echo(int sockfd)
{
    ssize_t n;
    char    buf[MAXLINE];

again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0) // 从套接字读入数据
        Writen(sockfd, buf, n);                   // 把其中内容回射给客户。如果客户关闭连接(这是正常情况)，那么接收到客户的FIN将导致服务器子进程的read函数返回0
    // 这又导致str_echo函数的返回，从而在tcpserv01.c中终止子进程。

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");

    std::cout << "exiting str_echo" << std::endl;
}
