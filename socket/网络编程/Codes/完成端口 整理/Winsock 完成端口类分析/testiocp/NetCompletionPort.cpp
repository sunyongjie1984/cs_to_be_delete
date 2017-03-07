/*++
Copyright (c) 2004 
模块名: 
iomodel.cpp
模块描述:
Winsock 完成端口类实现文件
作者:
PPP elssann@hotmail.com
开发环境:

Visual C++ 6.0, Windows 2000.

修订记录:
创建于: 2004.1.16
最后修改日期:
2004.1.23
	
--*/
#include <iostream.h>

#include "NetCompletionPort.h"

#include <windows.h>
#include <iostream.h>


#pragma comment(lib, "ws2_32.lib")


/*++
函数描述:
构造函数，初始化线程句柄数组，初始化AcceptEx()调用的计数。初始化临界段代码变量。
Arguments:
无。
Return Value:
无。
--*/
CompletionPortModel::CompletionPortModel()
{
	for (int i=0; i< MAXTHREAD_COUNT; i++)
	{
		m_hThreadArray[i] = INVALID_HANDLE_VALUE;
	}
	m_lAcceptExCounter = 0;
	InitializeCriticalSection(&m_ListCriSection); 
	InitializeCriticalSection(&m_HandleCriSection);
	InitializeCriticalSection(&m_IoCriSection);
	m_lpHandleLOOKasideLists = NULL;
	m_lpIoLookasideLists = NULL;
#ifndef _DEBUG
	GetAddressAndPort();
#endif
}//end of CompletionPortModel()



/*++
函数描述:
析构函数，释放链表所有结点。
Arguments:
无。
Return Value:
--*/
CompletionPortModel::~CompletionPortModel()
{
	PPER_IO_CONTEXT lpIoNode;
	while (m_lpConnectionListHead->pNext)
	{
		lpIoNode = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = lpIoNode->pNext;
		closesocket(lpIoNode->sClient);
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}
	while(NULL != m_lpIoLookasideLists)
	{
		lpIoNode = m_lpIoLookasideLists;
		m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}
	PPER_HANDLE_CONTEXT lpHandleNode;
	while(NULL != m_lpHandleLOOKasideLists)
	{
		lpHandleNode = m_lpHandleLOOKasideLists;
		m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpHandleNode);
	}
	DeleteCriticalSection(&m_ListCriSection); 
	DeleteCriticalSection(&m_HandleCriSection);
	DeleteCriticalSection(&m_IoCriSection);
	
}//end of ~CompletionPortModel()




/*++
函数描述:
初始化，创建完成端口、创建完成端口线程，并调用类成员函数InitWinsock初始化Winsock、
建立一个监听套接字m_ListenSocket，并将此套接字同完成端口关联起来，获取AcceptEx指针。
Arguments:
无。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。
--*/
BOOL CompletionPortModel::Init()
{
	BOOL bSuccess = InitLinkListHead();
	
	if (FALSE == bSuccess)
	{
		return FALSE;
	}
	
	m_hCOP = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE,	//数指定一个要同完成端口关联在一起的套接字句柄
		NULL,					//参数指定的是一个现有的完成端口
		NULL,					//则指定要与某个特定套接字句柄关联在一起的“单句柄数据”
		0		//NumberOfConcurrentThreads参数定义了在一个完成端口上，同时允许执行的线程数量。
		);
	/*
	设为0，表明系统内安装了多少个处理器，便允许同时运行多少个线程！
	*/
	if (NULL == m_hCOP)
	{
		cout << "CreateIoCompletionPort() failed: " << GetLastError() << endl;
		return FALSE;
	}
	//
	//取得系统中CPU的数目，创建和CPU数目相等的线程，如果事先估计到完成端口处理线程会堵塞，
	//可以考虑创建 SysInfo.dwNumberOfProcessors*2个线程。一般在单处理器上创建和CPU数目相等
	//的线程就可以了
	//
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	if (MAXTHREAD_COUNT < SysInfo.dwNumberOfProcessors)
	{
		SysInfo.dwNumberOfProcessors = MAXTHREAD_COUNT;
	}

	/*
	成功创建一个完成端口后，便可开始将套接字句柄与对象关联到一起。但在关联套接字
	之前，首先必须创建一个或多个“工作者线程”以便在I / O请求投递给完成端口对象
	后，为完成端口提供服务。
	*/
	for (int i=0; i<(int)SysInfo.dwNumberOfProcessors; i++)
	{
		m_hThreadArray[i] = CreateThread(
											NULL,
											0,
											CompletionRoutine,
											(LPVOID)this,
											0,
											NULL
											);

		if (NULL == m_hThreadArray[i])
		{
			while (i>0)
			{
				CloseHandle(m_hThreadArray[i-1]);
				m_hThreadArray[i-1] = INVALID_HANDLE_VALUE;
				i--;
			}//end of while
			cout << "CreateThread() failed: " << GetLastError() << endl;
			
			CloseHandle(m_hCOP);

			HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);
			
			return FALSE;
		}
	}//end of for
	//
	//调用InitWinsock函数初始化Winsock、建立一个监听套接字m_ListenSocket，
	//并将此套接字同完成端口关联起来，获取AcceptEx指针。
	//
	bSuccess = InitWinsock();
	if (!bSuccess)
	{
		//
		//给完成端口线程发送消息，指示线程退出。
		//
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead); 
		return FALSE;
	}
	//
	//调用BindAndListenSocket()绑定套接字并将套接字置于监听状态
	//
	bSuccess = BindAndListenSocket(); 
	if (!bSuccess)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);  
		
		return FALSE;
	}
	return TRUE; 
}//end of Init()



