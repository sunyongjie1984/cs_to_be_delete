#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#define MAX 10

pthread_t thread[2];
pthread_mutex_t mut;
int number=0;
int i;

void* thread1()
{
    printf ("thread1 : I'm thread 1\n");

    for (i = 0; i < MAX; i++)
    {
        printf("thread1 : number = %d\n",number);
        pthread_mutex_lock(&mut);
        number++;
        pthread_mutex_unlock(&mut);
        sleep(2);
    }

    printf("thread1 : is main function waiting for my finish\n");
    pthread_exit(NULL);
}

void* thread2()
{
    printf("thread2 : I'm thread 2\n");

    for (i = 0; i < MAX; i++)
    {
        printf("thread2 : number = %d\n",number);
        pthread_mutex_lock(&mut);
        number++;
        pthread_mutex_unlock(&mut);
        sleep(3);
    }

    printf("thread2 : is main function waiting for my finish\n");
    pthread_exit(NULL);
}

void thread_create(void)
{
    int temp;
    memset(&thread, 0, sizeof(thread));          //comment1
    if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)  //comment2     
        printf("create thread1 failed\n");
    else
        printf("create thread1 successfully\n");

    if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)  //comment3
        printf("create thread2 failed\n");
    else
        printf("create thread2 successfully\n");
}

void thread_wait(void)
{
    if(thread[0] !=0)
    {             //comment4    
        pthread_join(thread[0],NULL);
        printf("thread1 finished\n");
    }
    if(thread[1] !=0) 
    {
        pthread_join(thread[1],NULL);
        printf("thread2 finished\n");
    }
}

int main()
{
    pthread_mutex_init(&mut,NULL);

    printf("I am function main, I am creating thread\n");
    thread_create();
    printf("I am function main, I am waiting\n");
    thread_wait();

    return 0;
}
