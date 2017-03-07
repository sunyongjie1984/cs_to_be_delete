
#include <apr_pools.h>
#include <apr_network_io.h>
#include <apr_poll.h>
#include <apr_errno.h>


/* default socket timeout */
#define DEF_POLL_TIMEOUT	(APR_USEC_PER_SEC * 30)

/* default buffer size */
#define BUFSIZE			4096

/* useful macro */
#define CRLF_STR		"\r\n"


void apr_err_print(apr_status_t rv, char * msg)
{
	char err_buff[BUFSIZE] = {0};
	apr_strerror(rv, err_buff, sizeof(err_buff));
	printf("%s ->%d -- %s\n", msg, rv, err_buff);
}



void TCPChannel_init(apr_socket_t * channel)
{
	apr_status_t rv;
	apr_int32_t on = 1;
	if (APR_SUCCESS != (rv = apr_socket_opt_set(channel, APR_SO_NONBLOCK, 1)))
		apr_err_print(rv, "");
	if (APR_SUCCESS != (rv = apr_socket_timeout_set(channel, 0)))
		apr_err_print(rv, "");
	if (APR_SUCCESS != (rv = apr_socket_opt_set(channel, APR_TCP_NODELAY, on)))
		apr_err_print(rv, "");
}


#define IS_FAILED_RETURN(ok_val, rv, err_msg) { if ((ok_val) != (rv)) { apr_err_print(rv, (err_msg)); return (rv); } }

apr_status_t TCPAcceptor_create(apr_pool_t * mp, const apr_port_t listen_port, apr_socket_t ** acceptor)
{
	apr_status_t	rv;
	apr_sockaddr_t	* sa;
	apr_int32_t		on				= 1;

	rv = apr_sockaddr_info_get(&sa, NULL, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_create(acceptor, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_set(*acceptor, APR_SO_NONBLOCK, on);
    IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_set( *acceptor, APR_TCP_NODELAY, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

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

apr_status_t TCPAcceptor_start(apr_pool_t * mp, apr_socket_t * acceptor, apr_socket_t ** channel)
{
	apr_status_t rv = apr_socket_accept(channel, acceptor, mp);

	if (APR_SUCCESS == rv)
		TCPChannel_init(*channel);

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

apr_status_t Reactor_create(apr_pool_t * mp, apr_uint32_t size, apr_pollset_t ** reactor)
{
	return apr_pollset_create(reactor, size, mp, 0);
}

apr_status_t Reactor_destroy(apr_pool_t * mp, apr_pollset_t * reactor)
{
	return apr_pollset_destroy(reactor);
}

apr_status_t Reactor_append_fd(apr_pollset_t * reactor)
{
	return apr_pollset_wakeup(reactor);
}


typedef apr_status_t /*APR_THREAD_FUNC*/(* __REACTOR_DEAL)(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor);



apr_status_t Reactor_await(apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * acceptor, apr_interval_time_t timeout, __REACTOR_DEAL run)
{
	apr_status_t		rv;
	apr_int32_t			index = 0;
	apr_int32_t			num;
	
	const apr_pollfd_t	* ret_pfd;
	apr_socket_t		* channel = NULL;

	while (true)
	{
		if (APR_SUCCESS == (rv = apr_pollset_poll(reactor, timeout, &num, &ret_pfd)))
		{
			for (index = 0; index < num; index++)
			{
				if (ret_pfd[index].desc.s != acceptor)
					run(mp, ret_pfd[index].desc.s, reactor);
				else
					if (APR_SUCCESS == (rv = TCPAcceptor_start(mp, ret_pfd[index].desc.s, &channel)))
						rv = Reactor_append_fd(mp, reactor, channel);
					else
						printf("error\n");
			}
		}
		else
		{
			apr_err_print(rv, "Reactor_start :");
		}
	}
	return rv;
}




#if 1

void _nonblock_tcp_task_run(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor)
{
	apr_status_t	rv;

	char buf[BUFSIZE] = {0};
	apr_size_t len = sizeof(buf) - 1;
	
	while (true)
	{
		memset(buf, 0, sizeof(buf));

		rv = apr_socket_recv(channel, buf, &len);
		
		if (0 >= len)
		{
			if (APR_STATUS_IS_EAGAIN(rv))
			{
				apr_err_print(rv, "");
			}
			else if (APR_SUCCESS != rv && !APR_STATUS_IS_EAGAIN(rv))
			{
				if (APR_EOF == rv)
				{
					apr_err_print(rv, "");
					//break;
				}
				rv = Reactor_remove_fd(mp, reactor, channel);
				rv = apr_socket_close(channel);
				channel = NULL;
				
				apr_err_print(rv, "");
			}
			break;
		}
		else if (APR_SUCCESS == rv)
		{
			printf(" ** revc:[%d] **\n%s", len, buf);
			if (sizeof(buf)-1 == len)
			{
				break;
			}
		}
	}
}

apr_status_t Reactor_run(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor)
{
	_nonblock_tcp_task_run(mp, channel, reactor);
	return 0;
}


apr_status_t _poll_nonblock_tcp_task_init(apr_pool_t * mp)
{
	apr_status_t	rv = 0;
	apr_uint32_t	size = 512;
	apr_int32_t		num = 0;
	apr_port_t		listen_port	= 9198;
	apr_socket_t	* acceptor;
	apr_pollset_t	* reactor;
	
	rv = TCPAcceptor_create(mp, listen_port, &acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = Reactor_create(mp, size, &reactor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")
		
	rv = Reactor_append_fd(mp, reactor, acceptor);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = Reactor_await(mp, reactor, acceptor, DEF_POLL_TIMEOUT, Reactor_run);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	return rv;
}

#endif//0
