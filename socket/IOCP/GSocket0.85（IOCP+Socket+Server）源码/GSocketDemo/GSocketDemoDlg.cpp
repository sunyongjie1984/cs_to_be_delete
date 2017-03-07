// GSocketDemoDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "GSockInfo.h"
#include "GSocketDemo.h"
#include "GSocketDemoDlg.h"

#include "..\GLog.h"
#include "..\GMemory.h"
#include "..\GSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct _DATA_INFO
{
DWORD			dwSendBytes;
DWORD			dwRecvBytes;
DWORD			dwLong;
float			fSpeed;
DWORD			dwDataError;
DWORD			dwTickCountSend;
}DATA_INFO, *PDATA_INFO;

DATA_INFO DataInfo;

typedef struct _DATA_HEAD
{
DWORD			dwSender;
DWORD			dwSize;
DWORD			dwTickCount;
}DATA_HEAD, *PDATA_HEAD;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

int Random(int nNumber) 
{ 
	return (int)(nNumber/(float)RAND_MAX * rand());
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGSocketDemoDlg 对话框

BOOL OnTraversalClient(CGSocketDemoDlg* pDlg, const DWORD nIndex, const DWORD dwClientContext)
{
	PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);
	DWORD dwTickCount = GetTickCount();
	if(pDataInfo && (GHndDat_GetState(dwClientContext) == GHND_STATE_CONNECTED) && (dwTickCount - pDataInfo->dwTickCountSend > pDlg->m_dwSendSpace))
	{
		pDataInfo->dwTickCountSend = dwTickCount;
		PGIO_BUF pBuf = GIoDat_AllocGBuf();
		if(pBuf)
		{
			PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);
			PDATA_HEAD(pBuf)->dwSender = DWORD(pDataInfo);
			PDATA_HEAD(pBuf)->dwTickCount = GetTickCount();
			PDATA_HEAD(pBuf)->dwSize = pDlg->m_dwPackSize;
			DWORD i;
			for(i = sizeof(DATA_HEAD); i < pDlg->m_dwPackSize; i++)
				*(char *)(pBuf + i) = (char)i;
			GCommProt_PostSendGBuf(dwClientContext, pBuf, pDlg->m_dwPackSize);
		}
	}
	return(TRUE);
}

DWORD WINAPI ThreadSend(CGSocketDemoDlg* pDlg)
{
	while(!pDlg->m_bShutdownSend)
	{
		Sleep(1);
		GTcpClt_TraversalClient((DWORD)pDlg, 0, GTcpClt_GetClientCount(), (PFN_ON_GSOCK_TRAVERSAL)&OnTraversalClient);
	}
	pDlg->m_bShutdownSend = FALSE;
	return(0);
}

DWORD WINAPI ThreadDisconnect(CGSocketDemoDlg* pDlg)
{
	while(1)
	{
		Sleep(1000);
		if(pDlg->m_bRandoDisconnect)
		{
			int nIndex = pDlg->m_lstInfo.GetItemCount();
			if(nIndex)
			{
				nIndex = Random(nIndex * 2);
				if(nIndex < pDlg->m_lstInfo.GetItemCount())
				{
					GTcpClt_DisconnectClient((DWORD)(pDlg->m_lstInfo.GetItemData(nIndex)));
				}
			}
		}
	}
	return(0);
}


