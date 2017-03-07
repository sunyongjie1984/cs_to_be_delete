#include "thread.h"

CAbstractThread::CAbstractThread()
{
	init();
}
CAbstractThread::~CAbstractThread()
{
	fini();
}



apr_status_t CAbstractThread::create(apr_pool_t * mp)
{
	if (!m_createFlag)
	{
		apr_status_t rv	= apr_pool_create(&m_mp_thread, mp);
		if (APR_SUCCESS != rv)
			return rv;

		rv = apr_threadattr_create(&m_threadAttr, m_mp_thread);
		if (APR_SUCCESS != rv)
			return rv;
		
		rv = apr_thread_create(&m_thread, m_threadAttr, CAbstractThread::__entry, (void *)this, m_mp_thread);
		if (APR_SUCCESS != rv)
			return rv;
		else
			m_createFlag = true;
		return rv;
	}
	return 1;
}

apr_status_t CAbstractThread::join(void)
{
	apr_status_t rv;

	apr_thread_join(&rv, m_thread);
	if (m_mp_thread)
		apr_pool_destroy(m_mp_thread);
	return rv;
}

void * APR_THREAD_FUNC CAbstractThread::__entry(apr_thread_t * th, void * data)
{
	CAbstractThread * obj = reinterpret_cast<CAbstractThread*>(data);
	
	if (obj)
		obj->run();
	
	apr_thread_exit(th, APR_SUCCESS);
	return NULL;
}

void CAbstractThread::init(void)
{
	m_createFlag = false;
	m_thread_id = -1;
	m_thread = NULL;
	m_threadAttr = NULL;
	m_mp_thread = NULL;
}
void CAbstractThread::fini(void)
{
	m_createFlag = false;
}