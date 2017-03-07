#include <iostream>
#include <string>
using namespace std;

class ConstRef
{
public:

	ConstRef(int ii);

private:

	int i;
	const int ci;
	int& ri;
};

/*ConstRef::ConstRef(int ii)
{
	i = ii;
	//ci = ii;  must be initialized in constructor base/member initializer list
	ri = i;
}*/

ConstRef::ConstRef(int ii):i(ii), ci(i), ri(ii){ } 
// 初始化const或引用类型数据成员的唯一机会是在构造函数初始化列表中

class Z 
{ 
public:
	int p;
	string s;
	Z(int i):p(i){}
} ;


class X
{
public:
	X(int val):j(val),i(j),z(val),c(val),a(val){*p = val;} 
	int getVal(){return i;}
	Z z;
	int* p;
	const int c;
	int& a;

private:
	int j;
	int i;
	
	
};


struct Y 
{
	Y(int i,int j):base(i),rem(base%j){}
	int getBase(){return base;}
	int getRem(){return rem;}
	int base,rem;
} y(1,5);


int main()
{	
	int i = 3;
	cout << i << endl;
	X x(i);
	cout << x.getVal() << endl;
	cout << y.getBase() << endl;
    cout << y.getRem() << endl;

	//X *p = new X[10];
	//Z *po = new Z[10];
	return 0;
}