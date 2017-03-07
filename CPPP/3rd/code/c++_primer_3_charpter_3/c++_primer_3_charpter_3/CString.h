#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
class CString;
std::istream& operator>>(std::istream&, CString&);
std::ostream& operator<<(std::ostream&, const CString&);
class CString {
public:
	//friend std::istream& operator>>(std::istream&, CString&);
	//friend std::ostream& operator<<(std::ostream&, const CString&);
	CString();					// CString str1;
	CString(const char*);       // CString str2("literal");
	CString(const CString&);    // CString str3(str2);
	~CString();

	CString& operator=(const CString&); // str1 = str2;
	CString& operator=(const char*);    // str3 = "literal string";

	inline bool operator==(const CString&);    // str1 == str2;
	inline bool operator==(const char*);       // str3 == "literal string";

	char& operator[](int) const;

	int size() const
	{
		return m_size;
	}
	char* c_str() const
	{
		return m_string;
	}
private:
	int m_size;
	char* m_string;
};

bool CString::operator==(const CString& rhs) // 想要inline又不想放在类定义体中有放在这里，因为inline的必须放在一个文件中。
{
	if (m_size != rhs.m_size)
	{
		return false;
	}
	else
	{
		return strcmp(m_string, rhs.m_string)? false: true;
	}
}

bool CString::operator ==(const char* s)
{
	return strcmp(m_string, s)? false: true;
}