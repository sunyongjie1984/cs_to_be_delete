// ApiCommDlg.h : header file
//

#if !defined(AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_)
#define AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CApiCommDlg dialog

class CApiCommDlg : public CDialog
{
// Construction
public:
	CApiCommDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CApiCommDlg)
	enum { IDD = IDD_APICOMM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApiCommDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	volatile HANDLE m_hCom; // 串行口句柄
    OVERLAPPED m_osRead, m_osWrite; // 用于重叠读/写
	int m_nBaud;     //波特率
	int m_nDataBits; //停止位
	int m_nParity;   //校验位
	CString m_strPort;     //串口号
	int m_nStopBits; //停止位
	int m_nFlowCtrl; //流控制选项
	BOOL m_bEcho;    //是否在本地回显
	BOOL m_bNewLine; //是否自动换行

	// Generated message map functions
	//{{AFX_MSG(CApiCommDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APICOMMDLG_H__C105733E_AB00_4308_95C8_6B4FB5574C03__INCLUDED_)
