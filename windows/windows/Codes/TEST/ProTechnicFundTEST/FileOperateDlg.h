#if !defined(AFX_FILEOPERATEDLG_H__F7891611_8679_4212_BCE3_A43A38A1F7E7__INCLUDED_)
#define AFX_FILEOPERATEDLG_H__F7891611_8679_4212_BCE3_A43A38A1F7E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileOperateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileOperateDlg dialog
typedef struct _NETWORK_FILE
{
	
	SOCKET receiveSocket;
	
}NETWORK_FILE, *PNETWORK_FILE;

class CFileOperateDlg : public CDialog
{
public:
	CUDP_SocketCommuntication m_UdpCommuntication;

public:
	SOCKET UdpSocket;
	NETWORK_FILE receiveSocket;
public:
	int       ReceiveFile();
// Construction
public:
	CFileOperateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileOperateDlg)
	enum { IDD = IDD_FILE };
	CString	m_strMessage;
	CString	m_strFileName;
	CString	m_strIpAddress;
	int		m_nCommunicationPort;
	int		m_nInsertRecordcount;
	int		m_nInsertRecordTimeAlternation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOperateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileOperateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUdpSend();
	afx_msg void OnButtonUdpReceive();
	afx_msg void OnTcpSend();
	afx_msg void OnButtonUdpSendFile();
	afx_msg void OnTestEvent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_FILEOPERATEDLG_H__F7891611_8679_4212_BCE3_A43A38A1F7E7__INCLUDED_)
