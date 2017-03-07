// clntsock.h : interface of the CClientSocket class
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

#ifndef __CLNTSOCK_H__
#define __CLNTSOCK_H__

class CMessage;
class CServerDoc;

class CClientSocket : public CSocket
{
	DECLARE_DYNAMIC(CClientSocket);
private:
	CClientSocket(const CClientSocket& rSrc);         // no implementation
	void operator=(const CClientSocket& rSrc);		  // no implementation

// Construction
public:
	CClientSocket(CServerDoc* m_pDoc);

// Attributes
public:
	int m_nMsgCount;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	CServerDoc* m_pDoc;
	BOOL IsAborted() { return m_pArchiveOut == NULL; }
	BOOL HasConnectionDropped( void );
    bool needdel;
	CString name;
	WORD image;
// Operations
public:
	void Init();
	void Abort();
	void SendMsg(CMessage* pMsg);
	void ReceiveMsg(CMessage* pMsg);

// Overridable callbacks
protected:
	virtual void OnReceive(int nErrorCode);

// Implementation
public:
	virtual ~CClientSocket();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif // __CLNTSOCK_H__
