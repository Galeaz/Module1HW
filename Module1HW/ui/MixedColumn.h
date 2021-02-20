// Participant: Long Duong
// Date: 02-12-21
// Description: Provide a column class that accepts an arbitrary number of parameters of various types.


#ifndef PROJ1_MIXEDCOLUMN_H
#define PROJ1_MIXEDCOLUMN_H

#include <iostream>
#include <string>
#include <type_traits>
#include <optional>
#include <iomanip>
#include <functional>
#include <cassert>
#include "Table.h"
#include "AbstractColumn.h"
#include "configuration.h"

using namespace std;

size_t displayLength(const char* cStr);
size_t displayLength(const wchar_t* cStr);
size_t displayLength(wstring WideStr);
size_t displayLength(char);

// Preconditions: A numerical type.
// Postconditions: The width it takes to display the value on screen.
template<typename IntegerType,
    typename enable_if<is_integral<IntegerType>::value, int>::type = 0>
    size_t displayLength(const IntegerType& var)
{
    if (var < 0) return static_cast<size_t>(log10(-var) + 1 + 1);
    else if (var == 0) return 1;
    else return static_cast<size_t>(log10(var) + 1);
}

// Preconditions: A floating type (float, double, ...).
// Postconditions: The width it takes to display the value on screen.
template<typename FloatType,
         typename enable_if<is_floating_point<FloatType>::value, int>::type = 0>
size_t displayLength(const FloatType& var)
{
    //if (long(var) == var)
    //{
    //    return displayLength(long(var));
    //}
    return displayLength((long)var) + config::FLOAT_NUMBER_DIGITS + 1;
}


// Preconditions: A vector that contains any type.
// Postconditions: The width it takes to display the vector's content on screen.
template <typename T>
size_t displayLength(const vector<T>& vec)
{
    size_t totalLength = 0;
    if (vec.empty())
    {
        return displayLength("None");
    }
    for (auto it = vec.cbegin(); it != vec.cend(); it++)
    {
        if (distance(vec.cbegin(), it) > config::ARRAY_MAX_WRAPPING_LENGTH)
        {
            totalLength + string(", ...").size();
            return totalLength;
        }
        totalLength += displayLength(*it) + string(", ").size();
    }
    totalLength -= string(", ").size();
    return totalLength;
}


class MixedColumn : public AbstractColumn
{
public:

    // Preconditions: Horizontal paddings and titles
    // Postconditions: Instance is ready to receive entries.
    MixedColumn(int _leftPadding, int _rightPadding, wstring&& _title) :
        leftPadding {_leftPadding},
        rightPadding {_rightPadding},
        title {_title},
        maxCharLength {0},
        titlePrinted {false}
    {}


    // Preconditions: Horizontal paddings, title, and a parameter packs of various parameters of various types.
    // Postconditions: Instance is initialized with paddings and title given and all entries are internally added.
    template <typename ...ItemTypes>
    MixedColumn(int _leftPadding, int _rightPadding, wstring&& _title, ItemTypes... items) :
        leftPadding {_leftPadding},
        rightPadding {_rightPadding},
        title {_title},
        maxCharLength {0},
        titlePrinted {false}
    {
        addItems(items...);
    }
    

    // Preconditions: A vector of items of the same type.
    // Postconditions: All items in the vector are added as individual entries.
    template <typename T>
    void repeatedAddItems(vector<T> _items)
    {
        for (auto item: _items)
            addItems(item);
    }


    // Preconditions: A parameter packs of various types.
    // Postconditions: All items are added as entries in the column.
    template <typename ...ItemTypes>
    void addItems(ItemTypes... items);


    // Preconditions: NA.
    // Postconditions: Table is ready to be dumped to various outStream.
    template<>
    void addItems()
    {
        currentIt = items.begin();
        maxCharLength = max(maxCharLength, title.size());
    }
    

    // Preconditions: Expects a pointer to a table object.
    // Postconditions: Table is added as one of the entry in the column. 
    template <typename ...OtherTypes>
    void addItems(Table* table, OtherTypes... otherArgs)
    {
        maxCharLength = max(maxCharLength, static_cast<size_t>(table->tableWidth));
        items.push_back(
            [tablePtr = shared_ptr<Table>(table)] (wostream& os)
            {
                tablePtr->dumpTableTo(os);
            }
        );
        addItems(otherArgs...);
    }

    // Preconditions: Expect a vector type.
    // Postconditions: The vector is added as an entry in the column.
    template <typename T, typename ...OtherType>
    void addItems(vector<T> vec, OtherType... otherArgs)
    {
        maxCharLength = max(maxCharLength, displayLength(vec));
        items.push_back(
            [this, vec](wostream& os)
            {
                if (vec.empty())
                    os << "None";
                else
                {
                    for (auto it = vec.cbegin(); it != --vec.cend(); it++)
                    {
                        if (it != vec.cbegin()
                            && distance(vec.cbegin(), it) % config::ARRAY_MAX_WRAPPING_LENGTH == 0)
                            os << endl;
                        os << *it << L", ";
                    }
                    os << vec.back();
                }
                os << nSpace(maxCharLength - displayLength(vec) + rightPadding);
            }
        );
        addItems(otherArgs...);
    }

