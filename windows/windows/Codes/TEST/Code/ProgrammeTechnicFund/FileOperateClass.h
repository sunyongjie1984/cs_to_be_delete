// FileOperateClass.h: interface for the CFileOperateClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_)
#define AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ACE_Frame.h"
#include "ProgrammeTechnicFund.h"
//编码规范
//////////////////////////////类的名称都要以大写字母“C”开头，后跟一个或多个单词。
//////////////////////////////为便于界定，每个单词的首字母要大写。
class CFileOperateClass
{
public:
	static ACE_Process_Mutex m_FileOpeateProcessMutex;

public:
	CFileOperateClass();
	virtual ~CFileOperateClass();


//////////////////////////////函数名应当使用"动词"或者"动词＋名词"（动宾词组）的形式。
//////////////////////////////指针型变量和迭代子（pointer） 前缀标明一个变量的类型 -- p
public:

	static  VOID  GetFilePath(
							IN  OUT   PCHAR              lpFileName );

	static  VOID  GetFilePath(
							IN  OUT   string            &strFileName );

	static  BOOL  ReadFile( 
							IN        PCHAR              lpFileFullPath,
							IN  OUT   PDATA_STRUCTURE   &pDataStructure );

	static  int   ReadFile(
							IN  OUT   unsigned char     *pchBuffer,
							IN 	      const UINT         nDataLength,
							IN        string             strFileFullPath );		

	static  BOOL  WriteFile( 
							IN        PCHAR              lpFileFullPath,
							IN        PDATA_STRUCTURE    pDateStructure );

	static  BOOL  WriteFile(
							IN        unsigned char      *pchBuffer,
							IN 	      const UINT          nDataLength,
							IN        string              strFileFullPath );

	static  int   ParseConnectDbConfigurationFile(
							IN  OUT   string            &strConnection,
							IN        string             strIp,
							IN  OUT   string            &strUseID,
							IN  OUT   string	        &strPassWord,
							IN        string			 strFileFullPathName );

	static  HBITMAP CopyScreenToBitmap( LPRECT lpRect );

	static  int		SaveBitmapToFile( HBITMAP hBitmap,
									  LPSTR   lpFileName );
	
//////////////////////////////保护成员函数的开头应当加上一个下划线“_”以示区别.
protected:


private:

};

#endif // !defined(AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_)
