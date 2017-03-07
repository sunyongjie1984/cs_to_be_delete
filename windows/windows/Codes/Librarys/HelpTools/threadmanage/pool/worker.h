#ifndef _WORKER_H_
#define _WORKER_H_


#include "../thread/thread.h"
#include "task.h"
#include "threadmanager.h"



class __EXPORT_DLL CWorker : public CThread
{
public:
	CWorker();
	CWorker(CThreadManager * pManager);

	virtual ~CWorker();


	void AcceptTask(CBTask * pTask);
	CBTask * GetAlreadyAcceptedTask(void) { return m_pTask; }

	inline void ReleaseTask();

	virtual void Quit();

private:
	virtual int Run(ThreadPara * pThreadData);


private:
	CBTask			* m_pTask;
	CThreadManager	* m_pManager;
};

#endif//_WORKER_H_