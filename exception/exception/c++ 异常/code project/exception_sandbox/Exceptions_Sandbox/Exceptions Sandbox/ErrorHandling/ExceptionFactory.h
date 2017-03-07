/********************************************************************
  Purpose:	A factory for creating exceptions according to their tag name.
            Not for public usage.
            When deriving from JException, each derived class should be referenced here.
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#pragma once

#include "JException.h"
#include "TimeoutException.h"

class ExceptionFactory {

    friend class JException; // To allow access to the private method

private:

    /*
     * Creates an exception with a type according to the given className.
     *
     * Access   : private
     * Parameter: const string & className - a unique string for each exception in the solution
     * Parameter: const int skipFrames - see JException ctor
     * Parameter: const string & cause - see JException ctor
     * Parameter: const string & preStackTrace - see JException ctor
     * Returns  : created exception  
     */
    static JException Create(const string& className, const int skipFrames, const string& cause, const string& preStackTrace) {
        if (className == JException::JE_CLASS_NAME) {
            return JException(skipFrames, cause, preStackTrace);
        } 
        if (className == TimeoutException::TOE_CLASS_NAME) {
            return TimeoutException(skipFrames, cause, preStackTrace);
        }
        //Should never get here
        return JException("Bug: Unable to find an exception matching class tag %s", className);
    }
};

