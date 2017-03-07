#ifndef _TASK_H_
#define _TASK_H_


#include "../thread/thread.h"


class __EXPORT_DLL CBTask
{
	friend class CWorker;

public:
	CBTask();
	virtual ~CBTask();

	void InitTaskData(void * p, int len);
	void * GetTaskData(void);

	inline void SetTaskName(std::string &strTaskName);
	inline std::string GetTaskName(void);

private:
	virtual	int TaskEntry(CThread::ThreadPara * pThreadData	= 0) = 0;

private:
	std::string m_strTaskName;
protected:
	void * m_pTaskData;
};




#endif//_TASK_H_