//////////////////////////////////////////////////////////////////////
//
// Compile options needed: /GX
//
// Pushpop.cpp: Illustrates how to use the push and pop member
//              functions of the vector container.
//
// Functions:
//
//    vector::push_back - Appends (inserts) an element to the end of a
//                        vector, allocating memory for it if necessary.
//
//    vector::pop_back -  Erases the last element of the vector.
//
//    vector::begin - Returns an iterator to start traversal of the vector.
//
//    vector::end - Returns an iterator for the last element of the vector.
//
//    vector::iterator - Traverses the vector.
//
//////////////////////////////////////////////////////////////////////

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <iostream>
#include <vector>

using namespace std ;

typedef vector<int> INTVECTOR;

void main()
{
    // Dynamically allocated vector begins with 0 elements.
    INTVECTOR theVector;

    // Iterator is used to loop through the vector.
    INTVECTOR::iterator theIterator;

    // Add one element to the end of the vector, an int with the value 42.
    // Allocate memory if necessary.
    theVector.push_back(42) ;

    // Add two more elements to the end of the vector.
    // theVector will contain [ 42, 1, 109 ].
    theVector.push_back(1) ;
    theVector.push_back(109) ;

    // Erase last element in vector.
    theVector.pop_back();

    // Print contents of theVector. Shows [ 42, 1 ]
    cout << "theVector [ " ;
    for (theIterator = theVector.begin(); theIterator != theVector.end();
         theIterator++)
    {
        cout << *theIterator;
        if (theIterator != theVector.end()-1) cout << ", ";
                                             
    }
    cout << " ]" << endl ;
}
