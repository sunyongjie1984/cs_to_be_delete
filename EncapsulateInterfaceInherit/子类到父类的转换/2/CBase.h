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
        