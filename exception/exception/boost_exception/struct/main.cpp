#include <string>
#include <iostream>
using namespace std;
class CBase {

public:
    CBase(const std::string& book = "",
        double sales_price = 0.0): isbn(book), price(sales_price) { }
    virtual ~CBase() { }
    std::string book() const { return isbn; }
    virtual void display_all_data_member() { cout << isbn << " " << price << endl; }
    virtual double net_price(size_t n) const { return n * price; }

protected: // derived class is able to access
    double price;

private:
    std::string isbn; // derived class is not able to access, has to turn to public book()
};                    // and can not change the value of isbn; 
// without the default constructor of CBase, the derived class can not construct its own isbn,
// I am not quite sure of the sentence above

// the CBase class EXPECTS its derived class redefine the net_price function!!!!!! 

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

int main()
{
    return 0;
}