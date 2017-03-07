/********* 
  线程互斥量 
 **********/ 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x;
pthread_mutex_t mutex; // 声明一个互斥量

void* thread1(void*)
{
    while(x > 0)
    {
        pthread_mutex_lock(&mutex); //上锁
        printf("Thread 1 is running x=%d\n",x);
        x--;
        pthread_mutex_unlock(&mutex); //解锁
        sleep(1);
    }
    pthread_exit(NULL);
}

void* thread2(void*)
{
    while(x > 0)
    {
        pthread_mutex_lock(&mutex);    //上锁 //注释本行看区别
        //sleep(3);
        printf("Thread 2 is running x=%d\n",x);
        x--;
        pthread_mutex_unlock(&mutex); //解锁
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t id1;
    pthread_t id2;
    int ret;
    ret = pthread_mutex_init(&mutex, NULL); //初始化互斥量
    if(0 != ret)
    {
        printf("pthread_mutex_init error\n");
        exit(0);
    }
    x = 10; //初始值
    ret = pthread_create(&id1, NULL, thread1, NULL); //创建线程1
    if(ret!=0)
    {
        printf("Create pthread 1 error\n");
        exit(0);
    }
    ret = pthread_create(&id2, NULL, thread2, NULL); //创建线程2
    if(0 != ret)
    {
        printf("Create pthread 2 error\n");
        exit(0);
    }
    pthread_join(id1, NULL); //线程结束聚合线程
    pthread_join(id2, NULL);
    printf("Done\n");
    return 0;
}

