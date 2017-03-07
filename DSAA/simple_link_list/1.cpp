#include <iostream>
using namespace std;

// 清空标准输入流，std:cin.clear(),std::cin.ignore(); 

class Student {
public:
	int data;
	Student *next;
};

int main() 
{
	Student *head, *p, *s;
	int x;
	head = (Student*)malloc(sizeof(Student));
//	head = (Student*)new Student; // new Student();
	p = head;

	while (cin >> x && x != 0) // 考查cin >> x的使用，用好了Control+z
	{                // 不要随便用e,k啊使流产生错误就不好了。
		s = (Student*)malloc(sizeof(Student));
//		s = (Student*)new Student;
		s->data = x;
		p->next = s;
		p = s;
	}
	head = head->next;
	p->next = NULL;

                // 用control + z或者用e,f 啊什么的，都是有错误
	            // 还是要用那两个混蛋函数啊.

	for (p = head; p != NULL; p = p->next)
		cout << p->data << " ";

	std::cin.clear();
	std::cin.ignore();
	cout << endl;
	cout << "Please 再输入一个数字" << endl;
	cin >> x;
	cout << x << endl;


	return 0;
}