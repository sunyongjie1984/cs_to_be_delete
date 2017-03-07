#include "Screen.h"
int main()
{
    // 书中又用了do_display来解释了如何处理const对象与非const对象的显示
    cout << "第一组输出是默认的contents也就是由空格填充的" << endl;
    Screen myScreen(5, 6);
    myScreen.move(4, 0).set('#').display(cout);

    cout << "\n\n";
    cout << "第二组输出是在源文件中赋的值" << endl;
    Screen myScreen2(5, 6, "123456123456123456123456123456123456");
    myScreen2.move(4, 0).set('#').display(cout);

    cout << "\n\n";
    cout << "第三组调用的是const的display函数，由const的对象调用" << endl;
    const Screen myScreen3(5, 6, "123456123456123456123456123456123456");
    myScreen3.display(cout); // 因为上面的.move .set都是非const的函数

    return 0;
}
