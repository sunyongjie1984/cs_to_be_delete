#if !defined(AFX_FTPSOCKET_H__C10266B5_50F4_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_FTPSOCKET_H__C10266B5_50F4_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPSocket.h : header file
//

class CSFTPDoc;

/////////////////////////////////////////////////////////////////////////////
// CFTPSocket command target

class CFTPSocket : public CSocket
{
// Attributes
protected:
	CSFTPDoc* m_pDoc;
// Operations
public:
	CFTPSocket();
	virtual ~CFTPSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CFTPSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPSOCKET_H__C10266B5_50F4_11D5_B587_00E04C39B036__INCLUDED_)
