#include <iostream>
#include "isll.h"
isll::isll(int n)
{
    head = new islln;
    islln* p1 = head;
    cout << "请输入第 1个节点的值" << endl;
    cin >> head->info;
    for (int i = 0; i < n - 1; i++)
    {
        islln* p2 = new islln;
        cout << "请输入第 "<< i + 2 << "个节点的值" << endl;
        cin >> p2->info;
        p1->next = p2;
        p1 = p2;
    }
    tail = p1;
    tail->next = NULL;
}
isll::~isll()
{
    for (islln* p; !isEmpty(); )
    {
        p = head->next;
        delete head;
        head = p;
    }
}
// {
//     islln* p = head;
//     while (0 != p)
//     {
//         delete p;
//     }
// }
void isll::addToHead(int el)
{
    head = new islln(el, head);
    if (tail == 0)
    {
        tail = head;
    }
}
void isll::addToTail(int el)
{
    if (tail != 0)
    {
        tail->next = new islln(el);
        tail = tail->next;
    }
    else
    {
        head = tail = new islln(el);
    }
}
bool isll::deleteFromHead()
{
    bool bFlag; // use one flay to get rid of the multi-return statement
    if (isEmpty())
    {
        bFlag = 0;
    }
    else
    {
        int el = head->info;
        islln* tmp = head;
        if (head == tail) // only one node
        {
            head = tail = 0;
        }
        else
        {
            head = head->next;
        }
        delete tmp; // if tmp = 0, no dangerous to delete a NULL pointer
                    // if tmp != 0, it is a normal ok
        bFlag = 1;
    }
    return bFlag;
}
bool isll::deleteFromTail()
{
    bool bFlag;
    if (isEmpty())
    {
        bFlag = 0;
    }
    else
    {
        int el = tail->info;
        if (head == tail) // only one node
        {
            delete head;
            head = tail = 0;
        }
        else
        {
            islln* tmp;
            for (tmp = head; tmp->next != tail; tmp = tmp->next);
            delete tail;
            tail = tmp;
            tail->next = 0;
        }
        bFlag = 1;
    }
    return bFlag;
}
bool isll::deleteNode(int el)
{
    bool bFlag = 0;
    if (!isEmpty())
    {
        if (head == tail && el == head->info)
        {
            delete head;
            head = tail = 0;
        }
        else if (el == head->info)
        {
            islln* tmp = head;
            head = head->next;
            delete tmp;
        }
        else
        {
            islln* pred;
            islln* tmp;
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
        bFlag = 1;
    }
    return bFlag;
}
bool isll::isInList(int el) const
{
    islln* tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}
/*
   ostream& operator<<(ostream& os, isll& object) // 能用了，不过我把head与tail弄成public了
   {                                                   // 我加一个成员函数用来返回头指针不就好了
   for (islln* p = object.head; p != NULL; p = p->next) // 试试看，呵呵
   {
   os << p->info << " ";
   }
   return os;
   }
 */
ostream& operator<<(ostream& os, const isll& object)
{
	    for (islln* p = object.getHead(); p != NULL; p = p->next)
    {
        os << p->info << " ";
    }
    return os;
}
// 这种情况现在是可以用了，我试着删掉一些东西看看。   // 这是在head,tail是public的情况下的
/*istream& operator>>(istream& is, isll& object) // 我的这个程序有很多的地方要改，简直
  {                                                     // 保留的地方少。
  object.head = new islln;
  cin >> object.head->info;
  islln* p1 = object.head;
  int x;
  while (std::cin >> x) // 这个位置以前用字母来结束的时候会出问题
  {                     // 现在没有了，可能是因为节点的构造函数每生成一个的时候都是指针域赋值0的。
  islln* p2 = new islln;
  p2->info = x;
  p1->next = p2;
  p1 = p2;
  }
// object.tail = p1; // 为什么注释了这个也可以，我要看看我的输出符
return is;        // 我的输出符重载函数根本没有用到tail
}*/
/*
// 这个输入是head,tail,private的时候。
istream& operator>>(istream& is, isll& object)
{
islln* h = object.getHead();
//	islln* t = object.getTail(); 有用么，要设置它么？
islln* p1 = h;
p1 = new islln; // 这里错的非常严重，仔细考虑一下。
std::cin >> h->info;
int x;
while (std::cin >> x)
{
islln* p2 = new islln;
p2->info = x;
p1->next = p2;
p1 = p2;
}
p1->next = 0;
return is;
}*/
istream& operator>>(istream& is, isll& object)
{
    islln* h = new islln;
    object.setHead(h);
    std::cin >> h->info;
    int x;
    while (std::cin >> x)
    {
        islln* p2 = new islln;
        p2->info = x;
        h->next = p2;
        h = p2;
    }
    object.setTail(h);
    return is;
}
