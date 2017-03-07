#ifndef _SHARE_H_
#define _SHARE_H_


#pragma warning ( disable : 4786 )


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdarg.h>



#include <io.h>
#include <fcntl.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>


#include <winsock2.h>
#include <windows.h>
#include <process.h>



#define __SUCCESS	0
#define __FAILED	-1
#define __EXCEPTION 1


#define __EXPORT_DLL __declspec (dllexport)


//#define __TDebug

/*ÏûÏ¢*/
#define WM_DEBUG_LOG WM_USER + 1002
#define WM_EXIT_LOG WM_USER + 1003




#define DETECT(T) (int)(__SUCCESS == (T) ? 1 : 0)



#pragma warning ( disable : 4251 )



template<typename T>
std::string Frm(const T &vT)
{
	std::ostringstream os;
	os << vT;
	return os.str();
}





typedef std::list<std::string> StringList;



#endif//_SHARE_H_
