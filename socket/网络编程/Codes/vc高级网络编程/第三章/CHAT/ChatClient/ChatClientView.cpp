// ChatClientView.cpp : implementation of the CChatClientView class
//

#include "stdafx.h"
#include "ChatClient.h"

#include "ChatClientDoc.h"
#include "CntrItem.h"
#include "ChatClientView.h"
#include "login.h"
#include "mainfrm.h"
#include "message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatClientView

IMPLEMENT_DYNCREATE(CChatClientView, CRichEditView)

BEGIN_MESSAGE_MAP(CChatClientView, CRichEditView)
	//{{AFX_MSG_MAP(CChatClientView)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_WM_CREATE()
	ON_COMMAND(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_FILTER, OnFilter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientView construction/destruction

CChatClientView::CChatClientView()
{
	// TODO: add construction code here

}

CChatClientView::~CChatClientView()
{
}

BOOL CChatClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CChatClientView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	cfm.cbSize=sizeof(cfm);
	cfm.bCharSet=GB2312_CHARSET;
	cfm.crTextColor=RGB(0,0,0);
	cfm.dwMask=CFM_CHARSET | CFM_COLOR ;
	GetRichEditCtrl().SetDefaultCharFormat(cfm);

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientView printing

BOOL CChatClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CChatClientView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CChatClientView diagnostics

#ifdef _DEBUG
void CChatClientView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CChatClientView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CChatClientDoc* CChatClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChatClientDoc)));
	return (CChatClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatClientView message handlers

void CChatClientView::TextOut(LPCTSTR lpszMessage, COLORREF clr)
{
	cfm.cbSize=sizeof(cfm);
	cfm.crTextColor=clr;
	cfm.dwMask=CFM_COLOR;
	CString strTemp = lpszMessage;
	
	int len = GetWindowTextLength();
	GetRichEditCtrl().SetSel(len,len);
	
	GetRichEditCtrl().SetSelectionCharFormat(cfm);
	GetRichEditCtrl().ReplaceSel(strTemp);
}

void CChatClientView::OnConnect() 
{
	CLogin dlg;
	
	if(dlg.DoModal() != IDOK){
		return;
	}
	
	GetDocument()->ConnectSocket(dlg.m_strName, dlg.m_strServerIP, dlg.m_strImage, PORT);
}

void CChatClientView::OnSend() 
{
	CMainFrame* pFrame = (CMainFrame*)GetParent();
	CComboBox* pTo = (CComboBox*)pFrame->m_wndSend.GetDlgItem(IDC_TO);
	CComboBox* pType = (CComboBox*)pFrame->m_wndSend.GetDlgItem(IDC_TYPE);
	CWnd* pText = pFrame->m_wndSend.GetDlgItem(IDC_TEXT);
	CButton* pSecret = (CButton*)pFrame->m_wndSend.GetDlgItem(IDC_SECRET);
	
	CMessage* msg = &(GetDocument()->msg);

	CString tmp;
	pTo->GetWindowText(tmp);
	msg->to = tmp;
	CString str;
	pType->GetWindowText(str);
	msg->type = pType->FindString(0, str);
	tmp.Empty();
	pText->GetWindowText(tmp);
	msg->m_strText = tmp;
	if(!tmp.Compare(""))
		return;
	msg->secret = pSecret->GetCheck();

	pText->SetWindowText(_TEXT(""));
	GetDocument()->SendMsg();
}

void CChatClientView::OnColor() 
{
	CColorDialog clr(GetDocument()->msg.color, 0, NULL);
	if(clr.DoModal()==IDOK)
	{
		if(clr.GetColor() == RGB(255,255,255))
			AfxMessageBox("把字体设为白色就看不见了啊!");
		else
			GetDocument()->msg.color = clr.GetColor();
	}	
}

int CChatClientView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CChatClientView::OnDisconnect() 
{
	GetDocument()->Disconnect();
}

void CChatClientView::OnFilter() 
{
	CMainFrame* pFrame = (CMainFrame*)GetParent();
	CButton* pFilter = (CButton*)pFrame->m_wndSend.GetDlgItem(IDC_FILTER);

	GetDocument()->m_bFilter = 	pFilter->GetCheck();
}
