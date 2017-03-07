#include <iostream>
//#include <string> 为什么strcpy这个函数不用string这个头文件呢？
using namespace std;
void GetMemory(char**, int );
int main()
{
	char *str = NULL;

	GetMemory(&str, 100 );
	strcpy(str, "hello" );

	cout << *str << endl;
	cout << str << endl;
	cout << &str << endl;
	return 0;
}

void GetMemory(char** p, int num )
{
	*p = (char* )malloc(sizeof(char ) * num );
}


