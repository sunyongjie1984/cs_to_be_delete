// #include "apue.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

pthread_t ntid;

void printids(const char *s)
{
    pid_t     pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
            (unsigned int)tid, (unsigned int)tid);
}

int g_int = 800;

void * thr_fn(void *arg)
{
    printids("new thread: ");
    for (int i = 0; i < 10; ++i)
    {
        sleep(1);
        std::cout << " " << i << std::endl;
    }
    return((void *)&g_int); // ok
    //return((void *)0);    // crash when dereference
}

int main(void)
{
    int err;
    void* tret;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "can't create thread: " << strerror(err) << std::endl;
    printids("main thread:");
    err = pthread_join(ntid, &tret);
    if (0 != err)
    {
        std::cout << "pthread_join error: " << strerror(err) << std::endl;
    }
    else
    {
        std::cout << "thread exit code: " << (long)tret << std::endl;
        
        // if the value of pp is 0,
        // which means that the value of the variable pp holds the address on 0
        // pp points the a variable which has a value of 0 is ok
        // but the value of pp is zero is wrong
        int *pp = (int*)tret;
        std::cout << "pp = " <<  *pp << std::endl;
        // std::cout << "thread exit code: " << *((int*)tret) << std::endl;
        // std::cout << "thread exit code: " << *((long*)tret) << std::endl;
    }
    
    return 0;
}
