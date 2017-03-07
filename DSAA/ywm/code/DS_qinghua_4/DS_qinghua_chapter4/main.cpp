#include <iostream>

// ¶¨Î»º¯Êý
int Index(char* s, char* t, int pos) 
{
    int i = pos;
    int j = 1;
    while (i <= s[0] && j <= t[0])
    {
        if (s[i] == t[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i -j + 2;
            j = 1;
        }
    }
    if (j > t[0])
    {
        return i - t[0];
    }
    else
    {
        return 0;
    }
}

int main()
{
    char a[10] = { 9, 'c', 'i', 'a', 'i', 'a', 'b', 'i', 'n', 'a' };
    char b[3] = { 2, 'i', 'n' };
    std::cout << Index(a, b, 1) << std::endl;
    return 0;
}