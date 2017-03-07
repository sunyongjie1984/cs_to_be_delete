// A basic example of Exception Handling using try, throw, and catch (don't expect this to ammount to much in your program.

/*INCLUDE HEADER FILES*/
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	system("cls"); // NOT MANDATORY FOR EXCEPTION HANDLING; ONLY CLEARS THE SCREEN
	cout << "Welcome to Exception Handling.\n"; 

	try 
	{ // THIS BEGINS THE try BLOCK.
		cout << "You are inside a try block.\n";
		throw 1; // throw ERROR, CAN BE ANY RANDOM INT IN THIS EXAMPLE.
		cout << "This is random string that won't amount to any thing.\n"; // ANY CODE AFTER throw WILL NOT BE READ.
	} // ENDS try BLOCK

	catch (int n) 
	{ // CATCHES ERROR SENT BY throw 
		cout << "The value you sent me is:  " << n << "\nPress any key to continue."; // catch CATCHES THE VALUE SENT BY throw. 
			getch(); // PAUSES OUTPUT.
	}
	system("cls");
	cout << "You now know how to use basic Exception Handling in C++.\nRefer to the other files for more on Exception Handling.\n\n";
	return 0;
}

