// regkeyDlg.h : header file
//

#if !defined(AFX_REGKEYDLG_H__98B6415C_A386_4849_A029_EBF5A898AE72__INCLUDED_)
#define AFX_REGKEYDLG_H__98B6415C_A386_4849_A029_EBF5A898AE72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRegkeyDlg dialog

class CRegkeyDlg : public CDialog
{
// Construction
public:
	CRegkeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegkeyDlg)
	enum { IDD = IDD_REGKEY_DIALOG };
	CString	m_KeyValue;
	CString	m_username;
	CString	m_passname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegkeyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	HKEY      GetRootKey( CString strKeyName );
	VOID      OpenRegItem(PCHAR lpPathbuf);
	int       GetKeyValue(PCHAR lpPath);
	CString   GetFileExName(TCHAR cFileName[MAX_PATH]);
	void      ScreenSoftPro(CString strSoftPath);
	BOOL      AddEventSource(LPTSTR pszLogName, 
							 LPTSTR RegKeyPath,
							 LPTSTR KeyName,
							 DWORD  dwNum);
	BOOL      PreventSystemShutdown();
	BOOL      MySystemShutdown( LPTSTR lpMsg );
	int       readFromFile(IN OUT unsigned char *pchBuffer, const UINT nTotalLen,const UINT nCrcLen, OUT unsigned long int &crc32);
	VOID      aslfsl(PCHAR lpstrold, PCHAR lpstrnew);
	int 	  Foldername(CString strSoftPath, CString strPathname);
	CString      testfileexist(CString str, CString str1, CString stra);
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegkeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGKEYDLG_H__98B6415C_A386_4849_A029_EBF5A898AE72__INCLUDED_)
