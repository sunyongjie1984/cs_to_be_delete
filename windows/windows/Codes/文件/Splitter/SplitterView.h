// SplitterView.h : interface of the CSplitterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERVIEW_H__0EE870AC_0CF6_11D5_866A_E8FF0541A007__INCLUDED_)
#define AFX_SPLITTERVIEW_H__0EE870AC_0CF6_11D5_866A_E8FF0541A007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DirDialog.h"
//#include "Dialog.h"

class CSplitterView : public CFormView
{
protected: // create from serialization only
	CSplitterView();
	DECLARE_DYNCREATE(CSplitterView)

public:
	//{{AFX_DATA(CSplitterView)
	enum { IDD = IDD_SPLITTER_FORM };
	CEdit	m_SplitNumCtrl;
	CString	m_RebuildFile;
	CString	m_SplitFilePath;
	CString	m_SelectFolderRebuild;
	CString	m_SelectFolderSplit;
	UINT	m_SplitNum;
	//}}AFX_DATA


// Attributes
public:
	CSplitterDoc* GetDocument();
	void InitSplitNum(){m_SplitNum=2;}

// Operations
public:
	CString m_SplitFileName;
	CDirDialog m_DirDialogRebuild;
	CDirDialog m_DirDialogSplit;

	UINT FSLength;
	UINT AVLength;
	UINT LSTLength;

	BOOL bBrowse1Flag;
	BOOL bBrowse2Flag;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//CString SourcePath;
	CString s1;
	CString s2;
	CString s3;
	CString s4;
	CString s5;
	CString s6;
	CString s7;
	CString s8;
	CString s9;
	CString s10;
	CString s11;
	CString s12;
	CString s13;
	CString s14;
	CString s15;
	CString s16;
	CString s17;
	CString s18;
	CString s19;
	CString s20;

	CString m_RebuildFilePath;
	CString m_RebuildFileName;
	CString str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
	CString str6;
	CString str7;
	CString str8;
	CString str9;
	CString str10;
	CString str11;
	CString str12;
	CString str13;
	CString str14;
	CString str15;
	CString str16;
	CString str17;
	CString str18;
	CString str19;
	CString str20;

	virtual ~CSplitterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterView)
	afx_msg void OnBrowse1();
	afx_msg void OnBrowse2();
	afx_msg void OnSplit();
	afx_msg void OnIncreasebutton();
	afx_msg void OnDecreasebutton();
	afx_msg void OnSelectfolderrebuild();
	afx_msg void OnSelectfoldersplit();
	afx_msg void OnRebuild();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SplitterView.cpp
inline CSplitterDoc* CSplitterView::GetDocument()
   { return (CSplitterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERVIEW_H__0EE870AC_0CF6_11D5_866A_E8FF0541A007__INCLUDED_)
