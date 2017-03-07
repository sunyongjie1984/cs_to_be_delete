#include "TimeoutException.h"


const string TimeoutException::TOE_CLASS_NAME = "TimeoutException";

const string& TimeoutException::GetMyClassName() const
{
	return TOE_CLASS_NAME;
}

TimeoutException& TimeoutException::operator=( const TimeoutException& other )
{
	JException::operator=(other);  // Call base class assignment operator
	return *this;
}