CGSocketDemoDlg::CGSocketDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGSocketDemoDlg::IDD, pParent)
	, m_dwGMemPageSize(0)
	, m_bCloseMtu(FALSE)
	, m_dwConnectionCount(0)
{
	char szIp[30];

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_dwPostRecvNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_nSocketBufSize = 8192;
	m_dwWorkerThreadNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_dwConcurrentThreadNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_dwPostAcceptNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_dwSendLoop = 0;
	GSock_GetLocalNetIp(szIp, 28, FALSE);
	m_strListenIp.Format(_T("%s"), szIp);
	m_dwListenPort = 20020;
	m_dwSendSpace = 100;
	m_dwPackSize = GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16);
	m_dwHeartbeat = 50;
	m_dwConnectNumber = 1;
	m_strLocalIp.Format(_T("%s"), szIp);
	m_dwLocalPort = 20030;
	m_strRemoteIp.Format(_T("%s"), szIp);
	m_dwRemotePort = 20020;
	m_dwSendBytes = 0;
	m_dwRecvBytes = 0;
	m_dwByteTotal = 0;
	m_dwLong = 0;
	m_fBeat = 0;
	m_bCloseMtu = TRUE;
	m_bZeroAccept = FALSE;
	m_bZeroRecv = FALSE;
	m_bSendSelf = TRUE;
	m_bRandoDisconnect = FALSE;
	m_bShutdownSend = FALSE;

	m_dwGMemPageSize = GMem_GetPageSize();
	m_dwGMemTotal = GMem_GetTotalBytes();
	m_dwGBufSize = GIoDat_GetGBufSize();
	m_dwIoDataTotal = GIoDat_GetTotal();
	m_dwHndDataTotal = GHndDat_GetTotal();
	m_dwWorkerThreadNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_dwConcurrentThreadNumber = GWkrThrd_GetWorkerThreadNumberDef();
	m_dwAcceptOvertime = GSock_GetTimeAcceptOvertime();
	m_dwIdleOvertime = GSock_GetTimeIdleOvertime();
	m_dwMaxConnection = GSock_GetMaxNumberConnection();
	m_dwHeartbeat = 50;

	ZeroMemory(&DataInfo, sizeof(DATA_INFO));
	DataInfo.dwLong = GetTickCount();
}

void CGSocketDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GEDIT_1, m_edtGMemPageSize);
	DDX_Text(pDX, IDC_GEDIT_1, m_dwGMemPageSize);
	DDX_Control(pDX, IDC_GEDIT_2, m_edtGMemTotal);
	DDX_Text(pDX, IDC_GEDIT_2, m_dwGMemTotal);
	DDX_Control(pDX, IDC_GEDIT_3, m_edtGBufSize);
	DDX_Text(pDX, IDC_GEDIT_3, m_dwGBufSize);
	DDX_Control(pDX, IDC_GEDIT_4, m_edtIoDataTotal);
	DDX_Text(pDX, IDC_GEDIT_4, m_dwIoDataTotal);
	DDX_Control(pDX, IDC_GEDIT_5, m_edtHndDataTotal);
	DDX_Text(pDX, IDC_GEDIT_5, m_dwHndDataTotal);
	DDX_Control(pDX, IDC_GEDIT_6, m_edtPostRecvNumber);
	DDX_Text(pDX, IDC_GEDIT_6, m_dwPostRecvNumber);
	DDX_Control(pDX, IDC_GEDIT_7, m_edtSocketBufSize);
	DDX_Text(pDX, IDC_GEDIT_7, m_nSocketBufSize);
	DDX_Control(pDX, IDC_GEDIT_8, m_edtWorkerThreadNumber);
	DDX_Text(pDX, IDC_GEDIT_8, m_dwWorkerThreadNumber);
	DDX_Control(pDX, IDC_GEDIT_9, m_edtConcurrentThreadNumber);
	DDX_Text(pDX, IDC_GEDIT_9, m_dwConcurrentThreadNumber);
	DDX_Control(pDX, IDC_GEDIT_10, m_edtAcceptOvertime);
	DDX_Text(pDX, IDC_GEDIT_10, m_dwAcceptOvertime);
	DDX_Control(pDX, IDC_GEDIT_11, m_edtIdleOvertime);
	DDX_Text(pDX, IDC_GEDIT_11, m_dwIdleOvertime);
	DDX_Control(pDX, IDC_GEDIT_12, m_edtMaxConnection);
	DDX_Text(pDX, IDC_GEDIT_12, m_dwMaxConnection);
	DDX_Control(pDX, IDC_GEDIT_13, m_edtPostAcceptNumber);
	DDX_Text(pDX, IDC_GEDIT_13, m_dwPostAcceptNumber);
	DDX_Control(pDX, IDC_GEDIT_14, m_edtSendLoop);
	DDX_Text(pDX, IDC_GEDIT_14, m_dwSendLoop);
	DDX_Control(pDX, IDC_GEDIT_15, m_edtListenIp);
	DDX_Text(pDX, IDC_GEDIT_15, m_strListenIp);
	DDX_Control(pDX, IDC_GEDIT_16, m_edtListenPort);
	DDX_Text(pDX, IDC_GEDIT_16, m_dwListenPort);
	DDX_Control(pDX, IDC_GEDIT_17, m_edtSendSpace);
	DDX_Text(pDX, IDC_GEDIT_17, m_dwSendSpace);
	DDX_Control(pDX, IDC_GEDIT_18, m_edtPackSize);
	DDX_Text(pDX, IDC_GEDIT_18, m_dwPackSize);
	DDX_Control(pDX, IDC_GEDIT_19, m_edtHeartbeat);
	DDX_Text(pDX, IDC_GEDIT_19, m_dwHeartbeat);
	DDX_Control(pDX, IDC_GEDIT_20, m_edtConnectNumber);
	DDX_Text(pDX, IDC_GEDIT_20, m_dwConnectNumber);
	DDX_Control(pDX, IDC_GEDIT_21, m_edtLocalIp);
	DDX_Text(pDX, IDC_GEDIT_21, m_strLocalIp);
	DDX_Control(pDX, IDC_GEDIT_22, m_edtLocalPort);
	DDX_Text(pDX, IDC_GEDIT_22, m_dwLocalPort);
	DDX_Control(pDX, IDC_GEDIT_23, m_edtRemoteIp);
	DDX_Text(pDX, IDC_GEDIT_23, m_strRemoteIp);
	DDX_Control(pDX, IDC_GEDIT_24, m_edtRemotePort);
	DDX_Text(pDX, IDC_GEDIT_24, m_dwRemotePort);
	DDX_Control(pDX, IDC_GEDIT_25, m_edtSendBytes);
	DDX_Text(pDX, IDC_GEDIT_25, m_dwSendBytes);
	DDX_Control(pDX, IDC_GEDIT_26, m_edtRecvBytes);
	DDX_Text(pDX, IDC_GEDIT_26, m_dwRecvBytes);
	DDX_Control(pDX, IDC_GEDIT_27, m_edtByteTotal);
	DDX_Text(pDX, IDC_GEDIT_27, m_dwByteTotal);
	DDX_Control(pDX, IDC_GEDIT_28, m_edtLong);
	DDX_Text(pDX, IDC_GEDIT_28, m_dwLong);
	DDX_Control(pDX, IDC_GEDIT_29, m_edtBeat);
	DDX_Text(pDX, IDC_GEDIT_29, m_fBeat);

	DDX_Control(pDX, IDC_CHECK1, m_bnCloseMtu);
	DDX_Check(pDX, IDC_CHECK1, m_bCloseMtu);
	DDX_Control(pDX, IDC_CHECK2, m_bnZeroAccept);
	DDX_Check(pDX, IDC_CHECK2, m_bZeroAccept);
	DDX_Control(pDX, IDC_CHECK3, m_bnZeroRecv);
	DDX_Check(pDX, IDC_CHECK3, m_bZeroRecv);
	DDX_Control(pDX, IDC_CHECK4, m_bnSendSelf);
	DDX_Check(pDX, IDC_CHECK4, m_bSendSelf);
	DDX_Control(pDX, IDC_CHECK5, m_bnRandoDisconnect);
	DDX_Check(pDX, IDC_CHECK5, m_bRandoDisconnect);

	DDX_Control(pDX, IDC_BN_TCP_LISTEN, m_bnTcpListen);
	DDX_Control(pDX, IDC_BN_UDP_LISTEN, m_bnUdpListen);
	DDX_Control(pDX, IDC_BN_TCP_CONNECT, m_bnTcpConnect);
	DDX_Control(pDX, IDC_BN_UDP_CONNECT, m_bnUdpConnect);
	DDX_Control(pDX, IDC_BN_SERVICE, m_bnService);
	DDX_Control(pDX, IDC_GLIST3, m_lstInfo);
	DDX_Text(pDX, IDC_GEDIT_WAIT_ACCEPT3, m_dwConnectionCount);
}

