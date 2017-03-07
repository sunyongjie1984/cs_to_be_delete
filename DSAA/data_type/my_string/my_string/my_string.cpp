#include "my_string.h"

std::ostream& operator<<(std::ostream& os, const my_string& str)
{
    os << str.m_data;
    return os;
}

my_string::~my_string(void)
{
    delete [] m_data;
}

my_string::my_string(const char* str)
{
    if (str == NULL)
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    else
    {
        int length = strlen(str);
        m_data = new char[length + 1];
        strcpy(m_data, str);
    }
}

my_string::my_string(const my_string& other)
{
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy(m_data, other.m_data);
}

my_string& my_string::operator =(const my_string& other)
{
    if (this == &other)
        return *this;
    delete [] m_data;
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy(m_data, other.m_data);
    return *this;
}
