#include "apue.h"
#include <pthread.h>

void* thr_fn1(void* arg)
{
    printf("thread 1 returning\n");
    /* return a vaviable of type void*
    return a pointer who points to a variable of type void*/
    return((void*)10);
}

void* thr_fn2(void* arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)21);
}

/*
 p is a pointer to an pointer B
 B points to an vaviable with type void
 */
void test2(void** p)
{   /*
     void* tret;
     void** p = &tret;

     *p is equal to variable tret
     tret = 'n'
     test2 successfully modify the vaviable of tret
     just like 
     tret = (void*)'n';
     in outside of this function
     tret is treated as a variable of type char
     so the compiler treate the memory of &tret as a variable of char
     and the content (of course one byte) is the asc code of char 'n'
    */
    *p = (void*)'n'; // don't think too much, this is just a type conversion
}

int main(void)
{
    int       err;
    pthread_t tid1;
    pthread_t tid2;
    void*     tret; /* define a pointer to void*/

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_quit("can't create thread 1: %s\n", strerror(err));
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_quit("can't create thread 2: %s\n", strerror(err));
    /* pass an address of a vaviable, may change the value of the it*/
    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_quit("can't join with thread 1: %s\n", strerror(err));
    /*
     force a variable with type void* to int
     force a pointer to an int
     */
    printf("thread 1 exit code %d\n", (int)(long)tret);
    err = pthread_join(tid2, &tret);
    if (err != 0)
        err_quit("can't join with thread 2: %s\n", strerror(err));
    printf("thread 2 exit code %d\n", (int)(long)tret);

    test2(&tret);
    printf("%c\n", (char)(long)tret); // treate tret as a variable of type char
                                      // just like the following

    int a = 10;
    int* pp = &a;
    *pp = (int)'n'; // just like a = (int)'n'
    printf("%c \n", (char)a);


    exit(0);
}
