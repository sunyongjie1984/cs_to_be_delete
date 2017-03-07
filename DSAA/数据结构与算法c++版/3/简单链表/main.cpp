#include "intSLLst.h"
//#include <iostream.h>
int main()
{/*
	IntSLList list1;
	list1.addToHead(3); // 往头上加节点
	list1.addToHead(4);  
	list1.addToTail(5); // 往尾上加节点
	if (1 == list1.isEmpty())
	{
		cout << "这是一个空链表" << endl;
	}
	else
	{
		cout << "这个链表为" << endl;
	}
	list1.printAll(); // 输出链表
	list1.deleteFromHead(); // 删除头节点
	list1.printAll(); // 再次输出链表
	if(0 == list1.isInList(5))
		cout << "链表里面没有这个数" << endl;
	else
		cout << "Yes,There it is !  @.@~" << endl;*/
	IntSLList list2(3);

	list2.printAll();
	list2.deleteNode(3);
//	list2.printAll();
	std::cout << list2;
	
	return 0;
}