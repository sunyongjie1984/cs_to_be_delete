#include <vector>
#include <functional>
void TestPtrFun();
void TestMemFun();
class StoreVals   
{
    int val;
public:
    StoreVals() { val = 0; }
    StoreVals(int j) { val = j; }
    
    bool display() { cout << val << " "; return true; }
    int squareval() { val *= val; return val; }
    int lessconst(int k) {val -= k; return val; }
};



void TestAdaptors()
{    
    //TestPtrFun();
    TestMemFun();
}
void TestMemFun()
{
    vector<StoreVals *> v1;
    
    StoreVals sv1(5);
    v1.push_back(&sv1);
    StoreVals sv2(10);
    v1.push_back(&sv2);
    StoreVals sv3(15);
    v1.push_back(&sv3);
    StoreVals sv4(20);
    v1.push_back(&sv4);
    StoreVals sv5(25);
    v1.push_back(&sv5);
    
    cout << "The original values stored are: " ;
    for_each(v1.begin(), v1.end(), mem_fun<bool, StoreVals>(&StoreVals::display));
    cout << endl;
    
    // Use of mem_fun calling member function through a pointer
    // square each value in the vector using squareval ()
    for_each(v1.begin(), v1.end(), mem_fun<int, StoreVals>(&StoreVals::squareval));   
    cout << "The squared values are: " ;
    for_each(v1.begin(), v1.end(), mem_fun<bool, StoreVals>(&StoreVals::display));
    cout << endl;
    
    // Use of mem_fun1 calling member function through a pointer
    // subtract 5 from each value in the vector using lessconst ()
    for_each(v1.begin(), v1.end(), 
        bind2nd (mem_fun1<int, StoreVals,int>(&StoreVals::lessconst), 5));   
    cout << "The squared values less 5 are: " ;
    for_each(v1.begin(), v1.end(), mem_fun<bool, StoreVals>(&StoreVals::display));
    cout << endl;
}
void TestPtrFun()
{
    using namespace std; 
    vector <char*> v1;
    vector <char*>::iterator Iter1, RIter;
    
    v1.push_back ( "Open" );
    v1.push_back ( "up" );
    v1.push_back ( "the" );
    v1.push_back ( "pearly" );
    v1.push_back ( "gates" );
    
    cout << "Original sequence contains: " ;
    for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
        cout << *Iter1 << " ";
    cout << endl;
    
    // To search the sequence for "pearly"
    // use a pointer_to_function conversion
    RIter = find_if( v1.begin( ), v1.end( ),
        not1 ( bind2nd (ptr_fun ( strcmp ), "pearly" ) ) );
    
    if ( RIter != v1.end( ) )  
    {
        cout << "The search for 'pearly' was successful.\n";
        cout << "The next character string is: " 
            << *++RIter << "." << endl;
    }
}