/*
 *  * 1£©ÓÐÒ»intÐÍÈ«¾Ö±äÁ¿g_Flag³õÊ¼ÖµÎª0£»
 *   *
 *    * 2£©ÔÚÖ÷Ïß³ÆÖÐÆð¶¯Ïß³Ì1£¬´òÓ¡¡°this is thread1¡±£¬²¢½«g_FlagÉèÖÃÎª1
 *     *
 *      * 3£©ÔÚÖ÷Ïß³ÆÖÐÆô¶¯Ïß³Ì2£¬´òÓ¡¡°this is thread2¡±£¬²¢½«g_FlagÉèÖÃÎª2
 *       *
 *        */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

int g_Flag=0;

void* thread1(void*);
void* thread2(void*);

/*
 *  * when program is started, a single thread is created, called the initial thread or main thread.
 *   * Additional threads are created by pthread_create.
 *    * So we just need to create two thread in main().
 *     */
int main(int argc, char** argv)
{
    printf("enter main\n");
    pthread_t tid1, tid2;
    int rc1=0, rc2=0;
    rc2 = pthread_create(&tid2, NULL, thread2, NULL);
    if(rc2 != 0)
        printf("%s: %d\n",__func__, strerror(rc2));

    rc1 = pthread_create(&tid1, NULL, thread1, &tid2);
    if(rc1 != 0)
        printf("%s: %d\n",__func__, strerror(rc1));
    sleep(1);
    printf("leave main\n");
    exit(0);  
}
/*
 *  * thread1() will be execute by thread1, after pthread_create()
 *   * it will set g_Flag = 1;
 *    */
void* thread1(void* arg)
{
    printf("enter thread1\n");
    printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    g_Flag = 1;
    printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    printf("leave thread1\n");
    pthread_exit(0);
}

/*
 *  * thread2() will be execute by thread2, after pthread_create()
 *   * it will set g_Flag = 2;
 *    */
void* thread2(void* arg)
{
    printf("enter thread2\n");
    printf("this is thread2, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    g_Flag = 2;
    printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    printf("leave thread2\n");
    pthread_exit(0);
}
