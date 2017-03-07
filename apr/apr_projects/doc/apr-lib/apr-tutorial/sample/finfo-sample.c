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

/**
 * file info sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_file_t *fp;
    const char *fname;
    apr_finfo_t finfo;
        
    if (argc < 2) {
        printf("usage %s output-filename\n", argv[0]);
        return 0;
    }
    fname = argv[1];

    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* @remark after apr-1.1.0, use APR_FOPEN_READ intead of APR_READ */
    if ((rv = apr_file_open(&fp, fname, APR_READ, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        return -1;
    }

    /* the following two ways have the same effects.
     * if you have opened the file, the former is better. Otherwise, the latter is better */
    
    /* you can get file info. by apr_file_t */
    rv = apr_file_info_get(&finfo, APR_FINFO_NORM, fp);
    /* you can get file info. by file name, too */
    rv = apr_stat(&finfo, fname, APR_FINFO_NORM, mp);
    
    apr_file_close(fp);

    apr_terminate();
    return 0;
}
