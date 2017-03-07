//#include </home/sunyongjie/sunyongjie/UNIX_network_programming/source/unpv13e/lib/unp.h>
//#include <time.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

#include <winsock2.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int                 listenfd, connfd;
    struct sockaddr_in  servaddr;
    char                buff[4096];
    time_t              ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);   /* daytime server */
    bind(listenfd, (SOCKADDR *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    for ( ; ; ) {
        connfd = accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

        close(connfd);
    }
}
