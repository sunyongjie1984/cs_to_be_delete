#ifndef _STREAM_H_
#define _STREAM_H_

class CStream
{
protected:
    int m_Len;
    int m_Pos;
public:
    CStream(){m_Len=0;m_Pos=0;}
    virtual ~CStream(){Free();}
    
    virtual  long    Len(void){return m_Len;}
    virtual  long    Pos(void){return m_Pos;}
    virtual  long    SetPos(long iPos){m_Pos = iPos;}
    virtual  long    Read(void* pBuf,long iLen)=0;
    virtual  long    Write(void* pBuf,long iLen)=0;

    virtual  long    Free(void);
};

class CSocketStream:public CStream
{
protected:
    char* m_pData;
    AutoGrow(long iSize);
public:
    CSocketStream();
    virtual ~CSocketStream();

    virtual  long    SetPos(long iPos){m_Pos = iPos;}
    virtual  long    Read(void* pBuf,long iLen){return 0;}
    virtual  long    Write(void* pBuf,long iLen){return 0;}
};
#endif
