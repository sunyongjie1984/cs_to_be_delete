#include "isll.h"
int main()
{
    isll list1;
    cout << "list1 is " << (list1.isEmpty() ? "empty" : "not empty")
        << endl;
    list1.addToHead(30);
    cout << "list1 is " << (list1.isEmpty() ? "empty" : "not empty")
        << endl;
    cout << list1 << endl;
    list1.deleteFromHead();
    cout << list1 << endl;
    list1.addToTail(40);
    cout << list1 << endl;
    list1.deleteFromTail();
    cout << list1 << endl;
    list1.addToHead(30);
    list1.addToTail(20);
    list1.addToTail(40);
    list1.addToHead(50);
    cout << list1 << endl;
    list1.deleteNode(20);
    cout << list1 << endl;
    list1.deleteNode(30);
    cout << list1 << endl;
    list1.deleteNode(40);
    cout << list1 << endl;
    list1.deleteNode(50);
    cout << list1 << endl;
    /*isll list2(4);
    cout << list2;

    isll list3;
    cin >> list3;
    isll list4(list3);  // copy constructor
    isll list5 = list3; // copy constructor
    cout << list3 << endl;
    std::cout << list4 << endl;
    std::cout << list5 << endl;
    */
    return 0;
}
