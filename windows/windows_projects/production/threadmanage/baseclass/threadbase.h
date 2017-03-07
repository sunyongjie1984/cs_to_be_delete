#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_

#include "../../include/publicpact.h"

#ifdef _LINUX_

#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/msg.h>

typedef sem_t Semaphore;
#endif//_LINUX_

typedef enum
{
    THREAD_IDLE =0,
    THREAD_RUNNING,
    THREAD_SUSPENDED,
    THREAD_TERMINATED,
    THREAD_FINISHED,
    THREAD_DEAD
}
ThreadState;

#define Error_ThreadSuccess     0
#define Error_ThreadInit        1
#define Error_ThreadCreate      2	
#define Error_ThreadSuspend     3
#define Error_ThreadResume      4	
#define Error_ThreadTerminated  5
#define Error_ThreadExit        6	
#define Error_ThreadSetPriority	7
#define Error_ThreadWakeup      8
#define Error_ThreadYield       9
#define Error_ThreadDetach      10
#define Error_ThreadJoin        11

class CThreadBase
{
public:
    CThreadBase();
    CThreadBase(bool bSuspend, bool bDetach);

    virtual ~CThreadBase();

public:
    int  Start(void);
    int  Terminate(void);
    int  WarkUp(void);
    void Exit(void);

    virtual void Run(void) = 0;

    void SetConcurrency(int num);
    int  GetConcurrency(void);

    int  SetPriority(int priority);
    int  GetPriority(void);

    int  Detach(void);
    int  Wait(void);
    int  SchedYield(void);
    int  Self(void);

    inline int GetThreadId(void)
    {
        return m_iThreadId;
    }
    inline void SetThreadName(char * thrname)
    {
        if (NULL != thrname)
        {
            strcpy(m_strThreadName, thrname);
        }
    }
    inline char * GetThreadName(void)
    {
        return m_strThreadName;
    }
    inline void SetErrCode(int errcode)
    {
        m_iErrCode = errcode;
    }
    inline int GetLastError(void)
    {
        return m_iErrCode;
    }
    inline void SetThreadState(ThreadState state)
    {
        m_ThreadState = state;
    }
    inline ThreadState GetThreadState(void)
    {
        return m_ThreadState;
    }
private:
    static void * ThreadEntry(void * pV);

private:
    unsigned long m_iThreadId;
    char *        m_strThreadName;

    int  m_iErrCode;
    bool m_bDetach;
    bool m_bCreateSuspended;

#ifdef _LINUX_
    Semaphore m_ThreadSemaphore;
#endif

    ThreadState m_ThreadState;
};

class CSyncBase
{
public:
    CSyncBase();
    virtual ~CSyncBase();

    virtual int Lock(void) = 0;
    virtual int Unlock(void) = 0;
};

class CThreadMutex : public CSyncBase
{
public:
    CThreadMutex();
    virtual ~CThreadMutex();

    inline virtual int Lock(void)
    {
        int ret = 0;

        #ifdef _LINUX_
        ret = pthread_mutex_lock(&m_Mutex);
        #endif//_LINUX_

        return ret;
    }
    inline virtual int Unlock(void)
    {
        int ret = 0;

        #ifdef _LINUX_
        ret = pthread_mutex_unlock(&m_Mutex);
        #endif//_LINUX_

        return ret;
    }
    inline virtual int Trylock (void)
    {
        int ret = 0;

        #ifdef _LINUX_
        ret = pthread_mutex_trylock(&m_Mutex);
        #endif//_LINUX_

        return ret;
    }

    #ifdef _LINUX_
    inline pthread_mutex_t* GetMutex(void)
    {
        return &m_Mutex;
    }
    #endif//_LINUX_

protected:
    #ifdef _LINUX_
    pthread_mutex_t      m_Mutex;
    pthread_mutexattr_t  m_MutexAttr;
    #endif//_LINUX_
};

class CCondition
{
public:
    CCondition();
    virtual ~CCondition();

    void Signal(void);
    void SignalAll(void);
    void Wait(void);
    void WaitTimeOut(int ms);

    inline void Lock(void)
    {
        m_ThreadMutex.Lock();
    }
    inline void Unlock(void)
    {
        m_ThreadMutex.Unlock();
    }

protected:
    CThreadMutex m_ThreadMutex;
    int m_iActiveWaiters;
    bool m_bSendSignal;

    #ifdef _LINUX_
    pthread_cond_t m_Cond;
    #endif//_LINUX_
};

#endif//_THREAD_BASE_H_

