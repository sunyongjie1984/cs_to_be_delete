/*********
线程条件
**********/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x;
pthread_mutex_t mutex;
pthread_cond_t cond;

void producer(void)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        int i;
        for(i=0;i<3-x;i++)
        {
            x++;
            printf("Producing:i=%d x=%d \n",i,x);
            sleep(1);
        }
        if(x>=3)
        {
            pthread_cond_signal(&cond); /*条件改变，发送信号，通知consumer线程,激活等待该条件的线程*/
            /*pthread_cond_broadcast()激活所有等待线程*/
            printf("Producing complete %d\n",x);
        }
        pthread_mutex_unlock(&mutex);
        printf("producer Unlock Mutex\n");
        sleep(1);
    }
    pthread_exit(NULL);
}

void consumer(void)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(x<3)
        {
            pthread_cond_wait(&cond,&mutex);//等待一个条件 //等待
            printf("start consuming %d\n",x);
        }
        if(x>0)
        {
            x--;
            printf(" consuming %d\n",x);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        printf("consumer Unlock Mutex\n");
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t id1,id2;
    int ret;
    ret = pthread_mutex_init(&mutex,NULL); //初始化互斥量
    if(ret!=0)
    {
        printf("pthread_mutex_init error\n");
        exit(0);
    }
    ret=pthread_cond_init(&cond,NULL); //初始化条件变量
    if(ret!=0)
    {
        printf("pthread_cond_init error\n");
        exit(0);
    }
    printf("x=[%d]\n",x);
    ret = pthread_create(&id1,NULL,(void *)producer,NULL); //创建线程1 发生器
    if(ret!=0)
    {
        printf("Create pthread producer error\n");
        exit(0);
    }
    ret = pthread_create(&id2,NULL,(void *)consumer,NULL); //创建线程2 消耗器
    if(ret!=0)
    {
        printf("Create pthread consumer, error\n");
        exit(0);
    }
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    printf("Done\n");
    return 0;
}

