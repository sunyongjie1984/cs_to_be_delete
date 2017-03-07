// NOW, LETS CONTINUE WITH SOME MORE ADVANCED AND USEFULL EXCEPTION HANDLING.
// EH WITH CLASSES

/*INCLUDE HEADER FILES*/
#include <iostream>
#include <conio.h>
#include <string>
using namespace std; // VERY  IMPORTANT

class EHCLASS 
{ // MAKE THE CLASS

public:
	void error(char *e); 
private:
	char str[255];

}; // CLASS ENDS

int main()
{
	string gotostr;
begin:
	try 
	{
		system("cls");
		cout << "CTRL+C exits.\n";
		cout << "What is the name:  ";
		cin >> gotostr;
		if(gotostr == "Scooter" || gotostr == "scooter" || gotostr == "SCOOTER")
		{
			cout << "That is the right name.\n";
			getch();
			system("cls");
			return 0;
		}
		else 
		{
			throw gotostr;
		}
	}
	catch (string gotostr)
	{
		system("cls");
		cout << "Error, Press any key to try again.\n";
		getch();
		goto begin;
	}
}


