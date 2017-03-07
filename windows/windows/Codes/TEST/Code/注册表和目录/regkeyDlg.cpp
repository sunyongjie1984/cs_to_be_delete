// regkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "regkey.h"
#include "regkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EMPTY_DATA  2 //没有键值
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CProgressCtrl	m_progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
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
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegkeyDlg dialog

CRegkeyDlg::CRegkeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegkeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegkeyDlg)
	m_KeyValue = _T("");
	m_username = _T("");
	m_passname = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegkeyDlg)
	DDX_Text(pDX, IDC_REG_KEY, m_KeyValue);
	DDX_Text(pDX, IDC_REG_KEY2, m_username);
	DDX_Text(pDX, IDC_REG_KEY3, m_passname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegkeyDlg, CDialog)
	//{{AFX_MSG_MAP(CRegkeyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegkeyDlg message handlers

BOOL CRegkeyDlg::OnInitDialog()
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

void CRegkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRegkeyDlg::OnPaint() 
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
HCURSOR CRegkeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

PCHAR g_szRegRootName[] =
{
	"HKEY_CLASSES_ROOT",
	"HKEY_CURRENT_USER",
	"HKEY_LOCAL_MACHINE",
	"HKEY_USERES",
	"HKEY_CURRENT_CONFIG"
};

PCHAR	g_pRegType[] =
{
	"REG_NONE",
	"REG_SZ",
	"REG_EXPAND_SZ",
	"REG_BINARY",
	"REG_DWORD",
	"REG_DWORD_LITTLE_ENDIAN",
	"REG_DWORD_BIG_ENDIAN",
	"REG_LINK",
	"REG_MULTI_SZ",
	"REG_RESOURCE_LIST",
	"REG_FULL_RESOURCE_DESCRIPTOR",
	"REG_RESOURCE_REQUIREMENTS_LIST"
};

HKEY CRegkeyDlg::GetRootKey( CString strKeyName )
{
	for( int i = 0; i < 5; i ++ )
	{
		if( strKeyName == g_szRegRootName[i] )
		{
			if( 4 == i )
			{
				i ++;
			}
			HKEY hKeyReturn =  ( HKEY ) ( 0x80000000 + i );
			return hKeyReturn;
		}
	}
	return 0;
}

CHAR g_strsoftkeyname[50] = {0};

void CRegkeyDlg::OnStart() 
{
	ZeroMemory( g_strsoftkeyname, 50 );
	UpdateData();
	strcpy(g_strsoftkeyname, m_KeyValue.GetBuffer(0));
	CString strkey = "SOFTWARE\\";
 	strkey = strkey + m_KeyValue;
	CHAR	szProcessFullPath[MAX_PATH];
	ZeroMemory( szProcessFullPath, MAX_PATH );
	strcpy(szProcessFullPath, strkey);
	OpenRegItem(szProcessFullPath);
}

VOID CRegkeyDlg::OpenRegItem(PCHAR lpPathbuf) 
{
	HKEY hRootKey = GetRootKey( "HKEY_LOCAL_MACHINE" );	
	HKEY hCurrentKey;
	//打开键值
	long lResult = RegOpenKeyEx( hRootKey, 
								 lpPathbuf,
								 0,
								 KEY_ALL_ACCESS,
								 &hCurrentKey );	
	if( ERROR_SUCCESS != lResult )
	{
		return;
	}
	DWORD dwIndex = 0;



	while( TRUE )
	{
		CHAR	szProcessFullPath[MAX_PATH];
		ZeroMemory( szProcessFullPath, MAX_PATH );
		strcpy(szProcessFullPath,lpPathbuf);

		TCHAR tszEnumKeyName[MAX_PATH];
		ZeroMemory( tszEnumKeyName, sizeof(tszEnumKeyName) );
		
		lResult = RegEnumKey( hCurrentKey, 
							  dwIndex,
							  tszEnumKeyName, 
							  sizeof(tszEnumKeyName) );
		if( ERROR_NO_MORE_ITEMS == lResult )
		{
			break;
		}
		if( ERROR_SUCCESS != lResult )
		{
			DWORD dwError = GetLastError();
			continue;
		}
		dwIndex ++;

		strcat( szProcessFullPath, "\\" );
		strcat( szProcessFullPath, tszEnumKeyName );
		_strlwr( szProcessFullPath );

		CHAR	szFullPath[MAX_PATH];
		ZeroMemory( szFullPath, MAX_PATH );
		strcpy(szFullPath,szProcessFullPath);
		
		if (EMPTY_DATA == GetKeyValue(szProcessFullPath))
		{
			OpenRegItem(szFullPath);
		}
	}		
	RegCloseKey( hCurrentKey );	
}


