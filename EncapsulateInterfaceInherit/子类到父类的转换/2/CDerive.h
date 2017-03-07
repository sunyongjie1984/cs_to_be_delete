#include "CBase.h"
class CDerive: public CBase {

public:
    // the constructor initializer also implicitly invokes the CBase default constructor to 
    // initialize its base-class part
    CDerive(): min_qty(0), discount(0.0) { } 
    // passing arguments to a base-class constructor
    CDerive(const std::string& book, double sales_price,
        size_t qty = 0, double disc_rate = 0.0):
    CBase(book, sales_price), min_qty(qty), discount(disc_rate) { }

    double net_price(size_t cnt) const 
    { 
        if (cnt >= min_qty) return cnt * (1 - discount) * price;
        else return cnt * price; 
    } // CDerive can access price, but isbn.
    void display_all_data_member() 
    {
        cout << book() << " " << price << " " 
            << min_qty << " " << discount << endl;
    } 

private:
    size_t min_qty;
    double discount;
};
// although the isbn is a member of CDerive class but the class CDerive can not access the isbn
// data member, it has to use the base-class constructor to initialize the isbn, and there is 
// no more method for the CDerive class to access or modify the isbn member. I think.