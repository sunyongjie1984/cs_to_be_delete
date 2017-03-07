#include <iostream>
using namespace std;

int count;
char str;

void main2()
{
	//int max(int x,int y);
	int i = 56;
	int j = 78;
	int max(int x,int y);
	cout << count << endl;
	cout << str << endl;
	int p = max(i,j);
	cout << p << endl;
	const int* str1  = &i;
	const int* str2  = &i;
	str2++;
	str2 = str1;
	int* str3  = &j;
	int* str4  = &j;
	int* const str5 = &j;
	*str5 = i;
	const int* str6 = &j;
	cout << boolalpha << ( str1==str2 ) << endl; // 输出什么？
	cout << boolalpha << ( str3==str4 ) << endl; // 输出什么？
	cout << boolalpha << ( str5==str6 ) << endl; // 输出什么？

	
}


int max(int x,int y)
{
	++count;
	int z;
	if(x>y)
	{	
		z = x;
	}
	else
	{
		z = y;
	}
	cout << count << endl;
	return z;
}


int min(const int x,const int y)
{
	int z;
	if(x>y)
	{	
		z = y;
	}
	else
	{
		z = x;	
	}
	return z;
}
