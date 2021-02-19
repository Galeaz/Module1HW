#pragma once
// gia minh 
// 02/13/2021

#include<iostream>
#include <string>
#include <vector>

using namespace std;

void getInput(int& num)
{
	cout << "\n\tEnter an integer number of base 10: ";
	cin >> num;
}

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
void Convert(vector<int> temp,int num, int base)
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
void allBase(vector<int> temp, int num, int base)
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

int BaseConverterMain(int num, int base)
{
	vector<int> temp;
	do
	{
		cout << "\t2> Base Converter\n";
		cout << "==========================================================\n";
		cout << "\tA> Enter an integer number (base 10)\n";
		cout << "\tB> Specify and converting base\n";
		cout << "\tC> Display all converted bases (2..36)\n";
		cout << "-----------------------------------------------------------\n";
		cout << "\t 0> Return\n";
		cout << "==========================================================\n";
		cout << "\tOption:";
		char option;
		cin >> option;

		switch (toupper(option))
		{
		case 'A': getInput(num); break;
		case 'B': Convert(temp, num, base); break;
		case 'C': allBase(temp, num, base); break;
		default:;
		}
	} while (true);

	return 0;
}

