#include <iostream>
#include <conio.h>
using namespace std;

class interror
{
public:
	char str_error[80];
	int why1;

	interror() 
	{
		*str_error = 0; why1 = 0;
	}

	interror(char *e, int w)
	{
		strcpy(str_error, e);
		why1 = w;
	}

};

int main()
{
	int i;
	int n;
	try
	{
		cout << "Enter a denominator:  ";  // When you run this program enter 0.
		cin >> n;
		if (n == 0)
		{
			throw interror("Cannot divide by: ", n);
		}
		else
		{
			i=100/n;
			cout << "The answer is "  << i << "Press any key to continue.\n";
			getch();
		}
	}
	catch (interror e) 
	{
		cout << e.str_error << ":  ";
		cout << e.why1 << "\n";
		getch();
	}

	return 0;
}
