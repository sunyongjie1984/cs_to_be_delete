// CockFightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CockFight.h"
#include "CockFightDlg.h"

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
// CCockFightDlg dialog

CCockFightDlg::CCockFightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCockFightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCockFightDlg)
	m_strMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsSever = FALSE;
	m_bIsClient = FALSE;
	m_bIsPlaying = FALSE;
	m_pClient = NULL;
	m_nClientNum = 0;
	
}

void CCockFightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCockFightDlg)
	DDX_Control(pDX, IDC_LIST_TOYINFO, m_listReport);
	DDX_Control(pDX, IDC_LIST_HISTORY, m_listTalkHistory);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCockFightDlg, CDialog)
	//{{AFX_MSG_MAP(CCockFightDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FOREGIFT, OnBtnForegift)
	ON_BN_CLICKED(IDC_BTN_OPENONE, OnBtnOpenone)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_DISCLAIM, OnBtnDisclaim)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_TOYINFO, OnColumnclickListToyinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCockFightDlg message handlers

BOOL CCockFightDlg::OnInitDialog()
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
	InitDlg();
	InitReport();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CCockFightDlg::SetEnableWin(BOOL bFlag)
{
	GetDlgItem(IDC_BTN_FOREGIFT)->EnableWindow(bFlag);
	GetDlgItem(IDC_BTN_OPENONE)->EnableWindow(bFlag);
	GetDlgItem(IDC_BTN_DISCLAIM)->EnableWindow(bFlag);
	GetDlgItem(IDOK)->EnableWindow(!bFlag);
	return;
}

void CCockFightDlg::InitDlg()
{
	SetEnableWin(FALSE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	
}
void CCockFightDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCockFightDlg::OnPaint() 
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
	if(m_bIsSever | m_bIsClient)
	{
		ShowCard();
	}
}


void CCockFightDlg::ShowCard()
{
	CDC* pDC;
	CDC dcMem;

	pDC = GetDC();
	dcMem.CreateCompatibleDC(pDC);

	for(int i=0; i<TOY_CARD_NUM; i++)
	{
		bmpCard.LoadBitmap(m_nBmpID[i]);
		dcMem.SelectObject(&bmpCard);
		pDC->BitBlt(LEFT+i*CARD_WL,TOP+CARD_HL,CARD_W,CARD_H,&dcMem,0,0,SRCCOPY);
		bmpCard.DeleteObject();
	}
	DeleteObject(&bmpCard);
	dcMem.DeleteDC();	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCockFightDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

char* pColumnName[] = {
				"玩家",
				"胜绩",
				"拥有点数"};

#define COLUMN_CX 60

void CCockFightDlg::InitReport()
{
	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT |LVCF_SUBITEM ;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = COLUMN_CX;

	
	int nNum = sizeof(pColumnName) / sizeof(char*);
	for(int i=0; i<nNum; i++)
	{
		lvColumn.iSubItem = i; 
		lvColumn.pszText = pColumnName[i];
		m_listReport.InsertColumn(i,&lvColumn);
	}

//	m_listReport.SetStyle( LVS_SINGLESEL );
}

void CCockFightDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_bIsClient)
	{
		return;
	}
	if(m_bIsSever)
	{
		Deal(&m_connectionList,m_nClientNum);
		GetCardID(&m_pchNum[TOY_CARD_NUM*m_nClientNum-1]);
		SetEnableWin(TRUE);
		return;
	}
	CSelCSDlg dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		if(!dlg.m_nIndex)
		{
			m_psListenSocket = new CListenSocket(this);
			if(m_psListenSocket->Create(dlg.m_nPort))
			{
				if(!m_psListenSocket->Listen())
				{
					AfxMessageBox("侦听失败!");
					return;
				}
				else
				{
					m_bIsSever = TRUE;
					m_strName = dlg.m_strName;
					m_listReport.InsertItem(0,m_strName);
					m_listTalkHistory.AddString(m_strName+" 建得服务器开启了！");
					GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
					srand(time(0));
				}
			}
			else
			{
				AfxMessageBox("ListenSocket建立失败!");
				return;
			}
		}
		else
		{
			m_pClient = new CClientSocket(this);
			if(m_pClient->Create())
			{
				if(m_pClient->Connect(dlg.m_strSvrName,dlg.m_nPort))
				{
					m_bIsClient = TRUE;
					m_strName = dlg.m_strName;
					GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
					CString strCome = m_strName + "进来了!";
					SendTalkInfo(strCome.GetBuffer(1), strCome.GetLength());
					Sleep(100);
					SendControlInfo(0);
				}
				else
				{
					MessageBox("Can't Connect Sever!");
				}
			}
			else
			{
				MessageBox(" Can't Create Client Socket!");
			}

		}
	}
}

void CCockFightDlg::OnAccept()
{
	CClientSocket* pClientSocket = new CClientSocket(this);
	if(m_psListenSocket->Accept(*pClientSocket))
	{
		m_connectionList.AddTail(pClientSocket);
		m_nClientNum++;
		CString strGetName = 2;
		strGetName += 5;
		strGetName += '\0';
		pClientSocket->Send(strGetName.GetBuffer(1),3);
	}
	else
	{
		delete pClientSocket;
	}
}

void CCockFightDlg::OnReceive(CClientSocket* pSocket)
{
	char* pBuf = new char[512];
	int nLength = pSocket->Receive(pBuf,512);

	ManageInfo(pBuf, nLength);
	delete [] pBuf;
}


