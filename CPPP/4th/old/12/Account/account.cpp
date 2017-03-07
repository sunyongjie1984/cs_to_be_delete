#include "Account.h"
bool Account::withdraw(double amnt)
{
	if(amount < amnt)
	{
		return false;
	}
	else
	{
		amount -= amnt;
		return true;
	}
}

ostream& write(ostream& os, const Account& object)
{
	os << object.owner <<"\t\t\t" << object.amount << endl;
	return os;
}

istream& operator>>(istream& is, Account& object)
{
	is >> object.owner >> object.amount;
	return is;
}

ostream& operator<<(ostream& os, const Account& object)
{
	os << object.owner << "\t\t\t" << object.amount;
	return os;
}
double Account::interestRate = 2.5;
