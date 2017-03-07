#include "worker.h"
#include "threadpool.h"

CThreadPool::CThreadPool(int iWorkerNum)
{
    if (1 > iWorkerNum)
    {
        m_iWorkerNum = 10;
    }
    else
    {
        m_iWorkerNum = iWorkerNum;
    }

    m_WorkerList.clear();
    m_BusyWorkerList.clear();
    m_IdleWorkerList.clear();
    m_TaskList.clear();

    CWorker * pWorkerThread = NULL;

    for (int count = 0; count < m_iWorkerNum; count++)
    {
        pWorkerThread = new CWorker();

        pWorkerThread->SetThreadPool(this);

        AppendToIdleWorkerList(pWorkerThread);

        pWorkerThread->Start();

        int n = iWorkerNum + pWorkerThread->GetConcurrency();

        pWorkerThread->SetConcurrency(n);
    }
}

CThreadPool::~CThreadPool()
{
}

void CThreadPool::AddTask(CTask * pTask)
{
    m_MutexTaskList.Lock();

    m_TaskList.push_back(pTask);

    m_MutexTaskList.Unlock();

    m_WaitingTaskCond.Signal();
}

CTask * CThreadPool::GetWaitingTask(void)
{
    CTask * pTask = NULL;

    while (0 == m_TaskList.size())
    {
        m_WaitingTaskCond.Wait();
    }

    m_MutexTaskList.Lock();

    if (0 < m_TaskList.size())
    {
        pTask = (CTask *)m_TaskList.back();

        DeleteTask(pTask);
    }

    m_MutexTaskList.Unlock();

    return pTask;
}

void CThreadPool::DispatchTask(void)
{
    CWorker * pIdleWorker = NULL;

    while (true)
    {
        pIdleWorker = GetIdleWorker();

        CTask * pTask = GetWaitingTask();

        if (NULL != pTask)
        {
            pIdleWorker->SetThreadPool(this);

            pIdleWorker->m_WorkMutex.Lock();

            pIdleWorker->SetTask(pTask, NULL);

            pIdleWorker->SetThreadPool(this);

            pTask->SetWorkThread(pIdleWorker);
        }
        else
        {
            printf("cthreadpool::run ptask == NULL\n");
            break;
        }
    }
}


void CThreadPool::TeminateAllWorker(void)
{
    CWorker * p = NULL;

    int size = m_WorkerList.size();

    for (int i = 0; i < size; i++)
    {
        p = m_WorkerList[i];

        if (__FAILED == p->Terminate())
        {
            printf("TeminateAllWorker terminate failed\n");
        }
    }
}


CWorker * CThreadPool::GetIdleWorker(void)
{
    CWorker * pWorker = NULL;

    while (0 == m_IdleWorkerList.size())
    {
        m_IdleCond.Wait();
    }

    m_MutexIdleList.Lock();

    if (0 < m_IdleWorkerList.size())
    {
        pWorker = (CWorker *)m_IdleWorkerList.front();
    }

    m_MutexIdleList.Unlock();

    return pWorker;
}

void CThreadPool::WaitAll(void)
{
    CWorker * p = NULL;

    int size = m_WorkerList.size();

    for (int i = 0; i < size; i++)
    {
        p = m_WorkerList[i];

        p->Wait();
    }
}

void CThreadPool::AppendToIdleWorkerList(CWorker * pWorker)
{
    m_MutexIdleList.Lock();

    m_WorkerList.push_back(pWorker);

    m_IdleWorkerList.push_back(pWorker);

    m_MutexIdleList.Unlock();

    m_IdleCond.Signal();
}

void CThreadPool::RemoveListNode(std::vector<CWorker *> &list, CWorker * p)
{
    typedef std::vector<CWorker *>::iterator ITR;

    ITR pos = find(list.begin(), list.end(), p);

    if (pos != list.end())
    {
        list.erase(pos);
    }
}

void CThreadPool::MoveToBusyWorkerList(CWorker * pIdleWorker)
{
    m_MutexIdleList.Lock();

    RemoveListNode(m_IdleWorkerList, pIdleWorker);

    m_MutexIdleList.Unlock();

    m_MutexBusyList.Lock();

    m_BusyWorkerList.push_back(pIdleWorker);

    m_MutexBusyList.Unlock();
}

void CThreadPool::MoveToIdleWorkerList(CWorker * pBusyWorker)
{
    m_MutexBusyList.Lock();

    RemoveListNode(m_BusyWorkerList, pBusyWorker);

    m_MutexBusyList.Unlock();

    m_MutexIdleList.Lock();

    m_IdleWorkerList.push_back(pBusyWorker);

    m_MutexIdleList.Unlock();
 
    m_IdleCond.Signal();
}

int CThreadPool::DeleteTask(CTask * pTask)
{
    int ret = 0;

    if(0 == m_TaskList.size())
    {
         return __FAILED;
    }

    typedef std::vector<CTask *>::iterator ITR;

    ITR pos = find(m_TaskList.begin(), m_TaskList.end(), pTask);

    if(pos != m_TaskList.end())
    {
        m_TaskList.erase(pos);
    }

    return __SUCCESS;
}

