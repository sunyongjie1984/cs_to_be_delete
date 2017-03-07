// #include <iostream>
#include    "unp.h"

void
str_cli(FILE *fp, int sockfd)
{
    int         maxfdp1;
    fd_set      rset;
    char        sendline[MAXLINE], recvline[MAXLINE];

    FD_ZERO(&rset);
    for ( ; ; ) {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        printf("%s", "client select invoked\n");


        if (FD_ISSET(sockfd, &rset)) 
        {  /* socket is readable */
            int ret = Readline(sockfd, recvline, MAXLINE);
            if (0 == ret)
            {
                // 对端服务器发送一个FIN，对端进程终止，read返回0(EOF)
                err_quit("str_cli: server terminated prematurely");
            }
            if (0 > ret)
            {
                // 如果对端发送一个RST，对端主机崩溃并重新启动，read返回-1，errno中含有确切的错误码
            }
            if (0 < ret)
            {   // 对端tcp发送数据
                Fputs(recvline, stdout);
            }
        }

        if (FD_ISSET(fileno(fp), &rset)) 
        {  /* input is readable */
            if (Fgets(sendline, MAXLINE, fp) == NULL)
                return;     /* all done */
            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}
