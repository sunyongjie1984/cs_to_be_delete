#include "io_preamble.h"

int main()
{
    char ch;    // Using a char here invites disaster!

    // return from cin.get is converted from int to char and then compared to an int
    while ((ch = cin.get()) != EOF)
             cout.put(ch);
    cout << endl;

    return 0;
}
