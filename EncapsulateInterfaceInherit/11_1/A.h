#include <iostream>
using namespace std;
class A {
public:
	void virtual f()
	{ 
		cout << "A" << endl;
	}
};
class B: public A {
public:
	void virtual f()
	{
		cout << "B" << endl;
	}	
};


