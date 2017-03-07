#include "Address.h"

CAddress::CAddress()
{
    m_HostName = NULL;
    m_StrAddress = NULL;
}

CAddress::~CAddress()
{
    free(m_HostName);
    free(m_StrAddress);
}

int CAddress::AddressConvert(char* address,ADDR* inaddr)
{
    if(inet_aton(address,inaddr) == 1)
        return 1;

    struct hostent* he;
    he = gethostbyname(address);
    if(he != NULL)
    {
        *inaddr = *(struct in_addr*)he->h_addr_list[0];
        return 1;
    }
    return 0;
}


struct in_addr CAddress::GetAddress(char* strAddress)
{
    struct in_addr addr; 
    AddressConvert(strAddress,&addr);
    m_InAddr = addr;
    return m_InAddr;
}

main()
{
    CAddress add;
    printf("%s\n",inet_ntoa(add.GetAddress("x863_server2")));
    printf("%d\n",(add.GetAddress("www.xjtu.edu.cn")));
}
