#include "myException.h"

myException::myException(int errCode,const string& errMsg)
{
	initVars();
	errorCode = errCode;
	if ( errMsg[0] ) errorMsg.append(errMsg);
}

void myException::initVars()
{
	errorCode = 0;
	errorMsg = "";
}

void myException::response()
{
	winLog << "Error detect: " << endl;
	winLog << "		==> error code: " << errorCode << endl;
	winLog << "		==> error message: " << errorMsg << endl;

	cout << "Error detect: " << endl;
	cout << "		==> error code: " << errorCode << endl;
	cout << "		==> error message: " << errorMsg << endl;
	cout.flush();
}