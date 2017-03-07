#include "Socket.h"

int   CAddress::AddressConvert(char* address,struct in_addr* inaddr)
{
    struct hostent* he;
    //if the address is as the format 202.117.15.11
    if(inet_aton(address,inaddr) == 1)
	return 1;
    //otherwise 
    he = gethostbyname(address);
    if(he != NULL)
    {
	*inaddr = *(struct in_addr*)he->h_addr_list[0];
	return 1;
    }
    return 0;
}

char* CAddress::GetIPFromHost(char* host)
{
    struct sockaddr_in addr;
    struct hostent  *he;
    
    return NULL;
}

char* CAddress::GetDomainFromHost(char* host)
{
    return NULL;
}

//Get host name from addr such as 202.117.10.1 or www.xjtu.edu.cn
char* CAddress::GetHostFromAddr(char* addr)
{
    struct in_addr inaddr;
    struct hostent *he;
    if(AddressConvert(addr,&inaddr) == 1) 
    {
	he = gethostbyaddr(&inaddr,4,AF_INET);
	return he->h_name;
    }
    else
	return NULL;
}

////////////////////////////////////////////////////////////
//              The implementation of CSocket             //
////////////////////////////////////////////////////////////

CSocket::CSocket(void)
{
}

CSocket::~CSocket(void)
{
}

//==============================================================
//               Server   Side    Function                     //
//==============================================================

