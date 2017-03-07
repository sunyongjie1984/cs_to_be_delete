#pragma once
#include "stackwalker.h"
#include <string>

using std::string;

/**
* A StackWalker that sends its output to a string, which can in turn be retrieved with GetOutput().
* Example: retrieving the current thread's stack trace.
*    
*		#include "StackWalkerString.h"
*
*		StackWalkerString stackWalker;
*		stackWalker.ShowCallstack();
*       string stackTrace = stackWalker.GetOutput();
*/
class StackWalkerString : public StackWalker
{

public:

    StackWalkerString ( int options ) 
    : StackWalker( options )
    , m_buffer("") 
    {};

    virtual ~StackWalkerString() {};

    string& GetOutput() {return m_buffer;};

    virtual void OnOutput(LPCSTR szText) { m_buffer += szText; };

private:
    //A buffer into which the stack trace is written
    string m_buffer;

}; 

