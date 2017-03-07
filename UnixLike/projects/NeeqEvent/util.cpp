/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: util.cpp
功能说明:
作    者: 何李夫
开发日期: 2013-10-11   14:43:20
修改记录:
***********************************************************************/
#include "util.h"


int getHHMMSSCC()
{
    struct timeval now;
    gettimeofday(&now, NULL);

    struct tm t;
    localtime_r(&now.tv_sec, &t);

    return t.tm_hour*1000000 + t.tm_min*10000 + t.tm_sec*100 + now.tv_usec/10000;
}

int getTimespec(int iTimeout, timespec& ts)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    ts.tv_sec = now.tv_sec + iTimeout / 1000; /* 秒 */
    ts.tv_nsec = now.tv_usec + (iTimeout % 1000) * 1000; /* 微秒 */
    if(ts.tv_nsec >= (1000*1000)) /* 秒数已经进位 */
    {
        ts.tv_sec++; /* 秒+1 */
        ts.tv_nsec = ts.tv_nsec % (1000 * 1000); /* 剩余微秒 */
    }
    ts.tv_nsec = ts.tv_nsec * 1000; /* 转换成纳秒 */

    return 0;
}

int timeElapse(uint32_t uiHHMMSSCC)
{
    int iHH1 = uiHHMMSSCC / 1000000;
    int iMM1 = uiHHMMSSCC % 1000000 / 10000;
    int iSS1 = uiHHMMSSCC % 10000 / 100;
    int iCC1 = uiHHMMSSCC % 100;

    int iCurrTime = getHHMMSSCC();
    int iHH2 = iCurrTime / 1000000;
    int iMM2 = iCurrTime % 1000000 / 10000;
    int iSS2 = iCurrTime % 10000 / 100;
    int iCC2 = iCurrTime % 100;

    return ((iHH1-iHH2)*3600 + (iMM1-iMM2)*60 + (iSS1-iSS2))*1000 + (iCC1-iCC2)*10;
}
