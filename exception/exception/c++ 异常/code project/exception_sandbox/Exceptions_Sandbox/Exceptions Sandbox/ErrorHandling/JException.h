/********************************************************************
Purpose:	Base class for all the exceptions in the solution. 
            When deriving from this class, make sure to override and implement:
                GetMyClassName method, returning a unique identifying string
                assignment operator =,
                copy constructor
                protected constructor with signature: (int skipFrames, const string& cause, const string& preStackTrace)
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#pragma once

#include <string>
#include <wtypes.h>
#include "ExceptionLibExport.h"

using std::string;

class EXCEPTION_LIB_EXT_CLASS JException {

	friend class ExceptionFactory; // To allow access to non public ctor

public:

    /* 
     * A "do nothing" empty ctor. 
     *
     * Access   : public
     */
    JException() {};

	/* 
	 * Instantiates an exception with the given cause. The exception maintains the stack trace at the creation point.
     * For convenience of formatting the cause, constructor accepts a variable number of arguments, like sprintf.
	 * For example:
	 *
	 * JException e("Width %d and height %d are not compatible\n", width, height);
     *
     * Access   : public
     */
	JException(const string cause, ...);

	JException(const JException& other) : m_cause(other.m_cause), m_stackTrace(other.m_stackTrace) {};

	JException& operator = (const JException& other);
	
	virtual ~JException() {}

	const string& GetCause() const {return m_cause;}

	const string& GetStackTrace() const {return m_stackTrace;}

	/*
	 * Retrieves the cause and the stack trace concatenated as a single string. Useful, for dumping the exception to log.
	 * 
     * Access   : public
	 * Returns  : concatenated string of the cause and the stack trace
	 */
	const string AsString() const { return m_cause + m_stackTrace; };

	/*
	 * Prepends the given prefix to the cause.
     * For convenience, method accepts a variable number of arguments, like sprintf.
	 * For example:
	 *
	 * JException e("Not enough memory");
     * ...
	 * e.PrependToCause("Failed to read image from file %s due to: ", "Icon.gif");
	 * 
	 * cause turns into "Failed to read image from file Icon.gif due to: Not enough memory"
     *
     * Access   : public
	 */
	void PrependToCause(const string prefix, ...);

	/*
	 * A static method that reconstructs a JException, or one of its descendants, from the given XML string. Stack trace
     * of the current context is appended to the stack trace that is already embedded in the XML string.
	 *
	 * Parameter: const BSTR xmlString - an XML string, which is a result of serialization of a JException
	 * Returns  : the created exception (JException, or a descendant)
     *
     * Access   : public
	 */
	static const JException FromXml(const BSTR xmlString);

	/**
	 * Serializes this exception to an XML string. 
     *
     * Access   : public
	 */
	const string ToXml() const;

protected:

    /*
     * Retrieves a class identifier tag string. In use by ExceptionFactory. Should be overridden by each of the descendants from JException.
     *
     * Returns  : class identifier tag string.
     *
     * Access   : protected
     */
    virtual const string& GetMyClassName() const;

	/*
	 * Constructor for the usage of ExceptionFactory only. 
	 *
	 * Parameter: int skipFrames -
	 * Parameter: const string & cause -
	 * Parameter: const string & preStackTrace -
     *
     * Access   : protected
	 */
	JException(int skipFrames, const string& cause, const string& preStackTrace);

private:
	
	//Members

	string m_cause;

	string m_stackTrace;

	//Methods

	const string GenerateStackTrace(int skipFrames);

	void AppendNewLineIfNeeded(string& str);

    //Tags used for serializing to/from XML
    static const string EXCEPTION_TAG;
    static const string CLASS_NAME_TAG;
    static const string CAUSE_TAG;
    static const string STACK_TRACE_TAG;

    // Unique identifier for JException class
    static const string JE_CLASS_NAME;

};
