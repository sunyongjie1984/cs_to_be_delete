// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__12BB9B69_5C23_4A93_8206_EAFAAA22E1E4__INCLUDED_)
#define AFX_MAINFRM_H__12BB9B69_5C23_4A93_8206_EAFAAA22E1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

enum
	{
		FILEICON,
		DIRECTORYICON,
		LOCFILE,
		SERVFILE
	};


class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL m_bConnected;
	CString GetFtpName();
	int GetFtpPort();
	CString GetFtpUser();
	CString GetFtpPassword();

// Operations
public:
	void GetFtpPara(CComboBoxEx* pCombo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	CDialogBar m_wndMyDialogBar;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnQuickconnect();
	afx_msg void OnFileDisconnect();
	afx_msg void OnFileStop();
	afx_msg void OnUpdateFileDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnFileReconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


class CFtpParaClass  
{
public:
	CFtpParaClass();
protected:
	HCURSOR m_hDragCursor;
	BOOL m_bDragging;
	CImageList* m_pDragImageList;
	CImageList m_ctImageList;
public:
	typedef struct
	{
		char szFileName[256];
		char szFileDate[20];
		char szFileSize[20];
		int nType;
	}FILE_FTP_INFO;
	typedef struct
	{
		char fileName[256];
		UINT ufileFlag;
	}FILE_COUNT_INFO;
	typedef struct
	{
		char OldName[256];
		char NewName[256];
	}FILE_CHANGE_INFO;

protected:
	void SetPopMenu(int nIndex);
	void OnFileName(CListCtrl* pListCtrl);
	void OnInsertFile(CListCtrl* pListCtrl,LPVOID pIn,LPARAM lParam);
	void GetFileIcon(CString& fileName,int* iIcon,int* iIconSel=NULL);
	BOOL SetImageList(CListCtrl* pListCtrl,CComboBoxEx* pCombo=NULL);
	void SetFileColumns(CListCtrl* pListCtrl);
public:

	virtual ~CFtpParaClass();

};

/////////////////////////////////////////////////////////////////////////////
// CLocFileView form view



class CLocFileView : public CFormView ,public CFtpParaClass
{
protected:
	CLocFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLocFileView)

// Form Data
public:
	//{{AFX_DATA(CLocFileView)
	enum { IDD = IDD_LOC_FORMVIEW };
	CListCtrl	m_ctLocFile;
	CComboBoxEx	m_ctLocDir;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
protected:
	CMainFrame* m_pMainFrame;
	BOOL m_bHaveDotFlag;
	CWinThread* m_pSendFileThread;
	CWinThread* m_pFindLocFileThread;
	int m_iDirCount;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocFileView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL BeginSendFile(LPVOID pInfo);
	void GetLocCurrentDirectory();
	BOOL BeginFindLocFile();
	void GetLocDir();
	int InsertLocDir(CString& str,int iIcon,int iIconSel);
	virtual ~CLocFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLocFileView)
	afx_msg void OnDblclkLocFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeLocDir();
	afx_msg void OnDropdownLocDir();
	afx_msg void OnBegindragLocFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRclickLocFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditLocFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditLocFile(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnReDisplayLocFile(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetLocDirectoryDisplay(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnInsertLocFile(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetLocRedrawFlag(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetLocDir(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLocFileSend();
	afx_msg void OnLocFileDelete();
	afx_msg void OnLocFileReName();
	afx_msg void OnLocFileOpen();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CServFileView form view

class CServFileView : public CFormView ,public CFtpParaClass
{
protected:
	CServFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CServFileView)

// Form Data
public:
	BOOL BeginRenameFile(LPVOID pInfo);
	BOOL BeginReceiveFile(LPVOID pIn);
	BOOL BeginFindServFile();
	BOOL BeginDeleteFile(LPVOID pInfo);
	//{{AFX_DATA(CServFileView)
	enum { IDD = IDD_SERV_FORMVIEW };
	CButton	m_ctBack;
	CListCtrl	m_ctServFile;
	CComboBoxEx	m_ctServDir;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
protected:
	HBITMAP hBitmap;
	CMainFrame* m_pMainFrame;
	CImageList m_ctServImageList;
	CWinThread*m_pRenameFileThread;
	CWinThread* m_pDeleteFileThread;
	CWinThread* m_pReceiveFileThread;
	CWinThread* m_pFindServFileThread;
	BOOL m_bHaveDotFlag;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServFileView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL SetServImageList(UINT nBitmapID);	
	virtual ~CServFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CServFileView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkServFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragServFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRclickServFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditServFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditServFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBack();
	//}}AFX_MSG
	afx_msg LRESULT OnInsertServFile(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetServRedrawFlag(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetServDirectoryDisplay(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnReDisplayServFile(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetServDir(WPARAM wParam,LPARAM lParam);
	afx_msg void OnServFileDownload();
	afx_msg void OnServFileDelete();
	afx_msg void OnServFileReName();
	afx_msg void OnServFileOpen();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CFtpInfoView view

class CFtpInfoView : public CEditView
{
protected:
	CFtpInfoView();           
// protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFtpInfoView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpInfoView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_NewFont;
	virtual ~CFtpInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFtpInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileReconnect();
	//}}AFX_MSG
	afx_msg LRESULT OnRecordFtpInfo(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CMyAppThread thread
#include <afxinet.h>
class CMyAppThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyAppThread)
protected:
	CMyAppThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	static UINT RenameFileThread(LPVOID lParam);
	static UINT DeleteFileThread(LPVOID lParam);
	static UINT ReceiveFileThread(LPVOID lParam);
	static UINT SendFileThread(LPVOID lParam);
	static UINT FindLocFileThread(LPVOID lParam);
	static UINT FindServFileThread(LPVOID lParam);
protected:
	static BOOL PreDeleteFile(HINTERNET hInetSession,CString& strFtp,CString& OldDir);
	static BOOL PreReceiveFile(HINTERNET hInetSession,CString& str,CString& strFtp,LPVOID pInf);
	static BOOL PreSendFile(CFtpConnection* lpFtp,CString& str,CString& strFtp,LPVOID pInf);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyAppThread();

	// Generated message map functions
	//{{AFX_MSG(CMyAppThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CInputEdit window

class CInputEdit : public CEdit
{
// Construction
public:
	CInputEdit(int iItem,int iSubItem,CString& szInitText,CListCtrl* pListCtrl);

// Attributes
public:

// Operations

	
private:
	CListCtrl* m_pListCtrl;
	CString m_szInitText;
	int m_iItem;
	int m_iSubItem;
	BOOL m_bEsc;
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInputEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInputEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__12BB9B69_5C23_4A93_8206_EAFAAA22E1E4__INCLUDED_)
