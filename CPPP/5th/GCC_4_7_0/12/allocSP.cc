#include <vector>
using std::vector;

#include <string>
using std::string;

#include <memory>
using std::make_shared; using std::shared_ptr;

#include <iostream>
using std::istream; using std::ostream; 
using std::cin; using std::cout; using std::endl;

#include "Foo.h"

// factory returns a shared_ptr to a dynamically allocated object 
shared_ptr<Foo> factory(T arg)
{
	// process arg as appropriate
	// shared_ptr will take care of deleting this memory
	return make_shared<Foo>(arg); 
}

shared_ptr<Foo> use_factory(T arg)
{
	shared_ptr<Foo> p = factory(arg);
	print(cout, *p);
	cout << endl;
	// use p
	return p;  // reference count is incremented when we return p
} 

int main()
{
	T arg;
	while (cin >> arg)
		use_factory(arg);
}

