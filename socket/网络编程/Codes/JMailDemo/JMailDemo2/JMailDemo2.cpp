// JMailDemo2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "JMailDemo2.h"
#include "JMailDemo2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2App

BEGIN_MESSAGE_MAP(CJMailDemo2App, CWinApp)
	//{{AFX_MSG_MAP(CJMailDemo2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2App construction

CJMailDemo2App::CJMailDemo2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJMailDemo2App object

CJMailDemo2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2App initialization

BOOL CJMailDemo2App::InitInstance()
{
	AfxEnableControlContainer();

	::CoInitialize(NULL);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CJMailDemo2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CJMailDemo2App::ExitInstance() 
{
	::CoUninitialize();
	
	return CWinApp::ExitInstance();
}
