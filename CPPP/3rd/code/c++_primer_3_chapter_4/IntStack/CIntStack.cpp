#include "CIntStack.h"
bool CIntStack::pop(int &top_value)
{
    if(empty())
    {
        return false;
    }
    else
    {

    }
    top_value = m_stack[--m_top];
    std::cout << "CIntStack::pop(): " << top_value << std::endl;
    return true;
}

bool CIntStack::push(int value)
{
    std::cout << "CIntStack::push( " << value << " )\n";
    if (full())
    {
        return false;
    }
    else
    {

    }
    m_stack[m_top++] = value;
    return true;
}

void CIntStack::display()
{
    if (!size())
    {
        std::cout << "(0)\n";
        return;
    }
    std::cout << "( " << size() << " )( bot: ";
    for (int ix = 0; ix < m_top; ix++)
    {
        std::cout << m_stack[ix] << " ";
    }
    std::cout << ":top )\n";
}
