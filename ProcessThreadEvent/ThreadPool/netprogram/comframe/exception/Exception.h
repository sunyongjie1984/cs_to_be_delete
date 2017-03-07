#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string.h>
#include <iostream>

#define EMPTY_ERROR_NO	32767
#define EMPTY_LINE	-1

//CException is the base class of all the exception class
class CException
{
private:
protected:
    int		m_iErrorNo;
    char	m_strErrorMsg[1024];
    char	m_strFile[100];
    int		m_iLine;	 
public:
    CException(int iErrorNo, const char* sErrorMsg, const char* sFile, int iLine);
    CException(const char* sErrorMsg, const char* sFile, int iLine);
    int GetErrorNo() { return m_iErrorNo; }
    void  ShowErrMsg(){
	printf("ERROR:[%s] , FILE: %s , LINE: %d \n",m_strErrorMsg,m_strFile,m_iLine);
    }
    virtual ~CException();
};

class CMemException   :public  CException
{
public:
    CMemException(const char* sErrorMsg, const char* sFile, int iLine)
	: CException(sErrorMsg, sFile, iLine) {}
    virtual ~CMemException() {}
};

//**********************************************************//
class CSocketException : public CException
{
public:
    CSocketException(const char* sErrorMsg, const char* sFile, int iLine)
	: CException(sErrorMsg, sFile, iLine) {}
    virtual ~CSocketException() {}
};

//**********************************************************//
class CThreadException : public CException
{
public:
    CThreadException(const char* sErrorMsg, const char* sFile, int iLine)
	: CException(sErrorMsg, sFile, iLine) {}
    virtual ~CThreadException() {}
};

#endif
