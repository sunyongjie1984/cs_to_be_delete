#include <apr_pools.h>
#include <apr_network_io.h>

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




#define IS_FAILED_RETURN(ok_val, rv, err_msg) { if ((ok_val) != (rv)) { apr_err_print(rv, (err_msg)); return (rv); } }


apr_status_t TCPConnector_create(apr_pool_t * mp, const char * hostname, const apr_port_t listen_port, apr_socket_t ** connector)
{
	apr_status_t	rv				= APR_SUCCESS;
	apr_sockaddr_t	* sa		= NULL;
	apr_int32_t		on				= 1;

	rv = apr_sockaddr_info_get(&sa, hostname, APR_INET, listen_port, 0, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_create(connector, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_set(*connector, APR_TCP_NODELAY, on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_opt_get(*connector, APR_TCP_NODELAY, &on);
	IS_FAILED_RETURN(APR_SUCCESS, rv, "")

	rv = apr_socket_connect(*connector, sa);
	return rv;	
}



bool send_msg(apr_socket_t * s, int index)
{
	char			buff[512]		= {0};
	apr_size_t		len				= 0;
	apr_status_t	ret				= APR_SUCCESS;
	
	memset(buff, 0, sizeof(buff));
	len = sprintf(buff, "hello %p %.8d" CRLF_STR, s, index);
	
	for (int i=0; i < 5; i++)
	{
		if (APR_SUCCESS != (ret = apr_socket_send(s, buff, &len)))
		{
			printf("apr_socket_send failed");
			apr_sleep(APR_USEC_PER_SEC);
		}
		else
		{
			printf("[%s][%.8d]\n", buff, len);
			return true;
		}
	}
	return false;
}

int _block_tcp_task_init(apr_pool_t * mp)
{
	apr_socket_t	* connector = NULL;
	apr_port_t		listen_port		= 9198;
	apr_status_t	rv				= APR_SUCCESS;
	for (int i = 0; true; i++)
	{
		rv = TCPConnector_create(mp, "127.0.0.1", listen_port, &connector);

		if (APR_SUCCESS != rv)
		{
			apr_err_print(rv, "");

			if (connector)
			{
				apr_socket_close(connector);
				connector = NULL;
			}
			apr_sleep(1000*1000*10);
			continue;
		}
		
		for (int i=0; true; i++)
		{
			for (int j=0; j<100; j++)
			{
				send_msg(connector, j);
			}
			//apr_sleep(1000*10);
		}
		
		
		apr_socket_shutdown(connector, APR_SHUTDOWN_READWRITE);
		
		if (connector)
		{
			apr_socket_close(connector);
			connector = NULL;
		}
	}
	return rv;
}
