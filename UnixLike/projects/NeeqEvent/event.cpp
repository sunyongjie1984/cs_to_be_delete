///事件 CEvent 类实现
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: event.cpp
功能说明:
作    者: 何李夫
开发日期: 2013-7-11   9:15:46
修改记录:
***********************************************************************/
#include "util.h"
#include "event.h"

#include "event_id.h"


CEvent::CEvent()
: m_bNotify(false)
{
    /* 按缺省的属性初始化 */
    pthread_cond_init(&m_Cond, NULL);
    pthread_mutex_init(&m_Mutex, NULL);
}

CEvent::~CEvent()
{
    /* 销毁对象 */
    pthread_cond_destroy(&m_Cond);
    pthread_mutex_destroy(&m_Mutex);
}

int32_t CEvent::Wait(int32_t iWait /* = INFINITE */)
{
    int32_t iRet = pthread_mutex_lock(&m_Mutex);
    if (iRet != 0)
    {
        return iRet;
    }

    while (!m_bNotify)
    {
        if (iWait < 0)
        {
            /* 无限期条件等待 */
            iRet = pthread_cond_wait(&m_Cond, &m_Mutex);
        }
        else
        {
            /* 超时条件等待 */
            timespec tm;
            getTimespec(iWait, tm);
            iRet = pthread_cond_timedwait(&m_Cond, &m_Mutex, &tm);
        }

        if (iRet != 0)
        {
            pthread_mutex_unlock(&m_Mutex);
            return iRet;
        }
    }

    m_bNotify = false;
    pthread_mutex_unlock(&m_Mutex);
    return EVENT_OK;
}

int32_t CEvent::Set()
{
    int32_t iRet = pthread_mutex_lock(&m_Mutex);
    if (iRet != 0)
    {
        return iRet;
    }
    m_bNotify = true;

    iRet = pthread_cond_signal(&m_Cond);
    if (iRet != 0)
    {
        pthread_mutex_unlock(&m_Mutex);
        return iRet;
    }

    iRet = pthread_mutex_unlock(&m_Mutex);
    if (iRet != 0)
    {
        return iRet;
    }

    return 0;
}

int32_t CEvent::Reset()
{
    int32_t iRet = pthread_mutex_lock(&m_Mutex);
    if (iRet != 0)
    {
        return iRet;
    }
    m_bNotify = false;

    iRet = pthread_mutex_unlock(&m_Mutex);
    if (iRet != 0)
    {
        return iRet;
    }

    return 0;
}
