#include <vector>
#include <iostream>
class CIntStack {
public:
    CIntStack(int capacity): m_stack(capacity), m_top(0)
    {

    }
    bool pop(int& value);
    bool push(int value);

    bool full();
    bool empty();
    void display();

    int size();
private:
    int m_top;
    std::vector<int> m_stack;
};

inline int CIntStack::size()
{
    return m_top;
}

inline bool CIntStack::empty()
{
    return m_top? false: true;
}

inline bool CIntStack::full()
{
    return m_top < m_stack.size() - 1 ? false : true;
}
