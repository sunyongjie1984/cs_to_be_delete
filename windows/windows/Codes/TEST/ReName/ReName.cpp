#include <windows.h>
#include <iostream.h>
#include <string>
#include <share.h>
#include <stdio.h>
#include <process.h>
#include <conio.h>

using namespace std;


#define SUCCESS		1
#define ERROR		0

int ModifyFileNameTask( string strObjectPath , int iFileCount );

int CmpFileSize(	char * pszObjectPath ,
					char * pszCmpPath ,
					long * plObjectFileSize ,
					bool * bEquation			)
{
	FILE * pObjectFile ,
		 * pCmpFile;
	
	pObjectFile = _fsopen( pszObjectPath , "rb" , SH_DENYRW );
	pCmpFile    = _fsopen( pszCmpPath , "rb" , SH_DENYRW );

	if ( (NULL == pObjectFile) || (NULL == pCmpFile) )
	{
		printf("打开文件失败");
		return ERROR;
	}

	int iObjectResult = fseek( pObjectFile , 0L , SEEK_END );
	int iCmpResult	  = fseek( pCmpFile , 0L , SEEK_END );

	if ( iObjectResult || iCmpResult )
	{
		fclose( pObjectFile );
		fclose( pCmpFile );
		printf("FSEEK 失败");
		return ERROR;
	}

	*plObjectFileSize = ftell( pObjectFile );
	long lCmpResult    = ftell( pCmpFile );

	if ( (-1 == *plObjectFileSize) || (-1 == lCmpResult) )
	{
		fclose( pObjectFile );
		fclose( pCmpFile );
		printf("ftell 失败");
		return ERROR;
	}

	fclose( pObjectFile );
	fclose( pCmpFile );

	if (*plObjectFileSize == lCmpResult)
	{
		*bEquation = true;
	}
	else
	{
		*bEquation = false;
	}

	return SUCCESS;
}



void main (void)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	while ( TRUE )
	{
		int iRunFlag = 0;

		printf("运行程序输入 1   退出程序输入 0  : ");

		cin>>iRunFlag;

		if ( 0 == iRunFlag )
		{
			return;
		}

		printf("\n\r输入指定的文件夹 : ");

		// 输入文件夹
		char szSpecifyPath[MAX_PATH];

		memset( szSpecifyPath , 0 , MAX_PATH );

		cin>>szSpecifyPath;

		int iFileCount = 0;

		cin>>iFileCount;

		string strObjectFilePath;		// 存放要换名的文件路径

		strObjectFilePath = szSpecifyPath;

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		ModifyFileNameTask( strObjectFilePath , iFileCount );
		//------------------------------------------------------------------------------//
	}
	//---------------------------------------------------------------------------------------//
}

