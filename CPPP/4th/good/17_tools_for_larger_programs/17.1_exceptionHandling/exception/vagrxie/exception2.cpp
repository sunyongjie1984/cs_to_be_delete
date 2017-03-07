#include <iostream>
#include <string>
using namespace std;
class MyException : public exception
{
public:
	MyException(const char* astrDesc)
	{
		mstrDesc = astrDesc;
	}
	MyException(const MyException& aoOrig)
	{
		cout << "Copy Constructor MyException" <<endl;
		mstrDesc = aoOrig.mstrDesc;
	}
	MyException& operator=(const MyException& aoOrig)
	{
		cout << "Copy Operator MyException" <<endl;
		if(&aoOrig == this)
		{
			return *this;
		}
		mstrDesc = aoOrig.mstrDesc;
		return *this;
	}
	~MyException() throw()
	{
		cout << "~MyException" <<endl;
	}
	string mstrDesc;
};
void exceptionFun()
{
	try
	{
		throw MyException("A My Exception");
	}
	catch(MyException e)
	{
		cout << e.mstrDesc <<" In exceptionFun." <<endl;
		e.mstrDesc = "Changed exception.";
		throw;
	}
}
int main(void)
{
	try
	{
		exceptionFun();
	}
	catch(MyException e)
	{
		cout << e.mstrDesc <<" Out exceptionFun." << endl;
		throw;
	}
	return 0;
}
