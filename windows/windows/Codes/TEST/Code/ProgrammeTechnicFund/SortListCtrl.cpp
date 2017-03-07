/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
          This source may be used freely as long as it is not sold for
					profit and this copyright information is not altered or removed.
					Visit the web-site at www.mjsoft.co.uk
					e-mail comments to info@mjsoft.co.uk
File:     SortListCtrl.cpp
Purpose:  Provides a sortable list control, it will sort text, numbers
          and dates, ascending or descending, and will even draw the
					arrows just like windows explorer!
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "SortListCtrl.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");
#define MAX_BYTE_STRAM 500
ItemData::ItemData(const ItemData& itemdata)
{
	arrpsz.Copy(itemdata.arrpsz);
	dwData = itemdata.dwData;
	csID = itemdata.csID;
	pListCtrl = itemdata.pListCtrl;
}

void ItemData::operator = (const ItemData& itemdata)
{
	arrpsz.Copy(itemdata.arrpsz);
	dwData = itemdata.dwData;
	csID = itemdata.csID;
	pListCtrl = itemdata.pListCtrl;
}


CSortListCtrl::CSortListCtrl()
	: m_iNumColumns( 0 )
	, m_iSortColumn( -1 )
	, m_bSortAscending( TRUE )
	, m_iCurPoint( 0 )
	, m_bColumnSort( TRUE )
{
}
IMPLEMENT_DYNCREATE(CSortListCtrl, CListCtrl)

CSortListCtrl::~CSortListCtrl()
{
//	for (INT_PTR i = m_aRowData.GetUpperBound(); i >= 0; i--)
//		delete m_aRowData[i];
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSortListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	ON_NOTIFY_REFLECT(LVN_ODCACHEHINT, OnOdcachehint)

	ON_WM_RBUTTONDOWN()
	
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers

void CSortListCtrl::PreSubclassWindow()
{
	// the list control must have the report style.
	CListCtrl::PreSubclassWindow();
	
	if(GetStyle() & LVS_REPORT )
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}





// the heading text is in the format column 1 text,column 1 width;column 2 text,column 3 width;etc.
/*
BOOL CSortListCtrl::SetHeadings( const CString& strHeadings )
{
	int iStart = 0;

	for( ;; )
	{
		const int iComma = strHeadings.Find( _T(','), iStart );

		if( iComma == -1 )
			break;

		const CString strHeading = strHeadings.Mid( iStart, iComma - iStart );

		iStart = iComma + 1;

		int iSemiColon = strHeadings.Find( _T(';'), iStart );

		if( iSemiColon == -1 )
			iSemiColon = strHeadings.GetLength();

		const int iWidth = atoi( strHeadings.Mid( iStart, iSemiColon - iStart ) );
		
		iStart = iSemiColon + 1;

		if( InsertColumn( m_iNumColumns++, strHeading, LVCFMT_LEFT|LVCFMT_IMAGE, iWidth ) == -1 )
			return FALSE;
	}

	return TRUE;
}
*/
/*
int CSortListCtrl::AddItem(int image, LPCTSTR pszText, ... )
{
	const int iIndex = InsertItem( GetItemCount(), pszText,image );

	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
	arrpsz[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	(void)lstrcpy( arrpsz[ 0 ], pszText );

 	va_list list;
	va_start( list, pszText );

	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		ASSERT_VALID_STRING( pszText );
		VERIFY( CListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 ) );

		arrpsz[ iColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		(void)lstrcpy( arrpsz[ iColumn ], pszText );
	}

	va_end( list );

	VERIFY( SetTextArray( iIndex, arrpsz ) );

	return iIndex;
}

*/





bool IsNumber( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if(_istdigit(pszText[i]) || pszText[i] == '.')
			return true;

	return false;
}


int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	ASSERT_VALID_STRING( pszNumber1 );
	ASSERT_VALID_STRING( pszNumber2 );

	const double iNumber1 = atof( pszNumber1 );
	const double iNumber2 = atof( pszNumber2 );

	if( iNumber1 < iNumber2 )
		return -1;
	
	if( iNumber1 > iNumber2 )
		return 1;

	return 0;
}


bool IsDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	// format should be 99/99/9999.

	if( lstrlen( pszText ) != 10 )
		return false;

	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& pszText[ 2 ] == _T('/')
		&& _istdigit( pszText[ 3 ] )
		&& _istdigit( pszText[ 4 ] )
		&& pszText[ 5 ] == _T('/')
		&& _istdigit( pszText[ 6 ] )
		&& _istdigit( pszText[ 7 ] )
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}


