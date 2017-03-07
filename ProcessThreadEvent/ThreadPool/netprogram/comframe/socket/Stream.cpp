#include "Stream.h"
#include "../exception/Exception.h"
CSocketStream::CSocketStream():CStream()
{
    m_pData = NULL;
}

CSocketStream::~CSocketStream()
{
    delete m_pData;
}

long  CSocketStream::AutoGrow(int iSize)
{
    
}

long  CSocketStream::SetPos(long iPos)
{
}

long  CSocketStream::Read(void* pBuf,long iLen)
{
}

long  CSocketStream::Write(void* pBuf,long iLen)
{
}

