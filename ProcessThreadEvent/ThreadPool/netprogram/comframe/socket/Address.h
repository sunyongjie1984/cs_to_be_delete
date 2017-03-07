#ifndef __ADDRESS_H_
#define __ADDRESS_H_

#include "../include/comhead.h"

typedef struct in_addr	ADDR;

class CAddress
{
private:
    int   AddressConvert(char* address,ADDR* inaddr);
protected:
    char* m_HostName;		//Host Name
    char* m_StrAddress; //such 202.117.15.112 or www.xjtu.edu.cn

    struct in_addr	m_InAddr;
public:
    CAddress();
    ~CAddress();

    char* GetHostName(void){return m_HostName;}
    char* GetStrAddress(void){return m_StrAddress;}

    ADDR GetAddress(char* strAddress);
};

#endif

