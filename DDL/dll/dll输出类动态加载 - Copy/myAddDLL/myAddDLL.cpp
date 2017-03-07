#include <iostream>
class _declspec(dllexport) CBook {
public:
	void print()
	{
		std::cout << "I Love China" << std::endl;
	}
};