/*++
函数描述:
对每一个创建的线程调用CloseHandle()。
Arguments:
无。
Return Value:
无。
--*/
void CompletionPortModel::CloseThreadHandle()
{
	for (int i=0; i< MAXTHREAD_COUNT; i++)
	{
		if (INVALID_HANDLE_VALUE != m_hThreadArray[i])
		{
			CloseHandle(m_hThreadArray[i]);
			m_hThreadArray[i] = INVALID_HANDLE_VALUE;
		}
	}//end of for
	
	return;
}//end of CloseThreadHandle()



/*++
函数描述:
初始化Winsock,创建一个监听套接字，获取AcceptEx函数指针，为监听套接字分配一个单句柄
数据，并将监听套接字与完成端口hCOP关联。
Arguments:
无。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。
--*/
BOOL CompletionPortModel::InitWinsock()
{
	WSADATA wsd;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsd);
	if (0 != nResult)
	{
		cout << "WSAStartup() failed" << endl;
		
		return FALSE;
	}
	m_ListenSocket = WSASocket(
								AF_INET,
								SOCK_STREAM,
								IPPROTO_IP, 
								NULL,
								0,
								WSA_FLAG_OVERLAPPED
								);
	
	if (INVALID_SOCKET == m_ListenSocket)
	{
		cout << "WSASocket() failed: " << WSAGetLastError() << endl;
		WSACleanup();
		
		return FALSE;
	}
	
	
	DWORD dwResult;
	//
	//获取微软SOCKET扩展函数指针
	//
	nResult = WSAIoctl( 
						m_ListenSocket,
						SIO_GET_EXTENSION_FUNCTION_POINTER,
						&g_GUIDAcceptEx,
						sizeof(g_GUIDAcceptEx),
						&lpAcceptEx,
						sizeof(lpAcceptEx),
						&dwResult,
						NULL,
						NULL
						);
	
	if (SOCKET_ERROR == nResult)
	{
		cout << "Get AcceptEx failed: " << WSAGetLastError() << endl;
		closesocket(m_ListenSocket);
		WSACleanup();
		return FALSE;
	}
	nResult = WSAIoctl( 
						m_ListenSocket,
						SIO_GET_EXTENSION_FUNCTION_POINTER,
						&g_GUIDTransmitFile,
						sizeof(g_GUIDTransmitFile),
						&lpTransmitFile,
						sizeof(lpTransmitFile),
						&dwResult,
						NULL,
						NULL
						);
	
	if (SOCKET_ERROR == nResult)
	{
		cout << "Get TransmitFile failed: " << WSAGetLastError() << endl;
		closesocket(m_ListenSocket);
		WSACleanup();
		
		return FALSE;
	}
	
	//
	//为监听套接字分配一个单句柄数据
	//
	PPER_HANDLE_CONTEXT lpListenHandleContext =
		(PPER_HANDLE_CONTEXT)HeapAlloc(
										GetProcessHeap(),
										HEAP_ZERO_MEMORY, 
										sizeof(PER_HANDLE_CONTEXT)
										);
	if (NULL == lpListenHandleContext)
	{
		closesocket(m_ListenSocket);
		WSACleanup();
		cout << "HeapAlloc() failed " << endl;
		
		return FALSE;
	}
	lpListenHandleContext->IoSocket = m_ListenSocket;
	lpListenHandleContext->pNext = NULL;
	//
	//将监听套接字m_ListenSocket和已经建立的完成端口关联起来
	//
	HANDLE hrc = CreateIoCompletionPort(
										(HANDLE)m_ListenSocket,
										m_hCOP,
										(ULONG_PTR)lpListenHandleContext,
										0
										);

	
	if (NULL == hrc)
	{
		closesocket(m_ListenSocket);
		HeapFree(GetProcessHeap(), 0, lpListenHandleContext);
		WSACleanup();
		cout << "CreateIoCompletionPort failed: " << GetLastError() << endl;
		
		return FALSE;
	}
	return TRUE;
}//end of InitWinsock()



