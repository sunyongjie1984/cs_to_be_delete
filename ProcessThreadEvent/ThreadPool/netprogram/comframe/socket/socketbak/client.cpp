#include "comhead.h"
#include "IPCCom.h"
main()
{
    int iWrote,iRead;
    char pszRecv[1024];

    SOCKET sock=CreateConnectSocket("127.0.0.1",9090);
    TCPSendToPeer(sock,1024,"shanghairen",&iWrote,0); 
    TCPRecvFromPeer(sock,1024,pszRecv,&iRead,0);    
    printf("pszRecv	:%s\n",pszRecv);
}
