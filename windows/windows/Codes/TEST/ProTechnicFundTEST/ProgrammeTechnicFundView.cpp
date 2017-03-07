// ProgrammeTechnicFundView.cpp : implementation of the CProgrammeTechnicFundView class
//

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"

#include "ProgrammeTechnicFundDoc.h"
#include "ProgrammeTechnicFundView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView

IMPLEMENT_DYNCREATE(CProgrammeTechnicFundView, CView)

BEGIN_MESSAGE_MAP(CProgrammeTechnicFundView, CView)
	//{{AFX_MSG_MAP(CProgrammeTechnicFundView)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView construction/destruction

CProgrammeTechnicFundView::CProgrammeTechnicFundView()
{
	// TODO: add construction code here

}

CProgrammeTechnicFundView::~CProgrammeTechnicFundView()
{
}

BOOL CProgrammeTechnicFundView::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CView::PreCreateWindow(cs))
	{
		return FALSE;
	}
	
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass  = AfxRegisterWndClass(0);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView drawing

void CProgrammeTechnicFundView::OnDraw(CDC* pDC)
{
	CProgrammeTechnicFundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView printing

BOOL CProgrammeTechnicFundView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProgrammeTechnicFundView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProgrammeTechnicFundView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView diagnostics

#ifdef _DEBUG
void CProgrammeTechnicFundView::AssertValid() const
{
	CView::AssertValid();
}

void CProgrammeTechnicFundView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProgrammeTechnicFundDoc* CProgrammeTechnicFundView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgrammeTechnicFundDoc)));
	return (CProgrammeTechnicFundDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicFundView message handlers

/************************************************************************/
/*                                                                      */
/************************************************************************/
static DWORD sg_dwListColumnID[] = 
{
	IDS_COMPUTER_NAME,
	IDS_IP_ADDRESS,
	IDS_OS_VERSION,
	IDS_OLD_PATH,
	IDS_NEW_PATH,
	IDS_OPERATE_TIME,
	IDS_OPERATE_TYPE,
	IDS_VISIT_PROCESS
};

#define  LIST_COLUMN_COUNT   7

VOID CProgrammeTechnicFundView::InsertListColumn( CSortListCtrl * sortListCtrl )
{
	CString       strColumn;
	CStringArray  strColumnArray;

	for ( int m = 0; m < LIST_COLUMN_COUNT; m++ )
	{
		strColumn.LoadString( sg_dwListColumnID[m] );
		
		strColumnArray.Add(strColumn);
	}

	for ( int n = 0; n < LIST_COLUMN_COUNT; n++ )
	{
		sortListCtrl->InsertColumn( n, strColumnArray[n], LVCFMT_LEFT, 100 );
	}
	
}

int CProgrammeTechnicFundView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	BOOL bStatus = m_SortListCtrl.Create( WS_CHILD | WS_VISIBLE | LVS_SHOWSELALWAYS | LVS_OWNERDATA,
										  CRect(0,0,0,0),
										  this,
										  AFX_WS_DEFAULT_VIEW );

	if ( FALSE == bStatus )
	{
		return -1;
	}

	m_SortListCtrl.ModifyStyle( 0, LVS_REPORT );      /*|LVS_SINGLESEL*/
/*
	m_SortListCtrl.ModifyStyleEx( 0,
								  WS_EX_CLIENTEDGE,
								  0 );
*/
	m_SortListCtrl.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	m_SortListCtrl.SubclassHeaderCtrl();

	InsertListColumn( &m_SortListCtrl );

	m_SortListCtrl.EnableColumnSort(FALSE);

	return 0;
}

void CProgrammeTechnicFundView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	
/*	CVisitDatabaseInterface * pVisitDB = CVisitDatabaseInterface::Instance();
	
	if ( NULL == pVisitDB )
	{
		return;
	}
	
	DWORD dwGetRecordCount = 0;

	CFileAuditLogInfo auditRecord;

	int nResultStatus = pVisitDB->ReadRecordFromDatabase( dwGetRecordCount,
														  auditRecord,
														  0 );

	if ( -1 == nResultStatus )
	{
		return;
	}

	m_SortListCtrl.SetRefDataSource( pVisitDB->m_pRecord, dwGetRecordCount );		*/
}

void CProgrammeTechnicFundView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( ::IsWindow(m_SortListCtrl.m_hWnd) )
	{	
		m_SortListCtrl.MoveWindow(0,0,cx,cy);
	}	
}
