int const i = 30; // 这个const对象i是常量表达式，定义在这里是对的

int func(int i)
{
	return i + 20;
}

int const ii = func(i); // ii应该定义在源文件中，在头文件中extern，别的文件要用包含这个头文件。