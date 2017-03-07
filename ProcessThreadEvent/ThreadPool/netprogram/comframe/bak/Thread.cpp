#include "Thread.h"

CThread::CThread(bool createsuspended, int priority =-1)
{
    m_CreateSuspended = createsuspended;
    SetThreadState(issCreate);

    m_ThreadName = NULL;

    sem_init(&m_ThreadSemaphore,false,0);
}

CThread::~CThread()
{
    if(NULL != m_ThreadName)
	free(m_ThreadName);
    
}

/*
  About Suspend and Resume. POSIX does not support suspending/resuming a thread.
  Suspending a thread is considerd dangerous since it is not guaranteed where the
  thread would be suspend. It might be holding a lock, mutex or it might be inside
  a critical section.  In order to simulate it in Linux we've used signals. To
  suspend, a thread SIGSTOP is sent and to resume, SIGCONT is sent. Note that this
  is Linux only i.e. according to POSIX if a thread receives SIGSTOP then the
  entire process is stopped. However Linux doesn't entirely exhibit the POSIX-mandated
  behaviour. If and when it fully complies with the POSIX standard then suspend
  and resume won't work.
*/
void CThread::Suspended(void)
{
    SetThreadState(issSuspended);
    if(pthread_kill(m_ThreadID,SIGSTOP) !=0)
	SetErrCode(Error_ThreadSuspend);
    else
	SetErrCode(Error_ThreadSuccess);

    SetThreadState(issSuspended);
}

//send the signal SIGCONT
void CThread::Resume(void)
{
    SetThreadState(issRunnding);
}

//terminate the thread
void CThread::Terminate(void)
{
     
}

//set the thread to sleep
void CThread::Sleep(void)
{
}
