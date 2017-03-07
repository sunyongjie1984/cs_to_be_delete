#include <exception>
#include <string>
class CMyException : public exception {
public:
	CMyException(string s) : info(s) { }
	~CMyException() throw() { }
	string info;
};