int ModifyFileNameTask( string strObjectPath , int iFileCount )
{
	if ( strObjectPath.empty() )
	{
		printf( "输入的文件夹名为空" );
		return ERROR;
	}
	// 保存文件夹路径
	strObjectPath.append( "\\" );
	string strSave;
	strSave = strObjectPath;

	// 获得文件搜索句柄
	strObjectPath.append( "*.*" );
	WIN32_FIND_DATA wfData;
	memset( &wfData , 0 , sizeof( WIN32_FIND_DATA ) );

	HANDLE hFile = ::FindFirstFile( strObjectPath.c_str() , &wfData );
	if ( !hFile )
	{
		printf( "获得文件搜索句柄失败" );
		return ERROR;
	}

	memset( &wfData , 0 , sizeof( WIN32_FIND_DATA ) );

	string strNewFileName;		// 要设置的文件名
	string strfilename;
	char   szFileNumber[MAX_PATH];

	BOOL bResult = FALSE;
	int	 iPos	 = 0;
	int  iStatus = 0;

	while ( ::FindNextFile( hFile , &wfData ) )
	{
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		strfilename = wfData.cFileName;		

		iStatus = strfilename.compare( ".." );
		iPos    = strfilename.find_last_of( '.' );

		if ( ( -1 == iPos ) || ( 0 == iStatus ) )
		{
			printf( "%s\n\r" , wfData.cFileName );
			continue;
		}
		//--------------------------------------------------------------//

		//+++++++++++++++++++获得文件扩展名+++++++++++++++++++++++++++++//
		strfilename = strfilename.substr( iPos , strfilename.length() );
		//--------------------------------------------------------------//

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		strObjectPath = strSave;
		strObjectPath.append( wfData.cFileName );
		//--------------------------------------------------------------//

		//+++++++++++++++++++++++设置新文件名+++++++++++++++++++++++++++//
		memset( szFileNumber , 0 , MAX_PATH );
		sprintf( szFileNumber , "%d" , iFileCount );

		strNewFileName  = strSave;
		strNewFileName.append( szFileNumber );
		strNewFileName.append( strfilename.c_str() );

		iFileCount++;
		//--------------------------------------------------------------//

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		BOOL bResult = ::MoveFile(	strObjectPath.c_str() ,
									strNewFileName.c_str()		);

		if (bResult)
		{
			printf(	"将%s文件重命名为%s成功\n\r" ,
					strObjectPath.c_str() ,
					strNewFileName.c_str()			);
		}
		else
		{
			printf("重命名失败");
			return ERROR;
		}
		//--------------------------------------------------------------//
		memset( &wfData , 0 , sizeof( WIN32_FIND_DATA ) );
	}
	::FindClose( hFile );
	
	return SUCCESS;
}

/*
	char * envp[]={ "PATH = C:\\C_LIB" , NULL };

	char * argv[] = { "SPAWN-C" , "spawnvpe" , "Arg1" , "Arg2" , NULL };

	char Choice;

	printf( "Spawn Function. Select the following one" );
	printf( "which you want :\n" );
	printf( "-------------------------------------------\n" );
	printf( "	1.spawnl\n" );
	printf( "	2.spawnle\n" );
	printf( "	3.spawnlp\n" );
	printf( "	4.spawnlpe\n" );
	printf( "	5.spawnv\n" );
	printf( "	6.spawnve\n" );
	printf( "	7.spawnvp\n" );
	printf( "	8.spawnvpe\n" );
	printf( "-------------------------------------------\n" );
	printf( "	Choice:" );

	do
	{
		Choice = getche();

		switch(Choice)
		{
			case '1': spawnl( P_WAIT , "SPAWN-C" , "SPAWN-C" , "spawnl" , "Arg1" , "Arg2" , NULL );
			break;
			case '2': spawnle( P_WAIT , "SPAWN-C" , "SPAWN-C" , "spawnle" , "Arg1" , "Arg2" , NULL , envp );
			break;
			case '3': spawnlp( P_WAIT , "SPAWN-C" , "SPAWN-C" , "spawnlp" , "Arg1" , "Arg2" , NULL );
			break;
			case '4': spawnlpe( P_WAIT , "SPAWN-C" , "SPAWN-C" , "spawnlpe" , "Arg1" , "Arg2" , NULL , envp );
			break;
			case '5': argv[1][6] = '\0';
					spawnv( P_WAIT , "SPAWN-C" , argv );
			break;
			case '6': argv[1][6] = 'e';
					spawnve( P_WAIT , "SPAWN-C" , argv , envp );
			break;
			case '7': argv[1][7] = '\0';
					spawnvp( P_WAIT , "SPAWN-C" , argv );
			break;
			case '8': 
					spawnvpe( P_WAIT , "SPAWN-C" , argv , envp );
			break;
			default: printf("\a\b");

		}
	}
	while ( Choice < '1' || Choice > '8' );

	printf( "-------------------------------------------\n" );
	printf( "Return to parent process.\n" );
	return;
	//---------------------------------------------------------------------------------------//
*/