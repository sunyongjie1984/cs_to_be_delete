#include <iostream>
#include "unp.h"

int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd); /* do it all */

    std::cout << "exiting tcpcli01 main" << std::endl;
    // when a program is exiting, part of this action is that 
    // the kernal will close all descriptors opened,
    // including all the sockets.
    // 1, the client tcp(this program) will send FIN to server(tcpserv),
    // 2, the server tcp send ack to respond, then the server socket will be in CLOSE_WAIT status
    //    客户端套结字则处于FIN_WAIT_2状态
    // 3, 当服务器TCP接收FIN时，服务器子进程阻塞于readline调用，于是readline返回0，这导致
    //    str_echo函数返回服务器子进程的main函数
    // 4，服务器子进程调用exit来终止。服务器子进程中打开的所有描述符随之关闭，这会导致TCP连接终止序列
    //    的最后两个分节：一个从服务器到客户的FIN，和，一个从客户到服务器的ACK，至此，
    //    连接完全终止，客户套结字进入TIME_WAIT状态。
    // 
    // so the server will detect that this client is closing.
    exit(0);
}
