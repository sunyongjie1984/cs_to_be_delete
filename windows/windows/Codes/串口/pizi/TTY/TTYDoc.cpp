// TTYDoc.cpp : implementation of the CTTYDoc class
//

#include "stdafx.h"
#include "TTY.h"
#include "commsetDlg.h"
#include "TTYDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYDoc

IMPLEMENT_DYNCREATE(CTTYDoc, CDocument)

BEGIN_MESSAGE_MAP(CTTYDoc, CDocument)
	//{{AFX_MSG_MAP(CTTYDoc)
	ON_COMMAND(ID_API_CONNECT, OnApiConnect)
	ON_UPDATE_COMMAND_UI(ID_API_CONNECT, OnUpdateApiConnect)
	ON_COMMAND(ID_API_DISCONNECT, OnApiDisconnect)
	ON_UPDATE_COMMAND_UI(ID_API_DISCONNECT, OnUpdateApiDisconnect)
	ON_COMMAND(ID_API_SETTINGS, OnApiSettings)
	ON_UPDATE_COMMAND_UI(ID_API_SETTINGS, OnUpdateApiSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CTTYDoc construction/destruction

CTTYDoc::CTTYDoc()
{
	// TODO: add one-time construction code here
//初始化操作
	m_bConnected=FALSE;//断开连接菜单项无效
	m_pThread=NULL;

	m_nBaud = 9600;
	m_nDataBits = 8;
	m_bEcho = FALSE;
	m_bNewLine = FALSE;
	m_nParity = 0;
	m_sPort = "COM2";
	m_nStopBits = 0;
}

CTTYDoc::~CTTYDoc()
{
//程序结束时删除线程、关闭串口的操作
	if(m_bConnected)
		CloseConnection();

	// 删除事件句柄
	if(m_hPostMsgEvent)
		CloseHandle(m_hPostMsgEvent);

	if(m_osRead.hEvent)
		CloseHandle(m_osRead.hEvent);

	if(m_osWrite.hEvent)
		CloseHandle(m_osWrite.hEvent);
}

BOOL CTTYDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	// 为WM_COMMNOTIFY消息创建事件对象，手工重置，初始化为有信号的
	if((m_hPostMsgEvent=CreateEvent(NULL, TRUE, TRUE, NULL))==NULL)
		return FALSE;

	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));

	// 为重叠读创建事件对象，手工重置，初始化为无信号的
	if((m_osRead.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL))==NULL)
		return FALSE;

	// 为重叠写创建事件对象，手工重置，初始化为无信号的
	if((m_osWrite.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL))==NULL)
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTTYDoc serialization

void CTTYDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTTYDoc diagnostics

#ifdef _DEBUG
void CTTYDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTTYDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTYDoc commands

BOOL CTTYDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	SetModifiedFlag(FALSE); // 将文档的修改标志设置成未修改
	return CDocument::CanCloseFrame(pFrame);
	
}

// 工作者线程，负责监视串行口
UINT CommProc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CTTYDoc *pDoc=(CTTYDoc*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);

	if(os.hEvent==NULL)
	{
		AfxMessageBox("Can't create event object!");
		return (UINT)-1;
	}

	while(pDoc->m_bConnected)
	{
		ClearCommError(pDoc->m_hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			// 无限等待WM_COMMNOTIFY消息被处理完
			WaitForSingleObject(pDoc->m_hPostMsgEvent, INFINITE);
			ResetEvent(pDoc->m_hPostMsgEvent);

			// 通知视图
			PostMessage(pDoc->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask=0;

		if(!WaitCommEvent(pDoc->m_hCom, &dwMask, &os)) // 重叠操作
		{

			if(GetLastError()==ERROR_IO_PENDING)
			// 无限等待重叠操作结果
				GetOverlappedResult(pDoc->m_hCom, &os, &dwTrans, TRUE);
			else
			{
				CloseHandle(os.hEvent);
				return (UINT)-1;
			}
		}
	}

	CloseHandle(os.hEvent);
	return 0;
}

// 将指定数量的字符从串行口输出
DWORD CTTYDoc::WriteComm(char *buf, DWORD dwLength)
{
	BOOL fState;
	DWORD length=dwLength;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
	fState=WriteFile(m_hCom,buf,length,&length,&m_osWrite);

	if(!fState)
	{

		if(GetLastError()==ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hCom,&m_osWrite,&length,TRUE);// 等待
		}
		else
			length=0;
	}

	return length;
}

// 从串行口输入缓冲区中读入指定数量的字符
DWORD CTTYDoc::ReadComm(char *buf, DWORD dwLength)
{
	DWORD length=0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
	length=min(dwLength, ComStat.cbInQue);
	ReadFile(m_hCom,buf,length,&length,&m_osRead);

	return length;
}

//菜单项"串口连接"的响应
void CTTYDoc::OnApiConnect() 
{
	// TODO: Add your command handler code here
	if(!OpenConnection())
		AfxMessageBox("Can't open connection");
}

//更新"串口连接"菜单项
void CTTYDoc::OnUpdateApiConnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bConnected);
}

//菜单项"断开连接"的响应函数
void CTTYDoc::OnApiDisconnect() 
{
	// TODO: Add your command handler code here
	CloseConnection(); 
}

