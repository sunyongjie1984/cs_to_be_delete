/*! @file mate.hpp
 *  @brief Writing an exception safe code in generic way.
 *
 *  @author   JaeWook Choi (zzzz.ooo "at' gmail.com)
 *  @version  1.02
 *  @date 12.12.2006
 *  @warning  This software is provided "as is" without express or implied warranty.
 *  @warning  Use it at your own risk!
 */
#if !defined(__MATE_HPP__INCLUDED__)
#define __MATE_HPP__INCLUDED__

/*!  @page mate_introduction Introduction.
 *
 * Here is an example of a traditional scenario in our daily programming as shown below.
 * We are prone to forget to call some clean up codes when the function has multiple return
 * paths or an exception is thrown in the middle of very complicated constructs. 
 *
 *  @code
 void test01()
 {
  char const * lpszFilePath = "c:\\test.dat";

  HANDLE hFile( ::CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ) );

  if( INVALID_HANDLE_VALUE != hFile )
  {

    if( 100 > ::GetFileSize( hFile, NULL ) )
      throw "File size too small!";

    ::CloseHandle( hFile );
  }

  ::DeleteFile( lpszFilePath );
 }
 *  @endcode
 *
 *  @c boost::shared_ptr can be used to transform the code snippet above in exception safe way. It
 *  purely depends on the ability of the @c boost::shared_ptr that it allows for user to provide
 *  a custom deleter function object. See more details from 
 *  <a href="http://www.codeproject.com/vcpp/stl/boostsp_handleref.asp">here</a>.
 *
 *  @code
 #define BOOST_BIND_ENABLE_STDCALL
 #include <boost/bind.hpp>
 #include <boost/shared_ptr.hpp>

 void test02()
 {
   boost::shared_ptr<char const> spFilePath( "c:\\test.dat", &::DeleteFile );

   boost::shared_ptr<void> spFile(
    ::CreateFile( spFilePath.get(), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ),
    &::CloseHandle ); // Custom deleter.

   if( INVALID_HANDLE_VALUE != spFile.get() )
   {

     if( 100 > ::GetFileSize( spFile.get(), NULL ) )
       throw "File size too small!";
   }
 }
 *  @endcode
 *
 *  Writing a code in the exception safe way at object level doesn't require the fancy reference counting feature
 *  of @c boost::shared_ptr, but only requires that of the custom deleter function object. Speaking accurately,
 *  what we need is an ability to call an arbitrary custom function object in the destructor of our class variable
 *  when it goes out of scope. 
 *  By extracting and combining merits of the existing implementations such as @c boost::shared_ptr, @c ScopeGuard
 *  and etc., here I will like to introduce a small am::mate utility class.
 *
 *  @code
 #include "mate.h"

 void test03()
 {
   am::mate<char const *> lpszFilePath( "c:\\test.dat", &::DeleteFile );

   am::mate<HANDLE> hFile(
    ::CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ), // Host function.
    &::CloseHandle,                                                             // Mate function.
    (HANDLE)INVALID_HANDLE_VALUE != am::lambda::_1 ); // Mates the function only if the condition asserts true.

   // Treats am::mate<HANDLE> as if it is a HANDLE.
   if( INVALID_HANDLE_VALUE != hFile )
   {

     if( 100 > ::GetFileSize( hFile, NULL ) )
       throw "File size too small";
   }
 }
 *  @endcode
 *
 *  There are several benefits of using am::mate over the existing implementations.
 *
 *    -# More intuitive and well defined interfaces.
 *    -# Accepts any unary custom mate function object which takes the return of the host function as its argument.
 *    -# Not like @c boost::shared_ptr is limited only for the pointer type, am::mate works with any data type.
 *        i.e. intergral type, floating point type, pointer type and even reference type.
 *    -# Implicit conversion to the return type of the host function which cast an illusion that makes an 
 *        am::mate instance as if it is a stored variable of the return type of the host function.
 *    -# Easy, convenient and compiler-warning-free MATE() macro definitions to create
 *        an anonymous am::mate variable.
 *    -# Mates functions with a condition.
 *    -# Provides a simple set of boolean lambda operations to support composing an anonymous function object for the condition.
 *    -# am::mate<void> specialization when mating a mate function object without any host function call.
 *    -# Well standard compliant and portable. Tested on VC6, VC71, VC80, gcc3.4.2. 
 *    -# No dependency on boost library but works nicely with it.
 *    -# Provide am::ptr_fun, am::bind1st and am::bind2nd helper template functions that work well for any
 *        calling convention (including @c __stdcall).
 *    -# am::lambda::bind up to 3 arguments for both free function and member function are provided.
 *
 *  @ref mate_contents "[Contents]"
 */