/*++
函数描述:
private函数，供Init调用。
将监听套接字m_ListenSocket绑定到本地IP地址，并置于监听模式。

Arguments:
无。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。
--*/
BOOL CompletionPortModel::BindAndListenSocket()
{
	SOCKADDR_IN InternetAddr;
	InternetAddr.sin_family = AF_INET;
#ifdef _DEBUG
	InternetAddr.sin_addr.s_addr = inet_addr(LOCALADDRESS);
	InternetAddr.sin_port = htons(PORT);   
#else
	InternetAddr.sin_addr.s_addr = inet_addr(szAddress);
	InternetAddr.sin_port = htons(uPort);    
#endif 
	
	int nResult = bind(m_ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr));
	if (SOCKET_ERROR == nResult)
	{
		int nRet = GetLastError();
		WSACleanup();
		closesocket(m_ListenSocket);
		
		cout << "bind() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	} 
	nResult = listen(m_ListenSocket, 20);
	if (SOCKET_ERROR == nResult)
	{
		WSACleanup();
		closesocket(m_ListenSocket);
		cout << "listen() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	}  
	return TRUE;
}//end of BindAndListenSocket()




/*++
函数描述:
完成端口处理线程，循环调用GetQueuedCompletionStatus来获取IO操作结果。
Arguments:
Return Value:
线程退出代码。
--*/
DWORD __stdcall CompletionRoutine(LPVOID Param)
{
	CompletionPortModel* pThis = (CompletionPortModel*)Param;
	DWORD dwNumberBytes;
	PPER_HANDLE_CONTEXT lpHandleContext = NULL;
	LPWSAOVERLAPPED lpOverlapped = NULL;
	int nResult;
	BOOL bSuccess;
	
	while (TRUE)
	{
		bSuccess = GetQueuedCompletionStatus(
												pThis->m_hCOP,		//对应于要在上面等待的完成端口
												&dwNumberBytes,		//负责在完成了一次I / O操作后（如WSASend或WSARecv），接收实际传输的字节数
												(PULONG_PTR )&lpHandleContext,	//为原先传递进入CreateCompletionPort函数的套接字返回“单句柄数据
												&lpOverlapped,		//用于接收完成的I / O操作的重叠结果
												INFINITE	//用于指定调用者希望等待一个完成数据包在完成端口上出现的时间。假如将其设为INFINITE，调用会无休止地等待下去
												);
		
		if (FALSE == bSuccess)
		{
#ifndef _DEBUG
			cout << "GetQueuedCompletionStatus() failed: " << GetLastError() << endl;
#endif
			continue;
		}
		if (NULL == lpHandleContext)
		{
			//
			//PostQueuedCompletionStatus发过来一个空的单句柄数据，表示线程要退出了。
			//
			return 0;
		}
		PPER_IO_CONTEXT lpPerIoContext = (PPER_IO_CONTEXT)lpOverlapped;
#ifdef _DEBUG
		cout << "recv buffer data: " << lpPerIoContext->szBuffer << endl;  
#endif
		
		if(IoAccept != lpPerIoContext->IoOperation)
		{
			if((!bSuccess) || (bSuccess && (0 == dwNumberBytes))) 
			{
				closesocket(lpPerIoContext->sClient);
				lpPerIoContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				lpHandleContext->pNext = NULL;
				pThis->InsertToLookaside(NULL, lpHandleContext);
				
				continue;
			}
		}
		HANDLE hResult;
		PPER_HANDLE_CONTEXT lpNewperHandleContext;
		switch(lpPerIoContext->IoOperation)
		{
		case IoAccept : 
			if (dwNumberBytes)
			{
				//
				//第一次连接成功并且收到了数据,将这个结点从链表中解除
				//
				EnterCriticalSection(&pThis->m_ListCriSection);
				pThis->ReleaseNode(lpPerIoContext);
				LeaveCriticalSection(&pThis->m_ListCriSection);
			}
			nResult = setsockopt(
									lpPerIoContext->sClient, 
									SOL_SOCKET,
									SO_UPDATE_ACCEPT_CONTEXT,
									(char *)&pThis->m_ListenSocket,
									sizeof(pThis->m_ListenSocket)
									);
			
			if(SOCKET_ERROR == nResult) 
			{
				cout << "SO_UPDATE_ACCEPT_CONTEXT failed to update accept socket" << endl;
				closesocket(lpPerIoContext->sClient); 
				lpPerIoContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				
				continue;
			}
			
			lpNewperHandleContext = pThis->GetHandleFromLookaside();
			if (NULL == lpNewperHandleContext)
			{
				lpNewperHandleContext =
					(PPER_HANDLE_CONTEXT)HeapAlloc(
													GetProcessHeap(),
													HEAP_ZERO_MEMORY,
													sizeof(PER_HANDLE_CONTEXT)
													);
				if (NULL == lpNewperHandleContext)
				{
					cout << "HeapAlloc() for lpNewperHandlecontext failed" << endl;
					
					closesocket(lpPerIoContext->sClient);
					lpPerIoContext->pNext = NULL;
					pThis->InsertToLookaside(lpPerIoContext, NULL);
					
					continue;
				}    
			}
			lpNewperHandleContext->IoSocket = lpPerIoContext->sClient;
			lpNewperHandleContext->pNext = NULL;
			
			//
			//将新建立的套接字关联到完成端口
			//
			hResult = CreateIoCompletionPort(
												(HANDLE)lpPerIoContext->sClient,
												pThis->m_hCOP,
												(DWORD_PTR)lpNewperHandleContext,
												0
												);
			
			if (NULL == hResult)
			{
				cout << "CreateIoCompletionPort() failed: " << GetLastError();
				closesocket(lpPerIoContext->sClient);
				lpPerIoContext->pNext = NULL;
				lpNewperHandleContext->pNext = NULL;
				pThis->InsertToLookaside(lpPerIoContext, NULL);
				pThis->InsertToLookaside(NULL, lpNewperHandleContext);
				
				continue;
			}
			if (dwNumberBytes)
			{
				//
				//分析处理数据。
				//
				pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					continue;
				}
			}
			//
			//如果连接成功但是没有收到数据
			//
			else
			{
				pThis->HandleData(lpPerIoContext, IO_ACCEPT_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					continue;
				}
			}
			break;//end of case IoAccept
			
		case IoRead:
			pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				continue;
			}
			break;//end of case IoRead
		case IoWrite:
			pThis->HandleData(lpPerIoContext, IO_WRITE_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				continue;
			} 
			break;
		default:
			continue;
			break;
		}
	}
	return 0;
}//end of CompletionRoutine()



