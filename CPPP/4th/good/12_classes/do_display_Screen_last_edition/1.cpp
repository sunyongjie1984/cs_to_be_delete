#include "Screen.h"
int main()
{   // 这回算是解释清楚了一些const了，呵呵
    const Screen myscreen(5, 6, "123456123456123456123456123456123456");
    myscreen.display(cout);

    cout << endl;
    // Screen myscreen2(5, 6); // ok^_^~
    // Screen myscreen2(5, 6, ""); // ok^_^~
    // Screen myscreen2(5, 6, " "); // ok^_^~
    // Screen myscreen2(5, 6, ); // 错
    // Screen myscreen2(5, 6, "I Love China"); // ok
    Screen myscreen2(5, 6, "123456123456123456123456123456123456");
    myscreen2.move(4, 0).set('#').display(cout);

    cout << endl;
    cout << myscreen2.get_cursor() << endl;
    return 0;
}
