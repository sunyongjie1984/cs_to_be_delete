// MyQQClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyQQClient.h"
#include "MyQQClientDlg.h"
#include "LoginLoad.h"
#include "MainSocket.h"
#include "TypeDef.h"
#include "Message.h"

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
// CMyMyQQClientDlg dialog

CMyMyQQClientDlg::CMyMyQQClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMyQQClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyMyQQClientDlg)
	m_receive = _T("");
	m_SendName = _T("");
	m_message = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMyQQClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyMyQQClientDlg)
	DDX_Control(pDX, IDC_SEND, m_send);
	DDX_Control(pDX, IDC_RECEIVE, m_ReceiveCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_UserList);
	DDX_Text(pDX, IDC_RECEIVE, m_receive);
	DDX_CBString(pDX, IDC_COMBO1, m_SendName);
	DDX_Text(pDX, IDC_SEND, m_message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyMyQQClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMyMyQQClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVEMESSAGE,OnReceiveMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMyQQClientDlg message handlers
extern CMyMyQQClientApp theApp;
BOOL CMyMyQQClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(!m_skMainSocket.Create())
	{
		AfxMessageBox("创建错误!");
		EndDialog(IDCANCEL);
		return false;
	}
	CLoginLoad dlg;
	dlg.m_Port = 8888;
	dlg.m_Server = "127.0.0.1";
	if(dlg.DoModal() == IDOK)
	{
		if(!m_skMainSocket.Connect(dlg.m_Server,dlg.m_Port))
		{
			AfxMessageBox("连接错误!");
			EndDialog(IDCANCEL);
			return false;
		}
		Message msObj;
		msObj.iType = FIRSTLOG;
		msObj.iSubType = FIRSTTIME;
		CString strName = dlg.m_name;
		
		theApp.m_pMainWnd->SetWindowText(strName);
		int iLen = strName.GetLength();
		lstrcpy(msObj.strName,strName.GetBuffer(iLen));
		strName.ReleaseBuffer();
		m_skMainSocket.Send(&msObj,sizeof(Message));
		m_skMainSocket.SetUserName(strName);
	}
	else
	{
		EndDialog(IDCANCEL);
		return false;
	}

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

void CMyMyQQClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyMyQQClientDlg::OnPaint() 
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
HCURSOR CMyMyQQClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyMyQQClientDlg::OnReceiveMessage(WPARAM wParam, LPARAM lParam)
{
	Message msgObj = *(Message*)wParam;
	if(msgObj.iType == SYSERROR)
	{
		if(msgObj.iSubType == SERVERQUIT)
		{
			MessageBox("服务器关闭");
			EndDialog(IDCANCEL);
			//return;
		}
		else if(msgObj.iSubType = USEREXSIT)
		{
			MessageBox("重名了");
			EndDialog(IDCANCEL);
			//return;
		}
	}
	if(msgObj.iType == USERLOG)
	{
		if(msgObj.iSubType == USERLOGIN)
		{
			m_UserList.AddString(msgObj.strName);
		}
		else if(msgObj.iSubType == USERLOGOUT)
		{
			for(int i=0 ;i < m_UserList.GetCount(); i++)
			{
					CString strName;
					m_UserList.GetLBText(i,strName);
					if(strName == msgObj.strName)
					{
						m_UserList.DeleteString(i);
						break;
					}
			}
		}
	
	}	
	if(msgObj.iType == USERSESSION)
	{
		if(msgObj.iSubType == SERVERSAY)
		{
			CString str,str1;
			str1 = msgObj.strContent;
			str = "服务器通知:\n"+str1;
			MessageBox(str);
		}
		else
		{
			CString name,content,clientName;
			content = name = _T("");
			name = msgObj.strName;
			clientName = msgObj.strClientName;
			content = msgObj.strContent;
			content = name + " : "+content;
			m_receive += content;
			m_receive += char(13);
			m_receive += char(10);
			UpdateData(false);
		}
		
	}
	
}

void CMyMyQQClientDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Message msObj;
	memset(&msObj,0,sizeof(Message));
	msObj.iType = USERSESSION;
	msObj.iSubType = USERQUIT;
	CString strTemp = m_skMainSocket.GetUserName();
	int iLen = strTemp.GetLength();
	lstrcpy(msObj.strName,strTemp.GetBuffer(iLen));
	strTemp.ReleaseBuffer();
	m_skMainSocket.Send(&msObj,sizeof(Message));
	Sleep(100);
	m_skMainSocket.ShutDown();
	m_skMainSocket.Close();

	CDialog::OnClose();
}

void CMyMyQQClientDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	if (m_message.IsEmpty()) return;

	Message msObj;
	memset(&msObj,0,sizeof(Message));
	msObj.iType = USERSESSION;
	msObj.iSubType = SAYINPRIVATE;

	CString strTemp = m_skMainSocket.GetUserName();
	int iLen = strTemp.GetLength();
	lstrcpy(msObj.strName,strTemp.GetBuffer(iLen));
	iLen = iLen = m_SendName.GetLength ();
	lstrcpy(msObj.strClientName,m_SendName.GetBuffer(iLen));
	iLen = m_message.GetLength();
	lstrcpy(msObj.strContent ,m_message.GetBuffer(iLen));
	m_skMainSocket.Send(&msObj,sizeof(Message));

	
	CString strChat;
	m_ReceiveCtrl.GetWindowText(strChat);
	int nLength = strChat.GetLength();
	m_ReceiveCtrl.SetSel(nLength,nLength);
	strChat = m_skMainSocket.m_UserName +  _T(" :");
	m_ReceiveCtrl.ReplaceSel(strChat);
	
	strChat = _T(" ") + m_message + _T("\r\n");
	m_ReceiveCtrl.ReplaceSel(strChat);
	
	m_send.SetWindowText("");
	m_send.SetFocus();	
//	CDialog::OnOK();

}
