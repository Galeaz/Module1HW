// Names: Gabriela Lopez, Andrew Thompson, Duyen Tran, Long Duong, Christopher Gomez, Gia Minh Hoang, and Lincoln Nguyen
// Date: 02-12-21
// Description: Chapter 1 Solution

#include <iostream>
#include <string>
using namespace std;

#include "input.h"
#include "ASCIIConverter.h"
#include "Base_Converter.h"
#include "statisticsUI.h"

int menuOption();
void ASCIIConverter();
void baseConverter();
void descriptiveStatistics();

int main()
{
	do
	{
		switch (menuOption())
		{
		case 0:  exit(0);
		case 1:  system("cls"); ASCIIConverter();     break;
		case 2:  system("cls"); baseConverter();  break;
		case 3:  system("cls"); descriptiveStatistics();  break;
		default: cout << "\t\t    ERROR-Invalid Option. Please re-enter."; break;
		}
		cout << '\n';
		system("pause");
	} while (true);
	return 0;
}

//Precondition: N/A
//Postcondition: Prints menu and returns user int option selected
int menuOption()
{
	system("cls");
	cout << '\n';
	cout << '\t' << char(201) << string(42, char(205)) << char(187) << '\n';
	cout << '\t' << char(186) << "    \t    CMPR131: Chapter 1             " << char(186) << '\n';
	cout << '\t' << char(186) << "      \t\t  Made by:                 " << char(186) << '\n';
	cout << '\t' << char(186) << " - Gabriela Lopez\t- Andrew Thompson  " << char(186) << '\n';
	cout << '\t' << char(186) << " - Duyen Tran\t\t- Long Duong       " << char(186) << '\n';
	cout << '\t' << char(186) << " - Christopher Gomez\t- Gia Minh Hoang   " << char(186) << '\n';
	cout << '\t' << char(186) << " - Lincoln Nguyen                         " << char(186) << '\n';
	cout << "\t" << char(204) << string(42, char(205)) << char(185) << "\n";
	cout << "\t" << char(186) << "   1: ASCII Text to ASCII Numbers         " << char(186) << "\n";
	cout << "\t" << char(186) << "   2: Base Converter                      " << char(186) << "\n";
	cout << "\t" << char(186) << "   3: Descriptive Statistics              " << char(186) << "\n";
	cout << "\t" << char(199) << string(42, char(196)) << char(182) << "\n";
	cout << "\t" << char(186) << "   0: Exit                                " << char(186) << "\n";
	cout << "\t" << char(200) << string(42, char(205)) << char(188) << "\n";
	cout << "\t    Option: ";

	int option;
	cin >> option;
	cin.clear();
	cin.ignore(999, '\n');
	return option;
}

//Precondition: N/A
//Postcondition: Contains the ASCII Converter
void ASCIIConverter()
{
	using namespace Group1AC;
	int menuOption;
	vector<int>results;
	header();
	string textToConvert = getText();	
	do
	{
		menuOption = menu();
		switch (menuOption)
		{
			case 0: break;
			case 1: textToConvert = getText();     break;
			case 2: results = convertTextToNumber(textToConvert); break;
			case 3: copyToFile(results); break;
			case 4: readFile(); break;

			default: cout << "\t\t    ERROR-Invalid Option. Please re-enter."; break;
		}
		if (menuOption == 0)
			break;
		cout << '\n';
		system("pause");
	} while (true);
}

//Precondition: N/A
//Postcondition: Contains the Base Converter
void baseConverter()
{
	using namespace Group1BC;
	BaseConverterMain();
}

//Precondition: N/A
//Postcondition: Contains the Descriptive Statistics
void descriptiveStatistics()
{
	using namespace Group1DS;
	auto ui = StatsUI();
	ui.run();
}