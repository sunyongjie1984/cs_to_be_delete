#include <iostream>
#include <string>
using namespace std;
class Screen {
public:
    typedef string::size_type index;
    char get() const { return contents[cursor]; } // default inline
    inline char get(index ht, index wd) const;    // explicitly define inline
    index get_cursor() const;
    Screen(index hght, index wdth, const string &cntnts);

    Screen& move(index r, index c);
    Screen& set(char);
    Screen& display(ostream &os);

    const Screen& display(ostream &os) const;

private:
    void do_display(ostream &os) const { // 把两个display函数简化为了一个，好处多多啊
        string::size_type index = 0;
        while (index != contents.size()) {
            os << contents[index];
            if ((index + 1) % width == 0) {
                os << '\n';
            }
            ++index;
        }
        // os << contents; // 课本的源程序，但是和习题中的有些小出入
    }
    string contents;
    index cursor;
    index height, width;
};

Screen::Screen(index hght, index wdth, const string &cntnts = ""):
cursor(0), height(hght), width(wdth)
{
    contents.assign(hght * wdth, ' ');
    if (cntnts.size() != 0)
        contents.replace(0, cntnts.size(), cntnts);
}

char Screen::get(index r, index c) const
{
    index row = r * width;
    return contents[row + c];
}

inline Screen::index Screen::get_cursor() const
{
    return cursor;
}
// 设置那个字母
Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
// 确定那个位置要设置值
Screen& Screen::move(index r, index c)
{
    index row = r * width;
    cursor = row + c;
    return *this;
}
// 显示整个字符串
Screen& Screen::display(ostream &os)
{
    do_display(os);
    return *this;
}
// const display
// first, display is supposed to be a const member function,
// because, display is show the content, will not modiry the object.
// but, if there is only one const display,
// expression like below is not available, myscreen2 is non-const object.
// myscreen2.move(4, 0).set('#').display(cout);
// and if there is only one non-const display, as I have mention
// it is not logically good idea.
// so the overload method is implemented.
const Screen& Screen::display(ostream &os) const
{
    do_display(os);
    return *this;
}
