#include "screen3.h"
#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;

int main()
{
    Screen myScreen(5,3);

    // move cursor to given position, and set that character
    myScreen.move(4,0).set('#');
    // move cursor to given position, set that character and display the screen
    myScreen.move(4,0).set('#').display(cout);
    cout << endl;

    const Screen blank(5, 3);
    myScreen.set('#').display(cout);  // calls nonconst version
    cout << endl;
    blank.display(cout);              // calls const version
    cout << endl;

    myScreen.move(4,0);
    myScreen.set('#');
    myScreen.display(cout);

    return 0;
}
