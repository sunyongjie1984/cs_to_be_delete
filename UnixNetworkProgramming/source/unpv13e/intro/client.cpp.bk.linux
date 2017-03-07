// #include "unp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>

#include <iostream>

#define MAXLINE     4096    /* max text line length */
#define SA  struct sockaddr
int main(int argc, char ** argv)
{
    int                 sockfd;
    int                 n;
    char                recvline[MAXLINE + 1];
    struct sockaddr_in  servaddr;

    if (argc != 2)
    {
        std::cout << "usage: a.out <IPaddress>" << std::endl;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "socket error" << std::endl;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13); // daytime server
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        std::cout << "inet_pton error for" << argv[1] << std::endl;
    }

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "connect error" << std::endl;
    }

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
