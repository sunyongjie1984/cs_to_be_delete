#if !defined(AFX_EXPORTDIALOG_H__430472E1_1B81_4FC9_B43A_9C29CB152A9C__INCLUDED_)
#define AFX_EXPORTDIALOG_H__430472E1_1B81_4FC9_B43A_9C29CB152A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportDialog.h : header file
//

// CExportDialog dialog
//
class __declspec(dllexport) CExportDialog : public CDialog
{
// Construction
public:
	CExportDialog(CWnd* pParent = NULL);   // standard constructor

	DECLARE_SERIAL(CExportDialog)

// Dialog Data
	//{{AFX_DATA(CExportDialog)
	enum { IDD = IDD_EXPORTCLASSDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExportDialog)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_bmp;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTDIALOG_H__430472E1_1B81_4FC9_B43A_9C29CB152A9C__INCLUDED_)
