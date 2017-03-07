/**
 * apr tutorial sample code
 * http://dev.ariel-networks.com/apr/
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <apr_general.h>
#include <apr_thread_proc.h>
#include <apr_strings.h>

/**
 * Parse the output and find the largest file size.
 */
#define EXEC_CMD	"/bin/ls"
#define EXEC_CMD_ARG	"-l"

/* default buffer size */
#define BUFSIZE			4096

/* useful macros */
#undef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

/**
 * The max number of child process arguments. Normally, 64 is enough.
 */
#define APP_MAX_ARGC	64


static apr_status_t read_pipe(const apr_procattr_t *pattr, apr_pool_t *mp)
{
    apr_status_t rv;
    int argc = 0;
    const char* argv[APP_MAX_ARGC];
    apr_proc_t proc;
    apr_size_t max_sz = 0;
    int is_firstline = TRUE;

    argv[argc++] = EXEC_CMD;
    argv[argc++] = EXEC_CMD_ARG;
    argv[argc++] = NULL;/* @argvs should be null-terminated */

    if ((rv = apr_proc_create(&proc, EXEC_CMD, (const char* const*)argv,
                              NULL, (apr_procattr_t*)pattr, mp)) != APR_SUCCESS) {
        return rv;
    }

    while (1) {
        char buf[BUFSIZE];
        char **tokens;

        /* read the command's output through the pipe */
        rv = apr_file_gets(buf, sizeof(buf), proc.out);
        if (APR_STATUS_IS_EOF(rv)) {
            break;
        }
        if (is_firstline) {/* skip the first line */
            is_firstline = FALSE;
            continue;
        }
        apr_tokenize_to_argv(buf, &tokens, mp);
        assert(tokens[4]);
        max_sz = MAX(max_sz, atoi(tokens[4]));
    }
    apr_file_close(proc.out);
    printf("the largest file size is %" APR_SIZE_T_FMT "\n", max_sz);
        
    {
        int st;
        apr_exit_why_e why;
            
        rv = apr_proc_wait(&proc, &st, &why, APR_WAIT);
        if (APR_STATUS_IS_CHILD_DONE(rv)) {
            printf("child done: why = %d, exit status = %d\n", why, st);
        } else {
            printf("child notdone\n");
        }
    }

    return APR_SUCCESS;
}

/**
 * process execution and communicate through the pipe sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_procattr_t *pattr;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* prepare process attribute */
    if ((rv = apr_procattr_create(&pattr, mp)) != APR_SUCCESS) {
        goto error;
    }
    if ((rv = apr_procattr_io_set(pattr, APR_NO_PIPE, APR_FULL_BLOCK, APR_NO_PIPE)) != APR_SUCCESS) {
        goto error;
    }
    /* default value: APR_PROGRAM */
    if ((rv = apr_procattr_cmdtype_set(pattr, APR_PROGRAM_ENV)) != APR_SUCCESS) {
        goto error;
    }

    /* run the program and read the output from the pipe */
    read_pipe(pattr, mp);

    apr_terminate();
    return 0;

 error:
    {
        char errbuf[256];
        apr_strerror(rv, errbuf, sizeof(errbuf));
        printf("error: %d, %s\n", rv, errbuf);
    }
    apr_terminate();
    return -1;
}
