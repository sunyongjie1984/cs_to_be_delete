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

/* default buffer size */
#define BUFSIZE			4096


static apr_status_t copy_file(const char *src_fname, const char *dest_fname, apr_pool_t *mp);

/**
 * file copy sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
        
    if (argc < 3) {
        printf("usage %s copy-src-filename copy-dest-filename\n", argv[0]);
        return 0;
    }

    apr_initialize();
    apr_pool_create(&mp, NULL);

    rv = copy_file(argv[1], argv[2], mp);
    if (rv != APR_SUCCESS) {
        goto error;
    }

    apr_pool_destroy(mp);
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

static apr_status_t copy_file(const char *src_fname, const char *dest_fname, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_file_t *src_fp = NULL;
    apr_file_t *dest_fp = NULL;
        
    /* open the file. in other words, create apr_file_t object */
    /* @remark after apr-1.1.0, use APR_FOPEN_READ for third argument */
    if ((rv = apr_file_open(&src_fp, src_fname, APR_READ|APR_BINARY, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        goto done;
    }
    if ((rv = apr_file_open(&dest_fp, dest_fname, APR_CREATE|APR_WRITE|APR_BINARY, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        goto done;
    }

    while (1) {
        char buf[BUFSIZE];
        apr_size_t len = sizeof(buf);

        rv = apr_file_read(src_fp, buf, &len);
        if (rv != APR_SUCCESS) {
            break;
        }
        rv = apr_file_write(dest_fp, buf, &len);
        if (rv != APR_SUCCESS) {
            break;
        }
    }

 done:
    if (src_fp) {
        apr_file_close(src_fp);
    }
    if (dest_fp) {
        apr_file_close(dest_fp);
    }
    return rv;
}
