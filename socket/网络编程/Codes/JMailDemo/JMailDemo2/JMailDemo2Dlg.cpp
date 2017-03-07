// JMailDemo2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMailDemo2.h"
#include "JMailDemo2Dlg.h"

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
// CJMailDemo2Dlg dialog

CJMailDemo2Dlg::CJMailDemo2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJMailDemo2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJMailDemo2Dlg)
	m_strBody = _T("");
	m_strMailServer = _T("");
	m_strRecipients = _T("");
	m_strSender = _T("");
	m_strSubject = _T("");
	m_strUserName = _T("");
	m_strKey = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJMailDemo2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJMailDemo2Dlg)
	DDX_Text(pDX, IDC_EDIT_BODY, m_strBody);
	DDX_Text(pDX, IDC_EDIT_MAILSERVER, m_strMailServer);
	DDX_Text(pDX, IDC_EDIT_RECIPIENTS, m_strRecipients);
	DDX_Text(pDX, IDC_EDIT_SENDER, m_strSender);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_KEY, m_strKey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJMailDemo2Dlg, CDialog)
	//{{AFX_MSG_MAP(CJMailDemo2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2Dlg message handlers

BOOL CJMailDemo2Dlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJMailDemo2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJMailDemo2Dlg::OnPaint() 
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
HCURSOR CJMailDemo2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//--------------------------------------------------------------
//	发送邮件
//--------------------------------------------------------------

void CJMailDemo2Dlg::OnSend() 
{
	UpdateData();

	m_strMailServer.TrimLeft();
	m_strMailServer.TrimRight();
	m_strRecipients.TrimLeft();
	m_strRecipients.TrimRight();
	m_strSender.TrimLeft();
	m_strSender.TrimRight();

	if(m_strRecipients.GetLength() < 3)
	{
		AfxMessageBox("请填写正确的收件人邮箱");
		return;
	}
	if(m_strSender.GetLength() <= 0)
	{
		AfxMessageBox("请填写发件人邮箱");
		return;
	}
	if(m_strUserName=="")
	{
		/*
		AfxMessageBox("请输入服务名");
				return;*/
		
	}
	if(m_strKey=="")
	{
/*
		AfxMessageBox("请输入密码");
		return;
*/
	}
	
	try
	{
		jmail::IMessagePtr pMessage("JMail.Message");
		
		// 发件人邮箱
		pMessage->From = (LPCTSTR)m_strSender;
		
		// 发件人姓名
		pMessage->FromName = m_strUserName.GetBuffer(0);
		
		// 添加收件人
		pMessage->AddRecipient((LPCTSTR)m_strRecipients, "", "");
		
		// 优先级设置,1-5逐次降低, 3为中级
		pMessage->Priority = 3;
		
		// 编码方式设置, 默认是iso-8859-1
		pMessage->Charset = "GB2312";
		
		// 主题
		pMessage->Subject = (LPCTSTR)m_strSubject;
		
		// 正文
		pMessage->Body = (LPCTSTR)m_strBody;
		
		// 如有必要，可以再添加一些正文
		//pMessage->AppendText("VC知识库www.VCKBASE.com欢迎您! 祝您身体健康!");
		CString strTemp;
		if(m_strUserName!="")
		{			
			strTemp = m_strUserName;
			strTemp += ":";
			strTemp += m_strKey;
			strTemp += "@";
			strTemp += m_strMailServer;
		}
		else
		{
			strTemp = m_strMailServer;
		}
		
		
		// 开始发送
		pMessage->Send((LPCTSTR)strTemp, VARIANT_FALSE);

		pMessage.Release();
		
		AfxMessageBox("发送成功!");
	}
	catch (_com_error e)
	{
		CString strErr;
		strErr.Format("错误信息：%s\r\n错误描述：%s", (LPCTSTR)e.ErrorMessage(), (LPCTSTR)e.Description());
		AfxMessageBox(strErr);
	}
}
