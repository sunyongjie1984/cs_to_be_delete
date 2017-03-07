/*****************************************************************
*Role:The file manage Linux thread ,include create thread etc.   *
*CopyRight(c):                                                   *
*       flydish,2004,06,25                                       *
*History:                                                        *
*       Create by flydish,2004,06,25                             *
*****************************************************************/

#include "Job.h"

CJob::CJob(void)
:m_pWorkThread(NULL)
,m_JobNo(0)
,m_JobName(NULL)
{
}

CJob::~CJob()
{
    if(NULL != m_JobName)
	free(m_JobName);
}

bool CJob::GetTerminated(void)
{
    return false;
}

void CJob::SetJobName(char* jobname)
{
    if(NULL !=m_JobName)
    {
	free(m_JobName);
	m_JobName = NULL;
    }
    if(NULL !=jobname)
    {
	m_JobName = (char*)malloc(strlen(jobname)+1);
	strcpy(m_JobName,jobname);
    }
}

