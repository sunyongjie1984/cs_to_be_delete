// TTYView.cpp : implementation of the CTTYView class
//

#include "stdafx.h"
#include "TTY.h"
#include "TTYDoc.h"
#include "TTYView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYView

IMPLEMENT_DYNCREATE(CTTYView, CEditView)

BEGIN_MESSAGE_MAP(CTTYView, CEditView)
	//{{AFX_MSG_MAP(CTTYView)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_MESSAGE(WM_COMMNOTIFY, OnCommNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTYView construction/destruction

CTTYView::CTTYView()
{
	// TODO: add construction code here

}

CTTYView::~CTTYView()
{
}

BOOL CTTYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CTTYView drawing

void CTTYView::OnDraw(CDC* pDC)
{
	CTTYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTTYView printing

BOOL CTTYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CTTYView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTTYView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTTYView diagnostics

#ifdef _DEBUG
void CTTYView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTTYView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTTYDoc* CTTYView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTTYDoc)));
	return (CTTYDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTYView message handlers


void CTTYView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CTTYDoc* pDoc=GetDocument();
	
	char c=(char)nChar;

	if(!pDoc->m_bConnected)
		return;

	pDoc->WriteComm(&c, 1);

	if(pDoc->m_bEcho) 
		CEditView::OnChar(nChar, nRepCnt, nFlags); // 本地回显
}


LRESULT CTTYView::OnCommNotify(WPARAM wParam, LPARAM lParam)
{

	char buf[MAXBLOCK/4];
	CString str;
	int nLength, nTextLength;
	CTTYDoc* pDoc=GetDocument();

	CEdit& edit=GetEditCtrl();

	if(!pDoc->m_bConnected || 	(wParam & EV_RXCHAR)!=EV_RXCHAR) // 是否是EV_RXCHAR事件?
	{
		SetEvent(pDoc->m_hPostMsgEvent); // 允许发送下一个WM_COMMNOTIFY消息
		return 0L;
	}

	nLength=pDoc->ReadComm(buf,100);

	if(nLength)
	{
		nTextLength=edit.GetWindowTextLength();
		edit.SetSel(nTextLength,nTextLength); //移动插入光标到正文末尾

		for(int i=0;i<nLength;i++)
		{

			switch(buf[i])
			{

			case '\r': // 回车
				if(!pDoc->m_bNewLine) 
					break;

			case '\n': // 换行
				str+="\r\n";
				break;

			case '\b': // 退格
				edit.SetSel(-1, 0);
				edit.ReplaceSel(str);
				nTextLength=edit.GetWindowTextLength();
				edit.SetSel(nTextLength-1,nTextLength);
				edit.ReplaceSel(""); //回退一个字符
				str="";
				break;

			case '\a': // 振铃 
				MessageBeep((UINT)-1);
				break;

			default : 
				str+=buf[i];
			}
		}
		edit.SetSel(-1, 0);
		edit.ReplaceSel(str); // 向编辑视图中插入收到的字符
	}

	SetEvent(pDoc->m_hPostMsgEvent); // 允许发送下一个WM_COMMNOTIFY消息
	return 0L;
}


