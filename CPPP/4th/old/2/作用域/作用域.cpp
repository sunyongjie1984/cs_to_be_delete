#include <iostream>
#include <string>
using namespace std;
string s1 = "hello"; // s1 has a global scope
int main()
{
	string s2 = "world"; // s2 has a local scope 
	cout << s1 << " " << s2 << endl;
	int s1 = 42;
	cout << s1 << " " << s2 << endl;
	return 0;
}