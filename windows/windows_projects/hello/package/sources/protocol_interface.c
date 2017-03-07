
#include "../headers/protocol_interface.h"
#include <stdio.h>
#include <memory.h>
#include <windows.h>


#pragma warning(disable:4096 4996 4013)


int __cdecl get_error( void )
{
	return GetLastError();
}

void set_debug_depict(_in_ _out_ RESULT * ret)
{
#ifdef _DEBUG_DEPICT_
    if ( _IS_OK_POINTER_( ret ) )
    {
        memset( ret->file_, 0, sizeof(ret->file_) );
        sprintf( (char *)(ret->file_), "%s", __FILE__ );
        ret->line_ = __LINE__;
    }
#endif//_DEBUG_DEPICT_
}


RESULT __cdecl test_func_name( _in_ const u_char t, _in_ _out_ u_char * buff )
{
	RESULT ret;
	u_char * p = NULL;

	_INIT_RESULT_( ret )

    //ret.status_ = _true;

    //ret.status_ = _ok;

	if ( _IS_NULLITY_POINTER_( p ) )
	{
		p = (u_char *)&t;
	}
	if ( _IS_OK_POINTER_( p ) )
	{
		p = NULL;
	}
	_SET_RESULT_( ret, _ok, _true )

#if 0
	if ( _IS_NULLITY_POINTER_( ret ) )
	{
		p = (uchar *)&t;
	}
#endif//0

#if 0
	if ( _IS_NULLITY_POINTER_( t ) )
	{
		p = (uchar *)&t;
	}
#endif//0

#if 0
	_INIT_RESULT_( t )
#endif//0

	return ret;
}
