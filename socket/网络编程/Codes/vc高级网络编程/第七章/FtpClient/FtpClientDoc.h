// xiongFtpDoc.h : interface of the CFtpClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XIONGFTPDOC_H__C98EEB38_4B16_4E8C_8CAD_7A9545EA8E22__INCLUDED_)
#define AFX_XIONGFTPDOC_H__C98EEB38_4B16_4E8C_8CAD_7A9545EA8E22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFtpClientDoc : public CDocument
{
protected: // create from serialization only
	CFtpClientDoc();
	DECLARE_DYNCREATE(CFtpClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFtpClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFtpClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XIONGFTPDOC_H__C98EEB38_4B16_4E8C_8CAD_7A9545EA8E22__INCLUDED_)
