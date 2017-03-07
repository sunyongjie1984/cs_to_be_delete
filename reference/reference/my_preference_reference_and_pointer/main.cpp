int main()
{
    // modify start for coding rule and style
    // the following way of comment is good
    /* 类型名*& const    对象名  meaning
     * int*     const    p       // ok，p是const，不可以修改p的值，来改变指针对象p的指向
     * int&     const    r       // bad，r是一个引用，定义时初始化到死绑定一人，qualifier const is ignored
     *                           // 这个const无意义
     *
     * const    类型名*& 对象名   说明
     * const    int*     p        // ok，不可以通过p，去修改p指向的对象
     * const    int&     r        // ok，不可以通过r，去修改r绑定的对象
     */
    int i = 10;
    int* const pp1 = &i;      // pp1为const对象，不可以修改pp1的值，来改变pp1的指向
#ifndef SUNYJ_UNIXLIKE
    int& const rr1 = i;       // ignored，无意义(in windows visual 2012), error in linux

    rr1 = 10;
#endif

    const int* pp2 = &i;
    const int& rr2 = i;

    // *pp2 = 10;              // error
    // rr2  = 10;              // error

                               // 用语言描述的方法，对象名前描述对象类型，对象名后描述const性质
    int a = 10;                // 整型对象a为non-const
    int const b = 20;          // 整型对象b为const
    int const c = 20;          // 整型对象c为const
    int* p = &a;              // 指向non-const整形对象的指针对象p为non-const
                               // 程序员打算通过p修改a，程序员打算修改p
    const int* p2 = &a;       // 指向non-const或者const整型对象的指针对象p2为non-const
                               // 程序员不打算也不可以通过p2修改a，程序员打算修改p2
    const int* p3 = &b;       // 指向non-const或者const整型对象的指针对象p3为non-const
                               // 程序员不打算也不可以通过p3修改b，程序员打算修改p3
    int* const p4 = &a;       // 指向non-const整形对象的指针对象p4为const
                               // 程序员打算通过p4修改a，程序员不打算也不可以修改p4
    const int* const p5 = &a; // 指向non-const或者const整型对象的指针对象p5为const
                               // 程序员不打算也不可以通过p5修改a，程序员不打算也不可以修改p5 
    const int* const p6 = &b; // 指向non-const或者const整型对象的指针对象p6为const
                               // 程序员不打算也不可以通过p6修改b，程序员不打算也不可以修改p6 
    int& r = a;               // 绑定到non-const整型对象的引用对象r为non-const
                               // 程序员打算通过r修改a
    const int& r2 = a;        // 绑定到non-const或者const整型对象的引用对象r2为const
                               // 程序员不打算也不可以通过r2修改a
    const int& r3 = b;        // 绑定到non-const或者const整型对象的引用对象r3为const
                               // 程序员不打算也不可以通过r3修改b
    // add start for testing the above definition
    *p = 10;                   // ok，通过p修改a
    ++p;                       // ok，修改p的值，以改变指针对象的指向

    // *p2 = 10;               // error，不可以通过p2修改a，不是因为a为const，而是因为p2的定义
    ++p2;                      // ok，修改p2的值，以改变指针对象的指向

    // *p3 = 10;               // error，不可以通过p3修改a，不是因为b为const，而是因为p3的定义
    ++p3;                      // ok，修改p3的值，以改变指针对象的指向

    *p4 = 10;                  // ok，通过p4修改a
    // ++p4;                   // error，修改p4的值，因为对象p4为const

    // *p5 = 10;               // error，通过p5修改a
    // ++p5;                   // error，修改p5的值，以改变指针对象的指向

    // *p6 = 10;               // error，通过p6修改a
    // ++p6;                   // error，修改p6的值，以改变指针对象的指向
    // add end for testing the above definition
    // 2011_12_01_syj


    // int* p7 = &b;          // cannot convert from 'const int *' to 'int *'
                              // 对象b类型为const int，对象&b类型为const int*，对象p7类型为int*
                              // 程序员打算通过p7修改对象b，而对象b类型为const int，所以出错
    // int& r6 = b;           // cannot convert from 'const int' to 'int &'
                              // 对象r6类型为int&, 对象b类型为const int
                              // 程序员打算通过r6修改b，而对象b类型为const int，所以出错
    // int& const r7 = b;     // 错误的定义方式
    // modify end for coding rule and style
    // 2011_12_01_syj
}
