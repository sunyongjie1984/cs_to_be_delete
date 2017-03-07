#include <iostream>
#include <map>
#include <string>

#include "test_iterator.h"

int main()
{
    std::map<int, std::string> a;
    std::map<int, std::string>::value_type one(1, "hello");

    a.insert(one);

    std::map<int, std::string>::iterator iter = a.begin();

    std::cout << iter->first << std::endl;
    std::cout << iter->second << std::endl;

    typedef std::map<int, std::string> map_int_string;
    typedef std::map<int, std::string>::value_type value_type_map_int_string;
    typedef std::map<int, std::string>::iterator iterator_map_int_string;

    map_int_string b;
    value_type_map_int_string two(2, "China");

    b.insert(two);

    iterator_map_int_string iter2 = b.begin();

    std::cout << iter2->first << std::endl;
    std::cout << iter2->second << std::endl;

    // 试试类名加iterator
    // 实际上是在类CBook中定义了一个类my_iterator
    // 要想引用这个类就要在这个类前面加上CBook
    // CBook::my_iterator中的::是表示class my_iterator定义在类CBook中


    CBook::my_iterator iter3 = b.begin();

    std::cout << iter2->first << std::endl;
    std::cout << iter2->second << std::endl;

    return 0;
}
