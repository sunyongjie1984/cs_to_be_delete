#include "comhead.h"
#include "IPCCom.h"
/*
extern "C" SOCKET CreateAcceptSocket(SOCKET sockListen,char* pszHost, \
        int *piPort);
extern "C" SOCKET CreateListenSocket(char* pszLocalAddr,unsigned int uPort);
extern "C" int TCPRecvFromPeer(SOCKET m_sockComm,const int iWant, \
        char* pbBuf,int* iRead,int iTimeOut);
*/

main()
{
    SOCKET sock;
    char pszHost[20],pszMsg[1024];
    int iPort,iRead,iWrote;
    sock=CreateListenSocket("127.0.0.1",9090);
    SOCKET acceptSocket=CreateAcceptSocket(sock,pszHost,&iPort);
    printf("Host is:	%s\n",pszHost);
    printf("Port is:	%d\n",iPort);

    TCPRecvFromPeer(acceptSocket,1024,pszMsg,&iRead,0);
    printf("pszMsg:%s\n",pszMsg);
    TCPSendToPeer(acceptSocket,1024,"woshishen",&iWrote,0);
}
