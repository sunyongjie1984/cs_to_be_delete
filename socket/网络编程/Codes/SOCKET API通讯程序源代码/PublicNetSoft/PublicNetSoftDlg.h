// PublicNetSoftDlg.h : header file
//

#if !defined(AFX_PUBLICNETSOFTDLG_H__4EBB2F30_C788_46DC_AFDB_EC6A848FFA0D__INCLUDED_)
#define AFX_PUBLICNETSOFTDLG_H__4EBB2F30_C788_46DC_AFDB_EC6A848FFA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPublicNetSoftDlg dialog

class CPublicNetSoftDlg : public CDialog
{
// Construction
public:
	CPublicNetSoftDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPublicNetSoftDlg)
	enum { IDD = IDD_PUBLICNETSOFT_DIALOG };
	CListBox	list;
	CString	str;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublicNetSoftDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);

// Implementation

public:

	SOCKET Client;        //客户的连接请求
	SOCKET ServerSocket;                 //SOCKET 
	SOCKADDR_IN m_sockServerAddr;          //SOCKET 结构

	BOOL IsTrue;

	Msg msg;

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPublicNetSoftDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLICNETSOFTDLG_H__4EBB2F30_C788_46DC_AFDB_EC6A848FFA0D__INCLUDED_)
