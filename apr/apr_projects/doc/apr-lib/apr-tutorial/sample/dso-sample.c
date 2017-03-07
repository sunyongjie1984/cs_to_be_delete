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
#include <apr_dso.h>

/**
 * dso(dynamic symbol object) sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    const char fname[] = "libm.so";
    apr_dso_handle_t *dso_h;

    typedef double (*pow_fn_t)(double x, double y);
    pow_fn_t pow_fn;

    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* load libm.so */
    if ((rv = apr_dso_load(&dso_h, fname, mp)) != APR_SUCCESS) {
        goto error;
    }

    /* seek pow(3) function from libm.so */
    if ((rv = apr_dso_sym((apr_dso_handle_sym_t*)&pow_fn, dso_h, "pow")) != APR_SUCCESS) {
        goto error;
    }

    /* call pow(3) */
    printf("%d ^ %d = %f\n", 2, 2, pow_fn(2, 2));
    printf("%d ^ %d = %f\n", 3, 2, pow_fn(3, 2));
    printf("%d ^ %d = %f\n", 2, 10, pow_fn(2, 10));

    apr_dso_unload(dso_h);
    apr_pool_destroy(mp);
    
    apr_terminate();
    return 0;

 error:
    {
        char errbuf[256];
        apr_strerror(rv, errbuf, sizeof(errbuf));
        printf("error: %d, %s\n", rv, errbuf);
        apr_dso_error(dso_h, errbuf, sizeof(errbuf));
        printf("dso-error: %d, %s\n", rv, errbuf);
    }
    apr_terminate();
    return -1;
}
