#pragma once
// Participants: Gia Minh Hoang, Andrew Thompson, and Gabriela Lopez
// Date: 02-12-21
// Description: Chapter 1 - Base Converter

#include<iostream>
#include <string>
#include <vector>
#include "input.h"

using namespace std;

namespace Group1BC
{
	//Precondition: N/A
	//Postcondition: Prints header
	void header()
	{
		system("cls");
		cout << '\n';
		cout << '\t' << char(201) << string(42, char(205)) << char(187) << '\n';
		cout << '\t' << char(186) << "    CMPR131: Chapter 1 - Base Converter   " << char(186) << '\n';
		cout << '\t' << char(186) << "      \t\t  Made by:                 " << char(186) << '\n';
		cout << '\t' << char(186) << " - Gabriela Lopez\t- Andrew Thompson  " << char(186) << '\n';
		cout << '\t' << char(186) << " - Duyen Tran\t\t- Long Duong       " << char(186) << '\n';
		cout << '\t' << char(186) << " - Christopher Gomez\t- Gia Minh Hoang   " << char(186) << '\n';
		cout << '\t' << char(186) << " - Lincoln Nguyen                         " << char(186) << '\n';
		cout << '\t' << char(200) << string(42, char(205)) << char(188) << "\n\n";
	}

	//Precondition: N/A
	//Postcondition: Print the question and get user input
	void getInput(int& num, int& check)
	{
		num = inputInteger("\n\tEnter an integer number of base 10: ");
		cout << "\n";
		check = 1;
	}

	//Precondition: This function needs a vector, and 2 int input
	//Postcondition: Return the Vector with the remainder
	void getRemainder(vector<int>& temp, int num, int base)
	{
		int remain = 0;
		if (num == 0)
			temp.push_back(0);
		else
		{
			for (int i = 0; num > 0; i++)
			{
				remain = num % base;
				num = num / base;
				temp.push_back(remain);
			}
		}
	}

	//Precondition: This function needs a vector, and 2 int inputs
	//Postcondition: Print the results and the input base from the user, or convert the results to Character 
	// if it's greater or equal to 10 and lesser or equal to 36
	void Convert(vector<int> temp, int num, int base, int check)
	{
		if (check == -1)
			cout << "\n\tERROR: No input integer has been entered.\n\n";
		else
		{
			base = inputInteger("\n\tEnter the base (2..36) to convert to:", 2, 36);

			int ifPositive = 0;
			int num2 = 0;

			if (num < 0)
			{
				ifPositive = -1;
				num2 = num * -1;
			}
			else
				num2 = num;

			if (ifPositive == -1)
				cout << "\n\t" << num << " (base of 10) = -";
			else
				cout << "\n\t" << num << " (base of 10) = ";

			getRemainder(temp, num2, base);

			reverse(temp.begin(), temp.end());

			for (int i = 0; i < temp.size(); i++)
			{
				int alphabet;
				if (temp[i] >= 10 && temp[i] <= 36)
				{
					alphabet = temp[i] - 10;
					switch (alphabet)
					{
					case 0: cout << 'A'; break;
					case 1: cout << 'B'; break;
					case 2: cout << 'C'; break;
					case 3: cout << 'D'; break;
					case 4: cout << 'E'; break;
					case 5: cout << 'F'; break;
					case 6: cout << 'G'; break;
					case 7: cout << 'H'; break;
					case 8: cout << 'I'; break;
					case 9: cout << 'J'; break;
					case 10: cout << 'K'; break;
					case 11: cout << 'L'; break;
					case 12: cout << 'M'; break;
					case 13: cout << 'N'; break;
					case 14: cout << 'O'; break;
					case 15: cout << 'P'; break;
					case 16: cout << 'Q'; break;
					case 17: cout << 'R'; break;
					case 18: cout << 'S'; break;
					case 19: cout << 'T'; break;
					case 20: cout << 'U'; break;
					case 21: cout << 'V'; break;
					case 22: cout << 'W'; break;
					case 23: cout << 'X'; break;
					case 24: cout << 'Y'; break;
					case 25: cout << 'Z'; break;
					default:;
					}
				}
				else
					cout << temp[i];
			}
			cout << " (base of " << base << ")\n\n";
		}
		system("pause");
	}

