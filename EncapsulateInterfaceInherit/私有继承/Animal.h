#include <iostream>
using namespace std;
class Animal {
public:
	Animal() { }
	void eat() 
	{
		cout << "eat" << endl;
	}
};
class Giraffe: private Animal {
public:
	Giraffe() { }
	void StrechNeck() 
	{
		cout << "strech neck" << endl;
	}
};
class Cat: public Animal {
public:
	Cat() { }
	void Meaw()
	{
		cout << "meaw" << endl;
	}
};

