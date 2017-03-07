#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main()
{
	ifstream inputFile("d:\\a.txt");
	ofstream outputFile("d:\\b.txt");
	string word;
//	inputFile.close();
	inputFile >> word;
	outputFile << word;
	return 0;
}