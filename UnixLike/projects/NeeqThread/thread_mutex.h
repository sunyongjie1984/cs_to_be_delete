///线程互斥锁CThreadMutex及自动锁CAutoMutex类定义
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: thread_mutex.h
功能说明:
作    者: 何李夫
开发日期: 2013-7-11   11:07:12
修改记录:
***********************************************************************/
#ifndef _THREAD_MUTEX_H_
#define _THREAD_MUTEX_H_

#include "config_env.h"


///线程互斥锁定义
class CThreadMutex
{
public:
	///构造函数，初始化临界区
	CThreadMutex();

    ///析构函数， 清除临界区
	~CThreadMutex();

	///进入临界区
	int32_t Acquire();

	///离开临界区
	int32_t Release();

    ///尝试进入临界区，失败返回非零
    int32_t TryAcquire();

private:
	///核心互斥量句柄
	pthread_mutex_t m_Mutex;

    ///封闭掉下面函数
    CThreadMutex(const CThreadMutex& one);
    CThreadMutex& operator=(const CThreadMutex& one);
};

///自动锁定义
class CAutoMutex
{
public:
    ///构造函数
	CAutoMutex(CThreadMutex* pMutex);

    ///析构函数
    ~CAutoMutex();

private:
	CThreadMutex* m_lpMutex;

    ///封闭掉下面函数
    CAutoMutex(const CAutoMutex& one);
    CAutoMutex& operator=(const CAutoMutex& one);
};

#endif
