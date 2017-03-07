#pragma once


#include "template_task.h"
#include "tcprecovery.h"




class CTCPSession : public CAbstractTcp/*CAbstractIOCPTcp*/
{
public:
	CTCPSession()
	{
		m_worker = NULL;
		m_shineUpon = NULL;
	}
	virtual ~CTCPSession()
	{
	}
	
	inline void init(CTaskThread * worker, CChannelManager * shineUpon)
	{
		m_worker = worker;
		m_shineUpon = shineUpon;
	}
protected:
	virtual bool is_reject(void)
	{
		size_t tree_size;
		size_t queue_size;
		m_shineUpon->size(tree_size, queue_size);
		if (m_size <= tree_size)
		{
			LOG(8, "error 连接数超过 %d 当前已连接 %d", m_size, tree_size);
			return true;
		}
		else
		{
			LOG(8, "限制连接数 %d 当前已连接 %d", m_size, tree_size);
		}
		return false;
	}
	virtual void addtree(apr_socket_t * channel, CHANNEL * tc)
	{
		m_shineUpon->add_handle(channel, tc);
	}
	virtual bool check_interrupt_request(void)
	{
		return m_worker->check_interrupt_request();
	}
	virtual void session_close(apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * s)
	{
		apr_status_t rv = APR_SUCCESS;

		rv = Reactor_remove_fd(mp, reactor, s);
		apr_err_print(0, rv, "");

		rv = apr_socket_shutdown(s, APR_SHUTDOWN_READWRITE);
		apr_err_print(0, rv, "");

		CHANNEL * pch;
		if (m_shineUpon->find(s, pch))
			apr_time_exp_lt(&(pch->time_exp), apr_time_now());

		m_shineUpon->recovery(s);
	}

	virtual void start_worker(char * buff, apr_size_t len, apr_socket_t * channel)
	{
		// apr_sockaddr_t * sa;
		// apr_interface_e which = APR_REMOTE;
		// apr_socket_addr_get(&sa, which, channel);
		__QUERY_TICK_COUNT("m_d2_=", m_d2_)
		
		CAbstractTask * p = new __SESSION_TASK__(buff, len, channel);
		
		__QUERY_TICK_COUNT("m_d3_=", p->m_d3_)
			
		p->m_d0_ = m_d0_;
		p->m_d1_ = m_d1_;
		p->m_d2_ = m_d2_;
		
		m_worker->get_manager()->dispatch(p);
		
		//p->m_d3_ = QUERY_TICK_COUNT("m_d3_=");
	}
	
protected:
	CChannelManager * m_shineUpon;
	CTaskThread *		m_worker;
	
};









class CTCPSessionRecovery : public CAbstractRecoveryTcp
{
public:
	CTCPSessionRecovery() : m_worker(NULL)
	{
		
	}
	virtual ~CTCPSessionRecovery()
	{
		
	}
	void set_worker(CTaskThread * worker)
	{
		m_worker = worker;
	}
	static void clear_channel_tree(void * task, void * data)
	{
		CChannelManager * su = (CChannelManager*)data;
		if (task)
		{
			apr_socket_t * channel = (apr_socket_t*)task;
			apr_socket_shutdown(channel, APR_SHUTDOWN_READWRITE);
			su->recovery(channel);
		}
	}
protected:
	
	virtual bool check_interrupt_request(void)
	{
		return m_worker->check_interrupt_request();
	}
	
	virtual void remove_channel(CHANNEL * tc);
	virtual void clear_recovery(void);
	
private:
	CTaskThread * m_worker;
	
};




class CRecoveryTask : public CAbstractTask
{
public:
	CRecoveryTask(CChannelManager * shineUpon)
	{
		m_session_recovery.init(shineUpon);
		//m_shineUpon = shineUpon;
	}
	virtual ~CRecoveryTask()
	{
		
	}
	
	//定时清理线程
	void start(void * data)
	{
		m_session_recovery.set_worker(m_worker);
		m_session_recovery.run();
	}
	
protected:
	CTCPSessionRecovery m_session_recovery;
};




class CTCPSessionTask : public CAbstractTask
{
public:
	CTCPSessionTask(CChannelManager * shineUpon, int listen_port = 9198, apr_interval_time_t timeout = 50 * APR_USEC_PER_SEC , int size = 1024/*512*/)
	{
		m_shineUpon = shineUpon;
		m_listen_port = listen_port;
		m_timeout = timeout;
		m_size = size;
	}
	virtual ~CTCPSessionTask()
	{
	}
	
	inline apr_socket_t * get_acceptor(void)
	{
		return m_session.get_acceptor();
	}
	inline apr_pollset_t * get_reactor(void)
	{
		return m_session.get_reactor();
	}
	
	void start(void * data)
	{
		apr_interval_time_t timeout	= m_worker->get_timeout();
		
		LOG(0, "thread[%d][%p][%p]_run_CTCPSessionTask->begin[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
		
		m_session.init(m_worker, m_shineUpon);
		apr_status_t rv = m_session.run((void *)&m_session, m_manager->get_pool(), m_timeout, m_listen_port, m_size);
		
		if (APR_SUCCESS != rv)
		{
			LOG(8, "session start failed");
		}
		LOG(0, "thread[%d][%p][%p]_run_CTCPSessionTask->end[%d]", m_worker->get_thread_id(), m_worker, m_manager, timeout);
	}
	
protected:
	apr_interval_time_t m_timeout;
	int m_listen_port;
	int m_size;
	CTCPSession m_session;
	CChannelManager * m_shineUpon;
};
