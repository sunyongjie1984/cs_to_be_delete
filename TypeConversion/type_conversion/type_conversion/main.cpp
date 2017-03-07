#include <iostream>
#include <algorithm>
int main()
{
    std::string a = "prsetEntryId=15425,prsetId=1,imsSharedServiceDataId=1,managedElementId=HSS1";
    std::string::size_type i = a.find_first_of('=');
    std::string::size_type j = a.find_first_of(',');
    a = a.substr(i + 1, j - i);
    int n = atoi(a.c_str());
    std::cout << n << std::endl;
    return 0;
}