// TTYDoc.h : interface of the CTTYDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTYDOC_H__E5640313_0AED_4111_A859_25905A489350__INCLUDED_)
#define AFX_TTYDOC_H__E5640313_0AED_4111_A859_25905A489350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义最大数据块、XON和XOFF
#define MAXBLOCK 4096
#define XON 0x11
#define XOFF 0x13

UINT ComProc(LPVOID pParam);	//

class CTTYDoc : public CDocument
{
protected: // create from serialization only
	CTTYDoc();
	DECLARE_DYNCREATE(CTTYDoc)

// Attributes
public:
	CWinThread* m_pThread; // 代表辅助线程
	volatile BOOL m_bConnected;//表示连接否，用来标识菜单串口连接和断开连接是否可用
	volatile HWND m_hTermWnd;//辅助窗口
	volatile HANDLE m_hPostMsgEvent; // 用于WM_COMMNOTIFY消息的事件对象
	OVERLAPPED m_osRead, m_osWrite; // 用于重叠读/写

	volatile HANDLE m_hCom; // 串行口句柄
	int m_nBaud;//数据传输速率
	int m_nDataBits;//数据位
	BOOL m_bEcho;//表明本地回显
	BOOL m_bNewLine;//表明自动换行
	int m_nParity;//校验位
	CString m_sPort;//串行端口
	int m_nStopBits;//停止位

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CloseConnection();//关闭连接
	BOOL OpenConnection();//打开串口
	BOOL ConfigConnection();//配置连接
	DWORD ReadComm(char *buf,DWORD dwLength);//读串口
	DWORD WriteComm(char *buf,DWORD dwLength);//写串口
	virtual ~CTTYDoc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTYDoc)
	afx_msg void OnApiConnect();
	afx_msg void OnUpdateApiConnect(CCmdUI* pCmdUI);
	afx_msg void OnApiDisconnect();
	afx_msg void OnUpdateApiDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnApiSettings();
	afx_msg void OnUpdateApiSettings(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYDOC_H__E5640313_0AED_4111_A859_25905A489350__INCLUDED_)

