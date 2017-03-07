/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
          This source may be used freely as long as it is not sold for
					profit and this copyright information is not altered or removed.
					Visit the web-site at www.mjsoft.co.uk
					e-mail comments to info@mjsoft.co.uk
File:     SortListCtrl.h
Purpose:  Provides a sortable list control, it will sort text, numbers
          and dates, ascending or descending, and will even draw the
					arrows just like windows explorer!
----------------------------------------------------------------------*/

#ifndef SORTLISTCTRL_H
#define SORTLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#ifndef SORTHEADERCTRL_H
	#include "SortHeaderCtrl.h"
#endif	// SORTHEADERCTRL_H

#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG
#include "BackgroundUtil.h"
#include <map>
#include "listctrlprint.h"
#ifdef _OTL_SUPPORT
	#define OTL_ODBC // Compile OTL 4/ODBC
	#include "..\Src\Otlv4.h" // include the OTL 4 header file
#endif
#include "afxtempl.h"
#import <msado15.dll> no_namespace rename("EOF","adoEOF")

struct ItemData
{
public:
	ItemData() :  dwData( NULL ) {}
	CStringArray arrpsz;
	DWORD dwData;
	CString csID;
	void *pListCtrl;
public:
	ItemData( const ItemData& );
	void operator = ( const ItemData& );
};

//-------------------------added by muliu--------------
enum SortType {BYTEXT = 0, BYNUMBER, BYSHORTDATE, BYLONGDATE};
	//shortdate   format should be 9999-99-99.
	//longdate    format should be 9999-99-99 99:99:99.

typedef std::map<int, SortType> SortMap;
	//int             排序的列
	//SortType        该列排序类型
//-----------------------------end---------------------

class CSortListCtrl : public CListCtrl ,public CBackgroundUtil
{
// Construction
public:
	DECLARE_DYNCREATE(CSortListCtrl)
	CSortListCtrl();

// Attributes
public:

// Operations
public:

//	int AddItem( int image,LPCTSTR pszText, ... );
//	void LoadColumnInfo();
//	void SaveColumnInfo();
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	void Sort( int iColumn, BOOL bAscending );
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	//------------------added by muliu--------------
	void       EnableColumnSort(BOOL bColSort = TRUE)      { m_bColumnSort = bColSort; }
	void       SortItemsOwnerData();
	static     int  CompareFunOwnerData(const void *elem1, const void *elem2);
	virtual    BOOL OnChildNotify( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult );
	void       PrepCache(int iFrom, int iTo);
	void       SetRefDataSource(_RecordsetPtr Rptr);
	void       SetRefDataSource(_RecordsetPtr Rptr, int iRecCount);
	void       ReinterpretSQL(const CString SQL, CStringArray &csColName);
	_RecordsetPtr m_RPtr;
	int        m_iCurPoint;
	CString    VarToStr(_variant_t var);  
#ifdef _OTL_SUPPORT
	void       SetRefDataSource(otl_stream& o);
#endif
	BOOL       SetSortType(int nCol, SortType Stype);
	SortType   GetSortType(int nCol);
	//-------------------------end------------------
	void SetPrintInfo(
		const CString& csPage = "",		//页码
		const CString&	csPageHead = "",	//页头
		const CString& csPageFooter = ""	//页脚
		);
	void Print();
	BOOL SetItem (const LVITEM* pItem);
	void SubclassHeaderCtrl();
	CString GetItemID(int nItem);
	BOOL SetItemID(int nItem,CString strID);
	DWORD GetItemData_OLD( int nItem ) const;
	BOOL SetItemData_OLD( int nItem, DWORD dwData );
//	void MyTestHeard();
	//重载原有接口函数
	int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,int nFormat = LVCFMT_LEFT, int nWidth = -1 , int nSubItem = -1);
	BOOL DeleteColumn(int nCol);



	int	InsertItem(int nItem, LPCTSTR lpszItem);
	int	InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	int	InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask,int nImage, LPARAM lParam);
	int InsertItem(const LVITEM* pItem);
	BOOL DeleteItem( int iItem );
	BOOL DeleteAllItems();
		
	virtual ~CSortListCtrl();

	// Generated message map functions
protected:
	CDC * m_pDC;
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	void AddData(const int iDataCount,const int iColcount);

	CSortHeaderCtrl m_ctlHeader;

	//////////////////////////////////////////////////////////////////////////
	//print info
	CString			m_csPageHead;
	CString			m_csPageFooter;
	CString			m_csPage;
	//////////////////////////////////////////////////////////////////////////
	
	int m_iNumColumns;
	int m_iSortColumn;
	BOOL m_bSortAscending;

	SortMap m_tSortMap;                         //存储列的排序类型
	CArray<ItemData, ItemData>  m_aRowData;     //存储list的数据
	BOOL    m_bColumnSort;                      //允许列排序否

	//{{AFX_MSG(CSortListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGetDispInfo (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehint (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(	UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTLISTCTRL_H
