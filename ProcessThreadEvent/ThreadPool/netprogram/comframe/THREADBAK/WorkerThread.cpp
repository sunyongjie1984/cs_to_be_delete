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
    //problem occurs here
    for(;;)
    {
	//no job in job list,so we wait.^_^
	while(m_Job == NULL)
	{
	    printf("Job is null,thread %d will wait!\n",GetThreadID());
	    m_JobCond.Wait(); 
	}

	m_ThreadPool->MoveToBusyList(this);	

	printf("Idle thread %d has get a job and will execute!\n",GetThreadId());
	m_Job->Run(m_JobData);
	m_Job->SetWorkThread(NULL);
	m_Job = NULL;
	m_WorkMutex.Unlock();
	printf("Append the thread %d to idle list again\n",GetThreadID());
	m_ThreadPool->MoveToIdleList(this);
    }
}

void CWorkerThread::Wakeup(CJob* job,void* jobdata)
{
    m_WorkMutex.Lock();
    SetJob(job,jobdata);
    job->SetWorkThread(this);
    m_WorkMutex.Unlock();
    
    m_JobCond.Signal();
}

void CWorkerThread::SetJob(CJob* job,void* jobdata)
{
    m_VarMutex.Lock();
    m_ThreadPool->AppendToJobList(job);
    m_Job = job;
    m_JobData = jobdata;
    m_VarMutex.Unlock();

    m_JobCond.Signal();
}

void CWorkerThread::SetThreadPool(CThreadPool* thrpool)
{
    m_VarMutex.Lock();
    m_ThreadPool = thrpool;
    m_VarMutex.Unlock();
}

