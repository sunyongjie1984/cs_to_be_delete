#include <iostream>

#include "Sales_item.h"

int main()
{
    int k = 0;
    int j = 2;
    j = j + k;
    Sales_item item1, item2;

    std::cin >> item1 >> item2;   //read a pair of transactions
    std::cout << item1 + item2 << std::endl; //print their sum

    return 0;
}
