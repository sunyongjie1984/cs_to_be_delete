#ifndef __FLYDISHHTTP_H_
#define __FLYDISHHTTP_H_

#define CRLF  "\x0d\x0a"
#include "../comframe/thread/Thread.h"
#include "../comframe/thread/ThreadPool.h"
#include "../comframe/thread/ThreadManage.h"
#include "../comframe/thread/WorkerThread.h"
#include "../comframe/thread/Job.h"
#include "../comframe/socket/Socket.h"
#include "../comframe/socket/ServerSide.h"

class CHTTPJob:public CAcceptJob
{
public:
    CHTTPJob();
    ~CHTTPJob();
    
    virtual void  Run(void* jobdata);
};

#endif
