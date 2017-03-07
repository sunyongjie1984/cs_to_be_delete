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

/**
 * The max number of child process arguments. Normally, 64 is enough.
 */
#define APP_MAX_ARGC	64

/**
 * Execute a child process, and wait for its termination.
 */
static apr_status_t run_program(const char *progname, const apr_procattr_t *pattr, apr_pool_t *mp)
{
    apr_status_t rv;
    int argc = 0;
    const char* argv[APP_MAX_ARGC];
    apr_proc_t proc;

    argv[argc++] = progname;
    /* you can specify command line options as follows,
       argv[argc++] = "-i";
       argv[argc++] = "argument"; */
    argv[argc++] = NULL;/* @argvs should be null-terminated */

    if ((rv = apr_proc_create(&proc, progname, (const char* const*)argv,
                              NULL, (apr_procattr_t*)pattr, mp)) != APR_SUCCESS) {
        return rv;
    }

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
 * process execution sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    const char *progname;
    apr_procattr_t *pattr;
        
    if (argc != 2) {
	printf("usage: %s progname\n", argv[0]);
	exit(1);
    }
    progname = argv[1];

    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* prepare process attribute */
    if ((rv = apr_procattr_create(&pattr, mp)) != APR_SUCCESS) {
        goto error;
    }
    if ((rv = apr_procattr_io_set(pattr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE)) != APR_SUCCESS) {
        goto error;
    }
    /* default value: APR_PROGRAM */
    if ((rv = apr_procattr_cmdtype_set(pattr, APR_PROGRAM_ENV)) != APR_SUCCESS) {
        goto error;
    }
    /* detaching process has different effects on platform.
     * On Unix, detached process implies a daemon process.
     * On Windows, detached process implies a process without the console window. */
    apr_procattr_detach_set(pattr, TRUE);

    /* run the program */
    run_program(progname, pattr, mp);

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
