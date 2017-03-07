#include <iostream>
#include "myException.h"

void func()
{
	my_exception a("wangjie");
	my_exception2 const b(23);
	a.right = "xiao gou";
	try
	{
        // this will be caught out side this function
	    // because this function can only catch exception
	    // with the type CMyException2
        throw a;
		//throw b;
	}
	catch (my_exception2 const & e)
	{
		std::cout << "in func" << std::endl;
	}
}

int main()
{
	my_exception a("sunyongjie");	
	a.right = "China";
	my_exception2 const b(3);
	try
	{
		// throw a;
		// throw b;

		func();

		// int zero = 0;
		// int cc = 3/zero; // this is seemly a system exception
		std::cout << "no exception" << std::endl;
	}
	catch (my_exception const & e)
	{
		std::cout << e.what() << std::endl;
		// using exception mechanism
        // user define exception can specify anything you want
		// like member function or member data
		// it is more flexible for programmer
		std::cout << e.right << std::endl;
	}
	catch (my_exception2 const & e2)
	{
		std::cout << e2.what()  << std::endl;
	}
	catch (...)
	{
		std::cout << "unknown exception"  << std::endl;
	}
	return 0;
}
