// Main.cpp : Defines the entry point for the console application.
//
//*******************************************************************
//              
//  FILE:       Main.cpp
//              
//  AUTHOR:     sam sha
//              
//  PROJECT:    mproxysvr2
//              
//  COMPONENT:  -
//              
//  DATE:       23.06.2003
//              
//  COMMENTS:   - 在Service.cpp开始处修改监听端口，及指定二级代理地址及端口
//                -I 装载服务  ； -U 卸载服务
//              
//*******************************************************************

// Includes

#include "stdafx.h"
#include "Service.h"
#include "mproxy3.h"


int main(int argc, char* argv[])
{
//	CMProxy3 _proxy2(11600,"main-svr",8080);
//测试程序使用1
/*	_proxy2.Start();
	Sleep(1000);
	_proxy2.Stop();
	Sleep(5000);
	return 0;
*/
/*
//测试程序使用2
	_proxy2.Start();
	
	while(1)
	{//要调试状态强制终止
		Sleep(1000);
	}
	return 0;
*/

	_Module.Init("mproxysvr3","mproxysvr3");
	if (argc > 1)
	{
		char seps[] = "-/";
		char *pToken;
		
		pToken = strtok(argv[1],seps);
		while (pToken)
		{
			if (!stricmp(pToken,"I"))
			{
				_Module.Install();
			}
			else if (!stricmp(pToken,"U"))
			{
				_Module.Uninstall();
			}
			pToken = strtok( NULL, seps );
			return 0;
		}
	}
	_Module.m_bService = TRUE;
	_Module.Start();

	return 0;
}
