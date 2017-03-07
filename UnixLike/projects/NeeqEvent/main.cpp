#include <iostream>
#include "event.h"

pthread_t ntid;
CEvent a;

void printids(const char *s)
{
    pid_t     pid;
    pthread_t tid;
    int32_t ret_wait;
    int32_t count =0;

    while(true)
    {
        pid = getpid();
        tid = pthread_self();
        printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
               (unsigned int)tid, (unsigned int)tid);
        ret_wait = a.Wait(100);
        if (EVENT_TIMEOUT == ret_wait)
        {
            std::cout << "event time out" << std::endl;
        }
        if (EVENT_OK == ret_wait)
        {
            std::cout << "event happened" << std::endl;
            break;
        }
        std::cout << "looping " << count++ << std::endl;
    }
}

void * thr_fn(void *arg)
{
    printids("new thread: ");
    return((void *)0);
}

int main(int argc, char **argv)
{
    int err;
    std::cout << "Hello, world!" << std::endl;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "thread create err" << std::endl;
    sleep(5);
    std::cout << "begin to set event" << std::endl;
    a.Set();
    std::cout << "event set, begin to quit" << std::endl;
    return 0;
}
