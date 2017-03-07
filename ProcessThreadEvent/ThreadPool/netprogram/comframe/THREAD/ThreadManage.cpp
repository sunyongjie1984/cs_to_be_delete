#include "ThreadManage.h"

CThreadManage::CThreadManage()
{
    m_NumOfThread = 10;
    m_Pool = new CThreadPool(m_NumOfThread);
 
}

CThreadManage::CThreadManage(int num)
{
    m_NumOfThread = num;
    m_Pool = new CThreadPool(m_NumOfThread);
}

CThreadManage::~CThreadManage()
{
    if(NULL != m_Pool)
	delete m_Pool;
}

void CThreadManage::SetParallelNum(int num)
{
    m_NumOfThread = num;
}

void CThreadManage::Run()
{
    m_Pool->Run();
}

void CThreadManage::TerminateAll(void)
{
    m_Pool->TerminateAll();
    return;
}

void CThreadManage::PostJob(CJob* job,void* jobdata)
{
    m_Pool->PostJob(job,jobdata);
    return;
}
