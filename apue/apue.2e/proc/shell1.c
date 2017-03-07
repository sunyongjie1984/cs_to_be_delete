#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    char buf[MAXLINE]; /* from apue.h */
    pid_t pid;
    int status;

    printf("%% "); /* print prompt (printf requires %% to print %) */

    // We use the standard I/O function fgets to read one line at a time from the
    // standard input. When we type the end-of-file character (which is often
    // Control-D) as the first character of a line, fgets returns a null pointer, the loop
    // stops, and the process terminates. In Chapter 18, we describe all the special
    // terminal characters--end of file, backspace one character, erase entire line, and
    // so on -- and how to change them.
    // Because each line returned by fgets is terminated with a newline character,
    // followed by a null byte, we use the standard C function strlen to calculate the
    // length of the string, and then replace the newline with a null byte. We do this
    // because the execlp function wants a null-terminated argument, not a
    // newline-terminated argument.
    // We call fork to create a new process, which is a copy of the caller. We say that
    // the caller is the parent and that the newly created process is the child. Then
    // fork returns the non-negative process ID of the new child process to the parent,
    // and returns 0 to the child. Because fork creates a new process, we say that it is
    // called once--by the parent--but returns twice--in the parent and in the child.
    // In the child, we call execlp to execute the command that was read from the
    // standard input. This replaces the child process with the new program file. The
    // combination of fork followed by exec is called spawning a new process on
    // some operating systems. In the UNIX System, the two parts are separated into
    // individual functions. We'll say a lot more about these functions in Chapter 8.
    // Because the child calls execlp to execute the new program file, the parent
    // wants to wait for the child to terminate. This is done by calling waitpid,
    // specifying which process to wait for: the pid argument, which is the process ID
    // of the child. The waitpid function also returns the termination status of the
    // child--the status variable--but in this simple program, we don't do anything
    // with this value. We could examine it to determine how the child terminated
    // The most fundamental limitation of this program is that we can't pass
    // arguments to the command we execute. We can't, for example, specify the name
    // of a directory to list. We can execute ls only on the working directory. To allow
    // arguments would require that we parse the input line, separating the arguments
    // by some convention, probably spaces or tabs, and then pass each argument as a
    // separate parameter to the execlp function. Nevertheless, this program is still a
    // useful demonstration of the UNIX System's process control functions.
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0; /* replace newline with null */
        }

        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid == 0)
        {   /* child */
            // if the execlp execute successfully, execlp will not return
            // if it execute failed, return -1, and the error number store in errno variable
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    return 0;
}
