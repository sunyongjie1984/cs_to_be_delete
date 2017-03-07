// CloseWindowDoc.h : interface of the CCloseWindowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLOSEWINDOWDOC_H__8D51058F_46B6_417E_BA5B_EE7B50F42CC9__INCLUDED_)
#define AFX_CLOSEWINDOWDOC_H__8D51058F_46B6_417E_BA5B_EE7B50F42CC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCloseWindowDoc : public CDocument
{
protected: // create from serialization only
	CCloseWindowDoc();
	DECLARE_DYNCREATE(CCloseWindowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseWindowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCloseWindowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCloseWindowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEWINDOWDOC_H__8D51058F_46B6_417E_BA5B_EE7B50F42CC9__INCLUDED_)