/*! @page mate_basic_usage Basic usage.
 *
 *  @section mate_bu_s1 Mating a host function call with a mate function.
 *
 *  Mating a host function call with a mate function is easy. Provide the host function as the first argument
 *  (by calling it) and the mate function as the second argument of the constructor of the am::mate variable.
 *  Specifies the return type of the host function explicitly as the template argument of the am::mate when declaring it.
 *
 *  Use MATE() macro to create an anonymous am::mate variable when you are not concerning about using am::mate variable.
 *
 *  @code
 int prefix(int n) { return n + 100; }
 void suffix(int n) { n -= 100; }

 void test04()
 {
   am::mate<int> nNumber( prefix(123), &suffix );
   assert( 23 == nNumber );

   int nNumber2 = nNumber; // Compile OK!

 #if 0
   nNumber = nNumber2; // Compile error! mate is non-assignable.
   nNumber = 52;       // Compile error! mate is non-assignable.
 #endif

  {
    MATE( prefix( 333 ), &suffix );

  } // calls suffix( 233 ) here

 } // calls suffix( 23 ) here on exit.
 *  @endcode
 *
 *  An am::mate variable can be treated as a variable of the data type of which is specified as
 *  the template parameter when the am::mate variable is declared. This is due to the implict
 *  conversion operator to the data type. But also be aware that it is read-only access, which
 *  means it behaves like a const variable. i.e. an <tt>am::mate<int></tt> variable can be treated
 *  as a <tt>const int</tt> variable.
 *
 *  @section mate_bu_s2 Composing a mate fuction object.
 *
 *  Mate function object will take the return of the host function as its only input argument
 *  (it should be an unary function object) when it is called. You can use any known techniques
 *  to compose and provide an unary custom function object when constructing am::mate variable.
 *
 *  @code
 struct MyReleaseDC
 {
   HWND hwnd_;
   MyReleaseDC(HWND hwnd) : hwnd_( hwnd ) { }
   int operator ()(HDC hdc) const { return ::ReleaseDC( hwnd_, hdc ); }

 };  // struct MyReleaseDC

 struct MySelectObject
 {
   HDC hdc_;
   MySelectObject(HDC hdc) : hdc_( hdc ) { }
   HGDIOBJ operator ()(HGDIOBJ hgdiobj) const { return ::SelectObject( hdc_, hgdiobj ); }

 };  // struct MySelectObject

 void test05(HWND hwnd)
 {
   am::mate<HDC> hdc( ::GetWindowDC( hwnd ), MyReleaseDC( hwnd ) );

   MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), MySelectObject( hdc ) );
 } 
 *  @endcode
 *
 *  @code
 #define BOOST_BIND_ENABLE_STDCALL
 #include <boost/bind.hpp>

 void test06(HWND hwnd)
 {
   am::mate<HDC> hdc( ::GetWindowDC( hwnd ), boost::bind( &::ReleaseDC, hwnd, _1 ) );

   MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), boost::bind( &::SelectObject, hdc, _1 ) );
 }
 *  @endcode
 *
 *  @code
 void test07(HWND hwnd)
 {
   am::mate<HDC> hdc( ::GetWindowDC( hwnd ), am::bind1st( &::ReleaseDC, hwnd ) );

   MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), am::bind1st( &::SelectObject, hdc ) );
 }
 *  @endcode
 *
 *  @code
 #define AM_BIND_ENABLE_STDCALL
 #include "lambda.hpp"

 void test08(HWND hwnd)
 {
   am::mate<HDC> hdc( ::GetWindowDC( hwnd ), am::lambda::bind( &::ReleaseDC, hwnd, am::lambda::_1 ) );

   MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ),
     am::lambda::bind( &::SelectObject, hdc, am::lambda::_1 ) );
 }
 *  @endcode
 *
 *  @section mate_bu_s3 Mating with a condition.
 *
 *  Sometime there are cases in which the host function call might be failed and returns the error code
 *  as a result. In such cases, the mate function should not be called. Checking the error of the host
 *  function call can be easily performed as am::mate variable can be treated as a const variable of the
 *  return type of the host function call. Use dismate_mate() member function to dismiss the mate
 *  function call.
 *
 *  @code
 void test09()
 {
   am::mate<HANDLE> hEvent( ::CreateEvent( NULL, FALSE, FALSE, NULL ), &::CloseHandle );
   if( hEvent == NULL )
     hEvent.dismiss_mate();

 }
 *  @endcode
 *
 *  However this approach can not be used with MATE() macro. Use MATE_IF() macro instead and provides
 *  a unary predicate as the third input argument for a condition. MATE_IF() utilizes am::mate's another
 *  constructor which takes an unary predicate as its third input argument. If a condition is provided,
 *  the mate function will be called, when it goes out of scope, only if the provided unary predicate
 *  asserts true. 
 *
 *  The unary predicate takes the return of the host function as its only input argument as well. Like
 *  mate function object, you can compose a unary predicate in any techniques you know of. 
 *
 *  @code
 struct EventCreated
 {
   bool operator ()(HANDLE hevent) const { return NULL != hevent; }

 };  // struct EventCreated

 void test10()
 {
   MATE_IF( ::CreateEvent( NULL, FALSE, FALSE, NULL ), &::CloseHandle,  EventCreated() );

 }
 *  @endcode
 *
 *  There is one advantage of using am::mate with a condition than without a condition. When a mate
 *  function object is stored into the am::mate variable internally, the heap memory allocation is
 *  occurred. But if the condition does not hold, nor will the heap memory allocation occur since the
 *  mate function will not be called. 
 *
 *  @code
 void test11()
 {
   am::mate<HANDLE> hEvent( ::CreateEvent( NULL, FALSE, FALSE, NULL ),
     &::CloseHandle, (HANDLE)NULL != am::lambda::_1 );

 }
 *  @endcode
 *
 *  @section mate_bu_s4 am::mate<void> specialization.
 *
 *  If the mate function does not concern about the return of the host function which is given as
 *  its input argument, you can write a mate fuction object which takes the return of the host
 *  function, but then simply ignores it. 
 *
 *  @code
 #define RESOURCE_ACQUSITION_SUCCESS 100
 #define RESOURCE_ACQUSITION_FAIL    200

 int AcquireResource(HANDLE hres) { return RESOURCE_ACQUSITION_SUCCESS; }
 void ReleaseResource(HANDLE hres) { }

 struct IgnoreReturnAndReleaseResource
 {
   HANDLE hres_;
   IgnoreReturnAndReleaseResource(HANDLE hres) : hres_( hres ) { }
   void operator ()(int) const { ReleaseResource( hres_ ); }

 };  // struct IgnoreReturnAndReleaseResource

 void test12(HANDLE hres)
 {
   am::mate<int> nResult( AcquireResource( hres ),
     IgnoreReturnAndReleaseResource( hres ), RESOURCE_ACQUSITION_SUCCESS == am::lambda::_1  );

 } // Calls ReleaseResource( hres ) on exit if AcquireResource( hres ) returns RESOURCE_ACQUSITION_SUCCESS
 *  @endcode
 *
 *  If you use @c boost::bind, @c boost::lambda::bind or am::lambda::bind to compose a function object
 *  in the way that all of its input arguments are bound. It will automatically create an unary
 *  function object that simply ignores the return of the host function, and when it is called,
 *  it will call the mate function only with all those bound input arguments. 
 *
 *  @code
 #define RESOURCE_ACQUSITION_SUCCESS 100
 #define RESOURCE_ACQUSITION_FAIL    200

 int AcquireResource(HANDLE hres) { return RESOURCE_ACQUSITION_SUCCESS; }
 void ReleaseResource(HANDLE hres) { }

 void test13(HANDLE hres)
 {
   am::mate<int> nResult( AcquireResource( hres ),
     am::lambda::bind( &ReleaseResource, hres ), RESOURCE_ACQUSITION_SUCCESS == am::lambda::_1  );

 }
 *  @endcode
 *
 *  If the host function is a function with void return or even we don't have a host function
 *  to call at all, am::mate<void> specialization and MATE_VOID() macro play a neat role in
 *  such cases as am::mate<void> class' constructors do not take the return of host function
 *  as their first argument. 
 *
 *  @code
 void AcquireResourceEx(HANDLE hres) { }
 void ReleaseResourceEx(HANDLE hres) { }
 void Cleanup() { }

 void test14(HANDLE hres, int option)
 {
   am::mate<void> cleanup_on_exit( &Cleanup );

   if( 0 == option )
   {
     AcquireResourceEx( hres );
     MATE_VOID( am::lambda::bind( &ReleaseResourceEx, hres ) );

   }
   else if( 1 == option )
   {
     AcquireResourceEx( hres );
     MATE_VOID_IF( am::lambda::bind( &ReleaseResourceEx, hres ), am::condition( NULL != hres ) );

   }
   else if( 2 == option )
   {
     am::mate<void> dummy( ( AcquireResourceEx( hres ), am::lambda::bind( &ReleaseResourceEx, hres ) ) );

   }
   else if( 3 == option )
   {
     am::mate<void> dummy( ( AcquireResourceEx( hres ), am::lambda::bind( &ReleaseResourceEx, hres ) ),
       am::condition( NULL != hres ) );

   }
   else
   {
     MATE_VOID( ( AcquireResourceEx( hres ), am::lambda::bind( &ReleaseResourceEx, hres ) ) );

   }
 }
 * @endcode
 *
 *  It is possible to use comma (,) operator between the host function call and the mate function
 *  and then wrap them with the nested parenthesis to make it look and feel the same style as
 *  non-void am::mate.
 *
 *  @ref mate_contents "[Contents]"
 */

