#include <cstdlib>
#include <iostream>
#include <windows.h>

using namespace std;

#include <malloc.h>
#include <new>
#include <STDLIB.H>
#include <TIME.H>
#include <functional>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

#include "../../../include/mate.hpp"
#define AM_BIND_ENABLE_STDCALL
#include "../../../include/lambda.hpp"

#define DO_NOT_TEST_BOOST

#if !defined( DO_NOT_TEST_BOOST )

#include <boost/shared_ptr.hpp>

#define BOOST_BIND_ENABLE_STDCALL
#include <boost/bind.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

namespace lambda = boost::lambda;

#else // #if !defined( DO_NOT_TEST_BOOST )

namespace lambda = am::lambda;

#endif  // #if !defined( DO_NOT_TEST_BOOST )

// --------------------------------------------------------------------------------

void test01()
{
  char const * lpszFilePath = "c:\\test.dat";
  HANDLE hFile( ::CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ) );
  if( INVALID_HANDLE_VALUE != hFile )
  {
    if( 100 < ::GetFileSize( hFile, NULL ) )
      throw "File too small";

    ::CloseHandle( hFile );
    ::DeleteFile( lpszFilePath );
  }
}

// --------------------------------------------------------------------------------

#if !defined( DO_NOT_TEST_BOOST )

void test02()
{
  boost::shared_ptr<char const> spFilePath( "c:\\test.dat", &::DeleteFile );
  boost::shared_ptr<void> spFile( ::CreateFile( spFilePath.get(), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ),
    &::CloseHandle );
  if( INVALID_HANDLE_VALUE != spFile.get() )
  {
    DWORD dwFileSize = 0;
    ::GetFileSize( spFile.get(), &dwFileSize );
  }
}

#else

void test02() { }

#endif

// --------------------------------------------------------------------------------

void test03()
{
  am::mate<char const *> lpszFilePath( "c:\\test.dat", &::DeleteFile );
  am::mate<HANDLE> hFile( ::CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ),
    &::CloseHandle,
    (HANDLE)INVALID_HANDLE_VALUE  != lambda::_1 || ( (HANDLE)123 <= lambda::_1 && ! true ) );
  if( INVALID_HANDLE_VALUE != hFile )
  {
    DWORD dwFileSize = 0;
    ::GetFileSize( hFile, &dwFileSize );
  }
}

// --------------------------------------------------------------------------------

int prefix(int n) { return n + 100; }
void suffix(int n) { n -= 100; }

void test04()
{
  am::mate<int> nNumber( prefix(123), &suffix );
  assert( 223 == nNumber );

  int nNumber2 = nNumber; // Compile OK!

#if 0
  nNumber = nNumber2; // Compile error!
  nNumber = 52;       // Compile error!
#endif

  {
    MATE( prefix( 333 ), &suffix );

  } // calls suffix( 433 ) here

} // calls suffix( 223 ) here on exit.

// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------

#if !defined( DO_NOT_TEST_BOOST )

void test06(HWND hwnd)
{
  am::mate<HDC> hdc( ::GetWindowDC( hwnd ), boost::bind( &::ReleaseDC, hwnd, _1 ) );

  MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), boost::bind( &::SelectObject, hdc, _1 ) );
}

#endif

// --------------------------------------------------------------------------------

void test07(HWND hwnd)
{
  am::mate<HDC> hdc( ::GetWindowDC( hwnd ), am::bind1st( &::ReleaseDC, hwnd ) );

  MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), am::bind1st( &::SelectObject, hdc ) );
}

// --------------------------------------------------------------------------------

void test08(HWND hwnd)
{
  am::mate<HDC> hdc( ::GetWindowDC( hwnd ), am::lambda::bind( &::ReleaseDC, hwnd, am::lambda::_1 ) );

  MATE( ::SelectObject( hdc, ::GetStockObject( BLACK_PEN ) ), am::lambda::bind( &::SelectObject, hdc, am::lambda::_1 ) );
}

// --------------------------------------------------------------------------------

void test09()
{
  am::mate<HANDLE> hEvent( ::CreateEvent( NULL, FALSE, FALSE, NULL ), &::CloseHandle );
  if( hEvent == NULL )
    hEvent.dismiss_mate();
}

// --------------------------------------------------------------------------------

struct EventCreated
{
  bool operator ()(HANDLE hevent) const { return NULL != hevent; }

};  // struct EventCreated

void test10()
{
  MATE_IF( ::CreateEvent( NULL, FALSE, FALSE, NULL ), &::CloseHandle,  EventCreated() );
}

