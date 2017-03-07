class X {
public:
    X(int i)
    {
        x = i;
    }
private:
    int x;
};
int main()
{
    // 情况一
    const double i1 = 3.14;
    const double& rr1 = i1; // ok

    double i2 = 3.14;
    double& rr2 = i2; // ok

    // 情况二
    double dval   = 3.14;
    //int& ri2    = dval; // wrong， 非const引用只能绑定到与该类型同类型的对象
    const int& ri = dval; // ok，    const引用则可以绑定到不同但相关的类型的对象或绑定到右值
    // 上的面语句等于下边的两条语句
    // int temp = dval;
    // const int& ri = temp;
    // 也就是说，const引用能关联到具体的const左值对象，就关联到const左值对象，如果不能，则会生成一个临时变量，然后关联到那个临时变量
    // 按照上面的写法来自于c++ primer中，那就不是一个临时变量，而一个局部变量，这两个东西的生命期是不一样的，临时变量是语句结束就没有了
    // 局部变量是和这个引用是一个生命期的
    // 相关类型其中一种就是可以隐式转换了类型，隐式转换的类型中的一种
    // 有一类型X，X有一个构造函数X(int)，则const X& r = 3;是合法的
    const X& r  = 3;     // ok，我认为在这里调用X(3)生成了一个右值，就是所谓的匿名对象，生成完这个对象完成引用的初始化工作之后，这个对象就析构了，
    // 这个时候的临时对象和一些其它的临时对象可能还不同，因为它不能被析构，不然引用的指向不就有问题了么，但是X(3)生成的是右
    // 值这点错不了，const引用也能保证这个右值不被修改
    const X& r2 = 3.14;  // ok，两次类型转换
    // const X& r3 = "heh"; // wrong，不是相关类型，不能隐式转换
    return 0;
}