/*! @page mate_utility_classes Utility classes and their helper template functions.
 *
 *  @section mate_uc_s1 Supporting parameter by reference: am::ref and am::cref.
 *
 *  Specifies the reference type as the template argument of the am::mate class
 * if you want to provide the return of the host function as a reference to the mate function. 
 *
 *  @code
 int & Increase(int & x) { return ++x; }
 void Decrease(int & x) { --x; }

 void test15(int & refCount)
 {
   am::mate<int &> decreseOnExit( Increase( refCount ), &Decrease );

 } //  Calls Decrease( refCount ) on exit.
 *  @endcode
 *
 *  By default, a template parameter is passed by value, not by reference. Thus if a
 *  mate function provided wants to take the return of the host function as a reference
 *  and MATE() macro definition is used, the specified mate function will be called with
 *  the reference to the "copy" of the argument, not with the reference to argument itself,
 *  when it goes out of scope since template parameter is passed by value. Use am::ref or
 *  am::cref function to specify explicitly to use am::ref_holder class transforms a
 *  reference into a value.
 *
 *  @code
 void test16(int & refCount)
 {
   MATE( am::ref( Increase( refCount ) ), &Decrease );

 }  //  Calls Decrease( refCount ) on exit.
 * @endcode
 *
 *  @subsection mate_uc_s2 Free function pointer: am::ptr_fun.
 *
 *  am::ptr_fun is very similar to @c std::ptr_fun that it is used to convert unary and binary
 *  function pointers, respectively, into unary and binary adaptable function objects. However
 *  they are different in that am::ptr_fun can convert the function pointers of any calling
 *  covention while @c std::ptr_fun can only convert @c __cdecl function pointers. In general, use
 *  @c std::ptr_fun and ignore am::ptr_fun if you don't concern about calling convention. 
 *
 *  am::ptr_fun and other helper template functions of am::mate are designed to collaborate
 *  only with am::mate and its other sibling helper template functions so do not mix use it
 *  with helper template functions from STL (such as @c std::ptr_fun, @c std::bind1st, @c std::bind2nd
 *  and so on.) 
 *
 *  You can also use am::ptr_fun to resolve overloaded functions manually since the template
 *  rules are very strict for type checking and it is not supposed to resolve the resolution
 *  of the overloaded functions automatically. 
 *
 *  @code
 // Overloaded functions
 void foo(char const *, int) { }
 void foo(int) { }
 void __stdcall foo(char const *) { }

 void __stdcall bar(char const *) { }

 void test17()
 {
   // Provides function template parameter explicitly to resolve overloaded functions.
   MATE( "Hello foo!", am::ptr_fun<void (_stdcall *)(char const *)>( &foo ) );
   MATE( "Hello foo!", am::bind2nd( am::ptr_fun<void (*)(char const *, int)>( &foo ), 123 ) );

   // am::pointer_to_function is not necessary,
   // unless otherwise resolving overloaded functions is required.
   MATE( "Hello bar!", am::ptr_fun( &bar ) );
   MATE( "Hello bar!", &bar );
 }
 *  @endcode
 *
 *  Be aware that the template parameter is provided as a single function pointer not as
 *  individual types from the function signature like STL does. It gives am::ptr_fun and its
 *  sibling helper template functions the ability to resolve overloaded functions better as
 *  well as to work well with any calling conventions but it also prevents from being able to
 *  define the public interfaces such as @c first_argument_type, @c second_argument_type and @c result_type.
 *  Actually @c result_type is always fixed and defined as void internally since am::mate does not
 *  utilize the @c result_type under the hood. 
 *
 *  <b>- NOTE -</b>
 *
 *  <em>Do <b>NOT</b> use am::ptr_fun, am::bind1st, am::bind2nd to create a function object which
 *  wraps a free function with the calling convention other than @c __cdecl under none-MSVC
 *  environment. Calling convention is subject to be a platform specific therefore it does not
 *  work well for none-MSVC environment, especially when function pointer is passed as a template
 *  parameter. Use am::lambda::bind instead.</em>
 *
 *  @subsection mate_uc_s3 Bind the 1st or the 2nd argument of the binary function: am::bind1st and am::bind2nd.
 *
 *  am::bind1st and am::bind2nd are similar to @c std::bind1st and @c std::bind2nd respectively but they
 *  resolve overloaded functions better as well as work for any calling conventions at the expense
 *  of not having public interface @c first_argument_type. The template parameter is also required to
 *  be provided as a single function pointer not as individual types from the function signature when
 *  resolving overloaded functions is needed. 
 *
 *  @code
 void foo(char const *, int) { }
 void __stdcall bar(char const *, int) { }  // __stdcall calling convention.

 void main()
 {
   // MATE( "Hello foo!", std::bind2nd( &foo, 123 ) ); // Compiles error!
   // MATE( "Hello bar!", std::bind2nd( &bar, 123 ) ); // Compiles error!
   MATE( "Hello foo!", am::bind2nd( &foo, 123 ) ); // Compiles OK!
   MATE( "Hello bar!", am::bind2nd( &bar, 123 ) ); // Compiles OK!
 }
 *  @endcode
 *
 *  @subsection mate_uc_s4 Miscellaneous.
 *
 *  am::condition can be used to convert a boolean expression into a null-nary or unary predicate.
 *
 *  @code
 void test19(bool cond)
 {
   assert( false == am::condition( 2 == 3 )() );
   assert( false == am::condition( 2 == 3 )( "123" ) );  // Input argument is simply ignored.

   // Use am::lambda::condition instead when composing a function object using am::lambda
   MATE_IF( ::CreateMutex(NULL, TRUE, NULL), &::ReleaseMutex,
     (HANDLE)NULL != am::lambda::_1 && am::lambda::condition( cond ) );
 } 
 *  @endcode
 *
 *  @ref mate_contents "[Contents]"
 */

