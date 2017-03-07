#include <iostream>
using namespace std;
enum NEW_SERV_ID
{
	NSID_SERV_NULL = 0,
	
	NSID_SERV254 = 254,
	NSID_SERV255 = 255,
	NSID_BUTT
};

unsigned char GetNsid(char nsid)
{
	return (nsid);
}
int main()
{
	cout << GetNsid(NSID_SERV_NULL)<< ' '
		 << GetNsid(NSID_SERV255)<<' '
		 << GetNsid(NSID_BUTT)<< endl;
	return 0;
}

