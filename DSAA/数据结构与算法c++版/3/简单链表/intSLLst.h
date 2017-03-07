//************************  intSLLst.h  **************************
//           singly-linked list class to store integers
#include <iostream>
using std::ostream;
#ifndef INT_LINKED_LIST // 我要给你加一个构造函数，读入n个节点王欣的方法
#define INT_LINKED_LIST // 读入未知数目
                        // 一招是循环你的addtoTail
                        // 还有别的试试看。
class IntSLLNode {
public:
    int info;
    class IntSLLNode *next;
	IntSLLNode() { } // 为了我的构造函数，我给你也加了一个构造函数
    IntSLLNode(int el, IntSLLNode *ptr = 0) 
	{
        info = el; next = ptr;
    }
};
 // 链表类，和节点类，这中间的奥妙尽在综艺频道@.@
class IntSLList { // 整型的简单链表Int Singly-Linked List 多明白啊@.@~
public:           // 可是为什么类名与保存这个类的文件名不一样呢？
    IntSLList() 
	{ 
        head = tail = 0;
    }
	IntSLList(int); // 我的从头插入n个节点的构造函数
    ~IntSLList();
    int isEmpty() 
	{
        return head == 0; // 这里作的也帅气！
    }
    void addToHead(int);
    void addToTail(int);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    void printAll() const;
    // 我的可爱的"<<"
	friend ostream& operator<<(ostream&, const IntSLList&);
private:
    IntSLLNode *head, *tail;
};

#endif
