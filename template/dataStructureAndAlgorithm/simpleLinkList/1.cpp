#include <iostream>
using namespace std;
class Student {
public:
    int data;
    Student* next;
};
int main()
{
    Student* head;
    Student* p;
    Student* s;
    int x;
    // head=(Student*)malloc(sizeof(Student)); // ok
    // head= new Student(); // ok
    head = new Student;  // ok
    p = head;
    while (cin >> x && x != 0)
    {
        s = new Student;
        s->data = x;
        p->next = s;
        p = s;
    }
    head = head->next;
    p->next = NULL;
    Student* pp;
    p = head;
    while (NULL != p)
    {
        cout << p->data << " ";
        pp = p->next;
        delete p;
        p = pp;
    }
    std::cin.clear();
    std::cin.ignore();
    cout << endl;
    cout << "Please enter an integer:" << endl;
    cin >> x;
    cout << x << endl;
    return 0;
}
