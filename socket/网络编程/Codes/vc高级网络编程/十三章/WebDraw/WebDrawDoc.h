// WebDrawDoc.h : interface of the CWebDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBDRAWDOC_H__B176E223_78BE_4D7A_ABB2_FCCE410C4016__INCLUDED_)
#define AFX_WEBDRAWDOC_H__B176E223_78BE_4D7A_ABB2_FCCE410C4016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWebDrawSrvrItem;

class CWebDrawDoc : public COleServerDoc
{
protected: // create from serialization only
	CWebDrawDoc();
	DECLARE_DYNCREATE(CWebDrawDoc)

// Attributes
public:
	CWebDrawSrvrItem* GetEmbeddedItem()
		{ return (CWebDrawSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDrawDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWebDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	//{{AFX_MSG(CWebDrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBDRAWDOC_H__B176E223_78BE_4D7A_ABB2_FCCE410C4016__INCLUDED_)
