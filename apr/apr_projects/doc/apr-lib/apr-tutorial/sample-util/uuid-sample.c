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
#include <apr_uuid.h>

/**
 * uuid sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    apr_uuid_t uuid;
    char uuidstr[APR_UUID_FORMATTED_LENGTH + 1];
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* generate a new uuid */
    apr_uuid_get(&uuid);
    apr_uuid_format(uuidstr, &uuid);
    printf("generated UUID:%s\n", uuidstr);

    apr_terminate();
    return 0;
}
