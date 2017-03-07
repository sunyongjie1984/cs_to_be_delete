int main()
{
    int j = 10;
    const int& i = j; // const引用可以绑定到non-const对象，non-const引用却不能绑定到const对象
    // i++; wrong
    j++; // ok
    return 0;
}