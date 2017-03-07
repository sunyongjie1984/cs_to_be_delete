// SendFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SendFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFrameWnd

CSendFrameWnd::CSendFrameWnd()
{
}

CSendFrameWnd::~CSendFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CSendFrameWnd, CGuiControlBar)
	//{{AFX_MSG_MAP(CSendFrameWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	XRICHEDIT_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFrameWnd message handlers
XRICHEDIT_MSG_MAP_X(CSendFrameWnd,RecvSendWnd)

BOOL CSendFrameWnd::CreateX(LPCTSTR str, CWnd *pf, UINT unID, DWORD dwstyle)
{
	if (!Create(str,dwstyle, pf, unID))		return 0;
	SetBarStyle(GetBarStyle() |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	return 1;
}

int CSendFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_xrec.CreateX(this,CRect(0,0,0,0),  2))		return -1;
	DrawLnCol(m_xrec.GetLineIndex(),m_xrec.GetCursorCol());
	
	return 0;
}

void CSendFrameWnd::DrawLnCol(int nLine, int nCol)
{
	CString str;
	str.Format("[行 %d，字节 %d (%d)]",nLine+1,nCol/3+1,nCol+1);
	SetWindowText("发报窗    "+str);
	OnNcPaint();
	str.Empty();
}

void CSendFrameWnd::RecvSendWnd(WPARAM wParam, LPARAM lParam)
{
	if(wParam==1)	DrawLnCol(LOWORD(lParam),HIWORD(lParam));
}

void CSendFrameWnd::SaveConfig()
{
	m_xrec.SaveFile(m_xrec.GetFilePath(0));
}
