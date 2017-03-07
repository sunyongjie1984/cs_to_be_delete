// OperateString.cpp: implementation of the COperateString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SafetyCode.h"
#include "OperateString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COperateString::COperateString()
{

}

COperateString::~COperateString()
{

}

char g_szvariableaddress[MAX_PATH];		// 用于存放调试信息



/**************************************************************************************************
 * 函数名: set_file_full_path ( char * lpszfilepath , const char * lpszfilename )
 *
 * 功  能: 根据给出的(lpszfilepath)文件路径，得到在该路径目录下的指定文件(lpszfilename)的全路径
 *
 * 返回值: 成功返回SUCCESS_FLAG，失败返回FAILED_FLAG
 **************************************************************************************************/
int COperateString::set_file_full_path (	char	   * lpszfilepath ,
											const char * lpszfilename		)
{
	//
	// 从字符串尾部查找'\\'，以确定尾部'\\'出现的位置
	//
	char * pszlastfind = strrchr ( lpszfilepath , '\\' );
	//
	// 判断当前字符串是不是合法文件路径
	//
	if ( NULL == pszlastfind )
	{
		//
		//没有找到'\\'，表明当前字符串不是合法文件路径
		//
		//logerror
		return FAILED_FLAG;
	}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	int nstrsize = 0;
	//
	// 获得需要截取的字符串长度，设置缓冲范围
	//
	nstrsize = (++pszlastfind) - lpszfilepath;
	//
	// 判断是否会溢出缓冲区
	//
	if ( ( 1 > nstrsize ) || ( nstrsize > MAX_PATH ) )
	{
		//
		// 大于缓冲区范围
		//

		//logerror
		return FAILED_FLAG;
	}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "nstrsize" ,
						&nstrsize , nstrsize											)
#endif
//-------------------------------------------------------------------------------------------

	//
	// 定义缓冲区
	//
	char sztempmemory[MAX_PATH];

	memset ( sztempmemory , 0 , MAX_PATH );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "++pszlastfind" ,
						&(++pszlastfind) , ++pszlastfind								)
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "sztempmemory" ,
						&sztempmemory , sztempmemory									)
#endif
//-------------------------------------------------------------------------------------------

	pszlastfind = strncpy ( sztempmemory , lpszfilepath , nstrsize );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "lpszfilepath" ,
						&lpszfilepath , lpszfilepath									)
#endif
//-------------------------------------------------------------------------------------------

	//
	// 获得要合并的字符串长度
	//
	nstrsize = strlen (sztempmemory) + strlen (lpszfilename);
	//
	// 判断是否会溢出缓冲区
	//
	if ( (MAX_PATH-1) < nstrsize )
	{
		//
		// 大于缓冲区范围
		//

		//logerror
		return FAILED_FLAG;
	}

	pszlastfind = strcat ( sztempmemory , lpszfilename );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	memset ( lpszfilepath , 0 , MAX_PATH );
	//
	// 获得该函数要导出的字符串
	//
	pszlastfind = strcpy ( lpszfilepath , sztempmemory );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	return SUCCESS_FLAG;
}