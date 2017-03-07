#include "../lib/unp.h"
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* include Socket */
int
Socket(int family, int type, int protocol)
{
    int     n;

    if ( (n = socket(family, type, protocol)) < 0)
        printf("socket error");
    return(n);
}
/* include Listen */
void
Listen(int fd, int backlog)
{
    char    *ptr;

        /*4can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        printf("listen error");
}

void
Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        printf("bind error");
}

int
Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int     n;

again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef  EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif
            goto again;
        else
            printf("accept error");
    }
    return(n);
}

void
Write(int fd, void *ptr, size_t nbytes)
{                                 // without(signed int), there would be a warning.
    if (write(fd, ptr, nbytes) != (signed int)nbytes)
        printf("write error");
}

void
Close(int fd)
{
    if (close(fd) == -1)
        printf("close error");
}

int main(int argc, char **argv)
{
    int                 listenfd, connfd;
    struct sockaddr_in  servaddr;
    char                buff[MAXLINE];
    time_t              ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);   /* daytime server */
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for ( ; ; ) {
        connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
}