//更新菜单项"断开连接"
void CTTYDoc::OnUpdateApiDisconnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bConnected);
}

//菜单项"串行口设置" 的响应函数
void CTTYDoc::OnApiSettings() 
{
	// TODO: Add your command handler code here
	CCommSetDlg dlg;
	CString str;

	dlg.m_bConnected = m_bConnected;

	dlg.m_sPort = m_sPort;

	str.Format("%d", m_nBaud);
	dlg.m_sBaud = str;

	str.Format("%d", m_nDataBits);
	dlg.m_sDataBits = str;

	dlg.m_nParity = m_nParity;
	
	dlg.m_nStopBits = m_nStopBits;
	
	dlg.m_bEcho = m_bEcho;
	dlg.m_bNewLine = m_bNewLine;

	if(dlg.DoModal() == IDOK)
	{
		m_sPort = dlg.m_sPort;
		m_nBaud = atoi(dlg.m_sBaud);
		m_nDataBits = atoi(dlg.m_sDataBits);
		m_nParity = dlg.m_nParity;
		m_nStopBits = dlg.m_nStopBits;
		
		m_bEcho=dlg.m_bEcho;
		m_bNewLine=dlg.m_bNewLine;

		if(m_bConnected)
			if(!ConfigConnection())
				AfxMessageBox("Can't realize the settings!");
	}
}

//更新"串行口设置"菜单项
void CTTYDoc::OnUpdateApiSettings(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
 //配置串口连接
BOOL CTTYDoc::ConfigConnection()
{
	DCB dcb;

	if(!GetCommState(m_hCom, &dcb))
		return FALSE;

	dcb.fBinary=TRUE;
	dcb.BaudRate = m_nBaud; // 数据传输速率
	dcb.ByteSize = m_nDataBits; // 每字节位数
	dcb.fParity = TRUE;

	switch(m_nParity) // 校验设置
	{
	case 0: 
		dcb.Parity=NOPARITY;
		break;

	case 1: 
		dcb.Parity=EVENPARITY;
		break;

	case 2: 
		dcb.Parity=ODDPARITY;
		break;

	default:;
	}

	switch(m_nStopBits) // 停止位
	{
	case 0: 
		dcb.StopBits=ONESTOPBIT;
		break;

	case 1: 
		dcb.StopBits=ONE5STOPBITS;
		break;

	case 2:
		dcb.StopBits=TWOSTOPBITS;
		break;

	default:;
	}

	// 硬件流控制设置
	dcb.fOutxCtsFlow = TRUE;
	dcb.fRtsControl = TRUE;

	// XON/XOFF流控制设置
	dcb.fInX=dcb.fOutX = TRUE;
	dcb.XonChar = XON;
	dcb.XoffChar = XOFF;
	dcb.XonLim = 50;
	dcb.XoffLim = 50;

	return SetCommState(m_hCom, &dcb);
}

// 打开并配置串行口，建立工作者线程
BOOL CTTYDoc::OpenConnection()
{
	COMMTIMEOUTS TimeOuts;
	POSITION firstViewPos;
	CView *pView;

	firstViewPos=GetFirstViewPosition();
	pView=GetNextView(firstViewPos);

	m_hTermWnd=pView->GetSafeHwnd();

	if(m_bConnected)
		return FALSE;

	m_hCom=CreateFile(m_sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
		NULL); // 重叠方式

	if(m_hCom==INVALID_HANDLE_VALUE)
		return FALSE;

	SetupComm(m_hCom,MAXBLOCK,MAXBLOCK);
	SetCommMask(m_hCom, EV_RXCHAR);


	// 把间隔超时设为最大，把总超时设为0将导致ReadFile立即返回并完成操作
	TimeOuts.ReadIntervalTimeout=MAXDWORD; 
	TimeOuts.ReadTotalTimeoutMultiplier=0; 
	TimeOuts.ReadTotalTimeoutConstant=0; 

	/* 设置写超时以指定WriteComm成员函数中的GetOverlappedResult函数的等待时间*/
	TimeOuts.WriteTotalTimeoutMultiplier=50;
	TimeOuts.WriteTotalTimeoutConstant=2000;

	SetCommTimeouts(m_hCom, &TimeOuts);

	if(ConfigConnection())
	{

		m_pThread=AfxBeginThread(CommProc, this, THREAD_PRIORITY_NORMAL, 
			0, CREATE_SUSPENDED, NULL); // 创建并挂起线程

		if(m_pThread==NULL)
		{
			CloseHandle(m_hCom);
			return FALSE;
		}
		else

		{
			m_bConnected=TRUE;
			m_pThread->ResumeThread(); // 恢复线程运行
		}
	}
	else
	{
		CloseHandle(m_hCom);
		return FALSE;
	}
	
	return TRUE;
}

//关闭连接，关闭工作线程
void CTTYDoc::CloseConnection()
{
	if(!m_bConnected)
		return;

	m_bConnected=FALSE;

	//结束CommProc线程中WaitSingleObject函数的等待
	SetEvent(m_hPostMsgEvent); 

	//结束CommProc线程中WaitCommEvent的等待
	SetCommMask(m_hCom, 0); 

	//等待辅助线程终止
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_pThread=NULL;
	CloseHandle(m_hCom);

}
