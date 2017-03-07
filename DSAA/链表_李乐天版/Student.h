#include <iostream> // 一会儿，再好好考虑用const&* 的问题@.@~.
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
	std::cin.clear();
	std::cin.ignore();
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

#endif

// 
// 清空输入缓冲区的方法
// [ C++ ]
// 虽然不可以用 fflush(stdin)，但是我们可以自己写代码来清空输入缓冲区。只需要在 scanf 函数后面加上几句简单的代码就可以了。
// 
// /* C 版本 */
// 
// #include <stdio.h>
// 
// 
// 
// int main( void )
// 
// {
// 	
//     int i, c;
// 	
//     for (;;) {
// 		
//         fputs("Please input an integer: ", stdout);
// 		
//         if ( scanf("%d", &i) != EOF ) { /* 如果用户输入的不是 EOF */
// 			
//             /* while循环会把输入缓冲中的残留字符清空 */
// 			
//             /* 可以根据需要把它改成宏或者内联函数 */
// 			
//             /* 注：C99中也定义了内联函数，gcc3.2支持 */
// 			
//             while ( (c=getchar()) != '\n' && c != EOF ) {
// 				
// 				;
// 				
//             } /* end of while */
//         }
// 		
//         printf("%d\n", i);
// 		
//     }
// 	
//     return 0;
// 	
// }
// 
// 
// 
// /* C++ 版本 */
// 
// #include <iostream>
// 
// #include <limits> // 为了使用numeric_limits
// 
// 
// 
// using std::cout;
// 
// using std::endl;
// 
// using std::cin;
// 
// 
// 
// int main( )
// 
// {
// 	
// 	int value; 
// 	
// 	for (;;) {
// 		
// 		cout << "Enter an integer: ";
// 		
// 		cin >> value;
// 		
// 		/* 读到非法字符后，输入流将处于出错状态，
// 		
// 		  * 为了继续获取输入，首先要调用clear函数
// 		  
// 			* 来清除输入流的错误标记，然后才能调用
// 			
// 		* ignore函数来清除输入缓冲区中的数据。 */          
// 		
// 		cin.clear( );
// 		
// 		/* numeric_limits<streamsize>::max( ) 返回缓冲区的大小。
// 		
// 		  * ignore 函数在此将把输入缓冲区中的数据清空。
// 		  
// 		* 这两个函数的具体用法请自行查询。 */
// 		
// 		cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
// 		
// 		cout << value << '\n';
// 		
// 	}
// 	
// 	return 0;
// 	
// }