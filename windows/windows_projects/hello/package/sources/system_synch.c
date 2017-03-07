#include "../headers/system_synch.h"


#pragma warning(disable:4096 4996 4013)

#define _IS_ERR_EVENT_( h ) (NULL == (h)->handle_)
#define _IS_ERR_MUTEX_( h ) (NULL == (h)->handle_)


u_long __cdecl mutex_init( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * name )
{
	u_long ret = 0;

	if ( !h || !name )
		return _err_input_para;

	switch (h->status_)
	{
	case _create:
		ret = mutex_destroy( h );
		if ( _ok != ret )
			return ret;
		else
			break;
	default:
		break;
	}
	h->status_ = _instance;

	memset( (h->name_), 0, sizeof(h->name_) );
	strcpy( (h->name_), name );
	h->handle_ = NULL;
	return ret;
}

u_long __cdecl mutex_open( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * name )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl mutex_create( _in_ _out_ MUTEX_HANDLE * h, _in_ const int initial_owner,	_in_ const u_char * name )
{
	u_long ret = 0;

	ret = mutex_init( h, name );

	if ( _ok != ret )
		return ret;

	h->handle_ = CreateMutex( NULL, initial_owner, h->name_ );

	if ( _IS_ERR_MUTEX_(h) )
	{
		return _failed;
	}
	else
	{
		if ( ERROR_ALREADY_EXISTS == get_error() )
			ret = ERROR_ALREADY_EXISTS;
		else
			ret = _ok;
	}
	return ret;
}

u_long __cdecl mutex_wait( _in_ const MUTEX_HANDLE * h, _in_ const long ms )
{
	u_long ret = 0;

	if ( !h )
		ret = _err_input_para;

	if ( _IS_ERR_MUTEX_( h ) )
		ret = _err_object_create;

	switch( WaitForSingleObject( h->handle_, ms ) )
	{
	case WAIT_OBJECT_0:
		ret = _ok;		break;
	case WAIT_TIMEOUT:
		ret = _err_event_wait_time_out;	break;
	default:
		ret = get_error();	break;
	}
	return ret;
}

u_long __cdecl mutex_destroy( _in_ _out_ MUTEX_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || (_IS_ERR_MUTEX_( h )) )
		return _err_object_create;

	if ( CloseHandle( h->handle_ ) )
	{
		h->status_ = _callback;
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}

u_long __cdecl mutex_release( _in_ const MUTEX_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
	return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || _IS_ERR_MUTEX_(h) )
		return _err_object_create;
	
	return ( ReleaseMutex( h->handle_ ) ) ? _ok : get_error();
}

u_long __cdecl mutex_lock_create( _in_ _out_ MUTEX_HANDLE * h, _in_ const u_char * name )
{
	return mutex_create(h, 1, name);
}

u_long __cdecl mutex_lock( _in_ _out_ MUTEX_HANDLE * h )
{
	return mutex_wait( h, INFINITE );
}

u_long __cdecl mutex_unlock( _in_ _out_ MUTEX_HANDLE * h )
{
	return mutex_release( h );
}



u_long __cdecl event_init( _in_ _out_ EVENT_HANDLE * h, _in_ const u_char * name )
{
	u_long ret = 0;

	if ( !h || !name )
		return _err_input_para;

	switch (h->status_)
	{
	case _create:
		ret = event_destroy( h );
		if ( _ok != ret )
			return ret;
		else
			break;
	default:
		break;
	}
	h->status_ = _instance;

	memset( (h->name_), 0, sizeof(h->name_) );
	strcpy( (h->name_), name );
	h->handle_ = NULL;
	return ret;
}



u_long __cdecl event_create( _in_ _out_ EVENT_HANDLE * h, _in_ const int manual_reset, _in_ const int initial_owner, _in_ const u_char * name )
{
	u_long ret = 0;

	ret = event_init( h, name );

	if ( _ok != ret )
		return ret;

	h->handle_ = CreateEvent( NULL, manual_reset, initial_owner, h->name_ );

	if ( _IS_ERR_EVENT_(h) )
	{
		return _failed;
	}
	else
	{
		if ( ERROR_ALREADY_EXISTS == get_error() )
			ret = ERROR_ALREADY_EXISTS;
		else
			ret = _ok;
	}
	return ret;
}

u_long __cdecl event_destroy( _in_ _out_ EVENT_HANDLE * h )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || (_IS_ERR_EVENT_( h )) )
		return _err_object_create;

	if ( CloseHandle( h->handle_ ) )
	{
		h->status_ = _callback;
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}

u_long __cdecl event_wait( _in_ const EVENT_HANDLE * h, _in_ const long ms )
{
	u_long ret = 0;

	if ( !h )
		ret = _err_input_para;

	if ( _IS_ERR_EVENT_( h ) )
		ret = _err_object_create;

	switch( WaitForSingleObject( h->handle_, ms ) )
	{
	case WAIT_OBJECT_0:
		ret = _ok;		break;
	case WAIT_TIMEOUT:
		ret = _err_event_wait_time_out;	break;
	default:
		ret = get_error();	break;
	}
	return ret;
}


u_long __cdecl event_set( _in_ _out_ EVENT_HANDLE * h, _in_ const _BOOLEAN owner_flag )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( !(_IS_CREATE_(h->status_)) || _IS_ERR_EVENT_(h) )
		return _err_object_create;

	if ( _IS_OK_( owner_flag ) )
	{
		ret = ( SetEvent( h->handle_ ) ) ? _ok : get_error();
	}
	else if ( _IS_ERR_( owner_flag ) )
	{
		ret = ( ResetEvent( h->handle_ ) ) ? _ok : get_error();
	}
	return ret;
}


u_long __cdecl event_lock_create( _in_ _out_ EVENT_HANDLE * h, _in_ const u_char * name )
{
	return event_create( h, 0, 1, name );
}

u_long __cdecl event_lock( _in_ _out_ EVENT_HANDLE * h )
{
	return event_wait( h, INFINITE );
}

u_long __cdecl event_unlock( _in_ _out_ EVENT_HANDLE * h )
{
	return event_set( h, _true );
}


u_long __cdecl semaphore_init			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_char * name )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl semaphore_open			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_char * name )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl semaphore_create			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const int initial_owner, _in_ const u_char * name )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl semaphore_wait			( _in_ const SEMAPHORE_HANDLE * h, _in_ const long ms )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl semaphore_set				( _in_ const SEMAPHORE_HANDLE * h )
{
		u_long ret = 0;
	return ret;
}

u_long __cdecl semaphore_destroy			( _in_ _out_ SEMAPHORE_HANDLE * h )
{
		u_long ret = 0;
	return ret;
}