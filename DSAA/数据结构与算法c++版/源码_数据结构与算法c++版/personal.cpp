#include <iostream>
#include "personal.h"

Personal::Personal() : nameLen(10), cityLen(10) {
    name = new char[nameLen+1];
    city = new char[cityLen+1];
}

Personal::Personal(char *ssn, char *n, char *c, int y, long s) :
        nameLen(10), cityLen(10) {
    name = new char[nameLen+1];
    city = new char[cityLen+1];
    strcpy(SSN,ssn);
    strcpy(name,n);
    strcpy(city,c);
    year = y;
    salary = s;
}

void Personal::writeToFile(fstream& out) const {
    out.write(SSN,9);
    out.write(name,nameLen);
    out.write(city,cityLen);
    out.write(reinterpret_cast<const char*>(&year),sizeof(int));
    out.write(reinterpret_cast<const char*>(&salary),sizeof(int));
}

void Personal::readFromFile(fstream& in) {
    in.read(SSN,9);
    in.read(name,nameLen);
    in.read(city,cityLen);
    in.read(reinterpret_cast<char*>(&year),sizeof(int));
    in.read(reinterpret_cast<char*>(&salary),sizeof(int));
}

void Personal::readKey() {
    char s[80];
    cout << "Enter SSN: ";
    cin.getline(s,80);
    strncpy(SSN,s,9);
}

ostream& Personal::writeLegibly(ostream& out) {
    SSN[9] = name[nameLen] = city[cityLen] = '\0';
    out << "SSN = " << SSN << ", name = " << name
        << ", city = " << city << ", year = " << year
        << ", salary = " << salary;
    return out;
}

istream& Personal::readFromConsole(istream& in) {
    char s[80];
    cout << "SSN: ";
    in.getline(s,80);
    strncpy(SSN,s,9);
		cout<<'['<<SSN<<']';
    cout << "Name: ";
    in.getline(s,80);
    strncpy(name,s,nameLen);
		cout<<'['<<name<<']';
    cout << "City: ";
    in.getline(s,80);
    strncpy(city,s,cityLen);
		cout<<'['<<city<<']';
    cout << "Birthyear: ";
    in >> year;
		cout<<'['<<year<<']';
    cout << "Salary: ";
    in >> salary;
		cout<<'['<<salary<<']';
	cin.ignore();
    return in;
}
