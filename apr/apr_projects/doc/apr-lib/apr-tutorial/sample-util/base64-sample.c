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
#include <apr_base64.h>

/**
 * base64 sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    const char orig[] = "abcdefghijklmn";
    char *encbuf;
    char *decbuf;
    int elen;
    int dlen;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* get the length of encoded string */
    elen = apr_base64_encode_len(strlen(orig));
    encbuf = apr_palloc(mp, elen);
    apr_base64_encode(encbuf, orig, strlen(orig));
    printf("base64 encoded string: %s, len = %d\n", encbuf, elen);

    /* get the length of decoded string */
    dlen = apr_base64_decode_len(encbuf);
    decbuf = apr_palloc(mp, dlen);
    apr_base64_decode(decbuf, encbuf);
    printf("decoded string: %s, len = %d\n", decbuf, dlen);

    apr_terminate();
    return 0;
}
