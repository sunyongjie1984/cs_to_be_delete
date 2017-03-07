///事件 CEvent 类定义
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: event.h
功能说明:
作    者: 何李夫
开发日期: 2013-7-11   9:14:45
修改记录:
***********************************************************************/
#ifndef _EVENT_H_
#define _EVENT_H_

#include "config_env.h"


///等待事件时返回值
#define EVENT_OK        0   /* 有事件发生 */
#define EVENT_TIMEOUT   110 /* 等待时间超时 */

///事件对象定义
class CEvent
{
public:
    ///构造函数
    CEvent();
    
    ///析构函数
    ~CEvent();
    
    ///等待一个事件
    /**
     *@param iWait 等待的时间，单位毫秒，默认为直到有事件发生
     *@return EVENT_OK表示成功等到该事件激活，EVENT_TIMEOUT表示超时，其他失败
     */
	int32_t Wait(int32_t iWait = INFINITE);
	
    ///激发该事件
    /**
     * @return EVENT_OK表示成功，其他表示失败
     */
	int32_t Set(void);
	
    ///重置事件状态为false 
    /**
     * @return EVENT_OK表示成功，其他表示失败
    */
    int32_t Reset(void);

private:
    pthread_mutex_t m_Mutex; /* 保护条件变量的互斥子 */
    pthread_cond_t m_Cond; /* 条件变量句柄 */    
    bool m_bNotify;

    ///封闭掉下面函数
    CEvent(const CEvent& one);
    CEvent& operator=(const CEvent& one);
};

#endif
