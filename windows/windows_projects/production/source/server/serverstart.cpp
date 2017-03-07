#include "../../network/socket/socket.h"
#include "../../threadmanage/threadpool/threadmanager.h"
#include "testpooltask.h"

int response(void * p);

int main(int argc, char ** argv)
{
    int ithrNum = 0;

    if (1 < argc)
    {
        ithrNum = atoi(argv[1]);

        if (50 < ithrNum)
        {
            ithrNum = 50;
        }
    }
    else
    {
        ithrNum = 10;
    }

    CThreadManager * pM = CThreadManager::Init(ithrNum);

    if (NULL != pM)
    {
        pM->Start();
    }

    int listen_fd = 0;

    int ret = listener(&listen_fd, 1296);

    if (-1 == ret)
    {
        printf("listener failed\n");
    }

    accepter(listen_fd, &response);

    return 0;
}

int response(void * p)
{
    int * socket = (int *)p;

    CThreadManager * pM = CThreadManager::Init(0);

    if (NULL != pM)
    {
        CTestPoolTask * ptpTask = new CTestPoolTask();

        NETWORK s;

        s.socket = *socket;

        ptpTask->SetTaskParameter((char *)&s, sizeof(NETWORK));

        pM->AddTask(ptpTask);
    }

    return 0;
}

