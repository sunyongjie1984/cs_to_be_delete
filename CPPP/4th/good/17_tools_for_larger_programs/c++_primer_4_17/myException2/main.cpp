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
			throw runtime_error("IO stream fail()"); // ok
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "unknown exception" << endl;
	}
	cout << i << endl;
	return 0;
}