int DateCompare( const CString& strDate1, const CString& strDate2 )
{
	const int iYear1 = atoi( strDate1.Mid( 6, 4 ) );
	const int iYear2 = atoi( strDate2.Mid( 6, 4 ) );

	if( iYear1 < iYear2 )
		return -1;

	if( iYear1 > iYear2 )
		return 1;

	const int iMonth1 = atoi( strDate1.Mid( 3, 2 ) );
	const int iMonth2 = atoi( strDate2.Mid( 3, 2 ) );

	if( iMonth1 < iMonth2 )
		return -1;

	if( iMonth1 > iMonth2 )
		return 1;

	const int iDay1 = atoi( strDate1.Mid( 0, 2 ) );
	const int iDay2 = atoi( strDate2.Mid( 0, 2 ) );

	if( iDay1 < iDay2 )
		return -1;

	if( iDay1 > iDay2 )
		return 1;

	return 0;
}
int ShortDateCompare( const CString& strDate1, const CString& strDate2 )
{
	// format should be 9999-99-99.
	int nIndex1 = strDate1.Find('-');
	int nIndex2 = strDate2.Find('-');
	const int iYear1 = atoi(strDate1.Left(nIndex1).GetBuffer(0));
	const int iYear2 = atoi(strDate2.Left(nIndex2).GetBuffer(0));
	CString strRight1 = strDate1.Right(strDate1.GetLength() - nIndex1 - 1);
	CString strRight2 = strDate2.Right(strDate2.GetLength() - nIndex2 - 1);
	
	nIndex1 = strRight1.Find('-');         nIndex2 = strRight2.Find('-');
	const int iMonth1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iMonth2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	strRight1 = strRight1.Right(strRight1.GetLength() - nIndex1 - 1);
	strRight2 = strRight2.Right(strRight2.GetLength() - nIndex2 - 1);
	
	const int iDay1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iDay2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	
	if( iYear1 < iYear2 )
		return -1;
	if( iYear1 > iYear2 )
		return 1;
	
	if( iMonth1 < iMonth2 )
		return -1;
	if( iMonth1 > iMonth2 )
		return 1;
	
	if( iDay1 < iDay2 )
		return -1;
	if( iDay1 > iDay2 )
		return 1;
	
	return 0;
}
bool IsLongDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	// format should be 9999-99-99 99:99:99.
	if( lstrlen( pszText ) != 19 )//|| lstrlen(pszText)!=18)
		return false;

	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& _istdigit( pszText[ 2 ] )
		&& _istdigit( pszText[ 3 ] )
		&& pszText[ 4 ] == _T('-')
		&& _istdigit( pszText[ 5 ] )
		&& _istdigit( pszText[ 6 ] )
		&& pszText[ 7 ] == _T('-')
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] )
		&& pszText[ 10 ] == _T(' ')
		&& _istdigit( pszText[ 11 ] )
		&& _istdigit( pszText[ 12 ] )
		&& pszText[ 13 ] == _T(':')
		&& _istdigit( pszText[ 14 ] )
		&& _istdigit( pszText[ 15 ] )
		&& pszText[ 16 ] == _T(':')
		&& _istdigit( pszText[ 17 ] )
		&& _istdigit( pszText[ 18 ] );
}


int BBDateCompare( const CString& strDate1, const CString& strDate2 )
{
	// format should be 9999/99/99 99:99:99.
	const int iYear1 = atoi( strDate1.Mid( 0, 4 ) );
	const int iYear2 = atoi( strDate2.Mid( 0, 4 ) );

	if( iYear1 < iYear2 )
		return -1;

	if( iYear1 > iYear2 )
		return 1;

	const int iMonth1 = atoi( strDate1.Mid( 5, 2 ) );
	const int iMonth2 = atoi( strDate2.Mid( 5, 2 ) );

	if( iMonth1 < iMonth2 )
		return -1;

	if( iMonth1 > iMonth2 )
		return 1;

	const int iDay1 = atoi( strDate1.Mid( 8, 2 ) );
	const int iDay2 = atoi( strDate2.Mid( 8, 2 ) );

	if( iDay1 < iDay2 )
		return -1;

	if( iDay1 > iDay2 )
		return 1;

	const int iHour1 = atoi( strDate1.Mid( 11, 2 ) );
	const int iHour2 = atoi( strDate2.Mid( 11, 2 ) );
	if( iHour1 < iHour2 )
		return -1;

	if( iHour1 > iHour2 )
		return 1;

	const int iMin1 = atoi( strDate1.Mid( 14, 2 ) );
	const int iMin2 = atoi( strDate2.Mid( 14, 2 ) );
	if( iMin1 < iMin2 )
		return -1;

	if( iMin1 > iMin2 )
		return 1;

	const int iSec1 = atoi( strDate1.Mid( 17, 2 ) );
	const int iSec2 = atoi( strDate2.Mid( 17, 2 ) );
	if( iSec1 < iSec2 )
		return -1;

	if( iSec1 > iSec2 )
		return 1;

	return 0;
}
int LongDateCompare( const CString& strDate1, const CString& strDate2 )
{
	// format should be 9999-99-99 99:99:99.
	int nIndex1 = strDate1.Find('-');
	int nIndex2 = strDate2.Find('-');
	const int iYear1 = atoi(strDate1.Left(nIndex1).GetBuffer(0));
	const int iYear2 = atoi(strDate2.Left(nIndex2).GetBuffer(0));
	CString strRight1 = strDate1.Right(strDate1.GetLength() - nIndex1 - 1);
	CString strRight2 = strDate2.Right(strDate2.GetLength() - nIndex2 - 1);

	nIndex1 = strRight1.Find('-');         nIndex2 = strRight2.Find('-');
	const int iMonth1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iMonth2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	strRight1 = strRight1.Right(strRight1.GetLength() - nIndex1 - 1);
	strRight2 = strRight2.Right(strRight2.GetLength() - nIndex2 - 1);
	
	nIndex1 = strRight1.Find(' ');         nIndex2 = strRight2.Find(' ');
	const int iDay1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iDay2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	strRight1 = strRight1.Right(strRight1.GetLength() - nIndex1 - 1);
	strRight2 = strRight2.Right(strRight2.GetLength() - nIndex2 - 1);

	nIndex1 = strRight1.Find(':');         nIndex2 = strRight2.Find(':');
	const int iHour1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iHour2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	strRight1 = strRight1.Right(strRight1.GetLength() - nIndex1 - 1);
	strRight2 = strRight2.Right(strRight2.GetLength() - nIndex2 - 1);
	
	nIndex1 = strRight1.Find(':');         nIndex2 = strRight2.Find(':');
	const int iMin1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iMin2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );
	strRight1 = strRight1.Right(strRight1.GetLength() - nIndex1 - 1);
	strRight2 = strRight2.Right(strRight2.GetLength() - nIndex2 - 1);
	
	const int iSec1 = atoi( strRight1.Left(nIndex1).GetBuffer(0) );
	const int iSec2 = atoi( strRight2.Left(nIndex2).GetBuffer(0) );

	if( iYear1 < iYear2 )
		return -1;
	if( iYear1 > iYear2 )
		return 1;

	if( iMonth1 < iMonth2 )
		return -1;
	if( iMonth1 > iMonth2 )
		return 1;
	
	if( iDay1 < iDay2 )
		return -1;
	if( iDay1 > iDay2 )
		return 1;
	
	if( iHour1 < iHour2 )
		return -1;
	if( iHour1 > iHour2 )
		return 1;
	
	if( iMin1 < iMin2 )
		return -1;
	if( iMin1 > iMin2 )
		return 1;
	
	if( iSec1 < iSec2 )
		return -1;
	if( iSec1 > iSec2 )
		return 1;
	
	return 0;
}


