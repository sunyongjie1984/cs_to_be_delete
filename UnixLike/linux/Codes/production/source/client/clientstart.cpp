#include "../../network/socket/socket.h"
#include "../../network/formula/callpact.h"

int main(int argc, char ** argv)
{
    int connect_fd = 0;

    MSG_HEADER msgheader;

    int loop_ = 0;

    if (1 < argc)
    {
        loop_ = atoi(argv[1]);
    }
    else
    {
        loop_ = 10;
    }

    for (int i = 0; i < loop_; i++)
    {
        char strHello[30] = {0};

        msgheader.m_iMsgSymbol = SYMBOL_CONN;
        msgheader.m_iMsgModelId = MODELID_TESTPOOL;
        msgheader.m_ifollowerSize = sizeof(strHello);

        connecter(&connect_fd, 1296, "127.0.0.1");

        send_n(connect_fd, (char *)&msgheader, sizeof(MSG_HEADER));

        sprintf(strHello, "client send -----%d\n", i);
        send_n(connect_fd, strHello, sizeof(strHello));

        printf(strHello);

        close(connect_fd);
    }

    return 0;
}

