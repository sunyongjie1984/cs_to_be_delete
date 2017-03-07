///实现CThread线程基类
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: thread.cpp
功能说明:
作    者: 柳正龙
开发日期: 2013-9-7   9:14:45
修改记录:
***********************************************************************/
#include "util.h"
#include "thread.h"

#include "event_id.h"


void OnThreadExit(void* pArg)
{
	if (pArg)
	{
		CThread* pThread = (CThread* )pArg;

        pthread_mutex_lock(&pThread->m_CondMutex);
        pThread->m_bStarted = false;
        /** 通知Stop()调用者，线程已退出 */
        pthread_cond_signal(&pThread->m_Cond);
        pthread_mutex_unlock(&pThread->m_CondMutex);
	}
}

void* thread_function(void* pArg)
{
    void* rc = NULL;

	if (pArg)
	{
        CThread* pThread = (CThread* )pArg;

        /** 加锁防止线程过快结束，导致pthread_create返回失败，在调用者进入等待状态，这里才能加上锁 */
        pthread_mutex_lock(&pThread->m_CondMutex);
        pThread->m_bStarted = true;
        /** 提前设置线程退出清理函数，保证线程正常退出和kill退出都能正确设置线程状态 */
        pthread_cleanup_push(OnThreadExit, pThread);
        /** 通知Start()调用者，线程已启动 */
        pthread_cond_signal(&pThread->m_Cond);
        pthread_mutex_unlock(&pThread->m_CondMutex);

        /** 执行派生类线程执行体 */
    	rc = (void* )pThread->Run();

        /** 弹出并执行线程退出清理函数 */
        pthread_cleanup_pop(1);
	}

	return rc;
}

CThread::CThread()
: m_hThread(0)
, m_bStarted(false)
, m_bTerminateRequest(false)
{
	pthread_mutex_init(&m_CondMutex, NULL);
	pthread_cond_init(&m_Cond, NULL);
}

CThread::~CThread()
{
    if (m_bStarted)
    {
        Stop(100);
    }

    pthread_mutex_destroy(&m_CondMutex);
    pthread_cond_destroy(&m_Cond);
}

int32_t CThread::Start()
{
    int rc = 0;

    rc = pthread_mutex_lock(&m_CondMutex);
    if (rc != 0)
    {
        return rc;
    }

    /** 检查线程是否启动 */
	if (!m_bStarted)
    {
        m_bTerminateRequest = false;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, 1024 * 1024 * 10);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        /** 创建线程 */
        int rc = pthread_create(&m_hThread, &attr, thread_function, (void* )this);
        if (rc == 0)
        {
            /** 等待线程启动 */
            WaitCond();
        }

        pthread_attr_destroy(&attr);
    }
	
    rc = pthread_mutex_unlock(&m_CondMutex);
	return (int32_t)rc;
}

int32_t CThread::Stop(int iWait)
{
    int rc = 0;

	rc = pthread_mutex_lock(&m_CondMutex);
    if (rc != 0)
    {
        return rc;
    }

	/** 线程已启动且非线程自己调用 */
	if (m_bStarted && !pthread_equal(pthread_self(), m_hThread))
	{
		/** 通知线程停止 */
		Terminate();

        /** 等待线程Run()结束退出 */
		WaitCond(iWait);

		/** 线程已结束 */
        if (!m_bStarted)
        {
            m_bTerminateRequest = false;
        }
        else
        {
            /** 如果线程还没结束,简单粗暴杀线程 */
            if (pthread_cancel(m_hThread) == 0)
            {
                /** kill信号发出，说明该线程还在，10ms等待线程退出 */
                WaitCond(10);
            }

            /** 线程退出 */
            if (!m_bStarted)
            {
                m_bTerminateRequest = false;
            }
            else
            {
                /** 线程没杀掉，可能的情况：1，线程死锁；2，线程循环中不存在cancel点 */
                rc = -1;
            }
        }
	}

	rc = pthread_mutex_unlock(&m_CondMutex);
    return (int32_t)rc;
}

int CThread::WaitCond(int iWait)
{
    int rc = 0;

    if (iWait < 0)
    {
        rc = pthread_cond_wait(&m_Cond, &m_CondMutex);
    }
    else
    {
        timespec ts;
        getTimespec(iWait, ts);
        rc = pthread_cond_timedwait(&m_Cond, &m_CondMutex, &ts);
    }

    return rc;
}

const char* chOsVersion = NEEQ_OS_VERSION;
