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
#include <apr_getopt.h>

/**
 * command line options sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    /* API is data structure driven */
    static const apr_getopt_option_t opt_option[] = {
        /* long-option, short-option, has-arg flag, description */
        { "in", 'i', TRUE, "input file" },      /* -i name or --in name */
        { "out", 'o', TRUE, "output file" },    /* -o name or --out name */
        { "help", 'h', FALSE, "show help" },    /* -h or --help */
        { NULL, 0, 0, NULL }, /* end (a.k.a. sentinel) */
    };
    apr_getopt_t *opt;
    int optch;
    const char *optarg;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* initialize apr_getopt_t */
    apr_getopt_init(&opt, mp, argc, argv);

    /* parse the all options based on opt_option[] */
    while ((rv = apr_getopt_long(opt, opt_option, &optch, &optarg)) == APR_SUCCESS) {
        switch (optch) {
        case 'i':
            printf("opt=i, %s\n", optarg);
            break;
        case 'o':
            printf("opt=o, %s\n", optarg);
            break;
        case 'h':
            printf("show help\n");  /* no arg */
            break;
        }
    }
    if (rv != APR_EOF) {
        printf("bad options\n");
    }

    apr_terminate();
    return 0;
}
