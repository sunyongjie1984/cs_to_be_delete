// TestHandle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

DWORD WINAPI Thread1( LPVOID lpParameter )
{
    Sleep(1000);
    cout<<"Child thread Use GetCurrentThread "<<GetCurrentThread()<<endl;
    HANDLE hThreadHandle;
    DuplicateHandle(
        GetCurrentProcess(),
        GetCurrentThread(),
        GetCurrentProcess(),
        &hThreadHandle,
        0, FALSE, DUPLICATE_SAME_ACCESS
    );
    cout<<"After DuplicateHandle, the child thread handle "<<hThreadHandle<<endl;

    return 1;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
        // TODO: code your application's behavior here.
        cout<<"Parent thread Use GetCurrentThread "<<GetCurrentThread()<<endl;
        DWORD dThreadId;
        HANDLE hRes = CreateThread( NULL, 0, Thread1, NULL, 0, &dThreadId );
        cout<<"Child thread real Handle "<<hRes<<endl;
        WaitForSingleObject( hRes, INFINITE );
        CloseHandle( hRes );
	}

	return nRetCode;
}


