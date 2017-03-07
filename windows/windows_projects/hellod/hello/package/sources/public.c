
#include "../headers/public.h"
#include <stdio.h>
#include <memory.h>
#include <windows.h>


#pragma warning(disable:4096 4996 4013)


int __cdecl get_error( void )
{
	return GetLastError();
}


#if 0
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
#endif//0