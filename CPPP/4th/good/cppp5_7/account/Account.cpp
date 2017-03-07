#include <string>
using std::string;

#include "Account.h"

// define static data and function members
const string Account::accountType("Savings Account");
double Account::interestRate = initRate();

void Account::rate(double newRate) 
{
    interestRate = newRate; 
}
