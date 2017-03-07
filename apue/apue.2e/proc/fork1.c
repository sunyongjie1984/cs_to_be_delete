#include "apue.h"
/* syj 20140112 */

int glob = 6; /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int main(void)
{
    int var; /* automatic variable on the stack */
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        err_sys("write error");
    printf("before fork\n\n"); /* we don't flush stdout */
    /* fflush(stdout); */           /* if comments this line, the child will flush the stdout */

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
                                              /* child, first flush buffer */
        printf("hello, I am child process\n");
        glob++;                               /* modify variables */
        var++;
    }
    else
    {
        sleep(3);                             /* parent */
        printf("hello, I am parent process\n");
    }

    if (0 == pid) /* for the child process, variable pid is 0 */
    {
        printf("hello, I am child process, variable pid is 0\n");
    }
    else          /* for the parent process, variable pid is child pid */
    {
        printf("hello, I am parent process, variable pid is child pid\n");
    }
    printf("pid = %d, pid = %d, glob = %d, var = %d\n\n\n", pid, getpid(), glob, var);

    return 0;
}
