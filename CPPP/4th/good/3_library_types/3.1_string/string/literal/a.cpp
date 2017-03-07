#include <iostream>
int main()
{
    char ca1[] = { 'c', '+', '+' };       // no null, not C-style string
    char ca2[] = { 'c', '+', '+', '\0' }; // explicit null
    char ca3[] = "c++";     // null terminator added automatically
    const char* cp = "c++"; // null terminator added autoatically
    char* cp1 = ca1;        // points to first element of a array but not c-style string
    char* cp2 = ca2;
    return 0;
}
