#include <iostream>

using std::cout;
using std::endl;

class A 
{
public:
	A() 
	{ 
		object_count++; 
	}
	~A()
	{ 
		object_count--; 
	}
	static int number() 
	{ 
		return object_count; 
	}
	virtual void func(int data)
	{
		cout << "class A:" << data << endl; 
	}
	void func(char *str) 
	{ 
		cout << "class A:" << str << endl;
	}
private:
	static int object_count;
};
class B: public A 
{
public:
	B() 
	{ 
	} 
	// …其它成员
public:
	void func()
	{ 
		cout << "function in B without parameter! \n"; 
	}
	void func(int data)
	{
		cout << "class B:" << data << endl;
	}
	void func(char *str)
	{ 
		cout << "class B:" << str << endl;
	}
};
int A::object_count = 0; // 这就是传说中的成员的实现。

