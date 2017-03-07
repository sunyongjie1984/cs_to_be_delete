// FileOperateClass.cpp: implementation of the CFileOperateClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileOperateClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperateClass::CFileOperateClass()
{
	int i = 0;
}

CFileOperateClass::~CFileOperateClass()
{

}


VOID  CFileOperateClass::GetFilePath( IN  OUT   PCHAR  lpFileName )
{
	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );
	
	string strTempMemoryPath = szFilePath;

	///////////////////////////整型和位域变量（number）前缀 -- n
	int nPos = strTempMemoryPath.find_last_of( "\\" );

	strTempMemoryPath = strTempMemoryPath.substr( 0, (nPos + 1) );

	strTempMemoryPath.append( lpFileName );

	memset( lpFileName, 0, MAX_PATH );
	
	strcpy( lpFileName, strTempMemoryPath.c_str() );

	_strlwr( lpFileName );
}


VOID  CFileOperateClass::GetFilePath( IN  OUT   string  &strFileName )
{
 	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );

	string strFilePath = szFilePath;
	
	///////////////////////////整型和位域变量（number）前缀 -- n
	int nPos = strFilePath.find_last_of( "\\" );
	
	strFilePath = strFilePath.substr( 0, (nPos + 1) );
	
	strFilePath.append( strFileName );

	strFileName = strFilePath;
}


BOOL  CFileOperateClass::ReadFile( IN        PCHAR             lpFileFullPath,
								   IN  OUT   PDATA_STRUCTURE   &pDataStructure )
{	
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        PCHAR             lpFileFullPath,
									IN        PDATA_STRUCTURE   pDateStructure )
{
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        unsigned char       *pchBuffer,
								    IN 	      const UINT           nDataLength,
								    IN        string               strFileFullPath )
{
	//打开文件
	FILE *pFileW = NULL;
	
	pFileW = fopen( strFileFullPath.c_str(), "w+" );

	if ( NULL == pFileW )
	{
		return FALSE;
	}

	//写入文件
	fseek(pFileW, 0, SEEK_CUR); 

	fwrite( pchBuffer, sizeof(char), nDataLength, pFileW);

	char szTemp[512] = {0};
	
//	for( int i = 0; i < 1433; i++ )
	{
		fwrite( szTemp, sizeof(char), nDataLength, pFileW );
	}

	//关闭文件
	if ( fclose(pFileW) )
	{
		return FALSE;
	}
	
	return TRUE;
}

int CFileOperateClass::ReadFile( IN OUT    unsigned char       *pchBuffer,
								 IN 	   const UINT           nDataLength,
								 IN        string               strFileFullPath )
{
//	ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_FileOpeateProcessMutex, -1 );
	
	FILE *pFile = NULL;

	pFile = fopen( strFileFullPath.c_str(), "rb" );

	if( NULL == pFile)
	{
		return -1;
	}

	fseek( pFile, 0, SEEK_SET );				//////////Moves the file pointer to a specified location
	
	int numread = fread( (PCHAR)pchBuffer,
						 nDataLength,
						 1,
						 pFile );

	long lPos = ftell(pFile);					//////////Gets the current position of a file pointer.

	if ( fclose(pFile) )
	{
		return -1;
	}
	
	return 0;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
int CFileOperateClass::ParseConnectDbConfigurationFile(
									IN    OUT   string    &strConnection,
									IN          string     strIp,
									IN    OUT   string    &strUseID,
									IN    OUT   string	  &strPassWord,
									IN          string     strFileFullPathName )
{	
	PCONNECT_DB_CONFIGURATION_FILE pBuffer = new CONNECT_DB_CONFIGURATION_FILE;
	
	int nDataLength = sizeof( CONNECT_DB_CONFIGURATION_FILE );
	
	memset( (PCHAR)pBuffer, 0, nDataLength );
	
	int nStatus = CFileOperateClass::ReadFile( (unsigned char*)pBuffer,
											   nDataLength,
											   strFileFullPathName );
	
	if ( 0 == nStatus )
	{		
		strConnection  =  "Provider=";
		strConnection +=  pBuffer->Provider;
		strConnection +=  ";";
		strConnection +=  "Persist Security Info=";
		strConnection +=  pBuffer->PerSInfo;
		strConnection +=  ";";
		strConnection +=  "NETWORK=DBMSSOCN;";
		strConnection +=  "User ID=";
		strConnection +=  pBuffer->UserID;
		strConnection +=  ";";
		strConnection +=  "Initial Catalog=";
		strConnection +=  pBuffer->InitialCatalog;
		strConnection +=  ";";
		strConnection +=  "Data Source=";
		strConnection +=  pBuffer->DataSource;
		strConnection +=  ",";
		strConnection +=  pBuffer->port;
		
		if( strlen(pBuffer->Other) > 0 )
		{
			strConnection +=  ";";
			strConnection +=  pBuffer->Other;
			strConnection +=  ";";
		}
		strUseID     = pBuffer->UserID;
		strPassWord  = pBuffer->PassWord;
		
		strIp.assign(pBuffer->DataSource);
	}
	
	strConnection += "\n" + strUseID + "\n" + strPassWord + "\n" + strIp;
	
	::MessageBox( NULL, strConnection.c_str(), "", MB_OK );

	delete pBuffer;
	
	return nStatus;
}