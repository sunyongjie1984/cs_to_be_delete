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
#include <apr_dbm.h>

#define MY_KEY1       "first-key"
#define MY_VAL1       "first-val"


static int do_store(apr_dbm_t *db);
static int do_fetch(apr_dbm_t *db);
static int do_iterate(apr_dbm_t *db);
static int do_delete(apr_dbm_t *db);

/**
 * dbm sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_dbm_t *db;
    const char *dbname;
        
    if (argc < 2) {
        printf("usage %s dbname\n", argv[0]);
        return -1;
    }
    dbname = argv[1];

    apr_initialize();
    apr_pool_create(&mp, NULL);

    if ((rv = apr_dbm_open(&db, dbname, APR_DBM_RWCREATE, APR_OS_DEFAULT, mp)) != APR_SUCCESS) {
        goto error;
    }

    do_store(db);
    do_fetch(db);
    do_iterate(db);
    do_delete(db);
    
    apr_dbm_close(db);

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

/**
 * Store an element(key-value pair) to dbm
 * @return TRUE if success, otherwise FALSE.
 */
static int do_store(apr_dbm_t *db)
{
    apr_status_t rv;
    apr_datum_t key;
    apr_datum_t val;
    char *vstr;
    
    /* apr_datum_t::dptr will be duplicated in apr_dbm_store() */
    key.dptr = MY_KEY1;
    key.dsize = sizeof(MY_KEY1);/* In this example, the size includes the last '\0' byte */

    vstr = strdup(MY_VAL1);

    val.dptr = vstr;
    val.dsize = strlen(vstr) + 1;/* The size includes the last '\0' byte, again. This is often useful */

    if ((rv = apr_dbm_store(db, key, val)) != APR_SUCCESS) {
        return FALSE;
    }

    /* Since apr_datum_t::dptr was duplicated in apr_dbm_store(), we can free(3) this*/
    free(vstr);

    return TRUE;
}

/**
 * Fetch an element(key-value pair) from dbm by a key
 * @return TRUE if success, otherwise FALSE.
 */
static int do_fetch(apr_dbm_t *db)
{
    apr_status_t rv;
    int ret;
    apr_datum_t key;
    apr_datum_t rval;

    key.dptr = MY_KEY1;
    key.dsize = sizeof(MY_KEY1);

    /* Unlike other APIs, apr_dbm_exists() return TRUE or FALSE instead of apr_status_t */
    ret = apr_dbm_exists(db, key);
    printf("exists = %s\n", ret ? "yes" : "no");
    
    if ((rv = apr_dbm_fetch(db, key, &rval)) != APR_SUCCESS) {
        return FALSE;
    }
    printf("fetched value: %s, size=%d\n", rval.dptr, rval.dsize);
    return TRUE;
}

/**
 * Iterate on the dbm
 * @return TRUE if success, otherwise FALSE.
 */
static int do_iterate(apr_dbm_t *db)
{
    apr_status_t rv;
    apr_datum_t rkey;
    apr_datum_t rval;
    
    if ((rv = apr_dbm_firstkey(db, &rkey)) != APR_SUCCESS) {
        return FALSE;
    }
    printf("first key: %s\n", rkey.dptr);
    
    do {
        if ((rv = apr_dbm_fetch(db, rkey, &rval)) != APR_SUCCESS) {
            return FALSE;
        }
        printf("fetched key: %s, size=%d\n", rkey.dptr, rkey.dsize);
        printf("fetched value: %s, size=%d\n", rval.dptr, rval.dsize);
        
        if ((rv = apr_dbm_nextkey(db, &rkey)) != APR_SUCCESS) {
            return FALSE;
        }
    } while (rkey.dptr);

    return TRUE;
}

/**
 * Delete an element(key-value pair) from dbm by a key
 * @return TRUE if success, otherwise FALSE.
 */
static int do_delete(apr_dbm_t *db)
{
    apr_status_t rv;
    apr_datum_t key;

    key.dptr = MY_KEY1;
    key.dsize = sizeof(MY_KEY1);

    if ((rv = apr_dbm_delete(db, key)) != APR_SUCCESS) {
        return FALSE;
    }
    printf("deleted\n");
    return TRUE;
}
