#include "threadbase.h"

CThreadBase::CThreadBase() : m_iThreadId(0),
                             m_strThreadName(NULL),
                             m_bDetach(false),
                             m_bCreateSuspended(false)
{
    SetThreadState(THREAD_IDLE);

    #ifdef _LINUX_
    sem_init(&m_ThreadSemaphore, false, 0);
    #endif//_LINUX_
}

CThreadBase::CThreadBase(bool bSuspend, bool bDetach) : m_iThreadId(0),
                                                        m_strThreadName(NULL),
                                                        m_bDetach(false),
                                                        m_bCreateSuspended(false)
{
    m_bCreateSuspended = bSuspend;

    SetThreadState(THREAD_IDLE);

    m_bDetach = bDetach;

    #ifdef _LINUX_
    sem_init(&m_ThreadSemaphore, false, 0);
    #endif//_LINUX_
}

CThreadBase::~CThreadBase()
{
    if (NULL != m_strThreadName)
    {
        free(m_strThreadName);
    }
	
    SetThreadState(THREAD_FINISHED);

    #ifdef _LINUX_   
    sem_destroy(&m_ThreadSemaphore);
    #endif//_LINUX_
}

int CThreadBase::Start(void)
{
    int ret = 0;

    if (m_bCreateSuspended)
    {
        SetThreadState(THREAD_SUSPENDED);

        #ifdef _LINUX_
        sem_wait(&m_ThreadSemaphore);
        #endif//_LINUX_
    }

    #ifdef _LINUX_
    ret = pthread_create(&m_iThreadId, NULL, ThreadEntry, this);
    #endif//_LINUX_

    if (__SUCCESS != ret)
    {
        SetThreadState(THREAD_DEAD);
        ret = __FAILED;
    }

    if (m_bDetach)
    {
        #ifdef _LINUX_
        pthread_detach(m_iThreadId);
        #endif//_LINUX_
    }

    return ret;
}
void * CThreadBase::ThreadEntry(void * pV)
{
    printf("ThreadEntry start\n");

    CThreadBase * pT = reinterpret_cast<CThreadBase *>(pV);

    if (pT)
    {
        pT->SetThreadState(THREAD_RUNNING);

        pT->Run();

        pT->SetThreadState(THREAD_FINISHED);
    }

    printf("ThreadEntry end\n");

    return __SUCCESS;
}

int CThreadBase::Terminate(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = pthread_cancel(m_iThreadId);
    #endif//_LINUX_

    if (__SUCCESS != ret)
    {
        SetThreadState(THREAD_TERMINATED);

        SetErrCode(Error_ThreadTerminated);

        ret = __FAILED;
    }

    return ret;
}

void CThreadBase::Exit(void)
{
    SetThreadState(THREAD_FINISHED);

    #ifdef _LINUX_
    pthread_exit((void **)0);
    #endif//_LINUX_
}

int CThreadBase::WarkUp(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = sem_post(&m_ThreadSemaphore);
    #endif//_LINUX_

    if(__SUCCESS != ret)
    {
        SetErrCode(Error_ThreadWakeup);
        ret = __FAILED;
    }

    SetThreadState(THREAD_RUNNING);

    return ret;
}

void CThreadBase::SetConcurrency(int num)
{
    #ifdef _LINUX_
    pthread_setconcurrency(num);
    #endif//_LINUX_
}

int CThreadBase::GetConcurrency(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = pthread_getconcurrency();
    #endif//_LINUX_

    return ret;
}

int CThreadBase::SetPriority(int priority)
{
    int ret = 0;

    if(priority >10 || priority <0)
    {
        SetErrCode(Error_ThreadSetPriority);
        return -1;
    }

    #ifdef _LINUX_
    struct sched_param threadParameter;

    threadParameter.sched_priority = priority;

    ret = pthread_setschedparam(m_iThreadId, SCHED_OTHER, &threadParameter);
    #endif//_LINUX_

    if ( __SUCCESS != ret)
    {
        SetErrCode(Error_ThreadSetPriority);
        ret = __FAILED;
    }

    return ret;
}

int CThreadBase::GetPriority(void)
{
    int iPolicy = 0;
    int ret = 0;

    #ifdef _LINUX_
    struct sched_param threadParameter;

    ret = pthread_getschedparam(m_iThreadId, &iPolicy, &threadParameter);
    #endif//_LINUX_

    if(0 == ret)
    {
        ret = __FAILED;
    }
    else
    {
        #ifdef _LINUX_
        ret = threadParameter.sched_priority;
        #endif//_LINUX_
    }

    return ret;
}

