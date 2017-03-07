#include <string.h>
#include <iostream>
class String {
public:
	friend std::ostream& operator<<(std::ostream&,
			const String&);
public:
	String(const char* str = NULL);
	String(const String& other);
	~String(void);
	String& operator=(const String& other);
private:
	char* m_data;
};
