#ifndef C_BASE
#define C_BASE

#include <iostream>
class c_base {
public:
    void apple()          { std::cout << "apple in base" << std::endl; }
    virtual void orange() { std::cout << "orange in base" << std::endl; }
    virtual void pear()   { std::cout << "pear in base" << std::endl; }
};

#endif
