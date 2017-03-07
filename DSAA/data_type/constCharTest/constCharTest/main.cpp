// const_cast
#include <iostream>
using namespace std;

void print (char * str)
{
    cout << str << endl;
}

int main () {
    const char * c = "sample text";
    print (c);
    //print ( const_cast<char *> (c) );
    return 0;
}