int CThreadBase::Detach(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = pthread_detach(m_iThreadId);
    #endif//_LINUX_

    if(__SUCCESS != ret)
    {
        SetErrCode(Error_ThreadDetach);
        ret = __FAILED;
    }

    return ret;
}

int CThreadBase::Wait(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = pthread_join(m_iThreadId, NULL);
    #endif//_LINUX_

    if(__SUCCESS != ret)
    {
        SetErrCode(Error_ThreadJoin);
        ret = __FAILED;
    }

    return ret;
}

int CThreadBase::SchedYield(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = sched_yield();
    #endif//_LINUX_

    if(__SUCCESS != ret)
    {
        SetErrCode(Error_ThreadYield);
        ret = __FAILED;	
    }
    
    return ret;
}

int CThreadBase::Self(void)
{
    int ret = 0;

    #ifdef _LINUX_
    ret = pthread_self();
    #endif//_LINUX_

    return ret;
}

CSyncBase::CSyncBase()
{
}

CSyncBase::~CSyncBase()
{
}

CThreadMutex::CThreadMutex()
{
    #ifdef _LINUX_
    pthread_mutexattr_init(&m_MutexAttr);
    pthread_mutex_init(&m_Mutex, &m_MutexAttr);
    #endif//_LINUX_
}

CThreadMutex::~CThreadMutex()
{
    #ifdef _LINUX_
    pthread_mutexattr_destroy(&m_MutexAttr);
    pthread_mutex_destroy(&m_Mutex);
    #endif//_LINUX_
}

CCondition::CCondition() : m_bSendSignal(false),
                           m_iActiveWaiters(0)
{
    int ret = 0;

    #ifdef _LINUX_
    pthread_condattr_t condattrDetails;

    memset(&condattrDetails, 0, sizeof(condattrDetails));

    ret = pthread_condattr_init(&condattrDetails);

    if (__SUCCESS != ret)
    {
        return;
    }

    ret = pthread_cond_init(&m_Cond, &condattrDetails);

    if(__SUCCESS != ret)
    {
        return;
    }

    ret = pthread_condattr_destroy(&condattrDetails);

    if(__SUCCESS != ret)
    {
        return;
    }
    #endif//_LINUX_
}

CCondition::~CCondition()
{
    unsigned int retry = 0;

    int ret = 0;

    while (true)
    {
        #ifdef _LINUX_
        ret = pthread_cond_destroy(&m_Cond);

        if ((EBUSY == ret) && (retry <= 10))
        {
            retry++;
            SignalAll();
        }
        else
        {
            break;
        }
        #endif//_LINUX_
    }
}

void CCondition::Signal(void)
{
    Lock();

    if (false == m_bSendSignal)
    {
        #ifdef _LINUX_
        pthread_cond_signal(&m_Cond);
        #endif//_LINUX_

        m_bSendSignal = true;
    }

    Unlock();
}

void CCondition::SignalAll(void)
{
    Lock();

    #ifdef _LINUX_
    pthread_cond_broadcast(&m_Cond);
    #endif//_LINUX_

    m_bSendSignal = true;

    Unlock();
}

void CCondition::Wait(void)
{
    Lock();

    m_iActiveWaiters++;

    while (!m_bSendSignal)
    {
        #ifdef _LINUX_
        pthread_cond_wait(&m_Cond, m_ThreadMutex.GetMutex());
        #endif//_LINUX_
    }

    m_iActiveWaiters--;

    if (0 == m_iActiveWaiters)
    {
        m_bSendSignal = false;
    }

    Unlock();
}

void CCondition::WaitTimeOut(int ms)
{
    #ifdef _LINUX_
    struct timespec timeout;
    struct timeval  tp;

    gettimeofday(&tp, NULL);

    timeout.tv_sec   = (ms / 1000) + tp.tv_sec;
    timeout.tv_nsec  = ((ms % 1000) * 1000000) + (tp.tv_usec * 1000);

    while (timeout.tv_nsec >= 1000000000)
    {
        timeout.tv_nsec -= 1000000000;
        timeout.tv_sec++;
    }

    Lock();

    m_iActiveWaiters++;

    int ret = 0;

    while (!m_bSendSignal)
    {
        ret = pthread_cond_timedwait(&m_Cond, m_ThreadMutex.GetMutex(), &timeout);

        if (ETIMEDOUT == ret)
        {
            break;
        }
    }

    m_iActiveWaiters--;

    if ((0 == ret) && (0 == m_iActiveWaiters))
    {
        m_bSendSignal = false;
    }

    Unlock();
    #endif//_LINUX_
}

