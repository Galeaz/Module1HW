// Names: Gabriela Lopez, Andrew Thompson, Duyen Tran, Long Duong, Christopher Gomez, Gia Minh Hoang, and Lincoln Nguyen
// Date: 02-12-21
// Description: Provides an abstract interface for objects contained in the Table class.

#ifndef PROJ1_ABSTRACTCOLUMN_H
#define PROJ1_ABSTRACTCOLUMN_H
#include <iostream>

using namespace std;

class AbstractColumn
{
public:
    // Preconditions: None
    // Postconditions: Instance is initialized.
    AbstractColumn() = default;

    // Preconditions: Instance was properly initialized
    // Postconditions: Depends on the derived class implementation.
    virtual ~AbstractColumn() {};
    
    // Preconditions: Instance was property initialized.
    // Postconditions: Return the width of the column.
    virtual const int getColumnWidth() const = 0;

    // Preconditions: Instance was properly initialized.
    // Postconditions: The number of entries in the column is returned.
    virtual const size_t getSize() = 0;

    // Preconditions: Instance was properly initialized with entries appened.
    // Postconditions: Print the next entry onto the outstream given.
    virtual void dumpNext(wostream& os) = 0;

    // Preconditions: Instance was properly initialized.
    // Postconditions: Reset internal state so dumpNext will start printing from the first entry.
    virtual void reset() = 0;
};

#endif //PROJ1_ABSTRACTCOLUMN_H
