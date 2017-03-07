#pragma once



#include "tcpframe.h"
#include "thread_pool.h"




typedef CHandleManager<apr_socket_t*, CHANNEL*> CChannelManager;


//extern int g_session_count;
//extern int g_session_create_count;
//extern int g_session_destroy_count;


class CAbstractRecoveryTcp
{
protected:
	CChannelManager * m_shineUpon;
	
public:
	CAbstractRecoveryTcp() : m_shineUpon(NULL)
	{
		
	}
	virtual ~CAbstractRecoveryTcp()
	{
		
	}
	void init(CChannelManager * shineUpon)
	{
		m_shineUpon = shineUpon;
	}
	//定时清理线程
	void run()
	{
		size_t tree_size = 0;
		size_t queue_size = 0;
		apr_interval_time_t timeout = 10 * APR_USEC_PER_SEC;
		
		while (true)
		{
			if (APR_TIMEUP != m_shineUpon->await_recovery(timeout))
				LOG(0, "现在有心跳停跳的情况或连接断开" );
			
			//LOG(8, "[当前SESSION数量 %d] [创建数量 %d] [销毁数量 %d]", g_session_count, g_session_create_count, g_session_destroy_count);
			
			clear_recovery();
			
			m_shineUpon->size(tree_size, queue_size);
			if (check_interrupt_request())
			{
				timeout = 0;
				if (1 > m_shineUpon->get_handle_size())
					break;
			}
			for (int i = 0; i < queue_size; i++)
			{
				CHANNEL * tc = NULL;
				if (APR_SUCCESS == m_shineUpon->pop_front(tc, 0))
				{
					if (tc)
					{
						apr_time_exp_t now;
						apr_time_exp_lt(&now, apr_time_now());
						if ((now.tm_mon  != tc->time_exp.tm_mon ) || (now.tm_mday != tc->time_exp.tm_mday) ||
							(now.tm_hour != tc->time_exp.tm_hour) || (now.tm_min  != tc->time_exp.tm_min ) ||
							(now.tm_sec-tc->time_exp.tm_sec > 0))
						{
							remove_channel(tc);
						}
						else
						{
							m_shineUpon->push_front(tc);
						}
					}
				}
			}
		}
	}
	
protected:
	virtual void remove_channel(CHANNEL * tc) = 0;
	virtual bool check_interrupt_request(void) = 0;
	virtual void clear_recovery(void) = 0;
};
