#include "testpooltask.h"
#include "../../network/formula/callpact.h"

CTestPoolTask::CTestPoolTask()
{
    m_iSocket = 0;
}

CTestPoolTask::~CTestPoolTask()
{
}

void CTestPoolTask::Run(void * p)
{
    NETWORK s;

    this->GetTaskParameter((char *)&s);

    m_iSocket = s.socket;

    recvformula();

    close(m_iSocket);
}

int CTestPoolTask::recvformula()
{
    MSG_HEADER header;

    size_t write_size = sizeof(MSG_HEADER);

    int ret = recv_n(m_iSocket, (char *)&header, write_size);

    switch(header.m_iMsgSymbol)
    {
        case SYMBOL_CONN:
        {
            ret = ModelDisposalFun(&header);
            break;
        }
        default:
        {
            break;
        }
    }

    return ret;
}

int CTestPoolTask::ModelDisposalFun(MSG_HEADER * p)
{
    int ret = 0;

    switch(p->m_iMsgModelId)
    {
        case MODELID_TESTPOOL:
        {
            char * pBuf = new char[p->m_ifollowerSize];

            memset(pBuf, 0, p->m_ifollowerSize);

            ret = recv_n(m_iSocket, pBuf, p->m_ifollowerSize);

            if (0 != ret)
            {
                ret = -1;
                printf("recv_n failed\n");
            }
            else
            {
                printf("%s\n", pBuf);
                delete pBuf;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return ret;
}

