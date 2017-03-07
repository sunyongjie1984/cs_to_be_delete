// mainfrm.cpp : implementation of the CMainFrame class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "chatsrvr.h"

#include "mainfrm.h"
#include "srvrdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_RESTORE, OnRestore)
	ON_COMMAND(ID_KICKOUT, OnKickout)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SYSTRAY,OnSysTray)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
	
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_CONNECTIONS,
	ID_MESSAGES,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

#ifdef _WIN32
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
#endif
	
	pnid.cbSize = sizeof(NOTIFYICONDATA);
	pnid.hIcon = LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_MAINFRAME));
	pnid.hWnd = m_hWnd;
	sprintf(pnid.szTip, "聊天服务程序\n");
	pnid.uCallbackMessage = WM_SYSTRAY;
	pnid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	pnid.uID = ID_SYSTRAY;
	Shell_NotifyIcon(NIM_ADD, &pnid);
	ShowWindow(SW_HIDE);	
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSysTray(WPARAM wParam,LPARAM lParam)
{
	CPoint pt;
	CServerApp* app = (CServerApp*)AfxGetApp();
	switch (lParam) {
	case WM_RBUTTONUP:
	{ // Let's track a popup menu
		GetCursorPos(&pt);
		HMENU hmenu = LoadMenu(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDM_CONTEXTMAIN));
		HMENU hpopup = GetSubMenu(hmenu, 0);
		switch (TrackPopupMenu(hpopup,            // Popup menu to track
			TPM_RETURNCMD |    // Return menu code
			TPM_RIGHTBUTTON,   // Track right mouse button?
			pt.x, pt.y,        // screen coordinates
			0,                 // reserved
			m_hWnd,            // owner
			NULL))             // LPRECT user can click in
			// without dismissing menu
		{
		case ID_APP_EXIT: //DestroyWindow(hwnd); break;
			PostQuitMessage(0);
			Shell_NotifyIcon(NIM_DELETE, &pnid);
			break;
		case ID_APP_ABOUT:
			app->OnAppAbout();
			break;
		case ID_RESTORE:
			break;
		case ID_KICKOUT:
			OnKickout();
			break;
		}
	}
	case WM_LBUTTONDBLCLK:
		ShowWindow(SW_SHOWDEFAULT);
	}
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result = CFrameWnd::WindowProc(message, wParam, lParam);
	if(wParam == SC_MINIMIZE){
		ShowWindow(SW_HIDE);
	}
	return result;
}

void CMainFrame::OnClose() 
{
	Shell_NotifyIcon(NIM_DELETE, &pnid);
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnRestore() 
{
	
}

void CMainFrame::OnKickout() 
{
	CServerDoc* pDoc = (CServerDoc*)GetActiveDocument();
	pDoc->Clean();
}
