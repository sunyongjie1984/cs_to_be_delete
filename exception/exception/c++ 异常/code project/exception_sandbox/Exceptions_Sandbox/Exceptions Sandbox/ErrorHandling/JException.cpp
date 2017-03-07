/********************************************************************
  Purpose:	Implementation of JException
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#include "JException.h"
#include "xmlParser.h"
#include "StackWalkerString.h"
#include "ExceptionFactory.h"
#include <winbase.h>
#include <Strsafe.h>
#include <stdarg.h>

JException::JException(const string cause, ...)
{
    char temp[512];
	va_list args;
	va_start(args, cause);
    vsnprintf_s(temp, 512, _TRUNCATE, cause.c_str(), args);
    va_end(args);

    m_cause.assign(temp);
	AppendNewLineIfNeeded( m_cause );

	m_stackTrace = GenerateStackTrace( 3 /* Skip the first three frames, which are this ctor, GenerateStackTrace and StackWalker::showCallStack */ );
}

JException& JException::operator = (const JException& other)
{
    if ( this == &other) {// same object!
		return (*this);
	}
	m_cause = other.m_cause;
	m_stackTrace = other.m_stackTrace;

	return (*this);
}

JException::JException(int skipFrames, const string& cause, const string& preStackTrace) : m_cause(cause)
{
	AppendNewLineIfNeeded( m_cause );
	m_stackTrace = preStackTrace;
	m_stackTrace += "\n-------------------------\n";
	m_stackTrace += GenerateStackTrace( skipFrames );
}

void JException::AppendNewLineIfNeeded(string& str) 
{
	if (str[str.size() - 1] != '\n') {
        str += '\n';
    }
}

void JException::PrependToCause(const string prefix, ... )
{
    char temp[512];
    va_list args;
    va_start(args, prefix);
    vsnprintf_s(temp, 512, _TRUNCATE, prefix.c_str(), args);
    va_end(args);

    m_cause.insert(0, temp);
}

const string JException::GenerateStackTrace(int skipFrames)
{
	StackWalkerString stackWalker( StackWalker::RetrieveLine ); 
	stackWalker.ShowCallstack( skipFrames ); 
	string output = stackWalker.GetOutput();
	AppendNewLineIfNeeded( output );
	return output;
}

const string JException::ToXml() const
{
	XMLNode xMainNode = XMLNode::createXMLTopNode( "xml", TRUE );
    xMainNode.addAttribute("version", "1.0");
	
	XMLNode xRoot = xMainNode.addChild( EXCEPTION_TAG.c_str() );
	XMLNode xClass = xRoot.addChild( CLASS_NAME_TAG.c_str() );
	xClass.addText( GetMyClassName().c_str() );
	XMLNode xCause = xRoot.addChild( CAUSE_TAG.c_str() );
	xCause.addText( m_cause.c_str() );
	XMLNode xStack = xRoot.addChild( STACK_TRACE_TAG.c_str() );
	xStack.addText( m_stackTrace.c_str() );

    char* xmlString = xMainNode.createXMLString(0 /* no format */);
	string cstring(xmlString);
	
	free(xmlString);

	return cstring;
}

/* static */ const JException JException::FromXml(const BSTR xmlString)
{
	//Convert to ANSI
	int size = SysStringLen(xmlString) + 1;
	char *ansistr = new char[size];
	WideCharToMultiByte(CP_ACP, 0, xmlString, -1, ansistr, size, NULL, NULL);
	//Parse the XML string
	XMLNode xRoot = XMLNode::parseString(ansistr, EXCEPTION_TAG.c_str());	
	XMLNode xClass = xRoot.getChildNode( CLASS_NAME_TAG.c_str() );
	const char * className = xClass.getText();
	XMLNode xCause = xRoot.getChildNode( CAUSE_TAG.c_str() );
	const char * cause = xCause.getText();
	XMLNode xStackTrace = xRoot.getChildNode( STACK_TRACE_TAG.c_str() );
	const char * stackTrace = xStackTrace.getText();

	//free the string memory:
	delete[] ansistr;
	return ExceptionFactory::Create(className, 5, cause, stackTrace);
}

const string JException::JE_CLASS_NAME = "JException";

const string& JException::GetMyClassName() const
{
	return JE_CLASS_NAME;
}

const string JException::EXCEPTION_TAG = "EXCEPTION";
const string JException::CLASS_NAME_TAG = "CLASS";
const string JException::CAUSE_TAG = "CAUSE";
const string JException::STACK_TRACE_TAG = "STACKTRACE";

