// fileDlg.h : header file
//

#if !defined(AFX_FILEDLG_H__429F54FB_E134_44AB_9102_8C62675A2FF6__INCLUDED_)
#define AFX_FILEDLG_H__429F54FB_E134_44AB_9102_8C62675A2FF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog

class CFileDlg : public CDialog
{
// Construction
public:
	CFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileDlg)
	enum { IDD = IDD_FILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
struct FILEINFO
{
	char filename[260];
	int  filelength;
};
#endif // !defined(AFX_FILEDLG_H__429F54FB_E134_44AB_9102_8C62675A2FF6__INCLUDED_)
