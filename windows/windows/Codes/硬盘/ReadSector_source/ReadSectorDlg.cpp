// ReadSectorDlg.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////


//  READSECTOR  -- code by Sreejth S   < Sreejithsin@yahoo.com >


/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReadSector.h"
#include "ReadSectorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


#define SECTORSPERTRACK 18
#define NUMOFHEADS 2


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
// CReadSectorDlg dialog

CReadSectorDlg::CReadSectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadSectorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadSectorDlg)
	m_FileName_str = _T("");
	m_Head_int = 0;
	m_Sector_int = 0;
	m_Track_int = 0;
	m_NumSec_int = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadSectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadSectorDlg)
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_FileName_str);
	DDX_Text(pDX, IDC_HEAD_EDIT, m_Head_int);
	DDX_Text(pDX, IDC_SECTOR_EDIT, m_Sector_int);
	DDX_Text(pDX, IDC_TRACK_EDIT, m_Track_int);
	DDX_Text(pDX, IDC_NUMSEC_EDIT, m_NumSec_int);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReadSectorDlg, CDialog)
	//{{AFX_MSG_MAP(CReadSectorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBrowseButton)
	ON_BN_CLICKED(IDC_READ_BUTTON, OnReadButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadSectorDlg message handlers

BOOL CReadSectorDlg::OnInitDialog()
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

void CReadSectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReadSectorDlg::OnPaint() 
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
HCURSOR CReadSectorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}






char * CReadSectorDlg::ReadSectors(int head, int track, int sector, int numsec)
{


// getting logical sector from absolut head/track/sector ...
int LogicalSector = (sector-1) + (head*SECTORSPERTRACK) + (track*SECTORSPERTRACK*NUMOFHEADS) ;

typedef struct _DIOC_REGISTERS {
    DWORD reg_EBX;
    DWORD reg_EDX;
    DWORD reg_ECX;
    DWORD reg_EAX;
    DWORD reg_EDI;
    DWORD reg_ESI;
    DWORD reg_Flags;
} DIOC_REGISTERS ;


// char *buffer , errah[10], erral[10] ; 
 char *buffer ; 
 HANDLE hDevice ;
 DIOC_REGISTERS reg ;
 BOOL  fResult ;
 DWORD cb ;

 
 // Creating handle to vwin32.vxd  ...win 95 / 98 !
 hDevice = CreateFile ( "\\\\.\\vwin32", 0, 0, NULL, 0, FILE_FLAG_DELETE_ON_CLOSE, NULL );


 if ( hDevice == INVALID_HANDLE_VALUE ) 
 {

   //MessageBox ( "Error doing CreateFile () !" ) ;
 /* 
    ...this means that a handle to vwin32.vxd was not able to be opened ...
    ....so the operating system is not win 95/98 ...but NT , win2k ...or what (?) ..
    .....reading sectors is  more easy now .....
  */

	HANDLE hDevice; 
	char* buffer = (char*)malloc (512*numsec);
	strset ( buffer , ' ');
	DWORD bytesread ;

    
// Creating a handle to drive a: using CreateFile () function ..
	
	hDevice = CreateFile("\\\\.\\A:", 
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, OPEN_EXISTING, 0, NULL); 
 
    if (hDevice == INVALID_HANDLE_VALUE) 
	{
		MessageBox ("Failed !");
        return NULL;
	}
    
// Setting the pointer to point to the start of the sector we want to read ..
	
	SetFilePointer (hDevice, (LogicalSector*512), NULL, FILE_BEGIN); 

	if (!ReadFile (hDevice, buffer, 512*numsec, &bytesread, NULL) )
	 {
		 /*
		 int err;
		 char error[10];
		 err=GetLastError ();
		 itoa (err, error, 10);
		 MessageBox (error, "Reading sectors ...Failed  ");
		 */
		 return NULL ;
	 }

    CloseHandle(hDevice); 

	return buffer ;
 }

     
// code for win 95/98
// CODE TO ACCESS DISK SECTORS ( ABSOLUTE DISK READ  ) THRU INT 25 
 
// ----------------------------------------------------------------------------------
// CODE TO ACCESS DISK SECTORS ( ABSOLUTE DISK READ  ) THRU INT 25 
// for int 25 sector read 
//            ==> AL must contain the logical drive number ( 0 for floppy drive A: )
//            ==> CX must contain the number of sectors to read 
//   	      ==> DX must contain the starting logical sector number to read 
//	      ==> BX must point to the data buffer to store data 
// ----------------------------------------------------------------------------------
 
    reg.reg_EAX = 0 ;
    reg.reg_ECX = 1 ;

    buffer = (char*) malloc ( 512 * numsec ) ; 
	strset ( buffer , ' ' );


for ( int i = 0; i < numsec; i++ )
{	
	
	reg.reg_EDX = LogicalSector + i ;
	reg.reg_EBX = (DWORD)( buffer + i*512  );

 
 
 //  try atleast 3 times to ensure correct read/write 
 //  2 == VWIN32_DIOC_DOS_INT25
   
   fResult = DeviceIoControl (   hDevice, 2, &reg, sizeof (reg), &reg, sizeof (reg), &cb, 0 ) ;
   fResult = DeviceIoControl (   hDevice, 2, &reg, sizeof (reg), &reg, sizeof (reg), &cb, 0 ) ;
   fResult = DeviceIoControl (   hDevice, 2, &reg, sizeof (reg), &reg, sizeof (reg), &cb, 0 ) ;
   
   
   if (!fResult || (reg.reg_Flags & 0x0001))     
	{
		/*MessageBox ( "Error doing DeviceIoControl () !" ) ;
		int a, b ; 
		a = reg.reg_EAX ;						// ah ;- error code al ;- bios error code
		b = reg.reg_EAX ;
		a &= 255 ;
		b >>= 8 ;
		itoa ( a , erral , 10 ) ;
		itoa ( b , errah , 10 ) ;
		//MessageBox ( errah , "Error cOdE AH "  ) ;
		//MessageBox ( erral , "Error cODe AL "  ) ;
        return NULL ; 		*/
	   
	
	}

}
	
	return buffer ;
	CloseHandle(hDevice);

}



void CReadSectorDlg::OnBrowseButton() 
{

	CFileDialog m_SaveTo_file (FALSE) ;
	if ( m_SaveTo_file.DoModal () == IDOK )
		m_FileName_str = m_SaveTo_file.GetPathName ();

	UpdateData (FALSE) ;
		
	
}




void CReadSectorDlg::OnReadButton() 
{

	
	
	UpdateData (TRUE) ;
	CFile m_Sector_file ;
	char * buffer ;
	
	
	if ( m_FileName_str == "") 
	{
		MessageBox ("Please enter a file to which the read sector contents are to be stored !!");
		return ;
	}
	
	m_Sector_file.Open (m_FileName_str, CFile::modeCreate | CFile::modeWrite  , NULL ) ;
	
	buffer = (char*) malloc (512 * m_NumSec_int) ;


	buffer = ReadSectors (m_Head_int, m_Track_int, m_Sector_int, m_NumSec_int);
	if ( buffer == NULL ) 
	{
		MessageBox ("Operation Failed -- !!");
		return ;
	}
	m_Sector_file.Write (buffer, 512*m_NumSec_int) ;
	m_Sector_file.Close ();

	MessageBox ("Operation Complete !","ReadSectors",  MB_ICONINFORMATION );
	
	

}
