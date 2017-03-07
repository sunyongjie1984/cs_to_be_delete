// TestAllocView.cpp : implementation of the CTestAllocView class
//

#include "stdafx.h"
#include "TestAlloc.h"

#include "resource.h"
#include "TestAllocView.h"
#include "DefaultAllocator.h"
#include <vector>
#include <list>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int _MEMMAX = 3000;
/////////////////////////////////////////////////////////////////////////////
// CTestAllocView

IMPLEMENT_DYNCREATE(CTestAllocView, CScrollView)

BEGIN_MESSAGE_MAP(CTestAllocView, CScrollView)
//{{AFX_MSG_MAP(CTestAllocView)
ON_COMMAND(POOLMENU, OnPOOLMENU)
ON_COMMAND(MENUMACRO, OnMENUMACRO)
	ON_COMMAND(MENUNORMAL, OnMENUNORMAL)
	ON_COMMAND(MENUPOOLMACRO, OnMENUPOOLMACRO)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
ON_MESSAGE(WM_SETALLOC,OnSetMalloc)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAllocView construction/destruction

CTestAllocView::CTestAllocView()
:m_nMemUsed(0),
m_nPos(0)
{
	// TODO: add construction code here
	
}

CTestAllocView::~CTestAllocView()
{
}

BOOL CTestAllocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestAllocView drawing

void CTestAllocView::OnDraw(CDC* pDC)
{
	CTestAllocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	
	CBrush hrushRect(RGB(255,255,255));
	CBrush hrushRectUsed(RGB(0,255,0));
	CBrush hrushHead(RGB(255,0,0));
	int nMemSize = 0;
	RECT oRect;
	this->GetClientRect(&oRect);
	for(int j = oRect.top; j < oRect.bottom - 20; j += 20)
	{
		for( int i = oRect.left; i < oRect.right - 10; i += 10)
		{
			
			nMemSize++;	
			if ( nMemSize <= m_nMemUsed )
			{
				pDC->SelectObject(hrushRectUsed);
				for ( int k = 0; k< 500; k++)
				{
					if ( nMemSize >= m_naHead[k] + 1 && nMemSize < m_naHead[k] + 5)
					{
						pDC->SelectObject(hrushHead);
					}
				}	
				
			}
			else
			{
				pDC->SelectObject(hrushRect);
			}
			pDC->Rectangle(CRect(i,j,i + 10,j + 20));
			if ( nMemSize >= _MEMMAX )
			{
				break;
			}
		}
		if ( nMemSize >= _MEMMAX )
		{
			break;
		}
	}
}

void CTestAllocView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CTestAllocView printing

BOOL CTestAllocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestAllocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestAllocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestAllocView diagnostics

#ifdef _DEBUG
void CTestAllocView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTestAllocView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTestAllocDoc* CTestAllocView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestAllocDoc)));
	return (CTestAllocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAllocView message handlers
UINT ThreadFunc(LPVOID lpParam); 
void CTestAllocView::OnPOOLMENU() 
{
	for ( int k = 0; k< 500; k++)
	{
		m_naHead[k] = 0;
	}
	m_nPos = 0;
	m_nMemUsed = 0;	
	int* p = new int;
	*p = 3;
	::AfxBeginThread(ThreadFunc,p);
}
void CTestAllocView::OnSetMalloc(WPARAM wParam,LPARAM )
{
	if ( m_nPos == 500 )
	{
		::AfxMessageBox("Out of memory");
		return ;
	}
	m_naHead[m_nPos] = m_nMemUsed;
	m_nPos++;

	m_nMemUsed += static_cast<int>(wParam);
	this->Invalidate(FALSE);
}

void CTestAllocView::OnMENUMACRO() 
{
	for ( int k = 0; k< 500; k++)
	{
		m_naHead[k] = 0;
	}
	m_nPos = 0;
	m_nMemUsed = 0;
	int* p = new int;
	*p = 0;
	::AfxBeginThread(ThreadFunc,p);	
}
UINT ThreadFunc(LPVOID lpParam)
{
	int* n = (int *)lpParam;
	if ( 0 == *n )
	{
		std::vector<int, MyAllocator<int> > vi;
		for( int i = 0; i<50; i++)
		{	
			vi.push_back(i);
		}

	}
	else if ( 1 == *n )
	{
		for( int i = 0; i<50; i++)
		{		
			_DefaultAllocate( i+1,static_cast<int*>(0));
		}
		
	}
	else if ( 2 == *n )
	{
		for ( int i = 0; i < 50; i++ )
		{
			Sleep(200);
			HWND hwnd = (HWND)(((CFrameWnd*)( AfxGetApp()->GetMainWnd()) )->GetActiveView()->GetSafeHwnd());
			PostMessage(hwnd, WM_SETALLOC, static_cast<LPARAM>(8), 0);
		}
		
	}
	else if ( 3 == *n )
	{
		std::vector<int, DefaultAllocator<int> > vi;
		for( int i = 0; i<50; i++)
		{
			vi.push_back(i);
		}
		
	}
	delete lpParam;
	return 0;
}
void CTestAllocView::OnMENUNORMAL() 
{
	for ( int k = 0; k< 500; k++)
	{
		m_naHead[k] = 0;
	}
	m_nPos = 0;
	m_nMemUsed = 0;
	int* p = new int;
	*p = 2;
	::AfxBeginThread(ThreadFunc,p);	
	
}

void CTestAllocView::OnMENUPOOLMACRO() 
{
	for ( int k = 0; k< 500; k++)
	{
		m_naHead[k] = 0;
	}
	m_nPos = 0;
	m_nMemUsed = 0;	
	int* p = new int;
	*p = 1;
	::AfxBeginThread(ThreadFunc,p);
	
}
