#include "Item_base.h"

class Bulk_item : public Item_base {
public:
    Bulk_item(std::string const & book = "", double sales_price = 0.0,
            size_t qty = 0, double disc_rate = 0.0)
        : Item_base(book, sales_price), min_qty(qty), discount(disc_rate) { }

    double net_price(size_t const & cnt) const;

    void display_datamember() const;

private:
    size_t min_qty;
    double discount;
};

double Bulk_item::net_price(size_t const & cnt) const
{
    if (cnt >= min_qty)
    {
        return cnt * (1 - discount) * price;
    }
    else
    {
        return cnt * price;
    }
}

void Bulk_item::display_datamember() const
{
    std::cout << book() << " " << price << " " << min_qty << " " << discount << std::endl;
}
