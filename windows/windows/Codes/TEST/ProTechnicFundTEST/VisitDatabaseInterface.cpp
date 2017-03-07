// VisitDatabaseInterface.cpp: implementation of the CVisitDatabaseInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisitDatabaseInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  EXCEPTIONALERROR( exceptionalerrorinfo, infoHint )		\
{																\
	CHAR szHintInfo[MAX_PATH] = {0};							\
	CHAR szHint[MAX_PATH]     = {0};							\
																\
    sprintf( szHintInfo, "%s", (PCHAR)exceptionalerrorinfo );	\
																\
	::LoadString( NULL,											\
	              infoHint,										\
	              szHint,										\
	              sizeof(CHAR) * MAX_PATH );					\
																\
	::MessageBox( NULL, szHintInfo, szHint, MB_OK );			\
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//初始化单键
CVisitDatabaseInterface * CVisitDatabaseInterface::sm_pVisitDB = NULL;


CVisitDatabaseInterface::CVisitDatabaseInterface()
				:m_FileOpeateProcessMutex("SC_FILEMANAGE_MUTEX")
{
	m_pConnection = NULL;
	
	m_pRecord     = NULL;
}

CVisitDatabaseInterface::~CVisitDatabaseInterface()
{
	::CoUninitialize();
}


CVisitDatabaseInterface * CVisitDatabaseInterface::Instance()
{
	//访问数据库同步

	if ( NULL == sm_pVisitDB )
	{
		sm_pVisitDB = new CVisitDatabaseInterface;

		if ( -1 == sm_pVisitDB->__InitDatabaseConnection() )
		{
			ERRORMSGHINT( IDS_CONNECTION_DB_ERROR_HINT, IDS_HINT )
			return NULL;
		}
	}

	return sm_pVisitDB;
}


int CVisitDatabaseInterface::__InitDatabaseConnection()
{
//	ACE_GUARD_RETURN( ACE_Thread_Mutex, obj, m_ThreadMutex, -1 );
	
	if ( NULL != m_pConnection )
	{
		ReleaseDatabaseConnection();
	}
	
	try
	{
		::CoInitialize(NULL);

		m_pConnection.CreateInstance( __uuidof(Connection) );

		m_pConnection->ConnectionTimeout  = CONNECTION_TIME_OUT;

		m_pConnection->CommandTimeout     = COMMAND_TIME_OUT;

		string strDbConnection      = "";
		string strDbUseID           = "";
		string strDbPassWord        = "";
		string strIP                = "";

		int nStatus = __ParseConnectDbConfigurationFile( strDbConnection,
														 strIP,
														 strDbUseID,
														 strDbPassWord );

		if ( -1 == nStatus )
		{
			ERRORMSGHINT( IDS_CONFIGURATION_ERROR_HINT, IDS_HINT )
			return -1;
		}

		OutputDebugString( strDbConnection.c_str() );

		_bstr_t bstrDbConnection( strDbConnection.c_str() );
		
		HRESULT hResult = m_pConnection->Open( bstrDbConnection,
											   strDbUseID.c_str(),
											   strDbPassWord.c_str(),
											   adConnectUnspecified );
		
		if( FAILED(hResult) )
		{
			nStatus = -1;
		}

	}
	catch ( _com_error e )
	{		
		EXCEPTIONALERROR( e.Description(), IDS_HINT )
		return -1;
	}
	
	return 0;
}


int CVisitDatabaseInterface::__ParseConnectDbConfigurationFile(
										  IN    OUT   string    &strConnection,
										  IN          string    strIp,
										  IN    OUT   string    &strUseID,
										  IN    OUT   string	&strPassWord )
{
	string strFileFullPathName = "ConnectF.dat";

	CFileOperateClass::GetFilePath( strFileFullPathName );

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

	delete pBuffer;

	pBuffer = NULL; //delete 指针后要把指针置空，否则再使用delete的指针会报错
	
	return nStatus;
}


VOID CVisitDatabaseInterface::ReleaseDatabaseConnection()
{
	if ( m_pConnection->State )
	{
		m_pConnection->Close();
		
		m_pConnection = NULL;
	}
}


VOID CVisitDatabaseInterface::InsertSentenceConversion( _bstr_t &bstrSQL_Sentence,
													   CFileAuditLogInfo auditRecord )
{

	string strComputerName		= auditRecord.m_computer_name;
	string strOldPath			= auditRecord.m_old_path;
	string strNewPath			= auditRecord.m_new_path;
	string strVisitProcess		= auditRecord.m_visit_process;
	string strCurrentUser		= auditRecord.m_strCurrentUserName;

	char   szNetCall[1]  	    = {0};
	char   szOperateType[1]		= {0};
	char   szOperateTime[1]		= {0};

	sprintf( szNetCall,     "%d", auditRecord.m_lIsNetCall );
	sprintf( szOperateType, "%d", auditRecord.m_operate_time );
	sprintf( szOperateTime, "%d", auditRecord.m_operate_type );

	string strSQL_Sentence = 
				"INSERT INTO FILEAUDITLOG(COMPUTER_NAME,NEW_PATH,OLD_PATH,             \
				 VISIT_PROCESS,OPERATE_TIME,OPERATE_TYPE,VISIT_NETWORK,                \
				 VISITOR_NAME)VALUES('" + strComputerName + "','" + strNewPath + "','" \
				 + strOldPath + "','" + strVisitProcess + "'," + szOperateTime + ","   \
				 + szOperateType + "," + szNetCall + ",'" + strCurrentUser + "')";
	
	bstrSQL_Sentence = strSQL_Sentence.c_str();

}

int CVisitDatabaseInterface::RecordWriteIntoDatabase( vector<CFileAuditLogInfo> &auditRecord )
{
//	ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_ProcessMutex, -1 );

//	ACE_GUARD_RETURN( ACE_Thread_Mutex, ace_mon, m_ThreadMutex, -1 );

	try
	{
		if ( true == auditRecord.empty() )
		{
			return -1;
		}

		_RecordsetPtr  pRecord;
		_bstr_t        bstrSQL_Sentence;

		string strComputerName		= "";
		string strOldPath			= "";
		string strNewPath			= "";
		string strVisitProcess		= "";
		string strCurrentUser		= "";

		char   szNetCall[MAX_PATH]  	    = {0};
		char   szOperateType[MAX_PATH]		= {0};
		char   szOperateTime[MAX_PATH]		= {0};

		for ( int i = 0; i < auditRecord.size(); i++ )
		{
			strComputerName		= auditRecord[i].m_computer_name;
			strOldPath			= auditRecord[i].m_old_path;
			strNewPath			= auditRecord[i].m_new_path;
			strVisitProcess		= auditRecord[i].m_visit_process;
			strCurrentUser		= auditRecord[i].m_strCurrentUserName;

			sprintf( szNetCall,     "%d", auditRecord[i].m_lIsNetCall );
			sprintf( szOperateType, "%d", auditRecord[i].m_operate_time );
			sprintf( szOperateTime, "%d", auditRecord[i].m_operate_type );

			string strSQL_Sentence = 
						"INSERT INTO FILEAUDITLOG(COMPUTER_NAME,NEW_PATH,OLD_PATH, \
						 VISIT_PROCESS,OPERATE_TIME,OPERATE_TYPE,VISIT_NETWORK,    \
						 VISITOR_NAME)";
						 
			strSQL_Sentence = strSQL_Sentence + "VALUES('" + strComputerName + "',"	;
			strSQL_Sentence = strSQL_Sentence + "'" + strNewPath	  + "',"		;
			strSQL_Sentence = strSQL_Sentence + "'" + strOldPath	  + "',"		;
			strSQL_Sentence = strSQL_Sentence + "'" + strVisitProcess + "',"		;
			strSQL_Sentence = strSQL_Sentence + szOperateTime         + ","			;
			strSQL_Sentence = strSQL_Sentence + szOperateType         + ","			;
			strSQL_Sentence = strSQL_Sentence + szNetCall             + ",'"		;
			strSQL_Sentence = strSQL_Sentence + strCurrentUser + "')"				;

			bstrSQL_Sentence = strSQL_Sentence.c_str();

			m_pConnection->Execute( bstrSQL_Sentence, 0, adCmdText );
		}
		auditRecord.clear();
	}
	catch ( _com_error e )
	{
		if ( true == auditRecord.empty() )
		{
			auditRecord.clear();
		}
		
		EXCEPTIONALERROR( e.Description(), IDS_HINT )		
		return -1;
	}
	return 0;
}



VOID CVisitDatabaseInterface::SelectSentenceConversion(
									IN		OUT		_bstr_t				&bstrSQL_Sentence,
									IN		OUT		_bstr_t				&bstrGetRecordCount,
									IN				CFileAuditLogInfo    auditRecord,
									IN				int					 nFindRecordFlag )
{
	string strSQL_Sentence =
				"SELECT CLIENT_NAME,IP_ADDRESS,OS_VERSION,OLD_PATH,NEW_PATH,OPERATE_TIME,	\
				 OPERATE_TYPE,VISIT_PROCESS FROM FILEPRO_CLIENTINFOQUERY,FILEAUDITLOG";//		\
				 //WHERE FILEPRO_CLIENTINFOQUERY.CLIENT_NAME = FILEAUDITLOG.COMPUTER_NAME";
					//,VISIT_NETWORK  ,VISITOR_NAME,MAC_ADDRESS 

	string strGetRecordCount =
				"SELECT count(*) as Count from FILEAUDITLOG,FILEPRO_CLIENTINFOQUERY"; //WHERE	\
				 //FILEPRO_CLIENTINFOQUERY.CLIENT_NAME = FILEAUDITLOG.COMPUTER_NAME";


	if ( nFindRecordFlag )
	{
		int nChooseFlag = FALSE;
		
		string strTemp;

		if( true == auditRecord.m_computer_name.empty() )
		{
			strTemp = " WHERE COMPUTER_NAME LIKE '%" + auditRecord.m_computer_name + "%'";

			strSQL_Sentence   += strTemp;
			strGetRecordCount += strTemp;

			nChooseFlag = 1;
		}
		if( true == auditRecord.m_IP_address.empty() )
		{
			if ( nChooseFlag )
			{
				strTemp = " AND IP_ADDRESS ='" + auditRecord.m_IP_address + "'";

				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE IP_ADDRESS ='" + auditRecord.m_IP_address + "'";

				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;

				nChooseFlag = 1;
			}
		}
		if(!auditRecord.m_visit_process.empty())
		{
			if (nChooseFlag)
			{
				strTemp = " AND VISIT_PROCESS  LIKE'%" + auditRecord.m_visit_process + "%'";

				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE VISIT_PROCESS  LIKE'%" + auditRecord.m_visit_process + "%'";

				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
				nChooseFlag = 1;
			}
		}
		if(!auditRecord.m_new_path.empty())
		{
			if (nChooseFlag)
			{
				strTemp = " AND NEW_PATH LIKE '%" + auditRecord.m_new_path + "%'";

				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE NEW_PATH LIKE '%" + auditRecord.m_new_path + "%'";
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
				nChooseFlag = 1;
			}
		}
		if(!auditRecord.m_old_path.empty())
		{
			if (nChooseFlag) 
			{
				strTemp = " AND OLD_PATH LIKE '%" + auditRecord.m_old_path + "%'";
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE OLD_PATH LIKE '%" + auditRecord.m_old_path + "%'";
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
				nChooseFlag = 1;
			}
		}
		char szTypeConversion[MAX_PATH] = {0};
		
		if(auditRecord.m_operate_type)
		{
			memset( szTypeConversion, 0, sizeof(char) );

			sprintf( szTypeConversion, "%d", auditRecord.m_operate_type);

			if (nChooseFlag) 
			{
				strTemp = " AND OPERATE_TYPE = ";
				strTemp += szTypeConversion;
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE OPERATE_TYPE =";
				strTemp += szTypeConversion;
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
				nChooseFlag = 1;
			}
		}
		if(auditRecord.m_operate_time)
		{
			memset( szTypeConversion, 0, sizeof(char) );

			sprintf( szTypeConversion, "%d", auditRecord.m_operate_time );

			if (nChooseFlag)
			{
				strTemp = " AND OPERATE_TIME >=";
				strTemp += szTypeConversion;
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
			}
			else
			{
				strTemp = " WHERE OPERATE_TIME >=";
				strTemp += szTypeConversion;
				strSQL_Sentence   += strTemp;
				strGetRecordCount += strTemp;
				nChooseFlag = 1;
				
			}
		}
		if(auditRecord.m_operate_time_end)
		{
			sprintf( szTypeConversion, "%d", auditRecord.m_operate_time_end );
			strTemp = " AND OPERATE_TIME <= ";
			strTemp += szTypeConversion;
			strSQL_Sentence   += strTemp;
			strGetRecordCount += strTemp;
		}
	}

	bstrSQL_Sentence   = strSQL_Sentence.c_str();
	bstrGetRecordCount = strGetRecordCount.c_str();
}

int CVisitDatabaseInterface::ReadRecordFromDatabase(
								IN	OUT		DWORD				&dwGetRecordCount,
								IN  		CFileAuditLogInfo    auditRecord,
								IN  		int					 nFindRecordFlag )
{
	try
	{
		_bstr_t				 bstrSQL_Sentence;
		_bstr_t				 bstrGetRecordCount;

		CFileAuditLogInfo    auditRecord;

		SelectSentenceConversion( bstrSQL_Sentence,
								  bstrGetRecordCount,
								  auditRecord,
								  nFindRecordFlag );

		_RecordsetPtr pTempRecord = m_pConnection->Execute( bstrGetRecordCount,
															NULL,
															adCmdText );

		_variant_t    vResult  =
							pTempRecord->GetFields()->GetItem("Count")->GetValue();

		dwGetRecordCount = vResult.lVal;

		m_pRecord = m_pConnection->Execute( bstrSQL_Sentence, NULL, adCmdText );

	}
	catch ( _com_error e )
	{
		return -1;
	}
	return 0;
}

int CVisitDatabaseInterface::Test_RecordSetPro(_RecordsetPtr pRecord)
{
	if( pRecord )                      //if the _RecordsetPtr is invalid or is closed,return
	{
		if ( pRecord->State == adStateClosed )
		{
			return -1;
		}
	}
	
	if( NULL == pRecord->BOF )                  //make sure the cursor is in the first
	{
		pRecord->MoveFirst();
	}

	while( NULL == pRecord->adoEOF )
	{
		ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_FileOpeateProcessMutex, -1 );

		for( int i = 0; i < 8; i++ )
		{
			pRecord->GetFields()->GetItem( long(i) )->GetValue();
		}
		Sleep( 1000 * 5 );

		pRecord->MoveNext();

		if( pRecord )                      //if the _RecordsetPtr is invalid or is closed,return
		{
			if ( pRecord->State == adStateClosed )
			{
				return -1;
			}
		}
	}

	return 0;
}

