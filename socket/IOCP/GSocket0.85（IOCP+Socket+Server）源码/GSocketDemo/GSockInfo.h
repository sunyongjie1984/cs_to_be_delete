#pragma once

#include "resource.h"
#include "afxcmn.h"


// CGSockInfo 对话框

class CGSockInfo : public CDialog
{
	DECLARE_DYNAMIC(CGSockInfo)

public:
	CGSockInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGSockInfo();

// 对话框数据
	enum { IDD = IDD_GSOCK_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

	void PostNcDestroy(void);
public:
	DWORD m_dwPhyAvail;
	float m_fPhyFree;
	DWORD m_dwPhyPageSize;
	DWORD m_dwPhyUsedPage;
	DWORD m_dwPhyUsedBytes;

	DWORD m_dwGMemPageSize;
	DWORD m_dwGMemPageNumber;
	DWORD m_dwGMemTotal;
	DWORD m_dwGMemUsed;
	float m_fGMemUsedR;

	DWORD m_dwIodtBytes;
	DWORD m_dwGBufSize;
	DWORD m_dwIodtTotal;
	DWORD m_dwIodtUsed;
	float m_fIodtUsedR;

	DWORD m_dwHddtBytes;
	DWORD m_dwHddtSize;
	DWORD m_dwHddtTotal;
	DWORD m_dwHddtUsed;
	float m_fHddtUsedR;

	DWORD m_dwListener;
	DWORD m_dwClient;
	DWORD m_dwWorker;

	float m_fStartX;
	float m_fSizeOfPix;
	float m_fPixOfSize;
	CRect m_rect;
	DWORD m_dwWidth;
	CBrush m_brushGreen;
	CBrush m_brushRed;
	CPen m_penGreen;
	CClientDC *m_pdc;

	static void OnTraversalGMem(CGSockInfo* pSockInfo, const void* pAddr, DWORD dwSize, const BOOL bIsFree);
	static BOOL OnTraversalThread(CGSockInfo* pSockInfo, const DWORD nIndex, const DWORD dwGThreadId);
	static BOOL OnTraversalListener(CGSockInfo* pSockInfo, const DWORD nIndex, const DWORD dwListenerId);
	static BOOL OnTraversalClient(CGSockInfo* pSockInfo, const DWORD nIndex, const DWORD dwClientContext);
	void OnAddListener(DWORD dwListener);
	void OnConnect(DWORD dwClientContext);
	void OnDisconnect(DWORD dwClientContext);
	CListCtrl m_lstListener;
	CListCtrl m_lstClient;
	CListCtrl m_lstWorker;

	void GetInfo(void);
	void InitListCtrl(void);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	DWORD m_dwWaitAccept;
	DWORD m_dwListItemCount;
	DWORD m_dwThreadTotal;
};

void GInfo_Show(CWnd* pParent);
void GInfo_OnAddListener(DWORD dwListener);
void GInfo_OnConnect(DWORD dwClientContext);
void GInfo_OnDisconnect(DWORD dwClientContext);
void GInfo_ClearList(void);
