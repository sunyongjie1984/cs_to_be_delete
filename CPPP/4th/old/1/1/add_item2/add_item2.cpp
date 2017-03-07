#include <iostream>
#include "Sales_item.h"

int main() 
{
    Sales_item item1, item2;

    std::cin >> item1 >> item2;
    // first check that item1 and item2 represent the same book
    if (item1.same_isbn(item2)) 
	{
        std::cout << item1 + item2 << std::endl;
        return 0;   // indicate success
    } 
	else 
	{
        std::cerr << "Data must refer to same ISBN" 
                  << std::endl;
        return -1;  // indicate failure
    }
}
