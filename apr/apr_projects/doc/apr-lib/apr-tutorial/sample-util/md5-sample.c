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
#include <apr_md5.h>
#include <apr_time.h>
#include <apr_base64.h>

/**
 * md5 sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* we should call srand(3) when we use random numbers */
    srand(apr_time_now());

    while (1) {
        char passwd[256];
        char bsalt[64];/* random number(binary) for salt */
        char salt[128];
        char digest[128];
        
        puts("input password? [q:quit]: ");
        gets(passwd);/* XXX a real application program should not use gets(3) */
        if (strcmp(passwd, "q") == 0) {
            break;
        }

        /* generate a random number as a salt */
        apr_generate_random_bytes(bsalt, sizeof(bsalt));
        apr_base64_encode(salt, bsalt, sizeof(bsalt));

        apr_md5_encode(passwd, salt, digest, sizeof(digest));
        printf("md5 digest = %s, salt = %s\n", digest, salt);
    }

    apr_terminate();
    return 0;
}