	//Precondition: This function needs a vector, and 2 int input
	//Postcondition: Print the results of all bases, and convert the results to Character 
	// if it's greater or equal to 10 and lesser or equal to 36
	void allBase(vector<int> temp, int num, int base, int check)
	{
		if (check == -1)
			cout << "\n\tERROR: No input integer has been entered.\n\n";
		else
		{
			int ifPositive = 0;
			int num2 = 0;

			if (num < 0)
			{
				ifPositive = -1;
				num2 = num * -1;
			}
			else
				num2 = num;

			if (ifPositive == -1)
				cout << "\n\t" << num << " (base of 10) = \n";
			else
				cout << "\n\t" << num << " (base of 10) = \n";

			for (int allBase = 2; allBase <= 36; allBase++)
			{
				temp.clear();
				getRemainder(temp, num2, allBase);

				reverse(temp.begin(), temp.end());

				if (ifPositive == -1)
					cout << "\t\t-";
				else
					cout << "\t\t";

				for (int i = 0; i < temp.size(); i++)
				{
					int alphabet;
					if (temp[i] >= 10 && temp[i] <= 36)
					{
						alphabet = temp[i] - 10;
						switch (alphabet)
						{
						case 0: cout << 'A'; break;
						case 1: cout << 'B'; break;
						case 2: cout << 'C'; break;
						case 3: cout << 'D'; break;
						case 4: cout << 'E'; break;
						case 5: cout << 'F'; break;
						case 6: cout << 'G'; break;
						case 7: cout << 'H'; break;
						case 8: cout << 'I'; break;
						case 9: cout << 'J'; break;
						case 10: cout << 'K'; break;
						case 11: cout << 'L'; break;
						case 12: cout << 'M'; break;
						case 13: cout << 'N'; break;
						case 14: cout << 'O'; break;
						case 15: cout << 'P'; break;
						case 16: cout << 'Q'; break;
						case 17: cout << 'R'; break;
						case 18: cout << 'S'; break;
						case 19: cout << 'T'; break;
						case 20: cout << 'U'; break;
						case 21: cout << 'V'; break;
						case 22: cout << 'W'; break;
						case 23: cout << 'X'; break;
						case 24: cout << 'Y'; break;
						case 25: cout << 'Z'; break;
						default:;
						}
					}
					else
						cout << temp[i];
				}
				if (allBase == 2)
					cout << " (base of " << allBase << " - binary)\n";
				else if (allBase == 8)
					cout << " (base of " << allBase << "  - octal)\n";
				else if (allBase == 16)
					cout << " (base of " << allBase << " - hex)\n";
				else
					cout << " (base of " << allBase << ")\n";
			}
			cout << "\n";
		}
		system("pause");
	}

	//Precondition: N/A
	//Postcondition: Prints GUI
	int BaseConverterMain()
	{
		int num = 0, base = 0, check = -1;
		vector<int> temp;
		string optionAllowed = "abcx";
		do
		{
			header();
			cout << "==========================================================\n";
			cout << "\tA> Enter an integer number (base 10)\n";
			cout << "\tB> Specify and converting base\n";
			cout << "\tC> Display all converted bases (2..36)\n";
			cout << "-----------------------------------------------------------\n";
			cout << "\tX> Return\n";
			cout << "==========================================================\n";
			char option = inputChar("\tOption:", optionAllowed);

			switch (toupper(option))
			{
			case 'A': getInput(num, check); break;
			case 'B': Convert(temp, num, base, check); break;
			case 'C': allBase(temp, num, base, check); break;
			case 'X': return 0; break;
			default:;
			}
		} while (true);
		return 0;
	}
}