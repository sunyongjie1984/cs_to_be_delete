#include "ServerSide.h"
#include "error.h"

void CAcceptJob::Run(void* jobdata)
{
/*
    printf("================================\n");
    printf("Accept Request From Client:\n");
    printf("Address %s \n",acceptSock->GetRemoteAddress());
    printf("Port    %d \n",acceptSock->GetRemotePort());
    printf("================================\n");
*/
    printf("================================\n");
    printf("CAcceptJob::Run()\n");
    printf("================================\n");
}

//=====================================================
// The implementation of class CPreCreateServer      //
//=====================================================
CPreCreateServer::CPreCreateServer()
{
    m_ThreadManage = NULL;
    m_Job = NULL;
}

CPreCreateServer::~CPreCreateServer()
{
    if(m_ThreadManage!=NULL)
	delete m_ThreadManage;
    if(m_Job)
	delete m_Job;
}

void CPreCreateServer::Run(long lPort)
{
    int i=0;
    m_ThreadManage = new CThreadManage(50);
for(i=0;i<1000;i++)
{
    CAcceptJob acceptJob;
    m_ThreadManage->Run(&acceptJob,NULL);
}
/*
    CAcceptSocket* acceptSock = new CAcceptSocket();
    try
    {
	m_ThreadManage = new CThreadManage(50);
	m_ServSocket->Listen(lPort); 
	for(;;)
	{
	    if(m_ShutDown == false)
		break;
	    try
	    {
		acceptSock = m_ServSocket->Accept();
		printf("Accept %d Client Request\n",++i);
		m_Job->SetAcceptSocket(acceptSock);	
		m_ThreadManage->Run(m_Job,NULL);
		acceptSock->Close();
	    }
	    catch(CSocketException e)
	    {
		acceptSock->Close();
		if(acceptSock != NULL)
		    delete acceptSock;
		e.ShowErrMsg();
	    }

	}
    }
    catch(CSocketException e)
    {
	acceptSock->Close();
	if(acceptSock != NULL)
	    delete acceptSock;
	printf("Error:[NO: %d , ERRMSG: %s]\n",errno,strerror(errno));
	e.ShowErrMsg();
    }
*/
}

void CPreCreateServer::SetRunJob(CAcceptJob* job)
{
    m_Job = new CAcceptJob();
    m_Job = job;
}

main()
{
    CPreCreateServer serv;
//    CAcceptJob acceptJob;
//    serv.SetRunJob(&acceptJob);

    serv.Run(9090);
}
