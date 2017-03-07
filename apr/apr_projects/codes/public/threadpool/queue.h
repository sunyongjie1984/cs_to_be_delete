#pragma once


//#pragma warning(push) 

#pragma warning( disable:4005)
#pragma warning( disable:4503)
#pragma warning( disable:4786)

//#pragma warning(pop)

#include <map>
#include <list>
#include <queue>
#include "lock.h"


typedef void (* __CLEAR_TASK_FUNC)(void * task, void * data);


template<typename _I, typename _T>class CTree
{
public:
	CTree()
	{

	}
	~CTree()
	{

	}
	bool find(const _I &index, _T &data)
	{
		bool ret = false;
		CLock<CLocker> l(m_locker, _rd);
		std::map<_I, _T>::iterator itr = m_map.find(index);
		if ((m_map.end() != itr) && (0 < m_map.size()))
		{
			data = itr->second;
			ret = true;
		}
		return ret;
	}
	bool remove(const _I &index, _T &data)
	{
		bool ret = false;
		CLock<CLocker> l(m_locker);
		std::map<_I, _T>::iterator itr = m_map.find(index);
		if ((m_map.end() != itr) && (0 < m_map.size()))
		{
			data = itr->second;
			m_map.erase(itr);
			ret = true;
		}
		return ret;
	}
	inline void clear(__CLEAR_TASK_FUNC clear_func, void * data = NULL)
	{
		CLock<CLocker> l(m_locker);
		std::map<_I, _T>::iterator itr;
		for (itr = m_map.begin(); itr != m_map.end(); itr++)
		{
			if (clear_func)
				clear_func((void *)(itr->second), data);
			itr = m_map.begin();
		}
		m_map.clear();
	}
	bool insert(const _I &index, const _T &data)
	{
		bool ret = false;
		CLock<CLocker> l(m_locker);
		std::map<_I, _T>::iterator itr = m_map.find(index);
		if (m_map.end() == itr)
		{
			std::pair<_I, _T> pr;
			pr.first = index;
			pr.second = data;
			m_map.insert(pr);
			ret = true;
		}
		return ret;
	}
	bool update(const _I &index, const _T &data)
	{
		bool ret = false;
		CLock<CLocker> l(m_locker);
		std::map<_I, _T>::iterator itr = m_map.find(index);
		if ((m_map.end() != itr) && (0 < m_map.size()))
		{
			itr->second = data;
			ret = true;
		}
		return ret;
	}
	inline size_t size(void)
	{
		//CLock<CLocker> l(m_locker, _rd);
		return m_map.size();
	}
	void init(apr_pool_t * mp)
	{
		m_map.clear();
		m_locker.create(mp);
		//m_semaphore.create(mp);
	}
private:
	CLocker				m_locker;
	//CSemaphore			m_semaphore;
	std::map<_I, _T>	m_map;
};



template<typename _T> class CTaskQueue
{
public:
	CTaskQueue() : /*m_timeout(-1), */m_interrupt_request(false)
	{
		
	}
	~CTaskQueue()
	{
	}
	void init(apr_pool_t * mp)
	{
		m_list.clear();
		m_locker.create(mp);
		m_semaphore.create(mp);
	}
	inline void push_back(const _T &data)
	{
		CLock<CLocker> l(m_locker);
		m_list.push_back(data);
		m_semaphore.start();
	}
	inline void push_back_only(const _T &data)
	{
		CLock<CLocker> l(m_locker);
		std::list<_T>::iterator itr = m_list.begin();
		int len  = m_list.size();
		for (int i = 0; (i < len) && (itr != m_list.end()); i++)
		{
			if (*itr == data)
				return;
			else
				itr++;
		}
		m_list.push_back(data);
		m_semaphore.start();
	}
	inline void push_front(const _T &data)
	{
		CLock<CLocker> l(m_locker);
		m_list.push_front(data);
		m_semaphore.start();
	}
	inline void interrupt_request(int num/*, apr_interval_time_t timeout = 0*/)
	{
		m_interrupt_request = true;
		//m_timeout = timeout;
		for (int i=0; i<num; i++)
			m_semaphore.start();
	}

	inline apr_status_t pop_front(_T &data, apr_interval_time_t timeout = -1)
	{
		apr_status_t  rv = APR_SUCCESS;
		//m_timeout = timeout;
		while (true) {
			rv = -1;
			if (1 > front(data)) {	//apr_sleep(timeout / 2);
				if (APR_TIMEUP == (rv = m_semaphore.await(timeout)))
					return -1;
				else if (m_interrupt_request)
					return -1;
			} else {
				rv = APR_SUCCESS;
				break;
			}
		}
		return rv;
	}

	inline void remove(const _T &where)
	{
		CLock<CLocker> l(m_locker);
		for (std::list<_T>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)
		{
			if (*itr == where)
			{
				m_list.erase(itr);
			}
		}
	}
	inline bool find(const _T &where)
	{
		CLock<CLocker> l(m_locker, _rd);
		for (std::list<_T>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)
		{
			if (*itr == where)
			{
				return true;
			}
		}
		return false;
	}
	
	inline void clear(__CLEAR_TASK_FUNC clear_func, void * data = NULL)
	{
		CLock<CLocker> l(m_locker);
		for (std::list<_T>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)
		{
			clear_func((void *)(*itr), data);
		}
		m_list.clear();
	}
	inline size_t size(void)
	{
		//CLock<CLocker> l(m_locker, _rd);
		return m_list.size();
	}
protected:
	inline size_t front(_T &data)
	{
		size_t ret = -1;

		CLock<CLocker> l(m_locker);
		std::list<_T>::iterator itr = m_list.begin();
		if (itr != m_list.end())
		{
			ret = m_list.size();
			data = *itr;
			m_list.erase(itr);
		}
		else
		{
			ret = m_list.size();
		}
		return ret;
	}
private:
	CLocker				m_locker;
	CSemaphore			m_semaphore;
	std::list<_T>		m_list;
	bool				m_interrupt_request;
};

