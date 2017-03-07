#include "Thread.h"

void* GlobalThreadFunction(void* argv)
{
    CThread* thread = reinterpret_cast<CThread*>(argv);
    if (thread)
    {
	thread->SetThreadState(THREAD_RUNNING);
	thread->Run();
	thread->SetThreadState(THREAD_FINISHED);
    }
}

CThread::CThread()
{
    m_CreateSuspended = false;
    SetThreadState(THREAD_IDLE);
    m_ThreadName = NULL;
    m_Detach = false;
    sem_init(&m_ThreadSemaphore,false,0);
}

CThread::CThread(bool createsuspended,bool detach)
{
    m_CreateSuspended = createsuspended;
    SetThreadState(THREAD_IDLE);
    m_ThreadName = NULL;
    m_Detach = detach;
    sem_init(&m_ThreadSemaphore,false,0);
}

CThread::~CThread()
{
    if(NULL != m_ThreadName)
	free(m_ThreadName);
    SetThreadState(THREAD_FINISHED);
    
    sem_destroy(&m_ThreadSemaphore);
}

//terminate the thread
bool CThread::Terminate(void)
{
    if(pthread_cancel(m_ThreadID)!=0)
    {
	SetThreadState(THREAD_TERMINATED);
	SetErrcode(Error_ThreadTerminated);
	return false;
    }
    else
	return true;
}

bool CThread::Start(void)
{
   if(m_CreateSuspended)
   {
	SetThreadState(THREAD_SUSPENDED);
	sem_wait(&m_ThreadSemaphore);
   }
   int result = pthread_create(&m_ThreadID,NULL,GlobalThreadFunction,this);
   if (result == 0)
   {
      if (m_Detach)
         pthread_detach(m_ThreadID);
      return true;
   }
   else
   {
      SetThreadState(THREAD_DEAD);
      //POSIXSynchronousEvent("POSIXThread::start() - Failed to create thread.",threadID);
      return false;
   }
   return true;
}

void* CThread::ThreadFunction(void* argv)
{
   CThread* thread = reinterpret_cast<CThread*>(argv);
   if (thread)
   {
	thread->SetThreadState(THREAD_RUNNING);
	thread->Run();
	thread->SetThreadState(THREAD_FINISHED);
   }
}

void CThread::Exit(void)
{
    SetThreadState(THREAD_FINISHED);
    pthread_exit((void**)0);
}

bool CThread::Wakeup(void)
{
    if(sem_post(&m_ThreadSemaphore)!=0)
    {
	SetErrcode(Error_ThreadWakeup);
	return false;
    }
    else
    {
	SetThreadState(THREAD_RUNNING);
	return true;
    }
}

bool CThread::SetPriority(int priority)
{
    if(priority >10 || priority <0)
    {
	SetErrcode(Error_ThreadSetPriority);
        return false;
    }

    struct sched_param threadParameter;
    threadParameter.sched_priority = priority;

    if (pthread_setschedparam(m_ThreadID, SCHED_OTHER, &threadParameter) != 0)
    {
      //POSIXSynchronousEvent("POSIXThread::setPriority() - Failed to set thread priority.",threadID);
	SetErrcode(Error_ThreadSetPriority);
        return false;
    }
    else
        return true;
}

int CThread::GetPriority(void)
{
    struct sched_param threadParameter;
    int   policy = 0;

    if(pthread_getschedparam(m_ThreadID, &policy, &threadParameter) == 0)
    {
	//POSIXSynchronousEvent("POSIXThread::getPriority() - Failed to get thread priority.",threadID);
	return -1;
    }
    else
	return threadParameter.sched_priority;
}

bool CThread::Detach(void)
{
    if(pthread_detach(m_ThreadID)!=0)
    {
	SetErrcode(Error_ThreadDetach);
	return false;
    }
    else
	return true;
}

bool CThread::Join(void)
{
    if(pthread_join(m_ThreadID,NULL)!=0)
    {
	SetErrcode(Error_ThreadJoin);
	return false;
    }
    else
	return true;
}

bool CThread::Yield(void)
{
    if(sched_yield()!=0)
    {
	SetErrcode(Error_ThreadYield);
	return false;	
    }
    else
	return true;
}

int CThread::Self(void)
{
    return pthread_self();
}

void CThread::SetConcurrency(int num)
{
    pthread_setconcurrency(num);
}

int CThread::GetConcurrency(void)
{
    return pthread_getconcurrency();
}
