#include <string>
#include <iostream>
class Item_base {
public:
    Item_base(std::string const & book = "", double sales_price = 0.0):
        isbn(book), price(sales_price) { }
    virtual ~Item_base() { }

    std::string book() const
    {
        return isbn;
    }

    virtual double net_price(size_t const & n) const
    {
        return n * price;
    }

    virtual void display_datamember() const
    {
        std::cout << isbn << " " << price << std::endl;
    }
private:
    std::string isbn;
protected:
    double price;
};
