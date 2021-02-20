// Participant: Long Duong
// Date: 02-12-21
// Description: Provides an input function that look for input of a particular type.

#ifndef PROJ1_INPUTTYPE_H
#define PROJ1_INPUTTYPE_H

#include <iostream>
#include <string>

using namespace std;
/// Credit: Based largely on Prof. Hester Tools.cpp

// Preconditions: A well formed prompt and an inputable type parameter represents the expected input type.
// Postconditions: The user input is returned in type provided.
template <typename T>
T inputType(string prompt)
{
    while (true)
    {
        T input;
        cout << prompt;
        cin >> input;
        cin.ignore(999, '\n');
        if (!cin.fail())
            return input;
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Input Failure! Try again" << endl;
    }
}

#endif //PROJ1_INPUTTYPE_H
