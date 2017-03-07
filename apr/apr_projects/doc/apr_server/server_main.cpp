#include <apr_pools.h>
//#include <apr_network_io.h>

extern apr_status_t _block_tcp_task_init(apr_pool_t * mp);
extern apr_status_t _poll_nonblock_tcp_task_init(apr_pool_t * mp);


typedef apr_status_t (* __FUNC)(apr_pool_t * mp);

void apr_pool_init(__FUNC func)
{
	//try
	{
		apr_pool_t		* mp	= NULL;
		apr_status_t	rv		= APR_SUCCESS;
		
		apr_initialize();
		if (APR_SUCCESS == (rv = apr_pool_create(&mp, NULL)))
		{
			func(mp);
			
			if (mp)
			{
				apr_pool_destroy(mp);
				mp = NULL;
			}
		}
	}
	//__finally
	{
		apr_terminate();
	}	
}

void main()
{
	apr_pool_init(_poll_nonblock_tcp_task_init);
}
