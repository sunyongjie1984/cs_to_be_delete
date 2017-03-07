#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    printf("file %s, line %d parent, getpid() = %d\n", __FILE__, __LINE__, getpid());
    fflush(stdout);
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    { /* first child */
        printf("file %s, line %d child 1, getpid() = %d\n", __FILE__, __LINE__, getpid());
        fflush(stdout);
        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid > 0)
        {
            printf("first child, going to sleep(2)\n");
            sleep(2);
            printf("first child, after sleep(2), begin exiting\n");
            exit(0);   /* parent from second fork == first child */
        }

        /*
         * We're the second child; our parent becomes init as soon
         * as our real parent calls exit() in the statement above.
         * Here's where we'd continue executing, knowing that when
         * we're done, init will reap our status.
         */
        printf("file %s, line %d, child 2, getpid() = %d\n", __FILE__, __LINE__, getpid());
        printf("second child, going to sleep(5)\n");
        sleep(5);
        printf("second child, after sleep(5)\n");
        printf("second child, parent pid = %d, parent id is 1, which means my parent process is init\n", getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)  /* wait for first child */
        err_sys("waitpid error");
    else
        printf("after sleep(2), first child exit caught by parent (waitpid)\n");

    printf("file %s, line %d, getpid() = %d\n", __FILE__, __LINE__, getpid());

    /*
     * We're the parent (the original process); we continue executing,
     * knowing that we're not the parent of the second child.
     */
    exit(0);
}
