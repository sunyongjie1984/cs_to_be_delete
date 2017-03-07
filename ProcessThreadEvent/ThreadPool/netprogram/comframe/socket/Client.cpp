#include "Socket.h"

int main()
{
int i;
for(i=1;i<100;i++)
{
    try
    {
	CClientSocket sock ;
	sock.SetRemoteAddress("127.0.0.1");
	sock.SetRemotePort(9090);
	printf("Connect %d time\n",i);
	sock.Connect();
/*
	long int write,read;
	char* p = "hello";
	sock.SendToPeer(p,1024,&write);
	printf("Send %d request\n",i);
*/
/*
	char strBuffer[1024];

	sock.RecvFromPeer(strBuffer,1024,&read);
	printf("Receive From Server:%s\n",strBuffer);
*/
    }
    catch(CSocketException e)
    {
	e.ShowErrMsg();
    }
}

/*
        CClientSocket sock ;
        sock.SetRemoteAddress("127.0.0.1");
        sock.SetRemotePort(9090);
        sock.Connect();
        long int write,read;
        char* p = "The 510 Test";
        sock.SendToPeer(p,1024,&write);
        printf("We send %d request\n",++i);
        char strBuffer[1024];

        sock.RecvFromPeer(strBuffer,1024,&read);
        printf("Receive From Server:%s\n",strBuffer);
*/


    return 0;
}
