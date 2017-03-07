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
#include <apr_time.h>

static void format_to_struct(apr_time_t t)
{
    apr_time_exp_t tm;
    apr_time_t t2;
        
    apr_time_exp_gmt(&tm, t);
    printf("GMT: tm.hour = %d, tm.min = %d, tm.sec = %d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    apr_time_exp_lt(&tm, t);
    printf("local: tm.hour = %d, tm.min = %d, tm.sec = %d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

    /* reverse convert */
    apr_time_exp_gmt_get(&t2, &tm);/* from tm to t2 */
    assert(t == t2);
}

static void format_to_string(apr_time_t t)
{
    char rbuf[APR_RFC822_DATE_LEN + 1];
    char cbuf[APR_CTIME_LEN + 1];
        
    apr_rfc822_date(rbuf, t);
    printf("apr_rfc822_date: %s\n", rbuf);
    apr_ctime(cbuf, t);
    printf("apr_ctime: %s\n", cbuf);
}

/**
 * time-APIs sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    apr_time_t t;
        
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* get the current time (elapsed time from epoch(1970/1/1) in micro-second) */
    t = apr_time_now();
    printf("The current time: %" APR_TIME_T_FMT "[us]\n", t);
    printf("The current time: %" APR_TIME_T_FMT "[ms]\n", apr_time_as_msec(t));
    printf("The current time: %" APR_TIME_T_FMT "[s]\n", apr_time_sec(t));

    /* format the time */
    format_to_struct(t);
    format_to_string(t);

    apr_terminate();
    return 0;
}
