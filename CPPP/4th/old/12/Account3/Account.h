#include <string>
#include <iostream>
using namespace std;     // 不行的原因可否理解为，os是一种输出流，
//using std::ostream;    // 但是它不是std输出流，它只是一种孙永杰定义
//using std::string;     // 输出流，不像基于内置的，或像string的这种
class Account            // 由编译器自带的标准库类。
{                        // 不知道为什么，现在这样又可以了，疯了！
public:
	Account(string own, double amnt) : owner(own), amount(amnt) {}
	friend ostream& operator<<(ostream&, const Account&);
private:
	string owner;
	double amount;
}; 
ostream& operator<<(ostream& os, const Account &object)
{
	os << object.owner << "\t\t" << object.amount;
	return os;
}