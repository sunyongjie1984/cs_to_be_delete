#include <iostream>

class my_string {
public:
    friend std::ostream& operator<<(std::ostream&,
            const my_string&);
public:
    my_string(const char* str = NULL);
    my_string(const my_string& other);
    ~my_string(void);
    my_string& operator=(const my_string& other);
private:
    char* m_data;
};
