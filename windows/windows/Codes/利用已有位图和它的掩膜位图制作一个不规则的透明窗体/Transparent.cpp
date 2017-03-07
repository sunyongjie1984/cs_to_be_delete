// Transparent.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Transparent.h"

#include "TransparentWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentApp

BEGIN_MESSAGE_MAP(CTransparentApp, CWinApp)
	//{{AFX_MSG_MAP(CTransparentApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentApp construction

CTransparentApp::CTransparentApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTransparentApp object

CTransparentApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTransparentApp initialization

BOOL CTransparentApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CTransparentWnd* pFrame = new CTransparentWnd;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources
	CRect rect(0, 0, 320, 150);
	pFrame->CreateTransparent("Transparent Test", rect, IDB_MASK, IDB_BACK);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTransparentApp message handlers

