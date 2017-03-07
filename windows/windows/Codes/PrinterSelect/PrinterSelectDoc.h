// PrinterSelectDoc.h : interface of the CPrinterSelectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERSELECTDOC_H__2539138D_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
#define AFX_PRINTERSELECTDOC_H__2539138D_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrinterSelectDoc : public CDocument
{
protected: // create from serialization only
	CPrinterSelectDoc();
	DECLARE_DYNCREATE(CPrinterSelectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterSelectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrinterSelectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrinterSelectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERSELECTDOC_H__2539138D_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
