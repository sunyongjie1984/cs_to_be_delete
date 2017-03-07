// printerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "printer.h"
#include "printerDlg.h"
#include "Winspool.h"
#include <Winable.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma comment(lib,"Mpr")
#pragma comment(lib,"shell32")
#pragma comment(lib,"Winspool")

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
// CPrinterDlg dialog

CPrinterDlg::CPrinterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrinterDlg)
	m_csPath = _T("");
	m_csUser = _T("");
	m_csPass = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterDlg)
	DDX_Text(pDX, IDC_PATH, m_csPath);
	DDX_Text(pDX, IDC_USER, m_csUser);
	DDX_Text(pDX, IDC_PASS, m_csPass);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrinterDlg, CDialog)
	//{{AFX_MSG_MAP(CPrinterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_GET_PT_INFO, OnGetPtInfo)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_ADD_PRINTER, OnAddPrinter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterDlg message handlers

BOOL CPrinterDlg::OnInitDialog()
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
//	m_pAboutDlg = new CAboutDlg;


/*	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_PRINT;
	ns.lpRemoteName = "\\\\192.168.0.27";
	HANDLE	hEnum;
	dwRet = WNetOpenEnum(RESOURCE_GLOBALNET,RESOURCETYPE_PRINT,RESOURCEUSAGE_ALL,&ns,&hEnum);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("open enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	DWORD	dwCount = 1;
	DWORD	dwSize = 500;
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	*/
/*	PRINTER_INFO_5 pi1;
	ZeroMemory(&pi1,sizeof(pi1));
//	pi1.pComment = new TCHAR[50];
//	pi1.pDescription = new TCHAR[50];
//	pi1.pName = new TCHAR[50];
	pi1.pPortName = new TCHAR[50];
	pi1.pPrinterName = new TCHAR[50];
	DWORD	dwNeed;
	DWORD	dwReturn;
	if(!EnumPrinters(PRINTER_ENUM_NAME | PRINTER_ENUM_SHARED,"\\\\xialei",5,(LPBYTE)&pi1,500,&dwNeed,&dwReturn))
	{
		MessageBox("enum printer failed");
		return;
	}
	MessageBox(pi1.pPrinterName);
	MessageBox(pi1.pPortName);
	ASSERT(PRINTER_ATTRIBUTE_SHARED == pi1.Attributes);
//	MessageBox(pi1.pName);
//	MessageBox(pi1.pDescription);
*/	

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPrinterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPrinterDlg::OnPaint() 
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
HCURSOR CPrinterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPrinterDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	NETRESOURCE ns;
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_ANY;
	TCHAR	tcRemote[65536];
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	
	DWORD  dwRet = WNetAddConnection2(&ns,m_csPass,m_csUser,CONNECT_UPDATE_PROFILE);
	if(dwRet != NO_ERROR)
	{
		dwRet = WNetAddConnection2(&ns,NULL,NULL,CONNECT_UPDATE_PROFILE);
		if(dwRet != NO_ERROR)
		{
			MessageBox("connect error");
			return;
		}
	}
	MessageBox("connect ok");
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_PRINT;
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	HANDLE	hEnum;
	dwRet = WNetOpenEnum(RESOURCE_GLOBALNET,RESOURCETYPE_PRINT,RESOURCEUSAGE_ALL,&ns,&hEnum);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("open enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	DWORD	dwCount = 1;
	DWORD	dwSize = 500;
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
//		return;
	}
	
/*	PRINTER_INFO_5 pi1;
	ZeroMemory(&pi1,sizeof(pi1));
//	pi1.pComment = new TCHAR[50];
//	pi1.pDescription = new TCHAR[50];
//	pi1.pName = new TCHAR[50];
	pi1.pPortName = new TCHAR[50];
	pi1.pPrinterName = new TCHAR[50];
	DWORD	dwNeed;
	DWORD	dwReturn;
	if(!EnumPrinters(PRINTER_ENUM_NAME | PRINTER_ENUM_SHARED,"\\\\xialei",5,(LPBYTE)&pi1,500,&dwNeed,&dwReturn))
	{
		MessageBox("enum printer failed");
		return;
	}
	MessageBox(pi1.pPrinterName);
	MessageBox(pi1.pPortName);
	ASSERT(PRINTER_ATTRIBUTE_SHARED == pi1.Attributes);
//	MessageBox(pi1.pName);
//	MessageBox(pi1.pDescription);
*/	
//	m_pAboutDlg->Create(IDD_ABOUTBOX);
//	m_pAboutDlg->ShowWindow(SW_SHOW);

