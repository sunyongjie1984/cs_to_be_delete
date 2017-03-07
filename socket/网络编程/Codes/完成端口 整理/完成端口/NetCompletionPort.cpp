#include "stdafx.h"
#include "NetCompletionPort.h"
#include <ws2tcpip.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////WorkThrerd

NetCompletionPort* g_pHostServer = NULL;

WorkThread::WorkThread()
{
	m_hThread = NULL;
	m_nThreadID = 0;
	pnThreadFun = NULL;
	m_pParam = NULL;
}

WorkThread::WorkThread(unsigned int (__stdcall*pnThreadFun)(LPVOID param),void* param)
{
	m_hThread = NULL;
	m_nThreadID = 0;
	this->pnThreadFun = pnThreadFun;
	m_pParam = param;
}

WorkThread::~WorkThread()
{
}

bool WorkThread::Init()
{
	m_hThread = (HANDLE)_beginthreadex(NULL,0,pnThreadFun,m_pParam,CREATE_SUSPENDED,&m_nThreadID);//CREATE_SUSPENDED
	if(m_hThread)
		return TRUE;
	return FALSE;
}

void WorkThread::Start()
{
	if(m_hThread)
		ResumeThread(m_hThread);	
}

void WorkThread::Stop()
{	
	if (m_hThread)
	{
		DWORD code;
		int count = 0;
		while(TRUE)
		{
			if(count++ >= 5)
			{
				TerminateThread(m_hThread,0);
				break;
			}
			GetExitCodeThread(m_hThread,&code);
			if(code == STILL_ACTIVE)
			{
				Sleep(1000);
				continue;
			}
			else
				break;
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

void WorkThread::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (m_hThread)
		PostThreadMessage(m_nThreadID, Msg, wParam, lParam);
}

void WorkThread::SetPriority(int priority)
{
	if (m_hThread)
		SetThreadPriority(m_hThread, priority);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////NetClient

NetClient::NetClient()
{
	m_socket = NULL;
	m_pComKey = NULL;
}

NetClient::NetClient(int socket)
{
	m_socket = socket;
}

NetClient::~NetClient()
{
	if(m_socket)
		closesocket(m_socket);
}

void NetClient::SendPacket(void* pData,bool encrypt)
{
	g_pHostServer->SendPacket(m_socket,pData,encrypt);
}

void NetClient::Disconnect()
{
	if(m_socket)
	{
		closesocket(m_socket);
		m_socket = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////NetCompletionPort

NetCompletionPort::NetCompletionPort()
{
	g_pHostServer = this;
	m_pAcceptEx = NULL;
	m_comPort = NULL;
	m_port = 0;
	m_listenSocket = NULL;
	m_hEventListen = NULL;
	m_isCreate = FALSE;
	
	m_pWorkThreadList = new std::vector<WorkThread*>;
	m_pThreadAccept = NULL;
	m_pClientList = new std::map<int,NetClient*>;
	m_pConnectList = new std::set<LPPER_IO_CONTEXT>;
	m_pIoMemList = new std::deque<LPPER_IO_CONTEXT>;
	m_pHandleMemList = new std::deque<LPPER_HANDLE_CONTEXT>;

	m_pClientList->clear();
	m_pConnectList->clear();
	m_pIoMemList->clear();
	m_pHandleMemList->clear();
	
	InitializeCriticalSection(&m_clientListSection); 
	InitializeCriticalSection(&m_conSection); 
	InitializeCriticalSection(&m_ioMenListSection); 
	InitializeCriticalSection(&m_hdMemListSection); 
}

NetCompletionPort::~NetCompletionPort()
{
//	NetCompletionPort::StopServer();
	delete m_pClientList;
	delete m_pConnectList;
	delete m_pIoMemList;
	delete m_pHandleMemList;

	DeleteCriticalSection(&m_clientListSection);
	DeleteCriticalSection(&m_conSection);
	DeleteCriticalSection(&m_ioMenListSection);
	DeleteCriticalSection(&m_hdMemListSection);
}

bool NetCompletionPort::StartServer(int port)
{
	WSADATA m_wsaData;
	m_port = port;
	if(WSAStartup(MAKEWORD(2,2), &m_wsaData))
		return FALSE;
	if(InitWinSock() && InitListenSocket() && InitListenEvent() && InitWorkThread())
	{
		m_isCreate = TRUE;
		m_pThreadAccept->Start();
		std::vector<WorkThread*>::iterator pos = m_pWorkThreadList->begin();
		while (pos != m_pWorkThreadList->end())
		{
			(*pos)->Start();
			pos++;
		}
	}
	else
	{
		StopServer();
		return FALSE;
	}
	return TRUE;
}

bool NetCompletionPort::InitWinSock()
{
	m_comPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
	if(!m_comPort)
		return FALSE;
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	for(int i=0;i<(sysInfo.dwNumberOfProcessors*2);i++)
	{
		WorkThread* pThread = new WorkThread(&WorkThreadFun,this);
		if(pThread->Init())
			m_pWorkThreadList->push_back(pThread);
		else
		{
			delete pThread;
			return FALSE;
		}
	}
	return TRUE;
}

bool NetCompletionPort::InitListenSocket()
{
	m_listenSocket = WSASocket(PF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
	if(INVALID_SOCKET == m_listenSocket)
	{
		m_listenSocket = NULL;
		return FALSE;
	}
	if(!CreateIoCompletionPort((HANDLE)m_listenSocket,m_comPort,0,0))
		return FALSE;
	SOCKADDR_IN SockAddr;
	SockAddr.sin_family       = AF_INET;
	SockAddr.sin_port         = htons(m_port);
	SockAddr.sin_addr.s_addr  = INADDR_ANY;
	if(SOCKET_ERROR == bind(m_listenSocket,(PSOCKADDR)&SockAddr,sizeof(SockAddr)))
		return FALSE;
	if(SOCKET_ERROR == listen(m_listenSocket,10))
		return FALSE;
	DWORD dwTemp=0;
	if(SOCKET_ERROR == WSAIoctl(m_listenSocket,SIO_GET_EXTENSION_FUNCTION_POINTER,
		&g_GUIDAcceptEx,sizeof(g_GUIDAcceptEx),&m_pAcceptEx,sizeof(m_pAcceptEx),
		&dwTemp,NULL,NULL))
	{
		m_pAcceptEx = NULL;
		return FALSE;
	}
	if(SOCKET_ERROR == WSAIoctl(m_listenSocket,SIO_GET_EXTENSION_FUNCTION_POINTER,
		&g_GUIDGetAcceptExSockaddrs,sizeof(g_GUIDGetAcceptExSockaddrs),&m_pGetAcceptExSockaddrs,sizeof(m_pGetAcceptExSockaddrs),
		&dwTemp,NULL,NULL))
	{
		m_pGetAcceptExSockaddrs = NULL;
		return FALSE;
	}
	
	return TRUE;
}

bool NetCompletionPort::InitListenEvent()
{
	m_hEventListen = CreateEvent(NULL,FALSE,FALSE,NULL);
	if(NULL == m_hEventListen)
		return FALSE;
	if(SOCKET_ERROR == ::WSAEventSelect(m_listenSocket,m_hEventListen,FD_ACCEPT))
		return FALSE;
	return TRUE;
}

bool NetCompletionPort::InitWorkThread()
{
	m_pThreadAccept = new WorkThread(AcceptThreadFun,this);
	if(!m_pThreadAccept->Init())
	{
		delete m_pThreadAccept;
		return FALSE;
	}
	return TRUE;
}

void NetCompletionPort::StopServer()
{
	m_isCreate = FALSE;
	if(m_comPort)
	{
		PostQueuedCompletionStatus(m_comPort,0,0,NULL);
        CloseHandle(m_comPort);
		m_comPort = NULL;
	}
	if(m_pThreadAccept != NULL)
	{
		m_pThreadAccept->Stop();
		delete m_pThreadAccept;
		m_pThreadAccept = NULL;
	}
	std::vector<WorkThread*>::iterator pos = m_pWorkThreadList->begin();
	while (pos != m_pWorkThreadList->end())
	{
		(*pos)->Stop();
		delete (*pos);
		pos++;
	}
	m_pWorkThreadList->clear();
	if(m_listenSocket != NULL)
	{
		closesocket(m_listenSocket);
		m_listenSocket = NULL;
	}
	if(m_hEventListen != NULL)
	{
		CloseHandle(m_hEventListen);
		m_hEventListen = NULL;
	}
	std::map<int,NetClient*>::iterator pos1 = m_pClientList->begin();
	while(pos1 != m_pClientList->end())
	{
		NetClient* pClient = pos1->second;
		pClient->Disconnect();
		InsertHandleMem(pClient->m_pComKey);
		delete pClient;
		pos1++;
	}
	m_pClientList->clear();
	std::set<LPPER_IO_CONTEXT>::iterator pos2 = m_pConnectList->begin();
	while(pos2 != m_pConnectList->end())
	{
		free(*pos);
		pos2++;
	}
	m_pConnectList->clear();
	std::deque<LPPER_IO_CONTEXT>::iterator pos3 = m_pIoMemList->begin();
	while(pos3 != m_pIoMemList->end())
	{
		free(*pos3);
		pos3++;
	}
	m_pIoMemList->clear();
	std::deque<LPPER_HANDLE_CONTEXT>::iterator pos4 = m_pHandleMemList->begin();
	while(pos4 != m_pHandleMemList->end())
	{
		free(*pos4);
		pos4++;
	}
	m_pHandleMemList->clear();
	WSACleanup();
}

void NetCompletionPort::DeleteClient(NetClient* pClient)
{
	if(pClient == NULL)
		return;
	EnterCriticalSection(&m_clientListSection);
	std::map<int,NetClient*>::iterator pos = m_pClientList->find(pClient->m_socket);
	if(pos != m_pClientList->end())
	{
		NetClient* pClient = pos->second;
		pClient->Disconnect();
		InsertHandleMem(pClient->m_pComKey);
		delete pClient;
		m_pClientList->erase(pClient->m_socket);
	}
	LeaveCriticalSection(&m_clientListSection);	
}

void NetCompletionPort::AddClient(NetClient* pClient)
{
	if(pClient == NULL)
		return;
	EnterCriticalSection(&m_clientListSection);
	m_pClientList->insert(std::make_pair(pClient->m_socket,pClient));
	LeaveCriticalSection(&m_clientListSection);	
}

NetClient* NetCompletionPort::GetClient(int socket)
{
	NetClient* pClient = NULL;
	EnterCriticalSection(&m_clientListSection);
	std::map<int,NetClient*>::iterator pos = m_pClientList->find(socket);
	if(pos != m_pClientList->end())
		pClient = pos->second;
	LeaveCriticalSection(&m_clientListSection);	
	return pClient;
}

void NetCompletionPort::InsertConnect(LPPER_IO_CONTEXT pConnect)
{
	if(pConnect != NULL)
	{
		EnterCriticalSection(&m_conSection);
		m_pConnectList->insert(pConnect);
		LeaveCriticalSection(&m_conSection);	
	}
}

void NetCompletionPort::ReleaseConnect(int socket)
{
	EnterCriticalSection(&m_conSection);
	std::set<LPPER_IO_CONTEXT>::iterator pos = m_pConnectList->begin();
	while (pos != m_pConnectList->end())
	{
		if((*pos)->sClient == socket)
		{
			m_pConnectList->erase(pos);
			break;
		}
		pos++;
	}
	LeaveCriticalSection(&m_conSection);
}

LPPER_IO_CONTEXT NetCompletionPort::GetIoMem()
{
	LPPER_IO_CONTEXT pData = NULL;
	EnterCriticalSection(&m_ioMenListSection);
	if(m_pIoMemList->size() > 0)
	{
		pData = m_pIoMemList->front();
		m_pIoMemList->pop_front();
	}
	else
	{
		pData = (LPPER_IO_CONTEXT)malloc(sizeof(PER_IO_CONTEXT));
	}
	LeaveCriticalSection(&m_ioMenListSection);	
	memset(pData,0,sizeof(PER_IO_CONTEXT));
	return pData;
}

LPPER_HANDLE_CONTEXT NetCompletionPort::GetHandleMem()
{
	LPPER_HANDLE_CONTEXT pData = NULL;
	EnterCriticalSection(&m_hdMemListSection);
	if(m_pHandleMemList->size() > 0)
	{
		pData = m_pHandleMemList->front();
		m_pHandleMemList->pop_front();
	}
	else
	{
		pData = (LPPER_HANDLE_CONTEXT)malloc(sizeof(PER_HANDLE_CONTEXT));
	}
	LeaveCriticalSection(&m_hdMemListSection);	
	memset(pData,0,sizeof(PER_HANDLE_CONTEXT));
	return pData;
}

void NetCompletionPort::InsertIoMem(LPPER_IO_CONTEXT pMem)
{
	EnterCriticalSection(&m_ioMenListSection);
	if(m_pIoMemList->size() < MAX_MEM_COUNT)
		m_pIoMemList->push_back(pMem);
	else
		free(pMem);
	LeaveCriticalSection(&m_ioMenListSection);	
}

void NetCompletionPort::InsertHandleMem(LPPER_HANDLE_CONTEXT pMem)
{
	EnterCriticalSection(&m_hdMemListSection);
	if(m_pHandleMemList->size() < MAX_MEM_COUNT)
		m_pHandleMemList->push_back(pMem);
	else
		free(pMem);
	LeaveCriticalSection(&m_hdMemListSection);	
}

bool NetCompletionPort::PostAcceptEx()
{
	for(int i=0;i<10;i++)
	{
		SOCKET socketAcp = WSASocket(PF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
		if(INVALID_SOCKET == socketAcp)
			return FALSE;
		LPPER_IO_CONTEXT temp = GetIoMem();
		temp->IoOperation = IO_ACCEPT;
		temp->sClient = socketAcp;
		temp->id = socketAcp;
		temp->wsabuf.len = MAX_BUF;
		DWORD dwByte;
		if(!m_pAcceptEx(m_listenSocket,socketAcp,temp->buf,MAX_BUF-((sizeof(SOCKADDR_IN)+16)*2),
			sizeof(SOCKADDR_IN)+16,sizeof(SOCKADDR_IN)+16,&dwByte,&temp->ol))
		{
			if(ERROR_IO_PENDING != WSAGetLastError())
			{
				::closesocket(socketAcp);
			    InsertIoMem(temp);
			    return FALSE;
			}
		}
	}
	return TRUE;
}

bool NetCompletionPort::Disconnect(int socket)
{
	bool rlt = FALSE;
	EnterCriticalSection(&m_clientListSection);
	std::map<int,NetClient*>::iterator pos = m_pClientList->find(socket);
	if(pos != m_pClientList->end())
	{
		NetClient* pClient = pos->second;
		pClient->Disconnect();
		InsertHandleMem(pClient->m_pComKey);
		delete pClient;
		m_pClientList->erase(socket);
		rlt = TRUE;
	}
	LeaveCriticalSection(&m_clientListSection);	
	return rlt;
}

void NetCompletionPort::SendPacket(int socket,void * pData,bool encrypt)
{
	DWORD SendBytes,Flags;
	Flags = 0;
	int length = 0;
	EncryptPacket(pData,length,IO_SEND,encrypt);
	if(length > MAX_BUF)
		return;
	LPPER_IO_CONTEXT pIoMem = GetIoMem();
	pIoMem->IoOperation = IO_WRITE;
	pIoMem->sClient = socket;
	pIoMem->id = socket;
	memset(pIoMem->buf,0,MAX_BUF);
	pIoMem->wsabuf.buf = pIoMem->buf;
	pIoMem->wsabuf.len = MAX_BUF;
	memset(&(pIoMem->ol),0,sizeof(WSAOVERLAPPED));
	memcpy(pIoMem->buf,pData,length);
	WSASend(socket,&pIoMem->wsabuf,1,&SendBytes,Flags,&(pIoMem->ol),NULL);
	EncryptPacket(pData,length,IO_SEND,encrypt);
}

void NetCompletionPort::EncryptPacket(void * pData,int & length,BYTE type,bool encrypt)
{
}

void NetCompletionPort::RecvData(void * pData,NetClient* pClient)
{
}

void NetCompletionPort::AcceptEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte)
{
	DWORD flag = 0;
	DWORD dwRecv = 0;
	DWORD ret = 0;
	NetClient* pClient = new NetClient(pHd->IoSocket);
	pClient->m_pComKey = pHd;		
	AddClient(pClient);
	int count = 0;
	while(count < (RECV_COUNT - 1))
	{
		LPPER_IO_CONTEXT p = GetIoMem();
		memset(p,0,sizeof(PER_IO_CONTEXT));
		p->sClient = pIo->sClient;
		p->id = pIo->id;
		p->wsabuf.buf = p->buf;
		p->wsabuf.len = MAX_BUF;
		p->IoOperation = IO_READ;
		ret = WSARecv(pHd->IoSocket,&(p->wsabuf),1,&dwRecv,&flag,&(p->ol),NULL);
		if(SOCKET_ERROR == ret)
		{
			if(WSA_IO_PENDING != WSAGetLastError())
			{
				Disconnect(pHd->IoSocket);
				InsertIoMem(pIo);
				return;
			}
		}	
		count++;
	}
	if(dwByte > 0)
	{
		SOCKADDR * lpLocalSockaddr = NULL,* lpRemoteSockaddr = NULL;
		int LocalSockAddrLen = 0,RemoteSockaddrLen = 0;
		m_pGetAcceptExSockaddrs(pIo->buf,pIo->wsabuf.len - ((sizeof(SOCKADDR_IN) + 16)*2),
			  sizeof(SOCKADDR_IN) + 16,sizeof(SOCKADDR_IN) + 16,&lpLocalSockaddr,&LocalSockAddrLen,
			  &lpRemoteSockaddr,&RemoteSockaddrLen);
		if(lpRemoteSockaddr != NULL)
			memcpy(&pClient->m_address,lpRemoteSockaddr,sizeof(SOCKADDR_IN));
		RecvData(pIo->buf,pClient);
	}
	memset(pIo->buf,0,MAX_BUF);
	memset(&(pIo->ol),0,sizeof(WSAOVERLAPPED));
	pIo->wsabuf.buf = pIo->buf;
	pIo->wsabuf.len = MAX_BUF;
	pIo->IoOperation = IO_READ;
	ret = WSARecv(pHd->IoSocket,&(pIo->wsabuf),1,&dwRecv,&flag,&(pIo->ol),NULL);
	if(SOCKET_ERROR == ret)
	{
		if(WSA_IO_PENDING != WSAGetLastError())
		{
			Disconnect(pHd->IoSocket);
			InsertIoMem(pIo);
			return;
		}
	}	
}

void NetCompletionPort::SendEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte)
{
	if(dwByte < 0)
	{
		InsertIoMem(pIo);
		Disconnect(pHd->IoSocket);
	}
	else
		InsertIoMem(pIo);
}

void NetCompletionPort::RecvEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte)
{
	if(dwByte < 0)
	{
		InsertIoMem(pIo);
		Disconnect(pHd->IoSocket);
	}
	else
	{
		RecvData(pIo->buf,GetClient(pHd->IoSocket));
		DWORD flag = 0;
		DWORD dwRecv = 0;
		DWORD ret = 0;
		memset(pIo->buf,0,MAX_BUF);
		memset(&(pIo->ol),0,sizeof(WSAOVERLAPPED));
		pIo->wsabuf.buf = pIo->buf;
		pIo->wsabuf.len = MAX_BUF;
		pIo->IoOperation = IO_READ;
		ret = WSARecv(pHd->IoSocket,&(pIo->wsabuf),1,&dwRecv,&flag,&(pIo->ol),NULL);
		if(SOCKET_ERROR == ret)
		{
			if(WSA_IO_PENDING != WSAGetLastError())
			{
				Disconnect(pHd->IoSocket);
				InsertIoMem(pIo);
				return;
			}
		}	
	}
}

void NetCompletionPort::CloseEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd)
{
	Disconnect(pIo->sClient);
	InsertIoMem(pIo);
}

unsigned __stdcall NetCompletionPort::WorkThreadFun(LPVOID param)
{
	NetCompletionPort* p = (NetCompletionPort*)param;
	HANDLE port = p->m_comPort;
	DWORD dwByteSend;
	DWORD dwByteRecv;
	DWORD dwByteTrans;
	bool  flag;
	DWORD ret;
	BYTE opType;
	LPPER_IO_CONTEXT pIoData = NULL;
	LPPER_HANDLE_CONTEXT pHandleData = NULL;
	while(p->m_isCreate)
	{
		pIoData = NULL;
	    pHandleData = NULL;
		ret = GetQueuedCompletionStatus(port,&dwByteTrans,
			  (LPDWORD)&pHandleData,(LPOVERLAPPED*)&pIoData,1000);
		if(FALSE == ret)
		{
			continue;
		}
		else if(pIoData == NULL)
		{
			return 0;
		}
		opType = pIoData->IoOperation;
		if(opType != IO_ACCEPT && dwByteTrans == 0)
		{
			p->Disconnect(pHandleData->IoSocket);
			p->InsertIoMem(pIoData);
			continue;
		}
		if(opType == IO_ACCEPT)
		{
			//释放接点
			p->ReleaseConnect((DWORD)pIoData->sClient);
			if(SOCKET_ERROR == setsockopt(p->m_listenSocket,SOL_SOCKET,SO_UPDATE_ACCEPT_CONTEXT,
				(char*)&(pIoData->sClient),sizeof(pIoData->sClient)))
			{
				::closesocket(pIoData->sClient);
				p->InsertIoMem(pIoData);
				continue;
			}
			else
			{
				//分配单句柄数据
				LPPER_HANDLE_CONTEXT pNeW = p->GetHandleMem();
				pNeW->IoSocket = pIoData->sClient;
				if(!CreateIoCompletionPort((HANDLE)pIoData->sClient,p->m_comPort,(DWORD)pNeW,0))
				{
					::closesocket(pIoData->sClient);
				    p->InsertIoMem(pIoData);
					p->InsertHandleMem(pNeW);
				    continue;
				}				
				p->AcceptEvent(pIoData,pNeW,dwByteTrans);				
			}
			continue;
		}
		else if(opType == IO_READ)
		{
			p->RecvEvent(pIoData,pHandleData,dwByteTrans);
			continue;
		}
		else if(opType == IO_WRITE)
		{
			p->SendEvent(pIoData,pHandleData,dwByteTrans);
			continue;
		}
		else
		{
			p->Disconnect(pHandleData->IoSocket);
			p->InsertIoMem(pIoData);
			continue;
		}
	}
	return 1;
}

unsigned __stdcall NetCompletionPort::AcceptThreadFun(LPVOID param)
{
	NetCompletionPort* p=(NetCompletionPort*)param;
	DWORD ret=0;
	while(p->m_isCreate)
	{
		ret=::WaitForSingleObject(p->m_hEventListen,1000);
		if(WAIT_FAILED == ret)
		{
			return 0;
		}
		else if(WAIT_TIMEOUT == ret)
		{
			int optValue = 0;
	        int len = sizeof(optValue);
	        int ret = 0;
	        int count = 0;
		    EnterCriticalSection(&p->m_conSection);
		    std::set<LPPER_IO_CONTEXT>::iterator pos = p->m_pConnectList->begin();
		    while(pos != p->m_pConnectList->end())
			{
			    ret = ::getsockopt((*pos)->sClient,SOL_SOCKET,SO_CONNECT_TIME,(char*)&optValue,&len);
			    if(ret == SOCKET_ERROR)
				{
				    ++pos;
				    continue;
				}
			    else if(optValue != -1&&optValue >= 10)
				{
				    ::closesocket((*pos)->sClient);
				    std::set<LPPER_IO_CONTEXT>::iterator temp = pos;
				    ++pos;
					p->InsertIoMem(*temp);
				    p->m_pConnectList->erase(temp);
				    if(pos == p->m_pConnectList->end())						
					    break;
				    else
					{
					    LPPER_IO_CONTEXT temp1 = *pos;
						pos = p->m_pConnectList->find(temp1);
					    continue;
					}			
				}
				++pos;
			}
			LeaveCriticalSection(&p->m_conSection);
		}
		else if(WAIT_OBJECT_0==ret)
		{
			if(!p->PostAcceptEx())
			{
			    return 0;
			}
			else
			{
				continue;
			}
		}
	}
    return 1;
}

