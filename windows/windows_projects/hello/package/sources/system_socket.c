#include "../headers/system_socket.h"



#pragma warning(disable:4096 4996 4013)


#pragma comment (lib, "Ws2_32.lib")


#define _IS_ERR_SOCKET_( h ) (INVALID_SOCKET != (h)->socket_)


int __cdecl wsa_get_error( void )
{
	return WSAGetLastError();
}




static _BOOLEAN socket_init_flag = _false;




u_long __cdecl socket_init(void)
{
	WSADATA wsa_data;
	WORD	version_requested = MAKEWORD( 2, 2 );

	u_long ret = 0;

	if ( _IS_ERR_(socket_init_flag) )
	{
		socket_init_flag = _true;
	}
	else
	{
		return _ok;
	}
	if ( (0 == WSAStartup( version_requested, &wsa_data )) && ( (2 == LOBYTE(wsa_data.wVersion)) && (2 == HIBYTE(wsa_data.wVersion)) ) )
	{
		ret = _ok;
	}
	else
	{
		ret = wsa_get_error();
		socket_fini();
	}
	return ret;
}



u_long __cdecl socket_fini(void)
{
	if ( _IS_OK_( socket_init_flag ) )
	{
		socket_init_flag = _false;

		if ( SOCKET_ERROR == WSACleanup() )
		{
			return wsa_get_error();
		}
	}
	return _ok;
}



u_long __cdecl socket_set_addr( _in_ _out_ SOCKET_TCP_HANDLE * h, _in_ const u_char * ip, _in_ const u_short host_short )
{
	struct in_addr a;
	struct hostent * p = gethostbyname( ip );

	u_long ret = 0;

	if ( ( !h ) || ( !ip ) )
		return _err_input_para;

	if ( !_IS_CREATE_(h->status_) )
		return _err_object_create;

	if ( !p )
		return wsa_get_error();

	memset( (void *)&a, 0, sizeof(struct in_addr) );
	memset( (void *)&(h->addr_), 0, sizeof(h->addr_) );

	h->addr_.sin_family = AF_INET;
	h->addr_.sin_port = htons(host_short);

	memcpy( &a, p->h_addr_list[0], 4 );
	h->addr_.sin_addr = a;

	return _ok;
}


u_long __cdecl socket_set_mode( _in_ const SOCKET_TCP_HANDLE * h, _BOOLEAN nonblocking )
{
	u_long ul = nonblocking;

	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	if ( SOCKET_ERROR == ioctlsocket( h->socket_, FIONBIO, &ul ) )
		ret = wsa_get_error();
	else
		ret = _ok;
	
	return ret;
}


u_long __cdecl socket_set_nonblocking_mode( _in_ const SOCKET_TCP_HANDLE * h )
{
	return socket_set_mode( h, _true );
}

u_long __cdecl socket_set_blocking_mode( _in_ const SOCKET_TCP_HANDLE * h )
{
	return socket_set_mode( h, _false );
}

u_long __cdecl socket_get_ip( _in_ const SOCKET_TCP_HANDLE * h, _out_ u_char * ip )
{
	if ( ( !h ) || ( !ip ) )
		return _err_input_para;
	
	if ( !(_IS_INSTANCE_(h->status_)) || !(_IS_CREATE_(h->status_)) )
		return _err_object_create;

	sprintf( 
		ip, "%d.%d.%d.%d",
		h->addr_.sin_addr.S_un.S_un_b.s_b1,
		h->addr_.sin_addr.S_un.S_un_b.s_b2,
		h->addr_.sin_addr.S_un.S_un_b.s_b3,
		h->addr_.sin_addr.S_un.S_un_b.s_b4
		);
	return _ok;
}


u_long __cdecl socket_tcp_init( _in_ _out_ SOCKET_TCP_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
	{
		return _err_input_para;
	}
	if ( _IS_CREATE_(h->status_) )
	{
		ret = socket_tcp_destroy( h );

		if ( _ok != ret )
			return ret;
	}
	h->status_ = _instance;

	memset( (void *)&(h->addr_), 0, sizeof(h->addr_) );
	h->socket_ = INVALID_SOCKET;
	return _ok;
}

u_long __cdecl socket_destroy( _in_ _out_ SOCKET_TCP_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	if ( SOCKET_ERROR == closesocket( h->socket_ ) )
	{
		ret = wsa_get_error();
	}
	else
	{
		h->status_ = _destroy;
		ret = _ok;
	}
	return ret;
}