BOOL CRegkeyDlg::AddEventSource(LPTSTR RootName, 
								LPTSTR RegKeyPath,
								LPTSTR KeyName,
								DWORD  dwNum)
{
	HKEY hk; 
	DWORD dwData, dwDisp; 
	TCHAR szBuf[MAX_PATH]; 
	
	wsprintf(szBuf,  RegKeyPath); 
	
	if (RegCreateKeyEx( HKEY_LOCAL_MACHINE, 
		szBuf, 
		0, 
		NULL, 
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE, 
		NULL, 
		&hk, 
		&dwDisp )) 
	{
		return FALSE;
	}
	dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE; 
	
	if (RegSetValueEx(hk, 
		KeyName,
		0, 
		REG_DWORD, 
		(LPBYTE) &dwData,
		sizeof(DWORD))) 
	{
		return FALSE;
	}	
	RegCloseKey(hk); 
	return TRUE;
}


int CRegkeyDlg::GetKeyValue(PCHAR lpPath) 
{
	HKEY     hRootKey  = GetRootKey( "HKEY_LOCAL_MACHINE" );
	HKEY     hCurrentKey;
	
	long lResult = RegOpenKeyEx( hRootKey, 
								 lpPath,
								 0,
								 KEY_READ | KEY_QUERY_VALUE,//KEY_ALL_ACCESS,
								 &hCurrentKey );
	if( ERROR_SUCCESS != lResult )
	{
		return -1;
	}
	
	BOOL bDefaultIsSet = FALSE;
	CString strDefalultData;
	
	for( int i = 0; TRUE; i ++ )
	{
		DWORD	dwType = 0;
		BYTE	lpData[1024];
		ZeroMemory( lpData, sizeof(lpData) );
		DWORD	dwDataLen = sizeof(lpData);
		CHAR	lpValueName[1024];
		ZeroMemory( lpValueName, sizeof(lpValueName) );
		DWORD	dwValumeNameLen = sizeof(lpValueName);
		
		lResult = RegEnumValue( hCurrentKey,
								i,
								lpValueName,
								&dwValumeNameLen,
								0,
								&dwType,
								lpData,
								&dwDataLen );

		if( ERROR_NO_MORE_ITEMS == lResult )
		{
			RegCloseKey( hCurrentKey );
			DWORD dwError = GetLastError();
			return EMPTY_DATA;
		}
		if( ERROR_SUCCESS != lResult )
		{
			break;
		}
		if( 0 == lpValueName[0] )
		{
			bDefaultIsSet = TRUE;
			strDefalultData = (PCHAR)lpData;
			continue;
		}
		CString strData, strsoftkeyname;
		strData.Format("%s", lpValueName);
		strsoftkeyname.Format("%s", g_strsoftkeyname);

		int iPos = strData.Find("Path",0);
		
		if ( ((strsoftkeyname == "JiangMin")&&(strData == "Path"))||
			 ((strsoftkeyname == "rising")&&(strData == "installpath"))||
			 ((strsoftkeyname == "Symantec")&&(strData == "OptionsPath"))||
			 ((strsoftkeyname == "KingSoft")&&(strData == "Update Path")) )
		{
			strData = lpData;
			::MessageBox(0, strData, lpValueName, 0);
			ScreenSoftPro(strData);
		}

	}	
	return -1;
}

CString CRegkeyDlg::GetFileExName(TCHAR cFileName[MAX_PATH])
{
	CString strFileName,strFileExName;
	
	strFileName = (CString)cFileName;
	strFileExName.Empty();
	for (int i=strFileName.GetLength()-1; i>=0; i--)
	{
		if (strFileName.GetAt(i) != '.')
			strFileExName = strFileName.GetAt(i) + strFileExName;
		else
			return strFileExName;
	}
	return strFileExName;
}

void CRegkeyDlg::ScreenSoftPro(CString strSoftPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString strEx;
	strEx = strSoftPath + "\\*";
	hFind = FindFirstFile(strEx,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	while(FindNextFile(hFind, &wfd)) 
	{  
		strEx = GetFileExName(wfd.cFileName);
		strEx.MakeUpper();
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
            if (strEx == "EXE" || strEx == "KXP")
			{
				CHAR	szProcessFullPath[MAX_PATH];
				ZeroMemory( szProcessFullPath, MAX_PATH );
				strcpy(szProcessFullPath, strSoftPath);
				strcat( szProcessFullPath, "\\" );
				strcat( szProcessFullPath, wfd.cFileName );
				_strlwr( szProcessFullPath );
				::MessageBox(0, szProcessFullPath, "" , 0);
/*
								ACE_ERROR((LM_ERROR,"ScreenAuditFile : %s\r\n",szProcessFullPath));
								DWORD dwError = 0;
								BOOL bSet = FsmgrSetSystemProcess( m_hDriver,
									szProcessFullPath,
									&dwError );
								if( !bSet )
								{
									//error
								}
*/
				
			}
		}
	}
}




