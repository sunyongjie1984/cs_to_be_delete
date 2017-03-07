#include <iostream>
#include <iomanip>

#include "skiplist.h"

int main()
{
    int iii = 0;
    int jjj = 0;
    int rand_low;
    int randb_high;
    skiplist_bid* rand_bst;
    bool flag = true;
    int for_swap;
    int tmp_node;
    int rand_index = 100;
    void* val = nullptr;
    while (jjj++ < 10000) // 多少棵树
    {
        std::cout << "jjj = " << jjj << std::endl;
        rand_low   = abs(rand() % rand_index);
        randb_high = abs(rand() % rand_index);

        if (rand_low > randb_high)
        {
            for_swap = rand_low;
            rand_low = randb_high;
            randb_high = for_swap;
        }
        iii = 0;
        flag = (0 == rand_low % 2) ? true : false; 
        rand_bst = new skiplist_bid(flag);
        std::cout << "inserting... ";
        while (iii++ < rand_index) // 每棵树有多少结点
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " ";
            rand_bst->add(tmp_node, val); // 每个结点的取值范围(0～n)
        }
        std::cout << std::endl;
        rand_bst->set_valid_range(rand_low, randb_high);
        rand_bst->print_valid_range();
        rand_bst->print_by_level();
        iii = 0;
        std::cout << "deleting... ";
        while (iii++ < rand_index)
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " ";
            rand_bst->del(tmp_node, val);
        }  
        std::cout << std::endl;
        std::cout << "after delete: " << std::endl;
        rand_bst->print_valid_range();

        iii = 0;
        std::cout << "inserting... ";
        while (iii++ < rand_index) // 每棵树有多少结点
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " ";
            rand_bst->add(tmp_node, val); // 每个结点的取值范围(0～n)
        }
        std::cout << std::endl;
        rand_bst->print_valid_range();
        iii = 0;
        std::cout << "deleting... ";
        while (iii++ < rand_index)
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " " ;
            rand_bst->del(tmp_node, val);
        }  
        std::cout << std::endl;
        std::cout << "after delete: " << std::endl;
        rand_bst->print_valid_range();
        rand_bst->print_by_level();
        std::cout << "jjj = " << jjj << " end!" << std::endl;
        std::cout << std::endl;
    }
    getchar();
    return 0;

    skiplist_bid test;
    int buy1 = 6100;
    int buy2 = 5700;
    int buy3 = 5000;
    int buy4 = 4000;
    int buy5 = 3900;

    test.add(6100, static_cast<void*>(&buy1));
    test.add(5700, static_cast<void*>(&buy2));
    test.add(5000, static_cast<void*>(&buy3));
    test.add(4000, static_cast<void*>(&buy4));
    test.add(3900, static_cast<void*>(&buy5));

    uint32_t low  = 4000;
    uint32_t high = 6000;
    test.set_valid_range(low, high);
    test.first_valid(val);
    std::cout << std::dec << *(static_cast<int*>(val)) << std::endl;
    low = 5000;
    high = 7000;
    test.set_valid_range(low, high);
    test.first_valid(val);
    std::cout << std::dec << *(static_cast<int*>(val)) << std::endl;
    low = 5700;
    high = 7000;
    test.set_valid_range(low, high);
    test.first_valid(val);
    std::cout << std::dec << *(static_cast<int*>(val)) << std::endl;

    getchar();
    return 0;
    skiplist_bid SkipList;
    int a = 100;
    // be aware of that we add the address of variable a as value, 10 as key
    SkipList.add(3, static_cast<void*>(&a));
    std::cout << std::hex << &a << std::endl;

    int tmp = 888;
    void* p = &tmp;
    // the variable tmp and the initialization of p is not necessary
    // we just need a memory to hold the content of the address
    // it means we need an pointer to hold the value(address of a)
    // p will be assigned with the address of a
    // before SkipList.get(10, p), p points to variable tmp(the value of p is the address of tmp)
    // after this function p points to variable a
    // the changes happened by changing the content(value) of p(the value of p is the address of a)
    SkipList.get(3, p);
    std::cout << std::dec << *(static_cast<int*>(p)) << std::endl;
    std::cout << std::hex << p << std::endl;
    std::cout << tmp << std::endl;

    // the following 4 line is enough
    void* q;
    SkipList.get(3, q);
    std::cout << std::hex << q << std::endl;
    std::cout << std::dec << *(static_cast<int*>(q)) << std::endl;

    int b = 200;
    SkipList.add(6, static_cast<void*>(&b));
    int c = 300;
    SkipList.add(12, static_cast<void*>(&c));
    int d = 400;
    SkipList.add(8, static_cast<void*>(&d));
    int f = 500;
    SkipList.add(10, static_cast<void*>(&f));

    int e = SkipList.locate(9);
//     e = SkipList.first_valid(9, q);
    std::cout << std::dec << *(static_cast<int*>(q)) << std::endl;

    getchar();
    return 0;
}
