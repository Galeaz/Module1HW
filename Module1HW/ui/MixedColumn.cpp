// Name : Long Duong 
// Date: 02/18/2020
// Description: Implementation of various non-templated functions that output the display width of various types.

#include "MixedColumn.h"

using namespace std;

size_t displayLength(const char* cStr)
{
    return strlen(cStr);
}

size_t displayLength(const wchar_t* cStr)
{
    return wcslen(cStr);
}

size_t displayLength(wstring WideStr)
{
    return WideStr.size();
}

size_t displayLength(char)
{
    return 1;
}


