// Name: Gabriela Lopez
// Date: 02-12-21
// Description: Chapter 1 - ASCII Text to ASCII Number Converter

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace GabyL1
{
	//Precondition: N/A
	//Postcondition: Prints header
	void header()
	{
		system("cls");
		cout << '\n';
		cout << '\t' << char(201) << string(42, char(205)) << char(187) << '\n';
		cout << '\t' << char(186) << "    CMPR131: Chapter 1 - ASCII Converter  " << char(186) << '\n';
		cout << '\t' << char(186) << "      \t\t  Made by:                 " << char(186) << '\n';
		cout << '\t' << char(186) << " - Gabriela Lopez\t- Andrew Thompson  " << char(186) << '\n';
		cout << '\t' << char(186) << " - Duyen Tran\t\t- Long Duong       " << char(186) << '\n';
		cout << '\t' << char(186) << " - Christopher Gomez\t- Gia Minh Hoang   " << char(186) << '\n';
		cout << '\t' << char(186) << " - Lincoln Nguyen                         " << char(186) << '\n';
		cout << '\t' << char(200) << string(42, char(205)) << char(188) << "\n\n";
	}

	//Precondition: N/A
	//Postcondition: Returns the text to convert into numbers
	string getText()
	{
		cout << "\n Please enter text to be converted: ";
		string text;
		getline(cin, text);
		return text;
	}

	//Precondition: N/A
	//Postcondition: Prints menu and returns user int option selected
	int menu()
	{
		cout << "\n 1: Enter a new text\n";
		cout << " 2: Convert the text to ASCII numbers\n";
		cout << " 3: Save ASCII numbers into a binary file\n";
		cout << " 4: Read the binary file\n";
		cout << " 0: Exit\n";
		cout << " Option: ";

		int option;
		cin >> option;
		cin.clear();
		cin.ignore(999, '\n');
		return option;
	}

	//Precondition: This function needs a string to convert
	//Postcondition: Prints result and returns an int vector with the result
	vector<int> convertTextToNumber(string text)
	{
		vector<int> data;
		int result;
		cout << "\n Your text:\n";
		cout << ' ' << text << '\n';
		cout << " Result in decimal value:\n ";

		for (int index = 0; index < text.size(); index++)
		{
			result = (int)text[index];
			data.push_back(result);
		}

		for (int index = 0; index < data.size(); index++)
			cout << data[index] << ' ';
		cout << '\n';

		return data;
	}

	//Precondition: Needs an int vector that will be written into a file
	//Postcondition: N/A
	void copyToFile(vector<int> data)
	{
		if (data.empty())
			cout << "\n ERROR: Empty binary text.\n";
		else
		{
			ofstream writeToFile;
			writeToFile.open("data.bin");
			for (int index = 0; index < data.size(); index++)
				writeToFile << data[index] << ' ';
			writeToFile.close();
			cout << "\n Data successfully saved in data.bin\n";
		}
	}

	//Precondition: N/A
	//Postcondition: Prints data from binary file, validates existence of file and emptiness of file
	void readFile()
	{
		string value;
		ifstream file("data.bin");
		if (file.is_open())
		{
			if (file.peek() == ifstream::traits_type::eof())
				cout << "\n ERROR: The file is empty.\n";
			else
			{
				cout << '\n';
				while (getline(file, value))
					cout << value << ' ';
				cout << '\n';
			}
			file.close();
		}
		else
			cout << "\n ERROR: Unable to open file.\n";
	}
}




/*
//Precondition: N/A
//Postcondition: Returns a bool answer from the user to repeat program
bool repeat()
{
	char answer = inputChar("\n Do you want to do it again? (Y/N): ", 'y', 'n');
	if (answer == 'n' || answer == 'N')
		return false;
	else
	{
		cin.ignore(999,'\n');
		return true;
	}
}

//Precondition: N/A
//Postcondition: Returns a bool answer from the user to save data in a file
	bool saveData()
	{
		char answer = inputChar("\n Do you want to save your data? (Y/N): ", 'y', 'n');
		if (answer == 'n' || answer == 'N')
			return false;
		else
		{
			cin.ignore(999, '\n');
			return true;
		}
	}

used in main.cpp
if(saveData()) 
	copyToFile(results);
*/