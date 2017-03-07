// PrinterSelectView.h : interface of the CPrinterSelectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERSELECTVIEW_H__2539138F_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
#define AFX_PRINTERSELECTVIEW_H__2539138F_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrinterSelectView : public CFormView
{
protected: // create from serialization only
	CPrinterSelectView();
	DECLARE_DYNCREATE(CPrinterSelectView)

public:
	//{{AFX_DATA(CPrinterSelectView)
	enum { IDD = IDD_PRINTERSELECT_FORM };
	CComboBox	m_PrinterList;
	//}}AFX_DATA

// Attributes
public:
	CPrinterSelectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterSelectView)
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
	virtual ~CPrinterSelectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrinterSelectView)
	afx_msg void OnSelchangePrinterList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PrinterSelectView.cpp
inline CPrinterSelectDoc* CPrinterSelectView::GetDocument()
   { return (CPrinterSelectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERSELECTVIEW_H__2539138F_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
