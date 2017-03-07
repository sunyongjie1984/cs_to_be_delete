#if !defined(AFX_SERVERSOCKET_H__71EA5A8F_5664_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_SERVERSOCKET_H__71EA5A8F_5664_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//

#include "udpsocket.h"

/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CSocket
{
// Attributes
public:
	CUDPSocket m_udp;

// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__71EA5A8F_5664_11D5_B587_00E04C39B036__INCLUDED_)
