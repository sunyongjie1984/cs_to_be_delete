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

/**
 * apr skeleton code
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;

    /* per-process initialization */
    rv = apr_initialize();
    if (rv != APR_SUCCESS) {
        assert(0);
        return -1;
    }

    /* application impl. */

    apr_terminate();
    return 0;
}
