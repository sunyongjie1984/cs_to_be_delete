// CRCProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CRCProgram.h"
#include "CRCProgramDlg.h"

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
// CCRCProgramDlg dialog

CCRCProgramDlg::CCRCProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCRCProgramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCRCProgramDlg)
	m_strEditCRCResult = _T("");
	m_strEditRawdata = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRCProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCRCProgramDlg)
	DDX_Text(pDX, IDC_EDIT_CRCRESULT, m_strEditCRCResult);
	DDX_Text(pDX, IDC_EDIT_RAWDATA, m_strEditRawdata);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCRCProgramDlg, CDialog)
	//{{AFX_MSG_MAP(CCRCProgramDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETCRC, OnButtonGetcrc)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDATA, OnButtonCleardata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCRCProgramDlg message handlers

BOOL CCRCProgramDlg::OnInitDialog()
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

void CCRCProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCRCProgramDlg::OnPaint() 
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
HCURSOR CCRCProgramDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCRCProgramDlg::OnButtonGetcrc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char data[512];
	int len=Str2Hex(m_strEditRawdata,data);
	unsigned char *ptemp=(unsigned char*)((LPCTSTR)data);
	unsigned short cc=CreateCRC(ptemp,len);




	unsigned short hightbit=cc/256;
	unsigned short lowbit = cc-hightbit*256;

	if (hightbit == 0 && hightbit == 0 && m_strEditRawdata.GetLength() == 0 ) 
	{
		m_strEditCRCResult.Empty();
	}
	
	CString strHighBit;
	strHighBit.Format("%02x",hightbit);

	CString strLowBit;
	strLowBit.Format("%02x",lowbit);
 
	m_strEditCRCResult = strLowBit + ' ' + strHighBit;
	
	if (hightbit == 0 && hightbit == 0 && m_strEditRawdata.GetLength() == 0 ) 
	{
		m_strEditCRCResult.Empty();
	}
	UpdateData(false);
	
	
}


//---------------------下面为校验码处理函数-----------------------

#define CRC16_GEN_POL 0x8005
#define MKSHORT(a,b) ((unsigned short) (a) | ((unsigned short)(b) << 8))
/* ::---------------------------------------------------------------------
:: FN: CreateCRC; CRC in ANSI - C
:: Synopsis: static void CreateCRC(BYTE *CommData,WORD uLen)
:: Function: formation of the CRC16 checksum.
------------------------------------------------------------------------*/
unsigned short CCRCProgramDlg::CreateCRC(unsigned char *CommData, unsigned int uLen )

{
	unsigned short uCrc16;
	unsigned char abData[2];
	uCrc16 = 0;
	abData[0] = 0;
	while (uLen-- )
	{
	abData[1] = abData[0];
	abData[0] = *CommData++;
	if(uCrc16 & 0x8000)
	{
	uCrc16 = (uCrc16 & 0x7fff) << 1;
	uCrc16 ^= CRC16_GEN_POL;
	}
	else
	{
	uCrc16 <<= 1;
	}
	uCrc16 ^= MKSHORT (abData[0] , abData[1]);
	}
	return(uCrc16);
}


int CCRCProgramDlg::Str2Hex(CString str, char* data)
{
	int t,t1;
	int rlen=0,len=str.GetLength();
	//data.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char l,h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	return rlen;

}


char CCRCProgramDlg::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;
}

void CCRCProgramDlg::OnButtonCleardata() 
{
	// TODO: Add your control notification handler code here
	m_strEditCRCResult.Empty();
	m_strEditRawdata.Empty();
	UpdateData(FALSE);
	
}
