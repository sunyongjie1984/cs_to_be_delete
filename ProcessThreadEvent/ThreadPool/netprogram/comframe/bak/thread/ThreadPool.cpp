#include "ThreadPool.h"
#include "WorkerThread.h"
#include <assert.h>

CThreadPool::CThreadPool()
{
    m_MaxNum = 50;
    m_AvailLow = 5;
    m_InitNum=m_AvailNum = 10 ;   
    m_AvailHigh = 20;

    m_BusyList.clear();
    m_IdleList.clear();
    for(int i=0;i<m_AvailNum;i++)
    {
	printf("create a thread\n");
	CWorkerThread* thr = new CWorkerThread();
	thr->SetThreadPool(this);
	AppendToIdleList(thr);
	thr->Start();
    }
}

CThreadPool::CThreadPool(int initnum)
{
    assert(initnum>0 && initnum<=30);
    m_MaxNum   = 30;
    m_AvailLow = initnum-10>0?initnum-10:3;
    m_InitNum=m_AvailNum = initnum ;   
    m_AvailHigh = initnum+10;

    m_BusyList.clear();
    m_IdleList.clear();
    for(int i=0;i<m_AvailNum;i++)
    {
	CWorkerThread* thr = new CWorkerThread();
	AppendToIdleList(thr);
	thr->SetThreadPool(this);
	thr->Start();		//begin the thread,the thread wait for job
    }
}

CThreadPool::~CThreadPool()
{
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

CWorkerThread* CThreadPool::GetIdleThread(void)
{
    while(m_IdleList.size() ==0 )
    	m_IdleCond.Wait();
    
    m_IdleMutex.Lock();
    if(m_IdleList.size() > 0 )
    {
	CWorkerThread* thr = (CWorkerThread*)m_IdleList.front();
	printf("Get Idle thread %d\n",thr->GetThreadID());
	m_IdleMutex.Unlock();
	return thr;
    }
    m_IdleMutex.Unlock();

    return NULL;
}

//add an idle thread to idle list
void CThreadPool::AppendToIdleList(CWorkerThread* jobthread)
{
    m_IdleMutex.Lock();
    m_IdleList.push_back(jobthread); 
    m_ThreadList.push_back(jobthread);
    m_IdleMutex.Unlock();
}

//move and idle thread to busy thread 
void CThreadPool::MoveToBusyList(CWorkerThread* idlethread)
{
    m_BusyMutex.Lock();
    m_BusyList.push_back(idlethread);
    m_AvailNum--;
    printf("BusyList size: %d,m_AvailNum %d\n",m_BusyList.size(),m_AvailNum);
    m_BusyMutex.Unlock();
   
    m_IdleMutex.Lock();
    vector<CWorkerThread*>::iterator pos;
    pos = find(m_IdleList.begin(),m_IdleList.end(),idlethread);
    if(pos !=m_IdleList.end())
	m_IdleList.erase(pos);
    m_IdleMutex.Unlock();
}

void CThreadPool::MoveToIdleList(CWorkerThread* busythread)
{
    m_IdleMutex.Lock();
    m_IdleList.push_back(busythread);
    m_AvailNum++;
    printf("IdleList size: %d,m_AvailNum %d\n",m_IdleList.size(),m_AvailNum);
    m_IdleMutex.Unlock();
 
    m_BusyMutex.Lock();
    vector<CWorkerThread*>::iterator pos;
    pos = find(m_BusyList.begin(),m_BusyList.end(),busythread);
    if(pos!=m_BusyList.end())
	m_BusyList.erase(pos);

    m_BusyMutex.Unlock();

    m_IdleCond.Signal();
    m_MaxNumCond.Signal();
}

//create num idle thread and put them to idlelist
void CThreadPool::CreateIdleThread(int num)
{
    for(int i=0;i<num;i++)
    {
	CWorkerThread* thr = new CWorkerThread();
	thr->SetThreadPool(this);
	AppendToIdleList(thr);
	m_VarMutex.Lock();
	m_AvailNum++;
	m_VarMutex.Unlock();
	printf("===============Create A New Thread================\n");
	thr->Start();		//begin the thread,the thread wait for job
    } 
}

void CThreadPool::DeleteIdleThread(int num)
{
    printf("Enter into CThreadPool::DeleteIdleThread\n");
    m_IdleMutex.Lock();
    printf("Delete Num is %d\n",num);
    for(int i=0;i<num;i++)
    {
	CWorkerThread* thr;
	if(m_IdleList.size() > 0 )
	{
            thr = (CWorkerThread*)m_IdleList.front();
            printf("Get Idle thread %d\n",thr->GetThreadID());
	}

	printf("/////////////////Delete Thread %d/////////////\n",thr->GetThreadID());
	vector<CWorkerThread*>::iterator pos;
	pos = find(m_IdleList.begin(),m_IdleList.end(),thr);
	if(pos!=m_IdleList.end())
	    m_IdleList.erase(pos);
	m_AvailNum--;
	printf("The idle thread available num:%d \n",m_AvailNum);
	printf("The idlelist              num:%d \n",m_IdleList.size());
    }
    m_IdleMutex.Unlock();
}
void CThreadPool::Run(CJob* job,void* jobdata)
{
    assert(job!=NULL);
    
    //if the busy thread num adds to m_MaxNum,so we should wait
    if(GetBusyNum() == m_MaxNum)
    {
	printf(")))))))))))))))))All is busy((((((((((((((((((,wait!\n");
	m_MaxNumCond.Wait();
    }

    //if the threads num after creating is also below m_MaxNum
    //so we can create new idle threads,else we needn't create,just to use the idle thread
    printf("GetBusyNum():%d\n",GetBusyNum());
    printf("m_IdleList.size():%d\n",m_IdleList.size());
    printf("m_InitNum:%d\n",m_InitNum);
    printf("GetAllNum()+m_InitNum-m_IdleList.size():%d\n",GetAllNum()+m_InitNum-m_IdleList.size());

    if(m_IdleList.size()<m_AvailLow)
    {
	if(GetAllNum()+m_InitNum-m_IdleList.size() < m_MaxNum )
	{
	    printf("m_IdleList.size() < m_AvailLow,so new thread should be created \n");
	    CreateIdleThread(m_InitNum-m_IdleList.size());
	}
	else
	{
	    CreateIdleThread(m_MaxNum-GetAllNum());
	}
    }

/*
    if(m_IdleList.size()<m_AvailLow && GetAllNum()+m_InitNum-m_IdleList.size()<m_MaxNum)
    {
	printf("m_IdleList.size() < m_AvailLow,so new thread should be created \n");
	CreateIdleThread(m_InitNum-m_IdleList.size());
    }
    else if(m_IdleList.size()<m_AvailLow && m_MaxNum-GetAllNum() < m_AvailLow)
    {
	CreateIdleThread(m_MaxNum-GetAllNum());
    }
*/


    CWorkerThread*  idlethr = GetIdleThread();
    if(idlethr !=NULL)
    {
	idlethr->m_WorkMutex.Lock();
	MoveToBusyList(idlethr);
	idlethr->SetThreadPool(this);
	job->SetWorkThread(idlethr);
	printf("Job is set to thread %d \n",idlethr->GetThreadID());
	idlethr->SetJob(job,jobdata);
    }
}

