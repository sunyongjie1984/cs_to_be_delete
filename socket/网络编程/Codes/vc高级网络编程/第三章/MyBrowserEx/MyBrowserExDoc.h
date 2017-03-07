// MyBrowserExDoc.h : interface of the CMyBrowserExDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBROWSEREXDOC_H__FCB2C125_FFA7_415C_A464_5F32D0D317E9__INCLUDED_)
#define AFX_MYBROWSEREXDOC_H__FCB2C125_FFA7_415C_A464_5F32D0D317E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyBrowserExDoc : public CDocument
{
protected: // create from serialization only
	CMyBrowserExDoc();
	DECLARE_DYNCREATE(CMyBrowserExDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBrowserExDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyBrowserExDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyBrowserExDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBROWSEREXDOC_H__FCB2C125_FFA7_415C_A464_5F32D0D317E9__INCLUDED_)
