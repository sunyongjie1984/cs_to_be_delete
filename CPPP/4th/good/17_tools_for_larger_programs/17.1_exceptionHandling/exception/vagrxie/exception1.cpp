#include <string>
#include <iostream>
#include <exception>
using namespace std;

class MyException : public exception
{
public:
	MyException(char const * astrDesc)
	{
		mstrDesc = astrDesc;
	}
	//	MyException() throw()
	//	{
	//	}
	// because class exception has a virtual deconstructor
	// rewrite the deconstructor is necessary in linux OS for g++
	// not like compiler in windows
	~MyException() throw()
	{
	}
	string mstrDesc;
};

int main(void)
{
	try
	{
		throw MyException("A My Exception");
	}
	catch(MyException e)
	{
		cout <<e.mstrDesc <<endl;
	}

	return 0;
}
