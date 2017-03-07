#if !defined(AFX_UDPSOCKET_H__71EA5A92_5664_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_UDPSOCKET_H__71EA5A92_5664_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UDPSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CUDPSocket command target

class CUDPSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CUDPSocket();
	virtual ~CUDPSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUDPSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__71EA5A92_5664_11D5_B587_00E04C39B036__INCLUDED_)
