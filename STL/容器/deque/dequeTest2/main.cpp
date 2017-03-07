#include <deque>
#include <iostream>
class CDequeInfo{
public:
	unsigned int p;
	unsigned int n;
};

class CTempData{
public:
	CTempData()
	{
		m_dWave = 0;
		m_dResult = 0;
		m_iState = 0;
	}
	double m_dWave;
	double m_dResult;
	unsigned int m_iState;
};

std::deque<CTempData > m_v_data;
CDequeInfo m_dequeInfo;

unsigned int GetVectoriterator()
{
	m_dequeInfo.p = (unsigned int)(&m_v_data.begin()); // 自定义类型的双端队列的指向第一个元素的迭代器的地址，它被子强制转化为了一个无符号整型，因为它们都是四个字节的整数。我认为。
	m_dequeInfo.n = (unsigned int)m_v_data.size();
	return (unsigned int)(&m_dequeInfo);
}

int main()
{
	CTempData a; a.m_dWave = 1.1;
	CTempData b; b.m_dWave = 1.2;
	CTempData c; c.m_dWave = 1.3;
	m_v_data.push_back(a); m_v_data.push_back(b); m_v_data.push_back(c);
	
	const CDequeInfo* const pDequeInfo = (CDequeInfo*)GetVectoriterator();
	std::deque<CTempData>::const_iterator p = *((std::deque<CTempData>::const_iterator*)pDequeInfo->p);
	for (int i = 0; i < pDequeInfo->n; i++, p++)
	{
		std::cout << p->m_dWave << std::endl;
	}
	return 0;
}

//	for (;p != m_v_data.end(); p++)
//	{
//		std::cout << p->m_dWave << std::endl;
//	}