/*#include <iostream>
#include "Student.h"
Student* creat()
{
	Student *head, *p, *s;
	int x, cycle = 1;
	head = (Student*)malloc(sizeof(Student)); // new Student();
	p = head;
	while(cycle)
	{
		std::cout << "\n" << "please input the data: " << std::endl;
		std::cin >> x;
		if (x != 0)
		{
			s = (Student*)malloc(sizeof(Student));
			s->data = x;
			std::cout << "\n" << s->data;
			p->next = s;
			p = s;
		}
		else
			cycle = 0;
	}
	head = head->next;
	p->next = NULL;
	std::cout << "\n" << head->data;
	return (head);
}*/

