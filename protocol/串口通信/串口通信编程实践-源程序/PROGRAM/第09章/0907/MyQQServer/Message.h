#ifndef _MESSAGE_H
#define _MESSAGE_H
struct Message
{
public:
	int iType;
	int iSubType;
	char strName[20];
	char strContent[1024];
	char strClientName[20];
	
};
#endif