#include "Socket.h"

extern "C" int  TCPRecvFromPeer(Socket sock,void* pBuf,long iDataLen,long* iRead)
{
    char* p = (char*)pBuf;
    int iLeft = iDataLen;
    while(iLeft != 0)
    {
        int iReceived=recv(sock,p,iLeft,0);
        if(iReceived<0 && errno ==ETIMEDOUT)
        {
            shutdown(sock,2);
            *iRead = iDataLen-iLeft;
            throw CSocketException("Received Timeout");
        }
        if(iReceived<0 && errno == EINTR)
            continue;
        iLeft-=iReceived;
        p+=iReceived;
    }

    *iRead = iDataLen-iLeft;
    return iDataLen-iLeft;

}
extern "C" int  TCPSendToPeer(Socket sock,void* pBuf,long iDataLen,long* iWrite)
{
    char* p = (char*)pBuf;
    int iLeft = iDataLen;
    while(iLeft !=0)
    {
        int iSend=send(sock,p,iLeft,0);
        if(iSend < 0)
        {
            if(errno == EINTR)
                continue;
            {
            	shutdown(sock,2);
                *iWrite = iDataLen - iLeft;
                throw CSocketException("Send Data Error");
            }
        }

        iLeft-=iSend;
        p+=iSend;
    }
    *iWrite = iDataLen - iLeft;
    return iDataLen-iLeft;

}

//===============================================================
//         The implementation of CSocket                       //
//===============================================================
CSocket::CSocket()
{
    Create();
    m_SocketState = issNotASocket;
    m_IsBlock = true;
}

CSocket::CSocket(CSocket* pSocket)
{
    assert(pSocket != NULL);
    m_Socket = pSocket->GetSocket();
    m_SocketState = pSocket->GetSocketState();
    m_IsBlock = pSocket->IsBlock();
}

CSocket::~CSocket()
{
}

void CSocket::Create()
{
    if((m_Socket = socket(AF_INET,SOCK_STREAM,0))<0)
	throw CSocketException(strerror(errno),__FILE__,__LINE__);
}

void CSocket::Create(int domain, int type, int protocol)
{
    if((m_Socket = socket(domain,type,protocol))<0)
	throw CSocketException(strerror(errno),__FILE__,__LINE__);
}

void CSocket::SetBlock(bool bBlock)
{
    int flag = fcntl(m_Socket, F_GETFL);
    if (flag < 0)
	throw CSocketException(strerror(errno), __FILE__, __LINE__);

    if (bBlock)
	flag &= ~O_NONBLOCK;
    else
	flag |= O_NONBLOCK;
		
    if (fcntl(m_Socket, F_SETFL, flag) < 0)
	throw CSocketException(strerror(errno), __FILE__, __LINE__);
		
    m_IsBlock = bBlock;    
}
//==================================================================
//                The implementation of CClientSocket             //
//==================================================================
CClientSocket::CClientSocket():CSocket()
{
    m_RemoteAddress = new char[100];
}

CClientSocket::~CClientSocket()
{
    Close();
    delete m_RemoteAddress;
}

void CClientSocket::Connect()
{
    if(m_RemoteAddress == NULL)
	throw CSocketException("Server Address is NULL");	
    if(m_RemotePort <=0)
	throw CSocketException("Server Port illegal");
    if(m_Socket == INVALID_SOCKET)
	throw CSocketException("Invalid Socket");

    sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_port   = htons(m_RemotePort);
    inet_aton(m_RemoteAddress,&remoteaddr.sin_addr);

    int iStatus = connect(m_Socket,(struct sockaddr*)&remoteaddr,sizeof(remoteaddr));
    if(iStatus < 0 )
    {
	Close();
	throw CSocketException("Can't connect to server");
    }    
    m_SocketState = issConnected;
}

int CClientSocket::SendToPeer(void* pBuf,long iDataLen,long* iWrite)
{
    if(m_SocketState != issConnected)
        throw CSocketException("Socket has not been connected");
    if(NULL == pBuf || iDataLen ==0)
        return 0;

    return TCPSendToPeer(m_Socket,pBuf,iDataLen,iWrite);
}

