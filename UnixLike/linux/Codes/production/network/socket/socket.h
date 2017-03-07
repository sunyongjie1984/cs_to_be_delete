#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "../../include/publicpact.h"

#ifdef _LINUX_

#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#endif//_LINUX_

#define LISTEN_QUEUE 1024

typedef int (* function_type)(void * p);

extern int listener(int * listen_fd, unsigned int listen_port);
extern int accepter(int listen_fd, function_type response);
extern int connecter(int * connect_fd, unsigned int connect_port, const char * svc_addr);
extern int send_n(int fd, const char * buf, size_t n);
extern int recv_n(int fd, char * buf, size_t n);

#endif//_SOCKET_H_

