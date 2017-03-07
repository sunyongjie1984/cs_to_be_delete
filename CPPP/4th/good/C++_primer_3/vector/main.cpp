#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::string;
using std::vector;

int main()
{
    vector<int> ivec;
    for (vector<int>::size_type ix = 0; ix != 10; ix++)
    {
        //cout << ix << endl;
        ivec.push_back(ix);
    }

    for (vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter)
    {
        std::cout << *iter << std::endl;
        *iter = 20;
    }
    for (vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter)
    {
        std::cout << *iter << std::endl;
    }
    return 0;
}