int CALLBACK CSortListCtrl::CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CSortListCtrl* pListCtrl = reinterpret_cast<CSortListCtrl*>( lParamData );
	ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CListCtrl ) ) );

	ItemData* pid1 = reinterpret_cast<ItemData*>( lParam1 );
	ItemData* pid2 = reinterpret_cast<ItemData*>( lParam2 );
	
	ASSERT( pid1 );
	ASSERT( pid2 );

	LPCTSTR pszText1 = pid1->arrpsz[ pListCtrl->m_iSortColumn ].GetBuffer(0);
	LPCTSTR pszText2 = pid2->arrpsz[ pListCtrl->m_iSortColumn ].GetBuffer(0);

	ASSERT_VALID_STRING( pszText1 );
	ASSERT_VALID_STRING( pszText2 );

//	if( IsNumber( pszText1 ) )
//		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
//	else if( IsDate( pszText1 ) )
//		return pListCtrl->m_bSortAscending ? DateCompare( pszText1, pszText2 ) : DateCompare( pszText2, pszText1 );
//	else if( IsBBDate( pszText1) )
//		return pListCtrl->m_bSortAscending ? BBDateCompare(pszText1,pszText2) :BBDateCompare(pszText2,pszText1);
//	else
//		// text.
//		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
	SortType itype = pListCtrl->GetSortType(pListCtrl->m_iSortColumn);
	if(itype == BYNUMBER && IsNumber(pszText1))               //整数或是小数 
		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
	else if(itype == BYSHORTDATE)                             //9999-99-99
		return pListCtrl->m_bSortAscending ? ShortDateCompare( pszText1, pszText2 ) : ShortDateCompare( pszText2, pszText1 );
	else if(itype == BYLONGDATE)                              //9999-99-99 99:99:99
		return pListCtrl->m_bSortAscending ? LongDateCompare(pszText1,pszText2) :LongDateCompare(pszText2,pszText1);
	else if(itype == BYTEXT)                                  //文本    如果是百分数 请格式化成%3d + "%"的形式
		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
	return 0;
}


void CSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	//
	CString strText;
	DWORD start = GetTickCount();
	//

	if(m_bColumnSort)          
	{
		// if it's a second click on the same column then reverse the sort order,
		// otherwise sort the new column in ascending order.
		Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );

		Invalidate();
	}

	//
//	strText.Format("Time to complete Sort was:\n%li ticks,%d", GetTickCount()-start,GetItemCount());
//	::AfxMessageBox(strText);
	//

	*pResult = 0;
}


