#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
template <typename T1, typename T2>
T1& print(T1 &s, T2 val)
{
	s << val;
	return s;
}
int main()
{
	double dval = 0.88;
	float fval = -12.3;
	string oristr = "this is a test", desstr;
	ostringstream oss(desstr);
	ofstream outFile("result.dat");

	print(cout, -3) << endl;
	print(cout, dval) << endl;
	print(cout, fval) << endl;
	print(cout, oristr) << endl;




	return 0;
}