/*! @page mate_use_lambda Use am::lambda to compose a function object.
 *
 *  @c boost::lambda library provide a very powerful ability to create an anonymous function
 *  object on the spot. Unfortunately it does not support some outdated compilers which are
 *  still widely being used. In such environment, you can consider to use am::lambda. 
 *
 *  am::lambda is a limited subset of @c boost::lambda which only supports the following operators.
 *
 *    - Logical NOT : !
 *    - Logical AND : &&
 *    - Logical OR  : ||
 *    - Equality operators : ==, !=
 *    - Relational operators : <, >, <=, >=
 *    - Address-of operator : &
 *    - Pointer-to-member operator : ->* (to access member data pointer, not member function pointer and read-only access)
 *
 *  The above lambda operators seems good enough to collaborate with am::mate and, most of all,
 *  it might work for those outdated compiler which @c boost::lambda does not support.
 *
 *  Also am::lambda::bind overloaded helper template functions are provided to support arguments
 *  binding similar to @c boost::lambda::bind.
 *
 *  @code
 #include "mate.hpp"
 #include "lambda.hpp"

 class Graph { };

 std::pair<bool, unsigned> AddVertex(Graph & g)
 {
   bool is_success = false;
   unsigned vertex_descriptor = 0;

   // Add a new vertex.

   // return Pair of boolean success flag and the new vertex descriptor if it
   // successfully added a new vertex.
   return std::make_pair( is_success, vertex_descriptor );
 }

 void RemoveVertex(unsigned vertex_descriptor, Graph & g)
 {
   // Remove the vertex of the specified descriptor.
 }

 void test20(Graph & g)
 {
   typedef std::pair<bool, unsigned> result_pair;

   // 1. Calls the host function AddVertex()
   // 2. Mates RemoveVertex() with the second of the resultant std::pair of the host function
   //    only if the first of the resultant std::pair of the host functio hold true.
   MATE_IF( AddVertex( g ),
     am::lambda::bind( &RemoveVertex, &am::lambda::_1->*&result_pair::second, g ), 
     &am::lambda::_1->*&result_pair::first );
  }
 *  @endcode
 *
 *  am::lambda::bind can resolve overloaded free functions (non-member functions) with
 *  @c __stdcall calling convention when AM_ENABLE_BIND_STDCALL is defined before
 *  including, directly or indirectly, "lambda.hpp". am::lambda::bind supports binding
 *  only up to 3 input arguments. 
 *
 *  @code
 #include "mate.hpp"

 #define AM_BIND_ENABLE_STDCALL
 #include "lambda.hpp"

 typedef std::map<int, RECT> RECT_MAP; // Rect id -> Rectangle
 typedef RECT_MAP::value_type MAP_VALUE;

 MAP_VALUE ModifyRectangle(MAP_VALUE map_value) { return map_value; }
 void UndoRectangle(int rect_id) { }

 void test21(RECT_MAP const & rect_map, POINT pt)
 {
   RECT_MAP::const_iterator it = rect_map.begin(), it_e = rect_map.end();
   for( ; it != it_e; ++it )
   {
     // 1. Calls the host function ModifyRectangle()
     // 2. Mates UndoRectangle() with the first of the iterating map value that
     //    host function returns, only if the rectangle is found to contain the
     //    specified point and the specified point is not the origin (0, 0).
     MATE_IF( ModifyRectangle( *it ),
       am::lambda::bind( &UndoRectangle, &am::lambda::_1->*&MAP_VALUE::first ),
       am::lambda::bind( &::PtInRect, &( &am::lambda::_1->*&MAP_VALUE::second ), pt ) &&
       am::lambda::condition( 0 != pt.x && 0 != pt.y ) );
   }
 }
 *  @endcode
 *
 *  am::lambda is completely independent on am::mate and vice-versa, thus both can be used separately.
 *
 *  @ref mate_contents "[Contents]"
 */

/*! @page mate_references References.
 *
 *    -# <a href="http://www.codeproject.com/cpp/AutoMate.asp">CAutoMate\<\>: a tiny utility class to run a mate function automatically in code block.</a>
 *    -# <a href="http://www.ddj.com/dept/cpp/184403758">Generic: Change the Way You Write Exception-Safe Code ?Forever.</a>
 *    -# <a href="http://www.codeproject.com/vcpp/stl/boostsp_handleref.asp">boost 2: shared_ptr wraps resource handles by peterchen.</a>
 *    -# <a href="http://boost.org/libs/smart_ptr/sp_techniques.html#on_block_exit">Using shared_ptr to execute code on block exit.</a>
 *
 *  @ref mate_contents "[Contents]"
 */

