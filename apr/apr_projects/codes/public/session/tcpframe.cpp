#include "tcpframe.h"




CAbstractTcp::CAbstractTcp() : m_acceptor(NULL), m_reactor(NULL)
{
	
}
CAbstractTcp::~CAbstractTcp()
{
	
}


apr_status_t CAbstractTcp::run(void * data, apr_pool_t * mp, apr_interval_time_t timeout, int listen_port, int size)
{
	apr_status_t	rv = 0;
	m_size = size;
	rv = TCPAcceptor_create(mp, listen_port, &m_acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		rv = Reactor_create(mp, size, &m_reactor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		rv = Reactor_append_fd(mp, m_reactor, m_acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		rv = Reactor_await(mp, m_reactor, m_acceptor, timeout, __reactor_entry, data);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		return Reactor_destroy(m_reactor);
}

bool CAbstractTcp::__is_reject(void * data, apr_socket_t * channel, apr_pool_t * mp_child)
{
	CAbstractTcp *	tcp	= (CAbstractTcp*)data;
	if (tcp->is_reject())
	{
		if (channel)
		{
			apr_socket_close(channel);

			if (mp_child)
			{
				apr_pool_destroy(mp_child);
			}
		}
		return true;
	}
	return false;
}
apr_status_t CAbstractTcp::__accept(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data)
{
	CAbstractTcp *	tcp	= (CAbstractTcp*)data;
	
	CHANNEL * tc = new CHANNEL();
	tc->channel = channel;
	tc->mpchild = mp;
	tcp->addtree(channel, tc);
	
	return -1;
}
apr_status_t CAbstractTcp::__recv(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data)
{
	CAbstractTcp *		tcp						= (CAbstractTcp*)data;
	apr_status_t		rv						= APR_SUCCESS;
	char				buf[__RECV_BUFF_LEN__]	= {0};
	const apr_size_t	lc						= sizeof(buf) - 1;
	apr_size_t			len						= lc;

	char * out_pos;
	int out_len = 0;
	bool read_ret = false;
	
	do
	{
		__QUERY_TICK_COUNT("m_d0_=", tcp->m_d0_);

		len	= lc;
		memset(buf, 0, sizeof(buf));
		rv = apr_socket_recv(channel, buf, &len);

		__QUERY_TICK_COUNT("m_d1_=", tcp->m_d1_);


		do {
			read_ret = tcp->read(&out_pos, &out_len);
			if (read_ret)
				tcp->start_worker(out_pos, out_len, channel);
		} while (read_ret);

		if (0 >= len)
		{
			if (APR_STATUS_IS_EAGAIN(rv))
			{
				//apr_err_print(0, rv, "");
				break;
			}
			else if (APR_SUCCESS != rv && !APR_STATUS_IS_EAGAIN(rv))
			{
				apr_err_print(0, rv, "");
				tcp->session_close(mp, reactor, channel);
			}
			break;
		}
		else/* if (APR_SUCCESS == rv)*/
		{
			if (APR_SUCCESS != rv && !APR_STATUS_IS_EAGAIN(rv))
			{
				apr_err_print(0, rv, "");
				tcp->session_close(mp, reactor, channel);
			}
			else if (!tcp->write(buf, len))
			{
				LOG(5, "write session buffer failed");
			}
			/*
			if (lc > len)
			{
				tcp->start_worker(channel);
				break;
			}
			*/
		}
	} while (!tcp->check_interrupt_request());
	
	return -1;
}

apr_status_t CAbstractTcp::__reactor_entry(apr_pool_t * mp, apr_socket_t * descriptor, apr_pollset_t * reactor, apr_socket_t * acceptor, void * data)
{
	apr_status_t		rv;
	apr_pool_t			* mp_child	= NULL;
	apr_socket_t		* channel	= NULL;
	
	if (descriptor != acceptor)
	{
		//×¢ÒâÕâ¸ömp
		//mp_child = apr_pool_find(NULL/*(const void *)descriptor*/);
		__recv(mp, descriptor, reactor, data);
	}
	else
	{
		mp_child = NULL;
		
		if (APR_SUCCESS == (rv = TCPAcceptor_start(mp, descriptor, &channel, &mp_child)))
		{
			if (!__is_reject(data, channel, mp_child))
			{
				rv = Reactor_append_fd(mp_child, reactor, channel);
				__accept(mp_child, channel, reactor, data);
			}
			else
			{
				printf("---------\n");
			}
		}
		else
		{
			if (APR_STATUS_IS_ENOTSOCK(rv))
			{
				apr_err_print(0, rv, "Reactor_start:TCPAcceptor_start");
				
				rv = Reactor_remove_fd(mp, reactor, descriptor);
				rv = apr_socket_close(descriptor);
			}
		}
	}
	return rv;
}










CAbstractIOCPTcp::CAbstractIOCPTcp() : m_acceptor(NULL), m_reactor(NULL)
{
	
}
CAbstractIOCPTcp::~CAbstractIOCPTcp()
{
	
}


apr_status_t CAbstractIOCPTcp::run(void * data, apr_pool_t * mp, apr_interval_time_t timeout, int listen_port, int size)
{
	apr_status_t	rv = 0;
	rv = TCPAcceptor_create(mp, listen_port, &m_acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		rv = IOCPReactor_create(mp, size, &m_reactor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		rv = IOCPReactor_append_fd(mp, m_reactor, m_acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
	return IOCPReactor_await(m_reactor, timeout, reactor_entry, NULL);
}

int g_entry_count = 0;
apr_status_t CAbstractIOCPTcp::reactor_entry(void *baton, apr_pollfd_t *descriptor)
{
	g_entry_count ++;
	return -1;
}

apr_status_t CAbstractIOCPTcp::accept_entry(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data)
{
	CAbstractIOCPTcp *	tcp	= (CAbstractIOCPTcp*)data;
	
	tcp->addtree(channel);
	
	return -1;
}


apr_status_t CAbstractIOCPTcp::recv_entry(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data)
{
	CAbstractIOCPTcp *	tcp	= (CAbstractIOCPTcp*)data;
	apr_status_t	rv	= APR_SUCCESS;
	char cmd_break_point[4096]		= {0};
	char buf[128]		= {0};
	apr_size_t len		= sizeof(buf) - 1;
	
	__QUERY_TICK_COUNT("m_d0_=", tcp->m_d0_);
	
	do
	{
		//memset(buf, 0, sizeof(buf));
		len	= sizeof(buf) - 1;
		rv = apr_socket_recv(channel, buf, &len);
		
		__QUERY_TICK_COUNT("m_d1_=", tcp->m_d1_);
		
		if (0 >= len)
		{
			if (APR_STATUS_IS_EAGAIN(rv))
			{
				//apr_err_print(rv, "");
				break;
			}
			else if (APR_SUCCESS != rv && !APR_STATUS_IS_EAGAIN(rv))
			{
				if (APR_EOF == rv)
				{
					apr_err_print(0, rv, "");
				}
				tcp->session_close(mp, reactor, channel);
			}
			break;
		}
		else if (APR_SUCCESS == rv)
		{
			tcp->start_worker(cmd_break_point, buf, len, channel);
			if (sizeof(buf)-1 == len)
			{
				break;
			}
		}
	} while (!tcp->check_interrupt_request());
	
	return -1;
}
