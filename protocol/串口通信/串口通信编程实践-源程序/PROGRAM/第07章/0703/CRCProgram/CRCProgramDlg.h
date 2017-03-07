// CRCProgramDlg.h : header file
//

#if !defined(AFX_CRCPROGRAMDLG_H__0411373C_DAAA_4F9F_A76E_B712279FF9D6__INCLUDED_)
#define AFX_CRCPROGRAMDLG_H__0411373C_DAAA_4F9F_A76E_B712279FF9D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCRCProgramDlg dialog

class CCRCProgramDlg : public CDialog
{
// Construction
public:
	CCRCProgramDlg(CWnd* pParent = NULL);	// standard constructor

	unsigned short CreateCRC(unsigned char *CommData, unsigned int uLen );

	int Str2Hex(CString str, char* data);

	char HexChar(char c);




// Dialog Data
	//{{AFX_DATA(CCRCProgramDlg)
	enum { IDD = IDD_CRCPROGRAM_DIALOG };
	CString	m_strEditCRCResult;
	CString	m_strEditRawdata;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRCProgramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCRCProgramDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGetcrc();
	afx_msg void OnButtonCleardata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRCPROGRAMDLG_H__0411373C_DAAA_4F9F_A76E_B712279FF9D6__INCLUDED_)
