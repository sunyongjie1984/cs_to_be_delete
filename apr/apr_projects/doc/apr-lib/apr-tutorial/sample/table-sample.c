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
#include <apr_tables.h>

/* apr_table is a dynamic container. So the initial size is not a limitation of the table. */
#define TABLE_INIT_SZ           32

static int tab_cb(void *data, const char *key, const char *value);

/**
 * add/delete/modify the elements in the table)
 */
static void modify_table(apr_table_t *tab)
{
    /* set (no copy) */
    apr_table_setn(tab, "key1", "val1");

    /* set (duplicate both key and value)
     * internally, apr_pstrdup(mp, "key2") and apr_pstrdup(mp, "val2") are called */
    apr_table_set(tab, "key2", "val2");

    /* set over-write the old value. see apr_table_get() result below */
    apr_table_set(tab, "key2", "over-val2");

    /* unset remove the element */
    apr_table_setn(tab, "key3", "val3");
    apr_table_unset(tab, "key3");

    /* add doesn't over-write the old value. see apr_table_get() and iteration results below */
    apr_table_add(tab, "key4", "val4");
    apr_table_add(tab, "key4", "add-val4");
}

static void iterate_table(const apr_table_t *tab)
{
    const apr_array_header_t *tarr = apr_table_elts(tab);
    const apr_table_entry_t *telts = (const apr_table_entry_t*)tarr->elts;
    int i;

    for (i = 0; i < tarr->nelts; i++) {
        printf("key = %s, val = %s\n", telts[i].key, telts[i].val);
    }
}

/**
 * dynamic table sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    apr_table_t *tab;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* create a table(key/value string pair container) */
    tab = apr_table_make(mp, TABLE_INIT_SZ);

    modify_table(tab);
    
    /* get the values from key */
    printf("getter: key1:%s key2:%s key3:%s key4:%s unknown-key:%s\n",
           apr_table_get(tab, "key1"),
           apr_table_get(tab, "key2"),
           apr_table_get(tab, "key3"),
           apr_table_get(tab, "key4"),
           apr_table_get(tab, "unknown-key"));

    /* iteration with callback-function. Be careful the final NULL argument is required */
    apr_table_do(tab_cb, "label1", tab, NULL);
    apr_table_do(tab_cb, "label2", tab, "key1", "key2", NULL);/* iteration with filters */

    /* iteration by apr_array_header_t */
    iterate_table(tab);

    /* table is destroyed when @mp is destroyed */
    apr_pool_destroy(mp);

    apr_terminate();
    return 0;
}

/* table iteration callback function */
static int tab_cb(void *data, const char *key, const char *value)
{
    const char *label = data;
    printf("callback[%s]: %s %s\n", label, key, value);
    return TRUE;/* TRUE:continue iteration. FALSE:stop iteration */
}
