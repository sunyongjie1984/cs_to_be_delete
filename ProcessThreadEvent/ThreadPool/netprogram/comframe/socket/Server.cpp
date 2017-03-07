#include "Socket.h"

main()
{
    CServerSocket* servsocket = new CServerSocket();
    servsocket->Listen(9090);
    for(;;)
    {
	CAcceptSocket* accept =servsocket->Accept();
	printf("client comes from %s,port %d\n",accept->GetRemoteAddress(),accept->GetRemotePort());
	char* pbuf = new char[1024];
	long read,write;
	accept->RecvFromPeer(pbuf,1024,&read);
	printf("%s\n",pbuf);
	char* pb = "helloooo";
	accept->SendToPeer(pb,1024,&write);

	if(pbuf != NULL)
	    delete pbuf;
	if(accept!=NULL)
	    delete accept;
    }
}
