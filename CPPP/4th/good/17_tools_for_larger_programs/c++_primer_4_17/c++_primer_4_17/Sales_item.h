#include <iostream>
#include <string>

class Sales_item {
private: // 比较清析是private的函数
    friend bool compare(Sales_item const &, Sales_item const &);
    friend bool operator==(Sales_item const &, Sales_item const &); // 友元形式的重载操作符，是全局函数

public:
    friend std::istream& operator>>(std::istream &, Sales_item &); // 友元形式的重载操作符，是全局函数
    friend std::ostream& operator<<(std::ostream &, Sales_item const &);

    Sales_item(std::string const & book): isbn(book), units_sold(0), revenue(0.0) { }
    Sales_item(std::istream & is) // 用重载的输入操作符定义单个以输入流对象为参数的构造函数
    {
        is >> *this;
    }

    // default constructor needed to initialize members of built-in type
    Sales_item(): units_sold(0), revenue(0.0) { }

public:
    // operations on Sales_item objects
    Sales_item& operator+=(Sales_item const &); // 成员函数形式的重载操作符

    double avg_price() const;
    bool same_isbn(Sales_item const & rhs) const
    {
        return isbn == rhs.isbn;
    }
    std::string book() const
    {
        return isbn;
    }

private:
    std::string isbn;
    unsigned units_sold;
    double revenue;
};

// 全局的操作符重载必须为每个操作数定义一个参数
// nonmember binary operator: must declare a parameter for each operand
Sales_item operator+(Sales_item const &, Sales_item const &);

inline bool operator==(Sales_item const & lhs, Sales_item const & rhs)
{
    // must be made a friend of Sales_item
    return lhs.units_sold == rhs.units_sold &&
        lhs.revenue == rhs.revenue &&
        lhs.same_isbn(rhs);
}

inline bool operator!=(Sales_item const & lhs, Sales_item const & rhs)
{
    return !(lhs == rhs); // != defined in terms of operator==
}

inline bool compare(Sales_item const & lhs, Sales_item const & rhs)
{
    return lhs.book() < rhs.book();
}
