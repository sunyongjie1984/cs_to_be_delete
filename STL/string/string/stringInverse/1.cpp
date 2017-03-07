#include <iostream>
int main()
{
	char* p = "I Love China";
	p = "hehe";
//	*p = 'a'; // 这是绝对不行的，可是为什么程序员面试宝典中却说可以这么做
	std::cout << p << std::endl;
	std::cout << ++p << std::endl;
	return 0;
}