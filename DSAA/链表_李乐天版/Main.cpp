#include "Student.h" // 1，为什么直接输入字母就出错呢？
//#include <stdio.h>
#include <iostream>
int main()
{
	Student s1;
	s1.print();

	int i=0;
	std::cin >> i;
	std::cout << i << std::endl;
	return 0;
}