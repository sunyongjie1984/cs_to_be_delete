//************************  intSLLst.cpp  **************************

#include <iostream> // 这本书和C++ Primer的风格不一样
#include "intSLLst.h"
using namespace std;
//using std::cout;
//using std::ostream;
//using std::endl;
//using std::cin;

IntSLList::IntSLList(int n)
{                                   
	tail = new IntSLLNode; // 疯了，它的节点数据节构有构造函数，孙永杰，你这回学到东西了
	IntSLLNode *p1 = tail;
	cout << "请输入第 1个节点的值" << endl;
	tail->next = NULL;
	cin >> tail->info;
	for (int i = 0; i < n - 1; i++)
	{
		IntSLLNode *p2 = new IntSLLNode;
		cout << "请输入第 "<< i + 2 <<"个节点的值" << endl;
		cin >> p2->info;
		p2->next = p1;
		p1 = p2;
	}
	head = p1;
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
    head = new IntSLLNode(el,head);
    if (tail == 0)
       tail = head;
}

void IntSLList::addToTail(int el) 
{
    if (tail != 0) 
	{      // if list not empty;
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
    if (head == tail)     // if only one node on the list;
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
	{                     // if only one node on the list;
         delete head;
         head = tail = 0;
    }
    else 
	{                // if more than one node in the list,
         IntSLLNode *tmp; // find the predecessor of tail;
         for (tmp = head; tmp->next != tail; tmp = tmp->next);
         delete tail;
         tail = tmp;      // the predecessor of tail becomes tail;
         tail->next = 0;
    }
    return el;
}

void IntSLList::deleteNode(int el) 
{
    if (head != 0)                     // if non-empty list;
         if (head == tail && el == head->info) 
		 {                                       // if only one
              delete head;                       // node on the list;
              head = tail = 0;
         }
         else if (el == head->info) 
		 {                           // if more than one node on the list
              IntSLLNode *tmp = head;
              head = head->next;
              delete tmp;              // and old head is deleted;
         }
         else 
		 {                        // if more than one node in the list
              IntSLLNode *pred, *tmp;
              for (pred = head, tmp = head->next; // and a non-head node
                   tmp != 0 && !(tmp->info == el);// is deleted;
                   pred = pred->next, tmp = tmp->next);
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

bool IntSLList::isInList(int el) const 
{
    IntSLLNode *tmp; // 这个for语句也太牛逼了吧！！
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void IntSLList::printAll() const 
{
    for (IntSLLNode *tmp = head; tmp != 0; tmp = tmp->next)
	{
		cout << tmp->info << " ";
	}
	cout << endl;
}

ostream& operator<<(ostream &os, const IntSLList &object)
{
	for (IntSLLNode *tmp = object.head; tmp !=0; tmp = tmp->next)
	{
		os << tmp->info << " ";
	}
	os << endl;
	return os;
}