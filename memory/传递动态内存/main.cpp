#include <iostream>
using namespace std;
char* GetMemory(char* p, int num)
{
	p = (char*)malloc(sizeof(char) * num);
	return p;
}

int main()
{
	char* str = NULL;
	str = GetMemory(str, 100);
	strcpy(str, "hello");
	cout << str << endl;
	return 0;
}
