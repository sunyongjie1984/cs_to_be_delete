#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    // 从标准输入读入一行文本
    // 当遇到文件结束符或错误时，fgets将返回一个空指针，于是客户处理终止循环。我们的Fgets包裹函数检查是否发生错误，若发生则中止进程，因此Fgets只是在遇到文件结束符时
    // 才返回一个空指针
    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        // 写到服务器上
        Writen(sockfd, sendline, strlen(sendline));
        // 读入服务器对该行的回射
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        // 把回射写到标准输出
        Fputs(recvline, stdout);
    }
    Fputs("exiting str_cli\n", stdout);
}
