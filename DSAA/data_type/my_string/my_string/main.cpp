#include "my_string.h"
#include <iostream>
int main()
{
	my_string str("sunyongjie");
	my_string str2(str);
	my_string str3 = str;
	std::cout << str << std::endl;
	std::cout << str2 << std::endl;
	std::cout << str3 << std::endl;
	return 0;
}