u_long __cdecl socket_tcp_create( _in_ _out_ SOCKET_TCP_HANDLE * h )
{
	struct protoent * ppe = NULL;
	u_long ret = 0;

	if ( !h )
	{
		return _err_input_para;
	}
	if ( !( ppe = getprotobyname("tcp") ) )
	{
		return wsa_get_error();
	}
	if ( !( _IS_INSTANCE_(h->status_) ) )
	{
		ret = socket_tcp_init( h );

		if ( _ok != ret )
			return ret;
	}
	else if ( _IS_CREATE_(h->status_) )
	{
		return _ok;
	}

	h->socket_ = socket( PF_INET, SOCK_STREAM, ppe->p_proto );

	if( _IS_ERR_SOCKET_( h ) )
	{
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = wsa_get_error();
	}
	return ret;
}


u_long __cdecl socket_tcp_destroy( _in_ _out_ SOCKET_TCP_HANDLE * h )
{
	return socket_destroy(h);
}
// MSG_PEEK 
// MSG_OOB 
// MSG_WAITALL

u_long __cdecl socket_tcp_read( _in_ const SOCKET_TCP_HANDLE * h, _in_ _out_ u_char * buff, _in_ _out_ u_long * len, _in_ const int flags )
{
	u_long read_total = 0;
	u_long ret = 0;

	if ( ( !h ) || ( !buff ) || ( !len ) )
		return _err_input_para;

	if ( *len <= 0 )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_) ) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	read_total = recv(h->socket_, buff, *len, flags);

	switch (read_total)
	{
	case 0:
		{
			ret = wsa_get_error();//CONNECTION_CLOSE
			break;
		}
	case SOCKET_ERROR:
		{
			ret = wsa_get_error();
			break;
		}
	default:
		{
			ret = _ok;
			break;
		}
	}
	*len = read_total;

	return ret;
}

u_long __cdecl socket_tcp_write( _in_ const SOCKET_TCP_HANDLE * h, _in_ const u_char * buff, _in_ _out_ u_long * len, _in_ const int flags )
{
	u_long write_total = 0;

	u_long ret = 0;

	if ( ( !h ) || ( !buff ) || ( !len ) )
		return _err_input_para;

	if (  *len <= 0 )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	write_total = send(h->socket_, buff, *len, flags);
	
	switch(write_total)
	{
	case 0:
		{
			ret = wsa_get_error();//CONNECTION_CLOSE
			break;
		}
	case SOCKET_ERROR:
		{
			ret = wsa_get_error();
			break;
		}
	default:
		{
			if (write_total == *len)
			{
				ret = _ok;
				break;
			}
			else
			{
				ret = _err_unknown;
				break;
			}
		}
	}
	*len = write_total;

	return ret;
}



u_long __cdecl socket_tcp_accept( _in_ const SOCKET_TCP_HANDLE * h, _in_ _out_ SOCKET_TCP_HANDLE * client )
{
	int sock_addr_len = 0;//sizeof(struct sockaddr_in);
	u_long ret = 0;

	if ( !h || !client )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	ret = socket_tcp_init( client );

	if ( _ok != ret )
		return ret;

	sock_addr_len = sizeof(client->addr_);

	(client->socket_) = accept( (h->socket_), (struct sockaddr *)&(client->addr_), &sock_addr_len );

	if ( !_IS_ERR_SOCKET_( client ) )
	{
		ret = wsa_get_error();
	}
	else
	{
		client->status_ = _create;
		ret = _ok;
	}
	return ret;
}

u_long __cdecl socket_tcp_listen( _in_ const SOCKET_TCP_HANDLE * h, _in_ const int backlog )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;
	
	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	if ( SOCKET_ERROR == listen(h->socket_, backlog) )
	{
		ret = wsa_get_error();
	}
	else
	{
		ret = _ok;
	}
	return ret;
}

u_long __cdecl socket_tcp_bind( _in_ const SOCKET_TCP_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	if ( SOCKET_ERROR == bind( h->socket_, (struct sockaddr *)&(h->addr_), sizeof(h->addr_) ) )
	{
		ret = wsa_get_error();
	}
	else
	{
		ret = _ok;
	}
	return ret;
}

