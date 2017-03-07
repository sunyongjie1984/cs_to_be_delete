#include <iostream>
#include <stdio.h>

int my_sum(const int* const p, unsigned int const n, unsigned int& begin, unsigned int& end)
{
    int max = 0;
    int sum = 0;

    int sum_all_minus = 0x80000000;

/*
    std::cout << "sum_all_minus: " << sum_all_minus << std::endl;
    int kkk = sum_all_minus - 1;
    std::cout << "kkk: " << kkk << std::endl;

    if (kkk == 0x7FFFFFFF)
        std::cout << "hello wolrd" << std::endl;
*/

    unsigned int b = 0;
    unsigned int e = 0;
    unsigned int b_e_all_minus = 0;
    bool flag = true;

    for (unsigned int i = 0; i < n; ++i)
    {
        if (p[i] >= 0)
        {
            flag = false;
        }
        else
        {
            if (sum_all_minus < p[i])
            {
                sum_all_minus = p[i];
                b_e_all_minus = i;
            }
            else
            {

            }
        }

        sum += p[i];
        if (sum < 0)
        {
            sum = 0;
            b = i + 1;
            e = i + 1;
        }
        else
        {
            if (sum > max)
            {
                max = sum;
                begin = b;
                end = e = i;
            }
            else
            {

            }
        }
    }
    if (flag)
    {
        begin = end = b_e_all_minus;
        return sum_all_minus;
    }
    else
    {
        return max;
    }
}

int main()
{
    std::cout << (8 == sizeof(int*) ? "64 bit program" : "32 bit program")  << std::endl;

    unsigned int number_of_array;
    std::cout << "where come to max sum array, please input how many integers this array has?" << std::endl;
    std::cin >> number_of_array;

    int* p_array = new int [ number_of_array * sizeof(int)];
    std::cout << "please input these integers like this 1 -2 3 10 -4 7 2 -5 and end with enter key" << std::endl;
    for (unsigned int i = 0; i < number_of_array; i++)
    {
        std::cin >> p_array[i];
    }

    std::cout << "the array you input is :" << std::endl;
    for (unsigned int i = 0; i < number_of_array; i++)
    {
        std::cout << p_array[i] << " ";
    }
    std::cout << std::endl;

    unsigned int i;
    unsigned int j;
    std::cout << "max sum of sub array is: " << std::endl;
    std::cout << my_sum(p_array, number_of_array, i, j) << std::endl;
    std::cout << "the sub array is: " << std::endl;
    for (unsigned int m = i; m <= j; m++)
    {
        std::cout << p_array[m] << " ";
    }
    std::cout << std::endl;

    delete p_array;
    p_array = nullptr;
    getchar();
    getchar();
    return 0;
}
