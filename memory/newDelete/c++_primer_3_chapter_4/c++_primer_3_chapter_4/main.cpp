#include <string>
using std::string;
int main()
{
    // new 的几种情况
    // 内置类型
    int* pi = new int;
    int* pi2 = new int(3);
    int* pi3 = new int[20];
    int* pi4 = new int[20]();
    // int* pi4 = new int[20](3);

    // 自定类型
    string* ps = new string;
    string* ps2 = new string("heeh");
    string* ps3 = new string[20];
    string* ps4 = new string[20]();
    // string* ps4 = new string[20]("heeh");

    return 0;
}