void CSortListCtrl::Sort( int iColumn, BOOL bAscending )
{

	m_iSortColumn = iColumn;
	m_bSortAscending = bAscending;

	// show the appropriate arrow in the header control.
	m_ctlHeader.SetSortArrow( m_iSortColumn, m_bSortAscending );
	if(GetStyle() & LVS_OWNERDATA)
	{
		SortItemsOwnerData();
	}
	else
	{
		VERIFY( SortItems( CompareFunction, reinterpret_cast<DWORD>( this ) ) );
	}
}
void CSortListCtrl::SortItemsOwnerData()
{
	::AfxGetApp()->DoWaitCursor(TRUE);
	qsort( static_cast<void*>(&m_aRowData[0]), m_aRowData.GetSize(), sizeof(ItemData), CompareFunOwnerData );
	::AfxGetApp()->DoWaitCursor(FALSE);
}
int CSortListCtrl::CompareFunOwnerData(const void *elem1, const void *elem2)
{
	ASSERT(elem1);
	ASSERT(elem2);
	
	ItemData *itemdata1 = (ItemData*)elem1; 
	ItemData *itemdata2 = (ItemData*)elem2;	
	
	CSortListCtrl* pListCtrl = reinterpret_cast<CSortListCtrl*>( itemdata1->pListCtrl );
	ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CListCtrl ) ) );
	
	LPCTSTR pszText1 = itemdata1->arrpsz[ pListCtrl->m_iSortColumn ].GetBuffer(0);
	LPCTSTR pszText2 = itemdata2->arrpsz[ pListCtrl->m_iSortColumn ].GetBuffer(0);

	SortType itype = pListCtrl->GetSortType(pListCtrl->m_iSortColumn);
	if(itype == BYNUMBER && IsNumber(pszText1))               //整数或是小数 
		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
	else if(itype == BYSHORTDATE)                             //9999-99-99
		return pListCtrl->m_bSortAscending ? ShortDateCompare( pszText1, pszText2 ) : ShortDateCompare( pszText2, pszText1 );
	else if(itype == BYLONGDATE)                              //9999-99-99 99:99:99
		return pListCtrl->m_bSortAscending ? LongDateCompare(pszText1,pszText2) :LongDateCompare(pszText2,pszText1);
	else if(itype == BYTEXT)                                  //文本    如果是百分数 请格式化成%3d + "%"的形式
		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
	return 0;
}
/*
void CSortListCtrl::LoadColumnInfo()
{
	// you must call this after setting the column headings.
	ASSERT( m_iNumColumns > 0 );
	if(!(GetStyle() & LVS_REPORT) )
		return ;

	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );

	UINT nBytes = 0;
	BYTE* buf = NULL;
	if( AfxGetApp()->GetProfileBinary( g_pszSection, strKey, &buf, &nBytes ) )
	{
		if( nBytes > 0 )
		{
			CMemFile memFile( buf, nBytes );
			CArchive ar( &memFile, CArchive::load );
			m_ctlHeader.Serialize( ar );
			ar.Close();

			m_ctlHeader.Invalidate();
		}

		delete[] buf;
	}
}


void CSortListCtrl::SaveColumnInfo()
{
	ASSERT( m_iNumColumns > 0 );
	if(!(GetStyle() & LVS_REPORT) )
		return ;

	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );

	CMemFile memFile;

	CArchive ar( &memFile, CArchive::store );
	m_ctlHeader.Serialize( ar );
	ar.Close();

	DWORD dwLen = memFile.GetLength();
	BYTE* buf = memFile.Detach();	

	VERIFY( AfxGetApp()->WriteProfileBinary( g_pszSection, strKey, buf, dwLen ) );

	free( buf );
}
*/

void CSortListCtrl::OnDestroy() 
{
//	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
//	FreeItemMemory( iItem );
	DeleteAllItems();
	CListCtrl::OnDestroy();
}


BOOL CSortListCtrl::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	if( !CListCtrl::SetItemText( nItem, nSubItem, lpszText ) )
		return FALSE;

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ));
	if(pid != NULL)
	{
		pid->arrpsz[nSubItem] = lpszText;
	}else
	{
		ASSERT(FALSE);
	}
	return TRUE;
}


BOOL CSortListCtrl::SetItemData( int nItem, DWORD dwData )
{
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ));
	if( pid == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	pid->dwData = dwData;
	return TRUE;
}


DWORD CSortListCtrl::GetItemData( int nItem ) const
{
	ASSERT(nItem < GetItemCount());

	DWORD dwData = 0;
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ));
	ASSERT( pid != NULL )	;
	return pid->dwData;
}

int CSortListCtrl::InsertColumn(int nCol, const LVCOLUMN* pColumn)
{
	ASSERT(::IsWindow(m_hWnd));
	m_iNumColumns ++ ;

	int iItemCnt = this->GetItemCount();
	for(int i = 0 ; i < iItemCnt ; i ++)
	{
		ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( i ) );	
		if(pid != NULL)
		{
			pid->arrpsz.InsertAt(nCol,_T(""));
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	return CListCtrl::InsertColumn(nCol,pColumn);
}

int CSortListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
								int nFormat, int nWidth, int nSubItem)
{
	LVCOLUMN column;
	column.mask = LVCF_TEXT|LVCF_FMT;
	column.pszText = (LPTSTR)lpszColumnHeading;
	column.fmt = nFormat;
	if (nWidth != -1)
	{
		column.mask |= LVCF_WIDTH;
		column.cx = nWidth;
	}
	if (nSubItem != -1)
	{
		column.mask |= LVCF_SUBITEM;
		column.iSubItem = nSubItem;
	}
	return CSortListCtrl::InsertColumn(nCol, &column);
}

BOOL CSortListCtrl::DeleteColumn(int nCol)
{
	ASSERT(::IsWindow(m_hWnd));
	int iItemCnt = GetItemCount();
	for(int i = 0 ; i < iItemCnt ; i ++)
	{
		ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( i ) );	
		if(pid)
			pid->arrpsz.RemoveAt(nCol);
	}
	m_iNumColumns --;
	return CListCtrl::DeleteColumn(nCol);
}


int CSortListCtrl::InsertItem(const LVITEM* pItem)
{
	int iRetValue = CListCtrl::InsertItem(pItem);
	if ( iRetValue == -1)
		return -1;

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData(pItem->iItem ) );
	if(pid == NULL)
	{
		pid = new ItemData;
		pid->arrpsz.SetSize(m_iNumColumns);
		pid->arrpsz[0] = pItem->pszText;
	}else
	{
		ASSERT(FALSE);
	}
	CListCtrl::SetItemData(pItem->iItem,(DWORD)pid);

	return iRetValue;
}

int CSortListCtrl::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask,
	int nImage, LPARAM lParam)
{
	ASSERT(::IsWindow(m_hWnd));
	LVITEM item;
	item.mask = nMask;
	item.iItem = nItem;
	item.iSubItem = 0;
	item.pszText = (LPTSTR)lpszItem;
	item.state = nState;
	item.stateMask = nStateMask;
	item.iImage = nImage;
	item.lParam = lParam;
	return CSortListCtrl::InsertItem(&item);
}
int CSortListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{ 
	return CSortListCtrl::InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0);
}
int CSortListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{ 
	return CSortListCtrl::InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0);
}
BOOL CSortListCtrl::DeleteItem( int iItem )
{
	ASSERT( iItem < GetItemCount() );
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData(iItem ));
	if( pid != NULL )
	{
		delete pid;
	}
	return CListCtrl::DeleteItem( iItem );
}


