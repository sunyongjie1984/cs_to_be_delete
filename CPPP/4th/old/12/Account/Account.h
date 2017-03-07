#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;
using std::endl;
class Account 
{
public:
	// 构造函数1
	Account(string own, double amnt): owner(own), amount(amnt) 
	{
	} 
	
	// 构造函数2
	Account() 
	{ 
	} 
	             
	// 构造函数3
    /*	
    Account(): amount(10000) // 这也是合法的。	// 构造函数4
	{
	} 
	
	Account(): owner("syj"), amount(10000) 
	{
	}
	*/
	// 构造函数5
	Account(istream& is) // 向Sales_items类学习的。
	{
		is >> *this;
	} 

	void applyint() 
	{ 
		amount += amount * interestRate;
	}

	static double rate() 
	{
		return interestRate;
	}
	static void rate(double newRate)
	{
		interestRate = newRate; 
	}

	void deposit(double amnt) 
	{
		amount += amnt; 
	}                                             // 书中给出的例子返回了amount的值，我没有那么
	                                              // 做，因为只要你输出不就是可以看到了么？还是
	                                              // 作者是对的，返回amount有其它用处，我要想一
	                                              // 想。
	bool withdraw(double amnt); // 这个函数我知道有什么用，就是说返回一个bool型的值，可以用来判
	                            // 断是不是要满足用户取钱的申请，用在if中。
	double getBalance() // 查询余额
	{
		return amount;
	} 

	friend ostream& write(ostream&, const Account&); // 我自己定义的输出
	friend istream& operator>>(istream&, Account&);
	friend ostream& operator<<(ostream&, const Account&); // 操作符重载输出

private:
	string owner;
	double amount;
	static double interestRate;
};


