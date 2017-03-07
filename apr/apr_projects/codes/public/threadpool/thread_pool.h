#pragma once


#include "task_manager.h"



class CTaskManager
{
public:
	CTaskManager();
	virtual ~CTaskManager();
	
	void create(apr_pool_t * mp, int thread_num, int limite_num = 0);
	void join(void);
	void stop(void);
	void clear_task(void);
	
	inline void dispatch(CAbstractTask * task) { m_thread_manager.dispatch(task); }

protected:
	CThreadManager	m_thread_manager;
	CTaskThread		m_task_thread;
};