// SFTPView.cpp : implementation of the CSFTPView class
//

#include "stdafx.h"
#include "SFTP.h"

#include "SFTPDoc.h"
#include "SFTPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFTPView

IMPLEMENT_DYNCREATE(CSFTPView, CListView)

BEGIN_MESSAGE_MAP(CSFTPView, CListView)
	//{{AFX_MSG_MAP(CSFTPView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFTPView construction/destruction

CSFTPView::CSFTPView()
{
}

CSFTPView::~CSFTPView()
{

}

BOOL CSFTPView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = (cs.style & ~LVS_TYPEMASK) | LVS_REPORT;
	cs.style |= LVS_AUTOARRANGE;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSFTPView drawing

void CSFTPView::OnDraw(CDC* pDC)
{
	CSFTPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CSFTPView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CSFTPView printing

BOOL CSFTPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSFTPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSFTPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSFTPView diagnostics

#ifdef _DEBUG
void CSFTPView::AssertValid() const
{
	CListView::AssertValid();
}

void CSFTPView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSFTPDoc* CSFTPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSFTPDoc)));
	return (CSFTPDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSFTPView message handlers

BOOL CSFTPView::AddItem(CListItem *pItem)
{
	CListCtrl& list = GetListCtrl();
	// look for a match on the file name....
	LV_FINDINFO lvfi;
	lvfi.flags = LVFI_STRING;
	lvfi.psz = pItem->m_strName;
	
	// didn't find a match; add it to the list....
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM)pItem;
	lvi.iImage = pItem->GetImage();

	int ndx = 0;
	if ((ndx = list.InsertItem( &lvi )) != -1 )
	{
		// add all the callback sub items....
		lvi.mask = LVIF_TEXT;
		lvi.pszText = pItem->m_strName.GetBuffer(0);
		pItem->m_strName.ReleaseBuffer();
		lvi.iItem = ndx;
		lvi.iSubItem = 0;
		list.SetItem( &lvi );
		lvi.pszText = pItem->m_strDate.GetBuffer(0);
		pItem->m_strDate.ReleaseBuffer();
		lvi.iItem = ndx;
		lvi.iSubItem = 1;
		list.SetItem( &lvi );
		lvi.pszText = pItem->m_strSec.GetBuffer(0);
		pItem->m_strSec.ReleaseBuffer();
		lvi.iItem = ndx;
		lvi.iSubItem = 2;
		list.SetItem( &lvi );
	}
	else
	{
		// insert failed; kill it....
		delete pItem;
		pItem = NULL;
	}

	return (pItem != NULL);
}

BOOL CSFTPView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL bCreated = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	if ( bCreated )
	{
		CListCtrl& listView = GetListCtrl();
		int aWidths[] = { 280, 200, 100};
		CString strHeading;

		for ( int iCol = 0; iCol < C_COLUMNS; iCol++) {
			strHeading.LoadString( IDS_COLUMN1 + iCol );
			listView.InsertColumn( iCol, strHeading, LVCFMT_LEFT,
				aWidths[iCol], iCol );
		}

		// Create the full-sized and small icon image lists.
		if ( m_ilLarge.Create( IDB_IMAGES, 32, 1, RGB(0,255,0) ) )
		{
			listView.SetImageList( &m_ilLarge, LVSIL_NORMAL );
		}
		if ( m_ilSmall.Create( IDB_SMALLIMAGES, 16, 1, RGB(0,255,0) ) )
		{
			listView.SetImageList( &m_ilSmall, LVSIL_SMALL);
		}
	}
	return bCreated;
}

void CSFTPView::OnDestroy() 
{
	RemoveAll();
	CListView::OnDestroy();
}

void CSFTPView::RemoveAll()
{
	CListCtrl& list = GetListCtrl();
	int n = list.GetItemCount();
	if(n == 0)
		return;

	LVITEM lvi;
	lvi.mask = LVIF_PARAM;

	for(int i=0;i<n;i++)
	{
		lvi.iItem = i;
		list.GetItem(&lvi);

		CListItem* pfi = (CListItem*)lvi.lParam;
		delete pfi;
	}
	list.DeleteAllItems();
}

void CSFTPView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& list = GetListCtrl();
	int nSelected = list.GetSelectedCount();
	// only proceed if one item selected....
	if ( nSelected == 1 )
	{
		// find the selected item....
		int ndx = 0;
		int nItems = list.GetItemCount();
		while ( ndx < nItems )
		{
			if ( list.GetItemState( ndx, LVIS_SELECTED ) == LVIS_SELECTED )
			{
				LV_ITEM lvi;
				lvi.mask = LVIF_PARAM;
				lvi.iItem = ndx;
				lvi.iSubItem = 0;
				if (list.GetItem( &lvi ) )
				{
					// only do something for OK and non-executable hits...
					CListItem* pItem = (CListItem*)(lvi.lParam);
					if (!pItem->m_bDirectory)
					{
						GetDocument()->RetreiveFile(pItem->m_strName);
					}
					else{
						pItem->m_strName.TrimLeft();
						pItem->m_strName.TrimRight();
						if(!pItem->m_strName.CompareNoCase(".."))
							GetDocument()->Back();
						else
							GetDocument()->CD(pItem->m_strName);
					}
				}
				break;
			}
			++ndx;
		}
	}
	*pResult = 0;
}

void CSFTPView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	::SendMessage(m_hWnd,LVM_SORTITEMS,pNMListView->iSubItem,(LPARAM)SortProc);
	
	*pResult = 0;
}

int CALLBACK CSFTPView::SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lSortParam)
{
	CListItem* pfi1 = (CListItem*)lParam1;
	CListItem* pfi2 = (CListItem*)lParam2;

	if((pfi1->m_bDirectory ) && !(pfi2->m_bDirectory))
		return -1;
	if((pfi2->m_bDirectory ) && !(pfi1->m_bDirectory))
		return 1;

	int nRet;

	nRet = lstrcmpi(pfi1->m_strName, pfi2->m_strName);

	return nRet;
}

void CSFTPView::Sort()
{
	::SendMessage(m_hWnd, LVM_SORTITEMS, 0, (LPARAM)SortProc);
}
