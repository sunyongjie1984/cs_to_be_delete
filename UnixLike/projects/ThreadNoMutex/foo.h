#ifndef FOO_MY_HEADER
#define FOO_MY_HEADER

struct foo
{
    int             f_count;
    pthread_mutex_t f_lock;
    /* ... more stuff here ... */
};

#endif
