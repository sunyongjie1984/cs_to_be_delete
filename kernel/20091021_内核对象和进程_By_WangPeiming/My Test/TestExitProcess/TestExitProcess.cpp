// TestExitProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestExitProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

class A
{
public:
    A() { cout<<"construct class A!"<<endl; }
    ~A() { cout<<"destruct class A!"<<endl; }
};

DWORD WINAPI Thread1( LPVOID lpParameter )
{
    A a;
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
        DWORD dThreadId;
        HANDLE hRes = CreateThread( NULL, 0, Thread1, NULL, 0, &dThreadId );
//        TerminateThread( hRes, 0 );
//		TerminateProcess( GetCurrentProcess(),5);
        WaitForSingleObject( hRes, INFINITE );
        CloseHandle( hRes );
	}

	return nRetCode;
}


