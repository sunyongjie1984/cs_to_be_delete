#include "task.h"

CTask::CTask() : m_pWorkThread(NULL),
                 m_iTaskNo(0),
                 m_strTaskName(NULL),
                 m_pTaskParameter(NULL),
                 m_iSize(0)
{
}

CTask::~CTask()
{
    if(NULL != m_strTaskName)
    {
        free(m_strTaskName);
    }
}

void CTask::SetTaskName(char * strTaskName)
{
    if(NULL != m_strTaskName)
    {
        free(m_strTaskName);

        m_strTaskName = NULL;
    }

    if(NULL != strTaskName)
    {
        int size = strlen(strTaskName)+1;

        m_strTaskName = (char*)malloc(size);

        memset(m_strTaskName, 0, size);

        strcpy(m_strTaskName, strTaskName);
    }
}

bool CTask::GetTerminated(void)
{
    return false;
}