u_long __cdecl socket_tcp_connect( _in_ const SOCKET_TCP_HANDLE * h )
{
	int sock_addr_len = 0;
	u_long ret = 0;

	if ( !h )
		return _err_input_para;
	
	if ( !(_IS_CREATE_(h->status_)) || !(_IS_ERR_SOCKET_( h )) )
		return _err_object_create;

	sock_addr_len = sizeof(h->addr_);

	if ( SOCKET_ERROR == connect( h->socket_, (struct sockaddr *)&(h->addr_), sock_addr_len ) )
	{
		ret = wsa_get_error();
	}
	else
	{
		ret = _ok;
	}
	return ret;
}



u_long __cdecl socket_tcp_acceptor_create( _in_ _out_ SOCKET_TCP_HANDLE * h, _in_ const u_short host_short )
{
	u_long ret = 0;

	ret = socket_tcp_create( h );
	if ( _ok != ret )
		return ret;

	ret = socket_set_addr( h, "", host_short );
	if ( _ok != ret )
		return ret;

	ret = socket_tcp_bind( h );
	if ( _ok != ret )
		return ret;

	return socket_tcp_listen( h, SOMAXCONN );
}

u_long __cdecl socket_tcp_connector_create( _in_ _out_ SOCKET_TCP_HANDLE * h, _in_ const char * ip, _in_ const u_short host_short )
{
	u_long ret = 0;

	ret = socket_tcp_create( h );
	if ( _ok != ret )
		return ret;

	ret = socket_set_addr( h, ip, host_short );
	if ( _ok != ret )
		return ret;

	ret = socket_tcp_connect( h );
	if ( _ok != ret )
		return ret;
	else
		return ret;
}


u_long __cdecl socket_tcp_read_block(
									 _in_ const SOCKET_TCP_HANDLE * h,
									 _in_ _out_ u_char * buff,
									 _in_ _out_ u_long * len,
									 _in_ const u_long block_size
									 )
{
	u_long read_len = 0;
	u_long receive_len = 0;

	u_long ret = 0;

	if ( !len )
		return _err_input_para;

	receive_len = *len;

	for ( *len = 0; receive_len > *len; )
	{
		read_len = block_size < receive_len - *len ? block_size : receive_len - *len;

		ret = socket_tcp_read( h, (buff + *len), &read_len, 0 );

		if ( _ok != ret )
		{
			break;
		}
		else
		{
			*len += read_len;
		}
	}
	return ret;
}


u_long __cdecl socket_tcp_write_block(
									  _in_ const SOCKET_TCP_HANDLE * h,
									  _in_ const u_char * buff,
									  _in_ _out_ u_long * len,
									  _in_ const u_long block_size
									  )
{
	u_long wrote_len = 0;
	u_long send_len = 0;

	u_long ret = 0;

	if ( !len )
		return _err_input_para;

	send_len = *len;

	for ( *len = 0; send_len > *len; )
	{
		wrote_len = block_size < send_len - *len ? block_size : send_len - *len;

		ret = socket_tcp_write( h, (buff + *len), &wrote_len, 0 );

		if ( _ok != ret )
		{
			break;
		}
		else
		{
			*len += wrote_len;
		}
	}
	return ret;
}


u_long __cdecl socket_tcp_verify_read(
									  _in_ const SOCKET_TCP_HANDLE * h,
									  _in_ _out_ u_char * buff,
									  _in_ _out_ u_long * len,
									  _in_ const u_long block_size,
									  _in_ const u_char * verify
									  )
{
	u_long read_len = 0;
	u_long receive_len = 0;
	u_long verify_len = strlen(verify) + 1;

	u_long ret = 0;

	if ( !len )
		return _err_input_para;

	receive_len = *len;

	for ( *len = 0; receive_len > *len; )
	{
		read_len = block_size < receive_len - *len ? block_size : receive_len - *len;

		ret = socket_tcp_read( h, (buff + *len), &read_len, 0 );

		if ( _ok != ret )
		{
			break;
		}
		else
		{
			*len += read_len;

			ret = socket_tcp_write( h, verify, &verify_len, 0 );

			if ( _ok != ret )
			{
				break;
			}
		}
	}
	return ret;
}


