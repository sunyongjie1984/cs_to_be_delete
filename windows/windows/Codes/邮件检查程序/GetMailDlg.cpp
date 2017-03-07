//最简单的新邮件检查程序

#include "stdafx.h"
#include "GetMail.h"
#include "GetMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICON_NOTIFY WM_USER + 0xA0

static CWinThread *m_pGetMailThread = NULL;

UINT GetMailThread(LPVOID lpParam)
{
	if(lpParam != NULL)
	{
		CGetMailDlg *dlg = (CGetMailDlg *)lpParam;
		CString strPop3 = dlg->m_strPop3;
		CString strUser = dlg->m_strUser;
		CString strPass = dlg->m_strPass;
		CString strInfo;
		int nTime = dlg->m_nTime;
		
		char chData[1024];
		
		int nStart = ::GetTickCount();

		BOOL bRet = FALSE;
		while(1)
		{
			CSocket sckPop;
			bRet = sckPop.Create();
			if(!bRet)
				continue ;
			do
			{
				int nRet = 0;
				bRet = sckPop.Connect(strPop3, 110);
				if(!bRet)
					break ;
				// receive info
				ZeroMemory(chData, 1024);
				nRet = sckPop.Receive(chData, 1024);
				if(nRet < 0 || chData[0] != '+')
					break ;
				// send user name
				ZeroMemory(chData, 1024);
				sprintf(chData, "USER %s\r\n", strUser);
				nRet = sckPop.Send(chData, strlen(chData));
				if(nRet < 0)
					break ;
				// receive return info
				ZeroMemory(chData, 1024);
				nRet = sckPop.Receive(chData, 1024);
				if(nRet < 0 || chData[0] != '+')
					break ;
				
				// send user password
				ZeroMemory(chData, 1024);
				sprintf(chData, "PASS %s\r\n", strPass);
				nRet = sckPop.Send(chData, strlen(chData));
				if(nRet < 0)
					break ;
				// receive return info
				ZeroMemory(chData, 1024);
				nRet = sckPop.Receive(chData, 1024);
				if(nRet < 0 || chData[0] != '+')
					break ;
				// get mail count
				ZeroMemory(chData, 1024);
				sprintf(chData, _T("STAT\r\n"));
				nRet = sckPop.Send(chData, strlen(chData));
				if(nRet < 0)
					break ;
				// receive return info
				ZeroMemory(chData, 1024);
				nRet = sckPop.Receive(chData, 1024);
				if(nRet < 0 || chData[0] != '+')
					break ;
				strInfo = chData;
				// quit pop3
				ZeroMemory(chData, 1024);
				sprintf(chData, _T("QUIT\r\n"));
				nRet = sckPop.Send(chData, strlen(chData));
				if(nRet < 0)
					break ;
				// receive return info
				ZeroMemory(chData, 1024);
				nRet = sckPop.Receive(chData, 1024);
				strInfo.TrimRight();
				dlg->SetInfo(strInfo);
				bRet = TRUE; //OK
			}while(0); // do it once
			sckPop.Close();
			if(!bRet)
			{
				dlg->SetInfo(_T("连接服务器错误!"), FALSE);
			}
			//Delay
			int nEnd = ::GetTickCount();
			if((nEnd - nStart) < (nTime*1000))
			{
				::Sleep(nTime*1000 - (nEnd - nStart));
			}
			nStart = ::GetTickCount();
		}
	}
	return 0;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
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

CGetMailDlg::CGetMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetMailDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bStart = FALSE;
	m_nMailCount = -1;
}

void CGetMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetMailDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetMailDlg, CDialog)
	//{{AFX_MSG_MAP(CGetMailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_HIDE, OnHide)
	ON_COMMAND(IDM_SHOW, OnShow)
	ON_UPDATE_COMMAND_UI(IDM_HIDE, OnUpdateHide)
	ON_UPDATE_COMMAND_UI(IDM_SHOW, OnUpdateShow)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGetMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetDlgItemText(IDC_EDIT_POP3, _T("pop.yeah.net"));
	SetDlgItemText(IDC_EDIT_USER, _T("你的名字"));
	SetDlgItemText(IDC_EDIT_TIME, _T("60"));
	
	VERIFY(m_cSystray.Create(NULL,			// Parent window
			WM_ICON_NOTIFY,					// Icon notify message to use
			_T("新邮件通知程序"),		// tooltip
			m_hIcon,						// Icon to use
			IDR_MENU_TRAY));				// ID of tray icon

	return TRUE;
}

void CGetMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetMailDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

