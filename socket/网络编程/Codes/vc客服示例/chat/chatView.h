// chatView.h : interface of the CChatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATVIEW_H__92B5ED6C_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
#define AFX_CHATVIEW_H__92B5ED6C_F22F_11D7_8D52_0030F149A9D4__INCLUDED_

#include "Mesg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////
class CMesg;
class CCLientSocket;
#define N  15
//////////////////////////////////////////////////
class CChatView : public CFormView
{
protected: // create from serialization only
	CChatView();
	DECLARE_DYNCREATE(CChatView)

public:
	bool turn;
	int first;
	int start;
	int py;
	int px;
	CPoint pt;
	int state[N][N];
	CBitmap bmp[3];
	//{{AFX_DATA(CChatView)
	enum { IDD = IDD_CHAT_FORM };
	CStatic	m_info;
	CStatic	m_object;
	CListCtrl	m_namelist;
//	CButton	m_logout;
////	CButton	m_login;
//	CButton	m_send;
	CComboBox	m_combo;
	CEdit	m_msg;
	CListBox	m_msglist;
	//}}AFX_DATA

// Attributes
public:
	CChatDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int zz;
	int jj;
	int ii;
	int getformat(CString buf, int *x, int *y);
	CString formatsend(int x, int y);
	afx_msg void OnDraw(CDC *pDC);
	bool check(int x, int y, int me);
	void putchess(int px, int py);
	bool canvertpos(CPoint ps);
	void process_msg();

	void RecvMsg();
	void sendmsg();
	bool connectserver(CString name,CString servname,int servport);
//////////////////////////////////////////////////////////////////////////////
	CString name;
	CMesg msg;
	CImageList * m_pImageList;
	int initflag;
	virtual ~CChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CArchive *m_out;
	CArchive *m_in;
	CSocketFile *m_sockfile;
	CCLientSocket *m_socket;
	//{{AFX_MSG(CChatView)
	afx_msg void OnSend();
	afx_msg void OnLogin();
	afx_msg void OnLogout();
	afx_msg void OnClickNamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBlackstart();
	afx_msg void OnUpdateBlackstart(CCmdUI* pCmdUI);
	afx_msg void OnUpdatesend(CCmdUI* pCmdUI);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chatView.cpp
inline CChatDoc* CChatView::GetDocument()
   { return (CChatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATVIEW_H__92B5ED6C_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
