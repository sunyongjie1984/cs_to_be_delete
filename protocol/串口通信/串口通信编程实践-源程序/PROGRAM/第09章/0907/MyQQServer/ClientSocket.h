#if !defined(AFX_CLIENTSOCKET_H__51B22B88_3D12_4D4D_8CAA_34A063815016__INCLUDED_)
#define AFX_CLIENTSOCKET_H__51B22B88_3D12_4D4D_8CAA_34A063815016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:
	int m_image;
	CString m_UserName;
// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();


// Overrides
public:
	CString GetUserName();
	void SetUserName(CString sName);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
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

#endif // !defined(AFX_CLIENTSOCKET_H__51B22B88_3D12_4D4D_8CAA_34A063815016__INCLUDED_)
