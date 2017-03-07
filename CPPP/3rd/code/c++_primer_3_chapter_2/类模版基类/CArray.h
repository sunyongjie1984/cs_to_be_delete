#include <cassert>
#include <iostream>
#include <string>
template <class elemType>
class CArray {
public:
    friend std::ostream& operator<<(std::ostream& os, const CArray& arr) 
    {
        for (int i = 0; i != arr.size(); i++)
        {
            os << arr[i] << ' ';
        }
        return os;
    }
public:
    explicit CArray(int sz = DefaultArraySize)
    //CArray(int sz = DefaultArraySize)
    {
        Init(0, sz);
    }
    CArray(elemType* arr, int array_size)
    {
        Init(arr, array_size);
    }
    CArray(const CArray& rhs)
    {
        Init(rhs.ia, rhs.m_iSize);
    }
    ~CArray()
    {
        delete[] ia;
    }
public:
    int size() const
    {
        return m_iSize; 
    }
    virtual elemType& operator[](int index) const
    {
        assert(index >= 0 && index < size());
        return ia[index];
	}
	bool operator==(const CArray&) const;
	bool operator!=(const CArray&) const;
	CArray& operator=(const CArray&);
protected:
	void Init(elemType* arr, int sz);
	int m_iSize;
	elemType* ia;
    static const int DefaultArraySize = 12;
};

template <class elemType>
void CArray<elemType>::Init(elemType* arr, int sz)
{
	m_iSize = sz;
	ia = new elemType[m_iSize];
	for (int ix = 0; ix != m_iSize; ix++)
	{
		if (!arr)
		{
			//ia[ix] = 0; // 这是原来的CIntArray的写法，这不能用，当elemType为string时

			// 用这两个语句代替下面的一个语句在elemType没有默认构造函数的时候会崩溃，比如elemType为int类型
			//elemType a; // 为string时，a为一个空字符串，调用了string类的默认构造函数，这样定义当用于内置类型时
			//ia[ix] = a; // 因为内置类型在函数内部定义时，是不初始化的，在执行这个语句处就会崩溃

			//elemType b = elemType(); // 这样做是可以的，好像是内置类型这样定义初始化为它的相当于外部定义时的默认值
			//ia[ix] = b;              // 对于设计良好的类类型也就是有默认构造函数的类型，它会调用默认构造函数初始化这个对象

			ia[ix] = elemType();   // 这样写与上面是等价的，可是问题是构造函数不是不返回值吗，怎么可以用来给别的对象赋值呢？
			// c++ primer 3 page70每种内置数据类型都支持一种特殊的构造函数语法，可将对象初始化为0。
			// int ival = int();
			// double dval = double();
		}
		else
		{
			ia[ix] = arr[ix];
		}
	}
}
