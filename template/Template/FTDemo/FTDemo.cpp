//////////////////////////////////////////////////////////////
//  Template demostration
//
//
//
//
//
//////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
using namespace std;

//Macro
//#define minimum(p1, p2)  (p1 <= p2 ? p1 : p2)

//Function template
template <class T>
T minimum (T p1, T p2)
{
	return p1 <= p2 ? p1 : p2;
}

//Override the template for specified type
//Method 1
char* minimum (char* p1, char* p2)
{
	return strcmp(p1, p2) <= 0 ? p1 : p2;
}


//Method 2
template<> char* minimum<char *> (char* p1, char* p2)
{
	return strcmp(p1, p2) <= 0 ? p1 : p2;
}

/*
//Instantiating
int minimum (int p1, int p2)
{
	return p1 <= p2 ? p1 : p2;
}

double minimum (double p1, double p2)
{
	return p1 <= p2 ? p1 : p2;
}
*/
void main()
{
	int a = 5, b =10;
	cout << "The lesser between " << a << " and " << b << " is " << minimum(a, b) << endl;

	double x = 15.3, y =3.4;
	cout << "The lesser between " << x << " and " << y << " is " << minimum(x, y) << endl;


	//Override template
	char s1[] = "ABCDE";
	char s2[] = "Z1234";

	cout << "The lesser between  " << s1 << " and   " << s2 << "  is  " << minimum(s1, s2) << endl;
	cout << "The pointer to lessor between  " << (int)s1 << " and   " << (int)s2 << "  is  " << (int)(minimum(s1, s2)) << endl;

	//Type-safe
/*	minimum(a, y);

	unsigned int c = 0xFFFF;
	minimum(a, c);
*/

}