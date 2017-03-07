#if !defined(AFX_LISTENSOCKET_H__D1F3E595_E7B7_462F_B05A_656EC0D0C703__INCLUDED_)
#define AFX_LISTENSOCKET_H__D1F3E595_E7B7_462F_B05A_656EC0D0C703__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//


class CCockFightDlg;

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCockFightDlg* m_pDlg;
	CListenSocket(CCockFightDlg* pDlg);
	virtual ~CListenSocket();

// Overrides
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__D1F3E595_E7B7_462F_B05A_656EC0D0C703__INCLUDED_)