// --------------------------------------------------------------------------------
// Compiler configuration.
// --------------------------------------------------------------------------------
#if defined(_MSC_VER)
#if 1200 >= _MSC_VER
// --------------------------------------------------------------------------------
// VC6 or earlier.

// No solution for MS Visual C++ 6 or older for edit & continue, sigh~
// just do not use this macro more than once in a block scope,
// or use MATE_ macro definition instead.
#define AM_CAN_NOT_CREATE_UNIQUE_ANONYMOUS

#else
// --------------------------------------------------------------------------------
// VC7 or higher.

// Necessary for edit & continue in MS Visual C++ 7 or higher.
#define AM_CAN_CREATE_UNIQUE_COUNT_ANONYMOUS

#endif
#else
// --------------------------------------------------------------------------------
// Non-VC

#endif

//! namespace of <b>a</b>uto <b>m</b>ate.
/*! Defines mate class, utility classes and their helper template functions.
 */
namespace am
{

// --------------------------------------------------------------------------------

namespace detail
{

// --------------------------------------------------------------------------------

/*!
 *  @internal Base class of mate
 *
 *  @sa AM_ANONYMOUS_MATE(), AM_ANONYMOUS_MATE_IF()
 */
class mate_base
{
protected:
  mate_base() { }
  ~mate_base() { }

};  // class mate_base

// --------------------------------------------------------------------------------

/*!
 *  @internal Simple pointer holder.
 *  Store a pointer and delete it in type safe manner in its destructor when it
 *  goes out of scope.
 */
class simple_ptr_holder
{
private:

  mutable void * ptr_;

  typedef void (*typeless_deleter_stub)(void *);
  typeless_deleter_stub deleter_stub_;

  // --------------------------------------------------------------------------------

  template<class T> struct typed_
  {
    static void deleter(void * ptr)
    {
      delete static_cast<T *>( ptr );
    }

  };  // template<class T> struct typed_

  // --------------------------------------------------------------------------------

private:

  simple_ptr_holder & operator =(simple_ptr_holder const &);

public:

  simple_ptr_holder() // never throws
    : ptr_( 0 ), deleter_stub_( 0 )
  {
  }

  template<class T>
  simple_ptr_holder(T * ptr)  // never throws
    : ptr_( ptr ), deleter_stub_( &typed_<T>::deleter )
  {
  }

  simple_ptr_holder(simple_ptr_holder const & other)  // never throws
    : ptr_( other.ptr_ ), deleter_stub_( other.deleter_stub_ )
  {
    other.ptr_ = 0;
  }

  ~simple_ptr_holder()  // never throws
  {
    if( ptr_ )
      ( *deleter_stub_ )( ptr_ );
  }

  void * get() const  // never throws
  {
    return ptr_;
  }

  bool empty() const  // never throws
  {
    return 0 == ptr_;
  }

