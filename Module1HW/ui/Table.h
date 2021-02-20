// Names: Gabriela Lopez, Andrew Thompson, Duyen Tran, Long Duong, Christopher Gomez, Gia Minh Hoang, and Lincoln Nguyen
// Date: 02-12-21
// Description: A class that renders columns with nice formatting.

#ifndef PROJ1_TABLE_H
#define PROJ1_TABLE_H

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <sstream>
#include "configuration.h"
#include "AbstractColumn.h"

class Table 
{
public:
    int tableWidth;
    
    // Preconditions: Expects a vector of pointers to AbstractColum objects and a title
    // Postconditions: Instance initialzied with columns given
    Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title);

    // Preconditions: None
    // Postconditions: Instance initialized with columns given. If selfCentered is false, table is not centered. If it is true, center according to consoleWidth argument
    Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title, int _consoleWidth, bool selfCentered=true);
    
    // Preconditions: None
    // Postconditions: Outputs a string of n spaces
    std::wstring nSpace(int n) const;

    // Preconditions:  None 
    // Postconditions: Outputs a string of doublines with length of n
    std::wstring doubleLine(int n) const;

    // Preconditions: None
    // Postconditions: Outputs a string of singlines with length of n
    std::wstring singleLine(int n);
    
    // Preconditions: Table was properly initialized with columns
    // Postconditions: Content of columns contained is dumped into outstream.
    void dumpTableTo(std::wostream& os) const;
    
    // Preconditions: Table was properly initialized with heap allocated columns
    // Postconditions: All columns object contained is deallocated.
    ~Table();

private:
    int consoleWidth;
    std::wstring title;
    // Must use polymorphism because Columns
    // might contains items of different types.
    std::vector<AbstractColumn*> columns;
    int leftPadding, rightPadding;
};

#endif //PROJ1_TABLE_H