// --------------------------------------------------------------------------------

void test11()
{
  am::mate<HANDLE> hEvent( ::CreateEvent( NULL, FALSE, FALSE, NULL ), &::CloseHandle, (HANDLE)NULL != am::lambda::_1 );
}

// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------

void test13(HANDLE hres)
{
  am::mate<int> nResult( AcquireResource( hres ),
    am::lambda::bind( &ReleaseResource, hres ), RESOURCE_ACQUSITION_SUCCESS == am::lambda::_1  );

}

// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------

void decrease(int & nRef)
{
  --nRef;
}

int & Increase(int & x) { return ++x; }
void Decrease(int & x) { --x; }

void test15(int & refCount)
{
  am::mate<int &> decreseOnExit( Increase( refCount ), &Decrease );

} //  Calls Decrease( refCount ) on exit.

// --------------------------------------------------------------------------------

void test16(int & refCount)
{
  MATE( am::ref( Increase( refCount ) ), &Decrease );

}  //  Calls Decrease( refCount ) on exit.

// --------------------------------------------------------------------------------

// Overloaded functions
void foo(char const *, int) { }
void foo(int) { }
void __stdcall foo(char const *) { }

void __stdcall bar(char const *) { }

void test17()
{
  // Provides template parameters explicitly to resolve overloaded functions.
  // template parameter 
  MATE_( 0, "Hello foo!", am::ptr_fun<void (_stdcall *)(char const *)>( &foo ) );
  MATE_( 1, "Hello foo!", am::bind2nd( am::ptr_fun<void (*)(char const *, int)>( &foo ), 123 ) );

  // am::pointer_to_function is not necessary,
  // unless otherwise resolving overloading resolution is required.
  MATE_( 2, "Hello bar!", am::ptr_fun( &bar ) );
  MATE_( 3, "Hello bar!", &bar );
}

// --------------------------------------------------------------------------------
 
int foo2(char const *, int) { return 0; }
int bar2(char const *, int) { return 0; }
// int bar2(char const *, int) { return 0; }  // __stdcall calling convention.

void test18()
{
  // MATE_( 0, "Hello foo!", std::bind2nd( &foo2, 123 ) ); // Compiles error!
  // MATE_( 1, "Hello bar!", std::bind2nd( &bar2, 123 ) ); // Compiles error!
  
  // Do not use am::ptr_fun, am::bind1st and am::bind2nd for the free function with
  // calling convention other than __cdecl in gcc
  MATE_( 2, "Hello foo!", am::bind2nd( &foo2, 123 ) );
  MATE_( 3, "Hello bar!", am::bind2nd( &bar2, 123 ) ); // Compiles OK!
}

// --------------------------------------------------------------------------------

void test19(bool cond)
{
  assert( false == am::condition( 2 == 3 )() );
  assert( false == am::condition( 2 == 3 )( "123" ) );  // Input argument is simply ignored.

  // Use am::lambda::condition instead when composing a function object using am::lambda
  MATE_IF( ::CreateMutex(NULL, TRUE, NULL), &::ReleaseMutex,
    (HANDLE)NULL != am::lambda::_1 && am::lambda::condition( cond ) );

}

// --------------------------------------------------------------------------------

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
  //    only if the first of the resultant std::pair of the host function hold true.
  MATE_IF( AddVertex( g ), am::lambda::bind( &RemoveVertex, &am::lambda::_1->*&result_pair::second , g ), 
    &am::lambda::_1->*&result_pair::first );
}

// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------

void MyThreadFunc(LPVOID lpvParam)
{
  // SetEvent() is guaranteed to be called when MyThreadFunc() exit.
  MATE( lpvParam, &::SetEvent );

  ::Sleep(1000);

  // Do somethings.
}

DWORD test22()
{
  am::mate<HANDLE> hEvent( ::CreateEvent( NULL, FALSE, FALSE, NULL ),	// Auto-reset, not signaled, no-named event
    &::CloseHandle );  // Mate function.
  if( hEvent == NULL )
  {
    hEvent.dismiss_mate();
    return 0x0bad0001;
  }

  DWORD dwThreadID = 0;
  am::mate<HANDLE> hThread( ::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadFunc, (LPVOID)hEvent, 0, &dwThreadID ),
    &::CloseHandle ); // Mate function
  if( hThread == NULL )
  {
    hThread.dismiss_mate();
    return 0x0bad0002;
  }

  // Block the current thread and wait till the spawned child thread exit and signal the event.
  return ::WaitForSingleObject(hEvent, INFINITE);
}

