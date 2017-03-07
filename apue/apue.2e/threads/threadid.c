// threads/threadid.c 11-1
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char* s)
{
    printf("%d ", (unsigned int)ntid);
    pid_t     pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
            (unsigned int)tid, (unsigned int)tid);
}

void* thr_fn(void* arg)
{
    printids("new thread: ");
    return((void *)0);
}

/*This example has two oddities, which are necessary to handle races between the main
 * thread and the new thread. (We'll learn better ways to deal with these conditions later
 * in this chapter.) The first is the need to sleep in the main thread. If it doesn't sleep, the
 * main thread might exit, thereby terminating the entire process before the new thread
 * gets a chance to run. This behavior is dependent on the operating system's threads
 * implementation and scheduling algorithms.
 * The second oddity is that the new thread obtains its thread ID by calling
 * pthread_self instead of reading it out of shared memory or receiving it as an
 * argument to its thread-start routine. Recall that pthread_create will return the
 * thread ID of the newly created thread through the first parameter (tidp). In our
 * example, the main thread stores this ID in ntid, but the new thread can¡¯t safely use it.
 * If the new thread runs before the main thread returns from calling pthread_create,
 * then the new thread will see the uninitialized contents of ntid instead of the thread ID.
 */
int main(void)
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        err_quit("can't create thread: %s\n", strerror(err));
    printids("main thread:");
    sleep(1);
    exit(0);
}
