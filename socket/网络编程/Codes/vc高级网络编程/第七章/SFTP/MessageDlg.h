#if !defined(AFX_MESSAGEDLG_H__34E03321_51B0_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_MESSAGEDLG_H__34E03321_51B0_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog

class CMessageDlg : public CDialog
{
// Construction
public:
	CMessageDlg();
	void TextOut(CString strOut);
	CMessageDlg(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageDlg)
	enum { IDD = IDD_MESSAGE };
	CEdit	m_ctrlEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageDlg)
	public:
	virtual BOOL Create(CWnd* pParent);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEDLG_H__34E03321_51B0_11D5_B587_00E04C39B036__INCLUDED_)
