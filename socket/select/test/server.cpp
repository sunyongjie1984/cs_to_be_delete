#include <unistd.h> /* fork, close */
#include <stdlib.h> /* exit */
#include <string.h> /* strlen */
#include <stdio.h> /* perror, fdopen, fgets */
#include <sys/socket.h>
#include <sys/wait.h> /* waitpid */
#include <netdb.h> /* getaddrinfo */
#define die(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define PORT "4242"
#define NUM_CHILDREN 3
#define MAXLEN 1024
int readline(int fd, char *buf, int maxlen); // forward declaration
int recvdata(int fd, char *buf, int maxlen); // forward declaration
int main(int argc, char** argv)
{
    int i, n, sockfd, clientfd;
    int yes = 1;    // used in setsockopt(2)
    struct addrinfo *ai;
    struct sockaddr_in *client;
    socklen_t client_t;
    pid_t cpid;     // child pid
    char line[MAXLEN];
    char cpid_s[32];
    char welcome[32];
    /* Create a socket and get its file descriptor -- socket(2) */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        die("Couldn't create a socket");
    }
    /* Prevents those dreaded "Address already in use" errors */
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(int)) == -1) {
        die("Couldn't setsockopt");
    }
    /* Fill the address info struct (host + port) -- getaddrinfo(3) */
    if (getaddrinfo(NULL, PORT, NULL, &ai) != 0) {   // get localhost 
        die("Couldn't get address");
    }
    /* Assign address to this socket's fd */
    if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) != 0) {  // only bind on localhost ip
        die("Couldn't bind socket to address");
    }
    /* Free the memory used by our address info struct */
    freeaddrinfo(ai);
    /* Mark this socket as able to accept incoming connections */
    /* printf("Process %d Listening/n", getpid()); */
    if (listen(sockfd, 10) == -1) {
        die("Couldn't make socket listen");
    }
    printf("One new connection is coming!\n");
    /* Fork you some child processes. */
    for (i = 0; i < NUM_CHILDREN; i++) {
        cpid = fork();
        if (cpid == -1) {
            die("Couldn't fork");
        }
        if (cpid == 0) { // We're in the child ...
            for (;;) { // Run forever ...
                /* Necessary initialization for accept(2) */
                client_t = sizeof client;
                /* Blocks! */
                printf("Waiting new connection!\n");
                clientfd = accept(sockfd, (struct sockaddr *)&client, &client_t);
                if (clientfd == -1) {
                    die("Couldn't accept a connection");
                }
                printf("haha");
                /* Send a welcome message/prompt */
                bzero(cpid_s, 32);
                bzero(welcome, 32);
                sprintf(cpid_s, "%d", getpid());
                sprintf(welcome, "Child %s echo> ", cpid_s);
                send(clientfd, welcome, strlen(welcome), 0);
                /* Read a line from the client socket ... */
                /* n = readline(clientfd, line, MAXLEN);
                 *              if (n == -1) {
                 *                                  die("Couldn't read line from connection");
                 *                                                  }                                                 */

                n = recvdata(clientfd, line, MAXLEN);
                printf("recieve data: %s\n", line);
                /* ... and echo it back */
                send(clientfd, line, n, 0);
                /* Clean up the client socket */
                close(clientfd);
                printf("Close client socket.\n");
            }
        }
    }
    /* Sit back and wait for all child processes to exit */
    while (waitpid(-1, NULL, 0) > 0);
    /* Close up our socket */
    close(sockfd);
    printf("Close server socket.\n");
    return 0;
}

/**
 *  * Simple utility function that reads a line from a file descriptor fd,
 *   * up to maxlen bytes -- ripped from Unix Network Programming, Stevens.
 *    */
int readline(int fd, char *buf, int maxlen)
{
    int n, rc;
    char c;
    for (n = 1; n < maxlen; n++) {
        if ((rc = read(fd, &c, 1)) == 1) {
            *buf++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            if (n == 1)
                return 0; // EOF, no data read
            else
                break; // EOF, read some data
        } else
            return -1; // error
    }
    *buf = '\0'; // null-terminate

    return n;
}
int recvdata(int fd, char *buf, int maxlen)
{
    return recv(fd, buf, maxlen, 0);
}