HCURSOR CGetMailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetMailDlg::OnOK() 
{
	if(m_pGetMailThread != NULL)
	{
		::TerminateThread(m_pGetMailThread->m_hThread, 0);
		::WaitForSingleObject(m_pGetMailThread->m_hThread, INFINITE);
		m_pGetMailThread = NULL;
	}
	GetDlgItem(IDC_EDIT_POP3)->EnableWindow(m_bStart);
	GetDlgItem(IDC_EDIT_USER)->EnableWindow(m_bStart);
	GetDlgItem(IDC_EDIT_PASS)->EnableWindow(m_bStart);
	GetDlgItem(IDC_EDIT_TIME)->EnableWindow(m_bStart);

	GetDlgItemText(IDC_EDIT_POP3, m_strPop3);
	GetDlgItemText(IDC_EDIT_USER, m_strUser);
	
	CString strTip;
	strTip.Format(_T("新邮件程序 - 服务器名:%s, 用户名:%s"), m_strPop3, m_strUser);
	strTip.TrimLeft(); strTip.TrimRight();
	m_cSystray.SetTooltipText(strTip);

	if(!m_bStart)
	{
		GetDlgItemText(IDC_EDIT_PASS, m_strPass);
		m_nTime = GetDlgItemInt(IDC_EDIT_TIME);
		m_pGetMailThread = AfxBeginThread(GetMailThread, this);
		m_bStart = TRUE;
		SetDlgItemText(IDOK, _T("停止"));
		OnHide();
	}
	else
	{
		m_bStart = FALSE;
		SetDlgItemText(IDOK, _T("开始"));
	}
}

void CGetMailDlg::SetInfo(CString strInfo, BOOL bOk)
{
	if(!bOk)
	{
		SetDlgItemText(IDC_STATIC_INFO, strInfo);
		return ;
	}
	int nPos = strInfo.Find(_T(' '));
	if(nPos >= 0)
	{
		CString str = strInfo.Right(strInfo.GetLength() - nPos - 1);
		str.TrimLeft(); str.TrimRight();
		nPos = str.Find(_T(' '));
		if(nPos >= 0)
		{
			CString strCount = str.Left(nPos);
			CString strBytes = str.Right(str.GetLength() - nPos - 1);
			int nCount = atoi(strCount);
			int nBytes = atoi(strBytes);
			if(m_nMailCount != -1)
			{
				if(m_nMailCount < nCount)
				{
					CString str;
					str.Format(_T("您有新邮件了! 邮件总数:%d封! 新邮件:%d封!\n邮件服务器名:%s, 用户名:%s.\n"),
						nCount, nCount - m_nMailCount, m_strPop3, m_strUser);
					::MessageBox(NULL, str, _T("邮件通知"), 
						MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
				}
			}
			
			CString strText;
			strText.Format(_T("邮件总数:%d封,新邮件:%d封,大小总计:%.2fKB."), 
				nCount, (m_nMailCount == -1)?0:(nCount - m_nMailCount), 
				(float)(nBytes)/1024.f);
			m_nMailCount = nCount;
			SetDlgItemText(IDC_STATIC_INFO, strText);
			return ;
		}
	}
	SetDlgItemText(IDC_STATIC_INFO, _T("接收到的数据有错误!"));
}

void CGetMailDlg::OnCancel() 
{
	if(m_pGetMailThread != NULL)
	{
		::TerminateThread(m_pGetMailThread->m_hThread, 0);
		::WaitForSingleObject(m_pGetMailThread->m_hThread, INFINITE);
		m_pGetMailThread = NULL;
	}
	CDialog::OnCancel();
}

void CGetMailDlg::OnClose() 
{
	ShowWindow(FALSE);
}

void CGetMailDlg::OnHide()
{
	ShowWindow(FALSE);
}

void CGetMailDlg::OnShow()
{
	ShowWindow(TRUE);
}

void CGetMailDlg::OnUpdateHide(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsWindowVisible());
}

void CGetMailDlg::OnUpdateShow(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!IsWindowVisible());
}

void CGetMailDlg::OnExit()
{
	CDialog::OnOK();
}

void CGetMailDlg::OnAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CGetMailDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		m_cSystray.SetMenuDefaultItem(IDM_HIDE, FALSE);
	}
	else
	{
		m_cSystray.SetMenuDefaultItem(IDM_SHOW, FALSE);
	}
}

void CGetMailDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CDialog::OnWindowPosChanged(lpwndpos);
	if(IsIconic())
	{
		ShowWindow(FALSE);
	}
}
