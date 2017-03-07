#pragma once

#include "session.h"
#include "thread_pool.h"

#define __SESSION_TASK__ CTemplateTask





class CTemplateTask : public CAbstractTask
{
public:
	CTemplateTask(const char * buff, apr_size_t len, apr_socket_t * channel)
	{
		m_len = len;
		m_channel = channel;
		m_buff = new char[m_len+1];
		memset(m_buff, 0, m_len+1);
		memcpy(m_buff, buff, m_len);
	}
	virtual ~CTemplateTask()
	{
		if (m_buff)
		{
			delete[] m_buff;
			m_buff = NULL;
		}
	}
	void start(void * data)
	{
		__QUERY_TICK_COUNT("m_d4_=", m_d4_);
		
		//LOG(2, "%s", m_buff);
		
		LOG(2,
			"[m_d0_-m_d1_=%.8lf]"
			"[m_d1_-m_d2_=%.8lf]"
			"[m_d2_-m_d3_=%.8lf]"
			"[m_d3_-m_d4_=%.8lf]"
			"[m_d0_-m_d4_=%.8lf]"
			"[len=%d][cmd=%s]",
			m_d1_-m_d0_,
			m_d2_-m_d1_,
			m_d3_-m_d2_,
			m_d4_-m_d3_,
			m_d4_-m_d0_,
			m_len,
			m_buff);
	}
	
	
protected:
	apr_socket_t * m_channel;
	char * m_buff;
	apr_size_t m_len;
private:
};



class CTestTask : public CAbstractTask
{
public:
	CTestTask(CListBox &listbox) : m_task_index(0)
	{
		m_listbox = &listbox;
	}
	
	virtual ~CTestTask(){}
	
	void start(void * data)
	{
		__QUERY_TICK_COUNT("m_d4_=", m_d4_);
		
		LOG(1,
			"[m_d0_-m_d1_=%.8lf]"
			"[m_d1_-m_d2_=%.8lf]"
			"[m_d2_-m_d3_=%.8lf]"
			"[m_d3_-m_d4_=%.8lf]"
			"[m_d0_-m_d4_=%.8lf]\r\n",
			m_d1_-m_d0_,
			m_d2_-m_d1_,
			m_d3_-m_d2_,
			m_d4_-m_d3_,
			m_d4_-m_d0_);
		return;
		
		char debugbuf[1024] = {0};
		int id = (int)data;
		
		sprintf(debugbuf, "\nindex:%.4d -- thread addr:%.8d", m_task_index, id);
		
		for (int i=0; i<10; i++)
		{
			sprintf(debugbuf+strlen(debugbuf), "--%d", i);
		}
		//printf("%s" "--", debugbuf);
		//OutputDebugString(debugbuf);
		//m_listbox->InsertString(0, debugbuf);
		LOG(1, "%S", debugbuf);
	}
	int m_task_index;
	CListBox * m_listbox;
};





