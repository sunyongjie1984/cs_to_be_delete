// this project is about define array
// sunyongjie copy from c++ primer

#include <cstddef>    // for the definition of size_t
using std::size_t;

const size_t i = 100;
int iaa[i]; // initialized 0
int main()
{
    const size_t array_size = 10;
    int ia[array_size]; // 10 ints, elements are uninitialized
    
    // loop through array, assigning value of its index to each element
    for (size_t ix = 0; ix != array_size; ++ix)
          ia[ix] = ix;

    return 0;
}
