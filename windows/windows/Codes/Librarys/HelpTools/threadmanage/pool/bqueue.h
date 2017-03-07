#ifndef _BQUEUE_H_
#define _BQUEUE_H_




#include "../thread/synch.h"
#include "../../debuglog/debuglog.h"




template <class T>
class __EXPORT_DLL CBQueue
{
public:
	CBQueue() { InitQueue(); }
	virtual ~CBQueue() { }


	inline void InitQueue(void)
	{
		sprintf(m_szQueueName, "%p", this);

		CSynchEvent tmpSynch(m_szQueueName);
		m_list.clear();
	}

	inline void AppendQueue(T p)
	{
		CSynchEvent tmpSynch(m_szQueueName);
		m_list.push_back(p);
	}

	inline int RemoveQueueNode(T p)
	{
		CSynchEvent tmpSynch(m_szQueueName);
		
		typedef std::vector<T>::iterator ITR;

		ITR pos = std::find(m_list.begin(), m_list.end(), p);
		
		if (pos != m_list.end())
		{
			m_list.erase(pos);
			return __SUCCESS;
		}
		return __FAILED;
	}

	inline T GetQueueFrontNode()
	{
		CSynchEvent tmpSynch(m_szQueueName);

		T tRet;

		if (0 < m_list.size())
		{
			tRet = m_list.front();
		}
		return tRet;
	}

	inline T GetAt(int i)
	{
		CSynchEvent tmpSynch(m_szQueueName);

		T tRet;
		if ((i < m_list.size())&&(i >= 0))
		{
			tRet = m_list[i];
		}
		return tRet;
	}

	inline long GetQueueSize()
	{
		CSynchEvent tmpSynch(m_szQueueName);
		return m_list.size();
	}


private:
	char m_szQueueName[20];
	std::vector<T> m_list;
};



#endif//_BQUEUE_H_