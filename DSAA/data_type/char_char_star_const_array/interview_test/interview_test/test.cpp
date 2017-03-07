#include <iostream>
using namespace std;

void main()
{
	char str1[]       = "abc";
	char str2[]       = "abc";
	const char str3[] = "abc"; 
	const char str4[] = "abc";
	const char* str5  = "abc";
	const char* str6  = "abc";
	cout << boolalpha << ( str3==str4 ) << endl; // 输出什么？
	cout << boolalpha << ( str5==str6 ) << endl; // 输出什么？
	str6++;
	//*str6 = "edf";
	str6 = str1;
	char* str7  = "edf";
	char* str8  = "edf";
	*str8 = 'a';
	char * const str9 = "edf";
	//*str9 = 'h';
	cout << *str9 << endl;
	char* str10 = "abcdef";
	
	str7 = str1;
	cout << boolalpha << ( str1==str2 ) << endl; // 输出什么？
	cout << boolalpha << ( str3==str4 ) << endl; // 输出什么？
	cout << boolalpha << ( str5==str6 ) << endl; // 输出什么？
	cout << boolalpha << ( str7==str8 ) << endl; // 输出什么？
}




