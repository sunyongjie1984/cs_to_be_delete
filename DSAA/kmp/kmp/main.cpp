#include <iostream>

int ViolentMatch(char* s, char* p)  
{  
    int sLen = strlen(s);  
    int pLen = strlen(p);  

    int i = 0;  
    int j = 0;  
    while (i < sLen && j < pLen)  
    {  
        if (s[i] == p[j])  
        {  
            //①如果当前字符匹配成功（即S[i] == P[j]），则i++，j++      
            i++;  
            j++;  
        }  
        else  
        {  
            //②如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0      
            i = i - j + 1;  
            j = 0;  
        }  
    }  
    //匹配成功，返回模式串p在文本串s中的位置，否则返回-1  
    if (j == pLen)  
        return i - j;  
    else  
        return -1;  
}  

int main()
{
    char * p = "abcabcdefff";
    char * q = "abcd";
    int i = ViolentMatch(p, q);
    std::cout << i << std::endl;
    getchar();
    return 0;
}