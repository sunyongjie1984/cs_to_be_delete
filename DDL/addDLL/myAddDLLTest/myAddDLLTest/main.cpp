#include <iostream>
// 方法一，包含头文件
#include "myAddDLL.h" // 这两种方法都可以，编译的时候需要.lib来编译
// 运行的时候编译器通过这两种声明知道是外部引进的函数

// 方法二，用extern
// extern int add(const int&, const int&); // OK
// class _declspec(dllexport) CBook;    // 只这样不行，综合而言，建议方法一。
//class _declspec(dllexport) CBook {
//public:
//	void print();
//};

int main()
{
	std::cout << add(3, 4) << std::endl;

	CBook a;
	a.print();
	return 0;
}