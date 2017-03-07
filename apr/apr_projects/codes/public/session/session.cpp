#include "session.h"
#include "log.h"


// 
// __PRINTX g_printf_func_x = NULL;
// 
// int g_log_print_level_x;
// 
// inline void __cdecl LOGX(const int level, const char * f, ...)
// {
// 	if (level > g_log_print_level_x)
// 	{
// 		va_list _va_list;
// 		/* 初始化变长参数列表 */
// 		va_start(_va_list, f);
// 		char buf[__LOGX_INFO_LEN__];
// 		int len = vsprintf(buf, f, _va_list);
// 		va_end(_va_list);
// 		
// 		if (g_printf_func_x)
// 			g_printf_func_x(buf);
// 	}
// }
// 

void apr_err_print(const int level, apr_status_t rv, char * msg)
{
	char err_buff[__ERROR_INFO_LEN__] = {0};
	apr_strerror(rv, err_buff, sizeof(err_buff));
	LOG(level, "apr_strerror %s ->%d -- %s\n", msg, rv, err_buff);
}



void TCPChannel_init(apr_socket_t * channel)
{
	apr_status_t rv;
	apr_int32_t on = 1;
	if (APR_SUCCESS != (rv = apr_socket_opt_set(channel, APR_SO_NONBLOCK, 1)))
		apr_err_print(0, rv, "");
	if (APR_SUCCESS != (rv = apr_socket_timeout_set(channel, 0)))
		apr_err_print(0, rv, "");
	if (APR_SUCCESS != (rv = apr_socket_opt_set(channel, APR_TCP_NODELAY, on)))
		apr_err_print(0, rv, "");
}

apr_sockaddr_t * g_udp_sa = NULL;
apr_socket_t * g_udp_connector = NULL;

void UDPTest_send(const char * log, double t)
{
	char test_log[256] = {0};
	apr_size_t len = sprintf(test_log, "%s%.9lf", log, t);
	UDPConnector_send(g_udp_connector, g_udp_sa, 0, test_log, &len);
}

