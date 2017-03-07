#include "threadmanager.h"
#include "worker.h"




CThreadManager::CThreadManager()
{
	InitQueue();

}



CThreadManager::CThreadManager(int nThreadNum)
{
	InitQueue();
	RecruitWorker(nThreadNum);
}



CThreadManager::~CThreadManager()
{
	Quit();
}



int CThreadManager::RecruitWorker(int nThreadNum)
{
	CWorker * pWorker = NULL;

	m_nThreadNum = 0 >= nThreadNum ? 10 : nThreadNum;
	
	for (int i = 0; i < m_nThreadNum; i++)
	{
		pWorker = new CWorker(this);

		AppendWorkerQueue(pWorker);

		pWorker->Start();
	}
	return __SUCCESS;
}



void CThreadManager::InitQueue()
{
	m_BusyWorkerQueue.InitQueue();

	m_IdleWorkerQueue.InitQueue();

	m_TaskQueue.InitQueue();
}



int	CThreadManager::Active(int nThreadNum)
{
	RecruitWorker(nThreadNum);

	return CThread::Start();
}



int CThreadManager::Run(ThreadPara * p)
{
	return DispatchTask();
}



int CThreadManager::DispatchTask(void)
{
	CWorker * pIdleWorker	= NULL;
	CBTask  * pWaitingTask	= NULL;

	m_bDispatchTaskFlag		= true;

    while (m_bDispatchTaskFlag)
    {
        pIdleWorker  = GetIdleWorker();
        pWaitingTask = GetWaitingTask();

        if ((NULL != pWaitingTask)&&(NULL != pIdleWorker))
        {
			pIdleWorker->AcceptTask(pWaitingTask);

			AttemperIdleWorkerToBusyQueue(pIdleWorker);
        }
        else
        {
            break;
        }
    }
	return __SUCCESS;
}



int CThreadManager::AttemperIdleWorkerToBusyQueue(CWorker * pWorker)
{
	if (DETECT(m_IdleWorkerQueue.RemoveQueueNode(pWorker)))
	{
		m_BusyWorkerQueue.AppendQueue(pWorker);

		pWorker->IsSetWakeUp(false);

		return __SUCCESS;
	}
	return __FAILED;
}



int CThreadManager::AttemperDoneWorkerToIdleQueue(CWorker * pWorker)
{
	if (DETECT(m_BusyWorkerQueue.RemoveQueueNode(pWorker)))
	{
		m_IdleWorkerQueue.AppendQueue(pWorker);
		
		if (0 != m_IdleWorkerQueue.GetQueueSize())
		{
			ReleaseTask(pWorker->GetAlreadyAcceptedTask());

			m_IdleWorkerCondition.IsSetWakeUp(false);			
		}
		return __SUCCESS;
	}
	return __FAILED;
}



void CThreadManager::AppendWorkerQueue(CWorker * pWorker)
{
	m_IdleWorkerQueue.AppendQueue(pWorker);
	m_BeingWorkerQueue.AppendQueue(pWorker);
	
	if (0 != m_IdleWorkerQueue.GetQueueSize())
	{
		m_IdleWorkerCondition.IsSetWakeUp(false);
	}
}



void CThreadManager::AppendTaskQueue(CBTask * pTask)
{
	if (m_bDispatchTaskFlag)
	{
		m_TaskQueue.AppendQueue(pTask);

		if (0 != m_TaskQueue.GetQueueSize())
		{
			m_WaitingTaskCondition.IsSetWakeUp(false);
		}
	}
}



CWorker * CThreadManager::GetIdleWorker(void)
{
	CWorker * pWorker = NULL;

	m_IdleWorkerCondition.Init(
								FALSE,
								(void *)this,
								GetCurrentThreadID()
								);

	while (0 == m_IdleWorkerQueue.GetQueueSize())
    {
        m_IdleWorkerCondition.Suspend();
    }
	return m_IdleWorkerQueue.GetQueueFrontNode();
}



CBTask * CThreadManager::GetWaitingTask(void)
{
	CBTask * pTask = NULL;

	m_WaitingTaskCondition.Init(
								FALSE,
								(void *)this,
								GetCurrentThreadID()
								);

	while (0 == m_TaskQueue.GetQueueSize())
    {
        m_WaitingTaskCondition.Suspend();
    }
	pTask = m_TaskQueue.GetQueueFrontNode();

	m_TaskQueue.RemoveQueueNode(pTask);

	return pTask;
}



void CThreadManager::InitTaskData(CBTask * pTask, void *pData, int len)
{
	pTask->InitTaskData(pData, len);
}



void CThreadManager::ReleaseTask(CBTask * p)
{
	if (p)
	{
		delete p; p = NULL;
	}
}



void CThreadManager::Quit(void)
{
	m_bDispatchTaskFlag = false;

	int nSum = m_BeingWorkerQueue.GetQueueSize();

	for (int i=0; i < nSum; i++)
	{
		CWorker * pWorker = m_BeingWorkerQueue.GetAt(i);
		if (pWorker)
		{
			pWorker->Quit();
			
			if ((TERMINATED == pWorker->GetThreadState())||
				(FINISHED == pWorker->GetThreadState())||
				(DEAD == pWorker->GetThreadState()))
			{
				delete pWorker;
				pWorker = NULL;
			}
			else
			{
				pWorker->Terminate();
				delete pWorker;
				pWorker = NULL;
			}
		}
	}
	nSum = m_TaskQueue.GetQueueSize();

	for (i=0; i < nSum; i++)
	{
		CBTask * pTask = m_TaskQueue.GetAt(i);
		if (pTask)
		{
			delete pTask;	pTask = NULL;
		}
	}
}