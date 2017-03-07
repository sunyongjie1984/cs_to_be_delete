// WebDrawView.cpp : implementation of the CWebDrawView class
//

#include "stdafx.h"
#include "WebDraw.h"

#include "WebDrawDoc.h"
#include "CntrItem.h"
#include "WebDrawView.h"
#include "atlbase.h"
#include "connectdlg.h"

#define IID_DEFINED
#include "..\DrawServ\DrawServ_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView

IMPLEMENT_DYNCREATE(CWebDrawView, CView)

BEGIN_MESSAGE_MAP(CWebDrawView, CView)
	//{{AFX_MSG_MAP(CWebDrawView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(IDC_CONNECT, OnConnect)
	ON_COMMAND(IDC_DISCONNECT, OnDisconnect)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CWebDrawView, CCmdTarget)
	INTERFACE_PART(CWebDrawView, IID_IDrawServ, DrawServ)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView construction/destruction

CWebDrawView::CWebDrawView()
{
	m_pSelection = NULL;

/*	HRESULT hr;

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
	ASSERT(SUCCEEDED(hr));
*/
	m_bDragging = FALSE;
	m_pDrawServ = NULL;
	m_col = RGB(255, 0, 0);
}

CWebDrawView::~CWebDrawView()
{
	if (m_pDrawServ != NULL)
	{
		DisconnectSink(IID_IDrawServ,m_dwDrawServ);
		m_pDrawServ->Release();
	}
}

BOOL CWebDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView drawing

