#if !defined(AFX_DIALOGENTROPY_H__CDCD08D8_9A79_4ED8_96B8_B7FE91E48E61__INCLUDED_)
#define AFX_DIALOGENTROPY_H__CDCD08D8_9A79_4ED8_96B8_B7FE91E48E61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEntropy.h : header file
//

#include "TabPageSSL.h"
#include "En_Decode.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogEntropy dialog

class CDialogEntropy : public CTabPageSSL
{
// Construction
public:
	CDialogEntropy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogEntropy)
	enum { IDD = IDD_FORMVIEW_ENTROPY };
	int		m_bEnDeCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEntropy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEntropy)
	afx_msg void OnBUTTONOpen();
	afx_msg void OnBUTTONDecode();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioDecode();
	afx_msg void OnRadioEncode();
	afx_msg void OnButtonDestfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetFileInfo();
	TCHAR InFileName[256];
	TCHAR OutFileName[256];
	TCHAR ExtName[10];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGENTROPY_H__CDCD08D8_9A79_4ED8_96B8_B7FE91E48E61__INCLUDED_)
