#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Define bzero() as a macro if it's not in standard C library. */
#ifndef HAVE_BZERO
#define bzero(ptr,n)        memset(ptr, 0, n)
#endif

unsigned int const MAXLINE = 4096; // max text line length

int main(int argc, char ** argv)
{
    int         sockfd;
    int         n;
    char        recvline[MAXLINE + 1];
    sockaddr_in servaddr;

    if (argc != 2)
    {
        std::cout << "usage: a.out <IPaddress>" << std::endl;
    }                          // 也就是IP？  // 也就是TCP?
    // socket函数创建了一个网际(AF_INET)字节流(SOCK_STREAM)套接字，
    // 它是TCP套接字的花哨名字，
    // 该函数返回一个小整数描述符，以后的所有函数调用
    // （如随后的connect和read）就用该描述符来标识这个套接字。
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "socket error" << std::endl;
    }
    // 我们把服务器的IP地址和端口号填入一个网际套接字地址结构（一
    // 个名为servaddr的sockaddr_in结构变量）。使用bzero把整个结构
    // 清零后，置地址族为AF_INET,端口号为13（这是时间获取服务器的众所周知
    // 端口，支持该服务的任何TCP/IP主机都使用这个端口号）。IP地址为第一个
    // 命令行参数的值(argv[1])。网际套接字地址结构中IP地址和端口号这两个成员
    // 必须使用特定格式，为此我们调用库函数htons（主机到网络短整数）去转换
    // 二进制端口号，又调用库函数inet_pton(呈现形式到数值）去把ASCII命令行参数
    // (比如206.168.112.96)转换为合适的格式
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13); // daytime server
    // inet_pton把ASCII点分十进制数串变换成正确的格式
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        std::cout << "inet_pton error for" << argv[1] << std::endl;
    }

    // connect函数应用于一个TCP套接字时，将与它的第二个参数指向的套接字地址结构
    // 指定的服务器建立一个TCP连接。该套接字的地址长度也必须作为该函数的第三个
    // 参数指定，对于网际套接字结构，我们总是使用C语言的sizeof操作符由编译器来计算
    // 这个长度。
    if (connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "connect error" << std::endl;
    }

    // 我们使用read函数读取服务器的应答，并用标准的I/O函数输出结果，TCP是一个没有记录
    // 边界的字节流协议，服务器的应答通常是以\r\n结尾的字符串，\r为回车符\n为换行符。
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; // null terminate
        if (fputs(recvline, stdout) == EOF)
        {
            std::cout << "fputs error" << std::endl;
        }
    }
    if (n < 0)
    {
        std::cout << "read error" << std::endl;
    }

    exit(0);
}
