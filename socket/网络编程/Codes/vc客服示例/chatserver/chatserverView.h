// chatserverView.h : interface of the CChatserverView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATSERVERVIEW_H__8A3C08DA_4492_45C2_AFB9_AA914E3F27C6__INCLUDED_)
#define AFX_CHATSERVERVIEW_H__8A3C08DA_4492_45C2_AFB9_AA914E3F27C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////
#include "chatSocket.h"
#include "LisnSocket.h"
#include "chatserverDoc.h"
////////////////////////////////////////////////////////////////////////////////////
class CChatserverDoc;
class CMesg;
class CPort;
class CChatserverView : public CFormView
{
protected: // create from serialization only
	CChatserverView();
	DECLARE_DYNCREATE(CChatserverView)

public:
	//{{AFX_DATA(CChatserverView)
	enum { IDD = IDD_CHATSERVER_FORM };
	CListBox	m_list;
	CButton	m_end;
	CButton	m_start;
	CStatic	m_info;
	//}}AFX_DATA

// Attributes
public:
	CChatserverDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatserverView)
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
	void Accept();
	void Receive(CchatSocket*clientsock);
	void UpdateClient(CMesg *msg,CchatSocket*clientsock);
	void sendmsg(CchatSocket *sock,CMesg *msg);
	void addtolist(CString name);
	void deletefromlist(CString name);
	CPtrList m_clientlist;
	CLisnSocket * m_listensock;
	int initflag;
	virtual ~CChatserverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChatserverView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnd();
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chatserverView.cpp
inline CChatserverDoc* CChatserverView::GetDocument()
   { return (CChatserverDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSERVERVIEW_H__8A3C08DA_4492_45C2_AFB9_AA914E3F27C6__INCLUDED_)