// --------------------------------------------------------------------------------

void test23()
{
  CRITICAL_SECTION cs;
  MATE_VOID( ( ::InitializeCriticalSection(&cs), am::lambda::bind( &::DeleteCriticalSection, &cs ) ) );
  MATE_VOID_( 1, ( ::EnterCriticalSection(&cs), am::lambda::bind( &::LeaveCriticalSection, &cs ) ) );
}

// --------------------------------------------------------------------------------

void test24()
{
  am::mate<HANDLE> hMutex(::CreateMutex(NULL, FALSE, NULL), am::lambda::bind( ::CloseHandle, am::lambda::_1 ) );
  MATE_VOID( ( ::WaitForSingleObject(hMutex, INFINITE), am::lambda::bind( &::ReleaseMutex, hMutex ) ) );
}

// --------------------------------------------------------------------------------

#if defined(_MSC_VER)

void test25()
{
  CDC dc;

  MATE( dc.SelectStockObject( BLACK_PEN ),
    std::bind1st( std::mem_fun1<CGdiObject *, CDC, CGdiObject *>( &CDC::SelectObject ), &dc ) );

  MATE_( 1, dc.SetBkMode(TRANSPARENT),
    std::bind1st( std::mem_fun1( &CDC::SetBkMode ), &dc ) );

  MATE_( 2, dc.SetBkMode(TRANSPARENT),
    am::bind1st( std::mem_fun1( &CDC::SetBkMode ), &dc ) );

  MATE_( 3, dc.SetBkMode(TRANSPARENT),
    lambda::bind( &CDC::SetBkMode, &dc, lambda::_1 ) );
}

#endif  // #if defined(_MSC_VER)

// --------------------------------------------------------------------------------

void test26()
{
  try
  {

    am::mate<LPCSTR> szTestFilePath( "c:\\test.dat", &::DeleteFile );

    am::mate<HANDLE> hFile( ::CreateFile(
      szTestFilePath,					// file name
      GENERIC_READ,						// read-only access
      FILE_SHARE_READ | FILE_SHARE_WRITE,		// share read/write
      NULL,								    // no SD
      OPEN_ALWAYS,						// open existing file only
      FILE_ATTRIBUTE_NORMAL,	// normal attribute
      NULL),									// no template file
      am::lambda::bind( &::CloseHandle, am::lambda::_1 ),
      (HANDLE)NULL != lambda::_1 );

    if( hFile == NULL )
      throw 0;

    DWORD dwFileSize = ::GetFileSize( hFile, NULL );

    am::mate<HANDLE> hMapFile ( ::CreateFileMapping(
      hFile,			    // handle to file
      NULL,						// no security
      PAGE_READONLY,	// read-only protection
      0,							//
      dwFileSize,			// size
      NULL),					// unnamed
      am::lambda::bind( &::CloseHandle, am::lambda::_1 ),
      (HANDLE)NULL != lambda::_1 );

    if( hMapFile == NULL )
      throw 1;

    am::mate<LPVOID> lpMemoryMappedFileBase( ::MapViewOfFile(
      hMapFile,				// handle to the file-mapping object
      FILE_MAP_READ,	// read-only access
      0,							// no offset
      0,							// no offset
      dwFileSize),		// number of bytes to map
      am::lambda::bind( &::UnmapViewOfFile, am::lambda::_1 ),
      (LPVOID)NULL != lambda::_1 );

    if( lpMemoryMappedFileBase == NULL )
      throw 2;

  }
  catch(int) { }
}

// --------------------------------------------------------------------------------

int main(int /*argc*/, char* /*argv*/[])
{
  test01();

  test02();

  test03();

  test04();

  HMODULE hmod = ::GetModuleHandle(NULL);
  am::mate<HWND> hwnd(
    ::CreateWindow("BUTTON", NULL, WS_POPUP | WS_VISIBLE, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, (HINSTANCE)hmod, 0),
    &::DestroyWindow );
  assert( ::IsWindow( hwnd ) );

  test05( hwnd );

  // test06( hwnd );

  test07( hwnd );

  test08( hwnd );

  test09();

  test10();

  test11();

  test12(0);

  test13(0);

  test14(0, 1);

  int refCount = 10;
  test15( refCount );

  test16( refCount );

  test17();

  test18();

  test19( true );

  Graph g;
  test20( g );

  RECT_MAP rect_map;
  POINT pt = { 10, 20 };
  test21( rect_map, pt);

  test22();

  test23();

  test24();

  // test25();

  test26();    
}
