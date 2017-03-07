bool (*pf)(const int&, const int&); // 定义了一个函数指针
bool* ppf(const int&, const int&);   // 定义了一个函数

// 该定义表示cmpFcn为一种指向函数的指针类型名字。
// cmpFcn为一种类型名。可以用来定义对象的。
// 该类型为，指向返回值为bool类型并带有两个const int引用形参的函数的指针。
typedef bool (*cmpFcn)(int const &, int const &);

bool aaa(int const & a, int const & b)
{
	return 1;
}

int main()
{
	// 指向函数的指针的初始化与赋值
	// 在引用函数名又没有调用该函数时，函数名被自动解释为指向函数的指针。
	// bool lengthCompare(string const &, string const &); 被解释为
	// bool (*)(string const &, string const &);
	// 可以使用函数名对函数指针初始化
	
	return 0;
}