#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "../baseclass/threadbase.h"
#include "task.h"

class CWorker;

class CThreadPool
{
    friend class CWorker;

public:
    CThreadPool(int iWorkerNum);
    virtual ~CThreadPool();

    void    AddTask(CTask * pTask);
    void    DispatchTask(void);
    void    WaitAll(void);
    void    TeminateAllWorker(void);

protected:
    CWorker * GetIdleWorker(void);

    void    AppendToIdleWorkerList(CWorker * pWorker);
    void    MoveToBusyWorkerList(CWorker * pIdleWorker);
    void    MoveToIdleWorkerList(CWorker * pBusyWorker);

    CTask * GetWaitingTask(void);

    int     DeleteTask(CTask * pTask);

private:
    void RemoveListNode(std::vector<CWorker *> &list, CWorker * p);

public:
    std::vector<CWorker *> m_WorkerList;
    std::vector<CWorker *> m_BusyWorkerList;
    std::vector<CWorker *> m_IdleWorkerList;
    std::vector<CTask *>   m_TaskList;

public:
    CThreadMutex m_MutexBusyList;
    CThreadMutex m_MutexIdleList;
    CThreadMutex m_MutexTaskList;

    CCondition m_BusyCond;
    CCondition m_IdleCond;
    CCondition m_WaitingTaskCond;

private:
    int m_iWorkerNum;
};

#endif//_THREAD_POOL_H_

