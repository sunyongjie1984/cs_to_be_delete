class Foo 
{
public:
	Foo(int x) 
	{ 
		value = x;
	}
	int get() 
	{
		return value;
	}
private:
	int value;
};
