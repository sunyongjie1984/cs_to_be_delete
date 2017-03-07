#include <iostream>
#ifdef __linux
#include <stdio.h>
#endif

const char* my_strcpy(const char* q, const char* p)
{
    const char* ret;
    const char* pOri = p;
    const char* tmp;
    while('\0' != *q++)
    {
        p = pOri;
        ret = tmp = q;
        if (*q == *p)
        {
            while ('\0' != *tmp && *tmp++ == *p++)
            {
                if ('\0' == *p)
                {
                    return ret;
                }
                else
                {
                    std::cout << "hehe" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "hihi" << std::endl;
        }
    }
    return (char*)0;
}

int main()
{
    int i = 10;
    if (i++ && i == 11)
        std::cout << "test" << std::endl;
    const char* a = "abcdefgbcdknn";
    const char* b = "def";
    std::cout << my_strcpy(a, b) << std::endl;

    b = "bcdk";
    std::cout << my_strcpy(a, b) << std::endl;
    getchar();
    return 0;
}
