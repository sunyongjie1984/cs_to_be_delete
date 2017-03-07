#if !defined(AFX_LOCALFILEVIEW_H__76C90384_B001_4A72_92CB_38E151B9122A__INCLUDED_)
#define AFX_LOCALFILEVIEW_H__76C90384_B001_4A72_92CB_38E151B9122A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalFileView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalFileView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CLocalFileView : public CFormView
{
protected:
	CLocalFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLocalFileView)

// Form Data
public:
	//{{AFX_DATA(CLocalFileView)
	enum { IDD = IDD_LOCAL_FILELIST };
	CComboBox	m_cbFilePath;
	CListCtrl	m_ctFileLocal;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	int InsertLocDir(CString& str,int iIcon,int iIconSel);
	void GetLocDir();
	void GetLocCurrentDirectory();
	BOOL SendFile(LPVOID pInfo);
	BOOL FindLocalFile();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalFileView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLocalFileView();
	CWinThread* m_pFindLocalFileThread;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLocalFileView)
	afx_msg void OnBeginrdragFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBeginlabeleditFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropdownFilepath();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeFilepath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALFILEVIEW_H__76C90384_B001_4A72_92CB_38E151B9122A__INCLUDED_)
