#include "Version_test.h"

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
#if defined(DEFAULT_FCNS) && defined(IN_CLASS_INITS)
	Account() = default;
#else
	Account(): amount(0.0) { }
#endif
	Account(const std::string &s, double amt):
		owner(s), amount(amt) { }

    void calculate() { amount += amount * interestRate; }
    double balance() { return amount; }
public:
    static double rate() { return interestRate; }
    static void rate(double);   
private:
    std::string owner; 
#ifdef IN_CLASS_INITS
    double amount = 0.0; 
#else
	double amount;
#endif
    static double interestRate; 
    static double initRate() { return .0225; }
//    const std::string accountType_for_test;
    static const std::string accountType;
#ifdef CONSTEXPR_VARS
    static constexpr int period = 30;// period is a constant expression
#else
	static const int period = 30;// period is a constant expression
#endif
    double daily_tbl[period];
};
#endif
