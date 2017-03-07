// SparDoc.h : interface of the CSparDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPARDOC_H__E8E933EA_5ED8_4DA6_A1C0_9A74F073D5A9__INCLUDED_)
#define AFX_SPARDOC_H__E8E933EA_5ED8_4DA6_A1C0_9A74F073D5A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSparDoc : public CDocument
{
protected: // create from serialization only
	CSparDoc();
	DECLARE_DYNCREATE(CSparDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSparDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSparDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSparDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPARDOC_H__E8E933EA_5ED8_4DA6_A1C0_9A74F073D5A9__INCLUDED_)
