// SFTPView.h : interface of the CSFTPView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SFTPVIEW_H__C10266AD_50F4_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_SFTPVIEW_H__C10266AD_50F4_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "listitem.h"

#define C_COLUMNS       3
#define COLUMN_FILE     0
#define COLUMN_PATH     1
#define COLUMN_HITS     2
#define COLUMN_LAST     3
#define COLUMN_CMD      4
#define COLUMN_URL      5

class CSFTPView : public CListView
{
protected: // create from serialization only
	CSFTPView();
	DECLARE_DYNCREATE(CSFTPView)

// Attributes
public:
	CSFTPDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFTPView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Sort();
	static int CALLBACK SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lSortParam);
	BOOL AddItem(CListItem* pItem);
	void RemoveAll();
	virtual ~CSFTPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ilLarge, m_ilSmall;

// Generated message map functions
protected:
	//{{AFX_MSG(CSFTPView)
	afx_msg void OnDestroy();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#ifndef _DEBUG  // debug version in SFTPView.cpp
inline CSFTPDoc* CSFTPView::GetDocument()
   { return (CSFTPDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFTPVIEW_H__C10266AD_50F4_11D5_B587_00E04C39B036__INCLUDED_)
