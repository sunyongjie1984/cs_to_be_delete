#include <vector>
#include <iostream>
using namespace std;

struct Exmpl
{
	//默认构造函数
	Exmpl()
	{
		cout << "Exmpl()" << endl;
	}
	//复制构造函数
	Exmpl(const Exmpl&)
	{
		cout << "Exmpl(const Exmpl&)" << endl;
	}
	//赋值构造函数
	Exmpl& operator = (const Exmpl&)
	{
		cout << "operator = (const Exmpl&)" << endl;
		return *this;
	}
	//析构函数
	~Exmpl()
	{
		cout << "~Exmpl()" << endl;
	}
};

void func1(Exmpl obj)      //形参为Exmpl对象
{

}

void func2(Exmpl& obj)     //形参为Exmpl对象的引用
{

}

Exmpl func3()
{
	Exmpl obj;
	return obj;           //返回Exmpl对象
}



int main()
{
	Exmpl eobj;         //调用默认构造函数创建Exmpl对象
	func1(eobj);        //调用复制构造函数
						//将形参Exmpl对象创建为实参Exmpl对象的副本
						//函数执行完毕后调用析构函数撤销形参Exmpl对象

	func2(eobj);        //形参为Exmpl对象的引用，无需调用复制构造函数传递实参
	eobj = func3();     //调用默认构造函数创建局部Exmpl对象
						//函数返回时调用复制构造函数创建作为返回值副本的Exmpl对象
						//然后调用析构函数撤销局部Exmpl对象
						//然后调用复制操作符
						//执行完赋值操作后
						//调用析构函数撤销作为返回值副本的Exmpl对象

	Exmpl* p = new Exmpl;    //调用默认构造函数动态创建Exmpl对象
	vector<Exmpl> evec(3);   //调用默认构造函数
							 //创建一个临时值对象
						     //然后3次使用复制构造函数
							 //将临时值Exmpl复制到vector容器evec的每个元素
							 //然后调用析构函数撤销临时值Exmpl对象
	delete p;                //调用析构函数撤销动态创建的P对象
	
	return 0;                //evec及eobj生命期结束，自动调用析构函数撤销
							 //撤销evec需调用析构函数3次（因为evec有3个元素）
	     

}