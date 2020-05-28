#include <iostream>
#include <fstream>

#include "Smezhnost'.h"

using namespace std;


int main()
{
	ifstream file;
	file.open("input.txt");
	file.unsetf(ios::skipws);
	string tempS;
	char tempC;
	ListOfSmezh timetable;
	while (!file.eof())
	{
		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		string source = tempS;
		if (timetable.contains(source) == false)
			timetable.newNode(source);
		tempS.clear();

		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		string stock = tempS;
		if(timetable.contains(stock) == false)
			timetable.newNode(stock);
		tempS.clear();

		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		if (tempS != "N/A")
		{
			float value = stof(tempS);
			timetable.newPath(source, stock, value);
		}
		tempS.clear();

		file >> tempC;
		while (tempC != '\n' && !file.eof())
		{
			tempS += tempC;
			file >> tempC;
		}
		if (tempS != "N/A")
		{
			float value = stof(tempS);
			timetable.newPath(source, stock, value);
		}
		tempS.clear();
	}
	timetable.print();
	cout << timetable.algorhytm("A", "F");
}