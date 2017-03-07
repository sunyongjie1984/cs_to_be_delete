#if !defined(AFX_MAINSOCKET_H__03FAECEC_3713_4CC6_82DA_19577F322C7F__INCLUDED_)
#define AFX_MAINSOCKET_H__03FAECEC_3713_4CC6_82DA_19577F322C7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMainSocket command target

class CMainSocket : public CSocket
{
// Attributes
public:
	void *m_pMainDlg;
	CString m_UserName;

// Operations
public:
	CMainSocket();
	virtual ~CMainSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	void SetUserName(CString sName);
	CString GetUserName();
	void ReceiveMessage(CString UserName,CString strMessage);
	void SendMessage(CString UserName,CString strMessage);

	// Generated message map functions
	//{{AFX_MSG(CMainSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSOCKET_H__03FAECEC_3713_4CC6_82DA_19577F322C7F__INCLUDED_)