void CRegkeyDlg::OnButton2() 
{	
/*
		UpdateData();
		m_KeyValue = "\\\\" + m_KeyValue;
	    NETRESOURCE nr;
	    ZeroMemory(&nr, sizeof(nr));
	    nr.dwType = RESOURCETYPE_ANY;
	    nr.lpLocalName = NULL;
	    nr.lpProvider = NULL;
	    nr.lpRemoteName = m_KeyValue.GetBuffer(0);
	
		nr.dwDisplayType = RESOURCETYPE_ANY;
		nr.dwScope = RESOURCE_GLOBALNET;
		nr.dwUsage = RESOURCEUSAGE_CONTAINER;
		nr.lpComment = NULL;
		
		CFile file("c:\\new.TXT",CFile::modeCreate|CFile::modeWrite);	
		int length = m_passname.GetLength();
		file.Write((LPCTSTR)m_passname,length);
		file.Close();
		
	    DWORD dwResult = WNetAddConnection2(&nr, m_passname, m_username, 0);
		if (NO_ERROR == dwResult)
		{
			MySystemShutdown(NULL);
		}
	*/
	

}
BOOL CRegkeyDlg::MySystemShutdown( LPTSTR lpMsg )
{
/*
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	
	BOOL fResult;               // system shutdown flag 
	
	// Get the current process token handle so we can get shutdown 
	// privilege. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, 
		                  &hToken))
	{
		return FALSE; 
	}
	// Get the LUID for shutdown privilege. 
	// 查找远程关机权限
	LookupPrivilegeValue(m_KeyValue, 
		                 SE_SHUTDOWN_NAME, 
                         &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get shutdown privilege for this process. 
	//调整远程关机权限
	AdjustTokenPrivileges(hToken,
						  FALSE,
						  &tkp, 
						  0, 
						  (PTOKEN_PRIVILEGES) NULL,
						  0); 
	
	// Cannot test the return value of AdjustTokenPrivileges. 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{
		return FALSE; 
	}
	// Display the shutdown dialog box and start the countdown. 
	// 远程关机
	fResult = InitiateSystemShutdown(m_KeyValue.GetBuffer(0),    // shut down local computer 
									 lpMsg,   // message for user
									 20,      // time-out period 
									 FALSE,   // ask user to close apps 
									 TRUE);   // reboot after shutdown 
	
	if (!fResult)
	{
		return FALSE; 
	}
	// Disable shutdown privilege. 
	
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, 
						  FALSE, 
						  &tkp, 
						  0, 
						  (PTOKEN_PRIVILEGES) NULL, 
						  0); 
	
*/	return TRUE; 

}


BOOL CRegkeyDlg::PreventSystemShutdown()
{
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	
	// Get the current process token handle  so we can get shutdown 
	// privilege. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return FALSE; 
	
	// Get the LUID for shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
		&tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
	
	if (GetLastError() != ERROR_SUCCESS) 
		return FALSE; 
	
	// Prevent the system from shutting down. 
	
	if ( !AbortSystemShutdown(NULL) ) 
		return FALSE; 
	
	// Disable shutdown privilege. 
	
	tkp.Privileges[0].Attributes = 0; 
	
	AdjustTokenPrivileges(hToken,
						  FALSE, 
					 	  &tkp,
						  0, 
						  (PTOKEN_PRIVILEGES) NULL, 
						  0); 
	
	return TRUE;
}

int CRegkeyDlg::readFromFile(IN OUT unsigned char *pchBuffer, const UINT nTotalLen,const UINT nCrcLen, OUT unsigned long int &crc32)
{
	char szFilePath[MAX_PATH]={0};
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	CString strFilePath = szFilePath;
	int iPos=strFilePath.ReverseFind('\\');
	CString m_strModulePath=strFilePath.Left(iPos+1);  
	CString strFileName = m_strModulePath + "ConnectF.dat";
	
	FILE *file = NULL;
	
	file = fopen(strFileName.GetBuffer(0), "rb");
	if(!file)
	{
		return -1;
	}
	fseek(file, 0, SEEK_SET);
	long lPos = 0;
	while (lPos < nTotalLen)
	{
		fread(((char *)pchBuffer) + lPos, nTotalLen - lPos, 1, file);
		lPos = ftell(file);
	}
	
	crc32 = 0;
	fclose(file);	
	return 0;
}

