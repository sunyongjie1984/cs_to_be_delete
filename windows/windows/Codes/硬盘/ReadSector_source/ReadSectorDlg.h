// ReadSectorDlg.h : header file
//

#if !defined(AFX_READSECTORDLG_H__040394E3_37CA_4461_A9B5_C040D618F948__INCLUDED_)
#define AFX_READSECTORDLG_H__040394E3_37CA_4461_A9B5_C040D618F948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReadSectorDlg dialog

class CReadSectorDlg : public CDialog
{
// Construction
public:
	char * ReadSectors (int head, int track, int sector, int numsec);
	CReadSectorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReadSectorDlg)
	enum { IDD = IDD_READSECTOR_DIALOG };
	CString	m_FileName_str;
	int		m_Head_int;
	int		m_Sector_int;
	int		m_Track_int;
	int		m_NumSec_int;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadSectorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReadSectorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowseButton();
	afx_msg void OnReadButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READSECTORDLG_H__040394E3_37CA_4461_A9B5_C040D618F948__INCLUDED_)
