#include "window.h"
#include "dll.h"
#include "stdafx.h"
extern "C" __declspec(dllexport) int fun(int x1, int x2, int x3)
{
	return x1 + x2 + x3;
}