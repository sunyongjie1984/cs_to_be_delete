#include "Account.h"
//using namespace std;
using std::cout;
using std::endl;
int main()
{
	Account myAccount("SunYJ", 10000);

	cout << "name\t\t" << "amount" << endl;
	cout << myAccount << endl;

	return 0;
}
/*
ostream& operator<<(ostream& os, const Account& object)
{
	os << object.owner << "\t\t" << object.amount;
	return os;
}*/ // 这个函数不论写在哪里，它都是全局的，而且都是类的，所以在这里定义
    // 它的关于using namespace 的乱七八糟的事就好像在头文件中一样的。
