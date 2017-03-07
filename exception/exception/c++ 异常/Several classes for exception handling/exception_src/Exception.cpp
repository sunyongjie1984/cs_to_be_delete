/*
 Copyright (c) 2002
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru 
 Created: 16.01.2002 12:07:21
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 set of classes for working with win32 structured exception in C++.
 the example of using Symbol Handler and Debugging service API for printing a call stack's info  
*/

#include "stdafx.h"
#include "se_translator.h"
#include "exception_trap.h"
#include "unhandled_report.h"
#include "sym_engine.h"
#include "debug_stream.h"
#include "exception2.h"

// std::cout or debugger's output depending on running under debugger or not
std::ostream& get_ostream();
std::ostream& g_os = get_ostream();	

// tests cases
void force_access_violation(std::ostream& os) throw (se_translator::access_violation);
void force_no_memory(std::ostream& os) throw (se_translator::no_memory);
void force_cpp_exception(std::ostream& os) throw (exception2);
void force_trace_stack(std::ostream&);
void test(void (*f)(std::ostream&), std::ostream& os);

// article's example
void foo1(std::ostream& os);
void foo2(std::ostream& os);

#define TEST_CASE_TRACE_STACK
#define TEST_CASE_ACCESS_VIOLATION
#define TEST_CASE_NO_MEMORY
#define TEST_CASE_CPP_EXCEPTION
//#define TEST_CASE_UNHANDLED_EXCEPTION

// sets the trap for unhandled exceptions
exception_trap<unhandled_report> trap(true, unhandled_report(g_os));

// workaround of VCPP synchronous exception and se translator
bool global_force_exception_flag = false;
#define WORKAROUND_VCPP_SYNCHRONOUS_EXCEPTION  if (global_force_exception_flag) force_exception_frame();
void force_exception_frame(...) {std::cout.flush();}


int main(int argc, char* argv[])
{
	// sets the mapper win32 structured exception into to C++ exceptions

	se_translator translator;

//	foo1(g_os);
//	foo2(g_os);
		
	// runs several test cases

	#ifdef TEST_CASE_TRACE_STACK	
	test(force_trace_stack, g_os);
	#endif

	#ifdef TEST_CASE_ACCESS_VIOLATION	
	test(force_access_violation, g_os);
	#endif
	
	#ifdef TEST_CASE_NO_MEMORY		
	test(force_no_memory, g_os);
	#endif
		
	#ifdef TEST_CASE_CPP_EXCEPTION			
	test(force_cpp_exception, g_os);
	#endif
	
	// example of unhanlded exception trap
	// will print the exception address and trace call stack 
	// of course, we can't see anything if debugger already attached to the process
	// so in such case we must skip it
	#ifdef TEST_CASE_UNHANDLED_EXCEPTION
	if (!IsDebuggerPresent())
	{
		g_os << std::endl << "example of unhanlded exception trap .." << std::endl;
		force_access_violation(g_os);
	}
	#endif
	
	return 0;
}

std::ostream& get_ostream()
{
	static dostream dos;
	if (IsDebuggerPresent())
		return dos;
	else 
		return std::cout;
}

void test(void (*f)(std::ostream&), std::ostream& os)
{
	try
	{		
		f(os);
	}
	catch(se_translator::access_violation& ex)
	{			
		os	<< ex.name() << " at 0x" << std::hex << ex.address() 
			<< ", thread attempts to " << (ex.is_read_op() ? "read" : "write") 
			<< " at 0x" << std::right << ex.inaccessible_address() << std::endl
			<< "stack trace : " << std::endl;
		sym_engine::stack_trace(os, ex.info()->ContextRecord);		
	}
	catch(se_translator::no_memory& ex)
	{
		os  << ex.name() << " at 0x" << std::hex << ex.address() 
			<< ", unable to allocate " << std::dec << ex.mem_size() << " bytes" << std::endl
			<< "stack trace : " << std::endl;
		sym_engine::stack_trace(os, ex.info()->ContextRecord);		
	}
	catch(exception2& ex)
	{
		os  << ex.what() << std::endl
			<< "stack trace :" << std::endl
			<< ex.stack_trace() << std::endl;
	}
} 

void force_access_violation(std::ostream& os) throw (se_translator::access_violation)
{
	os << std::endl << "causes access_violation exception .." << std::endl;	
	char * p = 0;
	p[0] = '\n';
	printf(p);
}

void force_no_memory(std::ostream& os) throw (se_translator::no_memory)
{
	os << std::endl << "causes no_memory exception .." << std::endl;

	HANDLE heap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 64*1024, 64*1024);	
	__try
	{
		void *p1 = HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, 32*1024);
		void *p2 = HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, 32*1024);
		p1; p2;
	}
	__finally
	{
		HeapDestroy(heap);
	}		
}

void force_cpp_exception(std::ostream& os) throw (exception2)
{
	os << std::endl << "throws c++ exception (exception2) with call stack info .." << std::endl;
	throw exception2("c++ exception");
//	throw bug_check();
}

void force_trace_stack(std::ostream& os)
{
	os << std::endl << "just traces a call stack .." << std::endl;
	sym_engine::stack_trace(os);			
}

//

void foo(std::ostream& os)
{		
	try
	{		
		char * p = 0;					
		printf("%u", strlen(p)); // oops		
	}
	catch(se_translator::access_violation& ex)
	{
		sym_engine::stack_trace(os, ex.info()->ContextRecord);		
	}
}

void foo1(std::ostream& os)
{		
	try
	{		
		WORKAROUND_VCPP_SYNCHRONOUS_EXCEPTION // force to install a exception frame		
		char * p = 0;					
		printf("%u", strlen(p)); // oops		
	}
	catch(se_translator::access_violation& ex)
	{
		sym_engine::stack_trace(os, ex.info()->ContextRecord);		
	}
}

int exception_filter(std::ostream& os, EXCEPTION_POINTERS * pex)
{
	sym_engine::stack_trace(os, pex->ContextRecord);		
	return EXCEPTION_EXECUTE_HANDLER ;
}

void foo2 (std::ostream& os)
{		
	__try 
	{
		char * p = 0;		
		printf("%u", strlen(p)); // oops
	}
	__except(exception_filter(os, GetExceptionInformation())) 
	{
	}
}
