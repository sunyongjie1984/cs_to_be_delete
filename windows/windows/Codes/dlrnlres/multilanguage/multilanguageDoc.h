// multilanguageDoc.h : interface of the CMultilanguageDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILANGUAGEDOC_H__948444B4_09F8_4D44_B48E_ED4CA90EF631__INCLUDED_)
#define AFX_MULTILANGUAGEDOC_H__948444B4_09F8_4D44_B48E_ED4CA90EF631__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMultilanguageDoc : public CDocument
{
protected: // create from serialization only
	CMultilanguageDoc();
	DECLARE_DYNCREATE(CMultilanguageDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultilanguageDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultilanguageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultilanguageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILANGUAGEDOC_H__948444B4_09F8_4D44_B48E_ED4CA90EF631__INCLUDED_)
