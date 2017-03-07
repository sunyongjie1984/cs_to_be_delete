void fun(int i)
{
	return;
}
/*
void fun(int const i)
{
	return;
}
*/
void fun2(const int* i) // fun2可以构成重载，fun1不可以构成重载。
{
	return;
}

void fun2(int* i)
{
	return;
}
int main()
{
	int i = 3;
	fun(i);
	fun(i);

	int* p = &i;
	fun2(p);
	fun2(p);
	return 0;
}