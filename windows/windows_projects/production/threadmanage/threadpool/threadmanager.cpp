#include "threadmanager.h"    

CThreadManager * CThreadManager::sm_pManager = NULL;

CThreadManager::CThreadManager(int iThreadNum) : m_pThreadPool(NULL),
                                                 m_iThreadNum(0)
{
    if (1 > iThreadNum)
    {
        m_iThreadNum = 10;
    }
    else
    {
        m_iThreadNum = iThreadNum;
    }

    m_pThreadPool = new CThreadPool(m_iThreadNum);

    if (NULL != m_pThreadPool)
    {
    }
    else
    {
        printf("CThreadManager() new threadpool failed!\n");
    }
}

CThreadManager::~CThreadManager()
{
    if (NULL != m_pThreadPool)
    {
        delete m_pThreadPool;
    }
}

CThreadManager * CThreadManager::Init(int iThreadNum)
{
    if (NULL == sm_pManager)
    {
        sm_pManager = new CThreadManager(iThreadNum);
    }

    return sm_pManager;
}

void CThreadManager::Release()
{
    if (NULL != sm_pManager)
    {
        delete sm_pManager;
        sm_pManager = NULL;
    }
}

void CThreadManager::Run(void)
{
    if (NULL != m_pThreadPool)
    {
        m_pThreadPool->DispatchTask();
    }
};

void CThreadManager::CloseManager()
{
    m_pThreadPool->TeminateAllWorker();

    if (__FAILED == this->Terminate())
    {
        printf("closemanager terminate failed\n");
    }
}

