/*#include <iostream> // 一会儿，再好好考虑用const&* 的问题@.@~.
#ifndef SYJ
#define SYJ
class Student {
public:
	Student(); // 创建链表1
	int length(Student* head); // 求表长
	void print(); // 打印链表
	void del(Student*head, int num); // 还没有实现
	Student* h;
private:
	int data;
	Student* next;       
};
Student::Student() 
{
	Student *head, *p, *s;
	int x;
	head = (Student*)malloc(sizeof(Student));
//	head = (Student*)new Student; // new Student();
	p = head;

	while (std::cin >> x)
	{
		s = (Student*)malloc(sizeof(Student));
//		s = (Student*)new Student;
		s->data = x;
		p->next = s;
		p = s;
	}
	head = head->next;
	h = head;
	p->next = NULL;
}
int Student::length(Student* head)
{
	int n = 0;
	Student* p;
	p = head;
	while(p != NULL)
	{
		p = p->next;
		n++;
	}
	std::cout << "这个链表有" << n << "个节点" << std::endl;
	return n;
}
void Student::print()
{
	Student* p;
	int n;
	n = length(h);
	p = h;
	std::cout << "这些节点分别是" << std::endl;
	if (h != NULL)
		while (p != NULL)
		{
			std::cout << p->data << " ";
			p = p->next;
		}
}
void Student::del(Student* head, int num)
{
	Student *p1, *p2;
	p1 = head;
	while (num != p1->data && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if (num == p1->data)
	{
		if (p1 == head)
		{
			head = p1->next;
			free (p1);
		}
		else
			p2->next = p1->next;
	}
	else
		std::cout << "没有找到那个节点" << std::endl;
}

#endif*/
#include <iostream.h>
struct Studentnode
{
	int data;
	Student *next;
};
class Studentlist
{
public:
	Studentlist()
	{
		head = null;
		length=0;
	}
	void initlist(int n)
	{
		head = (Studentnode *)malloc(sizeof(studentnode));
		cout<<"please input head node data"<<endl;
		cin>>head->data;
		Studentnode * p1 = head;
		Studentnode * p2;
		int i=0;
		while(i<n-1)
		{
			p2 = (Studentnode *)malloc(sizeof(studentnode));
			cout<<"please input "<<(i+2)<<"node data"<<endl;
			cin>>p2->data;
			p1->next = p2;
			p1 = p2;
		}
		p1->next = null;
		length = n;
	}
	void printlist()
	{
		Studentnode *p1 = head; 
		while(p1)
		{
			cout<<p1->data<<endl;
			p1=p1->next;
		}
	}
	void addnode(int value)
	{
		Studentnode newstudent;
		newstudent.data = value;
		newstudent.next = null;
		Studentnode *p1 = head;
		while(p1->next)
		{
			p1=p1->next;
		}
		p1->next = newstudent;
		length++;
	}
	void delnode(int value)
	{
		Studentnode * p1 = head;
		if((p1->data) == value)
		{
			head = p1->next;
			free(p1);
			length--;
		}
		else
		{
			while(((p1->data)!=value)&&(p1!=null))
			{
				p2 = p1;
				p1 = p1->next;
			}
			if(p1==null)
			{
				return;
			}
			else
			{
				p2->next = p1->next;
				free(p1);
				length--;
			}
		}
	}
	
private:
	Studentnode *head;
	int length;
}
main()
{
	Studentlist sl;
	sl.initlist(5);
}