// testGDIDlg.h : header file
//

#if !defined(AFX_TESTGDIDLG_H__60FDB20D_6DE2_42C7_8D94_7CFE3445FB73__INCLUDED_)
#define AFX_TESTGDIDLG_H__60FDB20D_6DE2_42C7_8D94_7CFE3445FB73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// TestCharacterSetDlg dialog

class TestCharacterSetDlg : public CDialog
{
// Construction
public:
	TestCharacterSetDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(TestCharacterSetDlg)
	enum { IDD = IDD_TESTCHARACTERSET_DIALOG };
	CEdit	m_editCodePage;
	CStatic	m_staticText;
	CString	m_csFontName;
	int		m_nAPIType;
	CString	m_csCodePageSet;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TestCharacterSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(TestCharacterSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButtonQueryCodePage();
	afx_msg void OnButtonSetCodePage();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    void DrawMyText(LPCTSTR lpszFontName, LPCTSTR lpszText );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGDIDLG_H__60FDB20D_6DE2_42C7_8D94_7CFE3445FB73__INCLUDED_)
