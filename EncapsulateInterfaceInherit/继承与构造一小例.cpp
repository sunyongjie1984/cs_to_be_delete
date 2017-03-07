#include <iostream>
class Base {
//private:
protected:
	int i;
public:
	Base(int x) 
	{
		i = x; std::cout << i << " ";
	}
};
class Derived : public Base {
private:
	int i;
public:
	Derived(int x, int y) : Base(s)
	{
		i = y; std::cout << a << " " << y << std::endl;
	}
	void printTotal()
	{
		int total = i + Base::i;
	}
};
int main()
{
	Derived d(4, 3);
	return 0;
}