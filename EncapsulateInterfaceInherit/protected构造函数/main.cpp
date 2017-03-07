class A 
{
protected:
	A();
};
int main()
{
	A* p; // ok
	A q;  // error
	return 0;
}