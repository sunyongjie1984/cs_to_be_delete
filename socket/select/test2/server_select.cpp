#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int MYPORT   = 1234;  // the port users will be connecting to
const int BACKLOG  = 5;     // how many pending connections queue will hold
const int BUF_SIZE = 200;

int fd_A[BACKLOG];          // accepted connection fd
int conn_amount;            // current connection amount

void show_client()
{
    printf("client amount: %d\n", conn_amount);
    for (int i = 0; i < BACKLOG; i++)
    {
        printf("[%d]:%d  ", i, fd_A[i]);
    }
    printf("\n\n");
}

int main(void)
{
    int sock_fd;  // listen on sock_fd, new connection on new_fd
    int new_fd;
    struct sockaddr_in server_addr; // server address information
    struct sockaddr_in client_addr; // connector's address information
    socklen_t sin_size;
    int yes = 1;
    int ret;
    int i;
    char buf[BUF_SIZE];

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    server_addr.sin_family      = AF_INET;       // host byte order
    server_addr.sin_port        = htons(MYPORT); // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY;    // automatically fill with my IP
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    printf("listen port %d\n", MYPORT);
    fflush(stdout); // 立即刷新缓冲区，不然我在后台运行这个程序并且将标准输出打到文件中时即
                    // ./main > tmp & 时，如果我kill掉这个进程，则tmp文件中就不会有这句话

    fd_set fdsr;
    int maxsock;
    struct timeval tv;

    conn_amount = 0;
    sin_size = sizeof(client_addr);
    maxsock  = sock_fd;
    printf("max sock: %d\n", maxsock);
    while (1)
    {
        // initialize file descriptor set
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);

        // timeout setting
        tv.tv_sec = 30;
        tv.tv_usec = 0;

        // add active connection to fd set
        for (i = 0; i < BACKLOG; i++)
        {
            if (0 != fd_A[i])
            {
                FD_SET(fd_A[i], &fdsr);
            }
        }

        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
        if (ret < 0)
        {
            perror("select");
            break;
        }
        else if (ret == 0)
        {
            printf("timeout\n");
            continue;
        }

        // check every fd in the set
        for (i = 0; i < conn_amount; i++)
        {
            if (FD_ISSET(fd_A[i], &fdsr))
            {
                ret = recv(fd_A[i], buf, sizeof(buf), 0);
                if (ret <= 0)
                {        // client close
                    printf("client[%d] close\n", i);
                    close(fd_A[i]);
                    FD_CLR(fd_A[i], &fdsr);
                    fd_A[i] = 0;
                }
                else
                {        // receive data
                    if (ret < BUF_SIZE)
                    {
                        memset(&buf[ret], '\0', 1);
                    }
                    printf("client[%d] send:%s\n", i, buf);
                }
            }
        }

        // check whether a new connection comes
        if (FD_ISSET(sock_fd, &fdsr))
        {
            new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
            if (new_fd <= 0)
            {
                perror("accept");
                continue;
            }

            // add to fd queue
            if (conn_amount < BACKLOG)
            {
                fd_A[conn_amount++] = new_fd;
                printf("new connection client[%d] %s:%d\n", conn_amount,
                        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if (new_fd > maxsock)
                    maxsock = new_fd;
            }
            else
            {
                printf("max connections arrive, exit\n");
                send(new_fd, "bye sunyongjie", 15, 0);
                close(new_fd);
                break;
            }
        }
        show_client();
    }

    // close other connections
    for (i = 0; i < BACKLOG; i++)
    {
        if (fd_A[i] != 0)
        {
            close(fd_A[i]);
        }
    }

    exit(0);
}
