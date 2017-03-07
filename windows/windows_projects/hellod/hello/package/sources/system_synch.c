#include "../headers/system_synch.h"


#pragma warning(disable:4096 4996 4013)


void synch_begin(_BOOLEAN * synch_flag, const char * debug_out)
{
	if ( _true == *synch_flag )
		printf(debug_out);
	else
		*synch_flag = _true;
}

void synch_end(_BOOLEAN * synch_flag)
{
	*synch_flag = _false;
}

#ifdef _windows_sys_
_ERROR __cdecl mutex_os_init( _in_ _out_ MUTEX_HANDLE * h )
{
	h->status_ = _initialize;
	h->handle_ = NULL;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl mutex_os_init( _in_ _out_ MUTEX_HANDLE * h )
{
	h->status_ = _initialize;
	h->handle_ = PTHREAD_MUTEX_INITIALIZER;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_linux_sys_

#ifdef _windows_sys_
_ERROR __cdecl mutex_os_open( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * mutex_name )
{
	_ERROR ret = _failed;

	mutex_os_init( h );
	strcpy(h->name_, mutex_name);

	h->handle_ = OpenMutex( MUTEX_ALL_ACCESS, FALSE, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}
#endif//_windows_sys_


#ifdef _windows_sys_
_ERROR __cdecl mutex_os_create( _in_ _out_ MUTEX_HANDLE * h, _in_ const int initial_owner,	_in_ const u_char * mutex_name )
{
	_ERROR ret = _failed;

	mutex_os_init( h );
	strcpy(h->name_, mutex_name);
	
	h->handle_ = CreateMutex( NULL, initial_owner, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl mutex_os_create( _in_ _out_ MUTEX_HANDLE * h, _in_ const int initial_owner,	_in_ const u_char * mutex_name )
{
	_ERROR ret = _failed;
		
	mutex_os_init( h );
	strcpy(h->name_, mutex_name);

	if ( 0 != pthread_mutexattr_init(&(h->attr_)) )
		return _failed;

	if ( 0 == pthread_mutexattr_settype(&(h->attr_), PTHREAD_MUTEX_FAST_NP/*PTHREAD_MUTEX_RECURSIVE_NP*//*PTHREAD_MUTEX_ERRORCHECK_NP*/) )
		return _failed;

	/*
	//互斥锁的初始化,函数成功完成之后会返回零，其他任何返回值都表示出现了错误
	//函数成功执行后，互斥锁被初始化为锁住态
	int pthread_mutex_init	(
								pthread_mutex_t *restrict mutex,
								const pthread_mutexattr_t *restrict attr//新建互斥锁的属性。如果参数attr为空，则使用默认的互斥锁属性，默认属性为快速互斥锁 。互斥锁的属性在创建锁的时候指定
							);
	*/
	switch ( pthread_mutex_init( &(h->handle_), &mutex_attr ) )
	{
	case 0:
		h->status_ = _create;
		ret = _ok;
		break;
	default:
		ret = _failed;
		break;
	}
	return ret;
}
#endif//_linux_sys_


#ifdef _windows_sys_
_ERROR __cdecl mutex_os_lock( _in_ const MUTEX_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

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
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl mutex_os_lock( _in_ const MUTEX_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

	/*
	//在成功完成之后会返回零。其他任何返回值都表示出现了错误
	int pthread_mutex_lock	(
								pthread_mutex_t *mutex
							);
	*/
	switch( pthread_mutex_lock( &(h->handle_) ) )
	{
	case 0:
		{
			ret = _ok;
			break;
		}
	default:
		{
			ret = _failed;
			break;
		}
	}
	return ret;
}
#endif//_linux_sys_


#ifdef _windows_sys_
_ERROR __cdecl mutex_os_unlock( _in_ const MUTEX_HANDLE * h )
{	
	return ( ReleaseMutex( h->handle_ ) ) ? _ok : get_error();
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl mutex_os_unlock( _in_ const MUTEX_HANDLE * h )
{
	/*
	int pthread_mutex_unlock(pthread_mutex_t *mutex);
	*/
	return ( 0 == pthread_mutex_unlock( &(h->handle_) ) ) ? _ok : _failed;
}
#endif//_linux_sys_


#ifdef _windows_sys_
_ERROR __cdecl mutex_os_destroy( _in_ _out_ MUTEX_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( CloseHandle( h->handle_ ) )
	{
		mutex_os_init(h);
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
_ERROR __cdecl mutex_os_destroy( _in_ _out_ MUTEX_HANDLE * h )
{
	_ERROR ret = _failed;

	/*
	//int pthread_mutex_destroy (pthread_mutex_t* mutex); //清除互斥锁
	*/
	if ( 0 == pthread_mutex_destroy( &(h->handle_) ) )
	{
		mutex_os_init(h);
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
_ERROR __cdecl event_os_init( _in_ _out_ EVENT_HANDLE * h )
{
	h->status_ = _initialize;
	h->handle_ = NULL;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_windows_sys_



#ifdef _windows_sys_
_ERROR __cdecl event_os_open( _in_ _out_ EVENT_HANDLE * h, _in_ const u_char * event_name )
{
	_ERROR ret = _failed;

	event_os_init( h );
	strcpy(h->name_, event_name);

	h->handle_ = OpenEvent( EVENT_ALL_ACCESS, FALSE, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}
#endif//_windows_sys_


#ifdef _windows_sys_
_ERROR __cdecl event_os_create( _in_ _out_ EVENT_HANDLE * h, _in_ const int manual_reset, _in_ const int initial_owner, _in_ const u_char * event_name )
{
	_ERROR ret = _failed;

	event_os_init( h );
	strcpy(h->name_, event_name);

	h->handle_ = CreateEvent( NULL, manual_reset, initial_owner, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}
#endif//_windows_sys_



#ifdef _windows_sys_
_ERROR __cdecl event_os_wait( _in_ const EVENT_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

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
#endif//_windows_sys_


#ifdef _windows_sys_
_ERROR __cdecl event_os_set( _in_ _out_ EVENT_HANDLE * h, _in_ const _BOOLEAN owner_flag )
{
	_ERROR ret = 0;

	switch(owner_flag)
	{
	case _true:
		{
			ret = ( SetEvent( h->handle_ ) ) ? _ok : get_error();
			break;
		}
	case _false:
		{
			ret = ( ResetEvent( h->handle_ ) ) ? _ok : get_error();
			break;
		}
	default:
		{
			ret = _failed;
			break;
		}
	}
	return ret;
}
#endif//_windows_sys_


#ifdef _windows_sys_
u_long __cdecl event_os_destroy( _in_ _out_ EVENT_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( CloseHandle( h->handle_ ) )
	{
		event_os_init(h);
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}
#endif//_windows_sys_




_ERROR __cdecl semaphore_os_init		( _in_ _out_ SEMAPHORE_HANDLE * h )
{
	h->status_ = _initialize;
	h->handle_ = NULL;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}


_ERROR __cdecl semaphore_os_open			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_char * semaphore_name )
{
	_ERROR ret = _failed;

	semaphore_os_init( h );
	strcpy(h->name_, semaphore_name);

	h->handle_ = OpenSemaphore( SEMAPHORE_ALL_ACCESS, FALSE, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}


_ERROR __cdecl semaphore_os_create		(
											_in_ _out_ SEMAPHORE_HANDLE * h,
											_in_ const u_long initial_count, 
											_in_ const u_long maximum_count,
											_in_ const u_char * semaphore_name
										)
{
	_ERROR ret = _failed;

	semaphore_os_init( h );
	strcpy(h->name_, semaphore_name);

	h->handle_ = CreateSemaphore( NULL, initial_count, maximum_count, h->name_ );

	ret = get_error();

	if ( NULL != h->handle_ )
	{
		switch (ret)
		{
		case 0:
			ret = _ok;
			break;
		case ERROR_ALREADY_EXISTS:
			ret = _err_exist;
			break;
		}
		h->status_ = _create;
	}
	return ret;
}


_ERROR __cdecl semaphore_os_wait			( _in_ const SEMAPHORE_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

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


_ERROR __cdecl semaphore_os_set				( _in_ const SEMAPHORE_HANDLE * h )
{
	return ReleaseSemaphore( h->handle_, 1, NULL ) ? _ok : get_error();
}

_ERROR __cdecl semaphore_os_destroy			( _in_ _out_ SEMAPHORE_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( CloseHandle( h->handle_ ) )
	{
		semaphore_os_init(h);
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}





_ERROR __cdecl mutex_create( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * mutex_name )
{
	_ERROR ret = _failed;

	if ( (NULL == h) || (NULL == mutex_name) )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		switch( ret = mutex_os_create(h, 0, mutex_name) )
		{
		case _ok:
			break;
		case _err_exist:
			if ( _ok == (ret = mutex_os_destroy( h )) )
				ret = mutex_os_open(h, mutex_name);
			break;
		default:
			break;
		}
		return ret;
	}
	return _err_exist;
}

_ERROR __cdecl mutex_lock( _in_ const MUTEX_HANDLE * h )
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
	return mutex_os_lock(h, -1);
}


_ERROR __cdecl mutex_unlock( _in_ const MUTEX_HANDLE * h )
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
	return mutex_os_unlock(h);
}

_ERROR __cdecl mutex_destroy( _in_ _out_ MUTEX_HANDLE * h )
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
	return mutex_os_destroy(h);
}


_ERROR __cdecl mutex_facility_lock( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * lock_name )
{
	_ERROR ret = _failed;

	switch (ret = mutex_create(h, lock_name))
	{
		case _ok:
		case _err_exist:
			ret = mutex_lock(h);
			break;
	}
	return ret;
}

_ERROR __cdecl mutex_facility_unlock( _in_ _out_ MUTEX_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( _ok == (ret = mutex_unlock(h)) )
	{
		ret = mutex_destroy(h);
	}
	return ret;
}


_ERROR __cdecl event_create( _in_ _out_ EVENT_HANDLE * h, _in_ const int manual_reset, _in_ const int initial_owner, _in_ const u_char * event_name )
{
	_ERROR ret = _failed;

	if ( (NULL == h) || (NULL == event_name) )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		switch (ret = event_os_create(h, manual_reset, initial_owner, event_name))
		{
		case _ok:
			break;
		case _err_exist:
			if ( _ok == (ret = event_os_destroy( h )) )
				ret = event_os_open(h, event_name);
			break;
		default:
			break;
		}
		return ret;
	}
	return _err_exist;
}

_ERROR __cdecl event_wait( _in_ const EVENT_HANDLE * h, _in_ const long ms )
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
	return event_os_wait(h, ms);
}


_ERROR __cdecl event_set( _in_ _out_ EVENT_HANDLE * h, _in_ const _BOOLEAN owner_flag )
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
	return event_os_set(h, owner_flag);
}


_ERROR __cdecl event_destroy( _in_ _out_ EVENT_HANDLE * h )
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
	return event_os_destroy(h);
}



_ERROR __cdecl event_lock_create( _in_ _out_ EVENT_HANDLE * h, _in_ const u_char * name )
{
	return event_create( h, 0, 1, name );
}

_ERROR __cdecl event_lock( _in_ _out_ EVENT_HANDLE * h )
{
	return event_wait( h, -1 );
}

_ERROR __cdecl event_unlock( _in_ _out_ EVENT_HANDLE * h )
{
	return event_set( h, _true );
}

_ERROR __cdecl event_facility_lock( _in_ _out_ EVENT_HANDLE * h, _in_ const u_char * lock_name )
{
	_ERROR ret = _failed;

	switch (ret = event_lock_create(h, lock_name))
	{
	case _ok:
	case _err_exist:
		ret = event_lock(h);
		break;
	}
	return ret;
}

_ERROR __cdecl event_facility_unlock( _in_ _out_ EVENT_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( _ok == (ret = event_unlock(h)) )
	{
		ret = event_destroy(h);
	}
	return ret;
}

_ERROR __cdecl semaphore_create			(
											_in_ _out_ SEMAPHORE_HANDLE * h, 
											_in_ const u_long maximum_count,
											_in_ const u_char * semaphore_name
										)
{
	_ERROR ret = _failed;

	if ( (NULL == h) || (NULL == semaphore_name) )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		switch( ret = semaphore_os_create(h, 0, maximum_count, semaphore_name) )
		{
		case _ok:
			break;
		case _err_exist:
			if ( _ok == (ret = semaphore_os_destroy( h )) )
				ret = semaphore_os_open(h, semaphore_name);
			break;
		default:
			break;
		}
		return ret;
	}
	return _err_exist;
}

u_long __cdecl semaphore_wait			( _in_ const SEMAPHORE_HANDLE * h, _in_ const long ms )
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
	return semaphore_os_wait(h, ms);
}

_ERROR __cdecl semaphore_set				( _in_ const SEMAPHORE_HANDLE * h )
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
	return semaphore_os_set(h);
}

_ERROR __cdecl semaphore_destroy			( _in_ _out_ SEMAPHORE_HANDLE * h )
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
	return semaphore_os_destroy(h);
}

_ERROR __cdecl semaphore_accept( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_long maximum_count, _in_ const u_char * semaphore_name, _in_ const long ms )
{
	_ERROR ret = _failed;

	switch ( ret = semaphore_create(h, maximum_count, semaphore_name) )
	{
	case _ok:
	case _err_exist:
		ret = semaphore_wait(h, ms);
		break;
	}
	return ret;
}

_ERROR __cdecl semaphore_send( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_long maximum_count, _in_ const u_char * semaphore_name )
{
	_ERROR ret = _failed;

	switch ( ret = semaphore_create(h, maximum_count, semaphore_name) )
	{
	case _ok:
	case _err_exist:
		if ( _ok == (ret = semaphore_set(h)) )
		{
			ret = semaphore_destroy(h);
		}
		break;
	}
	return ret;
}