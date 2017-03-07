#pragma once



#include "protocol_interface.h"
#include <winsock2.h>



enum
{
	_err_fini = _err_socket_start + 1,//∑÷≈‰ƒ⁄¥Ê ß∞‹
	_err_select_io_array_over,
	_err_completed_immediately,
	_err_select_io_time_out
};


u_long __cdecl socket_init(void);
u_long __cdecl socket_fini(void);

#define _IS_ASYNC_ERR_( errors )				    _err_completed_immediately == (errors) 
//#define _IS_ASYNC_SOCKET_ERR_RESULT_( ret )			_IS_ERR_( (ret).result_ ) && _IS_ASYNC_ERR_( (ret).error_ )
#define _IS_ASYNC_SOCKET_ERR_RESULT_( ret )			_IS_ASYNC_ERR_( ret )

#define _IS_TIME_OUT_ERR_( errors )				    _err_select_io_time_out == (errors) 
//#define _IS_SELECT_IO_ERR_RESULT_( ret )			_IS_ERR_( (ret).result_ ) && _IS_TIME_OUT_ERR_( (ret).error_ )
#define _IS_SELECT_IO_ERR_RESULT_( ret )			_IS_TIME_OUT_ERR_( ret )

typedef struct sockaddr_in SOCK_ADDR;

typedef struct __tag_SOCKET_TCP_HANDLE
{

	_STATUS		status_;
	SOCKET		socket_;
	SOCK_ADDR	addr_;
}
SOCKET_TCP_HANDLE;


extern u_long __cdecl socket_tcp_create		(
												_in_ _out_ SOCKET_TCP_HANDLE * h
											);

extern u_long __cdecl socket_tcp_destroy	(
												_in_ _out_ SOCKET_TCP_HANDLE * h
											);


extern u_long __cdecl socket_tcp_read		(
												_in_ const SOCKET_TCP_HANDLE * h,
												_in_ _out_ u_char * buff,
												_in_ _out_ u_long * len,
												_in_ const int flags
											);

extern u_long __cdecl socket_tcp_write		(
												_in_ const SOCKET_TCP_HANDLE * h,
												_in_ const u_char * buff,
												_in_ _out_ u_long * len,
												_in_ const int flags
											);

extern u_long __cdecl socket_tcp_accept		(
												_in_ const SOCKET_TCP_HANDLE * h,
												_in_ _out_ SOCKET_TCP_HANDLE * client
											);

extern u_long __cdecl socket_tcp_listen		(
												_in_ const SOCKET_TCP_HANDLE * h,
												_in_ const int backlog
											);

extern u_long __cdecl socket_tcp_bind		(
												_in_ const SOCKET_TCP_HANDLE * h
											);

extern u_long __cdecl socket_tcp_connect	(
												_in_ const SOCKET_TCP_HANDLE * h
											);


extern u_long __cdecl socket_tcp_init		(
												_in_ _out_ SOCKET_TCP_HANDLE * h
											);

extern u_long __cdecl socket_set_addr		(
												_in_ _out_ SOCKET_TCP_HANDLE * h,
												_in_ const u_char * ip,
												_in_ const u_short host_short
											);

extern u_long __cdecl socket_get_ip			(
												_in_ const SOCKET_TCP_HANDLE * h,
												_out_ u_char * ip
											);



extern u_long __cdecl socket_tcp_acceptor_create	(
														_in_ _out_ SOCKET_TCP_HANDLE * h,
														_in_ const u_short host_short
													);

extern u_long __cdecl socket_tcp_connector_create	(
														_in_ _out_ SOCKET_TCP_HANDLE * h,
														_in_ const char * ip,
														_in_ const u_short host_short
													);

extern u_long __cdecl socket_tcp_read_block			(
														 _in_ const SOCKET_TCP_HANDLE * h,
														 _in_ _out_ u_char * buff,
														 _in_ _out_ u_long * len,
														 _in_ const u_long block_size
													 );

extern u_long __cdecl socket_tcp_write_block		(
														 _in_ const SOCKET_TCP_HANDLE * h,
														 _in_ const u_char * buff,
														 _in_ _out_ u_long * len,
														 _in_ const u_long block_size
													);

extern u_long __cdecl socket_tcp_verify_read		(
														 _in_ const SOCKET_TCP_HANDLE * h,
														 _in_ _out_ u_char * buff,
														 _in_ _out_ u_long * len,
														 _in_ const u_long block_size,
														 _in_ const u_char * verify
													 );

extern u_long __cdecl socket_tcp_verify_write		(
														 _in_ const SOCKET_TCP_HANDLE * h,
														 _in_ const u_char * buff,
														 _in_ _out_ u_long * len,
														 _in_ const u_long block_size,
														 _in_ const u_char * verify
													 );

extern u_long __cdecl async_socket_tcp_acceptor_create(
														_in_ _out_ SOCKET_TCP_HANDLE * h,
														_in_ const u_short host_short
														);

extern u_long __cdecl async_socket_tcp_accept		(
														_in_ const SOCKET_TCP_HANDLE * h,
														_in_ _out_ SOCKET_TCP_HANDLE * client
													);

typedef struct __tag_SELECT_IO_HANDLE
{
	_STATUS		status_;
	FD_SET		set_;
}
SELECT_IO_HANDLE;


u_long __cdecl select_io_init( _in_ _out_ SELECT_IO_HANDLE * h );
u_long __cdecl select_io_tcp_is_exist( _in_ const SELECT_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle, _out_ _BOOLEAN * state );
u_long __cdecl select_io_tcp_append( _in_ _out_ SELECT_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle );
u_long __cdecl select_io_tcp_delete( _in_ _out_ SELECT_IO_HANDLE * h, _in_ SOCKET_TCP_HANDLE * socket_handle );
u_long __cdecl select_io_tcp_wait( _in_ _out_ SELECT_IO_HANDLE * read_handle, _in_ _out_ SELECT_IO_HANDLE * write_handle, _in_ _out_ SELECT_IO_HANDLE * except_handle, _in_ const long microseconds );


typedef struct __tag_ADVANCED_IO_HANDLE
{
	_STATUS		status_;
	HANDLE		completion_port_;
	
}
ADVANCED_IO_HANDLE;


u_long __cdecl advanced_io_init( _in_ _out_ ADVANCED_IO_HANDLE * h );

u_long __cdecl advanced_io_create( _in_ _out_ ADVANCED_IO_HANDLE * h );

u_long __cdecl advanced_io_destroy( _in_ _out_ ADVANCED_IO_HANDLE * h );

u_long __cdecl advanced_io_overlapp( _in_ const ADVANCED_IO_HANDLE * h, _in_ const SOCKET_TCP_HANDLE * socket_handle );

u_long __cdecl advanced_io_receive( _in_ const ADVANCED_IO_HANDLE * h, _in_ _out_ const SOCKET_TCP_HANDLE * socket_handle, _out_ u_long * recv_len, _in_ const long milliseconds );