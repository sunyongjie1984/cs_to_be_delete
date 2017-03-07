#pragma once


#include <apr_pools.h>
#include <apr_thread_rwlock.h>
#include <apr_thread_cond.h>


class CLockTest
{
public:
	CLockTest()
	{
		m_lockFlag = false;
	}
	~CLockTest()
	{
		
	}
	
	void lock()
	{
		m_lockFlag = true;
	}
	void unlock()
	{
		m_lockFlag = false;
	}
	void printf()
	{
		if (!m_lockFlag)
		{
			//printf("\nlock_test-------------------\n");
		}
	}
	
protected:
	bool m_lockFlag;
};


enum
{
	_wr = 0,
	_rd,
	_tryrd,
	_trywr
};

class CMutex
{
public:
	CMutex();
	CMutex(apr_pool_t * mp);
	~CMutex();
	apr_status_t create(apr_pool_t * mp);

	inline void set_type(int lock_type = _wr)
	{
	}

	inline void lock(void)					{ apr_thread_mutex_lock(m_mutex);   }
	inline void unlock(void)				{ apr_thread_mutex_unlock(m_mutex); }
	inline apr_thread_mutex_t * get(void)	{ return m_mutex;					}

protected:
	void init(void);

	void destroy(void);
protected:
	apr_thread_mutex_t *	m_mutex;
	bool					m_createFlag;
};

class CLocker
{
public:

	CLocker();
	CLocker(apr_pool_t * mp);
	~CLocker();
	apr_status_t create(apr_pool_t * mp);

	inline void set_type(int lock_type = _wr)
	{
		m_lock_type = lock_type;
	}

	inline void lock(void)
	{
		switch (m_lock_type)
		{
		case _wr:
			apr_thread_rwlock_wrlock(m_rwLock);
			break;
		case _rd:
			apr_thread_rwlock_rdlock(m_rwLock);
			break;
		case _tryrd:
			apr_thread_rwlock_tryrdlock(m_rwLock);
			break;
		case _trywr:
			apr_thread_rwlock_trywrlock(m_rwLock);
			break;
		}
	}
	inline void unlock(void)
	{
		apr_thread_rwlock_unlock(m_rwLock);
	}

protected:
	void init(void);
	void destroy(void);
protected:
	apr_thread_rwlock_t * m_rwLock;
	bool				m_createFlag;
	int					m_lock_type;
	apr_pool_t			* m_mp_child;
};

template<typename _T>
class CLock
{
public:
	CLock(_T &locker, int lock_type = _wr)
	{
		m_locker = &locker;
		m_locker->set_type(lock_type);
		m_locker->lock();
	}
	~CLock()
	{
		m_locker->unlock();
	}
protected:
	_T * m_locker;
};

class CCondition
{
public:
	CCondition();
	CCondition(apr_pool_t * mp);
	~CCondition();
	apr_status_t create(apr_pool_t * mp);

	apr_status_t await(apr_interval_time_t timeout = -1);
	void start(void);

protected:
	void init(void);
	void destroy(void);

protected:
	apr_thread_cond_t * m_cond;
	CMutex				m_mutex;
	bool				m_createFlag;
};

class CSemaphore
{
public:
	CSemaphore();
	CSemaphore(apr_pool_t * mp, int value = 0);
	~CSemaphore();
	apr_status_t create(apr_pool_t * mp, int value = 0);
	
	apr_status_t await(apr_interval_time_t timeout = -1);
	void start(void);

protected:
	void init(void);
	void destroy(void);

protected:
	apr_thread_cond_t * m_cond;
	CMutex				m_mutex;
	long				m_cond_count;
	bool				m_createFlag;
};
