#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <malloc.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define RES_LENGTH  10240 //½ÓÊÜ×Ö·ûµÄ×î´ó³¤¶È

int     connect_socket(char * server,int serverPort);
int     send_msg(int sockfd,char * sendBuff);
char *  recv_msg(int sockfd);
int     close_socket(int sockfd);

int main(int argc, char ** argv)
{
    int   sockfd=0;
    char  sendMsg[30]="abc.org\r\n\r";
    char* res;
    int   port = 4242;
    char  ip[128] = {0};
    strncpy(ip, "127.0.0.1", 128);
    if(argc > 2)
    {
        strncpy(ip, argv[1], 128);
        port = atoi(argv[2]);
        printf("Input IP: %s, port : %d\n", ip, port);
    }
    else if(argc > 1)
    {
        port = atoi(argv[1]);
        printf("Input port : %d\n", port);
    }
    printf("%s %d\n", ip, port);
    printf("%d\n", argc);
    sockfd=connect_socket(ip, port);

    send_msg(sockfd,sendMsg);
    res=recv_msg(sockfd);

    printf("return from recv function\n");
    printf(res);
    // free(res);
    close_socket(sockfd);
    return 0;
}
/************************************************************
 ** Á¬½ÓSOCKET·þÎñÆ÷£¬Èç¹û³ö´í·µ»Ø-1£¬·ñÔò·µ»Øsocket´¦Àí´úÂë
 ** server£º·þÎñÆ÷µØÖ·(ÓòÃû»òÕßIP),serverport£º¶Ë¿Ú
 **********************************************************/
int connect_socket(char * server,int serverPort){
    int    sockfd=0;
    struct    sockaddr_in    addr;
    struct    hostent        * phost;
    //ÏòÏµÍ³×¢²á£¬Í¨ÖªÏµÍ³½¨Á¢Ò»¸öÍ¨ÐÅ¶Ë¿Ú
    //AF_INET±íÊ¾Ê¹ÓÃIPv4Ð­Òé
    //SOCK_STREAM±íÊ¾Ê¹ÓÃTCPÐ­Òé
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
        herror("Init socket error!");
        return -1;
    }
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = inet_addr(server);//°´IP³õÊ¼»¯

    if(addr.sin_addr.s_addr == INADDR_NONE){//Èç¹ûÊäÈëµÄÊÇÓòÃû
        phost = (struct hostent*)gethostbyname(server);
        if(phost==NULL){
            herror("Init socket s_addr error!");
            return -1;
        }
        addr.sin_addr.s_addr =((struct in_addr*)phost->h_addr)->s_addr;
    }
    if(connect(sockfd,(struct sockaddr*)&addr, sizeof(addr))<0)
    {
        perror("Connect server fail!");
        return -1; //0±íÊ¾³É¹¦£¬-1±íÊ¾Ê§°Ü
    }
    else
        return sockfd;
}
/**************************************************************
 * ·¢ËÍÏûÏ¢£¬Èç¹û³ö´í·µ»Ø-1£¬·ñÔò·µ»Ø·¢ËÍµÄ×Ö·û³¤¶È
 * sockfd£ºsocket±êÊ¶£¬sendBuff£º·¢ËÍµÄ×Ö·û´®
 * *********************************************************/
int send_msg(int sockfd,char * sendBuff)
{
    int sendSize=0;
    if((sendSize=send(sockfd,sendBuff,strlen(sendBuff),0))<=0){
        herror("Send msg error!");
        return -1;
    }else
        return sendSize;
}
/****************************************************************
 *½ÓÊÜÏûÏ¢£¬Èç¹û³ö´í·µ»ØNULL£¬·ñÔò·µ»Ø½ÓÊÜ×Ö·û´®µÄÖ¸Õë(¶¯Ì¬·ÖÅä£¬×¢ÒâÊÍ·Å)
 *sockfd£ºsocket±êÊ¶
 * *********************************************************/
char* recv_msg(int sockfd){
    char * response;
    int  flag=0,recLenth=0;
    response=(char *)malloc(RES_LENGTH);
    memset(response,0,RES_LENGTH);

    for(flag=0;;)
    {
        printf("======recv data:\n");
        if(( recLenth=recv(sockfd,response+flag,RES_LENGTH-flag,0))==-1 )
        {
            free(response);
            printf("Return value : %d\n", recLenth);
            perror("Recv msg error : ");
            return NULL;
        }
        else if(recLenth==0)
            break;
        else
        {
            printf("%d char recieved data : %s.\n", recLenth, response+flag);
            flag+=recLenth;
            recLenth=0;
        }
    }
    printf("Return value : %d\n", recLenth);
    response[flag]='\0';
    return response;
}
/**************************************************
 *¹Ø±ÕÁ¬½Ó
 * **********************************************/
int close_socket(int sockfd)
{
    close(sockfd);
    return 0;
}