BOOL CSortListCtrl::DeleteAllItems()
{
	ItemData* pid = NULL;
	int iItemCnt = GetItemCount();
	for( int i = 0 ; i <iItemCnt  ; i ++ )
	{
		pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( i ));
		if( pid != NULL )
		{
			delete pid;
			pid = NULL;
		}
	}
	if(m_aRowData.GetSize() > 0)
	{
		m_aRowData.RemoveAll();
	}
	return CListCtrl::DeleteAllItems();
}



BOOL CSortListCtrl::SetItemData_OLD(int nItem, DWORD dwData)
{
	return CListCtrl::SetItemData(nItem,dwData);
}

DWORD CSortListCtrl::GetItemData_OLD(int nItem) const
{
	return CListCtrl::GetItemData(nItem);
}


BOOL CSortListCtrl::SetItemID(int nItem,CString strID)
{
	ItemData *pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ));
	if( pid != NULL)
		pid->csID = strID;
	else
		return FALSE;

	return TRUE;
}

CString CSortListCtrl::GetItemID(int nItem)
{
	ItemData *pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ));
	if( pid != NULL)
		return pid->csID;
	return _T("");
}

void CSortListCtrl::SubclassHeaderCtrl()
{
	if(GetStyle() & LVS_REPORT )
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}

int CSortListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	return 0;
}

BOOL CSortListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;

	GetClientRect(rc);

	m_pDC = pDC;

	if (TileBitmap(pDC, rc) == TRUE)
		return TRUE;

	return CListCtrl::OnEraseBkgnd(pDC);
}

BOOL CSortListCtrl::SetItem(const LVITEM *pItem)
{
	if(pItem == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	if( !CListCtrl::SetItem(pItem))
		return FALSE;

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData(pItem->iItem));
	if(pid != NULL)
	{
		pid->arrpsz[pItem->iSubItem] = pItem->pszText;
	}else
	{
		ASSERT(FALSE);
	}
	return TRUE;
}

BOOL CSortListCtrl::SetSortType(int nCol,SortType Stype)
{
	if(nCol < 0)
		return FALSE;
	m_tSortMap.insert(std::make_pair(nCol,Stype));
	return TRUE;
}

SortType CSortListCtrl::GetSortType(int nCol)
{
	ASSERT(nCol >= 0);
	SortMap::iterator iter;
	iter = m_tSortMap.find(nCol);
	if(iter != m_tSortMap.end())
	{
		return iter->second;
	}
	else
	{
		return BYTEXT;
	}
}

void CSortListCtrl::Print()
{
	CListCtrlPrint	printjob;
	printjob.pList = this;
	printjob.csPage = m_csPage;
	printjob.csPageHead = m_csPageHead;
	printjob.csPageFooter = m_csPageFooter;
	printjob.OnFilePrint();
}

void CSortListCtrl::SetPrintInfo(const CString& csPage,		//页码
								 const CString&	csPageHead,	//页头
								 const CString& csPageFooter	//页脚
								 )
{
	//页头信息
	m_csPageHead = csPageHead;
	//页脚信息
	m_csPageFooter = csPageFooter;
	//页码
	m_csPage = csPage;
}
#ifdef _OTL_SUPPORT
void CSortListCtrl::SetRefDataSource(otl_stream& o)
{
	int iOpen = o.good();
	if(!iOpen)
		return;
	if(o.eof())
	{//you shoule write this MessageBox code
		//		::MessageBox(this->m_hWnd,"没有记录","提示",MB_OK);
		return;
	}
	int iCol = GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < iCol; ++i) 
	{
		DeleteColumn(0);
	}
	if(GetItemCount() > 0)
	{
		DeleteAllItems();
	}
	otl_column_desc* desc;
	int desc_len;
	desc = o.describe_select(desc_len);
	CString csTemp;
	for(i = 0; i < desc_len; i++)
	{
		csTemp = desc[i].name;
		int iWidth = 4*GetStringWidth(csTemp)/2;
		InsertColumn(i, csTemp, LVCFMT_LEFT, iWidth);
	}
	typedef std::vector<std::string> strVector;
	typedef std::vector<strVector>   strContents;
	strVector::iterator     strIter;
	strContents::iterator   saIter;
	strContents saContents;
	char *ch = new char[MAX_BYTE_STRAM];
	ZeroMemory(ch,MAX_BYTE_STRAM);
	while(!o.eof())
	{ 
		strVector strv;
		for(i = 0; i < desc_len; ++i)
		{
			o>>ch;         strv.push_back(ch);    
		}
		saContents.push_back(strv);
	}
	for(saIter = saContents.begin() ,i = 0; saIter != saContents.end(); ++saIter,++i)
	{
		strVector strv = *saIter;
		InsertItem(i,NULL);
		int j = 0;
		for(strIter = strv.begin(); strIter != strv.end(); ++strIter ,++j)
		{
			CString str = strv[j].c_str();
			str.TrimLeft();
			str.TrimRight();
			SetItemText(i,j,str);
		}
	}
	delete [] ch;
}
#endif
void CSortListCtrl::SetRefDataSource(_RecordsetPtr RPtr)
{
	try
	{
		if(RPtr)                      //if the _RecordsetPtr is invalid or is closed,return
		{
			if (RPtr->State == adStateClosed)
				return;
		}
		//保存_RecordsetPtr指针，在虚拟的时候要用它来获取数据
		m_RPtr = RPtr;                    //storage the _RecordsetPtr for Cache use
		m_RPtr->MoveLast();               //得记录的个数  现在这个只是个权宜之计
		int ir = m_RPtr->RecordCount;     //而且要用静态邮标,or keyset   肯定不能用forwardonly
		
		//保证记录集游标在最前边
		if(!m_RPtr->BOF)                  //make sure the cursor is in the first
		{
			m_RPtr->MoveFirst();
		}
		//指示记录集游标位置的变量
		m_iCurPoint = 0;
		
		// 添加列
		int iCol = GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < iCol; ++i) 
		{
			DeleteColumn(0);          //delete columns
		}
		_variant_t Index;
		FieldsPtr fldLoop;
		Index.vt = VT_I2;
		fldLoop = m_RPtr->GetFields();
		int iColCount = (int)fldLoop->GetCount();  
		CString csTemp;
		for(i = 0; i < iColCount; i++)
		{
			Index.iVal=i;
			csTemp = (LPSTR)fldLoop->GetItem(Index)->GetName();
			int iWidth = 4*GetStringWidth(csTemp)/2;
			InsertColumn(i, csTemp, LVCFMT_LEFT, iWidth);
		}
		
		//添加数据
		if(GetItemCount() > 0)
		{
			DeleteAllItems();         //delete data
		}
		if(RPtr->adoEOF)              //if no data, return
		{
			return;
		}
		AddData(ir,iColCount);
		
	}
	catch(_com_error e)
	{
		//::MessageBox(this->m_hWnd,e.Description(),"SetRefDataSource error",MB_OK);
	}
}

