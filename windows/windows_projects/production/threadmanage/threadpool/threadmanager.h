#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_

#include "../baseclass/threadbase.h"
#include "threadpool.h"
#include "task.h"

class CThreadManager : public CThreadBase
{
public:
    static CThreadManager * Init(int iThreadNum);
    static void Release();

public:
    inline void AddTask(CTask * pTask)
    {
        if (NULL != m_pThreadPool)
        {
            m_pThreadPool->AddTask(pTask);
        }
    };
    inline void WaitAll(void)
    {
        if (NULL != m_pThreadPool)
        {
            m_pThreadPool->WaitAll();
        }
    };
public:
	void CThreadManager::CloseManager();
private:
    CThreadManager(int iThreadNum);
    virtual ~CThreadManager();
protected:
    void Run(void);

private:
    static CThreadManager * sm_pManager;
private:
    CThreadPool * m_pThreadPool;
    int           m_iThreadNum;
};
#endif//_THREAD_MANAGER_H_

