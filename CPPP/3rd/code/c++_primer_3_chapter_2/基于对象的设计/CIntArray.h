#include <cassert>
#include <iostream>
class CIntArray {
public:
    // friend std::ostream& operator<<(std::ostream& os, CIntArray& arr);
    // 开始的时候不知道为什么右操作数不能为const CIntArray，后来发现我没有把函数CIntArray::operator[]定义为const成员函数，
    // 因为const对象只能调用const成员函数，所以当arr为const对象时，它是不能调用operator[]这个函数的，所以arr[i]会报错。
    friend std::ostream& operator<<(std::ostream& os, const CIntArray& arr) 
    {
        for (int i = 0; i != arr.size(); i++)
        {
            os << arr[i] << ' ';
        }
        return os;
    }
public:
    explicit CIntArray(int sz = DefaultArraySize);
    CIntArray(int* array, int array_size);
    CIntArray(const CIntArray& rhs);
    ~CIntArray()
    {
        delete[] ia;
    }
	bool operator==(const CIntArray&) const;
	bool operator!=(const CIntArray&) const;
	CIntArray& operator=(const CIntArray&);
    int size() const
    {
        return m_iSize; // 内联函数不会引入任何函数调用。
    }
    int& operator[](int index) const
    {
        assert(index >= 0 && index <size());
        return ia[index];
    }
protected:
    void Init(int* arr, int sz);
    int m_iSize;
    int* ia;
    static const int DefaultArraySize = 12;
};