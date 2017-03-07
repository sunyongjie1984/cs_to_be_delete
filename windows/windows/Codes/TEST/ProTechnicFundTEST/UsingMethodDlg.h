#if !defined(AFX_USINGMETHODDLG_H__EA96041B_0083_4590_870A_5117B01AC921__INCLUDED_)
#define AFX_USINGMETHODDLG_H__EA96041B_0083_4590_870A_5117B01AC921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsingMethodDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUsingMethodDlg dialog

class CUsingMethodDlg : public CDialog
{
// Construction
public:
	CUsingMethodDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUsingMethodDlg)
	enum { IDD = IDD_USING_METHOD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingMethodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


private:
	ACE_Task_Visit_DB m_iVisitDBTask;

protected:

	// Generated message map functions
	//{{AFX_MSG(CUsingMethodDlg)
	afx_msg void OnUsingCstringarray();
	afx_msg void OnWriteFile();
	afx_msg void OnStaticInstanceClass();
	afx_msg void OnWriteRecordIntoDb();
	afx_msg void OnReadConnectDbConfigurationFile();
	afx_msg void OnNumberAndCharacterStringConversion();
	afx_msg void OnConnectProcessCommunication();
	afx_msg void OnReadRecordInDb();
	afx_msg void OnDeleteRecordFromDb();
	afx_msg void OnTestArraySlopOver();
	afx_msg void OnCreateSpecifyRegeditKey();
	afx_msg void OnReadSpecifyRegeditKey();
	afx_msg void OnLongDistanceCloseCompeter();
	afx_msg void OnUdpConnectCommunication();
	afx_msg void OnTestLoadResource();
	afx_msg void OnGetHostComputerInfo();
	afx_msg void OnTestAceCommunication();
	afx_msg void OnTestUsingPoint();
	afx_msg void OnGetComputerName();
	afx_msg void OnTestAceSend();
	afx_msg void OnTestGlobalVariable();
	afx_msg void OnEmsMemoryLeak();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_USINGMETHODDLG_H__EA96041B_0083_4590_870A_5117B01AC921__INCLUDED_)
