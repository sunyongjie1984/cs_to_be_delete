#ifndef _IPCCOM_H_
#define _IPCCOM_H_

extern "C" SOCKET CreateConnectSocket(char* pszRemoteAddr,int iPort);
extern "C" SOCKET CreateAcceptSocket(SOCKET sockListen,char* pszHost, \
        int *piPort);
extern "C" SOCKET CreateListenSocket(char* pszLocalAddr,unsigned int uPort);

extern "C" int TCPRecvFromPeer(SOCKET m_sockComm,const int iWant, \
        char* pbBuf,int* iRead,int iTimeOut);
extern "C" int TCPSendToPeer(SOCKET m_sockComm,const int iWant, \
        const char *pbBuf, int* iWrote,int iTimeOut);

extern "C" SOCKET CreateUDPSocket(int iLocalPort,char* pszLocalAddr);

extern "C" int UDPSendToPeer(SOCKET m_sockComm,const int iWant, const \
	char* pbBuf, int* iWrote,char* pszHost,const int iPort,int iTimeOut);
extern "C" int UDPRecvFromPeer(SOCKET m_sockComm,const int iWant, \
        const char* pbBuf, int* iRead,char* pszHost,int *piPort,int iTimeOut);

#endif
