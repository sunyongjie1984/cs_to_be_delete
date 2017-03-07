// demoDlg.h : header file
//

#include "SerialPort.h"
#if !defined(AFX_DEMODLG_H__9F2011D0_1EE3_4811_A1B7_EF3276301EB6__INCLUDED_)
#define AFX_DEMODLG_H__9F2011D0_1EE3_4811_A1B7_EF3276301EB6__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor
	
	CSerialPort m_Port;  //CSerialPort类对象
	HICON m_hIconRed;    //串口打开时的红灯图标句柄
	HICON m_hIconOff;    //串口关闭时的指示图标句柄
	BOOL m_bStopDispRXData; //是否显示接收字符


	int m_nBaud;       //波特率
	int m_nCom;         //串口号
	char m_cParity;    //校验
	int m_nDatabits;    //数据位
	int m_nStopbits;    //停止位


// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
	CStatic	m_ctrlControlStatus;
	CStatic	m_ctrlTXCount;
	CStatic	m_ctrlPortStatus;
	CStatic	m_ctrlRXCOUNT;
	CEdit	m_ctrlReceiveData;
	CStatic	m_ctrlIconOpenoff;
	CComboBox	m_StopBits;
	CComboBox	m_DataBits;
	CComboBox	m_Parity;
	CComboBox	m_Baud;
	CComboBox	m_Com;
	CButton	m_ctrlHexSend;
	CButton	m_ctrlHexReceive;
	CButton	m_ctrlAutoSend;
	CButton	m_ctrlUrgencyStop;
	CButton	m_ctrlTurnRight;
	CButton	m_ctrlTurnLeft;
	CButton	m_ctrlSyn2;
	CButton	m_ctrlSyn1;
	CButton	m_ctrlSyn0;
	CButton	m_ctrlStopDisp;
	CButton	m_ctrlStop;
	CButton	m_ctrlStartMotor;
	CButton	m_ctrlOpenPort;
	CButton	m_ctrlOnWard;
	CButton	m_ctrlManualSend;
	CButton	m_ctrlCloseMotor;
	CButton	m_ctrlClearTXData;
	CButton	m_ctrlReverse;
	CString	m_ReceiveData;
	CString	m_strSendData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL PreTranslateMessage(MSG* pMsg);
	void StrtoHex(CString str);
	void CurrentControlStatus(int ControlStatus);
	BOOL m_bAutoSend;
	void CountDisplay(CString str);////用于显示命令的字节数
	char HexChar(char c);
	int Str2Hex(CString str, char *data);
	HICON m_hIcon;
	DWORD m_dwCommEvents;		
	BOOL m_bOpenPort;
	int m_nCycleTime;



	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);// 手动添加
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonClosemotor();
	afx_msg void OnButtonOpenport();
	afx_msg void OnButtonClearReciArea();
	afx_msg void OnButtonStopdisp();
	afx_msg void OnButtonClearrecasenda();
	afx_msg void OnButtonManualsend();
	afx_msg void OnCheckAutosend();
	afx_msg void OnChangeEditCycletime();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEditSend();
	afx_msg void OnButtonSyn0();
	afx_msg void OnButtonSyn1();
	afx_msg void OnButtonSyn2();
	afx_msg void OnButtonStartmotor();
	afx_msg void OnButtonUrgencystop();
	afx_msg void OnButtonOnward();
	afx_msg void OnButtonReverse();
	afx_msg void OnButtonTurnleft();
	afx_msg void OnButtonTurnright();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonCountreset();
	afx_msg void OnSelendokComboDatabits();
	afx_msg void OnSelendokComboParity();
	afx_msg void OnSelendokComboStopbits();
	afx_msg void OnSelendokComboComselect();
	afx_msg void OnSelendokComboBaud();
	afx_msg void OnButtonReset();
	afx_msg void OnButtoncReverse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__9F2011D0_1EE3_4811_A1B7_EF3276301EB6__INCLUDED_)
