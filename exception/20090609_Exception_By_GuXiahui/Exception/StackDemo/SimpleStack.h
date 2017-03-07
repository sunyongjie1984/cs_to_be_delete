// SimpleStack.h: interface for the SimpleStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLESTACK_H__F26D0F11_15BB_4CF5_B8D8_500B1841C91F__INCLUDED_)
#define AFX_SIMPLESTACK_H__F26D0F11_15BB_4CF5_B8D8_500B1841C91F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
template<class T>
class SimpleStack  
{
public:
	SimpleStack();
	virtual ~SimpleStack();
	SimpleStack(const SimpleStack&);
	SimpleStack& operator=(const SimpleStack&);
	size_t Count() const;
	void Push(const T&);
	T Pop();
// 	 void Pop();
// 	 T Top();
private:
	T* NewCopy(T* src, size_t srcSize, size_t destSize);
private:
	T* m_v;
	size_t m_vSize;
	size_t m_vUsed;
};

#endif // !defined(AFX_SIMPLESTACK_H__F26D0F11_15BB_4CF5_B8D8_500B1841C91F__INCLUDED_)
