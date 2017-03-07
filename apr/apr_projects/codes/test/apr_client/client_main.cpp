#include <apr_pools.h>
//#include <apr_network_io.h>


extern int _block_tcp_task_init(apr_pool_t * mp);

typedef int (* __FUNC)(apr_pool_t * pool);

void apr_pool_init(__FUNC func)
{
	//try
	{
		apr_pool_t		* pool	= NULL;
		apr_status_t	ret		= APR_SUCCESS;
		
		apr_initialize();
		if (APR_SUCCESS == (ret = apr_pool_create(&pool, NULL)))
		{
			func(pool);
			
			if (pool)
			{
				apr_pool_destroy(pool);
				pool = NULL;
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
	apr_pool_init(_block_tcp_task_init);
}