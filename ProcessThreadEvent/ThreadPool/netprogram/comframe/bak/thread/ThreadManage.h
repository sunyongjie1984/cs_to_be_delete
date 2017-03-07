/*****************************************************************
*Role:The file manage Linux thread ,include create thread etc.   *
*CopyRight(c):                                                   *
*	flydish,2004,06,25                                       *
*History:                                                        *
*	Create by flydish,2004,06,25                             * 
*****************************************************************/
#ifndef _THREADMANAGE_H_
#define _THREADMANAGE_H_

#include "ThreadPool.h"
#include "Thread.h"
#include "../sync/sync.h"
#include "WorkerThread.h"
#include "Job.h"

//===============================================================
//CThreadManage is the class that interact with client
//we usually use it as following
//CThreadManage* thrmanage = new CThreadManage(10);
//CXXJob job = new CXXJob();
//thrmanage->Run(job,NULL);

class CThreadManage
{
private:
    CThreadPool*    m_Pool;
    int		    m_NumOfThread;
protected:
public:
    void	    SetParallelNum(int num);
    CThreadManage();
    CThreadManage(int num);
    virtual ~CThreadManage();
 
    void    Run(CJob* job,void* jobdata);
    void    TerminateAll(void);
};

#endif

