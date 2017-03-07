#include <iostream>
#include "IntSLList.h"

IntSLList::IntSLList()
{
    head = NULL; // 指针一定要用空值来赋。
    tail = NULL;
}

IntSLList::IntSLList(istream &is)
{
    is >> *this;
}

IntSLList::IntSLList(const int&  n)
{
    head = new IntSLLNode;
    if (NULL == head)
    {
        return;
    }
    IntSLLNode *p1 = head;
    cout << "请输入第 1个节点的值" << endl;
    cin >> head->info;
    for (int i = 0; i < n - 1; i++)
    {
        IntSLLNode *p2 = new IntSLLNode;
        if (NULL == p2)
        {
            return;
        }
        cout << "请输入第 "<< i + 2 <<"个节点的值" << endl;
        cin >> p2->info;
        p1->next = p2;
        p1 = p2;
    }
    tail = p1;
    tail->next = NULL; // 两件事，1，把这里注释掉；2，将IntSLLNode里的next = 0 注释掉，自己看吧
}

IntSLList::IntSLList(const IntSLList &object) 
{   // 这一定不对啊，不能说是头尾相等，整个链表就相等啊，必须一个一个节点的赋值。
    head = object.head;
    tail = object.tail;
}

IntSLList::~IntSLList()
{
    for (IntSLLNode *p; !isEmpty(); )
    {
        p = head->next;
        head = p;
    }
}

bool IntSLList::addToHead(const int & el)
{
    head = new IntSLLNode(el, head); // 生成的新的头节点info为el，新生成的头节点next指向以前的head。
    if (NULL == head)
    {
        return false;
    }
    if (NULL == tail)
    {
        tail = head;
    }
    return true;
}

bool IntSLList::addtoTail(const int & el)
{
    if (tail != 0)
    {
        tail = tail->next = new IntSLLNode(el);
    }
    else
    {
        head = tail = new IntSLLNode(el);
    }
    return true;
}

int IntSLList::deleteFromHead()
{
	int el = head->info;
	IntSLLNode *tmp = head;
	if (head == tail)
	{
		head = tail = NULL;
	}
	else
    {
        head = head->next;
    }
	return el;
}

int IntSLList::deleteFromTail()
{
    int el = tail->info;
    if (head == tail)
    {
        head = tail = 0;
    }
    else
    {
        IntSLLNode *tmp;
        for (tmp = head; tmp->next != tail; tmp = tmp->next);
        tail = tmp;
        tail->next = 0;
    }
    return el;
}

bool IntSLList::deleteNode(const int & el)
{
    if (head != NULL)
    {
        if ((head == tail) && (el == head->info))
        {
            head = tail = NULL;
            return true;
        }
        else if (el == head->info)
        {
            IntSLLNode *tmp = head;
            head = head->next;
            return true;
        }
        else
        {
            IntSLLNode *pred = head;
            IntSLLNode *tmp = head->next;

            for (; (tmp != NULL) && (!(tmp->info == el)); pred = pred->next, tmp = tmp->next);

            if (tmp != NULL)
            {
                pred->next = tmp->next; // tmp指向的节点被删除。
                if (tmp == tail)		// 找到的节点是最后一个节点。
                {
                    tail = pred;		// tail被赋值最后一个节点的地址。
                }
                return true;
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool IntSLList::isInList(const int & el) const
{
    IntSLLNode* tmp = head;

    for (; (tmp != NULL) && (!(tmp->info == el)); tmp = tmp->next);

    return tmp != NULL;
}

bool IntSLList::isEmpty() const
{
    return NULL == head;
}

IntSLLNode* IntSLList::getHead() const
{
    return head;
}

IntSLLNode* IntSLList::getTail() const
{
    return tail;
}

void IntSLList::reverse_list()
{
    if(isEmpty())
    {
        return;
    }
    IntSLLNode * p = getHead();
    IntSLLNode * prev = NULL;
    IntSLLNode * pnext = p->next;
    while (NULL != p)
    {
        pnext = p->next;
        p->next = prev;
        prev = p;
        p = pnext;
    }
    head = prev;
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

ostream& operator<<(ostream &os, const IntSLList &object)
{
	for (const IntSLLNode *p = object.getHead(); p != NULL; p = p->next)
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
/*
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
		if (NULL == p2)
		{
			return is;
		}
		p2->info = x;
		h->next = p2;
		h = p2;
	}
	return is;
}
*/

/* 没有在类IntSLListNode中加	friend istream& operator>>(istream&, IntSLList&); 
istream& operator>>(istream &is, IntSLList &object) // I think this is better than the one above.
{
	IntSLLNode* p = new IntSLLNode;
	p->info = 10; 
	if (NULL == p)
	{
		return is;
	}
	object.head = p;
	int x;
	std::cin >> x;
	p->SetInfo(x);
	while (cin >> x) // whenever a wrong instream, quit loop
	{
		IntSLLNode *p2 = new IntSLLNode;
		if (NULL == p2)
		{
			return is;
		}
		p2->SetInfo(x);
		p->SetNext(p2);
		p = p2;
	}
	object.tail = p;
	return is;
}
*/

istream& operator>>(istream &is, IntSLList &object) // I think this is better than the one above.
{
	IntSLLNode* p = new IntSLLNode;
	if (NULL == p)
	{
		return is;
	}
	object.head = p;
	int x;
	cin >> x;
	p->info = x;
	while (cin >> x) // whenever a wrong istream, quit loop
	{
		IntSLLNode *p2 = new IntSLLNode;
		if (NULL == p2)
		{
			return is;
		}
		p2->info = x; // because the declaration in class IntSLLNode.h we can access the private member of IntSLLNode
		p->next = p2;
		p = p2;
	}
	object.tail = p;
	return is;
}
