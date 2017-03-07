// ExtensionDLLTestExe.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ExtensionDLLTestExe.h"
#include "ExtensionDLLTestExeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CExtensionDLLTestExeApp
//
BEGIN_MESSAGE_MAP(CExtensionDLLTestExeApp, CWinApp)
	//{{AFX_MSG_MAP(CExtensionDLLTestExeApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CExtensionDLLTestExeApp::CExtensionDLLTestExeApp()
{
}

// The one and only CExtensionDLLTestExeApp object
//
CExtensionDLLTestExeApp theApp;

// CExtensionDLLTestExeApp initialization
//
BOOL CExtensionDLLTestExeApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

//#ifdef _DEBUG
//	HMODULE hResource = ::LoadLibrary( 
//		_T( "ExtensionDLLTestd.dll" ));
//#else
//	HMODULE hResource = ::LoadLibrary( 
//		_T( "ExtensionDLLTest.dll" ));
//#endif

	CExtensionDLLTestExeDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

//	::FreeLibrary( hResource );

	return FALSE;
}
