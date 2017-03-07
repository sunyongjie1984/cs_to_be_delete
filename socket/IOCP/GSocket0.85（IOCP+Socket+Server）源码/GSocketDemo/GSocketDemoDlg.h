// GSocketDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGSocketDemoDlg 对话框
class CGSocketDemoDlg : public CDialog
{
// 构造
public:
	CGSocketDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GSOCKETDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtGMemPageSize;
	DWORD m_dwGMemPageSize;
	CEdit m_edtGMemTotal;
	DWORD m_dwGMemTotal;
	CEdit m_edtGBufSize;
	DWORD m_dwGBufSize;
	CEdit m_edtIoDataTotal;
	DWORD m_dwIoDataTotal;
	CEdit m_edtHndDataTotal;
	DWORD m_dwHndDataTotal;
	CEdit m_edtPostRecvNumber;
	DWORD m_dwPostRecvNumber;
	CEdit m_edtSocketBufSize;
	int m_nSocketBufSize;
	CEdit m_edtWorkerThreadNumber;
	DWORD m_dwWorkerThreadNumber;
	CEdit m_edtConcurrentThreadNumber;
	DWORD m_dwConcurrentThreadNumber;
	CEdit m_edtAcceptOvertime;
	DWORD m_dwAcceptOvertime;
	CEdit m_edtIdleOvertime;
	DWORD m_dwIdleOvertime;
	CEdit m_edtMaxConnection;
	DWORD m_dwMaxConnection;
	CEdit m_edtPostAcceptNumber;
	DWORD m_dwPostAcceptNumber;
	CEdit m_edtSendLoop;
	DWORD m_dwSendLoop;
	CEdit m_edtListenIp;
	CString m_strListenIp;
	CEdit m_edtListenPort;
	DWORD m_dwListenPort;
	CEdit m_edtSendSpace;
	DWORD m_dwSendSpace;
	CEdit m_edtPackSize;
	DWORD m_dwPackSize;
	CEdit m_edtHeartbeat;
	DWORD m_dwHeartbeat;
	CEdit m_edtConnectNumber;
	DWORD m_dwConnectNumber;
	CEdit m_edtLocalIp;
	CString m_strLocalIp;
	CEdit m_edtLocalPort;
	DWORD m_dwLocalPort;
	CEdit m_edtRemoteIp;
	CString m_strRemoteIp;
	CEdit m_edtRemotePort;
	DWORD m_dwRemotePort;
	CEdit m_edtSendBytes;
	DWORD m_dwSendBytes;
	CEdit m_edtRecvBytes;
	DWORD m_dwRecvBytes;
	CEdit m_edtByteTotal;
	DWORD m_dwByteTotal;
	CEdit m_edtLong;
	DWORD m_dwLong;
	CEdit m_edtBeat;
	float m_fBeat;
	CButton m_bnCloseMtu;
	BOOL m_bCloseMtu;
	CButton m_bnZeroAccept;
	BOOL m_bZeroAccept;
	CButton m_bnZeroRecv;
	BOOL m_bZeroRecv;
	CButton m_bnSendSelf;
	BOOL m_bSendSelf;
	CButton m_bnRandoDisconnect;
	BOOL m_bRandoDisconnect;
	CButton m_bnTcpListen;
	CButton m_bnUdpListen;
	CButton m_bnTcpConnect;
	CButton m_bnUdpConnect;
	CButton m_bnService;
	BOOL m_bShutdownSend;

	void EnabledCtrls(BOOL bIsActive);
	void GetGSocketInfo(void);
	void AddClient(DWORD dwClientContext);
	void DeleteClient(DWORD dwClientContext);

	static void OnConnectSvr(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes);
	static void OnDisconnectSvr(const DWORD dwClientContext);
	static void OnReceiveSvr(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnReceiveErrorSvr(const DWORD dwClientContext);
	static void OnConnectClt(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes);
	static void OnDisconnectClt(const DWORD dwClientContext);
	static void OnReceiveClt(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnReceiveErrorClt(const DWORD dwClientContext);
	static void OnSendedSvr(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnSendErrorSvr(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnSendedClt(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnSendErrorClt(const DWORD dwClientContext, const char* pBuf, const DWORD nBytes);
	static void OnIdleOvertime(const DWORD dwClientContext);
	static void OnConnectionOverflow(const DWORD dwClientContext);
	static void OnHeartbeat(const DWORD dwClientContext);
	static void OnConnectError(const DWORD dwClientContext);
	static void OnCreateClient(const DWORD dwClientContext);
	static void OnDestroyClient(const DWORD dwClientContext);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnEnChangeGedit17();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBnService();
	afx_msg void OnBnClickedBnTcpListen();
	afx_msg void OnBnClickedBnTcpConnect();
	afx_msg void OnBnClickedButton6();
	CListCtrl m_lstInfo;
	afx_msg void OnEnChangeGedit18();
	afx_msg void OnBnClickedButton3();
	DWORD m_dwConnectionCount;
};