    // Preconditions: Expects an optional type.
    // Postconditions: The optional type is added as an entry in the column.
    template <typename T, typename ...OtherTypes>
    void addItems(optional<T> op, OtherTypes... otherArgs)
    {
        if (op.has_value())
            maxCharLength = max(maxCharLength, displayLength(op.value()));
        else
            maxCharLength = max(maxCharLength, displayLength(L"None"));
        items.push_back(
            [this, op](wostream& os)
            {
                if (op.has_value())
                    os << op.value() << nSpace(maxCharLength - displayLength(op.value()) + rightPadding);
                else
                    os << L"None" << nSpace(maxCharLength - displayLength(L"None") + rightPadding);
            }
        );
        addItems(otherArgs...);
    }
    

    // Preconditions: Expects a c-string type.
    // Postconditions: The string is added as an entry in the column. 
    template <typename ...OtherTypes>
    void addItems(const char* str, OtherTypes... otherArgs)
    {
        maxCharLength = max(maxCharLength, displayLength(str));
        items.push_back(
            [this, str](wostream& os)
            {
                os << str << nSpace(maxCharLength - displayLength(str) + rightPadding);
            }
        );
        addItems(otherArgs...);
    }

    // Preconditions: A wide c-string type.
    // Postconditions: The wide c-string is added as an entry in the column.
    template <typename ...OtherTypes>
    void addItems(const wchar_t* str, OtherTypes... otherArgs)
    {
        maxCharLength = max(maxCharLength, displayLength(str));
        items.push_back(
        [this, str](wostream& os)
        {
            os << str << nSpace(maxCharLength - displayLength(str) + rightPadding);
        }
        );
        addItems(otherArgs...);
    }

    // Preconditions: Expects a cpp-wide-string.
    // Postconditions: cpp-wide-string is added as an entry in the column.
    template <typename ...OtherTypes>
    void addItems(wstring str, OtherTypes... otherArgs) {
        maxCharLength = max(maxCharLength, displayLength(str));
        items.push_back(
        [this, str](wostream &os) {
            os << str << nSpace(maxCharLength - displayLength(str) + rightPadding);
        }
        );
        addItems(otherArgs...);
    }

    // Preconditions: Expects an numeric type.
    // Postconditions: Numeric value is added as an entry in the column.
    template <typename IntegerType,
              typename enable_if<is_integral<IntegerType>::value, int>::type = 0,
              typename ...OtherType>
    void addItems(IntegerType integer, OtherType... otherArgs)
    {
        maxCharLength = max(maxCharLength, displayLength(integer));
        items.push_back(
            [this, integer](wostream& os)
            {
                os << integer << nSpace(maxCharLength - displayLength(integer) + rightPadding);
            }
        );
        addItems(otherArgs...);
    }

    // Preconditions: Expect a floating type.
    // Postconditions: Floating value is added as an entry in the column with precision truncated based on value in config.
    template <typename FloatingType,
              typename enable_if<is_floating_point<FloatingType>::value, int>::type = 0,
              typename ...OtherTypes>
    void addItems(FloatingType floatVar, OtherTypes... otherArgs)
    {
        maxCharLength = max(maxCharLength, displayLength(floatVar));
        items.push_back(
            [this, floatVar](wostream& os)
            {
                os << fixed << setprecision(config::FLOAT_NUMBER_DIGITS)
                    << floatVar
                    << nSpace(maxCharLength - displayLength(floatVar) + rightPadding);
            }
        );
        addItems(otherArgs...);
    }
    

    // Preconditions:  Expects an integer
    // Postconditions: Outputs a space of length equals to the integer given.
    wstring nSpace(int n)
    {
        /// Call to nSpace instead of setw is absolutely **_necessary_**
        /// because the Column class requires explicit and granular space management
        /// in order to function properly.
        assert(n >= 0);
        return wstring(n, L' ');
    }
    

    // Preconditions: Expects an outputStream.
    // Postconditions: Dump the next entry in the column into outputStream given.
    void dumpNext(wostream& os)
    {
        if (currentIt == items.cend())
            return;

        if (!titlePrinted && !title.empty())
        {
            os << nSpace(leftPadding)
               << title
               << nSpace(maxCharLength - title.size() + rightPadding);
            titlePrinted = true;
            return;
        }
        
        os << nSpace(leftPadding);
        invoke(*currentIt, os);

        currentIt++;
    }
    

    // Preconditions: Instance was properly initizalied.
    // Postconditions: The width of the entry column with padding is returned. 
    const int getColumnWidth() const override
    {
        return leftPadding + maxCharLength + rightPadding;
    }

    // Preconditions: Instance was properly initialized
    // Postconditions: The number of entries is returned.
    const size_t getSize() override
    {
        return items.size();
    }


    // Preconditions: Instance was properly constructed.
    // Postconditions: Reset the column so that dumpNext starts printing from the beginning entry again.
    void reset() override
    {
        currentIt = items.cbegin();
        titlePrinted = false;
    }

private:
    vector<function<void(wostream&)>> items;
    int leftPadding, rightPadding;
    size_t maxCharLength;
    wstring title;
    bool titlePrinted;

    decltype(items.cbegin()) currentIt;
};


#endif //PROJ1_MIXEDCOLUMN_H
