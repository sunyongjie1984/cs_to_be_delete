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
#include <apr_mmap.h>

static apr_status_t do_mmap(apr_mmap_t **mm, const char *fname, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_finfo_t finfo;
    apr_mmap_t *mmap;
    
    /* @remark APR_BUFFERED can't be specified with mmap. It causes APR_EBADF */
    if ((rv = apr_file_open(&fp, fname, APR_READ, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        return rv;
    }
    if ((rv = apr_file_info_get(&finfo, APR_FINFO_SIZE, fp)) != APR_SUCCESS) {
        return rv;
    }
    if ((rv = apr_mmap_create(&mmap, fp, 0, finfo.size, APR_MMAP_READ, mp)) != APR_SUCCESS) {
        return rv;
    }

    /* you can close the file after apr_mmap_create()'s completion */
    apr_file_close(fp);

    printf("fsize = %" APR_OFF_T_FMT ", mmap-size = %" APR_SSIZE_T_FMT "\n", finfo.size, mmap->size);

    *mm = mmap;
    return rv;
}

/**
 * Scan the contents of the mmap'd file
 */
static void scan_mmap(const apr_mmap_t *mmap)
{
    const char *pt = mmap->mm;
    int i;
    for (i = 0; i < mmap->size; i++) {
        putchar(*pt++);
    }
}
  

/**
 * mmap(memory map) sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    const char *fname;
    apr_mmap_t *mmap;
        
    if (argc != 2) {
	printf("usage %s filename\n", argv[0]);
	exit(0);
    }
    fname = argv[1];
    
    apr_initialize();
    apr_pool_create(&mp, NULL);

    rv = do_mmap(&mmap, fname, mp);
    if (rv != APR_SUCCESS) {
        goto error;
    }

    /* scan the file content */
    scan_mmap(mmap);

    apr_mmap_delete(mmap);
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
