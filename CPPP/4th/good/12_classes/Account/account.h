#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;
using std::endl;

class Account
{
public:
    Account() { }
    Account(string own, double amnt): owner(own), amount(amnt) { }
    // Account(string own, double amnt, int i):
    //     owner(own), amount(amnt), test3(i) { }
    Account(istream& is)
    {
        is >> *this;
    }
    void applyint()
    {
        amount += amount * interestRate;
    }
    // the static data member can and only can be
    // accessed by static function member, because
    // of the scope reason, static data member is defined
    // and initialized like global data
    // I think the static function member is like the
    // static data member in the aspect of scope.
    // but static function members can be define in class defination
    // like any other function members, which are
    // totally different with static data members.
    // get interestRate
    static double rate()
    {
        return interestRate;
    }
    // set interestRate
    static void rate(double newRate)
    {
        interestRate = newRate;
    }
    void deposit(double amnt)
    {
        amount += amnt;
    }
    bool withdraw(double amnt);
    // add const, so that every object can access this member function
    // otherwise, const object can not access non-const memeber function
    double getBalance() const
    {
        return amount;
    }
    friend ostream& write(ostream&, const Account&);
    friend istream& operator>>(istream&, Account&);
    friend ostream& operator<<(ostream&, const Account&);
private:
    // non-static data members are difined in a class defination, and
    // initialized in construtors
    string owner;
    double amount;
    // except scope, dont treat static data members as members
    // non-static class data members are defined
    // in class defination and initialized in constructor
    // static class data members are defined and initialized out of class
    // defination, only declare in class
    static double interestRate; // declaration

    // static const data member can not be initializd in constructor
    // because it is a static, with the scope reason,
    // remember non-static const data member has to be initlized in
    // constructor list
    // static const data member is an exception of other static data member
    // it can be defined in class defination
    static const int test = 20;
    // static const data members can be defined in
    // 1. class defination or
    // 2. out of the header file
    // 3. can not in the header file out of class defination
    static const int test2;
    // const int test3; // defined in class defination,
    // initialized only in constructor list
};
// static data member, no matter const or non-const
// can not be defined in header file
// double Account::interestRate = 2.5;
// int Account::test2 = 20;
