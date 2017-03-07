#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


#define closesocket close
#define client_count 100
#define BUFFER_SIZE 8192

struct connection{
    int clientfd;
    int remotefd;
    char clientbuf[BUFFER_SIZE];
    char remotebuf[BUFFER_SIZE];
    int clientbuf_size;
    int remotebuf_size;
} conns[client_count] = {0};

static void remove_client(int i)
{
    shutdown(conns[i].clientfd, SHUT_RD);
    closesocket(conns[i].clientfd);
    shutdown(conns[i].remotefd, SHUT_RD);
    closesocket(conns[i].remotefd);
    conns[i].clientfd = conns[i].remotefd = 0;
}

static int get_client()
{
    int i;
    for( i = 0; i<client_count; i++)
        if(!conns[i].clientfd)
            return i;
    return 0;
}

static int set_nonblocking(int sock)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if(opts < 0)
        return -1;
    opts = opts | O_NONBLOCK;
    if(fcntl(sock, F_SETFL, opts) < 0)
        return(-1);
    return 0;
}

int main(int argc, char **argv)
{
    fd_set fdreads, fdwrites;
    const int buf_size = 1024*32;
    int ret;
    char buf[buf_size];
    int sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    ret = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&ret, sizeof(ret)); //¶Ë¿Ú¸´ÓÃ
    struct sockaddr_in addr = {0};
    struct sockaddr_in remote_addr = {0};
    addr.sin_family = remote_addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons( 1080 );
    remote_addr.sin_addr.s_addr = inet_addr("221.130.162.247");
    remote_addr.sin_port = htons( 80 );
    if( bind( sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in) ) < 0 )
        perror("failed to bind socket");
    listen( sock , 5);
    printf("listening\n");
    for(;;){
        int i, j, k, lastfd=0;
        FD_ZERO(&fdreads);
        FD_ZERO(&fdwrites);
        FD_SET( sock, &fdreads);
        for( i=0; i<client_count; i++)
            if(conns[i].clientfd){
                if( conns[i].clientbuf_size == 0 ){
                    FD_SET( conns[i].clientfd, &fdreads );
                }else{
                    FD_SET( conns[i].remotefd, &fdwrites );
                }
                if( conns[i].remotebuf_size == 0){
                    FD_SET( conns[i].remotefd, &fdreads );
                }else{
                    FD_SET( conns[i].clientfd, &fdwrites );
                }
            }
        ret = select(client_count*2+2, &fdreads, &fdwrites, 0, 0);
        switch(ret){
            case -1:
                perror("error");
                break;
            case 0:
                perror("timeout?");
                break;
            default:
                if(FD_ISSET(sock, &fdreads)){
                    int j = get_client();
                    printf("accept %d\n", j);
                    int len = sizeof(struct sockaddr_in);
                    conns[j].clientfd = accept(sock, 0, 0);
                    conns[j].remotefd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
                    addr.sin_port = htons( 0 );
                    set_nonblocking(conns[j].clientfd);
                    set_nonblocking(conns[j].remotefd);
                    bind( conns[j].remotefd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in) );
                    connect( conns[j].remotefd, (struct sockaddr*)&remote_addr, sizeof(struct sockaddr_in) );
                }
                for( j=0; j<client_count; j++){
                    if(!conns[j].clientfd) continue;
                    if(FD_ISSET(conns[j].clientfd, &fdreads) ){
                        int ret = recv(conns[j].clientfd, conns[j].clientbuf, BUFFER_SIZE, 0);
                        if( ret > 0 )
                            conns[j].clientbuf_size = ret;
                        if( ret <= 0 )
                            remove_client(j);
                    }
                    if(FD_ISSET(conns[j].remotefd, &fdreads) ){
                        int ret = recv(conns[j].remotefd, conns[j].remotebuf, BUFFER_SIZE, 0);
                        if( ret > 0 )
                            conns[j].remotebuf_size = ret;
                        if( ret <= 0 )
                            remove_client(j);
                    }
                    if(FD_ISSET(conns[j].clientfd, &fdwrites) ){
                        int ret = send(conns[j].clientfd, conns[j].remotebuf, conns[j].remotebuf_size, 0);
                        if( ret > 0 )
                            conns[j].remotebuf_size -= ret;
                        if( ret <= 0 )
                            remove_client(j);
                    }
                    if(FD_ISSET(conns[j].remotefd, &fdwrites) ){
                        int ret = send(conns[j].remotefd, conns[j].clientbuf, conns[j].clientbuf_size, 0);
                        if( ret > 0 )
                            conns[j].clientbuf_size -= ret;
                        if( ret <= 0 )
                            remove_client(j);
                    }
                }
        }
    }
    return 0;
}

