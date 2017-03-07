#include "thread_pool.h"





class CManageTask : public CAbstractTask
{
public:
	
	CManageTask(int thread_num, int limite_num = 0)
	{
		m_max_thread_num		= limite_num;
		m_init_thread_num		= thread_num;
	}
	virtual ~CManageTask()
	{
		
	}
	
	void start(void * data = NULL)
	{
		apr_interval_time_t	timeout = m_worker->get_timeout();

		m_max_thread_num =
			m_init_thread_num>m_max_thread_num ? m_init_thread_num : m_max_thread_num;

		LOG(0, "thread[%d][%p][%p]_run_CManageTask->begin[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
		
		while (true)
		{
			size_t	thread_num		= 0;
			size_t	recovery_num	= 0;

			m_manager->get_handle_size(thread_num, recovery_num);

			size_t	task_num		= m_manager->get_task_size();
			int		len				= task_num + m_init_thread_num - thread_num;
			
			for (int i=0; true; i++)
			{
				m_manager->get_handle_size(thread_num, recovery_num);

				//if ((i<len) && (m_max_thread_num>len) && (!check_interrupt_request()))
				if (((m_init_thread_num > thread_num)||(task_num*2>m_init_thread_num&&thread_num<m_max_thread_num)) && (!check_interrupt_request()))
				{
					CAbstractThread * obj = new CTaskThread();
					obj->set_thread_id(m_manager->m_thread_count++);
					static_cast<CTaskThread*>(obj)->create(m_manager->get_pool(), *m_manager, timeout);
					m_manager->add_thread_handle(obj);
				}
				else
				{
					break;
				}				
			}
			if (check_interrupt_request())
			{
				break;
			}
			m_manager->await_create_sem(m_worker->get_timeout());
			timeout = APR_USEC_PER_SEC * 2;
		}
		LOG(0, "thread[%d][%p][%p]_run_CManageTask->end[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
	}

private:
	int m_init_thread_num;
	int m_max_thread_num;
};

class CRecoveryThreadTask : public CAbstractTask
{
public:
	
	CRecoveryThreadTask()
	{
	}
	virtual ~CRecoveryThreadTask()
	{
		
	}
	void start(void * data = NULL)
	{
		apr_interval_time_t	timeout = m_worker->get_timeout();

		CAbstractThread * obj = new CTaskThread();
		obj->set_thread_id((m_manager->m_thread_count)++);
		/*dynamic_cast*/static_cast<CTaskThread*>(obj)->create(m_manager->get_pool(), *m_manager, timeout);
		m_manager->add_thread_handle(obj);
		
		LOG(0, "thread[%d][%p][%p]_run_CRecoveryThreadTask->begin[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
		
		for (int i=0; true; i++)
		{
			obj = NULL;
			if (APR_SUCCESS == m_manager->pop_front_handle(obj, timeout))
			{
				LOG(0, "thread[%d][%p][%p]_run_CRecoveryThreadTask_release[%d]_=_thread[%d]_time[%d]", m_worker->get_thread_id(), m_worker, m_manager, i, obj->get_thread_id(), timeout);

				CAbstractThread::release(obj);
			}
			else if (check_interrupt_request())
			{
				timeout = m_manager->get_timeout();
				if (1 > m_manager->get_handle_size())
				{
					break;
				}
			}
		}
		LOG(0, "thread[%d][%p][%p]_run_CRecoveryThreadTask->end[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
	}
};

class CExitTask : public CAbstractTask
{
public:
	CExitTask()
	{
	}
	
	virtual ~CExitTask()
	{
	}
	
	void start(void * data)
	{
		apr_interval_time_t timeout	= m_worker->get_timeout();
		
		LOG(0, "thread[%d][%p][%p]_run_CExitTask->begin[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
		
		m_manager->set_exit_status(true);
		m_manager->clear_task();
		m_manager->start_create_sem();
		
		size_t	thread_num		= 0;
		size_t	recovery_num	= 0;
		
		m_manager->get_handle_size(thread_num, recovery_num);

		m_manager->task_interrupt_request(thread_num);
		m_manager->handle_interrupt_request(recovery_num + thread_num);
		
		LOG(0, "thread[%d][%p][%p]_run_CExitTask->end[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
	}
};


CTaskManager::CTaskManager()
{
}
CTaskManager::~CTaskManager()
{
}

void CTaskManager::create(apr_pool_t * mp, int thread_num, int limite_num/* = 0*/)
{
	m_thread_manager.create(mp);
	
	m_task_thread.set_thread_id(m_thread_manager.m_thread_count++);
	m_task_thread.create(mp, m_thread_manager);
	
	CAbstractTask * pRecovery = new CRecoveryThreadTask();
	m_thread_manager.dispatch(pRecovery);
	
	CAbstractTask * pInit = new CManageTask(thread_num, limite_num);
	m_thread_manager.dispatch(pInit);
}

void CTaskManager::join(void)
{
	m_task_thread.join();
}
void CTaskManager::stop(void)
{
	CAbstractTask * task = new CExitTask();
	m_thread_manager.dispatch_exit(task);
}


void CTaskManager::clear_task(void)
{
	m_thread_manager.clear_task();
}




