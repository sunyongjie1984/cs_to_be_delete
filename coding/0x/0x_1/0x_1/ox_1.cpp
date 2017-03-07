#include <iomanip>
#include <iostream>
#include <stdio.h>

using std::hex;
using std::dec;
using std::oct;

// windows little end low bytes store low bits

int main()
{
#ifdef _DEBUG
    std::cout << (8 == sizeof(int*) ? "64 bit program" : "32 bit program")  << std::endl;
    if (8 == sizeof(int*))
    {
#ifdef __linux
        std::cout << "hello this program is running on linux" << std::endl;
        std::cout << "in linux sizeof(long) is: " << sizeof(long) << std::endl;
#endif
#ifdef _WIN64
        std::cout << "hello this program is running on _WIN64" << std::endl;
        std::cout << "in windows sizeof(long) is: " << sizeof(long) << std::endl;
#endif
    }
    else
    {
#ifdef __linux
        std::cout << "hello this program is running on linux" << std::endl;
        std::cout << "in linux sizeof(long) is: " << sizeof(long) << std::endl;
#endif
#ifdef _WIN32
        std::cout << "hello this program is running on _WIN32" << std::endl;
        std::cout << "in windows sizeof(long) is: " << sizeof(long) << std::endl;
#endif
    }

#endif // DEBUG

    std::cout << "sizeof(int)       =: " << sizeof(int) << std::endl;
    std::cout << "sizeof(long)      =: " << sizeof(long) << std::endl;
    std::cout << "sizeof(long long) =: " << sizeof(long long) << std::endl;

    int test_negative_ox = -0x17;
    std::cout << test_negative_ox << std::endl;

    //                  -0x80000000   0x7FFFFFFF
    //                  -(2 31)       (2 31) - 1 
    // int number range [-2147483648, 2147483647]
                                                      // 4 byte 7654 3210 7654 3210  7654 3210 7654 3210
    int a = 0x00000001; //        1    = 1 x (16 0)             0000 0000 0000 0000  0000 0000 0000 0001
    int b = 0x00000010; //       16    = 1 x (16 1) 1 x (2 4)   0000 0000 0000 0000  0000 0000 0001 0000
    int c = 0x00000100; //      256    = 1 x (16 2) 1 x (2 8)   0000 0000 0000 0000  0000 0001 0000 0000
    int d = 0x00001000; //     4096    = 1 x (16 3) 1 x (2 12)  0000 0000 0000 0000  0001 0000 0000 0000
    int e = 0x00010000; //    65536    = 1 x (16 4) 1 x (2 16)  0000 0000 0000 0001  0000 0000 0000 0000
    int f = 0x00100000; //  1048576    = 1 x (16 5) 1 x (2 20)  0000 0000 0001 0000  0000 0000 0000 0000
    int g = 0x01000000; // 16777216    = 1 x (16 6) 1 x (2 24)  0000 0001 0000 0000  0000 0000 0000 0000
    int h = 0x10000000; // 268435456   = 1 x (16 7) 1 x (2 28)  0001 0000 0000 0000  0000 0000 0000 0000
    int i = 0x80000000; // first first this definition has a auto type conversions, I have to be aware that
    // 0x80000000 is a literal, the compiler ensure it is a positive, because the negative way is like this -0x7 
    // first 1000 0000 0000 0000  0000 0000 0000 0000, the 1 in the head means i is a negative
    // and to find the exact negative number of i, the method is reverse all bits, and plus 1, got the opponent positive 
    // number, reverse 0111 1111 1111 1111  1111 1111 1111 1111 , plus one, 1000 0000 0000 0000  0000 0000 0000 0000
    // and this is (2 31), so because i is a signed int, i is -2147483648, the smallest number that a int can present
    int j = 0x8FFFFFFF; // -1879048193
    int k = 0xFFFFFFFF; // -1
    int l = 0x7FFFFFFF; // 2147483647  = 7 x (16 7) 7 x (2 28)  0111 1111 1111 1111  1111 1111 1111 1111 biggest number 2147483647  

                                                                               // 4 byte
                                                                     // 7654 3210 7654 3210 7654 3210  7654 3210 7654 3210
    long long m = 0x0080000000; // 268435456   = 8 x (16 7) 1 x (2 28)  0000 0000 1000 0000 0000 0000  0000 0000 0000 0000
                           
    long n = 0x0100000000; // n and o has been force cut
    long o = 0x8000000000;

    long long p = 0x0100000000;
    long long q = 0x8000000000;

    std::cout << "dec a=: " << dec << a << std::endl;
    std::cout << "dec b=: " << dec << b << std::endl;
    std::cout << "dec c=: " << dec << c << std::endl;
    std::cout << "dec d=: " << dec << d << std::endl;
    std::cout << "dec e=: " << dec << e << std::endl;
    std::cout << "dec f=: " << dec << f << std::endl;
    std::cout << "dec g=: " << dec << g << std::endl;
    std::cout << "dec h=: " << dec << h << std::endl;
    std::cout << "dec i=: " << dec << i << std::endl;
    std::cout << "dec j=: " << dec << j << std::endl;
    std::cout << "dec k=: " << dec << k << std::endl;
    std::cout << "dec l=: " << dec << l << std::endl;
    std::cout << "dec m=: " << dec << m << std::endl;
    std::cout << "dec n=: " << dec << n << std::endl;
    std::cout << "dec o=: " << dec << o << std::endl;
    std::cout << "dec p=: " << dec << p << std::endl;
    std::cout << "dec q=: " << dec << q << std::endl;


    std::cout << std::endl;

    std::cout << "hex a=: " << hex << a << std::endl;
    std::cout << "hex b=: " << hex << b << std::endl;
    std::cout << "hex c=: " << hex << c << std::endl;
    std::cout << "hex d=: " << hex << d << std::endl;
    std::cout << "hex e=: " << hex << e << std::endl;
    std::cout << "hex f=: " << hex << f << std::endl;
    std::cout << "hex g=: " << hex << g << std::endl;
    std::cout << "hex h=: " << hex << h << std::endl;
    std::cout << "hex i=: " << hex << i << std::endl;
    std::cout << "hex j=: " << hex << j << std::endl;
    std::cout << "hex k=: " << hex << k << std::endl;
    std::cout << "hex l=: " << hex << l << std::endl;
    std::cout << "hex m=: " << hex << m << std::endl;
    std::cout << "hex n=: " << hex << n << std::endl;
    std::cout << "hex o=: " << hex << o << std::endl;
    std::cout << "hex p=: " << hex << p << std::endl;
    std::cout << "hex q=: " << hex << q << std::endl;

    std::cout << "test_negative_ox hex: " << std::endl;
    std::cout << test_negative_ox << std::endl;

    getchar();
    return 0;
}