int CClientSocket::RecvFromPeer(void* pBuf,long iDataLen,long* iRead)
{
    if(m_SocketState != issConnected)
        throw CSocketException("Socket has not been connected");
    if(NULL == pBuf || iDataLen ==0)
        return 0;

    return TCPRecvFromPeer(m_Socket,pBuf,iDataLen,iRead);
}

//=================================================================
//                The implementation of CServerSocket            //
//=================================================================
CServerSocket::CServerSocket()
{
    Create();
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::ReusePort(void)
{
    int i=1;
    setsockopt(m_Socket,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
}
//================================================================
void CServerSocket::Bind(void)
{
    struct sockaddr_in  servaddr;
    unsigned long addr;

    if(m_Socket == INVALID_SOCKET)
	throw CSocketException("Invalid Socket");
    
    memset(&servaddr,0x0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(GetLocalPort());
    
    int bindvalue = bind(m_Socket,(sockaddr*)&servaddr,sizeof(servaddr));
    if(bindvalue == 0)
	m_SocketState = issBound;
    else
	throw CSocketException("Socket Bind Error");
}
//==========================================================
void CServerSocket::Listen(int iPort)
{
    SetLocalPort(iPort);
    Bind();

    if(m_Socket == INVALID_SOCKET)
	throw CSocketException("Invalid Socket");

    if(m_SocketState != issBound)
	throw CSocketException("Socket Not Bind");

    int listenvalue = listen(m_Socket,5);
    if(listenvalue == 0)
	m_SocketState = issListening;
    else
	throw CSocketException("Socket Listen Error");
}
//==========================================================
CAcceptSocket* CServerSocket::Accept(void)
{
    if(m_Socket == INVALID_SOCKET)
	throw CSocketException("Invalid Socket");

    if(m_SocketState != issListening)
	throw CSocketException("Socket is not listening");

    Socket acceptsocket;
    struct sockaddr_in clientaddr;
    int addrlen = sizeof(clientaddr);
    
    acceptsocket = accept(m_Socket,(sockaddr*)&clientaddr,(socklen_t*)&addrlen);
    if(acceptsocket != INVALID_SOCKET)
    {
	CAcceptSocket* newSocket = new CAcceptSocket();
	newSocket->SetSocket(acceptsocket);
	newSocket->SetRemotePort(ntohs(clientaddr.sin_port));	
	char* remoteaddr = inet_ntoa(clientaddr.sin_addr);
	if(remoteaddr)
	    newSocket->SetRemoteAddress(remoteaddr);
	else
	    newSocket->SetRemoteAddress(NULL);
	newSocket->SetSocketState(issConnected);
	return newSocket;
    }
    else
	throw CSocketException("Socket Accept Error");
}

//===========================================================
//        The implementation of CAcceptSocket              //
//===========================================================
CAcceptSocket::CAcceptSocket()
{
    //m_Socket = iAcceptSocket;
    //m_AcceptSocket = new CAcceptSocket();
}

CAcceptSocket::~CAcceptSocket()
{
    if(m_RemoteAddress != NULL)
	free(m_RemoteAddress); 
}

void CAcceptSocket::SetRemoteAddress(char* strRemoteAddr)
{
    if(strRemoteAddr == NULL)
	m_RemoteAddress = NULL;
    else
    {
	m_RemoteAddress =(char*)malloc(sizeof(strRemoteAddr));
	strcpy(m_RemoteAddress,strRemoteAddr);
    } 
}

int  CAcceptSocket::RecvFromPeer(void* pBuf,long iDataLen,long* iRead)
{
    if(m_SocketState != issConnected)
        throw CSocketException("Socket has not been connected");

    if(NULL == pBuf || iDataLen ==0)
        return 0;
    return TCPRecvFromPeer(m_Socket,pBuf,iDataLen,iRead);
}

int CAcceptSocket::SendToPeer(void* pBuf,long iDataLen,long* iWrite)
{
    if(m_SocketState != issConnected)
        throw CSocketException("Socket has not been connected");

    if(NULL == pBuf || iDataLen ==0)
        return 0;
    return TCPSendToPeer(m_Socket,pBuf,iDataLen,iWrite);
}

