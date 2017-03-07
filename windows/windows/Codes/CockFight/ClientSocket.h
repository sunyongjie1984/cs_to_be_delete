#if !defined(AFX_CLIENTSOCKET_H__56D6F65E_4CB0_4656_ADE4_6C690278DD5E__INCLUDED_)
#define AFX_CLIENTSOCKET_H__56D6F65E_4CB0_4656_ADE4_6C690278DD5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//


class CCockFightDlg;

/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCockFightDlg* m_pDlg;
	CClientSocket(CCockFightDlg* pDlg);
	virtual ~CClientSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__56D6F65E_4CB0_4656_ADE4_6C690278DD5E__INCLUDED_)
