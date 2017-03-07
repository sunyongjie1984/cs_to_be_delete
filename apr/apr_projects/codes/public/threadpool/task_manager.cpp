#include "task_manager.h"



// 
// #include "stdarg.h"
// 
// __PRINT g_printf_func = NULL;
// 
// int g_log_print_level;
// 
// inline void __cdecl LOG(const int level, const char * f, ...)
// {
// 	if (level > g_log_print_level)
// 	{
// 		va_list _va_list;
// 		/* 初始化变长参数列表 */
// 		va_start(_va_list, f);
// 		char buf[BUFSIZE] = {0};
// 
// 		apr_time_exp_t now;
// 		apr_time_exp_lt(&now, apr_time_now());
// 
// 		sprintf(buf, "%.2d/%.2d %.2d:%.2d:%.2d:%d ", now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, now.tm_usec);
// 		int len = vsprintf(buf + strlen(buf), f, _va_list);
// 		va_end(_va_list);
// 		
// 		if (g_printf_func)
// 			g_printf_func(buf);
// 	}
// }








CThreadManager::CThreadManager()
{
	init();
}
CThreadManager::~CThreadManager()
{
	fini();
}
void CThreadManager::create(apr_pool_t * mp)
{
	m_mp = mp;
	
	m_task_queue.init(mp);
	m_create_sem.create(mp);

	m_handle_manager.create(mp);
}

void CThreadManager::add_thread_handle(CAbstractThread * handle)
{
	m_handle_manager.add_handle(handle, handle);
}

void CThreadManager::recovery_thread_handle(CAbstractThread * aw)
{
	m_handle_manager.recovery(aw);
	m_create_sem.start();
}

apr_status_t CThreadManager::await_create_sem(apr_interval_time_t timeout/* = -1*/)
{
	return m_create_sem.await(timeout);
}

void CThreadManager::clear_task_queue(void *task, void * data/* = NULL*/)
{
	CAbstractTask::release((CAbstractTask *)task);
}

void CThreadManager::start_create_sem(void)
{
	m_create_sem.start();
}

apr_status_t CThreadManager::pop_front_handle(CAbstractThread* &handle, apr_interval_time_t timeout/* = -1*/)
{
	return m_handle_manager.pop_front(handle, timeout);
}

int CThreadManager::get_handle_size(void)
{
	return m_handle_manager.get_handle_size();
}


void CThreadManager::clear_task(void)
{
	m_task_queue.clear(clear_task_queue);
}

void CThreadManager::get_handle_size(size_t &tree_size, size_t &queue_size)
{
	m_handle_manager.size(tree_size, queue_size);
}

int CThreadManager::get_task_size(void)
{
	return m_task_queue.size();
}

void CThreadManager::handle_interrupt_request(int num)
{
	m_handle_manager.interrupt_request(num);
}

void CThreadManager::task_interrupt_request(int num)
{
	m_task_queue.interrupt_request(num);
}

void CThreadManager::set_exit_status(bool f, apr_interval_time_t timeout/* = 0*/)
{
	m_timeout = timeout;
	m_exit_status = f;
}

void CThreadManager::dispatch_exit(CAbstractTask * task)
{
	m_task_queue.push_front(task);
	m_create_sem.start();
}

void CThreadManager::init(void)
{
	m_exit_status = false;
	m_thread_count = 0;
}
void CThreadManager::fini(void)
{
	m_exit_status = true;
}




CTaskThread::CTaskThread()
{
	init();
}
CTaskThread::~CTaskThread()
{
	fini();
}

apr_status_t CTaskThread::create(apr_pool_t * mp, CThreadManager &manager, apr_interval_time_t timeout/* = -1*/)
{
	m_timeout = timeout;
	m_manager = &manager;
	return CAbstractThread::create(mp);
}

void CTaskThread::run(void)
{
	CAbstractTask				* task		 = NULL;
	CTaskQueue<CAbstractTask *> * task_queue = m_manager->get_task_queue();
	int pri_th = (int)this;

	LOG(0, "thread[%d][%p][%p]->begin[%d]", this->get_thread_id(), pri_th, m_manager, m_timeout);
	
	while (!check_interrupt_request())
	{
		task = NULL;

		//LOG(8, "TASK_QUEUE = %d", task_queue->size());
		if (APR_SUCCESS == task_queue->pop_front(task, m_timeout))
		{
			//LOG(8, "TASK_QUEUE pop_front = %d", task_queue->size());
			if (task)
			{
				task->set_handle(m_manager, this);
				task->start();
				CAbstractTask::release(task);
			}
		}
		else
		{
			break;
		}
	}
	m_manager->recovery_thread_handle(this);

	LOG(0, "thread[%d][%p][%p]->end[%d]", this->get_thread_id(), pri_th, m_manager, m_timeout);
}

void CTaskThread::init(void)
{
	m_manager	= NULL;
	m_timeout	= -1;
}
void CTaskThread::fini(void)
{
	m_manager	= NULL;
	m_timeout	= -1;
}