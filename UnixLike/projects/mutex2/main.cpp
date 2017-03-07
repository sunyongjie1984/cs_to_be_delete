#include <iostream>

pthread_t ntid;
pthread_t ntid2;

pthread_mutex_t f_lock;

unsigned int g_count = 0;

void foo_hold(unsigned int const & thread_no)
{
    pthread_mutex_lock(&f_lock);
    std::cout << "I am in thread " << g_count++ << " " << thread_no << std::endl;
    pthread_mutex_unlock(&f_lock);
}

void * thr_fn(void *arg)
{
    for (int i = 0; i < 10000000; i++)
    {
        foo_hold(1);
    }
    return((void *)0);
}

void * thr_fn2(void *arg)
{
    for (int i = 0; i < 10000000; i++)
    {
        foo_hold(2);
    }
    return((void *)0);
}

int main(int argc, char **argv)
{
    if (pthread_mutex_init(&f_lock, NULL) != 0)
        std::cout << "pthread_mutex_init(&f_lock, 0) error " << std::endl;
    int err;
    void* tret;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "thread create err thread1" << std::endl;
    err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
    if (0 != err)
        std::cout << "thread create err thread1" << std::endl;
    err = pthread_join(ntid, &tret);
    if (0 != err)
    {
        std::cout << "pthread_join failed" << std::endl;
    }
    else
    {
        std::cout << "pthread_join successfully " << std::endl;
        std::cout << "tret=: " << (long)tret << std::endl;
    }
    err = pthread_join(ntid2, &tret);
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
