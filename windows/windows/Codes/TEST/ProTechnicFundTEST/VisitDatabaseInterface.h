// VisitDatabaseInterface.h: interface for the CVisitDatabaseInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISITDATABASEINTERFACE_H__D9614003_FD5B_43B5_B681_BB84F2224E49__INCLUDED_)
#define AFX_VISITDATABASEINTERFACE_H__D9614003_FD5B_43B5_B681_BB84F2224E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProgrammeTechnicFund.h"

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

#define CONNECTION_TIME_OUT  60 * 1
#define COMMAND_TIME_OUT     60 * 30

class CVisitDatabaseInterface
{
public:

	_RecordsetPtr		m_pRecord;
	_ConnectionPtr		m_pConnection;
	
	ACE_Process_Mutex	m_FileOpeateProcessMutex;
	ACE_Thread_Mutex	m_ThreadMutex;

public:

	static CVisitDatabaseInterface * Instance();

public:
	
	VOID	ReleaseDatabaseConnection();


public:
	int DeleteAuditLogFromDB();
	int Test_RecordSetPro( _RecordsetPtr pRecord );
	
	int		RecordWriteIntoDatabase( vector<CFileAuditLogInfo> &auditRecord );

	VOID	InsertSentenceConversion( 
								IN		OUT     _bstr_t             &bstrSQL_Sentence,
								IN              CFileAuditLogInfo    auditRecord );

	int		ReadRecordFromDatabase(
								IN		OUT		DWORD				&dwGetRecordCount,
								IN		OUT		CFileAuditLogInfo    auditRecord,
								IN				int					 nFindRecordFlag );

	VOID	SelectSentenceConversion(
								IN		OUT		_bstr_t				&bstrSQL_Sentence,
								IN		OUT		_bstr_t				&bstrGetRecordCount,
								IN				CFileAuditLogInfo    auditRecord,
								IN				int					 nFindRecordFlag );


private:
	
	CVisitDatabaseInterface();
	
	virtual ~CVisitDatabaseInterface();


//编码规范
///////////////////////////类的静态成员变量（static member） 前缀 sm_ 
private:
	
	static CVisitDatabaseInterface * sm_pVisitDB;


//////////////////////////////私有成员函数的开头应当加上两个下划线“__”.	
private:
	int		__InitDatabaseConnection();

	int		__ParseConnectDbConfigurationFile(
								IN    OUT   string    &strConnection,
								IN          string     strIp,
								IN    OUT   string    &strUseID,
								IN    OUT   string	  &strPassWord );
		
};

#endif // !defined(AFX_VISITDATABASEINTERFACE_H__D9614003_FD5B_43B5_B681_BB84F2224E49__INCLUDED_)
