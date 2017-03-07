#include "TestThread.h"

CTestThread::CTestThread()
{
}

CTestThread::~CTestThread()
{
}

void CTestThread::Run()
{
    printf("Enter into CWorkerThread::Run()\n");
    for(;;)
    {
    	printf("Job is NULL,wait for it\n");
	m_WorkCond.Wait(); 
    }
}
