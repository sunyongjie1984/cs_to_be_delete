#include "any_ptr.h"
#include <cassert>
#include <algorithm>

// Example code to show any_ptr in action.

int main(int /*argc*/, char * /*argv*/[])
{
    // Variables of different types.
    int   intVar   = 10;
    float floatVar = 20.5f;

    // any_ptrs which point to the variables of different types.
    any_ptr ptr1 = &intVar;
    any_ptr ptr2 = &floatVar;

    // Raw pointers which are assigned from the any_ptrs.
    const int *pInt   = ptr1; // Assigning non-const to const of the same type is valid, but not vice versa.
    float     *pFloat = ptr2;
    // The raw pointers will be valid because any_ptrs of their corresponding type are assigned to them.

    // The raw pointers should point to the correct variables.
    assert( pInt   == &intVar );
    assert( pFloat == &floatVar );

    // Swap the any_ptrs.
    std::swap( ptr1, ptr2 );
    // ptr1 will now point to floatVar; ptr2 will now point to intVar.

    // Reassign the raw pointers.
    pInt   = ptr1;
    pFloat = ptr2;
    // The raw pointers will be null because the any_ptrs assigned to them are not of their corresponding type.

    // The raw pointers should be null.
    assert( pInt   == 0 );
    assert( pFloat == 0 );

    return 0;
}
