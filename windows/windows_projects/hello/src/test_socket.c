#include "../package/headers/system_socket.h"


void test_server()
{
	int index = 0;
	SOCKET_TCP_HANDLE server, client[1024];

	socket_init();

	socket_tcp_acceptor_create( &server, 8090 );

	for ( index = 0; ; index++)
	{
		socket_tcp_accept( &server, &client[index] );
	}
	socket_tcp_destroy(&server);

	socket_fini();
}

void test_client()
{
	int index = 0;
	SOCKET_TCP_HANDLE client[1024];

	socket_init();
	for (index = 0; index < sizeof(client) / sizeof(SOCKET_TCP_HANDLE); index++)
		socket_tcp_connector_create( &client[index], "192.168.128.70"/*"169.254.217.225"*/, 8090 );

	system("pause");

#if 0
	for (index = 0; index < sizeof(client) / sizeof(SOCKET_TCP_HANDLE); index++)
		socket_tcp_destroy(client[index]);
#endif//0
	socket_fini();
}



void test_async_server()
{
	_BOOLEAN state;
	int index = 0;
	SOCKET_TCP_HANDLE server, client;
	SELECT_IO_HANDLE select_io;

	u_long ret = 0;
	socket_init();

	async_socket_tcp_acceptor_create( &server, 8090 );

	for ( ; ; )
	{
		ret = select_io_init( &select_io );

		if ( _ok != ret )
			return;

		ret = select_io_tcp_append( &select_io, &server );

		if ( _ok != ret )
		{
			
		}
		ret = select_io_tcp_wait(&select_io, NULL, NULL, -1/*5*1000*1000*/);

		if ( _IS_SELECT_IO_ERR_RESULT_(ret) )
			continue;

		ret = select_io_tcp_is_exist(&select_io, &server, &state);

		if ( _ok != ret )
		{
			continue;
		}
		else if ( _IS_OK_(state) )
		{
			ret = async_socket_tcp_accept( &server, &client );

			if (_IS_ASYNC_SOCKET_ERR_RESULT_(ret))
			{
				continue;
			}
			else
			{

			}
		}
	}
	socket_tcp_destroy(&server);

	socket_fini();
}

void test_async_client()
{
	int index = 0;
	SOCKET_TCP_HANDLE client[1024];

	socket_init();
	for (index = 0; index < sizeof(client) / sizeof(SOCKET_TCP_HANDLE); index++)
		socket_tcp_connector_create( &client[index], "192.168.128.70"/*"169.254.217.225"*/, 8090 );

	system("pause");

#if 0
	for (index = 0; index < sizeof(client) / sizeof(SOCKET_TCP_HANDLE); index++)
		socket_tcp_destroy(client[index]);
#endif//0
	socket_fini();
}