#include <apr_pools.h>
#include <apr_network_io.h>



bool _block_tcp_task_run(apr_socket_t * s)
{
	char			buff[512]		= {0};
	apr_size_t		len				= 0;
	apr_status_t	rv				= APR_SUCCESS;
	
	memset(buff, 0, sizeof(buff));
	len = sizeof(buff);
	
	if (APR_SUCCESS != (rv = apr_socket_recv(s, buff, &len)))
	{
		return false;
	}
	
	printf("recv:[%d] [%s]\n", len, buff);
	
	if (APR_SUCCESS != (rv = apr_socket_send(s, buff, &len)))
	{
		return false;
	}
	return true;
}

apr_status_t _block_tcp_task_init(apr_pool_t * mp)
{
	apr_socket_t	* listen_s	= NULL;
	apr_socket_t	* accept_s	= NULL;
	apr_sockaddr_t	* sock_addr	= NULL;
	apr_port_t		listen_port	= 9198;
	apr_status_t	rv			= APR_SUCCESS;
	apr_int32_t		on			= 1;
	
	if (APR_SUCCESS != (rv = apr_sockaddr_info_get(&sock_addr, NULL, APR_INET, listen_port, 0, mp)))
	{
	}
	if (APR_SUCCESS != (rv = apr_socket_create(&listen_s, sock_addr->family, SOCK_STREAM, APR_PROTO_TCP, mp)))
	{
	}
	if (APR_SUCCESS != (rv = apr_socket_bind(listen_s, sock_addr)))
	{
	}
	if (APR_SUCCESS != (rv = apr_socket_listen(listen_s, SOMAXCONN)))
	{
	}
	if (APR_SUCCESS != (rv = apr_socket_opt_set(listen_s, APR_TCP_NODELAY, on)))
	{
	}
	if (APR_SUCCESS != (rv = apr_socket_opt_get(listen_s, APR_TCP_NODELAY, &on)))
	{
	}
	while (true)
	{
		if (APR_SUCCESS == (rv = apr_socket_accept(&accept_s, listen_s, mp)))
		{
			while (true)
			{
				if (!_block_tcp_task_run(accept_s))
				{
					if (accept_s)
					{
						apr_socket_close(accept_s);
						accept_s = NULL;
					}
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	if (listen_s)
	{
		apr_socket_close(listen_s);
		listen_s = NULL;
	}
	return rv;
}
