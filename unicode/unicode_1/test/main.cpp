#include "stdio.h"
#include <locale.h>

int main()
{
	printf("\t-?\t\t\t\tFor Help\n");

	printf("中文测试\n");

	//setlocale(LC_ALL,"zh_CN.UTF-8");

	setlocale(LC_ALL, "chs");

	wprintf(L"中文测试\n");

	printf("w0:%ls\n", L"中文测试");

	wprintf(L"w1:%s\n", L"1中文测试 宽字符");

	wprintf(L"w2:%ls\n", L"2中文测试 宽字符");

	wprintf(L"w3:%ls\n", L"3tDirectory 中文测试 宽字符 end");

	wprintf(L"w4:%S\n", L"4 中文测试 宽字符 end");

	printf("w5:%S\n", L"中文测试\n");
	return 0;
}

//本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/chief1985/archive/2010/11/09/5998546.aspx