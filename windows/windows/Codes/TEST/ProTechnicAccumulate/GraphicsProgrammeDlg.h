#if !defined(AFX_GRAPHICSPROGRAMMEDLG_H__9CFBB8E2_FE69_49CD_A28F_CC98E4BA5FCA__INCLUDED_)
#define AFX_GRAPHICSPROGRAMMEDLG_H__9CFBB8E2_FE69_49CD_A28F_CC98E4BA5FCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicsProgrammeDlg.h : header file
//
#include "ShowBitmapChildWindowFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphicsProgrammeDlg dialog

class CGraphicsProgrammeDlg : public CDialog
{
// Construction
public:
	CShowBitmapChildWindowFrame * m_pShowBmpFrm;

public:
	CGraphicsProgrammeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphicsProgrammeDlg)
	enum { IDD = IDD_DLG_GRAPHICS_PROGRAMME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsProgrammeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphicsProgrammeDlg)
	afx_msg void OnButtonShowBitmapFile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSPROGRAMMEDLG_H__9CFBB8E2_FE69_49CD_A28F_CC98E4BA5FCA__INCLUDED_)
