#include "comhead.h"
#include "IPCCom.h"
/*************************************************************************
*Role:This file defines the function for network ,include TCP and UDP model
*CoypRight(C):flydish,2004,6,22
*History:
*	Create:By flydish,2004,06,22
*************************************************************************/

/************************************************************************
*The below is for TCP model
*************************************************************************/
/*
void sigalalarm_handler(int signo)
{
    to_flag=1;

}
*/

//Used by client to connect to server
extern "C" SOCKET CreateConnectSocket(char* pszRemoteAddr,int iPort)
{
    int iStatus;
    SOCKADDR sinRemote;
    SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock == INVALID_SOCKET)
	return INVALID_SOCKET ;

    sinRemote.sin_family=AF_INET;
    sinRemote.sin_port=htons(iPort);
    inet_aton(pszRemoteAddr,&sinRemote.sin_addr);
    iStatus = connect(sock,(struct sockaddr *)&sinRemote,sizeof(sinRemote));
    if(iStatus == ERR_SOCKET)
    {
	shutdown(sock,2);
	return INVALID_SOCKET ;
    }
    return sock;
}

//Used by server to accept client call
extern "C" SOCKET CreateAcceptSocket(SOCKET sockListen,char* pszHost, \
	int *piPort)
{
    SOCKADDR sinRemote;
    SOCKET sComm;
    socklen_t iLen=sizeof(sinRemote);
    sComm = accept(sockListen,(struct sockaddr *)&sinRemote,&iLen);
    if(sComm != INVALID_SOCKET)
    {
	if(pszHost)
	    strcpy(pszHost,inet_ntoa(sinRemote.sin_addr));
	if(piPort)
	    *piPort = ntohs(sinRemote.sin_port);
    }
    return sComm;
}

//Used by server to listen client call
extern "C" SOCKET CreateListenSocket(char* pszLocalAddr,unsigned int uPort)
{
    int iStatus;
    SOCKADDR sinLocal;
    SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock==INVALID_SOCKET)
	return INVALID_SOCKET ;

    sinLocal.sin_family=AF_INET;
    sinLocal.sin_port=htons(uPort);
    if(pszLocalAddr )
	inet_aton(pszLocalAddr,&sinLocal.sin_addr);
    else
	sinLocal.sin_addr.s_addr=INADDR_ANY;
    iStatus=bind(sock,(struct sockaddr *)&sinLocal,sizeof(sinLocal));

    if(iStatus==ERR_SOCKET)
    {
	shutdown(sock,2);
	return INVALID_SOCKET ;
    }
    iStatus=listen(sock,15);
    if(ERR_SOCKET==iStatus)
    {
	shutdown(sock,2);
	return INVALID_SOCKET ;
    }
    return sock;
}


//used to receive data form peer
//if iTimeOut=0,No timeout
extern "C" int TCPRecvFromPeer(SOCKET m_sockComm,const int iWant,char* pbBuf, \
	int* iRead,int iTimeOut)
{
    int iReceived=0,iRet;
    int iRecved=0;
    *iRead = 0;

    TIME recvTimeOut;
    recvTimeOut.tv_sec=0;
    recvTimeOut.tv_usec=iTimeOut;
    setsockopt(m_sockComm,SOL_SOCKET,SO_RCVTIMEO,&recvTimeOut,sizeof(TIME));
/*
    
    SIGACTION act;
    act.sa_handler=sigalalarm_handler;
    act.sa_mask=0;
    act.sa_flags=0;
    sigaction(SIGALARM,&act,NULL);

    while(iReceived<iWant)
    {
	
	if((iRet=recv(m_sockComm,pbBuf,iWant-iReceived,0))<0)
	{
	    alarm(0);
	}
	iReceived+=iRet;
	pbBuf=(char*)pbBuf+iReceived;
	
    } 
*/
	
    while(1)
    {
	//alarm(iTimeOut);//Set the timeout
	int iLeft = iWant -iRecved;
	int iRet = recv(m_sockComm,(char*)pbBuf+iRecved,iLeft,0);
	if(iRet<0&&errno==ETIMEDOUT)
	//if(iRet<0&&errno==EWOULDBLOCK)
	{
	    shutdown(m_sockComm,2);
	    return ERR_TIMEOUT;
	}
	if(iRet<0&&errno==EINTR)
	    continue;    
	iRecved += iRet;
	*iRead = iRecved;
	if(iRecved == iWant)
	{
	    return ERR_SUCCESS;
	}
    }
    return ERR_NETWORK;
}

extern "C" int TCPSendToPeer(SOCKET m_sockComm,const int iWant, \
	const char *pbBuf,int* iWrote,int iTimeOut)
{
    int iSent=0;
    *iWrote = 0;
    while(1)
    {
	int iLeft = iWant -iSent;
	int iRet = send(m_sockComm,(char*)pbBuf+iSent,iLeft,0);
	if(iRet ==0 || iRet == ERR_SOCKET  )
	    return ERR_NETWORK;
	iSent += iRet;
	*iWrote = iSent;
	if(iSent == iWant)
	    return ERR_SUCCESS;
    }
    return ERR_NETWORK;
}

/************************************************************************
*The below is for UDP model
*************************************************************************/
extern "C" SOCKET CreateUDPSocket(int iLocalPort,char* pszLocalAddr)
{
    SOCKET sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock == INVALID_SOCKET)
	return INVALID_SOCKET ;

    SOCKADDR sinLocal;
    sinLocal.sin_family=AF_INET;
    sinLocal.sin_port=htons(iLocalPort);
    if(pszLocalAddr )
	inet_aton(pszLocalAddr,&sinLocal.sin_addr);
    else
	sinLocal.sin_addr.s_addr=INADDR_ANY;
    int iStatus=bind(sock,(struct sockaddr *)&sinLocal,sizeof(sinLocal));

    if(iStatus==ERR_SOCKET)
    {
	shutdown(sock,2);
	return INVALID_SOCKET ;
    }
   
    return sock;
}

extern "C" int UDPSendToPeer(SOCKET m_sockComm,const int iWant, \
       const char* pbBuf,int* iWrote,char* pszHost,const int iPort,int iTimeOut)
{
    iWrote = 0;
    SOCKADDR sinRemote;
    sinRemote.sin_family=AF_INET;
    sinRemote.sin_port=htons(iPort);

    inet_aton(pszHost,&sinRemote.sin_addr);
    int iStatus = sendto(m_sockComm,(const char*)pbBuf,iWant,0, \
	(struct sockaddr *)&sinRemote,sizeof(sinRemote));
    if(iStatus ==ERR_SOCKET)
	return ERR_SOCKET;
    *iWrote = iStatus;
    return ERR_SUCCESS;
}

extern "C" int UDPRecvFromPeer(SOCKET m_sockComm,const int iWant, \
	const char* pbBuf,int* iRead,char* pszHost,int *piPort,int iTimeOut)
{
    iRead = 0;
    SOCKADDR sinRemote;
    socklen_t iLen = sizeof(sinRemote);
    int iStatus = recvfrom(m_sockComm,(char*)pbBuf,iWant,0, \
    	(struct sockaddr *)&sinRemote,&iLen);

    if(ERR_SOCKET == iStatus)
	return ERR_SOCKET;
    *iRead = iStatus;
    if(pszHost)
	strcpy(pszHost,inet_ntoa(sinRemote.sin_addr));
    if(piPort)
	*piPort = ntohs(sinRemote.sin_port);
    return ERR_SUCCESS;
}