//添加数据到界面
void CSortListCtrl::AddData(const int iRowCount,const int iColcount)
{
	if(GetStyle() & LVS_OWNERDATA)
	{
		SetItemCountEx(iRowCount,LVSICF_NOINVALIDATEALL|LVSICF_NOSCROLL);
		Invalidate();
	}
	else
	{
		typedef std::vector<std::string> strVector;
		typedef std::vector<strVector>   strContents;
		strVector::iterator     strIter;
		strContents::iterator   saIter;
		strContents saContents;
		_variant_t vTemp;
		int i = 0;
		while(!m_RPtr->adoEOF)
		{
			strVector strv;
			for(i = 0; i < iColcount; ++i)
			{
				vTemp  = m_RPtr->GetFields()->Item[long(i)]->Value; 
				CString str = VarToStr(vTemp);      str.TrimLeft();         str.TrimRight();
				strv.push_back(str.GetBuffer(0));
			}
			saContents.push_back(strv);
			m_RPtr->MoveNext();
		}
		for(saIter = saContents.begin() , i = 0; saIter != saContents.end(); ++saIter,++i)
		{
			strVector strv = *saIter;
			InsertItem(i,NULL);
			int j = 0;
			for(strIter = strv.begin(); strIter != strv.end(); ++strIter ,++j)
			{
				CString str = strv[j].c_str();
				str.TrimLeft();
				str.TrimRight();
				SetItemText(i,j,str);
			}
		}
	}
}

void CSortListCtrl::SetRefDataSource(_RecordsetPtr RPtr, int iRecCount)
{
	try
	{
		if(RPtr)                      //if the _RecordsetPtr is invalid or is closed,return
		{
			if (RPtr->State == adStateClosed)
				return;
		}
		//保存_RecordsetPtr指针，在虚拟的时候要用它来获取数据
		m_RPtr = RPtr;                    //storage the _RecordsetPtr for Cache use
		
		//保证记录集游标在最前边
		if(!m_RPtr->BOF)                  //make sure the cursor is in the first
		{
			m_RPtr->MoveFirst();
		}
		//指示记录集游标位置的变量
		m_iCurPoint = 0;
		
		// 添加列
		int iCol = GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < iCol; ++i) 
		{
			DeleteColumn(0);          //delete columns
		}
		_variant_t Index;
		FieldsPtr fldLoop;
		Index.vt = VT_I2;
		fldLoop = m_RPtr->GetFields();
		int iColCount = (int)fldLoop->GetCount();  
		CString csTemp;
		for(i = 0; i < iColCount; i++)
		{
			Index.iVal=i;
			csTemp = (LPSTR)fldLoop->GetItem(Index)->GetName();
			int iWidth = 4*GetStringWidth(csTemp)/2;
			InsertColumn(i, csTemp, LVCFMT_LEFT, iWidth);
		}
		
		//添加数据
		if(GetItemCount() > 0)
		{
			DeleteAllItems();         //delete data
		}
		if(m_RPtr->adoEOF)              //if no data, return
		{
			return;
		}
		AddData(iRecCount,iColCount);
	}
	catch(_com_error e)
	{
		::MessageBox(this->m_hWnd,e.Description(),"SetRefDataSource error",MB_OK);
	}
}
//------convert _variant_t to CString -----------------------------------------
CString CSortListCtrl::VarToStr(_variant_t var)           
{
	CString strValue;
	switch(var.vt)
	{
		case VT_EMPTY: strValue = _T("");                     break;
		case VT_UI1:   strValue.Format("%d", var.bVal);       break;  
		case VT_I2:    strValue.Format("%d", var.iVal);       break;  
		case VT_I4:    strValue.Format("%d", var.lVal);       break;  
		case VT_R4:    strValue.Format("%f", var.fltVal);     break;  
		case VT_R8:    strValue.Format("%15.9f", var.dblVal); break;  
		case VT_BSTR:  strValue = var.bstrVal; 	              break;  
		case VT_NULL:  strValue = _T("");                     break;  
		case VT_BOOL:  strValue.Format("%d", var.boolVal);    break;  
		default:       strValue = _T("");                     break;
	}
	return strValue;
}

