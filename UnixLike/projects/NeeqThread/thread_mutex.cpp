///线程互斥锁类实现
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: thread_mutex.cpp
功能说明:
作    者: 何李夫
开发日期: 2013-7-11   11:08:55
修改记录:
***********************************************************************/
#include "thread_mutex.h"


CThreadMutex::CThreadMutex()
{
    pthread_mutexattr_t attr;

    /* 初始化互斥锁属性对象 */
    pthread_mutexattr_init(&attr);

    /* 设置互斥锁的类型属性 */
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);

    /* 动态创建互斥锁 */
    pthread_mutex_init(&m_Mutex, &attr);

    /* 销毁互斥锁属性对象 */
    pthread_mutexattr_destroy(&attr);
}

CThreadMutex::~CThreadMutex()
{
    /* 销毁互斥锁 */
	pthread_mutex_destroy(&m_Mutex);
}

int32_t CThreadMutex::Acquire()
{
	return pthread_mutex_lock(&m_Mutex);
}

int32_t CThreadMutex::Release()
{
	return pthread_mutex_unlock(&m_Mutex);
}

int32_t CThreadMutex::TryAcquire()
{
    return pthread_mutex_trylock(&m_Mutex);
}

//////////////////////////////////////////////////////////////////////////
CAutoMutex::CAutoMutex(CThreadMutex* pMutex)
: m_lpMutex(pMutex)
{
    m_lpMutex->Acquire();
}

CAutoMutex::~CAutoMutex()
{
    m_lpMutex->Release();
}