int CSocket::Bind(void)
{
    struct sockaddr_in  servaddr;
    unsigned long addr;
    struct hostent* he;

    if(m_Socket == INVALID_SOCKET)
	return Error_InvalidSocket;
   
    if(NULL != GetLocalAddress())
	addr = inet_addr(GetLocalAddress());
    else
    {
	he = gethostbyname(GetLocalAddress());
	if(he)
	    memmove(&addr,&he->h_addr[0],sizeof(addr));
    }
    if( addr == INADDR_NONE )
	return Error_InvalidAddress;
    //if the address is valid ,such as 202.117.15.11 or bbs.xjtu.edu.cn
    memset(&servaddr,0x0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = addr;
    servaddr.sin_port = htons(GetLocalPort());
   
    int bindvalue = bind(m_Socket,(sockaddr*)&servaddr,sizeof(servaddr));
    //bind successful
    if(bindvalue == 0)
    {
	m_SocketState = issBound;	
	return Error_Success;
    } 
    else
	return Error_Bind;
}

int CSocket::Listen(int BackLog)
{
    if(m_Socket == (long)INVALID_SOCKET)
	return Error_InvalidSocket;	
    //If the socket has not been binded 
    //First should bind the socket
    if(m_SocketState != issBound)
    {
        int bindvalue = Bind();
	if(bindvalue != Error_Success)
	    return bindvalue;
    }
    if(BackLog > MAXBACKLOG)
	BackLog = MAXBACKLOG;
    
    int listenvalue = listen(m_Socket, BackLog);
    if(listenvalue == 0)
    {
	m_SocketState = issListening;
	return Error_Success;
    }
    else
	return Error_Listen; 
}


//Accept the connection from the client and return the
//socket of client
CSocket* CSocket::Accept(void)
{
    Socket acceptsocket;
    struct sockaddr_in clientaddr;
    int addrlen = sizeof(clientaddr);
    CSocket* newsocket;

    if(m_SocketState != issListening)
	return NULL;
    acceptsocket = accept(m_Socket, (sockaddr*)&clientaddr, (socklen_t*)&addrlen);
    if(acceptsocket != INVALID_SOCKET)
    {
	newsocket = CreateSocket();	
	newsocket->m_Socket = acceptsocket;
	newsocket->m_SocketDir = isdIncoming;
	newsocket->SetRemotePort(ntohs(clientaddr.sin_port));	
	char* remoteaddr = inet_ntoa(clientaddr.sin_addr);
	if(remoteaddr)
	    newsocket->SetRemoteAddress(remoteaddr);	
	else
	    newsocket->SetRemoteAddress(NULL);	
	//=======================================
	newsocket->m_SocketState = issConnected;
	return newsocket;
    }
    else
	return NULL;
}

//==========================================================//
//            Client   Side  Function                       //
//==========================================================//
//Connect to the server side
int CSocket::Connect(void)
{
    if(m_Socket == INVALID_SOCKET)
	return Error_InvalidSocket;
    if(m_SocketState != issInitialized)
	return Error_NotInitialized;
    
    unsigned long remoteaddr = inet_addr(GetRemoteAddress());
    if(remoteaddr == INADDR_NONE)
    {
	struct hostent* HostEnt = gethostbyname(GetRemoteAddress());
	if(HostEnt)
	    memmove(&remoteaddr, &HostEnt->h_addr[0], sizeof(remoteaddr));
    }
    else
	return Error_InvalidAddress; 
    
    struct sockaddr_in servaddr;
    memset(&servaddr,0x0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = remoteaddr;
    servaddr.sin_port = htons(GetRemotePort());
    
    int connectresult = connect(m_Socket,(sockaddr*)&servaddr,sizeof(servaddr)); 
    if(connectresult == 0)
    {
	//if connect success the fill the localaddress and localport	
	//the orginal address and port is not set
	if(GetLocalAddress() || (GetLocalPort() == 0))
	{
	    struct sockaddr_in tmpaddr;
	    memset(&tmpaddr,0x0,sizeof(tmpaddr));
	    tmpaddr.sin_family = AF_INET;
	    int i=sizeof(tmpaddr);
	    if(getsockname(m_Socket,(sockaddr*)&tmpaddr,(socklen_t*)&i)==0)
	    {
		SetLocalPort(ntohs(tmpaddr.sin_port));
		struct in_addr addr;
		addr.s_addr = tmpaddr.sin_addr.s_addr;
		SetLocalAddress(inet_ntoa(addr));
	    }
	}
	m_SocketState = issConnected;
    }
    else
	return Error_ConnectFailure;
}

int CSocket::AsyncConnect(void)
{
    if(m_Socket == INVALID_SOCKET)
	return Error_InvalidSocket;
    if(m_SocketState != issInitialized)
	return Error_NotInitialized;

    struct sockaddr_in servaddr;
    
    if(issInitialized == m_SocketState)
    {
        servaddr.sin_addr.s_addr = INADDR_NONE;
        unsigned long addr = inet_addr(GetRemoteAddress());
	if(addr == INADDR_NONE)
	{
	    struct hostent  *HostEnt = gethostbyname(GetRemoteAddress());
	    if(HostEnt)
	    memmove(&addr, &HostEnt->h_addr[0], sizeof(addr));
	}
	else
	    return Error_InvalidAddress;
  
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = addr;
	servaddr.sin_port = htons(GetRemotePort());
        u_long arg = 1;
	//ioctlsocket(FSocket, FIONBIO, &arg); //set non-blocking IO
	ioctl(m_Socket, FIONBIO, &arg); //set non-blocking IO
        int connectvalue = connect(m_Socket, (sockaddr*)&servaddr, sizeof(servaddr));
	if (0 != connectvalue)
	    return Error_ConnectFailure;
        else
	{
            m_SocketState = issConnecting;
	    return Error_Success;
	}
    }
    else
	return Error_NotInitialized;
}
//===========================================================
//      Both Function Used In Both Server and client        //
//===========================================================
int CSocket::Send(void* Data, long DataLen, long* Sent)
{
    int sendvalue;
    if(m_SocketState != issConnected)
	return Error_SocketState;

    sendvalue = send(m_Socket,(char*)Data, DataLen, 0);
    if(sendvalue == SOCKET_ERROR)
    {
	*Sent = 0;
        sendvalue = LAST_ERROR;
    }
    else
    {
	*Sent = sendvalue;
	sendvalue=0;
    }
    return sendvalue;
}
//DataLen is the num we wish to receive one time
//Received is the actual num we receive from client
int CSocket::Receive(void* Data, long DataLen, long* Received)
{
    int receivevalue=0;
    if(m_SocketState != issConnected)
	return Error_SocketState;
	
    if (NULL == Data || 0 == DataLen)
	return 0;

    //If the is some data in the buffer
    if (0 != m_IncomingBuf.Len)
    {
        receivevalue = 0;
        *Received = DataLen < m_IncomingBuf.Len ? DataLen : m_IncomingBuf.Len;
        memmove(Data, m_IncomingBuf.Data, *Received);
        if (*Received != m_IncomingBuf.Len)
        {
            memmove(m_IncomingBuf.Data, (char*)m_IncomingBuf.Data + *Received, m_IncomingBuf.Len - *Received);
            m_IncomingBuf.Len -= *Received;
        }
        else
        {
            m_IncomingBuf.Len = 0;
        }
     
    }
    else
    {
        receivevalue = recv(m_Socket, (char*)Data, DataLen, 0);
	if(receivevalue == SOCKET_ERROR)
	{ 
	    *Received = 0;
	    return Error_ReceiveData;
	}
	else
	{
	    *Received = receivevalue;
	    receivevalue = 0;
	}
    }
    return receivevalue;
}
main()
{
    //printf("%s\n",addr.GetHostFromAddr("202.117.15.114"));
    printf("%d",10);
}
