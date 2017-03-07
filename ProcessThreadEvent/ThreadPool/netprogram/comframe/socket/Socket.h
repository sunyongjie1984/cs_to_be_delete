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
#define LASE_ERROR	errno
typedef int	Socket;

//====================================================
//                Define Network Error  Code         //
//====================================================
#define  Error_Success                  0
#define  Error_InvalidSocket            1
#define  Error_InvalidAddress           2
#define  Error_NotInitialized           3
#define  Error_Bind                     4
#define  Error_Listen                   5
#define  Error_Connect		        6
#define  Error_SocketState              7
#define  Error_SendData                 8
#define  Error_ReceiveData              9
#define  Error_SendTo                   10
#define  Error_ReceiveFrom              11
#define  Error_Accept			12


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
    void	Close(void){close(m_Socket);}
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
    virtual ~CClientSocket();

    void	SetRemoteAddress(char* strRemoteAddress);
    char*	GetRemoteAddress(void){
	return m_RemoteAddress;
    }

    void	SetRemotePort(int iRemotePort){m_RemotePort = iRemotePort;}
    int		GetRemotePort(void){return m_RemotePort;}

    int		Connect();
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
protected:
    int		Bind(void);
public:
    CServerSocket();
    virtual ~CServerSocket();

    int		GetLocalPort(void){return m_LocalPort;}
    void	SetLocalPort(int iPort){m_LocalPort = iPort;}

    void	ReusePort(void);
    int 	Listen(int iPort);
    CAcceptSocket*	Accept(void);
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

    void	Close(void){close(m_Socket);}
};

#endif
