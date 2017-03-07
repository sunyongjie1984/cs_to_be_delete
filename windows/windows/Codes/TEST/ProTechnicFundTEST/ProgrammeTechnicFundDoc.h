// ProgrammeTechnicFundDoc.h : interface of the CProgrammeTechnicFundDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMMETECHNICFUNDDOC_H__BB4EF600_22E0_4B64_9093_A3C63BFC52B1__INCLUDED_)
#define AFX_PROGRAMMETECHNICFUNDDOC_H__BB4EF600_22E0_4B64_9093_A3C63BFC52B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProgrammeTechnicFundDoc : public CDocument
{
protected: // create from serialization only
	CProgrammeTechnicFundDoc();
	DECLARE_DYNCREATE(CProgrammeTechnicFundDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrammeTechnicFundDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgrammeTechnicFundDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgrammeTechnicFundDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMMETECHNICFUNDDOC_H__BB4EF600_22E0_4B64_9093_A3C63BFC52B1__INCLUDED_)
