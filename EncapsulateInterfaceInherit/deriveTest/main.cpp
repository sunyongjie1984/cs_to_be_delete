class A {
public:
	int a;
protected:
	int Getb();
	int b;
private:
	int c;
};

A::Getb()
{
	return 10;
}

class B : public A{
public:
B();
};
B::B()
{
	int i = A::Getb();
//	int i = Getb();
}


int main()
{
	B test;
//	int i = test.Getb();
	return 0;
}