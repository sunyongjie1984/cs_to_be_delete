#include <iostream>
#include <unistd.h>
#include "foo.h"


foo * foo_alloc(void);

void foo_hold(struct foo *fp, unsigned int const & third_id); /* add a reference to the object */

void foo_rele(struct foo *fp); /* release a reference to the object */

pthread_t ntid;
pthread_t ntid2;

foo* p = foo_alloc();
pthread_mutex_t lock_cout;

void printids(const char *s)
{
    // pid_t     pid;
    // pthread_t tid;
    // int ret_wait;
    // int count =0;

    while(true)
    {
    }
}

void * thr_fn(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        foo_hold(p, 1);
    }
    return((void *)0);
}

void * thr_fn2(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        foo_hold(p, 2);
    }
    return((void *)0);
}

int main(int argc, char **argv)
{
    if (pthread_mutex_init(&lock_cout, NULL) != 0)
        std::cout << "init lock_cout failed" << std::endl;

    void* tret;
    unsigned int err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "thread create err thread1" << std::endl;
    err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
    if (0 != err)
        std::cout << "thread create err thread2" << std::endl;

    err = pthread_join(ntid, &tret);
    if (0 != err)
    {
        pthread_mutex_lock(&lock_cout);
        std::cout << "pthread_join thread1 failed" << std::endl;
        pthread_mutex_unlock(&lock_cout);
    }
    else
    {
        pthread_mutex_lock(&lock_cout);
        std::cout << "pthread_join thread1 successfully " << std::endl;
        std::cout << "tret=: " << (long)tret << std::endl;
        pthread_mutex_unlock(&lock_cout);
    }
    err = pthread_join(ntid2, &tret);
    if (0 != err)
    {
        pthread_mutex_lock(&lock_cout);
        std::cout << "pthread_join thread2 failed" << std::endl;
        pthread_mutex_unlock(&lock_cout);
    }
    else
    {
        pthread_mutex_lock(&lock_cout);
        std::cout << "pthread_join thread2 successfully " << std::endl;
        std::cout << "tret=: " << (long)tret << std::endl;
        pthread_mutex_unlock(&lock_cout);
    }
    return 0;
}