void CSortListCtrl::OnGetDispInfo (NMHDR* pNMHDR, LRESULT* pResult)
{
	if(!(GetStyle() & LVS_OWNERDATA))
		return;
	NMLVDISPINFO* pDispInfo = (NMLVDISPINFO*)pNMHDR;
	LVITEM* pItem= &(pDispInfo)->item;   //the attributes of a list-view item
	if(pItem->iItem > m_aRowData.GetUpperBound())
	{
/*		int k = m_aRowData.GetUpperBound();
		CString strtemp = _T("");
		strtemp.Format("鼠标点住滚动条往下狂拖时,pItem->iItem = %d\r\nm_aRowData.GetUpperBound() = %d\r\nm_aRowData.GetSize() = %d\r\n\r\n"
			,pItem->iItem
			,m_aRowData.GetUpperBound()
			,m_aRowData.GetSize());
//		CFile file;
//		file.Open("c:\\virtaul.txt",CFile::modeCreate | CFile::modeWrite,NULL);
//		file.Write(strtemp.GetBuffer(0),strtemp.GetLength());
		//当鼠标点住滚动条往下狂拖时，该条件为真。所以准备cache
		//在这种情形下，怎么没有连续的LVN_ODCACHEHINT消息产生去准备cache, 还没有弄明白是怎么回事?
*/		TRACE("-----------bomb--------- m_aRowData.GetSize() = %d\r\n",m_aRowData.GetSize());
		PrepCache(m_aRowData.GetUpperBound(), pItem->iItem);
		TRACE("-----------bomb--------- m_aRowData.GetSize() = %d\r\n",m_aRowData.GetSize());
/*		strtemp.Format("鼠标点住滚动条往下狂拖时,pItem->iItem = %d\r\nm_aRowData.GetUpperBound() = %d\r\nm_aRowData.GetSize() = %d\r\n\r\n"
			,pItem->iItem
			,m_aRowData.GetUpperBound()
			,m_aRowData.GetSize());
//		file.Write(strtemp.GetBuffer(0),strtemp.GetLength());
		if(pItem->iItem > m_aRowData.GetUpperBound())
		{
			if(m_RPtr->adoEOF)
			{
				strtemp = "爆！m_RPtr == adoEOF, 说明是m_RPtr指针的问题";
			}
			strtemp = "爆！m_RPtr != adoEOF, 说明是PrepCache没有循环完";
//			file.Write(strtemp.GetBuffer(0),strtemp.GetLength());
		}
//		file.Close();
*/	}
	ItemData itemdata = m_aRowData.ElementAt(pItem->iItem); //get the item data
	
	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		pItem->pszText = (LPSTR)(LPCSTR)itemdata.arrpsz[pItem->iSubItem];
	}
	if (pItem->mask & LVIF_IMAGE)
	{
	}
	if(pItem->mask & LVIF_STATE)
	{
		int k = 3;
	}
	if(pItem->mask & LVIF_INDENT)
	{
		int j = 4;
	}
	if(pItem->mask & LVIF_PARAM)  
	{
		int l = 5;
	}
	*pResult = 0;
}
void CSortListCtrl::OnOdcachehint(NMHDR* pNMHDR, LRESULT* pResult)
{
/*	NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;
	// TODO: Add your control notification handler code here
	NMHDR* phdr = &pCacheHint->hdr;
	
	switch(phdr->code)
	{
	case LVN_ODCACHEHINT:
		// Load the cache with the recommended range.
		PrepCache(pCacheHint->iFrom, pCacheHint->iTo);
		break;
	default:
		break;
	}*/
	*pResult = 0;
}