u_long __cdecl socket_tcp_verify_write(
									   _in_ const SOCKET_TCP_HANDLE * h,
									   _in_ const u_char * buff,
									   _in_ _out_ u_long * len,
									   _in_ const u_long block_size,
									   _in_ const u_char * verify
									   )
{
	u_long wrote_len = 0;
	u_long send_len = 0;
	u_char * verify_buff = NULL;
	u_long verify_len = strlen(verify) + 1;

	u_long ret = 0;

	if ( !len )
		return _err_input_para;

	send_len = *len;

	for ( *len = 0; send_len > *len; )
	{
		wrote_len = block_size < send_len - *len ? block_size : send_len - *len;

		ret = socket_tcp_write( h, (buff + *len), &wrote_len, 0 );

		if ( _ok != ret )
		{
			break;
		}
		else
		{
			*len += wrote_len;

			verify_buff = (u_char *)malloc(verify_len);

			for ( ; ; )
			{
				memset( verify_buff, 0, verify_len );

				ret = socket_tcp_read( h, verify_buff, &verify_len, 0 );

				if ( _ok != ret )
				{
					continue;
				}
				else
				{
					if ( 0 == strcmp( verify_buff, verify ) )
						break;
				}
			}
			if ( verify_buff )
			{
				free(verify_buff);
				verify_buff = NULL;
			}
		}
	}
	return ret;
}


//asynchronism

u_long __cdecl async_socket_tcp_create( _in_ _out_ SOCKET_TCP_HANDLE * h )
{
	u_long ret = 0;

	ret = socket_tcp_create( h );

	if ( _ok != ret )
		return ret;
	else
		return socket_set_nonblocking_mode( h );
}


u_long __cdecl async_socket_tcp_acceptor_create( _in_ _out_ SOCKET_TCP_HANDLE * h, _in_ const u_short host_short )
{
	u_long ret = 0;

	ret = async_socket_tcp_create( h );
	if ( _ok != ret )
		return ret;

	ret = socket_set_addr( h, "", host_short );
	if ( _ok != ret )
		return ret;

	ret = socket_tcp_bind( h );
	if ( _ok != ret )
		return ret;

	return socket_tcp_listen( h, SOMAXCONN );
}

u_long __cdecl async_socket_tcp_accept( _in_ const SOCKET_TCP_HANDLE * h, _in_ _out_ SOCKET_TCP_HANDLE * client )
{
	u_long ret = 0;

	ret = socket_tcp_accept( h, client );

	if ( _ok != ret )
	{
		if ( WSAEWOULDBLOCK == ret )
			return _err_completed_immediately;
		else
			return ret;
	}
	return socket_set_nonblocking_mode( client );
}



u_long __cdecl select_io_init( _in_ _out_ SELECT_IO_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	FD_ZERO( &(h->set_) );
	h->status_ = _instance;
	return _ok;
}

u_long __cdecl select_io_tcp_is_exist( _in_ const SELECT_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle, _out_ _BOOLEAN * state )
{
	u_long ret = 0;

	if ( !h || !socket_handle || !state )
		return _err_input_para;

	if ( !_IS_INSTANCE_(h->status_) || !_IS_CREATE_(socket_handle->status_) )
		return _err_object_create;

	*state = _false;
	*state = FD_ISSET( socket_handle->socket_, &(h->set_) ) ? _true : _false;
	return _ok;
}

u_long __cdecl select_io_tcp_append( _in_ _out_ SELECT_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle )
{
	u_long ret = 0;

	if ( !h || !socket_handle )
		return _err_input_para;

	if ( !_IS_INSTANCE_(h->status_) || !_IS_CREATE_(socket_handle->status_) )
		return _err_object_create;

	if ( ( h->set_.fd_count ) < ( sizeof(h->set_.fd_array)/sizeof(SOCKET) ) )
	{
		FD_SET( socket_handle->socket_, &(h->set_) );
		ret = _ok;
	}
	else
	{
		ret = _err_select_io_array_over;
	}
	return ret;	
}

u_long __cdecl select_io_tcp_delete( _in_ _out_ SELECT_IO_HANDLE * h, _in_ SOCKET_TCP_HANDLE * socket_handle )
{
	u_long ret = 0;

	if ( !h || !socket_handle )
		return _err_input_para;

	if ( !_IS_INSTANCE_(h->status_) || !_IS_CREATE_(socket_handle->status_) )
		return _err_object_create;

	FD_CLR( socket_handle->socket_, &(h->set_) );
	return _ok;
}

