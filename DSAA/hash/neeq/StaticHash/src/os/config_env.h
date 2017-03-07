///跨平台环境配置头文件定义
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: config_env.h
功能说明:
作    者: 何李夫
开发日期: 2013-7-11   9:13:37
修改记录:
***********************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <new>
#include <error.h>
#include <syslog.h>

#include "os/config_posix.h"


#define FBASE_NEW new(std::nothrow)

/* os库的版本信息 */
#define NEEQ_OS_VERSION     "V2.0.0 ("__DATE__" "__TIME__")"

#endif
