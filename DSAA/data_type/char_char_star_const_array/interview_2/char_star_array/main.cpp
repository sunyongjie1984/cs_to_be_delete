#include <iostream>
#include <string>

char const * p[] = { "wang zong", "sun zong", "china" };
char const * q[] = { "wang zong2", "sun zong2", "china2" , 0 }; // 0 is necessary

char * pp[] = { "wang zong", "sun zong", "china" };
char * qq[] = { "wang zong", "sun zong", "china" , 0 };

char * a       = "hello world";
char const * b = "hello world again";

int main()
{
    for (int i = 0; NULL != q[i]; i++)
    {
        std::cout << q[i] << std::endl;
    }

    std::cout << "end\n" << std::endl;

    for (int i = 0; NULL != p[i]; i++)
    {
        std::cout << p[i] << std::endl;
    }
    return 0;
}
