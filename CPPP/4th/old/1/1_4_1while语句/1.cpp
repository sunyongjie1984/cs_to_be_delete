#include <iostream>
using namespace std;
int main()
{

	// 扩展1
	char i; // 这种情况相当的有意思，到现在我不明白
	int j = 'a';
	cout << j << endl;
// 	while (cin >> i && i != 'a') 
	while (cin >> i && i != 97) // 这两句话是一样的，因为我定义i是字符型，对吧？
		cout << "I Love China" << endl;
	
    /*
	// 扩展2
//	char i; 
	char *p = "I Love China";
	int i;
	while (cin >> i && p != "42") 
		cout << "I Love China" << endl; */
	return 0;
}