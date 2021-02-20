// Names: Gabriela Lopez, Andrew Thompson, Duyen Tran, Long Duong, Christopher Gomez, Gia Minh Hoang, and Lincoln Nguyen
// Date: 02-12-21
// Description: Implementation of various non-templated functions that output the display width of various types.

#include "MixedColumn.h"

using namespace std;


// Preconditions: A c-string.
// Postconditions: The width it takes to display the string on screen.
size_t displayLength(const char* cStr)
{
    return strlen(cStr);
}

// Preconditions: A wide c-string
// Postconditions: The width it takes to display the string on screen.
size_t displayLength(const wchar_t* cStr)
{
    return wcslen(cStr);
}

// Preconditions: A wide cpp-string
// Postconditions: The width it takes to display the string on screen.
size_t displayLength(wstring WideStr)
{
    return WideStr.size();
}

// Preconditions: A char type.
// Postconditions: The width it takes to display the character on screen.
size_t displayLength(char)
{
    return 1;
}
