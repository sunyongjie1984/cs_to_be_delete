// ShowBitmapChildWindowFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ProgrammeTechnicAccumulate.h"
#include "ShowBitmapChildWindowFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowFrame

IMPLEMENT_DYNCREATE(CShowBitmapChildWindowFrame, CFrameWnd)

CShowBitmapChildWindowFrame::CShowBitmapChildWindowFrame()
{
	m_pShowBmpView = NULL;
}

CShowBitmapChildWindowFrame::~CShowBitmapChildWindowFrame()
{
}


BEGIN_MESSAGE_MAP(CShowBitmapChildWindowFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CShowBitmapChildWindowFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowFrame message handlers

int CShowBitmapChildWindowFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	// ´´½¨ÊÓÍ¼
	int nStatus = CreateShowBmpView();

	if ( SUCCESS != nStatus )
	{
		return -1;
	}

	return 0;
}


int CShowBitmapChildWindowFrame::CreateShowBmpView()
{
	CRuntimeClass * pView = RUNTIME_CLASS(CShowBitmapChildWindowView);

	m_pShowBmpView = ( CShowBitmapChildWindowView * )( pView->CreateObject() );

	BOOL bStatus;

	bStatus = m_pShowBmpView->Create( NULL,
									  NULL,
									  AFX_WS_DEFAULT_VIEW,
									  CRect( 0, 0, 0, 0 ),
									  this,
									  AFX_IDW_PANE_FIRST,
									  NULL );

	if ( NULL == bStatus )
	{
		//LOGERROR
		return FAIL;
	}

	m_pShowBmpView->ShowWindow( SW_SHOW );

	return SUCCESS;
}