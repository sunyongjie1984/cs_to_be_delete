#ifndef _TASK_H_
#define _TASK_H_

#include "../baseclass/threadbase.h"

class CTask
{
public:
    CTask();
    virtual ~CTask();

public:
    virtual void Run(void * p) = 0;

public:
    inline void SetWorkThread(CThreadBase * pT)
    {
        m_pWorkThread = pT;
    };
    inline CThreadBase * GetWorkThread(void)
    {
        return m_pWorkThread;
    };

    inline int GetTaskNo(void) const
    {
        return m_iTaskNo;
    }
    inline void SetTaskNo(int iTaskNo)
    {
        m_iTaskNo = iTaskNo;
    }

    inline char * GetTaskName(void) const
    {
        return m_strTaskName;
    }
    inline void SetTaskParameter(char * p, int size)
    {
        m_iSize = size;
        m_pTaskParameter = (char *)malloc(m_iSize);
        memcpy(m_pTaskParameter, p, m_iSize);
    }
    inline void GetTaskParameter(char * p)
    {
        memcpy(p, m_pTaskParameter, m_iSize);

        if (NULL != m_pTaskParameter)
        {
            free(m_pTaskParameter);
        }
    }
public:
    void SetTaskName(char * strTaskName);
    bool GetTerminated(void);

protected:
    char * m_pTaskParameter;
    int m_iSize;

private:
    CThreadBase * m_pWorkThread;
    int           m_iTaskNo;
    char *        m_strTaskName;
};

#endif//_TASK_H_

