#include "Account.h"
using std::cin;
using std::cout; 
int main() 
{
	              // 测试了有一会儿了，突然发现，一没有只定义名字的构造函数，
//	Account test; // 二没有重载移位输入操作符。由Sales_item得到启示
//	cin >> test;  // 又设计了一个向Sales_item学习而得的构造函数
	Account test;   
	cin >> test;
	cout << test << endl;

	Account test2(cin);
	cout << test2 << endl;

	Account myAccount("syj", 10000);
	Account myAccount2("syj2", 10000);
//	myAccount = myAccount2; // 这个可以进行，说明编译器给定义了默认拷贝构造函还是说明重载了=操
	                        // 作符，应该是重载了操作符。呵呵。
	
//	double rate = myAccount.rate(); 
	double rate = Account::rate(); // 静态函数果然可以由类直接访问，不用对象也可以。
	myAccount.applyint(); // applyint = "执行利息",之后，我的钱就变多了，呵呵

	cout << "owner" << "\t\t\t" << "amount" << "\n\n";
	write(cout, myAccount); // 能够看出重载操作符带来的便利。
	cout << myAccount << "\n\n";
	cout << "the interestRate is: " << rate << "\n\n\n";
	
	
	// 设置新的interestRate
//	Account::rate(5.0); // 两种方法都可以访问static的，1，由类直接，2由对象直接。
	myAccount.rate(5.0);
	rate = Account::rate(); // 读出interestRate
	myAccount2.applyint(); //计算算上利息之后的amount
	

	cout << "owner" << "\t\t\t" << "amount" << "\n\n";
	write(cout, myAccount2);
	cout << myAccount2 << "\n\n";
	cout << "the interestRate is: " << rate << "\n\n";
	
	
	// 存款
	myAccount.deposit(5000);
	cout << "存款5000之后myAccount的余额" << endl;
	cout << myAccount << "\n\n";
	
	
	// 取款
	cout << "取款10000之后myAccount的余额" << endl; 
	bool i = myAccount.withdraw(10000);
	if (i)
	{
		cout << myAccount << endl;
	}
	else
	{
		cout << "not enough amount!" << endl;
	}

	return 0;
}