// Crude Debugger.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Crude Debugger.h"
#include "Crude DebuggerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrudeDebuggerApp

BEGIN_MESSAGE_MAP(CCrudeDebuggerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCrudeDebuggerApp construction

CCrudeDebuggerApp::CCrudeDebuggerApp()
{
//	char output_str[32];
	//char chbufferline[100];

	//chbufferline[50]=0;
	//chbufferline[49]=0x82;
	//chbufferline[48] = 0xDC;

	//// unsigned char buff[3]={0xDC,0x82,0x00};
	//unsigned long val=chbufferline[50] << 16 | chbufferline[49] << 8 | chbufferline[48];

	//val=((unsigned char)chbufferline[50] << 16 )| 
	//	((unsigned char)chbufferline[49] << 8 )|
	//	(unsigned char)chbufferline[48];


 //
//sprintf(output_str, "%02X%02X%02X",  chbufferline[50], chbufferline[49], chbufferline[48]);
//
 //unsigned long val=MAKELONG(MAKEWORD(chbufferline[48], chbufferline[49]), MAKEWORD(chbufferline[50],0) );
//
// val=((int)chbufferline[48]<<16 ); // |  chbufferline[49]<<8 |  chbufferline[48];
//

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCrudeDebuggerApp object

CCrudeDebuggerApp theApp;


// CCrudeDebuggerApp initialization

BOOL CCrudeDebuggerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CCrudeDebuggerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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
