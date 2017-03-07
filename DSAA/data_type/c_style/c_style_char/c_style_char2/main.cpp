#include <iostream>
#include <string>

int main()
{
    char c0 = 'a';                 // 字符类型对象c0为non-const
    char* p0_c0 = &c0;             // 指向non-const字符类型对象的指针类型对象p0_c0为non-const
    // 程序员打算通过p0_c0修改c0，程序员打算修改p0_c0的值，来改变指针对象的指向
    char* const p1_c0 = &c0;       // 指向non-const字符类型对象的指针类型对象p1_c0为const
    // 程序员打算通过p1_c0修改c0，程序员不打算也不可以修改p1_c0的值，来改变指针对象的指向
    const char* p2_c0 = &c0;       // 指向non-const或const字符类型对象的指针类型对象p2_c0为non-const
    // 程序员不打算也不可以通过p2_c0修改c0，程序员打算修改p2_c0的值，来改变指针对象的指向
    const char* const p3_c0 = &c0; // 指向non-const或const字符类型对象的指针类型对象p3_c0为const
    // 程序员不打算也不可以通过p3_c0修改c0，程序员不打算也不可以修改p3_c0的值，来改变指针对象的指向

    char const c1 = 'a';           // 字符类型对象c1为const
    const char* p0_c1 = &c1;       // 指向non-const或const字符类型对象的指针类型对象p0_c1为non-const
    // 程序员不打算也不可以通过p0_c1修改c1，程序员打算修改p0_c1的值，来改变指针对象的指向
    const char* const p1_c1 = &c1; // 指向non-const或const字符类型对象的指针类型对象p1_c1为const
    // 程序员不打算也不可以通过p1_c1修改c1，程序员不打算也不可以修改p1_c1的值，来改变指针对象的指向

    const char c2 = 'a';           // 字符类型对象c2为const，我不喜欢的定义方式，与对象以c1类型相同

    // 对象p0_c0，p1_c0，p2_c0，p3_c0，p0_c1，p1_c1都是指向---字符类型对象---的指针

    //char* p2_c1 = &c1;           // error，cannot convert from 'const char *' to 'char *'
    // 对象p2_c1是指向non-const字符类型对象的，意味着程序员可以通过对指针的解
    // 引用来修改p2_c1所指向的对象，而c1是const，这是矛盾的。
    //char* const p3_c1 = &c1;     // 同上



    // 理解二补充，c++ primer和我自己的理解
    char ca1[] = {'C', '+', '+'};        // no null, not C-style string
    char ca2[] = {'C', '+', '+', '\0'};  // explicit null
    char ca3[] = "C++";     // null terminator added automatically
    char const *cp = "C++"; // null terminator added automatically
    char *cp1 = ca1;        // points to first element of a array, but not C-style string
    char *cp2 = ca2;        // points to first element of a null-terminated char arra
    // ca1 和 cp1 都不是 C 风格字符串：ca1 是一个不带结束符 null 的字符数组，而指针 cp1 指向 ca1，
    // 因此，它指向的并不是以 null 结束的数组。其他的声明则都是C风格字符串，数组的名字即是指向该数组
    // 第一个元素的指针。于是，ca2 和 ca3 分别是指向各自数组第一个元素的指针。

    // warning
    // 无论如何都是要把它看作是定义了一个指针，再不要看成是定义了一个字符串对象了。
    // 


    // 指向non-const或const字符型对象的指针对象q为non-const
    // 程序员不打算也不可以通过q去修改c风格字符串的首字母，程序员打算修改q的值，以改变q的指向
    char const * q = "I love China";
    q = "I love American"; // ok
    // *q = 'a'; 对比*p = 'a'可以看出一个是编译能不能通过，一个是编译通过，但是运行崩溃。


    // 指向non-const字符型对象的指针对象pp为non-const
    // 程序员打算通过pp去修改c风格字符串的首字母，程序员打算修改pp的值，以改变pp的指向
    // 但是，这是一个特例，编译可通过，运行时出错，可能因为本身c风格字符串是常量吧，不可以修改
    char * pp = "I love China";

    pp = "I love American"; // ok
    pp++;                   // ok

    // *p = 'a'; 编译可以通过，但是运行就会崩溃














    // C++ 语言通过(const)char*类型的指针来操纵C风格字符串。一般来说，我们使用指针的算术操作来遍历
    // C 风格字符串，每次对指针进行测试并递增 1，直到到达结束符 null 为止
    const char *cp3 = "some value";
    while (*cp3) {
        // do something to *cp
        ++cp3;
    }
    // while 语句的循环条件是对 const char* 类型的指针 cp 进行解引用，并判断 cp 当前指向的字符是 true 值
    // 还是 false 值。真值表明这是除 null 外的任意字符，则继续循环直到 cp 指向结束字符数组的 null 时，
    // 循环结束。while 循环体做完必要的处理后，cp 加1，向下移动指针指向数组中的下一个字符
    // 如果 cp 所指向的字符数组没有 null 结束符，则此循环将会失败。这时，循环会从 cp 指向的位置开始读数，
    // 直到遇到内存中某处 null 结束符为止

    // cstring 是 string.h 头文件的 C++ 版本，而 string.h 则是 C 语言提供的标准库。
    // 传递给这些标准库函数例程的指针必须具有非零值，并且指向以 null 结束的字符数组中的第一个元素。
    // 其中一些标准库函数会修改传递给它的字符串，这些函数将假定它们所修改的字符串具有足够大的空间
    // 接收本函数新生成的字符，程序员必须确保目标字符串必须足够大。
    // C++ 语言提供普通的关系操作符实现标准库类型 string 的对象的比较。这些操作符也可用于比较指向
    // C风格字符串的指针，但效果却很不相同：实际上，此时比较的是指针上存放的地址值，而并非它们所指向的字符串：
    // if (cp1 < cp2) // compares addresses, not the values pointed to
    // 如果 cp1 和 cp2 指向同一数组中的元素（或该数组的溢出位置），上述表达式等效于比较在 cp1 和 cp2
    // 中存放的地址；如果这两个指针指向不同的数组，则该表达式实现的比较没有定义。
    // 字符串的比较和比较结果的解释都须使用标准库函数 strcmp 进行：

    const char *cp4 = "A string example";
    const char *cp5 = "A different string";
    int i = strcmp(cp4, cp5);    // i is positive
    i = strcmp(cp5, cp4);        // i is negative
    i = strcmp(cp4, cp4);        // i is zero
    // 标准库函数 strcmp 有 3 种可能的返回值：若两个字符串相等，则返回 0 值；若第一个字符串大于第二个字符串，
    // 则返回正数，否则返回负数。

    // 调用者必须确保目标字符串具有足够的大小
    // 传递给标准库函数 strcat 和 strcpy 的第一个实参数组必须具有足够大的空间存放新生成的字符串。
    // 以下代码虽然演示了一种通常的用法，但是却有潜在的严重错误：
    // Dangerous: What happens if we miscalculate the size of largeStr?
    char largeStr[16 + 18 + 2];         // will hold cp1 a space and cp2
    strcpy(largeStr, cp1);              // copies cp1 into largeStr
    strcat(largeStr, " ");              // adds a space at end of largeStr
    strcat(largeStr, cp2);              // concatenates cp2 to largeStr
    // prints A string example A different string
    std::cout << largeStr << std::endl;
    // 问题在于我们经常会算错 largeStr 需要的大小。同样地，如果 cp1 或 cp2 所指向的字符串大小发生了变化，
    // largeStr 所需要的大小则会计算错误。不幸的是，类似于上述代码的程序应用非常广泛，这类程序往往容易出错，
    // 并导致严重的安全漏洞。

    // 使用 strn 函数处理C风格字符串
    // 如果必须使用 C 风格字符串，则使用标准库函数 strncat 和 strncpy 比 strcat 和 strcpy 函数更安全：

    char largeStr2[16 + 18 + 2]; // to hold cp1 a space and cp2
    strncpy(largeStr2, cp1, 17); // size to copy includes the null
    strncat(largeStr2, " ", 2);  // pedantic, but a good habit
    strncat(largeStr2, cp2, 19); // adds at most 18 characters, plus a null
    // 使用标准库函数 strncat 和 strncpy 的诀窍在于可以适当地控制复制字符的个数。特别是在复制和串连字符串时，
    // 一定要时刻记住算上结束符 null。在定义字符串时要切记预留存放 null字符的空间，因为每次调用标准库函数后
    // 都必须以此结束字符串 largeStr。让我们详细分析一下这些标准库函数的调用：

    // 调用 strncpy 时，要求复制 17 个字符：字符串 cp1 中所有字符，加上结束符 null。留下存储结束符 null
    // 的空间是必要的，这样 largeStr 才可以正确地结束。调用 strncpy 后，字符串 largeStr 的长度 strlen 
    // 值是 16。记住：标准库函数 strlen 用于计算 C 风格字符串中的字符个数，不包括 null结束符。

    // 调用 strncat 时，要求复制 2 个字符：一个空格和结束该字符串字面值的 null。调用结束后，字符串 largeStr
    // 的长度是 17，原来用于结束 largeStr 的 null 被新添加的空格覆盖了，然后在空格后面写入新的结束符 null。

    // 第二次调用 strncat 串接 cp2 时，要求复制 cp2 中所有字符，包括字符串结束符 null。调用结束后，字符串 
    // largeStr 的长度是 35：cp1 的 16 个字符和 cp2 的 18 个字符，再加上分隔这两个字符串的一个空格。

    // 整个过程中，存储 largeStr 的数组大小始终保持为 36（包括结束符）

    // 只要可以正确计算出 size 实参的值，使用 strn 版本要比没有 size 参数的简化版本更安全。但是，如果要向目标
    // 数组复制或串接比其 size 更多的字符，数组溢出的现象仍然会发生。如果要复制或串接的字符串比实际要复制
    // 或串接的 size 大，我们会不经意地把新生成的字符串截短了。截短字符串比数组溢出要安全，但这仍是错误的。
    return 0;
}
