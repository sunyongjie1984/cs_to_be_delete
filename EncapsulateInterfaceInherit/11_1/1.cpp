#include "A.h"
int main()
{
	A* pa = new A(); 
	pa->f();
	B* pb = (B*)pa;
	// 这个题这里是有点意思的，这里将pa转化为指向B类型的指针不假，但是你没有给它赋新的值，它可
	// 还指着那块，你在new A()中返回的内存中分配的A类型的一个对象的地址呢@.@~.于是乎，你新建的
	// 指向B类型的指针pb,因为是pa的一个拷贝，所以也是指向new回来的那个对象的。
	pb->f();

	delete pa, pb;

	pa = new B();
	pa->f();
	pb = (B*)pa;
	pb->f();

	return 0;
}