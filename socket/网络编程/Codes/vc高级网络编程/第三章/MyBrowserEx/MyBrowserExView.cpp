// MyBrowserExView.cpp : implementation of the CMyBrowserExView class
//

#include "stdafx.h"
#include "MyBrowserEx.h"

#include "MyBrowserExDoc.h"
#include "MyBrowserExView.h"
#include "MainFrm.h"
#include "ProxyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView

IMPLEMENT_DYNCREATE(CMyBrowserExView, CEditView)

BEGIN_MESSAGE_MAP(CMyBrowserExView, CEditView)
	//{{AFX_MSG_MAP(CMyBrowserExView)
	ON_COMMAND(ID_DEFAULT, OnDefault)
	ON_UPDATE_COMMAND_UI(ID_DEFAULT, OnUpdateDefault)
	ON_COMMAND(ID_PROXY, OnProxy)
	ON_UPDATE_COMMAND_UI(ID_PROXY, OnUpdateProxy)
	ON_COMMAND(ID_HOST, OnHost)
	ON_UPDATE_COMMAND_UI(ID_HOST, OnUpdateHost)
	ON_MESSAGE(WM_READFILECOMPLETED,OnReadFileCompleted)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_CBN_SELENDOK(ID_COMBO,OnNewAddress)
	ON_COMMAND(IDOK,OnNewAddressEnter)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView construction/destruction

CMyBrowserExView::CMyBrowserExView()
{
	// TODO: add construction code here
	m_dwAccessType    = 0;   
}

CMyBrowserExView::~CMyBrowserExView()
{
}

BOOL CMyBrowserExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView drawing

void CMyBrowserExView::OnDraw(CDC* pDC)
{
	CMyBrowserExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView printing

BOOL CMyBrowserExView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMyBrowserExView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMyBrowserExView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView diagnostics

#ifdef _DEBUG
void CMyBrowserExView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyBrowserExView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyBrowserExDoc* CMyBrowserExView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyBrowserExDoc)));
	return (CMyBrowserExDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExView message handlers
void CMyBrowserExView::OnNewAddress()
{ 
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndAddress.GetLBText(pFrame->m_wndAddress.GetCurSel(), m_strAddress);
	Connect();
}

void CMyBrowserExView::OnNewAddressEnter()
{ 
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    pFrame->m_wndAddress.GetEditCtrl()->GetWindowText(m_strAddress);
	
	COMBOBOXEXITEM item;
	item.mask = CBEIF_TEXT;
	item.iItem = -1;
	item.pszText = (LPTSTR)(LPCTSTR)m_strAddress;
	pFrame->m_wndAddress.InsertItem(&item);
	Connect();
}

BOOL CMyBrowserExView::Connect()
{
  if ( m_strAddress.IsEmpty() || "http://"!=m_strAddress.Left(7))
  {
	  AfxMessageBox("ÇëÊäÈëÍøÒ³µØÖ·£¡",MB_OK | MB_ICONINFORMATION);
	  return FALSE;
  }
  m_InternetThread.Init(GetSafeHwnd());
  m_InternetThread.GetPage(m_strAddress);
  
  return TRUE;
}

void CMyBrowserExView::OnDefault() 
{
	// TODO: Add your command handler code here
	if (m_dwAccessType != 0)
		m_dwAccessType = 0;
	m_InternetThread.SetAccessTypeIndex(0);
}

void CMyBrowserExView::OnUpdateDefault(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dwAccessType == 0 );
}

void CMyBrowserExView::OnProxy() 
{
	// TODO: Add your command handler code here
	if (m_dwAccessType !=  1)
		m_dwAccessType = 1;
	m_InternetThread.SetAccessTypeIndex(1);
	CProxyDlg dlg;
	dlg.m_strProxy = m_InternetThread.GetProxyServer();
	if(dlg.DoModal() == IDOK)
	{
		m_InternetThread.SetProxyServer(dlg.m_strProxy);
	}

}

void CMyBrowserExView::OnUpdateProxy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dwAccessType ==  1);
}

void CMyBrowserExView::OnHost() 
{
	// TODO: Add your command handler code here
	if (m_dwAccessType != 2)
		m_dwAccessType = 2;
	m_InternetThread.SetAccessTypeIndex(2);
}

void CMyBrowserExView::OnUpdateHost(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dwAccessType == 2);
}

//DEL void CMyBrowserExView::EnableUI(BOOL bEnable)
//DEL {
//DEL 	CMenu* pMenu = GetMenu()->GetSubMenu(3);
//DEL 	pMenu->EnableMenuItem(IDR_MAINFRAME,bEnable);
//DEL }

afx_msg LRESULT CMyBrowserExView::OnReadFileCompleted(WPARAM wParm,LPARAM lParam)
{
	TRACE0("CMyBrowserExView::OnReadFileCompleted\r/n");
	UINT uiResult = (UINT)lParam;
	if (uiResult == THREAD_GOOD)
	{    
		 SetWindowText("");
		 SetWindowText(m_InternetThread.GetBuffer());
	}

	//EnableUI (TRUE);
		return TRUE;
}
