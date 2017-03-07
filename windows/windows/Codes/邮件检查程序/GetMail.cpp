
#include "stdafx.h"
#include "GetMail.h"
#include "GetMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetMailApp

BEGIN_MESSAGE_MAP(CGetMailApp, CWinApp)
	//{{AFX_MSG_MAP(CGetMailApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetMailApp construction

CGetMailApp::CGetMailApp()
{
}

CGetMailApp theApp;


BOOL CGetMailApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();	
#else
	Enable3dControlsStatic();
#endif

	CGetMailDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
