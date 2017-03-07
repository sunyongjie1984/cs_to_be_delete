#include <string>

class CBook {
public:
    CBook(): a(-1), b(0.0)
    {

    }

public:
    typedef std::map<int, std::string>::iterator my_iterator;

    my_iterator iter;

    int a;
    float b;

};