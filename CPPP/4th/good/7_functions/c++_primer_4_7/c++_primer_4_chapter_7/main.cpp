#include <iostream>

//int add(int i) 
//{
//	return 10;
//}

// 可基于函数的引用形参是指向const对象还是指向非const对象实现函数重载
int add(int const & i) // 这两个可以，加上上面的就不行了。强调引用。
{
	return 12;
}

int add(int& i)
{
	return 13;
}

int main()
{
	int a = 10;
	int const b = 20;
	std::cout << add(a) << std::endl;
	std::cout << add(b) << std::endl;
	return 0;
}