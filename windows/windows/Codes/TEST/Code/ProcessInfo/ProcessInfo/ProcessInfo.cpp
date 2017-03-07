/************************************************************************/
/*                                                                      */
/************************************************************************/
#include <stdio.h>
#include "windows.h"
#include "w2k_def.h"

#define LOADLIB_ntdll "ntdll.dll"

typedef ULONGLONG ( __stdcall * _NtCurrentTeb ) ( );

void main ( void )
{

	HMODULE	hModule_ntdll = ::LoadLibrary( LOADLIB_ntdll );
	
	_NtCurrentTeb NtCurrentTeb =
			( _NtCurrentTeb )GetProcAddress( hModule_ntdll, "NtCurrentTeb" );

	if ( NULL == NtCurrentTeb )
	{
		FreeLibrary( hModule_ntdll );
		printf( "GetProcAddress( NtCurrentTeb ) fail Error = %d\n\r", GetLastError() );
		return;
	}

	PTEB pTeb = ( PTEB )NtCurrentTeb ( );

	PPEB pCurrentPeb = pTeb->Peb;

}