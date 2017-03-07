#ifndef _WORKERTHREAD_H_
#define _WORKERTHREAD_H_

#include "Thread.h"
#include "Job.h"
#include "../sync/sync.h"
/**************************************************************
 *For class CThread is an abstract class,it can't be instantiated
 *class CWorkerThread is the actual thread that run the job,but
 *
 **************************************************************/


class CTestThread:public CThread
{
protected:
public:
    CCondition   m_WorkCond;
    CThreadMutex m_WorkMutex;
  
    CTestThread();
    virtual ~CTestThread();
    
    void Run();
     
};

#endif
