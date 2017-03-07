#include "worker.h"
#include "../../debuglog/debuglog.h"


CWorker::CWorker() : m_pTask(NULL),
					 m_pManager(NULL)
{

}



CWorker::CWorker(CThreadManager * pManager) : m_pTask(NULL),
											  m_pManager(NULL)
{
	m_pManager = pManager;
	std::string strWorkerName;
	strWorkerName = strWorkerName + m_pManager->GetThreadName() + "Worker";
	SetThreadName(strWorkerName.c_str());
}



CWorker::~CWorker()
{

}



void CWorker::AcceptTask(CBTask * pTask)
{
	m_pTask = pTask;
}



int CWorker::Run(ThreadPara * pThreadData)
{
	int nRet = __SUCCESS;

	InitCondition(FALSE, this, GetCurrentThreadID());

	while (DETECT(nRet = Suspend()))
	{
		m_pTask->TaskEntry(pThreadData);

		SetThreadState(CThread::FINISHED);

		m_pManager->AttemperDoneWorkerToIdleQueue(this);
	}
	return nRet;
}



void CWorker::ReleaseTask()
{
	if (m_pTask)
	{
		delete m_pTask; m_pTask = NULL;
	}
}



void CWorker::Quit()
{
	ReleaseCondition();	Sleep(100);
}
