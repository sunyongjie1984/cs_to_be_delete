// srvrdoc.h : interface of the CServerDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "lstnsock.h"
#include "clntsock.h"
#include <afxtempl.h>

#define PORT 2310

class CMessage;

class CServerDoc : public CDocument
{
protected: // create from serialization only
	CServerDoc();
	DECLARE_DYNCREATE(CServerDoc)

// Attributes
public:
	CListeningSocket* m_pSocket;
	CTypedPtrList<CPtrList, CMessage*> m_lsMsg;
	LONG m_lCount;

	CPtrList m_connectionList;

// Operations
public:
	void UpdateClients();
	void ProcessPendingAccept();
	void ProcessPendingRead(CClientSocket* pSocket);
	CMessage* AssembleMsg(CClientSocket* pSocket);
	CMessage* ReadMsg(CClientSocket* pSocket);
	void SendMsg(CClientSocket* pSocket, CMessage* pMsg);
	void CloseSocket(CClientSocket* pSocket);
	void Message(LPCTSTR lpszMessage);
	void Message1(LPCTSTR lpszMessage);
	void talk(int type2, CString from1, CString to1, CString str1);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Clean();
	void DelSocket();
	virtual ~CServerDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void UpdateList(CClientSocket* pSocke);
	//{{AFX_MSG(CServerDoc)
	afx_msg void OnClean();
	//}}AFX_MSG
	afx_msg void OnUpdateMessages(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnections(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
