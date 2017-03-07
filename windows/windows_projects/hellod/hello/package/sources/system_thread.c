#include "../headers/system_thread.h"
#include <stdio.h>


#pragma warning(disable:4096 4996 4013)


#ifdef _windows_sys_
_ERROR __cdecl thread_os_init( _in_ _out_ THREAD_HANDLE * h )
{
	h->status_		= _initialize;
	h->handle_		= NULL;
	h->initialcode_ = NULL;
	h->argument_	= NULL;
	h->u_id_		= 0;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_init( _in_ _out_ THREAD_HANDLE * h )
{
	h->status_		= _initialize;
	h->handle_		= 0;
	h->initialcode_ = NULL;
	h->argument_	= NULL;
	h->u_id_		= 0;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_linux_sys_


#ifdef _windows_sys_

unsigned __stdcall start_address( void * argument )
{
	__try
	{
		THREAD_HANDLE * h = (THREAD_HANDLE *)argument;

		if ( NULL != h )
		{
			if ( NULL != h->initialcode_ )
			{
				h->initialcode_( h->argument_, h->name_, h->u_id_ );
			}
		}
	}
	__finally
	{
		thread_os_exit( 0 );
	}
	return 0;
}

_ERROR __cdecl thread_os_create(
								_in_ _out_ THREAD_HANDLE * h,
								_in_ INITIAL_CODE initialcode,
								_in_ void * argument,
								_in_ const u_char * thread_name
								)
{
	_ERROR ret = _failed;	

	thread_os_init( h );

	h->argument_ = argument;
	h->initialcode_ = initialcode;
	strcpy(h->name_, thread_name);

	/*
	uintptr_t _beginthreadex( 
								void *security,
								unsigned stack_size,
								unsigned ( *start_address )( void * ),
								void *arglist,
								unsigned initflag,
								unsigned *thrdaddr 
							);
	*/
	h->handle_ = (HANDLE)_beginthreadex( 0, 0, &start_address, (void *)h, 0, &(h->u_id_ ) );

	if ( NULL != h->handle_ )
	{
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}
#endif//_windows_sys_

#ifdef _linux_sys_

void * start_routine(void * __arg)
{
	__try
	{
		THREAD_HANDLE * h = (THREAD_HANDLE *)__arg;

		if ( NULL != h )
		{
			if ( NULL != h->initialcode_ )
			{
				h->initialcode_( h->argument_, h->name_, h->u_id_ );
			}
		}
	}
	__finally
	{
		thread_os_exit( 0 );
	}
	return NULL;
}

_ERROR __cdecl thread_os_create(
								_in_ _out_ THREAD_HANDLE * h,
								_in_ INITIAL_CODE initialcode,
								_in_ void * argument,
								_in_ const u_char * thread_name
								)
{
	_ERROR ret = _failed;	

	thread_os_init( h );

	h->argument_ = argument;
	h->initialcode_ = initialcode;
	strcpy(h->name_, thread_name);

	/*
	//当创建线程成功时，函数返回0，若不为0则说明创建线程失败，
	//常见的错误返回代码为EAGAIN(表示系统限制创建新的线程，例如线程数目过多了)和EINVAL(表示第二个参数代表的线程属性值非法)
	extern int pthread_create __P	(
										(
											pthread_t *__thread,				//指向线程标识符的指针
											__const pthread_attr_t *__attr,		//设置线程属性
	　　									void *(*__start_routine) (void *),	//线程运行函数的起始地址
											void *__arg							//运行函数的参数
										)
									); 
	*/

	if ( 0 == pthread_create( &(h->handle_), NULL, &start_routine, __arg ) )
	{
		h->u_id_ = h->handle_;
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = _failed;
	}
	return ret;
}
#endif//_linux_sys_




#ifdef _windows_sys_
_ERROR __cdecl thread_os_wait( _in_ const THREAD_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

	/*
	DWORD WINAPI WaitForSingleObject(
										__in          HANDLE hHandle,
										__in          DWORD dwMilliseconds
									);
	*/

	switch( WaitForSingleObject( h->handle_, (-1 == ms) ? INFINITE : ms ) )
	{
	case WAIT_OBJECT_0:
		{
			ret = _ok;
			break;
		}
	case WAIT_TIMEOUT:
		{
			ret = _err_time_out;
			break;
		}
	default:
		{
			ret = get_error();
			break;
		}
	}
	return ret;
}
#endif _windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_wait( _in_ const THREAD_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;
	//_ERROR __thread_return = _failed;

	/*
	//这个函数是一个线程阻塞的函数，调用它的函数将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回。
	//如果执行成功，将返回0，如果失败则返回一个错误号
	extern int pthread_join __P	(
									(
										pthread_t __th,			//被等待的线程标识符
										void **__thread_return	//一个用户定义的指针，它可以用来存储被等待线程的返回值
									)
								); 
	*/
	switch( pthread_join( h->handle_, NULL )
	{
	case 0:
		{
			ret = _ok;
			break;
		}
	default:
		{
			ret = get_error();
			break;
		}
	}
	return ret;
}
#endif//_linux_sys_


#ifdef _windows_sys_
_ERROR __cdecl thread_os_exit( _in_ const unsigned retval )
{
	/*
	void _endthreadex( unsigned retval );
	*/
	_endthreadex( retval );

	return _ok;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_exit( _in_ const unsigned retval )
{
	/*
	//终止调用它的线程并返回一个指向某个对象的指针
	void pthread_exit(void* retval); 
	*/
	pthread_exit( NULL );

	return _ok;
}
#endif//_linux_sys_

#ifdef _windows_sys_
_ERROR __cdecl thread_os_destroy( _in_ THREAD_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( CloseHandle( h->handle_ ) )
	{
		thread_os_init(h);
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_destroy( _in_ THREAD_HANDLE * h )
{
	_ERROR ret = _ok;

	return ret;
}
#endif//_linux_sys_

_ERROR __cdecl thread_create		(
										_in_ _out_ THREAD_HANDLE * h,
										_in_ INITIAL_CODE initialcode,
										_in_ void * argument,
										_in_ const u_char * thread_name 
									)
{
	_ERROR ret = _failed;

	if ( (NULL == h) || (NULL == initialcode) || (NULL == thread_name) )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		return thread_os_create( h, initialcode, argument, thread_name );
	}
	return _err_exist;
}


_ERROR __cdecl thread_destroy	(
									_in_ THREAD_HANDLE * h,
									_in_ const long ms
								)
{
	_ERROR ret = _failed;

	if ( NULL == h )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		return _err_create;
	}
	if ( _ok == (ret = thread_os_wait(h, ms)) )
		return thread_os_destroy(h);
	else
		return ret;
}

