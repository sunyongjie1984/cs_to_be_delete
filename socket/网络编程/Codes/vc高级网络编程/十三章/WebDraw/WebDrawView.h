// WebDrawView.h : interface of the CWebDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBDRAWVIEW_H__848397AD_50EF_4585_A446_54F1CAD81C26__INCLUDED_)
#define AFX_WEBDRAWVIEW_H__848397AD_50EF_4585_A446_54F1CAD81C26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\DrawServ\DrawServ.h"

class CWebDrawCntrItem;

class CWebDrawView : public CView
{
protected: // create from serialization only
	CWebDrawView();
	DECLARE_DYNCREATE(CWebDrawView)

// Attributes
public:
	CWebDrawDoc* GetDocument();
	// m_pSelection holds the selection to the current CWebDrawCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CWebDrawCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CWebDrawCntrItem* m_pSelection;

private:
	IDrawServ*  m_pDrawServ;
	BOOL        m_bDragging;
	CPoint      m_pos;
	COLORREF    m_col;
	DWORD       m_dwDrawServ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	void DisconnectSink(REFIID iid, DWORD dwCookie);
	BOOL ConnectSink(REFIID iid, LPUNKNOWN punkSink);
	virtual ~CWebDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	Draw(long x1, long y1, long x2, long y2, unsigned long col);
	//{{AFX_MSG(CWebDrawView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BEGIN_INTERFACE_PART(DrawServ, IDrawServ)
		STDMETHOD(GetTypeInfoCount)(unsigned int*)
			{ return E_NOTIMPL; }
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**)
			{ return E_NOTIMPL; }
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
			{ return E_NOTIMPL; }
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*,
						  VARIANT*, EXCEPINFO*, unsigned int*)
			{ return E_NOTIMPL; }
		STDMETHOD(Draw)(long x1, long y1, long x2, long y2, unsigned long col);
	END_INTERFACE_PART(DrawServ)

	DECLARE_INTERFACE_MAP()
};

#ifndef _DEBUG  // debug version in WebDrawView.cpp
inline CWebDrawDoc* CWebDrawView::GetDocument()
   { return (CWebDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBDRAWVIEW_H__848397AD_50EF_4585_A446_54F1CAD81C26__INCLUDED_)
