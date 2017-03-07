#include <iostream>
#include <string>
using namespace std;
int main()
{
	char *ss = "0123456789" ;
//	cout << sizeof(ss ) << ' ' << strlen(*ss ) << endl;
	cout << sizeof(ss ) << ' ' << sizeof(*ss ) << endl;

	char ss2[] = "0123456789" ;
	cout << sizeof(ss2 ) << ' ' << sizeof(*ss2 ) << endl;

	char ss3[100] = "0123456789" ;
	cout << sizeof(ss3 ) << ' ' << strlen(ss3 ) << endl;

	int ss4[100] = "0123456789" ;
	cout << sizeof(ss4 ) <<  endl;
	return 0;
}