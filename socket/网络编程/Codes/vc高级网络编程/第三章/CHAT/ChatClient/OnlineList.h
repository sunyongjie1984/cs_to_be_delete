#if !defined(AFX_ONLINELIST_H__983FC24F_FC40_4FB9_A4EA_4CA2CAA403B4__INCLUDED_)
#define AFX_ONLINELIST_H__983FC24F_FC40_4FB9_A4EA_4CA2CAA403B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnlineList.h : header file
//
#define WM_DBCLICKITEM    WM_USER + 1003
/////////////////////////////////////////////////////////////////////////////
// COnlineList window

 class COnlineList : public CListCtrl
{
// Construction
public:
	COnlineList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnlineList)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Remove(char* name);
	void AddItem(short i, char* name, char* text);
	virtual ~COnlineList();

	// Generated message map functions
protected:
	CImageList m_imgList;
	//{{AFX_MSG(COnlineList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONLINELIST_H__983FC24F_FC40_4FB9_A4EA_4CA2CAA403B4__INCLUDED_)
