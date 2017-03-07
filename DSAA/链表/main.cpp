#include "Student.h" // 1，为什么直接输入字母就出错呢？
int main()
{
	Student s1;
	s1.print();
	int i;
//	s1.del(s1.h, 3); // 链表的删除有待详细想
	std::cin >> i;
	std::cout << i;
	std::cout << std::endl;
	return 0;
}