#include "Screen.h"
int main()
{
    Screen myscreen(5, 6, "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa\n");
    myscreen.move(4,0).set('#').display(cout);
    return 0;
}
