#include "socket.h"

int listener(int * listen_fd, unsigned int listen_port)
{
    *listen_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (-1 == *listen_fd)
    {
        printf("init socket failed\n");
        return -1;
    }

    struct sockaddr_in server_addr;

    unsigned int sin_size = sizeof(struct sockaddr);

    server_addr.sin_family      = PF_INET;
    server_addr.sin_port        = htons(listen_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server_addr.sin_zero), 0);

    int ret = bind(*listen_fd,
                   (struct sockaddr *)&server_addr,
                   sin_size);

    if (-1 == ret)
    {
        printf("bind failed\n");
        return -1;
    }

    ret = listen(*listen_fd, LISTEN_QUEUE);

    if (-1 == ret)
    {
        printf("listen failed\n");
        return -1;
    }

    return 0;
}

int accepter(int listen_fd, function_type response)
{
    int accept_fd = 0;

    struct sockaddr_in client_addr;

    unsigned int sin_size = sizeof(struct sockaddr_in);

    while (true)
    {
        accept_fd = accept(listen_fd,
                           (struct sockaddr *)&client_addr,
                           &sin_size);

        if (-1 == accept_fd)
        {
            printf("accept failed!");
            continue;
        }

        response(&accept_fd);
    }
    return 0;
}

int connecter(int * connect_fd, unsigned int connect_port, const char * svc_addr)
{
    *connect_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (-1 == *connect_fd)
    {
        printf("init socket failed\n");
        return -1;
    }

    struct sockaddr_in client_addr;

    client_addr.sin_family = PF_INET;
    client_addr.sin_port   = htons(connect_port);
    inet_aton(svc_addr, &(client_addr.sin_addr));

    bzero(&(client_addr.sin_zero),0);

    unsigned int sin_size = sizeof(struct sockaddr);

    int ret = connect(*connect_fd,
                      (struct sockaddr *)&client_addr,
                      sin_size);

    if (-1 == ret)
    {
        printf("connect failed\n");
        return -1;
    }

    return 0;
}

int send_n(int fd, const char * buf, size_t n)
{
    size_t buf_size = n;
    ssize_t written_size;

    const char * p = buf;

    while (buf_size > 0)
    {
        written_size = write(fd, p, buf_size);

        if (written_size <= 0)
        {
            if (errno = EINTR)
            {
                printf("------------written_size %d\n", written_size);
                written_size = 0;
            }
            else
            {
                printf("send failed\n");
                return -1;
            }
        }
        buf_size -= written_size;

        p += written_size;
    }
    return 0;
}

int recv_n(int fd, char * buf, size_t n)
{
    size_t buf_size = n;
    ssize_t read_size;

    char * p = buf;

    while (buf_size > 0)
    {
        read_size = read(fd, p, buf_size);

        if (read_size <= 0)
        {
            if (errno = EINTR)
            {
                printf("------------read_size %d\n", read_size);
                read_size = 0;
            }
            else
            {
                printf("send failed\n");
                return -1;
            }
        }
        buf_size -= read_size;

        p += read_size;
    }
    return 0;
}

