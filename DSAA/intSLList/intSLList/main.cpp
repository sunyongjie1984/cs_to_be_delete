#include "IntSLList.h"
#include <iostream>
int main()
{
	// test addToHead addToTail isEmpty operator << 
	/*
	IntSLList list1;
	list1.addToHead(35);             
	list1.addtoTail(40);
	list1.addToHead(30);
	list1.addtoTail(55);
	cout << list1 << endl; 
	*/

	/*
	// test IntSLList(int const n);
	IntSLList list2(4);
	cout << list2 << endl;
	*/

	/*
	// test
	cout << list1.isEmpty() << endl; // 不空了 @.@
	list1.addtoTail(40);             // 从尾插一个40
	cout << list1.isInList(40) << endl; // 40在list1中么？答：在
	cout << list1 << endl; 
	IntSLList list2(4);
	cout << list2;
	*/

	/**/
	// test operator >>
	IntSLList list3;
	cin >> list3; // 输入重载也好用了，呵呵呵。还有个返回tail 的函数
	cout << list3 << endl; // 然后把head tail private起来，还要看看为什么要加
	               // object.head;object.tail,不可以直接用head.tail

	list3.reverse_list();
	cout << list3 << endl;
	
/*	
//	IntSLList list4(cin);
	IntSLList list4(3);
	IntSLList list5(list4);
//	IntSLList list5 = list4; // 和上面的例子比较，感觉拷贝构造和=重载
                             // 用的是一个函数，由操作系统来使用的。
	                         // 我下面试试 自己不设拷贝构造的情况
	std::cout << list4;      // 有问题啊，我明天好好试试。
	std::cout << list5;
*/

	return 0;
}