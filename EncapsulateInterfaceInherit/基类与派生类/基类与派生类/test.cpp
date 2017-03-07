#include "a.h"
int main(int argc,char *argv[])
{
	// 这道题很有意思，让我知道了一些C++语言如何处理构造函数
	// B b的时候，如果B有构造函数，A也有构造函数，就A的B的都调用，通过调试设置断点得知
	// 如果A有构造函数，那么一定调用，无论你B有没有。这个题让我注释的很乱。
//	A *a = new A[3];
	A *pA; // 定义这样一个指针的时候，跟本就没有创建对象，也就是说，这里是不分配内存空间的
//	A *pA2; 

	B b; 
//	B b2;  

//	pA=&b; // 基类指针指向了派生类
//	pA2 = &b2;

//	pA->func(1); // func函数实参为整数的函数是虚函数？是，用派生类的
//	pA->func("haha"); // 否，还是用基类的函数

//	b.func("haha");
//	cout << A::object_count << endl;
//	delete *pA2;

//	cout << pA->number() << endl;
//	delete []a; // 删除之后
	cout << pA->number() << endl;
	return 0;
}