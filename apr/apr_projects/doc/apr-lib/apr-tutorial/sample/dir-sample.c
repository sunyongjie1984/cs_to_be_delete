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
#include <apr_file_info.h>
#include <apr_strings.h>

/**
 * traverse the directory recursively
 * @return TRUE if success, otherwise FALSE.
 */
static int traverse_dir(const char *dirpath, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_finfo_t dirent;
    apr_dir_t *dir;

    printf("Directory: %s\n", dirpath);
    if ((rv = apr_dir_open(&dir, dirpath, mp)) != APR_SUCCESS) {
        return FALSE;
    }

    while ((apr_dir_read(&dirent, APR_FINFO_DIRENT|APR_FINFO_TYPE|APR_FINFO_NAME, dir)) == APR_SUCCESS) {
        if (dirent.filetype == APR_DIR) {
            char *path;
            if (strcmp(dirent.name, ".") == 0 || strcmp(dirent.name, "..") == 0) {
                continue;
            }

            if ((rv = apr_filepath_merge(&path, dirpath, dirent.name, 0, mp)) != APR_SUCCESS) {
                goto error;
            }
            /* path = apr_pstrcat(mp, dirpath, "/", dirent.name, NULL); is much simpler */

            traverse_dir(path, mp);
        } else if (dirent.filetype == APR_REG) {
            printf("Regular file path: %s\n", apr_pstrcat(mp, dirpath, "/", dirent.name, NULL));
        } else {
            printf("Non-regular file path: %s\n", apr_pstrcat(mp, dirpath, "/", dirent.name, NULL));
        }
    }
    
    if ((rv = apr_dir_close(dir)) != APR_SUCCESS) {
        return FALSE;
    }
    return TRUE;

 error:
    apr_dir_close(dir);
    return FALSE;
}


/**
 * file directory sample code
 * @remark Error checks omitted
 */
int main(int argc, char **argv)
{
    apr_status_t rv;
    apr_pool_t *mp;
    const char *dirname;
    apr_finfo_t finfo;
        
    if (argc == 2) {
        dirname = argv[1];
    } else {
        dirname = ".";
    }

    apr_initialize();
    apr_pool_create(&mp, NULL);

    if ((rv = apr_stat(&finfo, dirname, APR_FINFO_TYPE, mp)) != APR_SUCCESS) {
        goto error;
    }
    if (finfo.filetype != APR_DIR) {
        printf("need a directory name\n");
        goto error;
    }
    traverse_dir(dirname, mp);

    apr_terminate();
    return 0;

 error:
    apr_terminate();
    return -1;
}
