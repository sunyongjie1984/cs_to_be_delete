The directory contains three projects:
=====================================

1)  MyExcHandler. This is built as static library.
2)  excptstorage. This is built as DLL.
3)  demo.         Showing how to use exception handler.


The following steps are needed to use my_exc_handler:

1)  Link with MyExcHandler.lib and excptstorage.lib.
2)  Make sure that excptstorage.dll is in your path.
3)  Set C runtime library to Multithreaded (for release) or Debug MultiThreaded (for DEBUG)


IMPORTANT:
============

BUILDING FOR VC++ 5.0:

VC++ 5.0 <functional> header has a bug, which will give compilation error. There are two 
workarounds:

a) add 'const' qualfier to mem_fun1_t::operator() in <functional>
b) Replace the header <functional> with the one provided by VC++ 6.0


Primarily built with VC++ 6.0 on Windows 2000. It also works fine with VC++ 5.0 (after overcoming the compilation problem) and VC++ 7.0. There is small difference between 6.0 and 7.0. 6.0 first copies the exception (or its reference) on catch block's frame and then perfroms stack unwinding before calling catch block. 7.0 library first performs stack unwinding. The behavior of my library is similar to 6.0 library.

