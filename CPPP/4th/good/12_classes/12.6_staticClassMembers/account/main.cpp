#include "account.h"
using std::cin;
using std::cout;
int main()
{
    // Account test;
    // cin >> test;
    Account test;
    cin >> test;
    cout << test << endl;

    Account test2(cin);
    cout << test2 << endl;

    Account myAccount("syj", 10000);
    Account myAccount2("syj2", 10000);
    // myAccount = myAccount2;

    // double rate = myAccount.rate();
    double rate = Account::rate();
    myAccount.applyint();

    cout << "owner" << "\t\t\t" << "amount" << "\n\n";
    write(cout, myAccount);
    cout << myAccount << "\n\n";
    cout << "the interestRate is: " << rate << "\n\n\n";


    // Account::rate(5.0);
    myAccount.rate(5.0);
    rate = Account::rate();
    myAccount2.applyint();

    cout << "owner" << "\t\t\t" << "amount" << "\n\n";
    write(cout, myAccount2);
    cout << myAccount2 << "\n\n";
    cout << "the interestRate is: " << rate << "\n\n";

    myAccount.deposit(5000);
    cout << "after deposit 5000" << endl;
    cout << myAccount << "\n\n";

    cout << "after withdraw 10000" << endl;
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
