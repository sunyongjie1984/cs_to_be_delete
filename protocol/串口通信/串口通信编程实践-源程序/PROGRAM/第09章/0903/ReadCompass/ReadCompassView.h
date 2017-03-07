// ReadCompassView.h : interface of the CReadCompassView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_READCOMPASSVIEW_H__DE80C36E_7EA2_4FAF_B73D_74BB5D124FE7__INCLUDED_)
#define AFX_READCOMPASSVIEW_H__DE80C36E_7EA2_4FAF_B73D_74BB5D124FE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReadCompassSet;

class CReadCompassView : public CRecordView
{
protected: // create from serialization only
	CReadCompassView();
	DECLARE_DYNCREATE(CReadCompassView)

public:
	//{{AFX_DATA(CReadCompassView)
	enum { IDD = IDD_READCOMPASS_FORM };
	CButton	m_ctrlOpenPort;
	CReadCompassSet* m_pSet;
	CString	m_strRXData;
	CMSComm	m_ctrlComm;
	//}}AFX_DATA

// Attributes
public:
	CReadCompassDoc* GetDocument();

// Operations
public:
    BOOL m_bOpenPort;
	CString m_strChecksum2;
	CString m_strPortRXData2;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadCompassView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReadCompassView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReadCompassView)
	afx_msg void OnComm();
	afx_msg void OnOpenComm();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ReadCompassView.cpp
inline CReadCompassDoc* CReadCompassView::GetDocument()
   { return (CReadCompassDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCOMPASSVIEW_H__DE80C36E_7EA2_4FAF_B73D_74BB5D124FE7__INCLUDED_)
