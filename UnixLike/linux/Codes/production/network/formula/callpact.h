#ifndef _CALL_PACT_H_
#define _CALL_PACT_H_

#define SYMBOL_CONN 1024
#define MODELID_TESTPOOL 786

class MSG_HEADER
{
public:
    MSG_HEADER()
    {
        m_iMsgSymbol = 0;
        m_iMsgModelId = 0;
        m_ifollowerSize = 0;
    }
public:	
    enum Symbol { CONN = 1024 };
    enum ModelID { TESTPOOL = 786 };

public:
    int m_iMsgSymbol;
    int m_iMsgModelId;
    int m_ifollowerSize;
};

typedef struct _NETWORK
{
    int socket;
}
NETWORK;

#endif//_CALL_PACT_H_

