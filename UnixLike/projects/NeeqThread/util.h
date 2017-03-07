/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: util.h
功能说明:
作    者: 何李夫
开发日期: 2013-10-11   14:33:32
修改记录:
***********************************************************************/
#ifndef _UTIL_H_
#define _UTIL_H_

#include "config_env.h"


///获取当前时间，格式：HHMMSSCC
/**
 *@return 返回HHMMSSCC格式的时间
 */
int getHHMMSSCC();

///获取高精度超时时刻
/**
 *@param int iTimeout 超时时间间隔，单位毫秒
 *@param timespec& ts 返回时刻
 *@return 0表示成功，其他值表示失败
 */
int getTimespec(int iTimeout, timespec& ts);

///计算时间差
/**
 *@param uint32_t uiHHMMSSCC HHMMSSCC格式的时间
 *@return 返回uiHHMMSSCC与当前时间的差值，单位毫秒
 *        <0表示输入时间早，>0表示输入时间迟
 */
int timeElapse(uint32_t uiHHMMSSCC);

#endif
