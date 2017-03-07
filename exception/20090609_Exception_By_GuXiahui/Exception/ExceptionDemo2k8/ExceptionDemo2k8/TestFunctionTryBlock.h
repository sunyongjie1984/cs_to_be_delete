#pragma once
class A{
public:
	A()
	{
		throw 1;
	}
};
class B{
public:
	B()
	{
		throw 2;
	}
};
class TestFunctionTryBlock: private A
{
public:
	TestFunctionTryBlock(void) throw();
	~TestFunctionTryBlock(void);
private:
	B m_b;
};
