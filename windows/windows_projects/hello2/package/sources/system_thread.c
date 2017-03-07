#include "../headers/system_thread.h"
#include <stdio.h>


#pragma warning(disable:4096 4996 4013)


#define _IS_ERR_THREAD_( h ) (NULL== (h)->handle_)


u_long __cdecl thread_init( _in_ _out_ THREAD_HANDLE * h, _in_ const u_char * name )
{
	u_long ret = 0;

	if ( !h || !name )
		return _err_input_para;

	switch (h->status_)
	{
	case _instance:
	case _callback:
		break;
	default:
		ret = thread_destroy( h, 0 );
		if ( _ok != ret )
			return ret;
		else
			break;
	}
	h->status_ = _instance;

	memset( (h->name_), 0, sizeof(h->name_) );
	strcpy( (h->name_), name );
	h->handle_ = NULL;

	return _ok;
}


unsigned int __stdcall thread_entry( void * argument )
{
	__try
	{
		
	}
	__finally
	{
		//MessageBox(NULL, "", "", MB_OK);
		thread_exit( 0 );
	}
	return 0;
}



u_long __cdecl thread_create( _in_ _out_ THREAD_HANDLE * h, _in_ unsigned (__stdcall * initialcode) (void *), _in_ void * argument, _in_ const u_char * thread_name )
{
	u_long ret = 0;

	if ( !h || !initialcode || !argument || !thread_name )
		return _err_input_para;

	switch (h->status_)
	{
	case _create:
	case _thread_running:
	case _thread_waitting:
		ret = thread_wait( h, 0 );
		switch (ret)
		{
		case _err_thread_wait_time_out:
			return _ok;
		default:
			if (_ok != ret)
				return ret;
		}
		break;
	case _instance:
	case _thread_stop:
	default:
		ret = thread_init( h, thread_name );
		if ( _ok != ret )
			return ret;
		else
			break;
	}

	h->handle_ = (HANDLE)_beginthreadex( 0, 0, initialcode, argument, 0, &(h->u_id ) );

	if ( !(_IS_ERR_THREAD_( h )) )
	{
		strcpy(h->name_, thread_name);
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}

u_long __cdecl thread_wait( _in_ const THREAD_HANDLE * h, _in_ const long ms )
{
	u_long ret = 0;

	if ( !h )
		ret = _err_input_para;

	if ( _IS_ERR_THREAD_( h ) )
		ret = _err_object_create;

	switch( WaitForSingleObject( h->handle_, ms ) )
	{
	case WAIT_OBJECT_0:
		ret = _ok;		break;
	case WAIT_TIMEOUT:
		ret = _err_thread_wait_time_out;	break;
	default:
		ret = get_error();	break;
	}
	return ret;
}

u_long __cdecl thread_exit( _in_ const unsigned retval )
{
	u_long ret = 0;

	_endthreadex( retval );

	return _ok;
}

u_long __cdecl thread_destroy( _in_ THREAD_HANDLE * h, _in_ const long ms  )
{
	u_long ret = 0;

	if ( !h )
		return _err_input_para;

	if ( _IS_ERR_THREAD_( h ) )
		return _err_object_create;

	ret = thread_wait( h, ms );
	switch (ret)
	{
	case _ok:
		break;
	case _err_thread_wait_time_out:
		return _err_object_destroy;
	default:
		return ret;
	}
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