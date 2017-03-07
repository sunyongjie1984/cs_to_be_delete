#include <iostream>
#include <string>
using namespace std;
using std::string;


//void main1()
//{
//	std::string s("Hello World!!!");
//	std::string::size_type punct_cnt = 0;
//	for(std::string::size_type index = 0; index != s.size(); ++ index)
//	{
//		if(ispunct(s[index]))
//		{
//			++punct_cnt;
//		}
//	}
//	std::cout << punct_cnt << " punctuation characters in " << s << std::endl;
//}
//
//void main2()
//{
//	string s("Hello World!!!");
//	string::size_type punct_cnt = 0;
//	for(string::size_type index = 0; index != s.size(); ++ index)
//	{
//		if(ispunct(s[index]))
//		{
//			++punct_cnt;
//		}
//	}
//	cout << punct_cnt << " punctuation characters in " << s << endl;
//}

void main3()
{
	string s("Hello World!!!");
	string::size_type punct_cnt = 0;
	for(string::size_type index = 0; index != s.size(); ++ index)
	{
		if(ispunct(s[index]))
		{
			++punct_cnt;
		}
	}
	cout << punct_cnt << " punctuation characters in " << s << endl;
}