  void reset()  // never throws
  {
    if( ptr_ )
    {
      ( *deleter_stub_ )( ptr_ );
      ptr_ = 0;
    }
  }

};  // class simple_ptr_holder

// --------------------------------------------------------------------------------

} // namespace detail

// --------------------------------------------------------------------------------

//! Mates a host function with the mate function object.
/*! Mates (associates) the result of the host function with the mate function object
 *  so that the associated mate function object is called int its destructor automatically
 *  when it goes out of scope.
 */
template<class R> class mate : public detail::mate_base
{
private:

  R ret_; //!< Return of the host function.
  detail::simple_ptr_holder mate_functor_ptr_;  //!< Mate functoion object.

  typedef void (*typeless_mate_stub)(void *, R);
  typeless_mate_stub mate_stub_;  //!< Typeless mate function object invoker.

  // --------------------------------------------------------------------------------

  /*! @internal typed mate function object mfn_invoker stub.
   */
  template<class T> struct typed_
  {
    /*! Invoke the mate function object in type safe manner.
     *
     *  @param[in] mate_ptr Specifies typeless mate function object.
     *  @param[in] ret Specifies the return of the host function.
     *  @return void.
     */
    static void mate_stub(void * mate_ptr, R ret)
    {
      ( *static_cast<T *>( mate_ptr ) )( ret );
    }

  };  // template<class T> struct typed_

  // --------------------------------------------------------------------------------

private:

  mate<R> & operator =(mate<R> const &);  //!< Restrict assignment.

public:

  /*! Constructor.
   *
   *  @param[in] ret Specifies the return of the host function.
   *  @param[in] mate_functor Specifies the mate function object which will be called
   *                          in the destructor. It should be a unary function object
   *                          which accept @a ret as its argument.
   *
   * @pre Host function should not throw an exception.
   */
  template<class T>
  mate(R ret, T mate_functor)
    : ret_( ret ), mate_functor_ptr_( new T( mate_functor ) )
    , mate_stub_( &typed_<T>::mate_stub )
  {
  }

  /*! Constructor.
   *
   *  @param[in] ret Specifies the return of the host function.
   *  @param[in] mate_functor Specifies the mate function object which will be called
   *                          in the destructor. It should be an unary function object
   *                          which accept @a ret as its argument.
   *  @param[in] mate_if Specifies the predicate which determines whether or not
   *                      the specified mate function object will be called in the destructor.
   *                      It should be an unary predicate which accept @a ret as its
   *                      argument. If it return false, no heap memory allocation is
   *                      even occurred to store the mate function object.
   *
   * @pre Host function should not throw an exception.
   */
  template<class T, class C>
  mate(R ret, T mate_functor, C mate_if)
    : ret_( ret ), mate_functor_ptr_( mate_if( ret ) ? new T( mate_functor ) : 0 )
    , mate_stub_( &typed_<T>::mate_stub )
  {
  }

  /*! Destructor.
   *  Calls mate function object.
   */
  ~mate()  // never throws
  {
    try { run_mate(); }
    catch(...) { }
  }

  /*! Run mate function object now.
   *
   *  @param[in] delete_mate_now Specifies whether or not the mate function object will be
   *                              deallocated after calling the mate function object.
   *                              If false, the mate function object will be deallocated in
   *                              the destructor when it goes out of scope.
   *  @return void.
   */
  void run_mate(bool delete_mate_now = false)
  {
    if( !mate_functor_ptr_.empty() )
    {
      if( mate_stub_ )
      {
        ( *mate_stub_ )( mate_functor_ptr_.get(), ret_ );
        mate_stub_ = 0; // Run mate only once
      }

      if( delete_mate_now )
        mate_functor_ptr_.reset();
    }
  }

  /*! Dismiss the mate functor.
   *
   *  @param[in] delete_mate_now Specifies whether or not the mate function object will be
   *                              deallocated. If false, the mate function object will be
   *                              deallocated in the destructor when it goes out
   *                              of scope.
   *  @return void.
   */
  void dismiss_mate(bool delete_mate_now = false)  // never throws
  {
    if( delete_mate_now )
      mate_functor_ptr_.reset();
    else
      mate_stub_ = 0;
  }

  /*! Implicit conversion.
   *  Cast an illusion to make it possible to use a mate instance as if it is
   *  a raw variable stored, which is the return of the host function.
   *
   *  @return Copy of the stored raw variable, which is the return of the host
   *          function.
   */
  operator R () const // never throws
  {
    return ret_;
  }

};  // template<class R> class mate

// --------------------------------------------------------------------------------

//! void template specialization for mate.
/*! Specifies mate function object to be called in its destructor automatically when it
 *  goes out of scope.
 *
 *  @sa MATE_VOID(), MATE_VOID_IF()
 */
template<> class mate<void>
{
private:

  detail::simple_ptr_holder mate_functor_ptr_;  //!< Mate function object.

  typedef void (*typeless_mate_stub)(void *);
  typeless_mate_stub mate_stub_;  //!< Typeless mate function object invoker.

  // --------------------------------------------------------------------------------

  /*! @internal typed mate function object mfn_invoker stub.
  */
  template<class T> struct typed_
  {
    /*! Invoke the mate function object in type safe manner.
    *
    *  @param[in] mate_ptr Specifies typeless mate function object.
    *  @return void.
    */
    static void mate_stub(void * mate_ptr)
    {
      ( *static_cast<T *>( mate_ptr ) )();
    }

  };  // template<class T> struct typed_

  // --------------------------------------------------------------------------------

private:

  mate<void> & operator =(mate<void> const &);  //!< Restrict assignment.

public:

  /*! Constructor.
  *
  * @param[in] mate_functor Specifies the mate function object which will be called
  *                          in the destructor. It should be a null-nary function object
  *                          which does not accept any argument.
  */
  template<class T>
  mate(T mate_functor)
    : mate_functor_ptr_( new T( mate_functor ) )
    , mate_stub_( &typed_<T>::mate_stub )
  {
  }

  /*! Constructor.
   *
   *  @param[in] mate_functor Specifies the mate function object which will be called
   *                          in the destructor. It should be an null-nary function object
   *                          which does not accept any argument.
   *  @param[in] mate_if Specifies the predicate which determines whether or not
   *                      the specified mate function object will be called in the destructor.
   *                      It should be an null-nary predicate which does not accept
   *                      any argument. If it return false, no heap memory allocation
   *                      is even occurred to store the mate function object.
   */
  template<class T, class C>
  mate(T mate_functor, C mate_if)
    : mate_functor_ptr_( mate_if() ? new T( mate_functor ) : 0 )
    , mate_stub_( &typed_<T>::mate_stub )
  {
  }


  /*! Destructor.
  *  Calls mate function object.
  */
  ~mate()  // never throws
  {
    try { run_mate(); }
    catch(...) { }
  }

  /*! Run mate function object now.
  *
  *  @param[in] delete_mate_now Specifies whether or not the mate function object will be
  *                              deallocated after calling the mate function object.
  *                              If false, the mate function object will be deallocated in
  *                              the destructor when it goes out of scope.
  *  @return void.
  */
  void run_mate(bool delete_mate_now = false)
  {
    if( !mate_functor_ptr_.empty() )
    {
      if( mate_stub_ )
      {
        ( *mate_stub_ )( mate_functor_ptr_.get() );
        mate_stub_ = 0; // Run mate only once
      }

      if( delete_mate_now )
        mate_functor_ptr_.reset();
    }
  }

  /*! Dismiss the mate function object.
  *
  *  @param[in] delete_mate_now Specifies whether or not the mate function object will be
  *                              deallocated. If false, the mate function object will be
  *                              deallocated in the destructor when it goes out
  *                              of scope.
  *  @return void.
  */
  void dismiss_mate(bool delete_mate_now = false)  // never throws
  {
    if( delete_mate_now )
      mate_functor_ptr_.reset();
    else
      mate_stub_ = 0;
  }

};  // template<> class mate<void>

// --------------------------------------------------------------------------------

/*! Helper template function to derive the template parameter automatically.
 *
 *  @param[in] ret Specifies the return of the host function.
 *  @param[in] mate_functor Specifies the mate function object which will be called
 *                          in the destructor. It should be a unary function object
 *                          which accept @a ret as its argument.
 *  @return Temporary mate<> instance.
 *  @sa MATE(), MATE_()
 */
template<class R, class T> mate<R> inline
make_mate(R ret, T mate_functor)
{
  return mate<R>( ret, mate_functor );
}

// --------------------------------------------------------------------------------

/*! Helper template function to derive the template parameter automatically.
 *
 *  @param[in] ret Specifies the return of the host function.
 *  @param[in] mate_functor Specifies the mate function object which will be called
 *                          in the destructor. It should be an unary function object
 *                          which accept @a ret as its argument.
 *  @param[in] mate_if Specifies the predicate which determines whether or not
 *                      the specified mate function object will be called in the destructor.
 *                      It should be an unary predicate which accept @a ret as its
 *                      argument. If it return false, no heap memory allocation is
 *                      even occurred to store the mate function object.
 *  @return Temporary mate<> instance.
 *  @sa MATE_IF(), MATE_IF_()
 */
template<class R, class T, class C> mate<R> inline
make_mate(R ret, T mate_functor, C mate_if)
{
  return mate<R>( ret, mate_functor, mate_if );
}

// --------------------------------------------------------------------------------

//! Predicate. 
/*! Convert a boolean expression into null-nary or unary predicate.
 */
struct condition
{
  bool expr_;

