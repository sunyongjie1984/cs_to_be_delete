
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MYDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MYDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MYDLL_EXPORTS

	#define EXPORT extern "C" __declspec(dllexport)	///// 使用MFC提供的修饰符号__declspec(dllexport)
													   // 在要输出的函数、类、数据的声明前加上_declspec(dllexport)的
													   // 修饰符，表示输出。__declspec(dllexport)在C调用约定、C编译
													   // 情况下可以去掉输出函数名的下划线前缀。
													   // 在“C++”下定义“C”函数，需要加extern “C”关键词。
													   // 用extern "C"来指明该函数使用C编译方式。输出的“C”函数可以从“C”代码里调用

#else

	#define EXPORT __declspec(dllexport)

#endif

EXPORT BOOL CALLBACK MyMsgBox();
EXPORT BOOL CALLBACK aMsgBoxA( HWND   hwnd,
							   LPCSTR lpText,
							   LPCSTR lpCaption );

