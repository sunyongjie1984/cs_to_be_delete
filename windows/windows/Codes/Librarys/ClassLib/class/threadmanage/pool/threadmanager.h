#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_


#include "../thread/thread.h"
#include "task.h"
#include "bqueue.h"


class CWorker;

class __EXPORT_DLL CThreadManager : public CThread
{
	friend class CWorker;

public:
	CThreadManager();
	CThreadManager(int nThreadNum);
	virtual ~CThreadManager();

	int			RecruitWorker(int nThreadNum);
	void		AppendTaskQueue(CBTask * pTask);
	int			Active(int nThreadNum);

	template<class T>
	void AppendTask(T &t, void * pData, int len)
	{
		T * p = new T;		*p = t;
		InitTaskData((CBTask *)p, pData, len);
		AppendTaskQueue(p);
	}
	
	void		Quit(void);
protected:
	inline void InitTaskData(CBTask * pTask, void *pData, int len);

private:
	int			DispatchTask(void);
	void		InitQueue();
	void		AppendWorkerQueue(CWorker * pWorker);

	int			AttemperIdleWorkerToBusyQueue(CWorker * pWorker);
	int			AttemperDoneWorkerToIdleQueue(CWorker * pWorker);

	CWorker *	GetIdleWorker(void);
	CBTask  *	GetWaitingTask(void);


	inline void ReleaseTask(CBTask * p);

private:
	virtual int Run(ThreadPara * p);

public:
	CCondition m_IdleWorkerCondition;
	CCondition m_WaitingTaskCondition;


private:
	CBQueue<CWorker *> m_BeingWorkerQueue;
	CBQueue<CWorker *> m_IdleWorkerQueue;
	CBQueue<CWorker *> m_BusyWorkerQueue;
	CBQueue<CBTask  *> m_TaskQueue;

	bool m_bDispatchTaskFlag;
	int m_nThreadNum;
};


template<class T>
class __EXPORT_DLL CTaskManager : public CThreadManager
{
public:
	CTaskManager() { }
	CTaskManager(int nThreadNum);
	virtual ~CTaskManager() { }
	
	void AppendTask(void * pData, int len);
};

template <class T>
CTaskManager<T>::CTaskManager(int nThreadNum) : CThreadManager(nThreadNum)
{
}

template <class T> void
CTaskManager<T>::AppendTask(void * pData, int len)
{
	T * p = new T();
	InitTaskData((T *)p, pData, len);
	AppendTaskQueue(p);
}





#endif//_THREAD_MANAGER_H_