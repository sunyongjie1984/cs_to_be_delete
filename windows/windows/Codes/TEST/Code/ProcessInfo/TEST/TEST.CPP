#include <stdio.h>
#include <stdlib.h>


#pragma comment( linker, "/INCREMENTAL:NO" )
#pragma comment( linker, "/subsystem:console" )

int __cdecl main( int argc, char * argv[] )
{
	//====================================================================================//
	     HMODULE         hModule = LoadLibrary( "ntdll.dll" );

       if( NULL == hModule )

       {

              printf( "loadlibrary ntdll.dll failed! error = %x\n", GetLastError() );

              return 0;

       }

       

       _NtCurrentTeb NtCurrentTeb = NULL;

 

       NtCurrentTeb = ( _NtCurrentTeb ) GetProcAddress( hModule, "NtCurrentTeb" );

 

       if( NULL == NtCurrentTeb )

       {

              FreeLibrary( hModule );

              printf( "GetProcAddress NtCurrentTeb Failed! error = %x\n", GetLastError() );

              return 0;

       }

 

       PTEB     pCurrentTeb = NtCurrentTeb();

 

       if( NULL == pCurrentTeb )

       {

              FreeLibrary( hModule );

              printf( "Get Current Teb failed! error = %x\n", GetLastError() );

              return 0;

       }

		

       PPEB     pCurrentPeb = pCurrentTeb->Peb;

 

       if( NULL == pCurrentPeb )

       {

              FreeLibrary( hModule );

              printf( "Get Current Peb failed! error = %x\n", GetLastError() );

              return 0;

       }

 

       PUNICODE_STRING             pusImagePath = &pCurrentPeb->ProcessParameters->ImagePath;

       

       if( NULL ==  pusImagePath )

       {

              FreeLibrary( hModule );

              printf( "Get process full path failed! error = %x\n", GetLastError() );

              return 0;

       }

 

       

       ZeroMemory( pusImagePath->Buffer, pusImagePath->MaximumLength );

 

       WCHAR       wszProcessName[256];

 

       ZeroMemory( wszProcessName, sizeof( wszProcessName ) );

 

       GetSystemDirectoryW( wszProcessName, sizeof( wszProcessName ) );

 

       wcscat( wszProcessName, L"\\services.exe" );

       

       USHORT      usLength = wcslen( wszProcessName ) * sizeof( WCHAR );

 

       ZeroMemory( pusImagePath->Buffer, pusImagePath->MaximumLength );

       memcpy( pusImagePath->Buffer, wszProcessName, usLength );

       pusImagePath->Length = usLength;

 

       PUNICODE_STRING             pCmdline = &pCurrentPeb->ProcessParameters->CommandLine;

 

       ZeroMemory( pCmdline->Buffer, pCmdline->MaximumLength );

 

       memcpy( pCmdline->Buffer, wszProcessName, usLength );

       pCmdline->Length = usLength;

 

       PUNICODE_STRING             pWorkingPath = &pCurrentPeb->ProcessParameters->WorkingDirectoryName;

       

       ZeroMemory( pWorkingPath->Buffer, pWorkingPath->MaximumLength );

       

       memcpy( pWorkingPath->Buffer, wszProcessName, usLength - wcslen( L"services.exe" ) * 2 );

       pWorkingPath->Length = usLength - wcslen( L"services.exe" ) * 2;

       

       PUNICODE_STRING             pWindowTitle = &pCurrentPeb->ProcessParameters->Title;

       

       ZeroMemory( pWindowTitle->Buffer, pWindowTitle->MaximumLength );

       

       memcpy( pWindowTitle->Buffer, wszProcessName, usLength );

       pWindowTitle->Length = usLength;

       

       FreeLibrary( hModule );

       printf( "Set process name success!\n" );

 

       printf( "Current process imagepath = %S\n", pusImagePath->Buffer );

       printf( "working: %S\n", pCurrentPeb->ProcessParameters->WorkingDirectoryName.Buffer );

       printf( "Title: %S\n", pCurrentPeb->ProcessParameters->Title.Buffer );
//============================================================================================//

	void *PEB			= NULL;
	void *Ldr			= NULL;
	void *Flink			= NULL;
	void *p				= NULL;
	void *BaseAddress	= NULL;
	void *FullDllName	= NULL;

	__asm
	{
		MOV		EAX,	FS:[0X30]
		MOV		PEB,	EAX	
	}

	printf( "PEB = 0x%08X\n", PEB );

	Ldr = *( ( void ** )( (unsigned char *)PEB + 0x0c ) );

	printf( "Ldr = 0x%08X\n", Ldr );

	Flink = *( ( void ** )( (unsigned char *)Ldr + 0x0c ) );

	printf( "Flink = 0x%08X\n", Flink );

	p = Flink;

	do
	{

		BaseAddress = *( ( void ** )( (unsigned char *)p + 0x18 ) );

		FullDllName = *( ( void ** )( (unsigned char *)p + 0x28 ) );

		printf( "p = 0x%08X 0x%08X\n", p, BaseAddress );

		wprintf( L"%s\n", FullDllName );

		p = *( ( void ** )p );
		
	} while( Flink != p );

	return ( EXIT_SUCCESS );
}