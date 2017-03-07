#if !defined(AFX_SERVERSOCKET_H__6E287064_7B6A_43E8_9C0B_70285F5E191B__INCLUDED_)
#define AFX_SERVERSOCKET_H__6E287064_7B6A_43E8_9C0B_70285F5E191B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// ServerSocket command target

class ServerSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	ServerSocket();
	virtual ~ServerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(ServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__6E287064_7B6A_43E8_9C0B_70285F5E191B__INCLUDED_)
