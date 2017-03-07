// SenderDoc.h : interface of the CSenderDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDERDOC_H__B86DD883_39E8_433E_AEAC_BAF3BB4D172D__INCLUDED_)
#define AFX_SENDERDOC_H__B86DD883_39E8_433E_AEAC_BAF3BB4D172D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSenderDoc : public CDocument
{
protected: // create from serialization only
	CSenderDoc();
	DECLARE_DYNCREATE(CSenderDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSenderDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSenderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSenderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDERDOC_H__B86DD883_39E8_433E_AEAC_BAF3BB4D172D__INCLUDED_)