void CCockFightDlg::Deal(CPtrList* pList,int nClientNum)
{
	POSITION pos;
	int nIndex = 0;
	
	RandDeal(nClientNum);
	for(pos=pList->GetHeadPosition(); pos!=NULL;)
	{
		CClientSocket* pSocket;
		pSocket = (CClientSocket*) pList->GetNext(pos);
		SockSendCard(pSocket, nIndex);
		nIndex ++;
	}
}


#define ALL_TOY_CARD_NUM(nClient) (1+nClient)*TOY_CARD_NUM

void CCockFightDlg::RandDeal(int nClientNum)
{
	BOOL bHave;
	int nToyNum = ALL_TOY_CARD_NUM(nClientNum);
	
	m_pchNum = new char [nToyNum];
	
	for(int i=0; i<nToyNum; i++)
	{
		while(TRUE)
		{
			bHave = FALSE;
			m_pchNum[i] = rand()%ALL_CARD_NUM;
			for(int j=0; j<i; j++)
			{
				if(m_pchNum[i] == m_pchNum[j])
				{
					bHave = TRUE;
					break;
				}
			}
			if(!bHave)
			{
				break;
			}
		}
	}
}

void CCockFightDlg::SockSendCard(CClientSocket *pSocket, int nIndex)
{
	char* pSend = new char [CONTROL+TOY_CARD_NUM];
	pSend[0] = 0;
	for(int i=0; i<TOY_CARD_NUM; pSend[i+1]=m_pchNum[i+nIndex*TOY_CARD_NUM], i++);
	pSocket->Send(pSend, TOY_CARD_NUM+1);		
}

void CCockFightDlg::GetCardID(char* pBuf)
{
	for(int i=0; i<TOY_CARD_NUM; i++)
	{
		m_nBmpID[i] = pBuf[i+1] + IDB_F2;
	}
	Invalidate(FALSE);
}


void CCockFightDlg::ManageInfo(char* pBuf,int nLength)
{
	switch(pBuf[0])
	{
		case	0:	GetCardID(pBuf);
					SetEnableWin(TRUE);
					break;
		
		case	1:	GetTalkInfo(pBuf, nLength);
					break;
		
		case	2:	GetControlInfo(pBuf, nLength);
					break;
	}
}
					
void CCockFightDlg::GetControlInfo(char *pBuf, int nLength)
{
	char chCotrol = pBuf[1];
	
	switch(chCotrol)
	{
		case	0:	m_listReport.InsertItem(m_nClientNum,&pBuf[2]);
					SendToyInfo();
					break;

		case	1:
		case	2:
		case	3:	break;
		
		case	5:	SendControlInfo(0);
					break;
	}
}

void CCockFightDlg::GetTalkInfo(char *pBuf,int nLength)
{
	m_listTalkHistory.AddString(&pBuf[1]);
	if(m_bIsSever)
	{
		SendToAll(pBuf, nLength);
	}
}

void CCockFightDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strMsg.IsEmpty())
	{
		MessageBox("消息不能为空!");
		return;
	}
	CString strTalk = m_strName;
	strTalk += "说：";
	strTalk += m_strMsg;
	int nLength = strTalk.GetLength();
	SendTalkInfo(strTalk.GetBuffer(1), nLength);
	m_strMsg.Empty();
	UpdateData(FALSE);
}

void CCockFightDlg::SendToAll(char *pBuf, int nLength)
{
	POSITION pos;
	
	for(pos=m_connectionList.GetHeadPosition(); pos!=NULL;)
	{
		CClientSocket* pSocket;
		pSocket = (CClientSocket*) m_connectionList.GetNext(pos);
		pSocket->Send(pBuf,nLength);
	}
}

void CCockFightDlg::SendTalkInfo(char *pBuf, int nLength)
{
	char* pchTempSend = new char [nLength+2];

	pchTempSend[0] = 1;
	for(int i=0; i<nLength; pchTempSend[i+1]=pBuf[i],i++);
	pchTempSend[nLength+1] = '\0';
	if(m_bIsClient)
	{
		m_pClient->Send(pchTempSend,nLength+2);
	}
	else
	{
		m_listTalkHistory.AddString(pBuf);
		SendToAll(pchTempSend,nLength+2);
	}
}

void CCockFightDlg::OnBtnDisclaim() 
{
	// TODO: Add your control notification handler code here
	const IDB_OVER = IDB_CARD - IDB_F2;
	char pBuf[] = {IDB_OVER,IDB_OVER,IDB_OVER};
	GetCardID(pBuf);

	SendControlInfo(2);
	
}

void CCockFightDlg::OnBtnForegift() 
{
	// TODO: Add your control notification handler code here
	SendControlInfo(1);
}

void CCockFightDlg::OnBtnOpenone() 
{
	// TODO: Add your control notification handler code here
	SendControlInfo(2);
}

void CCockFightDlg::SendControlInfo(char chControl)
{
	CString strControl;

	strControl = 2;
	strControl += chControl;

	switch(chControl)
	{
		case	0:	strControl += m_strName;
					break;
	
		case	1:
		case	2:	
		case	3:	break;
	}
	strControl += '\0';
	if(m_bIsClient)
	{
		m_pClient->Send(strControl.GetBuffer(1),
				strControl.GetLength());
	}
	return;
}

void CCockFightDlg::SendToyInfo()
{

}

void CCockFightDlg::OnColumnclickListToyinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	MessageBox("dfl");
	*pResult = 0;
}
