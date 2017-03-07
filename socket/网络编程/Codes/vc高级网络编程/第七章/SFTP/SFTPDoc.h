// SFTPDoc.h : interface of the CSFTPDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SFTPDOC_H__C10266AB_50F4_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_SFTPDOC_H__C10266AB_50F4_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ftpclient.h"
#include "ListItem.h"

class CSFTPDoc : public CDocument
{
protected: // create from serialization only
	CSFTPDoc();
	DECLARE_DYNCREATE(CSFTPDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFTPDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Back();
	void CD(CString dir);
	void RetreiveFile(CString filename);
	void AddLine(CString strLine);
	void RemoveAll();
	void Receive();
	virtual ~CSFTPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFTPClient* ftp;
// Generated message map functions
protected:
	//{{AFX_MSG(CSFTPDoc)
	afx_msg void OnFileConnect();
	afx_msg void OnFileDisconnect();
	afx_msg void OnLogin();
	afx_msg void OnUpdateLogin(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFTPDOC_H__C10266AB_50F4_11D5_B587_00E04C39B036__INCLUDED_)