//	HWND	hWnd = m_pAboutDlg->m_hWnd;
	Sleep(200);
	if(!SHInvokePrinterCommand(NULL,PRINTACTION_NETINSTALL/*|PRINTACTION_NETINSTALLLINK*/,ns.lpRemoteName ,NULL,FALSE))
	{
		MessageBox("SHInvokePrinterCommand failed");
		return;
	}
	MessageBox("SHInvokePrinterCommand ok");
/*	HWND HAddPrinter = ::FindWindow(NULL,_T("Add Printer Wizard"));
//	::ShowWindow(HAddPrinter,SW_HIDE);
//	SystemParametersInfo (SPI_SCREENSAVERRUNNING, 1,NULL, 0);
//	BlockInput(TRUE);

	
	::SetFocus(HAddPrinter);
		::ShowWindow(HAddPrinter,SW_HIDE);
	// Simulate a key press
//	SystemParametersInfo (SPI_SCREENSAVERRUNNING, 1,NULL, 0);
//	BlockInput(TRUE);

	Sleep(100);
         keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);

		 Sleep(100);
		 keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);

		 Sleep(100);
         keybd_event( VK_DOWN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_DOWN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);

		 Sleep(100);
		 keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
		 Sleep(100);
         keybd_event( VK_DOWN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_DOWN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);

		 Sleep(1000);
		 keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_RETURN,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
//		 BlockInput(FALSE);
//		SystemParametersInfo (SPI_SCREENSAVERRUNNING, 0,NULL, 0);

		//	Sleep(50000);
*/
	//	MessageBox("ok");
}

void CPrinterDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
/*
	DWORD dwResult, dwResultEnum;
  HANDLE hEnum;
  DWORD cbBuffer = 16384;      // 16K is a good size
  DWORD cEntries = -1;         // enumerate all possible entries
  LPNETRESOURCE lpnrLocal;     // pointer to enumerated structures
  DWORD i;
  //
  // Call the WNetOpenEnum function to begin the enumeration.
  //
  dwResult = WNetOpenEnum(RESOURCE_GLOBALNET, // all network resources
                          RESOURCETYPE_ANY,   // all resources
                          0,        // enumerate all resources
                          lpnr,     // NULL first time the function is called
                          &hEnum);  // handle to the resource

  if (dwResult != NO_ERROR)
  {  
    //
    // Process errors with an application-defined error handler.
    //
    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
    return ;
  }
  //
  // Call the GlobalAlloc function to allocate resources.
  //
  lpnrLocal = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer);
  
  do
  {  
    //
    // Initialize the buffer.
    //
    ZeroMemory(lpnrLocal, cbBuffer);
    //
    // Call the WNetEnumResource function to continue
    //  the enumeration.
    //
    dwResultEnum = WNetEnumResource(hEnum,      // resource handle
                                    &cEntries,  // defined locally as -1
                                    lpnrLocal,  // LPNETRESOURCE
                                    &cbBuffer); // buffer size
    //
    // If the call succeeds, loop through the structures.
    //
    if (dwResultEnum == NO_ERROR)
    {
      for(i = 0; i < cEntries; i++)
      {
        // Call an application-defined function to
        //  display the contents of the NETRESOURCE structures.
        //
        DisplayStruct(hdc, &lpnrLocal[i]);

        // If the NETRESOURCE structure represents a container resource, 
        //  call the EnumerateFunc function recursively.

        if(RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage
                                       & RESOURCEUSAGE_CONTAINER))
          if(!EnumerateFunc(hwnd, hdc, &lpnrLocal[i]))
            TextOut(hdc, 10, 10, "EnumerateFunc returned FALSE.", 29);
      }
    }
    // Process errors.
    //
    else if (dwResultEnum != ERROR_NO_MORE_ITEMS)
    {
      NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
      break;
    }
  }
  //
  // End do.
  //
  while(dwResultEnum != ERROR_NO_MORE_ITEMS);
  //
  // Call the GlobalFree function to free the memory.
  //
  GlobalFree((HGLOBAL)lpnrLocal);
  //
  // Call WNetCloseEnum to end the enumeration.
  //
  dwResult = WNetCloseEnum(hEnum);
  
  if(dwResult != NO_ERROR)
  { 
    //
    // Process errors.
    //
    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
    return ;
  }
*/


}

