#ifndef _WORKER_H_
#define _WORKER_H_

#include "../baseclass/threadbase.h"
#include "task.h"
#include "threadPool.h"

class CWorker : public CThreadBase
{
public:
    CWorker();
    virtual ~CWorker();

public:
    void Run(void);
    void SetTask(CTask * pTask, void * pTaskData);
    void SetThreadPool(CThreadPool * pThreadPool);
    void WakeUp(CTask * pTask, void * pTaskData);

public:
    inline  CTask * GetTask(void)
    {
        return m_pTask;
    };

    inline  CThreadPool * GetThreadPool(void)
    {
        return m_pThreadPool;
    };

    inline  bool IsWorking(void)
    {
        return m_pTask != NULL;
    };

public:
    CThreadMutex m_WorkMutex;
    CCondition   m_TaskCond;

private:
    CThreadPool * m_pThreadPool;
    CTask *       m_pTask;

    void *        m_pTaskData;
    CThreadMutex  m_DispatchMutex;
    bool          m_bIsEnd;
};

#endif//_WORKER_H_

