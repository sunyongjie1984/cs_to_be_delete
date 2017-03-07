// ChatSocket.h: interface for the CChatSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_)
#define AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "chatclientDoc.h"

class CChatSocket : public CSocket  
{
public:
	CChatSocket(CChatClientDoc* pDoc);
	CChatSocket();
	virtual ~CChatSocket();

private:
	CChatClientDoc* m_pDoc;
protected:
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_)