int CVisitDatabaseInterface::DeleteAuditLogFromDB()
{
	try
	{
		string strTestSQL = "TRUNCATE TABLE FILEAUDITLOG";

		m_pConnection->Execute( strTestSQL.c_str(), NULL, adCmdText );

		return 0;

		string strSQL_Sentence =
					"SELECT NUMBER as Number FROM FILEPRO_CLIENTINFOQUERY,FILEAUDITLOG";

		_bstr_t strbs = strSQL_Sentence.c_str();

		_RecordsetPtr pTempRecord = m_pConnection->Execute(strbs, NULL, adCmdText);

		if( pTempRecord->adoEOF )              //if no data, return
		{
			return -1;
		}
		
		_variant_t vTempNumber = pTempRecord->GetFields()->GetItem("Number")->GetValue();

//		pTempRecord->Close();

		DWORD nNumber = vTempNumber.lVal;
		
		string strGetRecordCount =
					"SELECT count(*) as Count from FILEAUDITLOG,FILEPRO_CLIENTINFOQUERY";

		strbs = strGetRecordCount.c_str();

		pTempRecord = m_pConnection->Execute(strbs, NULL, adCmdText);

		_variant_t    vResult  =
							pTempRecord->GetFields()->GetItem("Count")->GetValue();

		
		DWORD nCount = vResult.lVal;

//		m_pRecord->Close();
		
		if ( 100000 > nCount )
		{
			strSQL_Sentence = "DELETE FROM FILEAUDITLOG";
			
			strbs = strSQL_Sentence.c_str();
			
			m_pConnection->Execute(strbs, NULL, adCmdText);

			return 0;
		}
		
		while ( 0 < nCount )
		{
			nNumber += 80000;

			if ( 80000 <= nCount )
			{
				nCount -= 80000;
			}
			else
			{
				nCount = 0;
			}
			
			char szInfo[10] = {0};
			
			sprintf( szInfo, "%d", nNumber );

			strSQL_Sentence = "DELETE FROM FILEAUDITLOG WHERE NUMBER < ";
			
			strSQL_Sentence += szInfo;

			strbs = strSQL_Sentence.c_str();
			
			m_pConnection->Execute(strbs, NULL, adCmdText);
		}
	}
	catch ( _com_error e )
	{
		EXCEPTIONALERROR( e.Description(), IDS_HINT )
		return -1;
	}
	return 0;
}
