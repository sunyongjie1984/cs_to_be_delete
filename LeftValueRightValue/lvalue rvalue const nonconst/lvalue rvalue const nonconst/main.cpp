// 以下是我个人的理解，如有错误请告知，非常感谢你。
#include <string>
#include <iostream>
using namespace std;
string one("cute");         // non-const lvalue
const string two("fluffy"); // const lvalue
string three()              // non-const rvalue
{
    return "kittens";
}
const string four()         // const rvalue
{
    return "are an essential part of a healthy diet";
}
string& five(string& i)
{
    std::cout << i;
    i = "haha";
    return i;
}
void six(const string& i)
{

}
void six(string& i)
{

}
// 1，左值，右值针对表达式而言，而不是针对对象。
// 2，表达式是一个或多个操作数通过操作符组合而成，最简单的表达式只包含一个字面值或变量。我认为函数调用也是一个表达式，因为操作符对操作数操作是函数调用。
// 3，每个表达式都会产生一个结果，这个结果可以分成左值和右值，这是一个全集，只有两种可能。
// 4，什么是语句，语句是表达式加分号。
// 5，lvalue是指那些单一表达式结束之后依然存在的持久对象。例如： obj，*ptr， prt[index]，++x 都是lvalue。
// 6，上面的话强调一个操作数，一个操作符的表达式返回的结果，在表达式结束之后依然存在的持久对象，
// 7，如果说这个表达式结束之后就是一个分号，那么这个表达式的结果，也不会消失。
// 8，另一个培养判断一个表达式是不是 lvalue 的直觉感的方法就是自问一下"我能不能对表达式取址？"，
// 9，如果能够，那就是一个 lvalue；如果不能，那就是 一个 rvalue。
int main()
{
    345;       // 345这是一个字面值，所以它又是一个表达式，加上一个分号就构成了语句，这些都是合法的。
               // 这个字面值是不可以取址的，所以字面值表达式的结果是一个右值。
    string i = "hehe";
    i;         // i是一个变量，所有它也是一个表达式，加上一个分号就构成了语句。
               // 这个表达式的值就是对象i，在分号之后继续存在，而且也可以被取址，所以这个表达式是一个左值。
    three();   // three()是一个表达式，这个表达式的结果是一个string类型的临时对象，这个对象在分号之后就会消失，我不知道它能不能被取址，反正它是右值。
               // 不明白如果它是右值，它就是不能被取址么，还是说8和5都是必要条件，都满足才是左值，右值不一定都要满足，有一个满足就是右值，还有因为是
               // 全集的关系，非左值即是右值。
    four();    // four()是一个表达式，这个表达式的结果是一个const string类型的临时对象，在分号之后就会消失，所以这是一个const右值。
    five(i);   // five(i)是一个表达式，当且仅当函数调用返回一个引用的时候，函数调用表达式是一个左值。
               // Type&可绑定到non-const lvalue，比如本例（可以用这个引用来读取和修改原来的值），但不能绑定到const lvalue，因为那将违背const正确性；
               // 也不能把它绑定到non-const rvalue，这样做极端危险，你用这个引用来修改临时对象，但临时对象早就不存在了，
               // 这将导致难以捕捉而令人讨厌的 bug，因此 C++ 明智地禁止这这么做。
    five(three()); // Type&绑定到non-const rvalue，这句话不是不行么，vs2008就是能够编译通过且运行没有问题呀，服了。
                   // 把编译选项改为了/w4，出了warning c4239，MSDN：This type conversion is not allowed by the C++ standard,
                   // but it is permitted here as an extension. This warning is always followed by at least one line of
                   // explanation describing the language rule being violated.
                   // C4239.cpp
                   // compile with: /W4 /c
                   //struct C {
                   //   C() {}
                   //};
                   //void func(void) {
                   //   C & rC = C();   // C4239，C()表达式的结果是标准的non-const rvalue，匿名对象，临时变量等等叫法我不知道对不对，但是
                   //                   non-const rvalue应该是正确的叫法
                   //   const C & rC2 = C();   // OK
                   //   rC2;
                   //}
                   // 表达式的结果实际上有四种，non-const lvalue, non-const rvalue, const lvalue, const rvalue
                   // Type&只可能绑定到non-const lvalue, 不能绑定到const lvalue, const rvalue，显而易见，因为它们是const 而Type&不是。
                   // 不能绑定到non-const rvalue已经如上作了说明。
                   // 关于为什么，c++语言认为，定义一个非const的函数，你就是有要修改传入实参的企图，如果你不想
                   // 修改它，为什么不把函数定义一个接受const对象的函数，即定义为const Type&。而一但你把函数定义为Type&，那么c++语言就认为
                   // 在二种non-const这一的non-const rvalue就危险了，所以c++压根就禁止了你这么做，因为non-cnost rvalue的生命期的问题。
                   // 总结Type&只能接受四种类型之一的non-const lvalue。两种情况下常见，一种是直接的定义引用时，一种是five这种情况。

    six(i);        // 函数six有个重载版本，一个接受const string&, 一个接受string&，当实参为一个non-const的时候，比如本例，这时候会调用
                   // non-const版本，优先匹配，对于const Type&它能接受四种类型中的每一种类型的对象，对于lvalue的两种类型没有什么说的，
                   // 对于rvalue的两种类型，它会先生成一个临时变量，然后让引用关联这个临时变量，而且我认为这不是一个临时变量，而是一个
                   // 临时的局部变量，因为在分号之后，这个临时变量应该还不在其生命期内的，因为引用还是要有关联的内存的，引用是左值，总
                   // 要可以取址吧，取到一个临时变量是不可以的，所以我把这种变量叫临时局部变量，说它临时，是因为程序员看不到，说它局部
                   // 是因为它的生命期应该从定义到函数结尾return这前。这个在c++ primer的书上也是这样讲了一点，和我说的不一样，
                   // double dval = 3.14;
                   // cosnt int& i = dval; // 书中说编译器会把这些代码转换成如下形式的代码
                   //
                   // double dval = 3.14;
                   // int temp = dval;
                   // const int& i = temp;
    return 0;
}
