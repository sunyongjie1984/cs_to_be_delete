// ChatClientDoc.h : interface of the CChatClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
#define AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "message.h"
class CChatSocket;

class CChatClientDoc : public CRichEditDoc
{
protected: // create from serialization only
	CChatClientDoc();
	DECLARE_DYNCREATE(CChatClientDoc)

// Attributes
public:
	CMessage msg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	void Disconnect();
	BOOL m_bFilter;
	void ReceiveMsg();
	void SendMsg();
	BOOL ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress, LPCTSTR m_strImage, UINT nPort);
	void ProcessPendingRead();
	BOOL m_bConnected;
	virtual ~CChatClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CChatSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;

	CString  m_strHandle;
	void talk(int type, CString from, CString to, CString str,COLORREF clr);
	void DisplayRecMsg(int type, CString from, CString to,BOOL sec, CString str, COLORREF clr);
	void DisplayMsg(LPCTSTR lpszText);
// Generated message map functions
protected:
	//{{AFX_MSG(CChatClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
