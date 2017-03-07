#include <iostream>
#include <unistd.h>
#include "foo.h"


foo * foo_alloc(void);

void foo_hold(struct foo *fp, unsigned int const & third_id); /* add a reference to the object */

void foo_rele(struct foo *fp); /* release a reference to the object */

pthread_t ntid;
pthread_t ntid2;

foo* p = foo_alloc();

void * thr_fn(void *arg)
{
    for (int i = 0; i < 10000000; i++)
    {
        foo_hold(p, 1);
    }
    return((void *)0);
}

void * thr_fn2(void *arg)
{
    for (int i = 0; i < 10000000; i++)
    {
        foo_hold(p, 2);
    }
    return((void *)0);
}

int main(int argc, char **argv)
{
    int err;
    void* tret;
    std::cout << "Hello, world!" << std::endl;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "thread create err thread1" << std::endl;
    err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
    if (0 != err)
        std::cout << "thread create err thread2" << std::endl;

    pthread_join(ntid, &tret);
    if (0 != err)
    {
        std::cout << "pthread_join failed" << std::endl;
    }
    else
    {
        std::cout << "pthread_join successfully " << std::endl;
        std::cout << "tret=: " << (long)tret << std::endl;
    }
    pthread_join(ntid2, &tret);
    if (0 != err)
    {
        std::cout << "pthread_join failed" << std::endl;
    }
    else
    {
        std::cout << "pthread_join successfully " << std::endl;
        std::cout << "tret=: " << (long)tret << std::endl;
    }
    return 0;
}
