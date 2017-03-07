_declspec(dllimport) int add(const int& a, const int& b); // 不写这些东西，编译器不产生.lib文件。

class _declspec(dllexport) CBook {
public:
	void print();
};