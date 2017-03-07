#include <iostream>
#include "myException.h"
void func()
{
	CMyException a("wangjie");
	CMyException2 b(23);
	a.right = "xiao gou";
	try
	{
		// throw a;

		// this will be catched out side this function
	    // because this function can only catch exception
	    // with the type CMyException
		throw b;
	}
	catch (CMyException2 e)
	{
		std::cout << "in func" << std::endl;
	}
}

int main()
{
	CMyException a("sunyongjie");	
	a.right = "China";
	CMyException2 b(3);
	try
	{
		// throw a;
		throw b;
		func();
		// int zero = 0;
		// int cc = 3/zero; // this is seemly a system exception
		std::cout << "no exception" << std::endl;
	}
	catch (CMyException e)
	{
		std::cout << e.what() << std::endl;
		// using exception machnism
        // user define exception can specify anything you want
		// like member function or member data
		// it is more flexible for programmer
		std::cout << e.right << std::endl;
	}
	catch (CMyException2 e2)
	{
		std::cout << e2.what()  << std::endl;
	}
	catch (...)
	{
		std::cout << "unknown exception"  << std::endl;
	}
	return 0;
}
