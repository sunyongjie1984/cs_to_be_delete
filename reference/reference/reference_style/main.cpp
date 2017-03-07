int main()
{
    int a = 10;
    int const b = 20;
    int const& c = b;

    int* p = &a;
    const int* p2 = &b;

    const int* const p3 = &b;

    return 0;
}