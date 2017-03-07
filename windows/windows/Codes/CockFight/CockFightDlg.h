// CockFightDlg.h : header file
//
#include "SelCSDlg.h"
#include "ClientSocket.h"
#include "ListenSocket.h"

#if !defined(AFX_COCKFIGHTDLG_H__338A2C6F_518A_4192_A780_FD33C2C93599__INCLUDED_)
#define AFX_COCKFIGHTDLG_H__338A2C6F_518A_4192_A780_FD33C2C93599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define CARD_W		71
#define CARD_H		95

#define CARD_WL		45
#define CARD_HL		170

#define TOP			30
#define LEFT		50


#define CONTROL	1
#define ALL_CARD_NUM 51
#define TOY_CARD_NUM 3

/////////////////////////////////////////////////////////////////////////////
// CCockFightDlg dialog

class CCockFightDlg : public CDialog
{
// Construction
public:
	void SendToyInfo();
	void InitReport();
	CString m_strName;
	void SendControlInfo(char chControl);
	void GetControlInfo(char* pBuf, int nLength);
	void SetEnableWin(BOOL bFlag);
	BOOL m_bIsPlaying;
	void InitDlg();
	void SendTalkInfo(char* pBufint, int nLength);
	void SendToAll(char* pBuf, int nLength);
	void ShowCard();

	int m_nBmpID[TOY_CARD_NUM];
	CBitmap bmpCard;
	void GetTalkInfo(char* pBuf,int nLength);
	void ManageInfo(char* pBuf, int nLength);
	void GetCardID(char* pBuf);
	char* m_pchNum;
	void SockSendCard(CClientSocket* pSocket, int nIndex);
	void RandDeal(int nClientNum);
	int m_nClientNum;
	void Deal(CPtrList* pList, int nClientNum);
	BOOL m_bIsClient;
	CClientSocket* m_pClient;
	void OnReceive(CClientSocket* pSocket);
	CPtrList m_connectionList;
	BOOL m_bIsSever;
	void OnAccept();
	CListenSocket* m_psListenSocket;
	CCockFightDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCockFightDlg)
	enum { IDD = IDD_COCKFIGHT_DIALOG };
	CListCtrl	m_listReport;
	CListBox	m_listTalkHistory;
	CString	m_strMsg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCockFightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCockFightDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnForegift();
	afx_msg void OnBtnOpenone();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnDisclaim();
	afx_msg void OnColumnclickListToyinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COCKFIGHTDLG_H__338A2C6F_518A_4192_A780_FD33C2C93599__INCLUDED_)
