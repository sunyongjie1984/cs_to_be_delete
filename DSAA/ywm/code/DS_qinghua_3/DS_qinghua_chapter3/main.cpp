#include <iostream>

#include <stdlib.h>   // For _MAX_PATH definition
#include <stdio.h>
#include <malloc.h>
#include "SqStack.h"

void print_stack(SqStack& s)
{
    SElemType* base =s.base;
    while (s.top != base)
    {
        std::cout << *base;
        base++;
    }
    std::cout << std::endl;
}

Status InitStack(SqStack& s)
{
    s.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
    {
        exit(OVERFLOW);
    }
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack s, SElemType& e)
{
    if (s.top == s.base)
    {
        return ERROR;
    }
    e = *(s.top - 1);
    return OK;
}

Status Push(SqStack& s, SElemType e)
{
    if ((s.top - s.base) >= s.stacksize)
    {
        s.base = (SElemType*)realloc(s.base, (s.stacksize + STACKINCREMENT) * 
            sizeof(SElemType));
        if (!s.base)
        {
            exit(OVERFLOW);
        }
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    *s.top++ = e;
    return OK;
}

Status Pop(SqStack& s, SElemType& e)
{
    if (s.top == s.base)
    {
        return ERROR;
    }
    e = *(--s.top);
    return OK;
}

Status StackEmpty(SqStack s)
{
    if (s.base == s.top)
    {
        return TRUE;
    }
    return FALSE;
}

Status clear_stack(SqStack& s)
{
    s.top = s.base;
    return OK;
}

void conversion()
{
    SqStack sq_stack;
    InitStack(sq_stack);
    int N;
    scanf("%d", &N);
    while(N)
    {
        Push(sq_stack, N % 8);
        N = N / 8;
    }
    while (!StackEmpty(sq_stack))
    {
        SElemType e;
        Pop(sq_stack, e);
        printf("%d", e);
    }
}

void line_edit()
{
    SqStack sq_stack;
    InitStack(sq_stack);
    char ch = getchar();
    while (EOF != ch)
    {
        while (EOF != ch && ch != '\n')
        {
            SElemType c;
            switch (ch)
            {
            case '#' :
                Pop(sq_stack, c);
                break;
            case '@' :
                clear_stack(sq_stack);
                break;
            default:
                Push(sq_stack, ch);
            }
            ch = getchar();
        }
        print_stack(sq_stack);
    }
    clear_stack(sq_stack);
    if (EOF != ch)
    {
        ch = getchar();
    }
}

unsigned int fibonacci(const unsigned int n)
{
    if (0 == n)
    {
        return 0;
    }
    else if (1 == n)
    {
        return 1;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main()
{
    //for (int i = 0; i < 10; i++)
    //{
    //    std::cout << fibonacci(i) << std::endl;
    //}

    //SqStack sq_stack;
    //InitStack(sq_stack);
    //Push(sq_stack, 3);
    //int a;
    //GetTop(sq_stack, a);
    //std::cout << a << std::endl;
    //Push(sq_stack, 4);
    //GetTop(sq_stack, a);
    //std::cout << a << std::endl;

    //Pop(sq_stack, a);
    //GetTop(sq_stack, a);
    //std::cout << a << std::endl;

    line_edit();
    //conversion();
    return 0;
}
