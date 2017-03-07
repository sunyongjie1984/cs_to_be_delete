/********************************************************************
  Purpose:	An example of deriving an exception from JException. 
            An exception being thrown when timeout occurs. Useful to distinguish it from other general cases, to allow corrective action.          
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#pragma once

#include "JException.h"

class TimeoutException : public JException {

	friend class ExceptionFactory;

public:

	/*
	 * Instantiates an exception.
	 *
	 * Parameter: const string deviceName - name of the device on which timeout has occurred
     * Access   : public
	 */
	TimeoutException(const string deviceName) : JException("Timeout occurred on " + deviceName) {}

	TimeoutException(const TimeoutException& other) : JException(other) {}

	TimeoutException& operator = (const TimeoutException& other);

	virtual ~TimeoutException() {}

protected:

    virtual const string& GetMyClassName() const;

    TimeoutException(const int skipFrames, const string& cause, const string& preStackTrace) : JException(skipFrames, cause, preStackTrace) {};

private:

    // Unique identifier for TimeoutException class
    static const string TOE_CLASS_NAME;

};
