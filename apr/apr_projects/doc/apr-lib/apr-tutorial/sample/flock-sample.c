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
#include <apr_file_io.h>

static apr_status_t do_writelock(const char *fname, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_file_t *fp;
    
    if ((rv = apr_file_open(&fp, fname, APR_WRITE, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        return rv;
    }
    rv = apr_file_lock(fp, APR_FLOCK_EXCLUSIVE | APR_FLOCK_NONBLOCK);
    /* if you specify APR_FLOCK_NONBLOCK flag, apr_file_lock() would fail.
     * you should check the return value */
    if (rv != APR_SUCCESS) {
        puts("writable-lock failed");
        goto done;
    }
    printf("%s is writable locked. press any key to unlock\n", fname);
    getchar();

    apr_file_unlock(fp);
 done:
    apr_file_close(fp);
    return rv;
}

static apr_status_t do_readlock(const char *fname, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_file_t *fp;

    if ((rv = apr_file_open(&fp, fname, APR_READ,  APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        return rv;
    }
    rv = apr_file_lock(fp, APR_FLOCK_SHARED | APR_FLOCK_NONBLOCK);
    if (rv != APR_SUCCESS) {
        puts("readable-lock failed");
        goto done;
    }

    apr_file_unlock(fp);
 done:
    apr_file_close(fp);
    return rv;
}

/**
 * file lock sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    int c;
    const char *fname;
        
    if (argc < 2) {
        printf("usage %s output-filename\n", argv[0]);
        return 0;
    }
    fname = argv[1];

    apr_initialize();
    apr_pool_create(&mp, NULL);

    puts("writable-lock / readable-lock [w/r]?");
    c = getchar();
    if (c == 'w') {
        rv = do_writelock(fname, mp);
    } else if (c == 'r') {
        rv = do_readlock(fname, mp);
    }

    apr_pool_destroy(mp);
    apr_terminate();
    return 0;
}