  explicit condition(bool expr) : expr_( expr ) { }
  template<class T> bool operator ()(T t) const { return expr_; }
  bool operator ()() const { return expr_; }

};  // struct condition

// --------------------------------------------------------------------------------

//! Reference holder.
/*! Supports parameters by reference.
 *  It is used to "feed" reference to mate function since the input argument of the
 *  mate function is only passed by value. This class transforms a reference into a value.
 *
 *  @sa ref(), cref()
 */
template <class T> class ref_holder
{
private:
  T & ref_;

public:
  ref_holder(T & ref) : ref_( ref ) { }
  ref_holder(ref_holder<T> const & other) : ref_( other.ref_ ) { }
  ref_holder<T> & operator =(ref_holder<T> const & other)
  {
    if( this != &other )
      ref_ = other.ref_;
    return *this;
  }
  operator T & () const { return ref_; }

};  // template <class T> class ref_holder

// --------------------------------------------------------------------------------

/*! Helper template function for am::ref_holder.
 *
 *  @sa ref_holder, cref
 *
 */
template<class T> ref_holder<T> inline
ref(T & ref)
{
  return ref_holder<T>( ref );
}

// --------------------------------------------------------------------------------

/*! Helper template function for am::ref_holder.
 *
 *  @sa ref_holder, ref
 */
template<class T> ref_holder<T const> inline
cref(T const & ref)
{
  return ref_holder<T const>( ref );
}

// --------------------------------------------------------------------------------

//! Function pointer to an unary function or a binary function.
/*!
 *  It is not a std::unary_function nor a std::binary_function,
 *  but works for any calling convention.
 *
 *  @sa ptr_fun()
 */
template<typename Fn> struct pointer_to_function
{
  Fn const fn_;

  typedef void result_type;

  pointer_to_function(Fn const fn) : fn_( fn ) { }
  template<typename P1> void operator ()(P1 p1) const { ( *fn_ )( p1 ); }
  template<typename P1, typename P2> void operator ()(P1 p1, P2 p2) const { ( *fn_ )( p1, p2 ); }

};  // template<typename Fn> struct pointer_to_function

// --------------------------------------------------------------------------------

/*! Helper template function for am::pointer_to_function.
 *
 *  @sa pointer_to_function
 *
 */
template<typename Fn> pointer_to_function<Fn> inline
ptr_fun(Fn const fn)
{
  return pointer_to_function<Fn>( fn );
}

// --------------------------------------------------------------------------------

//! Bind the 1st argument of a binary function.
/*!
 * It is not a std::unary_function, but works for any calling convention.
 *
 *  @sa bind1st()
 */
template<typename Op, typename P1> struct binder1st
{
  Op const & op_;
  P1 p1_;

  typedef void result_type;

  binder1st(Op const & op, P1 p1) : op_( op ), p1_( p1 ) { }
  template<typename P2> void operator ()(P2 p2) const { op_( p1_, p2 ); }

};  // template<typename Op, typename P1> struct binder1st

// --------------------------------------------------------------------------------

/*! Helper template function for am::binder1st.
 *
 *  @sa binder1st
 */
template<typename Op, typename P1> binder1st<Op, P1> inline
bind1st(Op const & op, P1 p1)
{
  return binder1st<Op, P1>( op, p1 );
}

// --------------------------------------------------------------------------------

//! Bind the 2nd argument of a binary function.
/*!
 *  It is not a std::unary_function, but works for any calling convention.
 *
 *  @sa bind2nd()
 */
template<typename Op, typename P2> struct binder2nd
{
  Op const & op_;
  P2 p2_;

  typedef void result_type;

  binder2nd(Op const & op, P2 p2) : op_( op ), p2_( p2 ) { }
  template<typename P1> void operator ()(P1 p1) const { op_( p1, p2_ ); }

};  // template<typename Op, typename P2> struct binder2nd

// --------------------------------------------------------------------------------

/*! Helper template function for am::binder2nd.
 *
 *  @sa binder2nd
 */
template<typename Op, typename P2> binder2nd<Op, P2> inline
bind2nd(Op const & op, P2 p2)
{
  return binder2nd<Op, P2>( op, p2 );
}

// --------------------------------------------------------------------------------

} // namespace am

// --------------------------------------------------------------------------------

/*! @def MATE(HOST_FN, MATE_FN)
 *  Create an anonymous (unnamed) mate variable which calls the mate function object,
 *  @a MATE_FN in its destructor with the return of the host function, @a HOST_FN
 *  as its argument when it goes out of scope.
 *
 *  @sa AM_ANONYMOUS_MATE()
 */

/*! @def MATE_(N, HOST_FN, MATE_FN)
 *  It is devised to remedy the issue that some compiler can't generate an unique
 *  anonymous variable. In such compiler, user must provide an unique number @a N
 *  to create an unique identifier manually. In other compilers, it is identical
 *  to MATE() and @a N is simply ignored.
 *
 *  @sa MATE()
 */

/*! @def MATE_IF(HOST_FN, MATE_FN, COND)
 *  Create an anonymous (unnamed) mate variable which calls the mate function object, @a
 *  MATE_FN in its destructor with the return of the host function @a HOST_FN as
 *  its argument when it goes out of scope only if the unary predicate, @a COND
 *  asserts true.
 *
 *  @sa AM_ANONYMOUS_MATE_IF()
 */

/*! @def MATE_IF_(N, HOST_FN, MATE_FN, COND)
 *  It is devised to remedy the issue that some compiler can't generate an unique
 *  anonymous variable. In such compiler, user must provide an unique number @a N
 *  to create an unique identifier manually. In other compilers, it is identical
 *  to MATE_IF() and @a N is simply ignored.
 *
 *  @sa MATE_IF()
 */

/*! @def MATE_VOID(MATE_FN)
 *  Create an anonymous (unnamed) mate variable which calls the mate function object,
 *  @a MATE_FN in its destructor when it goes out of scope.
 *
 *  @sa AM_ANONYMOUS_MATE_VOID()
 */

/*! @def MATE_VOID_(N, MATE_FN)
 *  It is devised to remedy the issue that some compiler can't generate an unique
 *  anonymous variable. In such compiler, user must provide an unique number @a N
 *  to create an unique identifier manually. In other compilers, it is identical
 *  to MATE_VOID() and @a N is simply ignored.
 *
 *  @sa MATE_VOID()
 */

