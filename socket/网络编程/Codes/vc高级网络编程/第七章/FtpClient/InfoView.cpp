// InfoView.cpp : implementation file
//

#include "stdafx.h"
#include "FtpClient.h"
#include "InfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoView

IMPLEMENT_DYNCREATE(CInfoView, CEditView)

CInfoView::CInfoView()
{
}

CInfoView::~CInfoView()
{
}


BEGIN_MESSAGE_MAP(CInfoView, CEditView)
	//{{AFX_MSG_MAP(CInfoView)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoView drawing

void CInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CInfoView diagnostics

#ifdef _DEBUG
void CInfoView::AssertValid() const
{
	CEditView::AssertValid();
}

void CInfoView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoView message handlers

int CInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_NewFont.CreatePointFont(70,"Arial",NULL);
	GetEditCtrl().SetFont(&m_NewFont);
    	
	return 0;
}

void CInfoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	//CEditView::OnChar(nChar, nRepCnt, nFlags);
}

void CInfoView::OnChange() 
{
	return;
}
