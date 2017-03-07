// GSockInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "GSocketDemo.h"
#include "GSockInfo.h"

#include "..\GMemory.h"
#include "..\GSocket.h"

#define GMSG_ADD_LISTENER			(WM_USER + 101)
#define GMSG_CONNECT				(WM_USER + 102)
#define GMSG_DISCONNECT				(WM_USER + 103)
#define GMSG_CLEAR_LIST				(WM_USER + 104)

CGSockInfo *pGSocketInfo = NULL;

void GInfo_Show(CWnd* pParent)
{
	if(pGSocketInfo == NULL)
	{
		pGSocketInfo = new CGSockInfo;
		pGSocketInfo->Create(IDD_GSOCK_INFO_DIALOG, pParent);
		pGSocketInfo->ShowWindow(SW_SHOW);
	}
}

void GInfo_OnAddListener(DWORD dwListener)
{
	if(pGSocketInfo)
		PostMessage(pGSocketInfo->m_hWnd, GMSG_ADD_LISTENER, dwListener, 0);
}

void GInfo_OnConnect(DWORD dwClientContext)
{
	if(pGSocketInfo)
		PostMessage(pGSocketInfo->m_hWnd, GMSG_CONNECT, dwClientContext, 0);
}

void GInfo_OnDisconnect(DWORD dwClientContext)
{
	if(pGSocketInfo)
		PostMessage(pGSocketInfo->m_hWnd, GMSG_DISCONNECT, dwClientContext, 0);
}

void GInfo_ClearList(void)
{
	if(pGSocketInfo)
		SendMessage(pGSocketInfo->m_hWnd, GMSG_CLEAR_LIST, 0, 0);
}


// CGSockInfo 对话框

IMPLEMENT_DYNAMIC(CGSockInfo, CDialog)

CGSockInfo::CGSockInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CGSockInfo::IDD, pParent)
	, m_dwPhyAvail(0)
	, m_dwWaitAccept(0)
	, m_dwListItemCount(0)
	, m_dwThreadTotal(0)
{

}

CGSockInfo::~CGSockInfo()
{
	pGSocketInfo = NULL;
}

void CGSockInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GEDIT_PHY_AVAIL, m_dwPhyAvail);
	DDX_Text(pDX, IDC_GEDIT_PHY_FREE, m_fPhyFree);
	DDX_Text(pDX, IDC_GEDIT_PHY_PAGE_SIZE, m_dwPhyPageSize);
	DDX_Text(pDX, IDC_GEDIT_PHY_USED_PAGE, m_dwPhyUsedPage);
	DDX_Text(pDX, IDC_GEDIT_PHY_USED_BYTES, m_dwPhyUsedBytes);

	DDX_Text(pDX, IDC_GEDIT_GMEM_PAGE_SIZE, m_dwGMemPageSize);
	DDX_Text(pDX, IDC_GEDIT_GMEM_PAGE_NUMBER, m_dwGMemPageNumber);
	DDX_Text(pDX, IDC_GEDIT_GMEM_TOTAL, m_dwGMemTotal);
	DDX_Text(pDX, IDC_GEDIT_GMEM_USED, m_dwGMemUsed);
	DDX_Text(pDX, IDC_GEDIT_GMEM_USED_R, m_fGMemUsedR);

	DDX_Text(pDX, IDC_GEDIT_IODT_BYTES, m_dwIodtBytes);
	DDX_Text(pDX, IDC_GEDIT_GBUF_SIZE, m_dwGBufSize);
	DDX_Text(pDX, IDC_GEDIT_IODT_TOTAL, m_dwIodtTotal);
	DDX_Text(pDX, IDC_GEDIT_IODT_USED, m_dwIodtUsed);
	DDX_Text(pDX, IDC_GEDIT_IODT_USED_R, m_fIodtUsedR);

	DDX_Text(pDX, IDC_GEDIT_HDDT_BYTES, m_dwHddtBytes);
	DDX_Text(pDX, IDC_GEDIT_HDDT_SIZE, m_dwHddtSize);
	DDX_Text(pDX, IDC_GEDIT_HDDT_TOTAL, m_dwHddtTotal);
	DDX_Text(pDX, IDC_GEDIT_HDDT_USED, m_dwHddtUsed);
	DDX_Text(pDX, IDC_GEDIT_HDDT_USED_R, m_fHddtUsedR);

	DDX_Text(pDX, IDC_GEDIT_LISTENER, m_dwListener);
	DDX_Text(pDX, IDC_GEDIT_CLIENT, m_dwClient);
	DDX_Text(pDX, IDC_GEDIT_WORKER, m_dwWorker);
	DDX_Control(pDX, IDC_GLIST_LISTENER, m_lstListener);
	DDX_Control(pDX, IDC_GLIST_CLIENT, m_lstClient);
	DDX_Control(pDX, IDC_GLIST_WORKER, m_lstWorker);
	DDX_Text(pDX, IDC_GEDIT_WAIT_ACCEPT, m_dwWaitAccept);
	DDX_Text(pDX, IDC_GEDIT_WAIT_ACCEPT2, m_dwListItemCount);
	DDX_Text(pDX, IDC_GEDIT_WORKER2, m_dwThreadTotal);
}