void CWebDrawView::OnDraw(CDC* pDC)
{
	CWebDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CWebDrawView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	//Active documents should always be activated
	COleDocument* pDoc = (COleDocument*) GetDocument();
	if (pDoc != NULL)
	{
		// activate the first one
		POSITION posItem = pDoc->GetStartPosition();
		if (posItem != NULL)
		{
			CDocItem* pItem = pDoc->GetNextItem(posItem);

			// only if it's an Active document
			COleDocObjectItem *pDocObjectItem =
				DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);

			if (pDocObjectItem != NULL)
			{
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, this);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView printing

BOOL CWebDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;

	return TRUE;
}

void CWebDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWebDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWebDrawView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CWebDrawView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CWebDrawView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CWebDrawCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CWebDrawView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CWebDrawCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;

	BeginWaitCursor();

	CWebDrawCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CWebDrawDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CWebDrawCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CWebDrawView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CWebDrawView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CWebDrawView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CWebDrawView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView diagnostics

#ifdef _DEBUG
void CWebDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CWebDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWebDrawDoc* CWebDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebDrawDoc)));
	return (CWebDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWebDrawView message handlers

STDMETHODIMP_(ULONG) CWebDrawView::XDrawServ::AddRef()
{
	METHOD_PROLOGUE_EX(CWebDrawView, DrawServ)
	TRACE("AddRef\n");
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CWebDrawView::XDrawServ::Release()
{
	METHOD_PROLOGUE_EX(CWebDrawView, DrawServ)
	TRACE("Release\n");
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CWebDrawView::XDrawServ::QueryInterface(
	REFIID iid, LPVOID far * ppvObj)
{
	METHOD_PROLOGUE_EX(CWebDrawView, DrawServ)
	TRACE("QueryInterface\n");
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CWebDrawView::XDrawServ::Draw(
	long x1, long y1, long x2, long y2, unsigned long col)
{
	METHOD_PROLOGUE_EX(CWebDrawView, DrawServ)

	pThis->Draw(x1, y1, x2, y2, col);

	return S_OK;
}

void CWebDrawView::OnConnect() 
{
	HRESULT hr;
	hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
	
	COSERVERINFO si;
	MULTI_QI     qi;

	CConnectDlg dlg;
	if(dlg.DoModal() != IDOK){
		return;
	}
	LPWSTR name;// = L"10.12.11.74";
	CComBSTR str(dlg.m_strName);
	name = str.m_str;
	si.dwReserved1 = 0;
	si.pwszName = name;
	si.pAuthInfo = NULL;
	si.dwReserved2 = 0;
	
	qi.pIID = &IID_IDrawServ;
	qi.pItf = NULL;
	//qi.hr = 0;
	
	hr = CoCreateInstanceEx(CLSID_CDrawServ, NULL, CLSCTX_SERVER, &si, 1, &qi);
	if (FAILED(hr))
	{
		TRACE(_T("CoCreateInstanceEx failed"));
		return;
	}
	if (FAILED(qi.hr))
	{
		TRACE(_T("Failed to connect to server"));
		return;
	}
	m_pDrawServ = (IDrawServ*)qi.pItf;
	IUnknown* pUnk;
	m_xDrawServ.QueryInterface(IID_IUnknown, (void**) &pUnk);
	if (ConnectSink(IID_IDrawServ, pUnk) == FALSE)
	{
		m_pDrawServ->Release();
		m_pDrawServ = NULL;
	}
	pUnk->Release();	
}

void CWebDrawView::OnDisconnect() 
{
	if (m_pDrawServ != NULL)
	{
		DisconnectSink(IID_IDrawServ,m_dwDrawServ);
		m_pDrawServ->Release();
		m_pDrawServ = NULL;
		AfxMessageBox("Disconnected");
	}
}

BOOL CWebDrawView::ConnectSink(REFIID iid, LPUNKNOWN punkSink)
{
	BOOL    bRC = FALSE;
	ASSERT(m_pDrawServ != NULL);

	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((m_pDrawServ != NULL) &&
		SUCCEEDED(m_pDrawServ->QueryInterface(IID_IConnectionPointContainer,
			(LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;

		HRESULT hRes = pConnPtCont->FindConnectionPoint(iid, &pConnPt);
		ASSERT(hRes == S_OK);
		if (SUCCEEDED(hRes))
		{
			ASSERT(pConnPt != NULL);
			hRes = pConnPt->Advise(punkSink, &m_dwDrawServ);
			if (FAILED(hRes))
			{
				TCHAR buf[32];
				wsprintf(buf, _T("%x"), hRes);
				AfxMessageBox(buf);
				return FALSE;
			}
			AfxMessageBox(_T("Connected"));
			bRC = TRUE;
			pConnPt->Release();
		}
		pConnPtCont->Release();
	}
	return bRC;
}

void CWebDrawView::DisconnectSink(REFIID iid, DWORD dwCookie)
{
	if (dwCookie == 0)
		return;

	ASSERT(m_pDrawServ != NULL);

	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((m_pDrawServ != NULL) &&
		SUCCEEDED(m_pDrawServ->QueryInterface(IID_IConnectionPointContainer,
			(LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(iid, &pConnPt)))
		{
			ASSERT(pConnPt != NULL);
			pConnPt->Unadvise(dwCookie);
			pConnPt->Release();
		}

		pConnPtCont->Release();
	}
}

CWebDrawView::Draw(long x1, long y1, long x2, long y2, unsigned long col)
{
	CClientDC dc(this);

	CPen pen(PS_SOLID, 2, (COLORREF) col);
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y2);
	dc.SelectObject(oldPen);
}

void CWebDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDragging = TRUE;
	m_pos = point;
	
	CView::OnLButtonDown(nFlags, point);
}

void CWebDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{
		if (m_pDrawServ != NULL)
		{
			HRESULT hr;
			hr = m_pDrawServ->Draw(
				m_pos.x, m_pos.y,
				point.x, point.y,
				m_col);
			if (FAILED(hr))
			{
				TCHAR buf[32];
				wsprintf(buf, _T("%xd"), hr);
				AfxMessageBox(buf);
			}
		}
		m_pos = point;
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CWebDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bDragging = FALSE;
	
	CView::OnLButtonUp(nFlags, point);
}
