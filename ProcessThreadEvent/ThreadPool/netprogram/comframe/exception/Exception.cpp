#include "Exception.h"

CException::CException(int iErrorNo, const char* sErrorMsg, const char* sFile, int iLine )
{
    m_iErrorNo = iErrorNo;
    if (sErrorMsg)
    {
	memset(m_strErrorMsg,0x0,1024);
	strcpy(m_strErrorMsg, sErrorMsg);
    }
    if (sFile)
    {
	memset(m_strFile,0x0,100);
	strcpy(m_strFile, sFile);
    }
    m_iLine = iLine;
}

CException::CException(const char* sErrorMsg, const char* sFile, int iLine)
{
    m_iErrorNo = EMPTY_ERROR_NO;
    if (sErrorMsg)
    {
	memset(m_strErrorMsg,0x0,1024);
	strcpy(m_strErrorMsg , sErrorMsg);
    }
    if (sFile)
    {
	memset(m_strFile,0x0,100);
	strcpy(m_strFile , sFile);
    }
    m_iLine = iLine;
}

CException::~CException()
{
    if(m_strErrorMsg!=NULL)
	free(m_strErrorMsg);
    if(m_strFile !=NULL)
	free(m_strFile);
}
/*
main()
{
    CSocketException ce = CSocketException("Out Of Socket Exception occurs",__FILE__,__LINE__);
    ce.ShowErrMsg(); 

    CMemException mem = CMemException("Out of Memory of this",__FILE__,__LINE__);
    mem.ShowErrMsg(); 

    CThreadException ct = CThreadException("Thread Error of this this",__FILE__,__LINE__);
    ct.ShowErrMsg(); 
}
*/
