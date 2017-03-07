//#include "../algs_preamble.h"
#include "../Sales_item.h"
#include <iterator>
using namespace std;

int main() 
{
    istream_iterator<Sales_item> item_iter(cin), eof;
    Sales_item sum;     // initially empty Sales_item
    sum = *item_iter++; // read first transaction into sum and get next record

    while (item_iter != eof) { // 这个也可以用ctrl + z退出
        if (item_iter->same_isbn(sum))
            sum = sum + *item_iter;
        else {
            cout << sum << endl;
            sum = *item_iter;
        }
        ++item_iter;  // read next transaction
    }
    cout << sum << endl;  // remember to print last set of records
    return 0;
}
