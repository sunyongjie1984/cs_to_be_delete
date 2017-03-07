#include <iostream>
using std::cout;
using std::endl;
int main()
{
	char greeting[]  = "ILoveChina!";
	char greeting2[] = "ILoveChina!";
	char greeting3[] = "ILoveChina!";
	char greeting4[] = "ILoveChina!";

	char* p = greeting; // 这是我的风格了@_@~. // 没有风格就是风格，一切以C++ Primer一致，绝对一致
	const char* p2 = greeting2; // 就是看const在*的左右边来决定的。
	char* const p3 = greeting3;
	const char* const p4 = greeting4;
	
	// 第一种定义方式
	cout << p << "\t" << *p << endl; 
	p++;                                // ok! char* p的指针自身可以修改
	cout << p << "\t" << *p << endl; 
    
	p--;                            
	*p = 'Y';                           // ok! char* p的指针所指对象可以修改
	cout << p << "\n\n" << endl;

	// 第二种定义方式
	cout << p2 << "\t" << *p2 << endl; 
	p2++;                               // ok! char* p的指针自身可以修改
	cout << p2 << "\t" << *p2 << "\n\n" << endl; 

	p2--;
//	*p2 = 'Y';                          // 错！p的指针所指对象不以修改

	// 第三种定义方式
	cout << p3 << "\t" << *p3 << endl;  
//	p3++;                               // 错！指针自身不可以修改

	*p3 = 'Y';                          // ok! 指针所指对象可以修改
	cout << p3 << "\t" << *p3 << "\n\n" << endl; 

	// 第四种定义方式
	cout << p4 << "\t" << *p4 << endl;
//	p4++;                               // 错！指针自身不可以修改
	
//	*p4 = 'y';                          // 错！指针所指对象不可以修改 
	
	return 0;
}