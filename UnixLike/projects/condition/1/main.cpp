#include <iostream>
#include <unistd.h>

pthread_mutex_t m_Mutex; /* 保护条件变量的互斥子 */
pthread_cond_t m_Cond;   /* 条件变量句柄 */    
bool flag = false;

void * thr_fn(void *arg)
{
    sleep(5);
    
    return((void *)0);
}

int main(int argc, char **argv)
{
    /* 按缺省的属性初始化 */
    pthread_cond_init(&m_Cond, NULL);
    pthread_mutex_init(&m_Mutex, NULL);
    
    pthread_t ntid;
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (0 != err)
        std::cout << "thread create err" << std::endl;
    
    int ret = 0;
    pthread_mutex_lock(&m_Mutex);
    ret = pthread_cond_wait(&m_Cond, &m_Mutex);
    if (0 == ret)
        
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}