BEGIN_MESSAGE_MAP(CGSocketDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGSocketDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGSocketDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CGSocketDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK4, &CGSocketDemoDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CGSocketDemoDlg::OnBnClickedCheck4)
	ON_EN_CHANGE(IDC_GEDIT_17, &CGSocketDemoDlg::OnEnChangeGedit17)
	ON_EN_CHANGE(IDC_GEDIT_14, &CGSocketDemoDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_GEDIT_18, &CGSocketDemoDlg::OnBnClickedCheck4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BN_SERVICE, &CGSocketDemoDlg::OnBnClickedBnService)
	ON_BN_CLICKED(IDC_BN_TCP_LISTEN, &CGSocketDemoDlg::OnBnClickedBnTcpListen)
	ON_BN_CLICKED(IDC_BN_TCP_CONNECT, &CGSocketDemoDlg::OnBnClickedBnTcpConnect)
	ON_BN_CLICKED(IDC_BUTTON6, &CGSocketDemoDlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_GEDIT_18, &CGSocketDemoDlg::OnEnChangeGedit18)
	ON_BN_CLICKED(IDC_BUTTON3, &CGSocketDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGSocketDemoDlg 消息处理程序

void SetListCtrlStyleDemo(CListCtrl* pLstCtrl)
{
	//获得原有风格
	DWORD dwStyle = GetWindowLong(pLstCtrl->m_hWnd, GWL_STYLE); 
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);

	//设置新风格
    SetWindowLong(pLstCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);

	//设置扩展风格
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(pLstCtrl->m_hWnd, styles, styles );
}