u_long __cdecl select_io_tcp_wait( _in_ _out_ SELECT_IO_HANDLE * read_handle, _in_ _out_ SELECT_IO_HANDLE * write_handle, _in_ _out_ SELECT_IO_HANDLE * except_handle, _in_ const long microseconds )
{
	struct timeval tm_val;
	struct timeval * tm_out = NULL;

	int select_state = 0;

	_BOOLEAN flags = _false;
	FD_SET * read_set = NULL;
	FD_SET * write_set = NULL;
	FD_SET * except_set = NULL;

	u_long ret = 0;

	if ( !read_handle && !write_handle && !except_handle )
		return _err_input_para;

	if ( read_handle )
	{
		if ( !_IS_INSTANCE_(read_handle->status_) )
			select_io_init(read_handle);
		else
			flags = _true;

		read_set = &(read_handle->set_);
	}
	if ( write_handle )
	{
		if ( !_IS_INSTANCE_(write_handle->status_) )
			select_io_init(write_handle);
		else
			flags = _true;

		write_set = &(write_handle->set_);
	}
	if ( except_handle )
	{
		if ( !_IS_INSTANCE_(except_handle->status_) )
			select_io_init(except_handle);
		else
			flags = _true;

		except_set = &(except_handle->set_);
	}
	if ( _IS_ERR_(flags) )
	{
		return _err_object_create;
	}
	if ( 0 < microseconds )
	{
		tm_val.tv_usec = microseconds % 1000000;
		tm_val.tv_sec  = microseconds / 1000000;
		tm_out = &tm_val;
	}
	select_state = select( 0, read_set, write_set, except_set, tm_out );

	if ( SOCKET_ERROR == select_state )
	{
		ret = wsa_get_error();

		if ( WSAEINVAL == ret )
			ret = _err_select_io_time_out;
	}
	else
	{
		ret = _ok;
	}
	return ret;
}




u_long __cdecl advanced_io_init( _in_ _out_ ADVANCED_IO_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
	{
		return _err_input_para;
	}
	if ( _IS_CREATE_(h->status_) )
	{
		ret = advanced_io_destroy( h );

		if ( _ok != ret )
			return ret;
	}
	h->status_ = _instance;
	h->completion_port_ = NULL;

	return _ok;
}

u_long __cdecl advanced_io_create( _in_ _out_ ADVANCED_IO_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
	{
		return _err_input_para;
	}
	if ( !( _IS_INSTANCE_(h->status_) ) )
	{
		ret = advanced_io_init( h );

		if ( _ok != ret )
			return ret;
	}
	else if ( _IS_CREATE_(h->status_) && _IS_NULLITY_POINTER_(h->completion_port_ ) )
	{
		return _ok;
	}
	h->completion_port_ = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	if( _IS_OK_POINTER_( h->completion_port_ ) )
	{
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = wsa_get_error();
	}
	return  ret;
}

u_long __cdecl advanced_io_destroy( _in_ _out_ ADVANCED_IO_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || (_IS_NULLITY_POINTER_( h->completion_port_ )) )
		return _err_object_create;

	if ( !CloseHandle( h->completion_port_ ) )
	{
		ret = wsa_get_error();
	}
	else
	{
		h->status_ = _destroy;
		ret = _ok;
	}
	return ret;
}

u_long __cdecl advanced_io_overlapp( _in_ const ADVANCED_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle )
{
	u_long ret = 0;

	if ( !h || socket_handle )
		return _err_input_para;

	if ( !( _IS_CREATE_(h->status_) ) || !( _IS_CREATE_(socket_handle->status_) ) )
		return _err_object_create;

	if( _IS_OK_POINTER_( CreateIoCompletionPort( (HANDLE)(socket_handle->socket_), h->completion_port_, (long)(socket_handle->socket_), 0 ) ) )
		return _ok;
	else
		return wsa_get_error();
}

u_long __cdecl advanced_io_receive( _in_ const ADVANCED_IO_HANDLE * h, _in_ _out_ const SOCKET_TCP_HANDLE * socket_handle, _out_ u_long * recv_len, _in_ const long milliseconds )
{
	long time_out = 0;
	OVERLAPPED		overlapped;
	u_long ret = 0;

	if ( !h || socket_handle || !recv_len )
		return _err_input_para;

	if ( !( _IS_CREATE_(h->status_) ) || !( _IS_CREATE_(socket_handle->status_) ) )
		return _err_object_create;

	if ( 0 > milliseconds )
		time_out = INFINITE;
	else
		time_out = milliseconds;

	if( GetQueuedCompletionStatus( h->completion_port_, recv_len, (LPDWORD)&socket_handle->socket_, (LPOVERLAPPED *) &overlapped, time_out) )
		return _ok;
	else
		return wsa_get_error();
}