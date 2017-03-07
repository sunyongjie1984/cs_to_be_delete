// TestAllocDoc.h : interface of the CTestAllocDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTALLOCDOC_H__477DFD09_9168_4698_A984_1420DEE53435__INCLUDED_)
#define AFX_TESTALLOCDOC_H__477DFD09_9168_4698_A984_1420DEE53435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestAllocDoc : public CDocument
{
protected: // create from serialization only
	CTestAllocDoc();
	DECLARE_DYNCREATE(CTestAllocDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAllocDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestAllocDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestAllocDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTALLOCDOC_H__477DFD09_9168_4698_A984_1420DEE53435__INCLUDED_)
