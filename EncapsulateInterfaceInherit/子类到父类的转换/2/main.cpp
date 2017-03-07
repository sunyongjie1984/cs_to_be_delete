// #include "CBase.h"
#include "CDerive.h"

void print_total(ostream& os, const CBase& item, size_t n)
{  
    os << "ISBN: " << item.book() << "\tnumber sold: " << n << "\ttotal price: "
        << item.net_price(n) << endl;
}

void print_total2(ostream& os, const CBase item, size_t n)
{
    os << "ISBN: " << item.book() << "\tnumber sold: " << n << "\ttotal price: "
        << item.net_price(n) << endl;
}

// c++ primer 4 15.3.1 Derived-to-Base conversions
// 1,if we have an object of a derived type, we can use its address to ASSIGN OR INITIALIZE  
// a pointer to the base type.
// 2,similarly, we can use a reference or object of the derived type to INITIALIZE a 
// reference to the base type.
// 3,pedantically speaking, there is no similar conversion for objects. The compiler will
// not automatically CONVERT an object of derived type into an object of the base type.
// 4,It is,however,usually possible to use a derived-type object to INITIALIZE or ASSIGN 
// an object of base type.
// 5,The difference between initializing and/or assigning an object and the automatic 
// conversion that is possible for a reference or pointer is subtle and must be well 
// understood.
int main()
{
    CDerive a("sunyongjie", 10, 10, 0.1); // isbn, price, min_qty, discount.
    print_total(cout, a, 10);             // discount.
    print_total(cout, a, 9);              // no discount.
    CBase b("wangjie", 10);
    print_total(cout, b, 10);
    cout << "....................................................\n";
    CBase* p = &b;
    print_total(cout, *p, 10);
    CBase* p1 = &a;             // initialize a pointer to the base type/
    print_total(cout, *p1, 10); // dynamic binding.
    cout << "....................................................\n";
    CBase* q = &b;
    print_total(cout, *q, 10);
    q = &a;                    // assign a pointer to the base type.
    print_total(cout, *q, 10); // dynamic binding.
    cout << "....................................................\n";
    CBase& m = a;              // object initialize a reference to the base type.
    print_total(cout, a, 10);  // dynamic binding.
    CDerive& b1 = a;
    CBase& n = b1;             // reference initialize a reference to the base type.
    print_total(cout, n, 10);  // dynamic binding.
    cout << "....................................................\n";
    CBase& m1 = b;
    m1 = a;                    // object assign a reference to the base type.
    print_total(cout, m1, 10); // NOT DYNAMIC BINDING. compare to print_total(cout, *q, 10);
	// from // 2, similarly, we can use a reference or object of the derived type to INITIALIZE a 
	// reference to the base type.
    // we can see it is clearly written on the c++ primer book.
    // another test below.
    cout << "....................................................\n";
    CBase* qq = &b;
    qq->display_all_data_member();
    qq = &a;
    qq->display_all_data_member(); // dynamic binding.
    CBase& qq2 = b;
    qq2.display_all_data_member();
    qq2 = a;
    qq2.display_all_data_member(); // NOT DYNAMIC BINDING
    cout << "....................................................\n";
    // 3,pedantically speaking, there is no similar conversion for objects. The compiler will
    // not automatically CONVERT an object of derived type into an object of the base type.
    CDerive k("hehe", 10);
    CBase k3 = (CBase)k;
    k3.display_all_data_member();
    CDerive s("hehe", 10, 10, 0.1);  
    CBase s3 = (CBase)s; // I don't understand,这不是转换么，难道问题出在automatically CONVERT
    s3.display_all_data_member(); // 我这里是强制转换。我定义一个print_total2试一下非强制转换
    print_total2(cout, s, 10); // 这里居然也不行，这难道不是编译器自动转换了么？
    // and in c++ primer conversion to a reference is not the same as converting an object
    // as we've seen, we can pass an OBJECT of derived type to a function expecting a reference
    // to base, We might therefore think that the object is converted. However, that is not
    // what happens. When we pass an object to a function expecting a reference, the
    // reference is bound directly to that object. Althought it appears that we are passing
    // an object, the argument is actually a reference to that object. The object itself is not
    // copied and the conversion doesn't change the derived-type object in any way. It remains
    // a derived-type object.
    // 也就是说在函数print_total执行的时候，我们根据这个函数的参数看出它要接受一个引用，
    // 在参数传递的时候传过去的就是一个实参的引用(the argument is actually a reference to
    // that object)，这个引用是真实的实参，形参(是一个引用)通过实参初始化自己。
    // 下面的话与上面对比，表面都是传递对象，实际一个传递引用，一个传递对象。传递引用的只是
    // 生成了一个指向父类对象的引用实际指向了子类对象；传递对象的，真正通过子类对象的父类部
    // 份生成了一个父类对象。
    // when we pass a derived object to a function expecting a base-type object(as opposed to
    // a reference)the situation is quite different. In that case, the parameter's type is
    // fixed--both complile time and run time it will be a base-type object. If we call such
    // a function with a derived-type object, then the base-class portion of that derived
    // object is copied into the parameter(这句话与3不是矛盾么？根据3与4的说法，子类对象不可
    // 自动转换我不知道是不是隐式转换的意思为父类对象，但是可以初始化父类对象或给父类对象赋
    // 值，难道我的print_total2也不是一个好的自动转化的例子，那么怎么样才是自动转换呢？)
    
    cout << "....................................................\n";
    // 4,It is,however,usually possible to use a derived-type object to INITIALIZE or ASSIGN 
    // an object of base type. 
    // using a derived object to initialize or assign a base object
    // when we initialize or assign an object of base type, we are actually calling a function
    // when we initialize, we're calling a constructor; when we assign, we're calling an 
    // assignment operator.
    // when we use a derived-type object to initialize or assign a base object, there are two
    // possibilities, the first possibility is that the base class might explicitly define
    // what it means to copy or assign an object of the derived type to an object of the 
    // base type. It would do so by defining an appropriate constructor or assignment operator
    // class Derived;
    // class Base {
    // public:
        // Base(const& Derived&);
        // Base& operator=(const Derived&);
    // }; however, it is uncommon. Instead, base class usually define their own copy constructor
    // and assignment operator. 还是看书吧，比较长。c++ primer 4 page 578
    CBase kkk = a; // initialize.
    kkk.display_all_data_member();
    kkk = k;       // assign.
    kkk.display_all_data_member();
    
    return 0;
}