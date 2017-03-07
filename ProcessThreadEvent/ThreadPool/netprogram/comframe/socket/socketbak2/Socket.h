#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "../exception/Exception.h"

#define INVALID_SOCKET	-1
#define MAXBACKLOG	20
typedef int	Socket;

extern "C" int	TCPRecvFromPeer(Socket sock,void* pBuf,long iDataLen,long* iRead);
extern "C" int	TCPSendToPeer(Socket sock,void* pBuf,long iDataLen,long* iWrite);

//======================================================
class CSocket
{
protected:
    typedef enum
    {
	issNotASocket = 0,
	issInitializing,
	issInitialized,
	issBound,
	issConnected,
	issListening,
	issConnecting
    } SocketState;

protected:
    Socket	m_Socket;
    SocketState m_SocketState;
    bool	m_IsBlock;
    
public:
    CSocket();
    CSocket(CSocket* pSocket);
    virtual ~CSocket();

    Socket	GetSocket(void){return m_Socket;}
    SocketState GetSocketState(void){return m_SocketState;}
    void	SetSocketState(SocketState eSocketState){m_SocketState = eSocketState;}
    bool	IsBlock(void){return m_IsBlock;}

    void	Create();
    void	Create(int domain, int type, int protocol = 0);

    void	SetBlock(bool bBlock);
    void	Close(void){shutdown(m_Socket,2);}
};

//========================================================
class CClientSocket:public CSocket
{
private:
protected:
    char*	m_RemoteAddress;
    int		m_RemotePort;
public:
    CClientSocket();
    ~CClientSocket();

    void	SetRemoteAddress(char* strRemoteAddress){
	strcpy(m_RemoteAddress,strRemoteAddress);
    }
    char*	GetRemoteAddress(void){
	return m_RemoteAddress;
    }

    void	SetRemotePort(int iRemotePort){m_RemotePort = iRemotePort;}
    int		GetRemotePort(void){return m_RemotePort;}

    void	Connect();
    int		RecvFromPeer(void* pBuf,long iDataLen,long* iRead);
    int		SendToPeer(void* pBuf,long iDataLen,long* iWrite);
};

//========================================================
class CAcceptSocket;
class CServerSocket:public CSocket
{
private:
    int		m_LocalPort;	
    int		m_BackLog;	
    //CAccpetSocket* m_AcceptSocket;
protected:
    void	Bind(void);
public:
    CServerSocket();
    ~CServerSocket();

    int		GetLocalPort(void){return m_LocalPort;}
    void	SetLocalPort(int iPort){m_LocalPort = iPort;}

    void	ReusePort(void);
    void	Listen(int iPort);
    CAcceptSocket*	Accept(void);
   
    //int		RecvFromPeer(void* pBuf,long iDataLen,long* iRead);
    //int		SendToPeer(void* pBuf,long iDataLen,long* iWrite);
};

class CAcceptSocket:public CSocket
{
protected:
    Socket	m_Socket;
    int		m_RemotePort;
    char*	m_RemoteAddress;
public:
    CAcceptSocket();
    ~CAcceptSocket();

    Socket	GetSocket(){return m_Socket;}
    void	SetSocket(Socket iSocket){m_Socket = iSocket;}
    int		GetRemotePort(void){return m_RemotePort;}
    void	SetRemotePort(int iPort){m_RemotePort = iPort;}
    char*	GetRemoteAddress(void){return m_RemoteAddress;}
    void	SetRemoteAddress(char* strRemoteAddr);

    int		RecvFromPeer(void* pBuf,long iDataLen,long* iRead);
    int		SendToPeer(void* pBuf,long iDataLen,long* iWrite);
};

#endif