void CSortListCtrl::PrepCache(int iFrom, int iTo)
{
	AfxGetApp()->DoWaitCursor(TRUE);
	_variant_t vTemp;
	int iflag = m_iCurPoint;
	try
	{
		while((!m_RPtr->adoEOF) && (m_iCurPoint - iflag < iTo - iFrom + 1 ))    
		{
			ItemData *itemdata = new ItemData;
			if(itemdata == NULL)
			{
				::MessageBox(this->m_hWnd,"out of memory","windows",MB_OK);
				break;
			}
			itemdata->pListCtrl = this;
			for(int i = 0; i < m_iNumColumns; ++i)
			{
				vTemp  = m_RPtr->GetFields()->GetItem(long(i))->GetValue(); 
				CString str = VarToStr(vTemp);      str.TrimLeft();         str.TrimRight();
				itemdata->arrpsz.Add(str);
			}
			m_aRowData.SetAtGrow(m_iCurPoint, *itemdata);
			m_iCurPoint ++;
			m_RPtr->MoveNext();
			delete itemdata;
		}
	}
	catch(_com_error e)
	{
		::MessageBox(this->m_hWnd,e.Description(),"PrepCache error",MB_OK);
	}
	AfxGetApp()->DoWaitCursor(FALSE);
}
BOOL CSortListCtrl::OnChildNotify( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult )
{
	NMLVCACHEHINT* pcachehint=NULL;
	
	if (message == WM_NOTIFY)
    {
        NMHDR* phdr = (NMHDR*)lParam;
		
        switch(phdr->code)
        {
        case LVN_ODCACHEHINT:
            pcachehint= (NMLVCACHEHINT*) phdr;
			// Load the cache with the recommended range.
            PrepCache(pcachehint->iFrom, pcachehint->iTo);
            break;
        default:
            return CListCtrl::OnChildNotify(message, wParam, lParam, pLResult);
        }
        return FALSE;
    }
    else
        return CListCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
void CSortListCtrl::OnVScroll(	UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar );

	if(GetStyle() & LVS_OWNERDATA)
	{
		int imin, imax;
		GetScrollRange(SB_VERT,	&imin,	&imax ) ;
		SetScrollRange(SB_VERT, imin, m_aRowData.GetSize(), TRUE);   // set the range about the scroll

		SCROLLINFO ScrollInfo;
		GetScrollInfo(SB_VERT,&ScrollInfo);  // get information about the scroll
		
		switch(nSBCode)
		{
		case SB_BOTTOM:         //Scrolls to the lower right. 
			break;
			
		case SB_ENDSCROLL:      //Ends scroll. 
			break;
			
		case SB_LINEDOWN:       //Scrolls one line down. 
			SetScrollPos(SB_VERT,GetScrollPos(SB_VERT) + 1);
			break;
			
		case SB_LINEUP:         //Scrolls one line up. 
			SetScrollPos(SB_VERT,GetScrollPos(SB_VERT) - 1);
			break;
			
		case SB_PAGEDOWN:       //Scrolls one page down. 
			SetScrollPos(SB_VERT,GetScrollPos(SB_VERT) + ScrollInfo.nPage);
			break;
			
		case SB_PAGEUP:         //Scrolls one page up. 
			SetScrollPos(SB_VERT,GetScrollPos(SB_VERT) - ScrollInfo.nPage);
			break;
			
		case SB_THUMBPOSITION:  //The user has dragged the scroll box (thumb) and released the mouse button. The nPos parameter indicates the position of the scroll box at the end of the drag operation. 
			break;
			
		case SB_THUMBTRACK:     //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The nPos parameter indicates the position that the scroll box has been dragged to. 
			SetScrollPos(SB_VERT,nPos);
			break;

		case SB_TOP:            //Scrolls to the upper left. 
			break;
			
		default:
			break;
		}
	}
}

/*
 *	函数功能：解释SQL
 *  参数：aSQL      [in]         SQL语句
 *        m_arAlias [out]        要在listctrl中显示的列名 
 *  说明：SQL语句不支持统计函数，可以嵌套查询，可以指定表.字段，可以给字段指定别名。
 */
void CSortListCtrl::ReinterpretSQL(const CString aSQL, CStringArray &m_arAlias)
{
	CString lSQL = aSQL;
	CString alias;
	CString sField;
	CString sRes;
	//
	lSQL.MakeUpper();
	
	//
	CStringArray FunArray;
	FunArray.Add("COUNT(");          FunArray.Add("MAX(");
	FunArray.Add("MIN(");            FunArray.Add("SUM(");
	FunArray.Add("AVG(");            
	
	for(int i = 0; i < FunArray.GetSize(); ++i)
	{
		if(lSQL.Find(FunArray.GetAt(i)) != -1)
		{
			return /*aSQL*/;
		}
	}
	
	// 
	int iPos = lSQL.Find(" FROM ", 0);
	lSQL = lSQL.Left(iPos);
	lSQL = lSQL.Right(lSQL.GetLength()-sizeof(char)*6);
	
	lSQL.TrimRight ();
	lSQL.TrimLeft ();
	
	// 
	int iPosxing = lSQL.Find("*", 0);
	if(iPosxing != -1)
	{
		return /*aSQL*/;
	}
	
	//
	int iPosComma = lSQL.Find(",", 0);
	int iPosAs = -1;
	if ((lSQL.GetLength()>0) && (iPosComma == -1))
		iPosComma = lSQL.GetLength ();
	
	// 
	while ( iPosComma > -1 )
    {
		//
		sField = lSQL.Mid(0,iPosComma);
		
		//
		int iposfullstop = sField.Find(".", 0); 
		if(iposfullstop != -1)
		{
			sField = sField.Right(sField.GetLength() - iposfullstop - 1 );
		}
		
		//
		iPosAs = sField.Find(" AS ", 0);
		//
		if (iPosAs > -1)
		{
			//
			alias = sField.Mid(iPosAs+sizeof(char)*4, sField.GetLength());
			//
			alias.TrimRight(']');
			alias.TrimLeft('[');
			//
			sField.Delete(iPosAs,sField.GetLength()-iPosAs);
		}
		else 
		{
			alias = sField;
		}
		//
		alias.TrimLeft();
		alias.TrimRight();
		//
		m_arAlias.Add (alias); 
		//
		sRes = sRes + sField + ", ";
		//
		lSQL.Delete(0, iPosComma+1);
		lSQL.TrimLeft ();
		iPosComma = lSQL.Find(",", 0);
		//
		if ((lSQL.GetLength()>0) && (iPosComma == -1))
			iPosComma = lSQL.GetLength ();
    }
	
//	sRes.TrimRight(", ");
//	sRes = "SELECT " + sRes;
//	lSQL = aSQL;
//	lSQL.Delete(0, iPos);
//	lSQL = sRes + lSQL;
//	return lSQL;

}

void CSortListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default		
	 
	GetParent()->SendMessage(WM_RBUTTONDOWN,(WPARAM)&nFlags,MAKELPARAM(point.x,point.y));
	
}
