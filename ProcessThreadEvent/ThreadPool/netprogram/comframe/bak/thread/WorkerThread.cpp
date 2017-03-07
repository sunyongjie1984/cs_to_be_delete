#include "WorkerThread.h"

CWorkerThread::CWorkerThread()
{
    m_Job = NULL;
    m_JobData = NULL;
    m_ThreadPool = NULL;
    m_IsEnd = false;
}

CWorkerThread::~CWorkerThread()
{
    if(NULL != m_Job)
	delete m_Job;

    if(m_ThreadPool != NULL)
	delete m_ThreadPool;
}

void CWorkerThread::Run()
{
    SetThreadState(THREAD_RUNNING);
    for(;;)
    {
	while(m_Job == NULL)
	{
	    printf("Job is null,thread %d will wait!\n",GetThreadID());
	    m_JobCond.Wait(); 
	}

	printf("Idle thread %d has get a job and will execute!\n",GetThreadId());
	m_Job->Run(m_JobData);
	m_Job->SetWorkThread(NULL);
	m_Job = NULL;
	printf("Append the thread %d to idle list again\n",GetThreadID());
	m_ThreadPool->MoveToIdleList(this);
	if(m_ThreadPool->m_IdleList.size() > m_ThreadPool->GetAvailHighNum())
	{
            printf("m_IdleList.size() > m_AvailHigh\n");
	    printf("++++++++m_ThreadPool->m_IdleList.size():%d+++++\n",m_ThreadPool->m_IdleList.size());
	    printf("++++++++m_ThreadPool->GetInitNum():%d+++++\n",m_ThreadPool->GetInitNum());
            m_ThreadPool->DeleteIdleThread(m_ThreadPool->m_IdleList.size()-m_ThreadPool->GetInitNum());
	}
	m_WorkMutex.Unlock();
    }
    printf("Idle List Num:%d \n",m_ThreadPool->m_IdleList.size());
}

void CWorkerThread::SetJob(CJob* job,void* jobdata)
{
    m_VarMutex.Lock();
    m_Job = job;
    m_JobData = jobdata;
    job->SetWorkThread(this);
    m_VarMutex.Unlock();

    m_JobCond.Signal();
}

void CWorkerThread::SetThreadPool(CThreadPool* thrpool)
{
    m_VarMutex.Lock();
    m_ThreadPool = thrpool;
    m_VarMutex.Unlock();
}

