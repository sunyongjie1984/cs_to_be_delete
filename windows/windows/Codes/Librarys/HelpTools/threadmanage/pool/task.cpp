#include "task.h"
#include "../../debuglog/debuglog.h"





CBTask::CBTask() : m_pTaskData(NULL)
{

}

CBTask::~CBTask()
{
	if (m_pTaskData)
	{			
		delete[] m_pTaskData;
		m_pTaskData = NULL;
	}
}

void CBTask::InitTaskData(void * p, int len)
{
	m_pTaskData = new byte[len];
	if (m_pTaskData)
	{
		memset(m_pTaskData, 0, len);
		memcpy(m_pTaskData, p, len);
	}
}

void * CBTask::GetTaskData(void)
{
	return m_pTaskData;
}


void CBTask::SetTaskName(std::string &strTaskName)
{
	m_strTaskName = strTaskName;
}


std::string CBTask::GetTaskName(void)
{
	return m_strTaskName;
}