void CPrinterDlg::OnGetPtInfo() 
{
	// TODO: Add your control notification handler code here
	PRINTER_INFO_5 pi1;
	ZeroMemory(&pi1,sizeof(pi1));
//	pi1.pComment = new TCHAR[50];
//	pi1.pDescription = new TCHAR[50];
//	pi1.pName = new TCHAR[50];
//	pi1.pPortName = new TCHAR[50];
//	pi1.pPrinterName = new TCHAR[50];
//	DWORD	dwNeed;
//	DWORD	dwReturn;
/*	if(!EnumPrinters(PRINTER_ENUM_LOCAL ,NULL,5,(LPBYTE)&pi1,250,&dwNeed,&dwReturn))
	{
		MessageBox("enum printer failed");
		return;
	}
	AfxMessageBox("enum printer ok");
*///	delete[] pi1.pPortName;
//	delete[] pi1.pPrinterName;
	DWORD		Flags = PRINTER_ENUM_FAVORITE | PRINTER_ENUM_LOCAL; //local printers
	DWORD		cbBuf;
	DWORD		pcReturned ;
//	DWORD		index;
	DWORD		Level = 2;
	TCHAR		Name[500] ;
	LPPRINTER_INFO_2 pPrinterEnum = NULL ;

	memset(Name, 0, sizeof(TCHAR) * 500) ;
	::EnumPrinters(Flags, Name, Level, NULL, 0, &cbBuf, &pcReturned) ;
	pPrinterEnum = (LPPRINTER_INFO_2)LocalAlloc(LPTR, cbBuf + 4) ;

	if (!pPrinterEnum)
		{
		TRACE("Error %1d\n", GetLastError()) ;
		}

	if (!EnumPrinters(
			Flags,							// DWORD Flags, printer object types 
			Name,							// LPTSTR Name, name of printer object 
			Level,							// DWORD Level, information level 
			(LPBYTE)pPrinterEnum,			// LPBYTE pPrinterEnum, printer information buffer 
			cbBuf,							// DWORD cbBuf, size of printer information buffer
			&cbBuf,							// LPDWORD pcbNeeded, bytes received or required 
			&pcReturned)					// LPDWORD pcReturned number of printers enumerated 
			)
			{
			TRACE("Error %1d\n", GetLastError()) ;
			return ;
			}

	if (pcReturned > 0)
	{
		AfxMessageBox("ok");
	}


/*	HANDLE hPrinter = NULL;
	PRINTER_DEFAULTS pd;
	if(!OpenPrinter(NULL,&hPrinter,NULL))
	{
		int ret = GetLastError();
		AfxMessageBox("open failed");
	}
	MessageBox("open ok");
//	GetPrinter()
*/
}

void CPrinterDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	NETRESOURCE ns;
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_ANY;
	TCHAR	tcRemote[65536];
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	
	DWORD  dwRet = WNetAddConnection2(&ns,m_csPass,m_csUser,CONNECT_UPDATE_PROFILE);
	if(dwRet != NO_ERROR)
	{
		dwRet = WNetAddConnection2(&ns,NULL,NULL,CONNECT_UPDATE_PROFILE);
		if(dwRet != NO_ERROR)
		{
			MessageBox("connect error");
			return;
		}
	}
	MessageBox("connect ok");
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_PRINT;
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	HANDLE	hEnum;
	dwRet = WNetOpenEnum(RESOURCE_GLOBALNET,RESOURCETYPE_PRINT,RESOURCEUSAGE_ALL,&ns,&hEnum);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("open enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	DWORD	dwCount = 1;
	DWORD	dwSize = 500;
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
//		return;
	}
	if(!AddPrinterConnection(ns.lpRemoteName))
	{
		int errorcode = GetLastError();
		CString csError;
		csError.Format("AddPrinterConnection error with %d",errorcode);
		MessageBox(csError);
		return;
	}
	MessageBox("AddPrinterConnection ok");
	
}

void CPrinterDlg::OnAddPrinter() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	NETRESOURCE ns;
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_ANY;
	TCHAR	tcRemote[65536];
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	
	DWORD  dwRet = WNetAddConnection2(&ns,m_csPass,m_csUser,CONNECT_UPDATE_PROFILE);
	if(dwRet != NO_ERROR)
	{
		dwRet = WNetAddConnection2(&ns,NULL,NULL,CONNECT_UPDATE_PROFILE);
		if(dwRet != NO_ERROR)
		{
			MessageBox("connect error");
			return;
		}
	}
	MessageBox("connect ok");
	ZeroMemory(&ns,sizeof(ns));
	ns.dwType = RESOURCETYPE_PRINT;
	_tcscpy(tcRemote,m_csPath.GetBuffer(0));
	ns.lpRemoteName = tcRemote;
	HANDLE	hEnum;
	dwRet = WNetOpenEnum(RESOURCE_GLOBALNET,RESOURCETYPE_PRINT,RESOURCEUSAGE_ALL,&ns,&hEnum);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("open enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	DWORD	dwCount = 1;
	DWORD	dwSize = 500;
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
		return;
	}
	dwRet = WNetEnumResource(hEnum,&dwCount,&ns,&dwSize);
	if(dwRet != NO_ERROR)
	{
		CString csError;
		csError.Format("enum error : %d",dwRet);
		MessageBox(csError);
//		return;
	}	
}
