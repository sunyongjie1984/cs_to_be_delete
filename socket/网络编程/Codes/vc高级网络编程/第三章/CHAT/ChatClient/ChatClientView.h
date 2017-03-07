// ChatClientView.h : interface of the CChatClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCLIENTVIEW_H__725008EF_E497_4E0A_91C2_2A23DE427754__INCLUDED_)
#define AFX_CHATCLIENTVIEW_H__725008EF_E497_4E0A_91C2_2A23DE427754__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PORT	2310

class CChatClientCntrItem;

class CChatClientView : public CRichEditView
{
protected: // create from serialization only
	CChatClientView();
	DECLARE_DYNCREATE(CChatClientView)

// Attributes
public:
	CChatClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void TextOut(LPCTSTR lpszMessage,COLORREF clr);
	virtual ~CChatClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CHARFORMAT cfm;
// Generated message map functions
protected:
	//{{AFX_MSG(CChatClientView)
	afx_msg void OnDestroy();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	afx_msg void OnColor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDisconnect();
	afx_msg void OnFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ChatClientView.cpp
inline CChatClientDoc* CChatClientView::GetDocument()
   { return (CChatClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTVIEW_H__725008EF_E497_4E0A_91C2_2A23DE427754__INCLUDED_)
