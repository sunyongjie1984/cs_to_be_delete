// CALC.H - declares the CCalc class that is exported from the DLL
// and is imported in the EXE

#include <tchar.h>

#ifdef CALC_EXPORTS
#define CALC_API __declspec (dllexport)
#else
#define CALC_API __declspec (dllimport)
#endif

#define SOME_INSTN_BUF		260

class CALC_API CCalc
{
private:	
	TCHAR m_szLastUsedFunc[SOME_INSTN_BUF];

public:
	CCalc (); 
	
	int Add (int i, int j);
	int Sub (int i, int j);
	TCHAR* GetLastUsedFunc ();
	
};
