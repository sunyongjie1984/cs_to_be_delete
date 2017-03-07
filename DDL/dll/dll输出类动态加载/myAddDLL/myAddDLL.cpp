#include <iostream>
ExternC __declspec(dllexport) class CBook {
public:
	void print()
	{
		std::cout << "I Love China" << std::endl;
	}
};