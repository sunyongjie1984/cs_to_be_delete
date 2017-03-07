#include <iostream>
#include "IntSLList.h"
IntSLList::IntSLList(int n) 
{
	head = new IntSLLNode; // 疯了，它的节点数据节构有构造函数，孙永杰，你这回学到东西了
	IntSLLNode *p1 = head;
	cout << "请输入第 1个节点的值" << endl;
	cin >> head->info;
	for (int i = 0; i < n - 1; i++)
	{
		IntSLLNode *p2 = new IntSLLNode;
		cout << "请输入第 "<< i + 2 <<"个节点的值" << endl;
		cin >> p2->info;
		p1->next = p2;
		p1 = p2;
	}
	tail = p1;
	tail->next = NULL; // 两件事，1，把这里注释掉；2，将IntSLLNode里的next = 0 注释掉，自己看吧
}

IntSLList::~IntSLList()
{
	for (IntSLLNode *p; !isEmpty(); )
	{
		p = head->next;
		delete head;
		head = p;
	}
}

void IntSLList::addToHead(int el)
{
	head = new IntSLLNode(el, head);
	if (tail == 0)
	{
		tail = head;
	}
}

void IntSLList::addtoTail(int el)
{
	if (tail != 0)
	{
		tail->next = new IntSLLNode(el);
		tail = tail->next;
	}
	else
	{
		head = tail = new IntSLLNode(el);
	}
}

int IntSLList::deleteFromHead()
{
	int el = head->info;
	IntSLLNode *tmp = head;
	if (head == tail)
	{
		head = tail = 0;
	}
	else
	{
		head = head->next;
	}
	delete tmp;
	return el;
}

int IntSLList::deleteFromTail()
{
	int el = tail->info;
	if (head == tail)
	{
		delete head;
		head = tail = 0;
	}
	else
	{
		IntSLLNode *tmp;
		for (tmp = head; tmp->next != tail; tmp = tmp->next);
		delete tail;
		tail = tmp;
		tail->next = 0;
	}
	return el;
}

void IntSLList::deleteNode(int el)
{
	if (head != 0)
	{
		if (head == tail && el == head->info)
		{
			delete head;
			head = tail = 0;
		}
		else if (el == head->info)
		{
			IntSLLNode *tmp = head;
			head = head->next;
			delete tmp;
		}
		else
		{
			IntSLLNode *pred, *tmp;
			for (pred = head, tmp = head->next; tmp != 0 && !(tmp->info == el);pred = pred->next, tmp = tmp->next);
            if (tmp != 0)
			{
				pred->next = tmp->next;
				if (tmp == tail)
				{
					tail = pred;
				}
				delete tmp;
			}
		}
	}
}

bool IntSLList::isInList(int el) const
{
	IntSLLNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
	return tmp != 0;
}

/*
ostream& operator<<(ostream &os, IntSLList &object) // 能用了，不过我把head与tail弄成public了
{                                                   // 我加一个成员函数用来返回头指针不就好了
	for (IntSLLNode *p = object.head; p != NULL; p = p->next) // 试试看，呵呵
	{
		os << p->info << " ";
	}
	return os;
}
*/
// 干的不错孙永杰，这个输出弄的不错么@.@~
ostream& operator<<(ostream &os, IntSLList &object)
{
	for (IntSLLNode *p = object.getHead(); p != NULL; p = p->next)
	{
		os << p->info << " ";
	}
	return os;
}
// 这种情况现在是可以用了，我试着删掉一些东西看看。   // 这是在head,tail是public的情况下的
/*istream& operator>>(istream &is, IntSLList &object) // 我的这个程序有很多的地方要改，简直
{                                                     // 保留的地方少。
	object.head = new IntSLLNode;
	cin >> object.head->info;
	IntSLLNode *p1 = object.head;
	int x;
	while (std::cin >> x) // 这个位置以前用字母来结束的时候会出问题
	{                     // 现在没有了，可能是因为节点的构造函数每生成一个的时候都是指针域赋值0的。
		IntSLLNode *p2 = new IntSLLNode;
		p2->info = x;
		p1->next = p2;
		p1 = p2;
	}
//	object.tail = p1; // 为什么注释了这个也可以，我要看看我的输出符
	return is;        // 我的输出符重载函数根本没有用到tail
}*/

/*
// 这个输入是head,tail,private的时候。
istream& operator>>(istream &is, IntSLList &object)
{
	IntSLLNode *h = object.getHead();
//	IntSLLNode *t = object.getTail(); 有用么，要设置它么？
	IntSLLNode *p1 = h;
	p1 = new IntSLLNode; // 这里错的很可怕好好顺一顺，看看错的有多惨。
	std::cin >> h->info;
	int x;
	while (std::cin >> x)
	{
		IntSLLNode *p2 = new IntSLLNode;
		p2->info = x;
		p1->next = p2;
		p1 = p2;
	}
	p1->next = 0;
	return is;
}*/

// 我终于成功了
istream& operator>>(istream &is, IntSLList &object)
{
	// 我想了很久实在想不出什么其它办法，只有填加一个设置头节点的函数了，试试看。
	object.setHead();
	IntSLLNode *h = object.getHead();
	std::cin >> h->info;
	int x;
	while (std::cin >> x)
	{
		IntSLLNode *p2 = new IntSLLNode;
		p2->info = x;
		h->next = p2;
		h = p2;
	}
	return is;
}




	

