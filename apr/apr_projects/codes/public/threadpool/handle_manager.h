#pragma once

#pragma warning( disable:4005)
#pragma warning( disable:4503)
#pragma warning( disable:4786)

#include "queue.h"



template<typename _I, typename _T>
class CHandleManager
{
public:
	CHandleManager()
	{
		m_handle_num = 0;
	}
	virtual ~CHandleManager()
	{
		
	}
	void create(apr_pool_t * mp)
	{
		m_recovery_queue.init(mp);
		m_handle_tree.init(mp);
		m_recovery_sem.create(mp);
	}
	
	inline apr_status_t await_recovery(apr_interval_time_t timeout = -1)
	{
		return m_recovery_sem.await(timeout);
	}
	void add_handle( _I &index, _T &data)
	{
		if (m_handle_tree.insert(index, data))
			++m_handle_num;
	}
	bool find(_I &index, _T &data)
	{
		return m_handle_tree.find(index, data);
	}
	void recovery(_I &index)
	{
		_T data;
		if (m_handle_tree.remove(index, data))
			m_recovery_queue.push_back(data);
		m_recovery_sem.start();
	}
	void push_front(const _T &data)
	{
		m_recovery_queue.push_front(data);
	}
	apr_status_t pop_front(_T &data, apr_interval_time_t timeout = -1)
	{
		apr_status_t rv = m_recovery_queue.pop_front(data, timeout);
		if (APR_SUCCESS == rv)
		{
			--m_handle_num;
		}
		return rv;
	}
	void clear(__CLEAR_TASK_FUNC clear_func, void * data = NULL)
	{
		m_handle_tree.clear(clear_func, data);
	}
	void size(size_t &tree_size, size_t &queue_size)
	{
		tree_size = m_handle_tree.size();
		queue_size = m_recovery_queue.size();
	}
	int get_handle_size(void)
	{
		return m_handle_num;
	}
	void interrupt_request(int num)
	{
		m_recovery_queue.interrupt_request(num);
	}
protected:
	CTaskQueue<_T>	m_recovery_queue;
	CTree<_I, _T>	m_handle_tree;
	CSemaphore		m_recovery_sem;
	int				m_handle_num;
private:
};
