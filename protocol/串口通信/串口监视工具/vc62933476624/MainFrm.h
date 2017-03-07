// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C16C937D_CDB5_4C95_A93D_418310A23218__INCLUDED_)
#define AFX_MAINFRM_H__C16C937D_CDB5_4C95_A93D_418310A23218__INCLUDED_

#include "GUILIB\HEADER\GuiComboBoxExt.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GUILIB\HEADER\GuiFrameWnd.h"
#include "GUILIB\HEADER\GuiToolBarWnd.h"	// Added by ClassView
#include "SerialPort.h"
#include "SCCView.h"
#include "SendFrameWnd.h"	// Added by ClassView
#include "DlgSend.h"	// Added by ClassView
#include "DlgFilter.h"	// Added by ClassView

class CMainFrame : public CGuiFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	BOOL m_bSPort,m_bSSend,m_bSTime;
	BOOL m_bPauseDis,m_bFilter;
// Attributes
public:
	BOOL m_bAscRecv,m_bAscSend;
	BOOL m_bAddEnter,m_bAddEcho,m_bAddStx,m_bAddEtx;
	BOOL m_bToNext;
	struct  _Transmit{
		BOOL bCOM;
		BYTE btCOM1;
		BYTE btCOM2;
	}Trasmt;
	struct  _AutoSave{
		BOOL bSave;
		BOOL bClear;
		int nTime;
		CString strPath;
	}AutoSave;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveIni();
	CSCCView* GetView(){return (CSCCView *)GetActiveView();};
	int IsTriggerLine(CString str);
	UINT m_unCycTimer;
	UINT m_unMulti;
	CDlgSend m_dlgSend;
	BOOL m_bTrigger;
	BOOL SendLine(int nCOMIndex,int nLineIndex=-1);
	int AscSendAdd(CString &str);
	CSendFrameWnd m_wndSF;
	CSerialPort* GetCOM(int nCOMIndex=-1);
	BOOL IsCOMOpen(int nCOMIndex=-1);
	void DisplayStr(CString str,int nCOMIndex,BOOL bRecv=1,BOOL bEnter=1);
	void SetCOMParam(CSerialPort *psp,int nSet);
	CSCCArray m_ascc;
//	CImageList* m_imgList1;
	void EnableSCCBtn(BOOL bEnable=1);
	int m_nCurCOM,m_nToolBtns;
	CGuiComboBoxExt m_comboCOM,m_comboBaud,m_comboParity,m_comboData,m_comboStop,m_comboRTO,m_comboFC;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

// Generated message map functions
protected:
	CString GetRWPath(BOOL bOpen,LPCSTR lpstr,LPCSTR lpstrName=NULL);
	BOOL IsFilterFrame(LPBYTE lpb,int nLength);
	CDlgFilter m_dlgFilter;
	void Transmits(int nCOM,LPBYTE lpbt,int nLength);
	void ReplaceBtnIcon(UINT unID, int nNew);
	void CreateImagelist();
	
	CGuiToolBarWnd m_wndSCCTool;
	DWORD m_dwMs;
	BYTE m_btTrigger,m_btTriggerCOM;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileOpen();
	afx_msg void OnFileXsave();
	afx_msg void OnUpdateFileXsave(CCmdUI* pCmdUI);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	afx_msg void OnSCCComboComSelok();
	afx_msg void OnSCCCommon(UINT nID);
	afx_msg void OnUpdateSCCCommon(CCmdUI* pCmdUI);
	afx_msg void OnSCCCS(UINT nID);
	afx_msg void OnUpdateSCCCS(CCmdUI* pCmdUI);
	afx_msg void OnSCCMRU(UINT nID);
	afx_msg void OnSCCView(UINT nID);
	afx_msg void OnUpdateSCCView(CCmdUI* pCmdUI);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_SCC_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RecvSCCMsg(WPARAM wParam, LPARAM lParam);
	void CreateSCCTool();
	BOOL IsCASDown(int nFlag);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C16C937D_CDB5_4C95_A93D_418310A23218__INCLUDED_)
