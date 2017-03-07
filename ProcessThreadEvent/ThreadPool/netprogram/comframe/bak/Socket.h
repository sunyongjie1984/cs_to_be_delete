#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "comhead.h"
#include <sys/ioctl.h>
//====================================================
//              Const value define                   //
//====================================================
#define MAXBACKLOG		10
#define LAST_ERROR 		errno
#define SOCKET_ERROR		-1
//====================================================
//                Define Network Error  Code         //
//====================================================
#define  Error_Success			0
#define  Error_InvalidSocket		1
#define  Error_InvalidAddress		2
#define  Error_NotInitialized		3
#define  Error_Bind			4
#define  Error_Listen			5
#define  Error_ConnectFailure		6
#define  Error_SocketState		7
#define  Error_SendData			8
#define  Error_ReceiveData		9
#define  Error_SendTo			10
#define  Error_ReceiveFrom		11

typedef int Socket;

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

typedef enum
{
    isdOutgoing, 
    isdIncoming
} SocketDir; 

typedef enum
{
    istStream,
    istDatagram
} SocketType;

typedef enum 
{
    issClient, 
    issServer
} SocketSide; 

/////////////////////////////////////////////////////////
//                CAddress                             //
/////////////////////////////////////////////////////////
class CAddress
{
private:
    int   AddressConvert(char* address,struct in_addr* inaddr);
protected:
    char* m_HostName;
    char* m_NetAddress; //such 202.117.15.112 or www.xjtu.edu.cn
    int   m_Port;
public:
    void  SetHostName(char* hostname){strcpy(m_HostName,hostname);}
    char* GetHostName(void){return m_HostName;}

    void  SetNetAddress(char* netaddress){strcpy(m_NetAddress,netaddress);}
    char* GetNetAddress(void){return m_NetAddress;}

    void  SetPort(int port){m_Port = port ;}
    int   GetPort(void){return m_Port;}

    char* GetIPFromHost(char* host);
    char* GetDomainFromHost(char* host);
    char* GetHostFromAddr(char* addr);
};

///////////////////////////////////////////////////////////////////////
//                     CSocket                                       //
///////////////////////////////////////////////////////////////////////
class CSocket
{
private:
    Socket m_Socket;
    SocketState m_SocketState;
    SocketDir   m_SocketDir;
    SocketType  m_SocketType;
    SocketSide  m_SocketSide; 

    char*  m_LocalAddress;
    int    m_LocalPort;
    char*  m_RemoteAddress;
    int    m_RemotePort;
protected:
    //the buf is used to save data received from client
    struct {
	void* Data;
	long Len;
       	long Size;
    } m_IncomingBuf;

public:
    CSocket(void);
    virtual ~CSocket(void);

    Socket	 GetSocket(void){return m_Socket;}
    void	 SetSocket(Socket sock){m_Socket = sock;}
 
    SocketState  GetSocketState(void){return m_SocketState;}
    void	 SetSocketState(SocketState sockstate){m_SocketState = sockstate;}

    SocketDir	 GetSocketDir(void){return m_SocketDir;}
    void	 SetSocketDir(SocketDir sockdir){m_SocketDir = sockdir;} 
    
    char*	 GetLocalAddress(void){return m_LocalAddress;}
    void	 SetLocalAddress(char* laddress){strcpy(m_LocalAddress,laddress);}

    char*	 GetRemoteAddress(void){return m_RemoteAddress;}
    void	 SetRemoteAddress(char* raddress){strcpy(m_RemoteAddress,raddress);}

    int		 GetLocalPort(void){return m_LocalPort;}
    void	 SetLocalPort(int lport){m_LocalPort = lport;}
   	
    int		 GetRemotePort(void){return m_RemotePort;}
    void	 SetRemotePort(int rport){m_RemotePort = rport;}

    ///////////////////////////////////
    //Client Side
    virtual int      Connect(void);
    virtual int      AsyncConnect(void);// 
    virtual void     FinishAsyncConnect(void);

    //Server Side
    virtual int      Bind(void);
    virtual int      Listen(int BackLog);
    virtual CSocket* Accept(void);
    virtual int      ReusePort();

    //Both
    virtual CSocket* CreateSocket(void){return new CSocket;}
    virtual int      AfterConnection(void);
    virtual int      Close(bool Forced);
    static  void     FinalizeWinSock(void);
    static  void     InitializeWinSock(void);

    virtual int      Send(void* Data, long DataLen, long* Sent);
    virtual int      SendTo(void* Data, long DataLen, long& Sent, char* RemoteAddress,
		                        unsigned int RemotePort); 
    virtual int      Receive(void* Data, long DataLen, long* Received);
    virtual int      ReceiveFrom(void* Data, long DataLen, long& Received, char*& RemoteAddress,
		                        unsigned int& RemotePort);
};

#endif
