#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 255
int main(int argc, char **argv)
{
    struct sockaddr_in peeraddr, myaddr;

    int sockfd;
    char recmsg[BUFLEN + 1];
    unsigned int socklen;

    /* ´´½¨ socket ÓÃÓÚUDPÍ¨Ñ¶ */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("socket creating error/n");
        exit(1);
    }
    socklen = sizeof(struct sockaddr_in);

    /* ÉèÖÃ¶Ô·½µÄ¶Ë¿ÚºÍIPÐÅÏ¢ */
    memset(&peeraddr, 0, socklen);
    peeraddr.sin_family = AF_INET;
    if (argv[2])
        peeraddr.sin_port = htons(atoi(argv[2]));
    else
        peeraddr.sin_port = htons(7838);
    if (argv[1]) {
        /* ×¢ÒâÕâÀïÉèÖÃµÄ¶Ô·½µØÖ·ÊÇÖ¸×é²¥µØÖ·£¬¶ø²»ÊÇ¶Ô·½µÄÊµ¼ÊIPµØÖ· */
        if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0) {
            printf("wrong group address!/n");
            exit(0);
        }
    } else {
        printf("no group address!/n");
        exit(0);
    }

    /* ÉèÖÃ×Ô¼ºµÄ¶Ë¿ÚºÍIPÐÅÏ¢ */
    memset(&myaddr, 0, socklen);
    myaddr.sin_family = AF_INET;
    if (argv[4])
        myaddr.sin_port = htons(atoi(argv[4]));
    else
        myaddr.sin_port = htons(23456);

    if (argv[3]) {
        if (inet_pton(AF_INET, argv[3], &myaddr.sin_addr) <= 0) {
            printf("self ip address error!/n");
            exit(0);
        }
    } else
        myaddr.sin_addr.s_addr = INADDR_ANY;

    /* °ó¶¨×Ô¼ºµÄ¶Ë¿ÚºÍIPÐÅÏ¢µ½socketÉÏ */
    if (bind
            (sockfd, (struct sockaddr *) &myaddr,
             sizeof(struct sockaddr_in)) == -1) {
        printf("Bind error/n");
        exit(0);
    }

    /* Ñ­»·½ÓÊÜÓÃ»§ÊäÈëµÄÏûÏ¢·¢ËÍ×é²¥ÏûÏ¢ */
    for (;;) {
        /* ½ÓÊÜÓÃ»§ÊäÈë */
        bzero(recmsg, BUFLEN + 1);
        if (fgets(recmsg, BUFLEN, stdin) == (char *) EOF)
            exit(0);
        /* ·¢ËÍÏûÏ¢ */
        if (sendto
                (sockfd, recmsg, strlen(recmsg), 0,
                 (struct sockaddr *) &peeraddr,
                 sizeof(struct sockaddr_in)) < 0) {
            printf("sendto error!/n");
            exit(3);
        }
        printf("'%s' send ok/n", recmsg);
    }
}


