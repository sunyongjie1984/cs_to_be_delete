#ifndef CARRAYRC_SUNYONGJIE_20101204
#define CARRAYRC_SUNYONGJIE_20101204
#include "CArray.h"
template <class elemType>
class CArrayRC: public CArray<elemType> {
public:
	CArrayRC(int sz = CArray<elemType>::DefaultArraySize): CArray<elemType>(sz)
	{

	}
	CArrayRC(elemType* ia, int sz): CArray<elemType>(ia, sz)
	{

	}
	CArrayRC(const CArray& rhs): CArray<elemType>(rhs)
	{

	}
	virtual elemType& operator[](int index) // 这个在这里定上就没有用了吧，不是和基类的一样么
	{
		assert((index >= 0) && (index < CArray<elemType>::size()));
		return ia[index];
	}
};
#endif