#include <iostream>
#include <vector>
#include <stdio.h>

int my_sum(const std::vector<int>& v_int, std::vector<int>::const_iterator& begin, std::vector<int>::const_iterator& end)
{
    int max = 0;
    int sum = 0;

    int sum_all_minus = 0x80000000;

    std::vector<int>::const_iterator b = v_int.begin();
    std::vector<int>::const_iterator e = v_int.begin();
    std::vector<int>::const_iterator b_e_all_minus = v_int.begin();
    bool flag = true;

    for (std::vector<int>::const_iterator iter = v_int.begin(); iter != v_int.end(); ++iter)
    {
        if (flag && *iter >= 0)
        {
            flag = false;
        }
        else
        {
            if (sum_all_minus < *iter)
            {
                sum_all_minus = *iter;
                b_e_all_minus = iter;
            }
            else
            {

            }
        }

        sum += *iter;
        if (sum < 0)
        {
            sum = 0;
            b = iter + 1;
            e = iter + 1;
        }
        else
        {
            if (sum > max)
            {
                max = sum;
                begin = b;
                end = e = iter;
                ++end;
            }
            else
            {

            }
        }
    }
    if (flag)
    {
        begin = end = b_e_all_minus;
        ++end;
        return sum_all_minus;
    }
    else
    {
        return max;
    }
}

int main()
{
    std::cout << "this program is a " << (8 == sizeof(int*) ? "64 bit program" : "32 bit program")  << std::endl;

    unsigned int number_of_array;
    std::cout << "where come to max sum array, please input how many integers this array has?" << std::endl;
    std::cin >> number_of_array;
    std::cout << "please input these integers like this 1 -2 3 10 -4 7 2 -5 and end with enter key" << std::endl;

    int tmp_input;    
    std::vector<int> v_int;
    for (unsigned int i = 0; i < number_of_array; i++)
    {
        std::cin >> tmp_input;
        v_int.push_back(tmp_input);
    }
    std::cout << "the array you input is :" << std::endl;
    for (std::vector<int>::const_iterator iter = v_int.begin(); iter != v_int.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "max sum of sub array is: " << std::endl;
    std::vector<int>::iterator begin_iter;
    std::vector<int>::iterator end_iter;
    std::cout << my_sum(v_int, begin_iter, end_iter) << std::endl;
    std::cout << "the sub array is: " << std::endl;
    for (std::vector<int>::const_iterator iter = begin_iter; iter != end_iter; ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    getchar();
    getchar();
    return 0;
}
