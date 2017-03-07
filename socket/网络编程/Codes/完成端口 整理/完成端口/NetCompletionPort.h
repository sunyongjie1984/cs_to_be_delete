#ifndef _COMPLETIONPORT_H
#define _COMPLETIONPORT_H

#include <winsock2.h>
#include <mswsock.h>
#include <process.h>
#include <vector>
#include <map>
#include <deque>
#include <set>

#define MAX_MEM_COUNT   1000
#define MAX_BUF         1024
#define RECV_COUNT      5

#pragma pack (push)
#pragma pack (1)

enum
{
	IO_ACCEPT,
	IO_READ,
	IO_WRITE,
	IO_END,
};

enum
{ 
	IO_SEND,
	IO_RECV
};


//单IO数据
typedef struct _PER_IO_CONTEXT
{
	WSAOVERLAPPED ol;
	char buf[MAX_BUF];
	WSABUF wsabuf;
	SOCKET sClient;
	DWORD id;
	BYTE IoOperation;
}PER_IO_CONTEXT,*LPPER_IO_CONTEXT;

//完成键（单句炳数据）
typedef struct _PER_HANDLE_CONTEXT
{
	SOCKET IoSocket;

}PER_HANDLE_CONTEXT,*LPPER_HANDLE_CONTEXT;

static GUID g_GUIDAcceptEx             = WSAID_ACCEPTEX;
static GUID g_GUIDGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;

class WorkThread
{
private:
	HANDLE m_hThread;
	unsigned int  m_nThreadID;
	unsigned int (__stdcall*pnThreadFun)(LPVOID param);
	void* m_pParam;
public:
	WorkThread();
	WorkThread(unsigned int (__stdcall*pnThreadFun)(LPVOID param),void* param);
	~WorkThread();
	bool Init();
	void Start();
	void Stop();
	void SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	void SetPriority(int priority);
};

class NetClient 
{
public:
	SOCKET m_socket;
	SOCKADDR_IN m_address;
	LPPER_HANDLE_CONTEXT m_pComKey;
	NetClient();
	NetClient(int socket);
	~NetClient();
	void SendPacket(void* pData,bool encrypt = TRUE);
	void Disconnect();
};

class NetCompletionPort
{
private:
	LPFN_ACCEPTEX m_pAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS m_pGetAcceptExSockaddrs;
	HANDLE m_comPort;
	int    m_port;
	SOCKET m_listenSocket;
	HANDLE m_hEventListen;
	bool m_isCreate;

	std::vector<WorkThread*>* m_pWorkThreadList;
	WorkThread* m_pThreadAccept;

	bool InitWinSock();
	bool InitListenSocket();
	bool InitListenEvent();
	bool InitWorkThread();
	
	std::map<int,NetClient*>* m_pClientList;
	CRITICAL_SECTION m_clientListSection;
	void DeleteClient(NetClient* pClient);
	void AddClient(NetClient* pClient);
	NetClient* GetClient(int socket);
	
	std::set<LPPER_IO_CONTEXT>* m_pConnectList;
	CRITICAL_SECTION m_conSection;
	void InsertConnect(LPPER_IO_CONTEXT pConnect);
	void ReleaseConnect(int socket);
	
	std::deque<LPPER_IO_CONTEXT>* m_pIoMemList;
	std::deque<LPPER_HANDLE_CONTEXT>* m_pHandleMemList;
	CRITICAL_SECTION m_ioMenListSection;
	CRITICAL_SECTION m_hdMemListSection;
	LPPER_IO_CONTEXT GetIoMem();
	LPPER_HANDLE_CONTEXT GetHandleMem();
	void InsertIoMem(LPPER_IO_CONTEXT pMem);
	void InsertHandleMem(LPPER_HANDLE_CONTEXT pMem);

	bool PostAcceptEx();
	
protected:
public:
	NetCompletionPort();
	virtual ~NetCompletionPort();
	bool StartServer(int port);
	void StopServer();

	virtual bool Disconnect(int socket);
	void SendPacket(int socket,void * pData,bool encrypt = TRUE);
	virtual void EncryptPacket(void * pData,int & length,BYTE type,bool encrypt = TRUE);
	virtual void RecvData(void * pData,NetClient* pClient);
	
	void AcceptEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte);
	void SendEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte);
	void RecvEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd,DWORD dwByte);
	void CloseEvent(LPPER_IO_CONTEXT pIo,LPPER_HANDLE_CONTEXT pHd);

	static unsigned __stdcall WorkThreadFun(LPVOID param);
	static unsigned __stdcall AcceptThreadFun(LPVOID param);
	
};

#pragma pack (pop)

#endif