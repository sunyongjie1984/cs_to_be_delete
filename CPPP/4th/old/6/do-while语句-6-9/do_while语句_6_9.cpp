#include <iostream>
#include <string>
using namespace std;
int main()
{
	string rsp;
	do {
		cout << "please enter two values: " << endl;
		int val1, val2;
		cin >> val1 >> val2;
		cout << "The sum of " << val1 << " and " << val2
			 << " = " << val1 + val2 << "\n\n"
//		     << " More?  yes or no : ";
             << " 还计算不计算别的了？   y / n :__ "; 
		cin >> rsp;
	} while (!rsp.empty() && rsp[0] != 'n');
	return 0;
}