/*++
Fucntion Description:
连续发出10个AcceptEx调用。
Arguments:
Return Value:
函数调用成功返回TRUE，失败返回FALSE。

--*/
BOOL CompletionPortModel::PostAcceptEx()
{
	while (m_lAcceptExCounter < 10)
	{
		SOCKET AcceptSocket = WSASocket(
										AF_INET,
										SOCK_STREAM,
										IPPROTO_IP,
										NULL,
										0,
										WSA_FLAG_OVERLAPPED
										);
		
		if (INVALID_SOCKET == AcceptSocket)
		{
			cout << "WSASocket failed " << endl;
			
			return FALSE;
		}
		PPER_IO_CONTEXT lpAcceptExIoContext = GetIoFromLookaside();
		if (NULL == lpAcceptExIoContext)
		{
			lpAcceptExIoContext = (PPER_IO_CONTEXT)HeapAlloc(
																GetProcessHeap(),
																HEAP_ZERO_MEMORY,
																sizeof(PER_IO_CONTEXT)
																);
			if (NULL == lpAcceptExIoContext)
			{
				cout << "HeapAlloc() failed " << endl;
				closesocket(AcceptSocket);
				
				return FALSE;
			}
		}
		ZeroMemory(&(lpAcceptExIoContext->ol), sizeof(lpAcceptExIoContext->ol));
		lpAcceptExIoContext->sClient = AcceptSocket;
		lpAcceptExIoContext->IoOperation = IoAccept;
		lpAcceptExIoContext->pNext = NULL;
		
		ZeroMemory(lpAcceptExIoContext->szBuffer, BUFFER_SIZE);
		lpAcceptExIoContext->wsaBuffer.buf = lpAcceptExIoContext->szBuffer;
		lpAcceptExIoContext->wsaBuffer.len = BUFFER_SIZE;
		lpAcceptExIoContext->unId = lpAcceptExIoContext->sClient;
		
		DWORD dwBytes;
		BOOL bSuccess = lpAcceptEx(
									m_ListenSocket,
									lpAcceptExIoContext->sClient,
									lpAcceptExIoContext->szBuffer,
									lpAcceptExIoContext->wsaBuffer.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
									sizeof(SOCKADDR_IN) + 16,
									sizeof(SOCKADDR_IN) + 16,
									&dwBytes,
									&(lpAcceptExIoContext->ol)
									);

		if (FALSE == bSuccess)
		{
			int nResult = WSAGetLastError();
			if (nResult != ERROR_IO_PENDING)
			{
				cout << "AcceptEx() failed :" << nResult << endl;
				closesocket(AcceptSocket);
				HeapFree(GetProcessHeap(), 0 , lpAcceptExIoContext);
				
				return FALSE;
			}
			
			InsertNode(lpAcceptExIoContext, NULL); 
			InterlockedExchangeAdd(&m_lAcceptExCounter, 1);
		} 
	}
	InterlockedExchangeAdd(&m_lAcceptExCounter, -10);
	return TRUE;
}//end of PostAccetExRoutine()



