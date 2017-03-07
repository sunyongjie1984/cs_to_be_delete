// OperateString.h: interface for the COperateString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATESTRING_H__0D7FE5DA_C963_4281_B8AA_748CC5E1FBD4__INCLUDED_)
#define AFX_OPERATESTRING_H__0D7FE5DA_C963_4281_B8AA_748CC5E1FBD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SUCCESS_FLAG	0
#define FAILED_FLAG		1
#define EXCEPTION_FLAG -1

class COperateString  
{
public:
	COperateString();
	virtual ~COperateString();

public:
	int set_file_full_path ( char * lpszfilepath , const char * lpszfilename );
};

#endif // !defined(AFX_OPERATESTRING_H__0D7FE5DA_C963_4281_B8AA_748CC5E1FBD4__INCLUDED_)