void CRegkeyDlg::OnButton3() 
{
	UpdateData();
	CString strpathname;
	CHAR	szProcessFullPath[MAX_PATH];
	ZeroMemory( szProcessFullPath, MAX_PATH );
	
	strcpy(szProcessFullPath, m_KeyValue.GetBuffer(0));
	aslfsl(szProcessFullPath, NULL);
	strpathname.Format("%s", szProcessFullPath);
	strpathname += testfileexist(strpathname, "1234567891.TXT", "");
	::MessageBox(0, strpathname, "", 0);
}
VOID CRegkeyDlg::aslfsl(PCHAR lpstrold, PCHAR lpstrnew)
{
	CString strfilename, strfoldername, strpathname, strmemory ,str, str1;
	
	strpathname.Format("%s", lpstrold);
	
	int iPos = 0;

	while (TRUE)
	{
		int nCount = strpathname.GetLength();
		iPos = strpathname.ReverseFind('\\');
		nCount -= iPos;
		strmemory = strpathname.Right(nCount);
		strpathname = strpathname.Left(iPos);
		str1 = strmemory.Right(nCount - 1);
		
		if ( (8<str1.GetLength())&&(-1 == str1.ReverseFind('.')) )
		{	
			str1 = str1.Left(6) + "~1";
			strmemory = testfileexist(strpathname, str1, str);
		}
		
		str = strmemory + str;

		if (-1 == iPos)
		{
			break;
		}
	}
	iPos = str.ReverseFind('\\');
	strfoldername = str.Left(iPos);
	strcpy( lpstrold, strfoldername.GetBuffer(0) );
	_strlwr( lpstrold );

}

CString CRegkeyDlg::testfileexist(CString strpathname, CString str1, CString stra)
{
	int testCount = 1;
	int iPospro = str1.ReverseFind('.');
	if (-1 != iPospro)
	{				
		CString strtestCount, str2;
		str2 = str1.Right(str1.GetLength() - iPospro);
		strtestCount.Format("%d", testCount++);
		str1 = str1.Left(6) + "~" + strtestCount + str2;
	}
	

 	while (TRUE)
	{
		CString strtemp = strpathname + "\\" + str1+ stra;

		HANDLE hFile = CreateFile( strtemp.GetBuffer(0),
								   GENERIC_READ,
								   FILE_SHARE_READ,
								   NULL,
								   OPEN_EXISTING,
							  	   FILE_ATTRIBUTE_NORMAL,
								   NULL );
		if (hFile != INVALID_HANDLE_VALUE) 
		{ 

			CString strtestCount;
			strtestCount.Format("%d", ++testCount);
			str1 = str1.Left(6) + "~" + strtestCount;		
			
			
			::MessageBox(0, "openfilefail", "", 0);
		}
		else
		{
			CloseHandle(hFile);
			break;
		}
	}
	str1 = "\\" + str1;
	return str1;
}


int CRegkeyDlg::Foldername(CString strSoftPath, CString strPathname)
{
	WIN32_FIND_DATA wfd;
	int nlistCount = 2;
	BOOL nFlag = TRUE;
	HANDLE hFind;
	CString strEx;
	strEx = strSoftPath + "\\*";
	hFind = FindFirstFile(strEx,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	while(FindNextFile(hFind, &wfd)) 
	{  
		strEx.Format("%s", wfd.cFileName);
// 		if () 
		{
			int no1 = strEx.GetLength();
			int no2 = strPathname.GetLength();
			no1 = no1<=no2 ? no1:no2;
			for(int temp = 9; temp<=no1; temp++)
			{
				if (strPathname.GetAt(temp)<strEx.GetAt(temp))
				{
					nFlag = TRUE;
					break;
				}
				else
				{
					if (strPathname.GetAt(temp) == strEx.GetAt(temp)) 
					{
						continue;
					}
					else
					{
						nFlag = FALSE;
						break;
					}
				}
			}
			if (nFlag) 
			{
				--nlistCount;
			}
			else
			{
				--nlistCount;
				++nlistCount;
			}
		}
	}
	return nlistCount;
}
bool g_bflag = false;
BOOL CRegkeyDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ( g_bflag ) 
	{
		return TRUE;	//锁定界面
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CRegkeyDlg::OnButton1() 
{
	g_bflag = true;
	AddEventSource("", 
					"SOFTWARE\\JiangMin\\KV2004\\Install",
					"AA",
					0);	 
}
/*
void CALLBACK  TimerProcForbid(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	int n = 5;
	for(int temp = 0; temp < 100; )
	{
		Sleep(500);
		m_progress.SetPos(temp);
		temp += n;
	}
	::KillTimer( NULL , g_nTimer );
}*/

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	m_progress.SetPos(5);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	m_progress.SetRange32(0,100);
	int n = 5;
	for(int temp = 5; temp <= 100; )
	{
		Sleep(500);
		m_progress.SetPos(temp);
		temp += n;
	}

	
	// Do not call CDialog::OnPaint() for painting messages
}