/*++
Fucntion Description:
根据参数类型将传递进来结点插入到相应的链表头。
Arguments:
pNode       -  要插入链表中的结点
pHandleNode -  要插入链表中的结点

Return Value:
无.
--*/
void CompletionPortModel::InsertNode(PPER_IO_CONTEXT pNode, PPER_HANDLE_CONTEXT pHandleNode)
{
	if (NULL != pNode)
	{  
		EnterCriticalSection(&m_ListCriSection);
		pNode->pNext = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = pNode;
		LeaveCriticalSection(&m_ListCriSection);
	}
	return;
}//end of InsertNode



/*++
Fucntion Description:

主线程循环，用WaitForSigleObject等待m_hEvent，已经发出的AcceptEx()调用耗尽，FD_ACCEPT
事件将被触发，WaitForSigleObject成功返回，然后调用PostAcceptEx()来新发出10个AcceptEx()调用。
WaitForSigleObject每次等待10秒，超时返回后，对系统中已经建立成功了的并且还没有收发过数据的
SOCKET连接进行检测，如果某个连接已经建立了30秒，并且还没收发过数据，则强制关闭。
Arguments:

无。
Return Value:

函数调用成功返回TRUE，调用失败返回FALSE；

--*/
BOOL CompletionPortModel::ThreadLoop()
{
	int nOptval;
	int nOptlen;
	int nResult;
	DWORD dwResult;
	int nCounter = 0;
#ifdef _DEBUG
	int nTimeOut = 0;
#endif
	cout << "Server is running.........." << nCounter << " times" << endl; 
	
	while (TRUE)
	{  
		dwResult = WaitForSingleObject(m_hEvent, 10000);
		
		if (WAIT_FAILED == dwResult)
		{
			PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
			cout << "WSAWaitForMultipleEvents() failed: " << WSAGetLastError() << endl;
			return FALSE;
		}
		
		if (WAIT_TIMEOUT == dwResult)
		{ 
			nCounter++;
			cout << "Server is running.........." << nCounter << " times" << endl;
			
#ifdef _DEBUG
			nTimeOut++;
			cout << nTimeOut << "*******TIME_OUT********" << nTimeOut << endl;
#endif
			
			PPER_IO_CONTEXT lpCurentNode = m_lpConnectionListHead->pNext;
			PPER_IO_CONTEXT lpPreNode = m_lpConnectionListHead;
			PPER_IO_CONTEXT lpTempNode; 
			
			while (NULL != lpCurentNode)
			{ 
				EnterCriticalSection(&m_ListCriSection);
				nOptlen = sizeof(nOptval);
				
				nResult = getsockopt(
										lpCurentNode->sClient,
										SOL_SOCKET,
										SO_CONNECT_TIME,
										(char*)&nOptval,
										&nOptlen
										);
#ifdef _DEBUG
				cout << "nOptval = " << nOptval << endl;
#endif _DEBUG
				
				if (SOCKET_ERROR == nResult)
				{
					cout << "SO_CONNECT_TIME failed: " << WSAGetLastError() << endl;
					lpPreNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
					LeaveCriticalSection(&m_ListCriSection);
					
					continue;
				}
				if ((nOptval!=0xFFFFFFFF) && (nOptval>30))
				{
					lpPreNode->pNext = lpCurentNode->pNext;
					lpTempNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
					closesocket(lpTempNode->sClient);
					lpTempNode->pNext = NULL;
					InsertToLookaside(lpTempNode, NULL);
				}
				else
				{
					lpPreNode = lpCurentNode;
					lpCurentNode = lpCurentNode->pNext;
				}
				LeaveCriticalSection(&m_ListCriSection);
			}
		}
		else
		{
			if (WAIT_TIMEOUT != dwResult)
			{
				if (FALSE == PostAcceptEx())
				{
					PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
					
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}//end of CheckConnectTime



/*++
Fucntion Description:
将参数中传递的结点从链表中解除,但不释放结点。以便不让ThreadLoop函数对其进行超时检测。
此函数在完成端口线程里收发数据成功后调用。
Arguments:

要从链表中释放的结点。
Return Value:
无。

--*/
void CompletionPortModel::ReleaseNode(PPER_IO_CONTEXT pNode)
{
	PPER_IO_CONTEXT pTempNode = m_lpConnectionListHead->pNext;
	PPER_IO_CONTEXT pPreNode =m_lpConnectionListHead;
	PPER_IO_CONTEXT pDeleteNode;
	
	while (NULL != pTempNode)
	{
		if (pNode->unId == pTempNode->unId)
		{  
			pPreNode->pNext = pTempNode->pNext;
			pDeleteNode = pTempNode;
			pTempNode = pTempNode->pNext;
			
			return;
		}
		else
		{ 
			pPreNode = pTempNode;
			pTempNode = pTempNode->pNext;
		}
	}
	return;
}//end of RealeseNode



/*++
Fucntion Description:
根据传进来的nFlags参数对lpPerIoContext进行设置，并指示下一步IO操作。
Arguments:

lpPerIoContext - 调用GetQueueCompletionStatus函数得到的上一次IO操作的结果(扩展的
WSAOVERLAPPED结构)。
nFlags         - 指明已经完成上一次IO的操作类型。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。

--*/
BOOL CompletionPortModel::HandleData(PPER_IO_CONTEXT lpPerIoContext, int nFlags)
{
	//
	//nFlags == IO_READ_COMPLETION表示完成的上一次IO操作是WSARecv。
	//
	if (IO_READ_COMPLETION == nFlags)
	{
		//
		//完成了WSARecv，接下来需要调用WSASend把刚接收到的数据发送回去，把
		//lpPerIoContext->ContinueAction = ContinueWrite;
		//
		lpPerIoContext->IoOperation = IoWrite;
		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		
		//
		//接收到的数据在lpPerIoContext->wsaBuffer.buf里，可以调用
		//自定义函数对数据自行处理，本例中，简单的将数据再发送回去
		//
		strcpy(lpPerIoContext->szBuffer, lpPerIoContext->wsaBuffer.buf);
		lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;
		
		return TRUE;
	}
	if (IO_WRITE_COMPLETION == nFlags)
	{
		//
		//上一次IO操作WSASend数据发送完成，将后续操作标志设置为关闭
		//如果不需要关闭而是要继续发送，将lpPerIoContext->IoOperation设置为
		//IoWrite，如果要继续接收，将lpPerIoContext->IoOperation设置为
		//IoRead,并初始化好BUFFER,本例中，设置关闭
		//
		lpPerIoContext->IoOperation = IoEnd;
		return TRUE;
	}
	if (IO_ACCEPT_COMPLETION == nFlags)
	{
		//
		//刚建立了一个连接，并且没有收发数据，，，，
		//
		lpPerIoContext->IoOperation = IoRead;
		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
		lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;
		lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		return TRUE;
	}
	
	
	return FALSE;
}// end of HandleData()



/*++
Fucntion Description:
初始化链表头指针。
Arguments:
无。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。

--*/
BOOL CompletionPortModel::InitLinkListHead()
{
	m_lpConnectionListHead = (PPER_IO_CONTEXT)HeapAlloc(
														GetProcessHeap(),
														HEAP_ZERO_MEMORY,
														sizeof(PER_IO_CONTEXT)
														);
	
	if (NULL == m_lpConnectionListHead)
	{
		cout << "HeapAlloc() failed " << endl;
		
		return FALSE;
	}
	m_lpConnectionListHead->pNext = NULL;
	
	return TRUE;
}// end of InitLinkListHead()



/*++
Fucntion Description:
将FD_ACCEPT事件注册到m_hEvent，这样当可用AcceptEx调用被耗尽的时候，就会触发FD_ACCEPT
事件，然后ThreadLoop里的WaitForSingleObject就会成功返回，导致PostAcceptEx被调用。
Arguments:
无。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。

--*/
BOOL CompletionPortModel::AllocEventMessage()
{
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == m_hEvent)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		cout << "CreateEvent() failed: " << GetLastError() << endl;
		return FALSE;
	}
	
	int nResult = WSAEventSelect(m_ListenSocket, m_hEvent, FD_ACCEPT);
	if (SOCKET_ERROR == nResult)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseHandle(m_hEvent);
		cout << "WSAEventSeclet() failed: " << WSAGetLastError() << endl;
		
		return FALSE;
	}
	return TRUE;
}//end of AllocEventMessage()



/*++
Fucntion Description:
根据参数lpPerIoContext的成员IoOperation的值来进行下一步IO操作。
Arguments:

lpPerIoContext        - 将随WSASend或者WSARecv一起投递的扩展WSAOVERLAPPED结构。
lpNewperHandleContext - AcceptEx调用成功后给新套接字分配的"单句柄数据"。
Return Value:
函数调用成功返回TRUE，失败返回FALSE。

--*/
BOOL CompletionPortModel::DataAction(PPER_IO_CONTEXT lpPerIoContext, PPER_HANDLE_CONTEXT lpNewperHandleContext)
{
	int nResult;
	DWORD dwIosize = 0;
	DWORD dwFlags =0;
	if (IoWrite == lpPerIoContext->IoOperation)
	{
		nResult = WSASend(
							lpPerIoContext->sClient,
							&(lpPerIoContext->wsaBuffer),
							1,
							&dwIosize,
							0,
							&(lpPerIoContext->ol),
							NULL
							);
		
		if((SOCKET_ERROR==nResult) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			cout << "WSASend() failed: " << WSAGetLastError() << endl;
			
			closesocket(lpPerIoContext->sClient);
			lpPerIoContext->pNext = NULL;
			lpNewperHandleContext->pNext = NULL;
			InsertToLookaside(lpPerIoContext, NULL);
			InsertToLookaside(NULL, lpNewperHandleContext);
			
			return FALSE;
		}
	}
	
	if (IoRead == lpPerIoContext->IoOperation)
	{
		nResult = WSARecv(
							lpPerIoContext->sClient,
							&(lpPerIoContext->wsaBuffer),
							1,
							&dwIosize,
							&dwFlags,
							&(lpPerIoContext->ol),
							NULL
							);
		
		if((SOCKET_ERROR==nResult) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			cout << "WSARecv() failed: " << WSAGetLastError() << endl;
			
			closesocket(lpPerIoContext->sClient);
			lpNewperHandleContext->pNext = NULL;
			lpPerIoContext->pNext = NULL;
			InsertToLookaside(lpPerIoContext, NULL);
			InsertToLookaside(NULL, lpNewperHandleContext);
			
			return FALSE;
		}
		
	}
	
	if (IoEnd == lpPerIoContext->IoOperation)
	{
		closesocket(lpPerIoContext->sClient);
		lpNewperHandleContext->pNext = NULL;
		InsertToLookaside(NULL, lpNewperHandleContext);
		lpPerIoContext->pNext = NULL;
		InsertToLookaside(lpPerIoContext, NULL);
	}
	return TRUE;
}// end of DataAction()



/*++
Fucntion Description:
由类构造函数调用的函数，用来输入服务器要绑定的本地IP地址和端口。
Arguments:

无。
Return Value:

无。   

--*/
void CompletionPortModel::GetAddressAndPort()
{
	cout << "\nPlease input a port: ";
	cin >> uPort;
	cout << "\nPlease input localaddress:";
	cin >> szAddress;
	system("cls");
	return;
}// end of GetAddressAdnPort




/*++
Fucntion Description:
给旁视列表的链表中插入一个空闲的结点。
Arguments:

lpIoNode     - 要插入的结点，类型为PPER_IO_CONTEXT。
lpHandleNode - 要插入的结点，类型为PPER_HANDLE_CONTEXT。
Return Value:

无。   

--*/
void CompletionPortModel::InsertToLookaside(PPER_IO_CONTEXT lpIoNode, PPER_HANDLE_CONTEXT lpHandleNode)
{
	if (NULL != lpIoNode)
	{
		if (NULL == m_lpIoLookasideLists)
		{
			m_lpIoLookasideLists = lpIoNode;
			
			return;
		}
		lpIoNode->pNext = m_lpIoLookasideLists->pNext;
		m_lpIoLookasideLists->pNext = lpIoNode;
		
		return;
	}
	if (NULL != lpHandleNode)
	{
		if (NULL == m_lpHandleLOOKasideLists)
		{
			m_lpHandleLOOKasideLists = lpHandleNode;
			
			return;
		}
		lpHandleNode->pNext = m_lpHandleLOOKasideLists->pNext;
		m_lpHandleLOOKasideLists->pNext = lpHandleNode;
		
		return;
	}
	return;
}



/*++
Fucntion Description:
从旁视列表中解除一个结点并将其返回。
Arguments:

无。
Return Value:

返回一个PPER_IO_CONTEXT类型的结点。   

--*/
PPER_IO_CONTEXT CompletionPortModel::GetIoFromLookaside()
{
	if (NULL == m_lpIoLookasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_IoCriSection);
	PPER_IO_CONTEXT lpReturnNode = m_lpIoLookasideLists;
	m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
	LeaveCriticalSection(&m_IoCriSection);
	return lpReturnNode;
}



/*++
Fucntion Description:
从旁视列表中解除一个结点并将其返回。
Arguments:

无。
Return Value:

返回一个PPER_HANDLE_CONTEXT类型的结点。   

--*/
PPER_HANDLE_CONTEXT CompletionPortModel::GetHandleFromLookaside()
{
	if (NULL == m_lpHandleLOOKasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_HandleCriSection);
	PPER_HANDLE_CONTEXT lpReturnNode = m_lpHandleLOOKasideLists;
	m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
	LeaveCriticalSection(&m_HandleCriSection);
	
	return lpReturnNode;
}
