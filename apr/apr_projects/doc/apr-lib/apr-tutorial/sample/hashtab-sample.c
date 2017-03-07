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
#include <apr_hash.h>
#include <apr_strings.h>

/**
 * add/delete/modify the elements in the hash table
 */
static void modify_hashtab(apr_hash_t *ht, apr_pool_t *mp)
{
    /* add key and value pair to the hash table
     * @remark apr_hash_t doesn't duplicate strings of neither key nor value */
    apr_hash_set(ht, "foo", APR_HASH_KEY_STRING, "FOO");

    /* it is a good idea to allocate strings in the same memory pool in almost cases */
    apr_hash_set(ht, apr_pstrdup(mp, "bar"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "BAR"));
    apr_hash_set(ht, apr_pstrdup(mp, "foobar"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "BAR"));
    apr_hash_set(ht, apr_pstrdup(mp, "barfoo"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "FOO"));

    /* To delete an entry, pass NULL as a value */
    apr_hash_set(ht, apr_pstrdup(mp, "to-del"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "TO-DEL"));
    apr_hash_set(ht, "to-del", APR_HASH_KEY_STRING, NULL);

    /* over-write with the same key. read the tutorial about its caution */
    apr_hash_set(ht, apr_pstrdup(mp, "override"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "old-val"));
    apr_hash_set(ht, apr_pstrdup(mp, "override"), APR_HASH_KEY_STRING, apr_pstrdup(mp, "new-val"));
}

static void iterate_hashtab(apr_hash_t *ht)
{
    apr_hash_index_t *hi;
    for (hi = apr_hash_first(NULL, ht); hi; hi = apr_hash_next(hi)) {
        const char *k;
        const char *v;
        
        apr_hash_this(hi, (const void**)&k, NULL, (void**)&v);
        printf("ht iteration: key=%s, val=%s\n", k, v);
    }
}

/**
 * hash table sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    apr_hash_t *ht;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    ht = apr_hash_make(mp);

    modify_hashtab(ht, mp);

    /* get the value from a key */
    {
        const char *val = apr_hash_get(ht, "foo", APR_HASH_KEY_STRING);
        printf("val for \"foo\" is %s\n", val);
    }
    
    /* iteration */
    iterate_hashtab(ht);

    /* the hash table is destroyed when @mp is destroyed */
    apr_pool_destroy(mp);

    apr_terminate();
    return 0;
}
