#include "String.h"
#include <iostream>
int main()
{
	String str("sunyongjie");
	String str2(str);
	String str3 = str;
	std::cout << str << std::endl;
	std::cout << str2 << std::endl;
	std::cout << str3 << std::endl;
	return 0;
}

