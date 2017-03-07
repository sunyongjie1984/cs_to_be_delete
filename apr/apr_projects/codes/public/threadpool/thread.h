#pragma once


#include <apr_thread_proc.h>
#include "lock.h"


class CAbstractThread
{
public:
	CAbstractThread();
	virtual ~CAbstractThread();
	
	apr_status_t create(apr_pool_t * mp);

	apr_status_t join(void);

	inline static void release(CAbstractThread * obj)
	{
		if (obj) {
			obj->join();
			delete obj;
			obj = NULL;
		}
	}
	inline long get_thread_id(void)
	{
		return m_thread_id;
	}
	inline void set_thread_id(int id)
	{
		m_thread_id = id;
	}
protected:
	virtual void run(void) = 0;
	
	static void * APR_THREAD_FUNC __entry(apr_thread_t * th, void * data);
	
	void init(void);
	void fini(void);

protected:
	bool				m_createFlag;
	apr_thread_t *		m_thread;
	apr_threadattr_t *	m_threadAttr;
	apr_pool_t			* m_mp_thread;

	
private:
	long m_thread_id;
};