/*! @def MATE_VOID_IF(MATE_FN, COND)
 *  Create an anonymous (unnamed) mate variable which calls the mate function object,
 *  @a MATE_FN in its destructor when it goes out of scope only if the null-nary
 *  predicate, @a COND asserts true.
 *
 *  @sa AM_ANONYMOUS_MATE_VOID_IF()
 */

/*! @def MATE_VOID_IF_(N, MATE_FN, COND)
 *  It is devised to remedy the issue that some compiler can't generate an unique
 *  anonymous variable. In such compiler, user must provide an unique number @a N
 *  to create an unique identifier manually. In other compilers, it is identical
 *  to MATE_VOID_IF() and @a N is simply ignored.
 *
 *  @sa MATE_VOID_IF()
 */

#define AM_JOIN(a, b)         AM_DO_JOIN(a, b)
#define AM_DO_JOIN(a, b)      AM_DO_JOIN2(a, b)
#define AM_DO_JOIN2(a, b)     a##b

// --------------------------------------------------------------------------------

/*!
 *  @internal Generates anonymous mate variable.
 */
#define AM_ANONYMOUS_MATE(HOST_FN, MATE_FN, UNIQUE) \
  am::detail::mate_base const & AM_JOIN(_anonymous_, UNIQUE) = \
  am::make_mate((HOST_FN), (MATE_FN)); AM_JOIN(_anonymous_, UNIQUE);

/*!
 *  @internal Generates anonymous mate variable with a condition.
 */
#define AM_ANONYMOUS_MATE_IF(HOST_FN, MATE_FN, COND, UNIQUE) \
  am::detail::mate_base const & AM_JOIN(_anonymous_if_, UNIQUE) = \
  am::make_mate((HOST_FN), (MATE_FN), (COND)); AM_JOIN(_anonymous_if_, UNIQUE);

/*!
 *  @internal Generates anonymous mate<void> variable.
 */
#define AM_ANONYMOUS_MATE_VOID(MATE_FN, UNIQUE) \
  am::mate<void> AM_JOIN(_anonymous_void_, UNIQUE)((MATE_FN)); \
 AM_JOIN(_anonymous_void_, UNIQUE);

/*!
 *  @internal Generates anonymous mate<void> variable with a condition.
 */
#define AM_ANONYMOUS_MATE_VOID_IF(MATE_FN, COND, UNIQUE) \
  am::mate<void> AM_JOIN(_anonymous_void_if_, UNIQUE)((MATE_FN), (COND)); \
 AM_JOIN(_anonymous_void_if_, UNIQUE);

// --------------------------------------------------------------------------------

#if defined(AM_CAN_NOT_CREATE_UNIQUE_ANONYMOUS)
#define MATE(HOST_FN, MATE_FN)          AM_ANONYMOUS_MATE(HOST_FN, MATE_FN, can_not_create_unique)
#define MATE_IF(HOST_FN, MATE_FN, COND) AM_ANONYMOUS_MATE_IF(HOST_FN, MATE_FN, COND, can_not_create_unique)
#define MATE_VOID(MATE_FN)              AM_ANONYMOUS_MATE_VOID(MATE_FN, can_not_create_unique)
#define MATE_VOID_IF(MATE_FN, COND)     AM_ANONYMOUS_MATE_VOID_IF(MATE_FN, COND, can_not_create_unique)
#elif defined(AM_CAN_CREATE_UNIQUE_COUNT_ANONYMOUS)
#define MATE(HOST_FN, MATE_FN)          AM_ANONYMOUS_MATE(HOST_FN, MATE_FN, __COUNTER__)
#define MATE_IF(HOST_FN, MATE_FN, COND) AM_ANONYMOUS_MATE_IF(HOST_FN, MATE_FN, COND, __COUNTER__)
#define MATE_VOID(MATE_FN)              AM_ANONYMOUS_MATE_VOID(MATE_FN, __COUNTER__)
#define MATE_VOID_IF(MATE_FN, COND)     AM_ANONYMOUS_MATE_VOID_IF(MATE_FN, COND, __COUNTER__)
#else
#define MATE(HOST_FN, MATE_FN)          AM_ANONYMOUS_MATE(HOST_FN, MATE_FN, __LINE__)
#define MATE_IF(HOST_FN, MATE_FN, COND) AM_ANONYMOUS_MATE_IF(HOST_FN, MATE_FN, COND, __LINE__)
#define MATE_VOID(MATE_FN)              AM_ANONYMOUS_MATE_VOID(MATE_FN, __LINE__)
#define MATE_VOID_IF(MATE_FN, COND)     AM_ANONYMOUS_MATE_VOID_IF(MATE_FN, COND, __LINE__)
#endif

// --------------------------------------------------------------------------------

#if defined(AM_CAN_NOT_CREATE_UNIQUE_ANONYMOUS)
#define MATE_(N, HOST_FN, MATE_FN)          AM_ANONYMOUS_MATE(HOST_FN, MATE_FN, create_unique_##N)
#define MATE_IF_(N, HOST_FN, MATE_FN, COND) AM_ANONYMOUS_MATE_IF(HOST_FN, MATE_FN, COND, create_unique_##N)
#define MATE_VOID_(N, MATE_FN)              AM_ANONYMOUS_MATE_VOID(MATE_FN, can_not_create_unique##N)
#define MATE_VOID_IF_(N, MATE_FN, COND)     AM_ANONYMOUS_MATE_VOID_IF(MATE_FN, COND, can_not_create_unique##N)
#else
#define MATE_(N, HOST_FN, MATE_FN)          MATE(HOST_FN, MATE_FN)
#define MATE_IF_(N, HOST_FN, MATE_FN, COND) MATE_IF(HOST_FN, MATE_FN, COND)
#define MATE_VOID_(N, MATE_FN)              MATE_VOID(MATE_FN)
#define MATE_VOID_IF_(N, MATE_FN, COND)     MATE_VOID_IF(MATE_FN, COND)
#endif

// --------------------------------------------------------------------------------

#endif  // #if !defined(__MATE_HPP__INCLUDED__)
