#include "ServerSide.h"

void CAcceptJob::Run(void* jobdata)
{
    printf("================================\n");
    printf("Accept Request From Client:\n");
    printf("Address %d \n",acceptSock->GetRemoteAddress());
    printf("Port    %d \n",acceptSock->GetRemotePort());
    printf("================================\n");
}
//=====================================================
// The implementation of class CPreCreateServer      //
//=====================================================
CPreCreateServer::CPreCreateServer()
{
    m_ThreadManage = NULL;
}

CPreCreateServer::~CPreCreateServer()
{
}

void CPreCreateServer::Run(long lPort)
{
    m_ThreadManage = new CThreadManage(10);
    m_ServSocket->Listen(lPort); 
    for(;;)
    {
	CAcceptSocket* acceptSock = m_ServSocket->Accept();
	CAcceptJob* acceptJob= new CAcceptJob() ;
	acceptJob->SetAcceptSocket(acceptSock);	
	m_ThreadManage->Run(acceptJob,NULL);

	delete acceptSock;
	delete acceptJob;
    }
}

main()
{
    CPreCreateServer serv;
    serv.Run(9090);
}
