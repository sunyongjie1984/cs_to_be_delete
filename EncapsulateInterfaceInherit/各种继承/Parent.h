#include <iostream>
class Parent {
public:
	Parent(int var = -1)
	{
		pub = var;
		ptd = var;
		prt = var;
	}
public:
	int pub;
protected:
	int ptd;
private:
	int prt;
};

class Child1: public Parent {
public:
	int Getpub() { return pub; }
    int Getptd() { return ptd; }
	// 下面这个是试验用函数
	int Getptd2() { ptd++; std::cout << ptd; return ptd; }
//	int Getprt() { return prt; } // 错误！prt为父类私有成员，子类不可访问
};
class Child2: protected Parent {
public:
	int Getpub() { return pub; }
	int Getptd() { return ptd; }
//	int Getprt() { return prt; } // 错误！prt为父类私有成员，子类不可访问
};

class Child3: private Parent {
public:
	int Getpub() { return pub; }
	int Getptd() { return ptd; }
//	int Getprt() { return prt; } // 错误！prt为父类私有成员，子类不可访问
};
