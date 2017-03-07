#include <iostream>
#include <string>
void GetMemory(char** p, int num)
{
	*p = (char* )malloc(num);
}
int main()
{
	char *str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "I Love China!");
//	strcpy(str, "I Love \0China!"); // 真的能够截断啊！
	printf(str);
	std::cout << std::endl;// 如何解决这个内存泄露问题呢，可以str == NULL?
	return 0;
}
