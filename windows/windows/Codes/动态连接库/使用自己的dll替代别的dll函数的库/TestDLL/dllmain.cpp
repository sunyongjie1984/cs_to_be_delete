#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <ddraw.h>
#include "testdll.h"
#include "..\apihijack.h"

// Text buffer for sprintf
char Work[256];

HINSTANCE hDLL;

// Function pointer types.
typedef HRESULT (WINAPI *DirectDrawCreateEx_Type)( GUID FAR *lpGUID, LPVOID *lplpDD, REFIID iid, IUnknown FAR *pUnkOuter );

// Function prototypes.
HRESULT WINAPI MyDirectDrawCreateEx( GUID FAR * lpGuid, LPVOID  *lplpDD, REFIID  iid,IUnknown FAR *pUnkOuter );

// Hook structure.
enum
{
    D3DFN_DirectDrawCreateEx = 0
};

SDLLHook D3DHook = 
{
    "DDRAW.DLL",
    false, NULL,		// Default hook disabled, NULL function pointer.
    {
        { "DirectDrawCreateEx", MyDirectDrawCreateEx },
        { NULL, NULL }
    }
};

// Hook function.
HRESULT WINAPI MyDirectDrawCreateEx( GUID FAR * lpGuid, LPVOID  *lplpDD, REFIID  iid,IUnknown FAR *pUnkOuter )
{
    // Let the world know we're working.
    MessageBeep( MB_ICONINFORMATION );

    OutputDebugString( "TESTDLL: MyDirectDrawCreateEx called.\n" );

    DirectDrawCreateEx_Type OldFn = 
        (DirectDrawCreateEx_Type)D3DHook.Functions[D3DFN_DirectDrawCreateEx].OrigFn;
    return OldFn( lpGuid, lplpDD, iid, pUnkOuter );
}

// CBT Hook-style injection.
BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved )
{
    if ( fdwReason == DLL_PROCESS_ATTACH )  // When initializing....
    {
        hDLL = hModule;

        // We don't need thread notifications for what we're doing.  Thus, get
        // rid of them, thereby eliminating some of the overhead of this DLL
        DisableThreadLibraryCalls( hModule );

        // Only hook the APIs if this is the Everquest proess.
        GetModuleFileName( GetModuleHandle( NULL ), Work, sizeof(Work) );
        PathStripPath( Work );

        OutputDebugString( "TESTDLL checking process: " );
        OutputDebugString( Work );
        OutputDebugString( "\n" );

        if ( stricmp( Work, "bend.exe" ) == 0 )
            HookAPICalls( &D3DHook );
    }

    return TRUE;
}

// This segment must be defined as SHARED in the .DEF
#pragma data_seg (".HookSection")		
// Shared instance for all processes.
HHOOK hHook = NULL;	
#pragma data_seg ()

TESTDLL_API LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
    return CallNextHookEx( hHook, nCode, wParam, lParam); 
}

TESTDLL_API void InstallHook()
{
    OutputDebugString( "TESTDLL hook installed.\n" );
    hHook = SetWindowsHookEx( WH_CBT, HookProc, hDLL, 0 ); 
}

TESTDLL_API void RemoveHook()
{
    OutputDebugString( "TESTDLL hook removed.\n" );
    UnhookWindowsHookEx( hHook );
}