apr_status_t TCPAcceptor_create(apr_pool_t * mp, const apr_port_t listen_port, apr_socket_t ** acceptor)
{
	apr_status_t	rv;
	apr_sockaddr_t	* sa;
	apr_int32_t		on				= 1;

	if (__SEND_UDP_TEST__)
		UDPConnector_create(mp, "127.0.0.1", 9988, &g_udp_sa, &g_udp_connector);

	rv = apr_sockaddr_info_get(&sa, NULL, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_create(acceptor, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_set(*acceptor, APR_SO_NONBLOCK, on);
    IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	on = 1;
	rv = apr_socket_opt_set( *acceptor, APR_TCP_NODELAY, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	on = 1;
	/* this is useful for a server(socket listening) process */
	rv = apr_socket_opt_set(*acceptor, APR_SO_REUSEADDR, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_timeout_set(*acceptor, 0);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_bind(*acceptor, sa);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_listen(*acceptor, SOMAXCONN);
	return rv;
}


apr_status_t TCPAcceptor_start(apr_pool_t * mp, apr_socket_t * acceptor, apr_socket_t ** channel, apr_pool_t ** mp_child)
{
	*mp_child	= NULL;
	apr_status_t rv	= apr_pool_create(mp_child, mp);
	
	if (APR_SUCCESS == rv)
	{
		apr_status_t rv = apr_socket_accept(channel, acceptor, *mp_child);
		
		if (APR_SUCCESS == rv)
			TCPChannel_init(*channel);
	}
	return rv;
}

apr_status_t Reactor_append_fd(apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * s)
{
	apr_pollfd_t pfd = {mp, APR_POLL_SOCKET, APR_POLLIN, 0, {NULL}, NULL};
	pfd.desc.s = s;
	return apr_pollset_add(reactor, &pfd);
}


apr_status_t Reactor_remove_fd(apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * s)
{
	apr_pollfd_t pfd = {mp, APR_POLL_SOCKET, APR_POLLOUT, 0, {NULL}, NULL};
	pfd.desc.s = s;
	return apr_pollset_remove(reactor, &pfd);
}

//使用唤醒模式会严重影响POll的效率
apr_status_t Reactor_create(apr_pool_t * mp, apr_uint32_t size, apr_pollset_t ** reactor, apr_uint32_t wakeup_flags)
{
	return apr_pollset_create(reactor, size, mp, wakeup_flags);
}

apr_status_t Reactor_destroy(apr_pollset_t * reactor)
{
	return apr_pollset_destroy(reactor);
}



apr_status_t Reactor_wakeup(apr_pollset_t * reactor)
{
	return apr_pollset_wakeup(reactor);
}





apr_status_t Reactor_await(
						   apr_pool_t			* mp,
						   apr_pollset_t		* reactor,
						   apr_socket_t			* acceptor,
						   apr_interval_time_t	timeout,
						   __REACTOR_ENTRY		__reactor_entry,
						   void					* data
						   )
{
	apr_status_t		rv;
	apr_int32_t			index = 0;
	apr_int32_t			num;
	
	const apr_pollfd_t	* ret_pfd;

	while (true)
	{
		if (APR_SUCCESS == (rv = apr_pollset_poll(reactor, timeout, &num, &ret_pfd)))
		{
			for (index = 0; index < num; index++)
			{
				__reactor_entry(mp, ret_pfd[index].desc.s, reactor, acceptor, data);
			}
		}
		else
		{
			apr_err_print(0, rv, "Reactor_start:apr_pollset_poll");
			if (APR_STATUS_IS_TIMEUP(rv))
			{
				//The timeout specified has expired，num为0
				continue;
			}
			else if (APR_STATUS_IS_ENOTSOCK(rv))
			{
				//在一个非套接字上尝试了一个操作。num为-1
				break;
			}
			else if (/*APR_POLLSET_WAKEABLE*/4 == rv)
			{
				//Interrupted function call 唤醒时，num为0
				continue;
			}
			else if (9 == rv)
			{
				//Bad file descriptor 这个错误是销毁了reactor导致的，num为1
				break;
			}
		}
	}
	return rv;
}



apr_status_t TCPConnector_create(apr_pool_t * mp, const char * hostname, const apr_port_t listen_port, apr_socket_t ** connector)
{
	apr_status_t	rv		= APR_SUCCESS;
	apr_sockaddr_t	* sa	= NULL;
	apr_int32_t		on		= 1;
	
	* connector = NULL;
	
	rv = apr_sockaddr_info_get(&sa, hostname, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		rv = apr_socket_create(connector, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		on = 1;
	rv = apr_socket_opt_set(*connector, APR_SO_REUSEADDR, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

		on = 1;
		rv = apr_socket_opt_set(*connector, APR_SO_NONBLOCK, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		on = 1;
		rv = apr_socket_timeout_set(*connector, -1);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		on = 1;
		rv = apr_socket_opt_set(*connector, APR_TCP_NODELAY, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
	//	rv = apr_socket_opt_get(*connector, APR_TCP_NODELAY, &on);
	//IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
	rv = apr_socket_connect(*connector, sa);
	if (APR_SUCCESS == rv)
	{
		apr_socket_opt_set(*connector, APR_SO_NONBLOCK, 0);
	}
	return rv;	
}


apr_status_t UDPConnector_create(apr_pool_t * mp, const char * hostname, const apr_port_t listen_port, apr_sockaddr_t ** sa, apr_socket_t ** connector)
{
    apr_status_t rv;
	
	rv = apr_sockaddr_info_get(sa, hostname, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_create(connector, (*sa)->family, SOCK_DGRAM, APR_PROTO_UDP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
	
	rv = apr_socket_opt_set(*connector, APR_SO_NONBLOCK, 0);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_timeout_set(*connector, -1);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_set(*connector, APR_SO_REUSEADDR, 1);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
	
	return apr_socket_bind(*connector, *sa);
}

apr_status_t UDPConnector_send(apr_socket_t *connector, apr_sockaddr_t *where, apr_int32_t flags, const char *buf, apr_size_t *len)
{
	return apr_socket_sendto(connector, where, flags, buf, len);
}

apr_status_t UDPAcceptor_create(apr_pool_t * mp, const apr_port_t listen_port, apr_sockaddr_t ** sa, apr_socket_t ** acceptor)
{
	apr_status_t	rv;
	apr_int32_t		on				= 1;
	
	rv = apr_sockaddr_info_get(sa, NULL, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		rv = apr_socket_create(acceptor, (*sa)->family, SOCK_DGRAM, APR_PROTO_UDP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		rv = apr_socket_opt_set(*acceptor, APR_SO_NONBLOCK, on);
    IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		on = 1;
	rv = apr_socket_opt_set( *acceptor, APR_TCP_NODELAY, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		on = 1;
	/* this is useful for a server(socket listening) process */
	rv = apr_socket_opt_set(*acceptor, APR_SO_REUSEADDR, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		rv = apr_socket_timeout_set(*acceptor, 0);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
		rv = apr_socket_bind(*acceptor, *sa);
	return rv;
}

apr_status_t UDPAcceptor_recv(apr_sockaddr_t * from, apr_socket_t *acceptor, apr_int32_t flags, char *buf, apr_size_t *len)
{
	return apr_socket_recvfrom(from, acceptor, flags, buf, len);
}




apr_status_t IOCPReactor_create(apr_pool_t * mp, apr_uint32_t size, apr_pollcb_t ** iocp_reactor)
{
	typedef struct __tagIOCPReactorAttr
	{
		apr_uint32_t			flags;
		apr_pollset_method_e	method;
	}
	IOCPReactorAttr;
	
	IOCPReactorAttr ra[] =
	{
		{0,							APR_POLLSET_DEFAULT	},
		{0,							APR_POLLSET_SELECT	},
		{0,							APR_POLLSET_KQUEUE	},
		{0,							APR_POLLSET_PORT	},
		{0,							APR_POLLSET_EPOLL	},
		{0,							APR_POLLSET_POLL	},

		{APR_POLLSET_THREADSAFE,	APR_POLLSET_DEFAULT	},
		{APR_POLLSET_THREADSAFE,	APR_POLLSET_SELECT	},
		{APR_POLLSET_THREADSAFE,	APR_POLLSET_KQUEUE	},
		{APR_POLLSET_THREADSAFE,	APR_POLLSET_PORT	},
		{APR_POLLSET_THREADSAFE,	APR_POLLSET_EPOLL	},
		{APR_POLLSET_THREADSAFE,	APR_POLLSET_POLL	},

		{APR_POLLSET_NOCOPY,		APR_POLLSET_DEFAULT	},
		{APR_POLLSET_NOCOPY,		APR_POLLSET_SELECT	},
		{APR_POLLSET_NOCOPY,		APR_POLLSET_KQUEUE	},
		{APR_POLLSET_NOCOPY,		APR_POLLSET_PORT	},
		{APR_POLLSET_NOCOPY,		APR_POLLSET_EPOLL	},
		{APR_POLLSET_NOCOPY,		APR_POLLSET_POLL	},


		{APR_POLLSET_WAKEABLE,		APR_POLLSET_DEFAULT	},
		{APR_POLLSET_WAKEABLE,		APR_POLLSET_SELECT	},
		{APR_POLLSET_WAKEABLE,		APR_POLLSET_KQUEUE	},
		{APR_POLLSET_WAKEABLE,		APR_POLLSET_PORT	},
		{APR_POLLSET_WAKEABLE,		APR_POLLSET_EPOLL	},
		{APR_POLLSET_WAKEABLE,		APR_POLLSET_POLL	},

		{APR_POLLSET_NODEFAULT,		APR_POLLSET_DEFAULT	},
		{APR_POLLSET_NODEFAULT,		APR_POLLSET_SELECT	},
		{APR_POLLSET_NODEFAULT,		APR_POLLSET_KQUEUE	},
		{APR_POLLSET_NODEFAULT,		APR_POLLSET_PORT	},
		{APR_POLLSET_NODEFAULT,		APR_POLLSET_EPOLL	},
		{APR_POLLSET_NODEFAULT,		APR_POLLSET_POLL	}
	};
	
	apr_status_t rv;

	size = 1;

	for (int i=0; i < sizeof(ra)/sizeof(IOCPReactorAttr); i++)
	{
		if (APR_SUCCESS == (rv = apr_pollcb_create_ex(iocp_reactor, size, mp, ra->flags, ra->method)))
		{
			break;
		}
	}
	return rv;
}


apr_status_t IOCPReactor_await(
							   apr_pollcb_t				* iocp_reactor,
							   apr_interval_time_t		timeout,
							   apr_pollcb_cb_t			__IOCP_REACTOR_ENTRY,
							   void						* baton
							   )
{
	apr_status_t rv = APR_SUCCESS;

	while (true)
	{
		if (APR_SUCCESS != (rv = apr_pollcb_poll(iocp_reactor, timeout, __IOCP_REACTOR_ENTRY, baton)))
		{
			apr_err_print(0, rv, "Reactor_start:apr_pollset_poll");
			if (APR_STATUS_IS_TIMEUP(rv))
			{
				//The timeout specified has expired，num为0
				continue;
			}
			else if (APR_STATUS_IS_ENOTSOCK(rv))
			{
				//在一个非套接字上尝试了一个操作。num为-1
				break;
			}
			else if (/*APR_POLLSET_WAKEABLE*/4 == rv)
			{
				//Interrupted function call 唤醒时，num为0
				continue;
			}
			else if (9 == rv)
			{
				//Bad file descriptor 这个错误是销毁了reactor导致的，num为1
				break;
			}
		}
	}
	return rv;
}

apr_status_t IOCPReactor_append_fd(apr_pool_t * mp, apr_pollcb_t * iocp_reactor, apr_socket_t * s)
{
	apr_pollfd_t pfd = {mp, APR_POLL_SOCKET, APR_POLLIN, 0, {NULL}, NULL};
	pfd.desc.s = s;
	return apr_pollcb_add(iocp_reactor, &pfd);
}

apr_status_t IOCPReactor_remove_fd(apr_pool_t * mp, apr_pollcb_t * iocp_reactor, apr_socket_t * s)
{
	apr_pollfd_t pfd = {mp, APR_POLL_SOCKET, APR_POLLOUT, 0, {NULL}, NULL};
	pfd.desc.s = s;
	return apr_pollcb_remove(iocp_reactor, &pfd);
}
