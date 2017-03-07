// apr_mfc_demoDlg.h : header file
//

#if !defined(AFX_APR_MFC_DEMODLG_H__D2299BE3_764D_4C15_9E0F_6A93277EF95E__INCLUDED_)
#define AFX_APR_MFC_DEMODLG_H__D2299BE3_764D_4C15_9E0F_6A93277EF95E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <apr_pools.h>
//#include "thread_pool.h"


/////////////////////////////////////////////////////////////////////////////
// CApr_mfc_demoDlg dialog

class CApr_mfc_demoDlg : public CDialog
{
// Construction
public:
	CApr_mfc_demoDlg(CWnd* pParent = NULL);	// standard constructor

	virtual ~CApr_mfc_demoDlg();

// Dialog Data
	//{{AFX_DATA(CApr_mfc_demoDlg)
	enum { IDD = IDD_APR_MFC_DEMO_DIALOG };
	CListBox	m_listbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApr_mfc_demoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	protected:
	apr_pool_t		* mp;
	CTaskManager  * m_task_manager;
	CChannelManager * m_shineUpon;
	CTCPSessionTask * m_session;
	CMenu m_menu;


// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CApr_mfc_demoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnThreadPoolStart();
	afx_msg void OnThreadPoolStop();
	afx_msg void OnThreadPoolTest();
	afx_msg void OnClearList();
	afx_msg void OnSessionStart();
	afx_msg void OnSessionStop();
	afx_msg void OnSessionConnector();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APR_MFC_DEMODLG_H__D2299BE3_764D_4C15_9E0F_6A93277EF95E__INCLUDED_)
