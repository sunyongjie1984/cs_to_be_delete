#include "worker.h"

CWorker::CWorker() : m_pTask(NULL),
                     m_pTaskData(NULL),
                     m_pThreadPool(NULL),
                     m_bIsEnd(false)
{
}

CWorker::~CWorker()
{
    if (NULL != m_pTask)
    {
        delete m_pTask;
    }
    if (NULL != m_pThreadPool)
    {
        delete m_pThreadPool;
    }
}

void CWorker::Run(void)
{
    while (true)
    {
        while(NULL == m_pTask)
        {
            m_TaskCond.Wait();
        }

        if (NULL == m_pTask)
        {
            m_WorkMutex.Unlock();
            break;
        }

        m_pThreadPool->MoveToBusyWorkerList(this);

        m_pTask->Run(m_pTaskData);

        m_pTask->SetWorkThread(NULL);

        m_pTask = NULL;

        m_WorkMutex.Unlock();

        m_pThreadPool->MoveToIdleWorkerList(this);
    }
}

void CWorker::SetTask(CTask * pTask, void * pTaskData)
{
    m_DispatchMutex.Lock();

    m_pTask = pTask;

    m_pTaskData = pTaskData;

    m_DispatchMutex.Unlock();

    m_TaskCond.Signal();
}

void CWorker::SetThreadPool(CThreadPool * pThreadPool)
{
    m_DispatchMutex.Lock();

    m_pThreadPool = pThreadPool;

    m_DispatchMutex.Unlock();
}

void CWorker::WakeUp(CTask * pTask, void * pTaskData)
{
    m_WorkMutex.Lock();

    SetTask(pTask, pTaskData);

    pTask->SetWorkThread(this);

    m_WorkMutex.Unlock();
    
    m_TaskCond.Signal();
}

