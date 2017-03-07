#include <iostream>
#include "unp.h"
#include <time.h>

struct book {
    int i;
};

int main(int argc, char ** argv)
{
    // c语言自定类型定义对象的时候必须要加struct这个关键字！服了！
    struct book a;
    std::cout << a.i << std::endl; // without this line, there would be a warning

    int    listenfd;
    int    connfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr; // 它将存放客户的协议地址
    socklen_t          len;
    char   buff[MAXLINE];
    time_t ticks;

    // TCP套接字的创建
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 通过填写一个网际套接字地址结构并调用bind函数，服务器的众所周知端口（对于
    // 时间服务器是13）被捆绑到所创建的套接字。我们指定IP地址为INADDR_ANY，这样
    // 要是服务器主机有多个网络接口，服务器进程就可以在任意网络接口上接受客户连接
    // 以后我们将了解怎样限定服务器进程只在单个网络接口上接受客户连接。
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);   // daytime server

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // 调用listen函数把该套接字换成一个监听套接字，这样来自客户的外来连接就可在该
    // 套接字上由内核接受。socket,bind,listen这3个调用步骤是任何TCP服务器准备所谓
    // 的监听描述符(listening descriptor,本例中为listenfd)的正常步骤
    // LISTENQ指定系统内核允许在这个监听描述符上排队的最大客户接连数。
    Listen(listenfd, LISTENQ);

    // 接受客户连接，发送应答
    // 通常情况下，服务器进程在accept调用中被投入睡眠，等待某个客户连接的到达并
    // 被内核接受。TCP连接使用所谓的三路握手(three-way handshake)来建立连接。
    // 握手完毕时accept函数返回，其返回值是一个称为已连接描述符(connected
    // descriptor)的新描述符(本例中为connfd)。该描述符用于与新连接的那个客户通信
    // accept为每个连接到本服务器的客户返回一个新描述符。
    for ( ; ; )
    {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &len);
        printf("connection from %s, port %d\n",
                Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
                ntohs(cliaddr.sin_port));


        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        // 服务器调用close关闭与客户的连接。该调用引发正常的TCP连接终止序列
        Close(connfd);
    }
}
