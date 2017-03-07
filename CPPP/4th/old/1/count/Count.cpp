#include <iostream>
int main()
{
    // same code as before
    // prompt user for number range to print
    std::cout << "Enter two numbers: " << std::endl;
    int v1, v2, lower, upper;
    std::cin >> v1 >> v2;
    // use smaller value for lower bound, larger for upper
    if (v1 <= v2)
    {
        lower = v1;
        upper = v2;
    } 
    else
    {
        lower = v2;
        upper = v1;
    }
    // sum values from lower up to and including upper
    int sum = 0;
    int val = lower;
    while (val <= upper) 
    {
        sum += val;  // sum = sum + val
        ++val;       // increment val (val = val + 1)
    }
    std::cout << "Sum of " << lower << " to " << upper
        << " inclusive is " << sum << std::endl;
    return 0;
}
