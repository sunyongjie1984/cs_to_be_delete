#ifndef _TEST_POOL_TASK_H_
#define _TEST_POOL_TASK_H_

#include "../../threadmanage/threadpool/threadmanager.h"
#include "../../threadmanage/threadpool/task.h"
#include "../../network/formula/callpact.h"
#include "../../network/socket/socket.h"

class CTestPoolTask : public CTask
{
public:
    CTestPoolTask();
    virtual ~CTestPoolTask();

public:
    void Run(void * p);

protected:
    int recvformula();
    int ModelDisposalFun(MSG_HEADER * p);

protected:
    int m_iSocket;
};

#endif//_TEST_POOL_TASK_H_

