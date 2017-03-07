#include "ThreadPool.h"
#include "WorkerThread.h"
#include <assert.h>

CThreadPool::CThreadPool()
{
    m_MaxNum = 20;
    m_MinNum = 5;
    m_ActiveNum = 10 ;   
    m_BusyNum = 0;
    m_IdleNum = 0;

    m_JobList.clear();
    m_BusyList.clear();
    m_IdleList.clear();
    for(int i=0;i<m_ActiveNum;i++)
    {
	printf("create a thread\n");
	CWorkerThread* thr = new CWorkerThread();
	thr->SetThreadPool(this);
	AppendToIdleList(thr);
	thr->Start();
	thr->SetConcurrency(m_ActiveNum+thr->GetConcurrency());
    }
}

CThreadPool::CThreadPool(int maxnum,int minnum,int initnum)
{
    assert(maxnum > 0);
    assert(minnum > 0 && minnum <= maxnum);
    assert(initnum > 0 && initnum <=maxnum && initnum >= minnum);
    if(maxnum>0)
	m_MaxNum = maxnum;
    else if(minnum>0 && minnum<=m_MaxNum)
	m_MinNum = minnum;
    else if(initnum>=m_MinNum && initnum <= m_MaxNum)
	m_ActiveNum = initnum;
    else
    {
	m_MinNum = 5;
	m_ActiveNum = 10 ;   
	m_BusyNum = 0;
	m_IdleNum = 0;
    }
    m_JobList.clear();
    m_BusyList.clear();
    m_IdleList.clear();
    for(int i=0;i<m_ActiveNum;i++)
    {
	CWorkerThread* thr = new CWorkerThread();
	thr->SetThreadPool(this);
	AppendToIdleList(thr);
	thr->Start();
	thr->SetConcurrency(initnum+thr->GetConcurrency());
    }
}

CThreadPool::CThreadPool(int initnum)
{
    assert(initnum>0);
    m_MinNum = 5;
    m_ActiveNum = initnum ;   
    m_BusyNum = 0;
    m_IdleNum = 0;

    m_JobList.clear();
    m_BusyList.clear();
    m_IdleList.clear();
    for(int i=0;i<m_ActiveNum;i++)
    {
	CWorkerThread* thr = new CWorkerThread();
	thr->SetThreadPool(this);
	AppendToIdleList(thr);
	thr->Start();		//begin the thread,the thread wait for job
	thr->SetConcurrency(initnum+thr->GetConcurrency());
    }
}

CThreadPool::~CThreadPool()
{
   WaitForAllWorkerToIdle();
   TerminateAll();
}

void CThreadPool::TerminateAll()
{
    for(int i=0;i < m_ThreadList.size();i++)
    {
	CWorkerThread* thr = m_ThreadList[i];
	thr->Join();
    }
    return;
}

//Usually when there no thread in idle list,we will wait
//but in our implement,we get idle thread complying below sequence
//(1)check the sum of exist thread,if the num below max value
CWorkerThread* CThreadPool::GetIdleThread(void)
{
    //===================================================//
    //       Here we will do some modify                 //
    //===================================================//
    //if the idle list is null
    while(m_IdleList.size() ==0 )
    	m_IdleCond.Wait();
    
    m_IdleMutex.Lock();
    if(m_IdleList.size()>0)
    {
	CWorkerThread* thr = (CWorkerThread*)m_IdleList.front();
	m_IdleMutex.Unlock();
	return thr;
    }
    m_IdleMutex.Unlock();

    return NULL;
}

CJob* CThreadPool::GetIdleJob(void)
{
    //no job in job list,so we wait for job!
    while(m_JobList.size() == 0)
	m_IdleJobCond.Wait();	

    m_JobMutex.Lock();
    if(m_JobList.size()>0)
    {
	CJob* job = (CJob*)m_JobList.back();
	m_JobMutex.Unlock();
	return job;
    }
    m_JobMutex.Unlock();
    
    return NULL;
}

bool  CThreadPool::DeleteJob(CJob* job)
{
    if(m_JobList.size() ==0)
	return false;
    vector<CJob*>::iterator pos;
    pos = find(m_JobList.begin(),m_JobList.end(),job);
    if(pos!=m_JobList.end())
	m_JobList.erase(pos);
}

//add an idle thread to idle list
void CThreadPool::AppendToIdleList(CWorkerThread* jobthread)
{
    m_IdleMutex.Lock();
    m_IdleList.push_back(jobthread); 
    m_ThreadList.push_back(jobthread);
    m_IdleMutex.Unlock();

}

void CThreadPool::AppendToJobList(CJob* job)
{
    m_JobMutex.Lock();
    m_JobList.push_back(job);
    m_JobMutex.Unlock();

    m_IdleJobCond.Signal();
}

//move and idle thread to busy thread 
void CThreadPool::MoveToBusyList(CWorkerThread* idlethread)
{
    m_BusyMutex.Lock();
    //add the idle thread to busy list
    m_BusyList.push_back(idlethread);
    //delete it from idle list
    m_BusyMutex.Unlock();
   
    m_IdleMutex.Lock();
    vector<CWorkerThread*>::iterator pos;
    pos = find(m_IdleList.begin(),m_IdleList.end(),idlethread);
    if(pos !=m_IdleList.end())
	m_IdleList.erase(pos);
    m_IdleMutex.Unlock();

    //notify the thread wait for job
}

void CThreadPool::MoveToIdleList(CWorkerThread* busythread)
{
    m_IdleMutex.Lock();
    m_IdleList.push_back(busythread);
    m_IdleMutex.Unlock();
 
    m_BusyMutex.Lock();
    vector<CWorkerThread*>::iterator pos;
    pos = find(m_BusyList.begin(),m_BusyList.end(),busythread);
    if(pos!=m_BusyList.end())
	m_BusyList.erase(pos);
    m_BusyMutex.Unlock();

    m_IdleCond.Signal();
}

void CThreadPool::WaitForAllWorkerToIdle(void)
{
    return;
}

void CThreadPool::Run(CJob* job,void* jobdata)
{
    assert(job!=NULL);
    
    //The Problem occurs here
    CWorkerThread*  idlethr = GetIdleThread();
    
    if(idlethr !=NULL)
    {
	idlethr->SetThreadPool(this);
	idlethr->m_WorkMutex.Lock();
	printf("Job is set to thread %d \n",idlethr->GetThreadID());
	idlethr->SetJob(job,jobdata);
	idlethr->SetThreadPool(this);
	job->SetWorkThread(idlethr);
    }
}

