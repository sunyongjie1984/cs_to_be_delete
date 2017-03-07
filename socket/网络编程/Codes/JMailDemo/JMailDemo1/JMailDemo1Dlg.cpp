// JMailDemo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMailDemo1.h"
#include "JMailDemo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo1Dlg dialog

CJMailDemo1Dlg::CJMailDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJMailDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJMailDemo1Dlg)
	m_strMailServer = _T("");
	m_strPassword = _T("");
	m_strUserid = _T("");
	m_strBody = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJMailDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJMailDemo1Dlg)
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_ctlMessagesList);
	DDX_Text(pDX, IDC_EDIT_MAILSERVER, m_strMailServer);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserid);
	DDX_Text(pDX, IDC_EDIT_BODY, m_strBody);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJMailDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CJMailDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnReceive)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MESSAGES, OnShowBody)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo1Dlg message handlers

BOOL CJMailDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// 列表控件
	::SendMessage(m_ctlMessagesList.m_hWnd,
					LVM_SETEXTENDEDLISTVIEWSTYLE,
					LVS_EX_FULLROWSELECT,
					LVS_EX_FULLROWSELECT);
	
	m_ctlMessagesList.InsertColumn(0, "发件人", LVCFMT_LEFT, 120);
	m_ctlMessagesList.InsertColumn(1, "主题", LVCFMT_LEFT, 350);
	m_ctlMessagesList.InsertColumn(2, "日期", LVCFMT_LEFT, 100);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJMailDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJMailDemo1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJMailDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//----------------------------------------------------------------
//	接收邮件
//----------------------------------------------------------------

void CJMailDemo1Dlg::OnReceive() 
{
	UpdateData();
	
	m_strMailServer.TrimLeft();
	m_strMailServer.TrimRight();
	m_strUserid.TrimLeft();
	m_strUserid.TrimRight();
	m_strPassword.TrimLeft();
	m_strPassword.TrimRight();

	if(m_strMailServer.GetLength() <= 0)
	{
		AfxMessageBox("邮件服务器不能为空");
		return;
	}
	if(m_strUserid.GetLength() <= 0)
	{
		AfxMessageBox("帐号不能为空");
		return;
	}
	
	m_ctlMessagesList.DeleteAllItems();	// 清空列表
	m_strBodyArray.RemoveAll();
	
	try
	{		
		jmail::IPOP3Ptr pPOP3("JMail.POP3");
		jmail::IMessagesPtr pMessages;


		// 超时 30S
		pPOP3->Timeout = 30;
		
		// 连接邮件服务器
		pPOP3->Connect((LPCTSTR)m_strUserid,
						(LPCTSTR)m_strPassword, 
						(LPCTSTR)m_strMailServer, 
						110);
	
		pMessages = pPOP3->Messages;

		// 已下载的邮件的实际个数(因为第0个ITEM是未用的，所以-1)
		long lCount = pMessages->Count - 1;
		if(lCount == 0)
			AfxMessageBox("信箱为空");
		else
		{
			jmail::IMessagePtr pMessage;

			// 遍历每封信
			for(long i = 1; i <= lCount; i++)
			{
				pMessage = pMessages->Item[i];
				
				_bstr_t bstrFrom = pMessage->From;
				_bstr_t bstrSubject = pMessage->Subject;
				_bstr_t bstrBody = pMessage->Body;
				COleDateTime oleDate = pMessage->Date;

				int nListItem = m_ctlMessagesList.InsertItem(i, (const char*)bstrFrom);
				m_ctlMessagesList.SetItem(nListItem, 1, LVIF_TEXT, (const char*)bstrSubject, 0, 0, 0, NULL);
				m_ctlMessagesList.SetItem(nListItem, 2, LVIF_TEXT, (const char*)oleDate.Format("%Y-%m-%d"), 0, 0, 0, NULL);
				
				m_strBodyArray.Add((const char*)bstrBody);
				
				pMessage.Release();
			}
		}
		// 断开连接
		pPOP3->Disconnect();
	}
	catch(_com_error e)
	{
		CString strErr;
		strErr.Format("错误信息：%s\r\n错误描述：%s", (LPCTSTR)e.ErrorMessage(), (LPCTSTR)e.Description());
		AfxMessageBox(strErr);		
	}
}

//----------------------------------------------------------------
//	显示邮件正文
//----------------------------------------------------------------

void CJMailDemo1Dlg::OnShowBody(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	POSITION pos = m_ctlMessagesList.GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = m_ctlMessagesList.GetNextSelectedItem(pos);
		m_strBody = m_strBodyArray.GetAt(nItem);
		UpdateData(FALSE);
	}
	*pResult = 0;
}


