// FileOperateDlg.h : header file
//

#if !defined(AFX_FILEOPERATEDLG_H__B415EFC3_8698_414B_8453_63871D77B4B9__INCLUDED_)
#define AFX_FILEOPERATEDLG_H__B415EFC3_8698_414B_8453_63871D77B4B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileOperateDlg dialog

class CFileOperateDlg : public CDialog
{
// Construction
public:
	int GetAllFilePath();
	CFileOperateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileOperateDlg)
	enum { IDD = IDD_FILEOPERATE_DIALOG };
	CListCtrl	m_PathList;
	CString	m_strFolderPath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOperateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileOperateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPERATEDLG_H__B415EFC3_8698_414B_8453_63871D77B4B9__INCLUDED_)
