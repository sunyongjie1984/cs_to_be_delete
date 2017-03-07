#include    "unp.h"

int
main(int argc, char **argv)
{
    int                 sockfd;
    struct sockaddr_in  servaddr;

    // if (argc != 2)
    //     err_quit("usage: udpcli <IPaddress>");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5150);
    // Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    char recvline[100];
    int n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

    recvline[n] = 0;    /* null terminate */
    Fputs(recvline, stdout);

    exit(0);
}
