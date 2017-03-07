#include <iostream>
class SmallInt {
public:
    SmallInt(int i = 0);
    int Get_Value() { return val; }

    friend std::ostream& operator<<(std::ostream& os, const SmallInt& si);
    friend std::istream& operator>>(std::istream &is, SmallInt &si);

    SmallInt operator+(const SmallInt& si) { return SmallInt(val + si.val); }
    SmallInt operator-(const SmallInt& si) { return SmallInt(val - si.val); }
    SmallInt operator*(const SmallInt& si) { return SmallInt(val * si.val); }
    SmallInt operator/(const SmallInt& si) { return SmallInt(val / si.val); }
    SmallInt& operator+=(const SmallInt &si);

    bool operator==(const SmallInt& si) { return (val == si.val); }
private:
    char val;
};
SmallInt::SmallInt(int i)
{
    while (i > 127)
        i -= 256;
    while (i <- 128)
        i += 256;
    val = i;
}
SmallInt& SmallInt::operator+=(const SmallInt& si)
{
    val += si.val;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const SmallInt& si)
{
    os << (int)si.val;
    return os;
}
std::istream& operator>>(std::istream& is, SmallInt& si)
{
    int tmp;
    is >> tmp;
    si = SmallInt(tmp);
    return is;
}
