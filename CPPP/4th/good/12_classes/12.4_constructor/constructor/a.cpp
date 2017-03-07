#include <string>
#include <iostream>
using namespace std;
class Node {
    friend ostream& operator<<(ostream& os, const Node& node)
    {
        os << node.name << " " << node.age;
        return os;
    }
public:
    /* Node(char* n = " ", int a = 0): age(a)
    {
        name = strdup(n); // in null-terminated source string
                          // return a pointer to the storage location for the copied string
                          // or NULL if storage cannot be allocated
                          // use free to free the memory
    } */
    // it is an example of constructor list, compared to the above one,
    // I prefer the below one
    Node(char* n = " ", int a = 0): age(a), name(strdup(n)) { }
    ~Node()
    {
        free(name);
    }
    Node(const Node& n)
    {
        name = strdup(n.name);
        age  = n.age;
    }
private:
    char* name;
    int age;
};
int main()
{
    Node node1("Roger", 20);
    Node node2(node1);

    cout << node1 << endl;
    cout << node2 << endl;
    return 0;
}