BEGIN_MESSAGE_MAP(CGSockInfo, CDialog)
	ON_BN_CLICKED(IDOK, &CGSockInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGSockInfo::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGSockInfo 消息处理程序

void CGSockInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CGSockInfo::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnCancel();
	KillTimer(1000);
	DestroyWindow();
}

void CGSockInfo::PostNcDestroy()
{
     CDialog::PostNcDestroy();
     delete this;
}

void SetListCtrlStyle(CListCtrl* pLstCtrl)
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

void CGSockInfo::InitListCtrl(void)
{
	LV_COLUMN col;

	SetListCtrlStyle(&m_lstListener);
	
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("序号");
	col.cx = 40;
	m_lstListener.InsertColumn(0, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("IP地址");
	col.cx = 120;
	m_lstListener.InsertColumn(1, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("端口");
	col.cx = 50;
	m_lstListener.InsertColumn(2, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("链接");
	col.cx = 50;
	m_lstListener.InsertColumn(3, &col);

	SetListCtrlStyle(&m_lstWorker);
	
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("序号");
	col.cx = 40;
	m_lstWorker.InsertColumn(0, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("线程名");
	col.cx = 105;
	m_lstWorker.InsertColumn(1, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("状态");
	col.cx = 45;
	m_lstWorker.InsertColumn(2, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("活动计数");
	col.cx = 65;
	m_lstWorker.InsertColumn(3, &col);

	SetListCtrlStyle(&m_lstClient);
	
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("序号");
	col.cx = 40;
	m_lstClient.InsertColumn(0, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("类型");
	col.cx = 60;
	m_lstClient.InsertColumn(1, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("状态");
	col.cx = 50;
	m_lstClient.InsertColumn(2, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("本地IP");
	col.cx = 115;
	m_lstClient.InsertColumn(3, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("本地端口");
	col.cx = 65;
	m_lstClient.InsertColumn(4, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("远程IP");
	col.cx = 115;
	m_lstClient.InsertColumn(5, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("远程端口");
	col.cx = 65;
	m_lstClient.InsertColumn(6, &col);

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	col.pszText = _T("空闲");
	col.cx = 45;
	m_lstClient.InsertColumn(7, &col);
}

BOOL CGSockInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_brushRed.CreateSolidBrush(RGB(255, 0, 0));
	m_brushGreen.CreateSolidBrush(RGB(0, 255, 0));
	m_penGreen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	GetClientRect(&m_rect);
	m_rect.left += 10;
	m_rect.top += 10;
	m_rect.bottom = m_rect.top + 30;
	m_rect.right -= 10;

	InitListCtrl();
	GetInfo();
	GTcpSvr_TraversalListener((DWORD)this, (PFN_ON_GSOCK_TRAVERSAL)&OnTraversalListener);
	GTcpSvr_TraversalClient((DWORD)this, 0, GTcpSvr_GetClientCount(), (PFN_ON_GSOCK_TRAVERSAL)&OnTraversalClient);
	GTcpClt_TraversalClient((DWORD)this, 0, GTcpClt_GetClientCount(), (PFN_ON_GSOCK_TRAVERSAL)&OnTraversalClient);
	SetTimer(1000, 1000, NULL);

	return TRUE;
}

void CGSockInfo::OnTraversalGMem(CGSockInfo* pSockInfo, const void* pAddr, const DWORD dwSize, const BOOL bIsFree)
{
	float fWidth;
	fWidth = pSockInfo->m_fPixOfSize * dwSize;
	if(!bIsFree)
	{
		pSockInfo->m_fStartX += fWidth;
		return;
	}

	CClientDC *dc = pSockInfo->m_pdc;
	
	CBrush *brushSave;
	CPen *penSave;

	brushSave = dc->SelectObject(&(pSockInfo->m_brushGreen));
	penSave = dc->SelectObject(&pSockInfo->m_penGreen);
	dc->SetDCPenColor(RGB(0, 255, 0));

	dc->Rectangle(DWORD(pSockInfo->m_rect.left + pSockInfo->m_fStartX), pSockInfo->m_rect.top, DWORD(pSockInfo->m_rect.left + pSockInfo->m_fStartX + fWidth) - 2, pSockInfo->m_rect.bottom);
	pSockInfo->m_fStartX += fWidth;

	dc->SelectObject(&brushSave);
	dc->SelectObject(&penSave);
}

void CGSockInfo::OnPaint()
{
	CDialog::OnPaint();

	CClientDC dc(this);
	m_pdc = &dc;
	GetClientRect(&m_rect);
	m_rect.left += 10;
	m_rect.top += 10;
	m_rect.bottom = m_rect.top + 30;
	m_rect.right -= 10;
	CBrush *brushSave;

	brushSave = dc.SelectObject(&m_brushRed);
	dc.Rectangle(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	dc.SelectObject(&brushSave);
	
	m_dwWidth = (DWORD)m_rect.right - m_rect.left;
	m_fSizeOfPix = (float)GMem_GetTotalBytes() / m_dwWidth;
	m_fPixOfSize = (float)m_dwWidth / GMem_GetTotalBytes();
	m_rect.left += 1;
	m_rect.top += 1;
	m_rect.bottom -= 1;
	m_rect.right -= 1;
	m_fStartX = m_fPixOfSize * GMem_GetSysUsedBytes();

	GMem_Traversal((DWORD)this, (PFN_ON_GMEM_TRAVERSAL)&OnTraversalGMem);
}

BOOL CGSockInfo::OnTraversalThread(CGSockInfo* pSockInfo, const DWORD dwIndex, const DWORD dwGThreadId)
{
	LV_ITEM lvitem;
	CString str;

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = dwIndex;
	lvitem.iSubItem = 0;
	str.Format(_T("%d"), dwIndex + 1);
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	pSockInfo->m_lstWorker.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = dwIndex;
	lvitem.iSubItem = 1;
	str.Format(_T("%s:%d"), GThrd_GetName(dwGThreadId), GThrd_GetThreadId(dwGThreadId));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	pSockInfo->m_lstWorker.SetItem(&lvitem);
	
	lvitem.iItem = dwIndex;
	lvitem.iSubItem = 2;
	str.Format(_T("%d"), GThrd_GetState(dwGThreadId));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	pSockInfo->m_lstWorker.SetItem(&lvitem);

	lvitem.iItem = dwIndex;
	lvitem.iSubItem = 3;
	str.Format(_T("%d"), GThrd_GetRunCount(dwGThreadId));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	pSockInfo->m_lstWorker.SetItem(&lvitem);

	pSockInfo->m_lstWorker.SetItemData(dwIndex, (DWORD_PTR)dwGThreadId);
	return(TRUE);
}

BOOL CGSockInfo::OnTraversalListener(CGSockInfo* pSockInfo, const DWORD nIndex, const DWORD dwListenerId)
{
	pSockInfo->OnAddListener(dwListenerId);
	return(TRUE);
}

BOOL CGSockInfo::OnTraversalClient(CGSockInfo* pSockInfo, const DWORD nIndex, const DWORD dwClientContext)
{
	pSockInfo->OnConnect(dwClientContext);
	return(TRUE);
}

void CGSockInfo::GetInfo(void)
{
	InvalidateRect(&m_rect, FALSE);

	DWORD dwPhyTotal;
	m_dwPhyAvail = GMem_GetAvailPhyBytes(&dwPhyTotal);
	m_fPhyFree = (float)m_dwPhyAvail / dwPhyTotal * 100;
	m_dwPhyPageSize = GMem_GetPhyPageSize();
	m_dwPhyUsedPage = GMem_GetUsedPhyPageNumber();
	m_dwPhyUsedBytes = GMem_GetUsedPhyBytes();

	m_dwGMemPageSize = GMem_GetPageSize();
	m_dwGMemPageNumber = GMem_GetPageNumber();
	m_dwGMemTotal = GMem_GetTotalBytes();
	m_dwGMemUsed = GMem_GetUsedBytes();
	m_fGMemUsedR = (float)m_dwGMemUsed / (float)m_dwGMemTotal * 100;

	m_dwIodtBytes = GIoDat_GetMemBytes();
	m_dwGBufSize = GIoDat_GetGBufSize();
	m_dwIodtTotal = GIoDat_GetTotal();
	m_dwIodtUsed = GIoDat_GetUsed();
	m_fIodtUsedR = (float)m_dwIodtUsed / (float)m_dwIodtTotal * 100;

	m_dwHddtBytes = GHndDat_GetMemBytes();
	m_dwHddtSize = GHndDat_GetSize();
	m_dwHddtTotal = GHndDat_GetTotal();
	m_dwHddtUsed = GHndDat_GetUsed();
	m_fHddtUsedR = (float)m_dwHddtUsed / (float)m_dwHddtTotal * 100;

	m_dwListener = GTcpSvr_GetListenerCount();
	m_dwClient = GSock_GetClientCount();
	m_dwThreadTotal = GThrd_GetThreadCount();
	m_dwWorker = GWkrThrd_GetWorkerThreadNumber();
	m_dwWaitAccept = GTcpSvr_GetPendingAcceptCount();
	m_dwListItemCount = m_lstClient.GetItemCount();

	if(m_lstWorker.GetItemCount() != m_dwThreadTotal)
	{
		m_lstWorker.DeleteAllItems();
		GThrd_TraversalThread((DWORD)this, (PFN_ON_GSOCK_TRAVERSAL)&OnTraversalThread);
	}

	LV_ITEM lvitem;
	CString str;
	int i;
	int nEnd;

	lvitem.state = 0;
	lvitem.stateMask = 0;
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;

	i = m_lstListener.GetTopIndex();
	nEnd = i + 4;
	if(nEnd > m_lstListener.GetItemCount())
		nEnd = m_lstListener.GetItemCount();
	while(i < nEnd)
	{
		lvitem.iItem = i;
		lvitem.iSubItem = 3;
		str.Format(_T("%d"), GTcpSvr_GetListenerConnectCount((DWORD)m_lstListener.GetItemData(i)));
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstListener.SetItem(&lvitem);
		i++;
	}

	i = m_lstWorker.GetTopIndex();
	nEnd = i + 4;
	if(nEnd > m_lstWorker.GetItemCount())
		nEnd = m_lstWorker.GetItemCount();
	while(i < nEnd)
	{
		lvitem.iItem = i;
		lvitem.iSubItem = 2;
		str.Format(_T("%d"), GThrd_GetState((DWORD)m_lstWorker.GetItemData(i)));
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstWorker.SetItem(&lvitem);

		lvitem.iItem = i;
		lvitem.iSubItem = 3;
		str.Format(_T("%d"), GThrd_GetRunCount((DWORD)m_lstWorker.GetItemData(i)));
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstWorker.SetItem(&lvitem);
		i++;
	}

	i = m_lstClient.GetTopIndex();
	nEnd = i + 4;
	if(nEnd > m_lstClient.GetItemCount())
		nEnd = m_lstClient.GetItemCount();
	while(i < nEnd)
	{
		lvitem.iItem = i;
		lvitem.iSubItem = 2;
		DWORD dwClientContext = (DWORD)m_lstClient.GetItemData(i);
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
		m_lstClient.SetItem(&lvitem);

		lvitem.iItem = i;
		lvitem.iSubItem = 7;
		str.Format(_T("%d"), GetTickCount() - GHndDat_GetTickCountAcitve(dwClientContext));
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstClient.SetItem(&lvitem);
		i++;
	}

	UpdateData(FALSE);
}

void CGSockInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetInfo();

	CDialog::OnTimer(nIDEvent);
}

void CGSockInfo::OnAddListener(DWORD dwListener)
{
	LV_ITEM lvitem;
	CString str;
	int nIndex;
	char szIp[30];

	nIndex = m_lstListener.GetItemCount();
	if(0 > nIndex)
		nIndex = 0;

	lvitem.state = 0;
	lvitem.stateMask = 0;

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 0;
	str.Format(_T("%d"), nIndex + 1);
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstListener.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 1;
	GSock_AddrToIp(szIp, 28, GHndDat_GetAddr(dwListener));
	lvitem.pszText = szIp;
	m_lstListener.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 2;
	str.Format(_T("%d"), GHndDat_GetPort(dwListener));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstListener.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 3;
	str.Format(_T("%d"), GTcpSvr_GetListenerConnectCount(dwListener));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstListener.SetItem(&lvitem);

	m_lstListener.SetItemData(nIndex, (DWORD_PTR)dwListener);
}

void CGSockInfo::OnConnect(DWORD dwClientContext)
{
	LV_ITEM lvitem;
	CString str;
	char szIp[30];
	int nIndex;

	nIndex = m_lstClient.GetItemCount();
	if(0 > nIndex)
		nIndex = 0;
	
	lvitem.state = 0;
	lvitem.stateMask = 0;

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 0;
	str.Format(_T("%d"), nIndex + 1);
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstClient.InsertItem(&lvitem);

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
	m_lstClient.SetItem(&lvitem);

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
	m_lstClient.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 3;
	if((GHND_TYPE_TCP_SVR_CLIENT == HndType) || (GHND_TYPE_UDP_SVR_CLIENT == HndType))
	{
		GSock_AddrToIp(szIp, 28, GHndDat_GetAddr((DWORD)GHndDat_GetOwner(dwClientContext)));
		lvitem.pszText = szIp;
	}else
		lvitem.pszText = NULL;
	m_lstClient.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 4;
	if((GHND_TYPE_TCP_SVR_CLIENT == HndType) || (GHND_TYPE_UDP_SVR_CLIENT == HndType))
	{
		str.Format(_T("%d"), GHndDat_GetPort((DWORD)GHndDat_GetOwner(dwClientContext)));
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	}else
		lvitem.pszText = NULL;
	m_lstClient.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = nIndex;
	lvitem.iSubItem = 5;
	GSock_AddrToIp(szIp, 28, GHndDat_GetAddr(dwClientContext));
	lvitem.pszText = szIp;
	m_lstClient.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 6;
	str.Format(_T("%d"), GHndDat_GetPort(dwClientContext));
	lvitem.pszText = (LPTSTR)(LPCTSTR)str;
	m_lstClient.SetItem(&lvitem);

	lvitem.iItem = nIndex;
	lvitem.iSubItem = 7;
	lvitem.pszText = _T("0");
	m_lstClient.SetItem(&lvitem);

	m_lstClient.SetItemData(nIndex, (DWORD_PTR)dwClientContext);
}

void CGSockInfo::OnDisconnect(DWORD dwClientContext)
{
	int i, nIndex = -1;

	for(i = 0; i <= m_lstClient.GetItemCount() - 1; i++)
	{
		if((DWORD)m_lstClient.GetItemData(i) == dwClientContext)
		{
			nIndex = i;
			m_lstClient.DeleteItem(nIndex);
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

	for(i = nIndex; i <= m_lstClient.GetItemCount() - 1; i++)
	{
		lvitem.iItem = i;
		lvitem.iSubItem = 0;
		str.Format(_T("%d"), i + 1);
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstClient.SetItem(&lvitem);
	}
}

BOOL CGSockInfo::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	switch(message)
	{
		case GMSG_ADD_LISTENER:
			OnAddListener(wParam);
			break;
		case GMSG_CONNECT:
			OnConnect(wParam);
			break;
		case GMSG_DISCONNECT:
			OnDisconnect(wParam);
			break;
		case GMSG_CLEAR_LIST:
			m_lstListener.DeleteAllItems();
			m_lstWorker.DeleteAllItems();
			m_lstClient.DeleteAllItems();
			break;
	}

	return(CDialog::OnWndMsg(message, wParam, lParam, pResult));
}