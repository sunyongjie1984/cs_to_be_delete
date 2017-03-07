#ifndef INT_SINGLY_LINKED_LIST
#define INT_SINGLY_LINKED_LIST
#include "IntSLLNode.h"
#include <iostream>
using namespace std;
class IntSLList {
public:
	IntSLList() 
	{
		head = 0;
		tail = 0;
	}
	IntSLList(int n);
    // 这是第三个构造函数
	// 还没有用好用明白。我回头看看C++ Primer的书，或者试试Sales_item.h
	IntSLList(istream &is) 
	{
		is >> *this; 
	}
	// 第四个拷贝构造函数
	IntSLList(const IntSLList &object) // 又能正确输出，又出错，为什么？
	{
		head = object.head;
		tail = object.tail;
		cout << 3; // 测试用
	}
    void setHead()
	{
		head = new IntSLLNode;
	}
	~IntSLList();
	int isEmpty()
	{
		return head == 0;
	}

	void addToHead(int);
	void addtoTail(int);
	
	int deleteFromHead();
	int deleteFromTail();

	void deleteNode(int);

	bool isInList(int) const;

	// 我加一个输出操作符重载
//	friend ostream& operator<<(ostream&, const IntSLList&);
	friend ostream& operator<<(ostream&, IntSLList&);
	friend istream& operator>>(istream&, IntSLList&); 
	// 我加一个返回链表头指针的函数
	IntSLLNode* getHead()
	{
		return head;
	}
	IntSLLNode* getTail()
	{
		return tail;
	}
private:
	IntSLLNode *head, *tail;
};
#endif
