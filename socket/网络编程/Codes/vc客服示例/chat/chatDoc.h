// chatDoc.h : interface of the CChatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATDOC_H__92B5ED6A_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
#define AFX_CHATDOC_H__92B5ED6A_F22F_11D7_8D52_0030F149A9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChatDoc : public CDocument
{
protected: // create from serialization only
	CChatDoc();
	DECLARE_DYNCREATE(CChatDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChatDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDOC_H__92B5ED6A_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
