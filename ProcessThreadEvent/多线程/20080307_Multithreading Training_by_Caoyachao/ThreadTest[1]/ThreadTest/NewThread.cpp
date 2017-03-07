// NewThread.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadTest.h"
#include "NewThread.h"
#include "ThreadTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HANDLE g_hEvent;
/////////////////////////////////////////////////////////////////////////////
// NewThread

IMPLEMENT_DYNCREATE(NewThread, CWinThread)

NewThread::NewThread()
{
}

NewThread::~NewThread()
{
}

BOOL NewThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int NewThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(NewThread, CWinThread)
	//{{AFX_MSG_MAP(NewThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
    ON_THREAD_MESSAGE( THREAD_MESSAGE1, OnMessage1 )
    ON_THREAD_MESSAGE( THREAD_MESSAGE2, OnMessage2 )
    ON_THREAD_MESSAGE( THREAD_MESSAGE3, OnMessage3 )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewThread message handlers

void NewThread::OnMessage1( WPARAM wParam, LPARAM lParam )
{
    CThreadTestDlg* pDlg = (CThreadTestDlg*)lParam;
    pDlg->DoSomething();
}

void NewThread::OnMessage2( WPARAM wParam, LPARAM lParam )
{
    CThreadTestDlg* pDlg = (CThreadTestDlg*)lParam;
    pDlg->DoSomething();
    if ( g_hEvent != NULL )
    {
        ::SetEvent( g_hEvent );
    }
}

void NewThread::OnMessage3( WPARAM wParam, LPARAM lParam )
{
    CThreadTestDlg* pDlg = (CThreadTestDlg*)lParam;
    pDlg->m_btnB.EnableWindow(FALSE);
    pDlg->DoSomething();
    pDlg->m_btnB.EnableWindow(TRUE);
}