BOOL CGSocketDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetListCtrlStyleDemo(&m_lstInfo);

	LV_COLUMN col;

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("序");
	col.cx = 25;
	m_lstInfo.InsertColumn(0, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("类型");
	col.cx = 60;
	m_lstInfo.InsertColumn(1, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("状态");
	col.cx = 50;
	m_lstInfo.InsertColumn(2, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("远程");
	col.cx = 50;
	m_lstInfo.InsertColumn(3, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("发送");
	col.cx = 70;
	m_lstInfo.InsertColumn(4, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("接收");
	col.cx = 70;
	m_lstInfo.InsertColumn(5, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("收发");
	col.cx = 70;
	m_lstInfo.InsertColumn(6, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("双程耗时");
	col.cx = 70;
	m_lstInfo.InsertColumn(7, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("双程速率");
	col.cx = 70;
	m_lstInfo.InsertColumn(8, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("错误");
	col.cx = 60;
	m_lstInfo.InsertColumn(9, &col);

	srand((ULONG)(time(NULL)));

	SetTimer(10000, 1000, NULL);

	DWORD dwThreadId;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadDisconnect, this, 0, &dwThreadId));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGSocketDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGSocketDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGSocketDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGSocketDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CGSocketDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(10000);
	BOOL bIsSend = GTcpClt_GetClientCount() > 0;
	m_bShutdownSend = TRUE;		
	if(bIsSend)
		while(m_bShutdownSend)
			Sleep(1);
	if(GSock_IsActive())
	{
		GInfo_ClearList();
		GSock_StopService();
	}
	OnCancel();
}

void CGSocketDemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GMem_Create();
	GInfo_Show(this);
}

void CGSocketDemoDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CGSocketDemoDlg::OnEnChangeGedit17()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/*if(GTcpClt_GetClientCount())
	{
		UpdateData(TRUE);
		KillTimer(10001);
		SetTimer(10001, m_dwSendSpace, NULL);
	}*/
}

void CGSocketDemoDlg::EnabledCtrls(BOOL bIsActive)
{
	m_edtGMemPageSize.EnableWindow(!bIsActive);
	m_edtGMemTotal.EnableWindow(!bIsActive);
	m_edtGBufSize.EnableWindow(!bIsActive);
	m_edtIoDataTotal.EnableWindow(!bIsActive);
	m_edtHndDataTotal.EnableWindow(!bIsActive);
	m_edtPostRecvNumber.EnableWindow(!bIsActive);
	m_edtSocketBufSize.EnableWindow(!bIsActive);
	m_edtWorkerThreadNumber.EnableWindow(!bIsActive);
	m_edtConcurrentThreadNumber.EnableWindow(!bIsActive);
	m_edtAcceptOvertime.EnableWindow(!bIsActive);
	m_edtIdleOvertime.EnableWindow(!bIsActive);
	m_edtMaxConnection.EnableWindow(!bIsActive);
	m_edtPostAcceptNumber.EnableWindow(!bIsActive);
	m_edtHeartbeat.EnableWindow(!bIsActive);

	m_bnCloseMtu.EnableWindow(!bIsActive);
	m_bnZeroAccept.EnableWindow(!bIsActive);
	m_bnZeroRecv.EnableWindow(!bIsActive);
	m_bnTcpListen.EnableWindow(bIsActive);
	m_bnUdpListen.EnableWindow(bIsActive);
	m_bnTcpConnect.EnableWindow(bIsActive);
	m_bnUdpConnect.EnableWindow(bIsActive);
}


void CGSocketDemoDlg::GetGSocketInfo(void)
{
	m_dwGMemPageSize = GMem_GetPageSize();
	m_dwGMemTotal = GMem_GetTotalBytes();
	m_dwGBufSize = GIoDat_GetGBufSize();
	m_dwIoDataTotal = GIoDat_GetTotal();
	m_dwHndDataTotal = GHndDat_GetTotal();
	m_dwWorkerThreadNumber = GWkrThrd_GetWorkerThreadNumber();
	m_dwConcurrentThreadNumber = GWkrThrd_GetConcurrentThreadNumber();
	m_dwAcceptOvertime = GSock_GetTimeAcceptOvertime();
	m_dwIdleOvertime = GSock_GetTimeIdleOvertime();
	m_dwMaxConnection = GSock_GetMaxNumberConnection();
	m_dwHeartbeat = 50;
	UpdateData(FALSE);
}

void CGSocketDemoDlg::OnBnClickedBnService()
{
	// TODO: 在此添加控件通知处理程序代码
	if(GSock_IsActive())
	{
		//KillTimer(10001);		
		m_bShutdownSend = TRUE;
		m_lstInfo.DeleteAllItems();
		GInfo_ClearList();
		GSock_StopService();
		m_dwListenPort = 20020;
		UpdateData(FALSE);
		m_bnService.SetWindowText(_T("开始服务"));
		m_bnTcpListen.SetWindowText(_T("TCP监听(尚未监听)"));
		m_bnUdpListen.SetWindowText(_T("UDP监听"));
		OnBnClickedButton6();
		EnabledCtrls(FALSE);
	}else
	{		
		UpdateData(TRUE);
		if(m_dwPackSize > GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16))
			m_dwPackSize = GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16);

		GMem_SetPageSize(m_dwGMemPageSize);
		GMem_SetTotalBytes(m_dwGMemTotal);
		GIoDat_SetGBufSize(m_dwGBufSize);
		GIoDat_SetTotal(m_dwIoDataTotal);
		GHndDat_SetTotal(m_dwHndDataTotal);
		GSock_SetNumberPostRecv(m_dwPostRecvNumber);
		GSock_SetMtuNodelay(m_bCloseMtu);
		GSock_SetZeroByteRecv(m_bZeroRecv);
		GSock_SetZeroByteAccept(m_bZeroAccept);
		GSock_SetSocketSendBufSize(m_nSocketBufSize);
		GSock_SetSocketRecvBufSize(m_nSocketBufSize);
		GWkrThrd_SetWorkerThreadNumber(m_dwWorkerThreadNumber);
		GWkrThrd_SetConcurrentThreadNumber(m_dwConcurrentThreadNumber);
		GSock_SetTimeAcceptOvertime(m_dwAcceptOvertime);
		GSock_SetTimeIdleOvertime(m_dwIdleOvertime);
		GSock_SetMaxNumberConnection(m_dwMaxConnection);
		GSock_SetNumberPostAccept(m_dwPostAcceptNumber);

		GSock_SetTimeHeartbeat(m_dwHeartbeat);

		GSock_SetOnConnectProcTcpSvr(&OnConnectSvr);
		GSock_SetOnDisconnectProcSvr(&OnDisconnectSvr);
		GSock_SetOnReceiveProcSvr(&OnReceiveSvr);
		GSock_SetOnSendedProcSvr(&OnSendedSvr);
		GSock_SetOnSendErrorProcSvr(&OnSendErrorSvr);
		GSock_SetOnIdleOvertimeProc(&OnIdleOvertime);
		GSock_SetOnConnectionOverflowProc(&OnConnectionOverflow);

		GSock_SetOnConnectProcClt(&OnConnectClt);
		GSock_SetOnConnectErrorProc(&OnConnectError);
		GSock_SetOnDisconnectProcClt(&OnDisconnectClt);
		GSock_SetOnCreateClientProc(&OnCreateClient);
		GSock_SetOnDestroyClientProc(&OnDestroyClient);
		GSock_SetOnReceiveProcClt(&OnReceiveClt);
		GSock_SetOnSendedProcClt(&OnSendedClt);
		GSock_SetOnSendErrorProcClt(&OnSendErrorClt);
		GSock_SetOnHeartbeatProc(&OnHeartbeat);

		GSock_StartService();
		if(GSock_IsActive())
		{
			m_bnService.SetWindowText(_T("停止服务"));
			EnabledCtrls(TRUE);
		}else
			MessageBox(_T("GSocket启动失败，请参阅日志文件：GLog.ini"));
		GetGSocketInfo();
	}
}

void CGSocketDemoDlg::OnBnClickedBnTcpListen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwListenerId = GTcpSvr_CreateListen((char*)m_strListenIp.GetBuffer(), m_dwListenPort, this);
	if(dwListenerId)
	{
		m_dwListenPort++;
		UpdateData(FALSE);
		GInfo_OnAddListener(dwListenerId);
		CString str;
		str.Format(_T("TCP监听(%d)"), GTcpSvr_GetListenerCount());
		m_bnTcpListen.SetWindowText(str);
	}else
		MessageBox(_T("创建监听失败，请参阅日志文件：GLog.ini"));
}

void CGSocketDemoDlg::OnConnectSvr(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
	GInfo_OnConnect(dwClientContext);
	if(dwBytes)
		OnReceiveSvr(dwClientContext, pBuf, dwBytes);
}

void CGSocketDemoDlg::OnDisconnectSvr(const DWORD dwClientContext)
{
	GInfo_OnDisconnect(dwClientContext);
}

void CGSocketDemoDlg::OnReceiveSvr(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
	if(!((CGSocketDemoDlg*)GHndDat_GetOwner((DWORD)GHndDat_GetOwner(dwClientContext)))->m_bSendSelf)
		return;
	
	int i = ((CGSocketDemoDlg*)GHndDat_GetOwner((DWORD)GHndDat_GetOwner(dwClientContext)))->m_dwSendLoop;
	while(i)
		i--;

	GCommProt_PostSendBuf(dwClientContext, (char*)pBuf, dwBytes);
}

void CGSocketDemoDlg::OnReceiveErrorSvr(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnSendedSvr(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
}

void CGSocketDemoDlg::OnSendErrorSvr(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
}

void CGSocketDemoDlg::OnIdleOvertime(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnConnectionOverflow(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnHeartbeat(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnConnectError(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnCreateClient(const DWORD dwClientContext)
{
	PDATA_INFO pDataInfo = new DATA_INFO;
	ZeroMemory(pDataInfo, sizeof(DATA_INFO));
	GHndDat_SetData(dwClientContext, pDataInfo);
	GInfo_OnConnect(dwClientContext);
}

void CGSocketDemoDlg::OnDestroyClient(const DWORD dwClientContext)
{
	GInfo_OnDisconnect(dwClientContext);
	PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);
	GHndDat_SetData(dwClientContext, NULL);
	delete pDataInfo;
}

void CGSocketDemoDlg::OnConnectClt(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{

}

void CGSocketDemoDlg::OnDisconnectClt(const DWORD dwClientContext)
{
	
}

void CGSocketDemoDlg::OnReceiveClt(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
	PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);
	if(!pDataInfo)
		return;
	BOOL bIsError = FALSE;

	InterlockedExchangeAdd((volatile LONG*)&pDataInfo->dwRecvBytes, dwBytes);
	InterlockedExchangeAdd((volatile LONG*)&DataInfo.dwRecvBytes, dwBytes);

	if((PDATA_HEAD(pBuf)->dwSender != (DWORD)pDataInfo) || (PDATA_HEAD(pBuf)->dwSize != dwBytes))
	{
		InterlockedIncrement((volatile LONG*)&pDataInfo->dwDataError);
		bIsError = TRUE;
	}else
	{
		DWORD i;
		for(i = sizeof(DATA_HEAD); i < dwBytes; i++)
			if(*(char *)(pBuf + i) != (char)i)
			{
				InterlockedIncrement((volatile LONG*)&pDataInfo->dwDataError);
				bIsError = TRUE;
				break;
			}
	}
	if(!bIsError)
	{
		pDataInfo->dwLong = GetTickCount() - ((PDATA_HEAD)pBuf)->dwTickCount;
		
		if(pDataInfo->dwLong)
			pDataInfo->fSpeed = float(PDATA_HEAD(pBuf)->dwSize) * 2 / pDataInfo->dwLong;
		else
			pDataInfo->fSpeed = float(PDATA_HEAD(pBuf)->dwSize) * 2;
	}
}

void CGSocketDemoDlg::OnReceiveErrorClt(const DWORD dwClientContext)
{
}

void CGSocketDemoDlg::OnSendedClt(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
	PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);
	if(!pDataInfo)
		return;
	InterlockedExchangeAdd((volatile LONG*)&pDataInfo->dwSendBytes, dwBytes);
	InterlockedExchangeAdd((volatile LONG*)&DataInfo.dwSendBytes, dwBytes);
}

void CGSocketDemoDlg::OnSendErrorClt(const DWORD dwClientContext, const char* pBuf, const DWORD dwBytes)
{
}

void CGSocketDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(10000 == nIDEvent)
	{
		m_dwSendBytes = DataInfo.dwSendBytes;
		m_dwRecvBytes = DataInfo.dwRecvBytes;
		m_dwByteTotal = m_dwSendBytes + m_dwRecvBytes;
		m_dwLong = GetTickCount() - DataInfo.dwLong;
		m_fBeat = (float)m_dwByteTotal / (float)m_dwLong;
		CString str;

		str.Format(_T("%d"), m_dwSendBytes);
		m_edtSendBytes.SetWindowText(str);
		str.Format(_T("%d"), m_dwRecvBytes);
		m_edtRecvBytes.SetWindowText(str);
		str.Format(_T("%d"), m_dwByteTotal);
		m_edtByteTotal.SetWindowText(str);
		str.Format(_T("%d"), m_dwLong);
		m_edtLong.SetWindowText(str);
		str.Format(_T("%f"), m_fBeat);
		m_edtBeat.SetWindowText(str);

		LV_ITEM lvitem;
		int i, nEnd;

		i = m_lstInfo.GetTopIndex();
		nEnd = i + 7;
		if(nEnd > m_lstInfo.GetItemCount())
			nEnd = m_lstInfo.GetItemCount();
		lvitem.state = 0;
		lvitem.stateMask = 0;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
		while(i < nEnd)
		{
			lvitem.iItem = i;
			lvitem.iSubItem = 2;
			DWORD dwClientContext = (DWORD)m_lstInfo.GetItemData(i);
			switch(GHndDat_GetState(dwClientContext))
			{
				case GHND_STATE_CONNECTED:
				{
					lvitem.pszText = _T("在线");
					break;
				}
				case GHND_STATE_CONNECTING:
				{
					lvitem.pszText = _T("连接中");
					break;
				}
				default:
					lvitem.pszText = _T("断线");
			}
			m_lstInfo.SetItem(&lvitem);

			PDATA_INFO pDataInfo = (PDATA_INFO)GHndDat_GetData(dwClientContext);

			lvitem.iSubItem = 4;
			str.Format(_T("%d"), pDataInfo->dwSendBytes);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;
			m_lstInfo.SetItem(&lvitem);

			lvitem.iSubItem = 5;
			str.Format(_T("%d"), pDataInfo->dwRecvBytes);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;
			m_lstInfo.SetItem(&lvitem);

			lvitem.iSubItem = 6;
			str.Format(_T("%d"), pDataInfo->dwRecvBytes + pDataInfo->dwSendBytes);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;
			m_lstInfo.SetItem(&lvitem);

			lvitem.iSubItem = 7;
			str.Format(_T("%d"), pDataInfo->dwLong);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;
			m_lstInfo.SetItem(&lvitem);

			lvitem.iSubItem = 8;
			str.Format(_T("%f"), pDataInfo->fSpeed);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;

			m_lstInfo.SetItem(&lvitem);

			lvitem.iSubItem = 9;
			str.Format(_T("%d"), pDataInfo->dwDataError);
			lvitem.pszText = (LPTSTR)(LPCTSTR)str;
			m_lstInfo.SetItem(&lvitem);
			i++;
		}

		/*if(m_bRandoDisconnect)
		{
			int nIndex = m_lstInfo.GetItemCount();
			if(nIndex)
			{
				nIndex = Random(nIndex * 2);
				if(nIndex < m_lstInfo.GetItemCount())
				{
					GTcpClt_DisconnectClient((DWORD)m_lstInfo.GetItemData(nIndex));
				}
			}
		}*/

		return;
	}
	CDialog::OnTimer(nIDEvent);
}

void CGSocketDemoDlg::DeleteClient(DWORD dwClientContext)
{
	int i, nIndex = -1;

	for(i = 0; i <= m_lstInfo.GetItemCount() - 1; i++)
	{
		if((DWORD)m_lstInfo.GetItemData(i) == dwClientContext)
		{
			nIndex = i;
			m_lstInfo.DeleteItem(nIndex);
			break;
		}
	}

	if(-1 == nIndex)
		return;

	LV_ITEM lvitem;
	CString str;

	lvitem.state = 0;
	lvitem.stateMask = 0;
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;

	for(i = nIndex; i <= m_lstInfo.GetItemCount() - 1; i++)
	{
		lvitem.iItem = i;
		lvitem.iSubItem = 0;
		str.Format(_T("%d"), i + 1);
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstInfo.SetItem(&lvitem);
	}
	m_dwConnectionCount = m_lstInfo.GetItemCount();
	UpdateData(FALSE);
}

void CGSocketDemoDlg::AddClient(DWORD dwClientContext)
{
	LV_ITEM lvitem;
	CString str;
	char szIp[30];
	int nIndex;

	nIndex = m_lstInfo.GetItemCount();
	if(0 > nIndex)
		nIndex = 0;
	
	lvitem.state = 0;
	lvitem.stateMask = 0;

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 0;
	str.Format(_T("%d"), nIndex + 1);
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstInfo.InsertItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 1;
	GHND_TYPE HndType = GHndDat_GetType(dwClientContext);
	switch(HndType)
	{
		case GHND_TYPE_TCP_SVR_CLIENT:
			lvitem.pszText = _T("TCP服务");
		break;
		case GHND_TYPE_TCP_CLT_CLIENT:
			lvitem.pszText = _T("TCP客户");
		break;
		case GHND_TYPE_UDP_SVR_CLIENT:
			lvitem.pszText = _T("UDP服务");
		break;
		default:
			lvitem.pszText = _T("UDP客户");
	}
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 2;
	switch(GHndDat_GetState(dwClientContext))
	{
		case GHND_STATE_CONNECTED:
		{
			lvitem.pszText = _T("在线");
			break;
		}
		case GHND_STATE_CONNECTING:
		{
			lvitem.pszText = _T("连接中");
			break;
		}
		default:
			lvitem.pszText = _T("断线");
	}
	m_lstInfo.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 3;
	GSock_AddrToIp(szIp, 28, GHndDat_GetAddr(dwClientContext));
	str.Format(_T("%s:%d"), szIp, GHndDat_GetPort(dwClientContext));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 4;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 5;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 6;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 7;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 8;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 9;
	lvitem.pszText = _T("0");
	m_lstInfo.SetItem(&lvitem);

	m_lstInfo.SetItemData(nIndex, (DWORD_PTR)dwClientContext);

	m_dwConnectionCount = m_lstInfo.GetItemCount();
	UpdateData(FALSE);
}

void CGSocketDemoDlg::OnBnClickedBnTcpConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD i, dwClient;

	UpdateData(TRUE);
	if(!GTcpClt_GetClientCount())
	{
		DataInfo.dwLong = GetTickCount();
		//SetTimer(10001, m_dwSendSpace, NULL);
		DWORD dwThreadId;
		m_bShutdownSend = FALSE;
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadSend, this, 0, &dwThreadId));
	}
	if(m_dwPackSize > GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16))
		m_dwPackSize = GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16);

	UpdateData(TRUE);
	for(i = 0; i < m_dwConnectNumber; i++)
	{
		dwClient = GTcpClt_CreateClient((char *)m_strRemoteIp.GetBuffer(), m_dwRemotePort, (char *)m_strLocalIp.GetBuffer(), this);
		if(dwClient)
			AddClient(dwClient);
		else
			break;
	}
}

void CGSocketDemoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	ZeroMemory(&DataInfo, sizeof(DATA_INFO));
	DataInfo.dwLong = GetTickCount();
}

void CGSocketDemoDlg::OnEnChangeGedit18()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_dwPackSize > GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16))
		m_dwPackSize = GIoDat_GetGBufSize() - 2 * (sizeof(SOCKADDR_IN) + 16);
}

void CGSocketDemoDlg::OnBnClickedButton3()
{
	if(0 < m_lstInfo.GetItemCount())
	{
		GTcpClt_DisconnectClient((DWORD)m_lstInfo.GetItemData(0));
	}
}
