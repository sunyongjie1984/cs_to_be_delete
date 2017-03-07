///Linux平台下posix标准的环境配置头文件定义
/***********************************************************************
系统名称: 
模块名称:
文 件 名: config_posix.h
功能说明:
作    者: 
开发日期: 2013-7-11   9:14:00
修改记录:
***********************************************************************/
#ifndef _CONFIG_POSIX_H_
#define _CONFIG_POSIX_H_

#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <fnmatch.h>
#include <limits.h>
#include <ctype.h>
#include <sys/poll.h>
#include <netipx/ipx.h>


///定义linux/unix下目录路径字符串的最大长度
#ifndef MAX_PATH
    #define MAX_PATH			256
#endif

static const int INFINITE = (-1);

#endif
