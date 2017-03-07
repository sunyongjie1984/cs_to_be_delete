#include <string>

class Account {
public:
    // interface functions here
    void applyint() { amount += amount * interestRate; }
friend int main();
    double balance() { return amount; }
public:
//    static double rate() { return interestRate; }
    static void rate(double);  // sets a new rate
private:
    std::string owner;
    double amount;
    static double interestRate;
//    static double initRate();
private:
    static const std::string accountType;
private:
    static const int period = 30;  // interest posted every 30 days
    double daily_tbl[period]; // ok: period is constant expression
};
using std::string;
const string Account::accountType("Savings Account");

void Account::rate(double newRate)
{
    interestRate = newRate;
}
