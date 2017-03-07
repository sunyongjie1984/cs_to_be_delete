#include "lock.h"



CMutex::CMutex()
{
	init();
}
CMutex::CMutex(apr_pool_t * mp)
{
	init();
	create(mp);
}
CMutex::~CMutex()
{
	destroy();
}
apr_status_t CMutex::create(apr_pool_t * mp)
{
	if (!m_createFlag)
	{
		apr_status_t rv = apr_thread_mutex_create(&m_mutex, APR_THREAD_MUTEX_UNNESTED, mp);
		if (APR_SUCCESS == rv)
			m_createFlag = true;
		return rv;
	}
	return 1;
}

void CMutex::init(void)
{
	m_createFlag = false;
	m_mutex = NULL;
}

void CMutex::destroy(void)
{
	if (m_mutex)
	{
		apr_thread_mutex_destroy(m_mutex);;
		m_mutex = NULL;
		m_createFlag = false;
	}
}



CLocker::CLocker()
{
	init();
}
CLocker::CLocker(apr_pool_t * mp)
{
	init();
	create(mp);
}
CLocker::~CLocker()
{
	destroy();
}
apr_status_t CLocker::create(apr_pool_t * mp)
{
	if (!m_createFlag)
	{
		apr_status_t rv	= apr_pool_create(&m_mp_child, mp);
		if (APR_SUCCESS != rv)
			return rv;

		rv = apr_thread_rwlock_create(&m_rwLock, m_mp_child);
		if (APR_SUCCESS == rv)
			m_createFlag = true;
		return rv;
	}
	return 1;
}


void CLocker::init(void)
{
	m_createFlag = false;
	m_rwLock = NULL;
	m_lock_type = _wr;
}

void CLocker::destroy(void)
{
	if (m_rwLock)
	{
		apr_thread_rwlock_destroy(m_rwLock);
		if (m_mp_child)
			apr_pool_destroy(m_mp_child);

		m_rwLock = NULL;
		m_createFlag = false;
	}
}

CCondition::CCondition()
{
	init();
}
CCondition::CCondition(apr_pool_t * mp)
{
	init();
	create(mp);
}
CCondition::~CCondition()
{
	destroy();
}
apr_status_t CCondition::create(apr_pool_t * mp)
{
	if (!m_createFlag)
	{
		m_mutex.create(mp);
		apr_status_t rv = apr_thread_cond_create(&m_cond, mp);
		if (APR_SUCCESS == rv)
			m_createFlag = true;
		return rv;
	}
	return 1;
}

apr_status_t CCondition::await(apr_interval_time_t timeout/* = -1*/)
{
	CLock<CMutex> m(m_mutex);
	return apr_thread_cond_timedwait(m_cond, m_mutex.get(), timeout);
}
void CCondition::start(void)
{
	//CLock<CMutex> m(m_mutex);
	apr_thread_cond_broadcast(m_cond);
	
}

void CCondition::init(void)
{
	m_createFlag = false;
	m_cond = NULL;
}

void CCondition::destroy(void)
{
	if (m_cond)
	{
		apr_thread_cond_broadcast(m_cond);
		apr_thread_cond_destroy(m_cond);
		m_cond = NULL;
		m_createFlag = false;
	}
}

CSemaphore::CSemaphore()
{
	init();
}
CSemaphore::CSemaphore(apr_pool_t * mp, int value/* = 0*/)
{
	init();
	create(mp, value);
}
CSemaphore::~CSemaphore()
{
	destroy();
}
apr_status_t CSemaphore::create(apr_pool_t * mp, int value/* = 0*/)
{
	if (!m_createFlag)
	{
		m_cond_count = value;
		m_mutex.create(mp);
		apr_status_t rv = apr_thread_cond_create(&m_cond, mp);
		if (APR_SUCCESS == rv)
			m_createFlag = true;
		return rv;
	}
	return 1;
}

apr_status_t CSemaphore::await(apr_interval_time_t timeout/* = -1*/)
{
	apr_status_t rv = APR_SUCCESS;
	CLock<CMutex> m(m_mutex);
	
	if (1 > m_cond_count)
		if (0 <= timeout)
			rv = apr_thread_cond_timedwait(m_cond, m_mutex.get(), timeout);
		else
			rv = apr_thread_cond_wait(m_cond, m_mutex.get());
		
		if (0 < m_cond_count)
			m_cond_count--;
		
		return rv;
}
void CSemaphore::start(void)
{
	CLock<CMutex> m(m_mutex);
	apr_thread_cond_broadcast(m_cond);
	m_cond_count++;
}

void CSemaphore::init(void)
{
	m_createFlag = false;
	m_cond_count = 0;
	m_cond = NULL;
}

void CSemaphore::destroy(void)
{
	if (m_cond)
	{
		apr_thread_cond_broadcast(m_cond);
		apr_thread_cond_destroy(m_cond);
		m_cond = NULL;
		m_createFlag = false;
		m_cond_count = 0;
	}
}