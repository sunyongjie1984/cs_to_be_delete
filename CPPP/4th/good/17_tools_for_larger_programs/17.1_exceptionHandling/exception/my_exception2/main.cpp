#include <iostream>
#include <stdexcept>
using namespace std;
int main()
{
	int i;
	try
	{
		cin >> i;
		// when enter a char instead of an int cin.fail() become true
		if (cin.fail())
		{
			// throw; // can not be catched in catch(...), system abort, terminate prog
			throw runtime_error("IO stream fail()"); // ok
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "exception" << endl;
	}
	cout << i << endl;
	return 0;
}
