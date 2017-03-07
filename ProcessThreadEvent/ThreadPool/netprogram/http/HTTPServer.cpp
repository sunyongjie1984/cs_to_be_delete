#include "HTTPServer.h"
CHTTPJob::CHTTPJob()
{
}

CHTTPJob::~CHTTPJob()
{
}

void CHTTPJob::Run(void* jobdata)
{
/*
    printf("CHTTPJob::Run()\n");
    char  strBuffer[1024];
    long int   iRead,iWrite;
    acceptSock->RecvFromPeer(strBuffer,1024,&iRead);
    printf("Receive From Client:%s\n",strBuffer);
    char* p = "string comes from server";
    acceptSock->SendToPeer(p,1024,&iWrite);
*/
    printf("==============================\n");
    printf("Accept Request From Client:\n");
    printf("Address    %s\n",acceptSock->GetRemoteAddress());
    printf("Port       %d\n",acceptSock->GetRemotePort());
    printf("==============================\n");
//    sleep(4);
}

main()
{
    CPreCreateServer serv;
    CHTTPJob* httpJob = new CHTTPJob();
    serv.SetRunJob(httpJob);
    serv.Run(9090);
}

