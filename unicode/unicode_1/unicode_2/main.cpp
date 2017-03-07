#include <iostream>
using namespace std;
int main()
{
	char* p = "I love China";
	wchar_t* p1 = L"I love China";
	char* p2 = "我是中国人";
	wchar_t* p3 = L"我是中国人";

	std::cout  << p << std::endl; // 对于p这两个函数都运转正常
	std::wcout << p << std::endl;

	std::cout  << std::endl;

	std::cout  << p1 << std::endl; // 失败
	std::wcout << p1 << std::endl; 

	std::cout << std::endl;

	std::cout << p2 << std::endl; // 两个函数都正常工作
	std::wcout << p2 << std::endl;

	std::cout << std::endl;

	std::wcout.imbue(std::locale("chs")); // 不加两个都不能工作，加上后第二个可以正常工作了
	std::cout << p3 << std::endl;
	std::wcout << p3 << std::endl;

	std::cout << std::endl;

	return 0;
}