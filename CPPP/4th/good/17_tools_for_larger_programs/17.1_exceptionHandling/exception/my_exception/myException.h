#ifndef SUNYONGJIE_EXCEPTION
#define SUNYONGJIE_EXCEPTION
#include <stdexcept>

class CMyException: public std::logic_error
{
public:
	explicit CMyException(std::string const & s):
		std::logic_error(s) { }

	CMyException(std::string const & s,
			std::string const & lhs, std::string const & rhs):
		std::logic_error(s), left(lhs), right(rhs) { }

	// this member data can be initialized not assigned
	// it is a necessary for a construcor initialize list
	const std::string left;

	std::string right;

	// myref(section)(exceptSpec) explains the destructor and why we need one
	virtual ~CMyException() throw() { }
};

class CMyException2: public std::logic_error
{
public:
	CMyException2(int const & i) : std::logic_error("hehe") { }
	~CMyException2() throw() { }
};

class CMyException3 : public std::exception {
public:
	CMyException3() { }
	~CMyException3() throw() { }
};


#endif
