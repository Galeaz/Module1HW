// Name : Long Duong 
// Date: 02/18/2020
// Description: Implements methods that outputs a table based on columns contained.

#include "Table.h"


Table::Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title) :
    columns {_columns},
    title {_title},
    tableWidth {0},
    consoleWidth {config::CONSOLE_WIDTH}
{
    // Center table
    tableWidth = std::transform_reduce(
        columns.cbegin(), columns.cend(),
        0,
        std::plus<int> (),
        [](const auto& a) { return a->getColumnWidth(); }
    );
    leftPadding = (config::CONSOLE_WIDTH - tableWidth) / 2;
    rightPadding = leftPadding;
}

Table::Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title, int _consoleWidth, bool selfCentered) :
    columns {_columns},
    title {_title},
    tableWidth {0}
{
    // Center table
    tableWidth = std::transform_reduce(
        columns.cbegin(), columns.cend(),
        0,
        std::plus<int> (),
        [](const auto& a) { return a->getColumnWidth(); }
    );

    if (!selfCentered)
    {
        consoleWidth = tableWidth;
    }
    else
    {
        consoleWidth = _consoleWidth;
    }
    leftPadding = (consoleWidth - tableWidth) / 2;
    rightPadding = leftPadding;
}

std::wstring Table::nSpace(int n) const
{
    return std::wstring(n, ' ');
}

std::wstring Table::doubleLine(int n) const
{
    return std::wstring(n, L'=');
}

std::wstring Table::singleLine(int n)
{
    return std::wstring(n, '_');
}

void Table::dumpTableTo(std::wostream& os) const
{
    if (!title.empty())
    {
        os << nSpace(leftPadding)
           << title
           << std::endl;

        os << nSpace(leftPadding)
           << doubleLine(consoleWidth - leftPadding - rightPadding)
           << std::endl;
    }

    for (std::size_t i = 0; i <= columns.at(0)->getSize(); i++)
    {
        os << nSpace(leftPadding);
        for (auto columnIt = columns.begin(); columnIt != columns.end(); columnIt++)
        {
            auto& column = *columnIt;
            std::wstringstream tmpOs;
            column->dumpNext(tmpOs);
            wchar_t t ;
            while (tmpOs.get(t))
            {
                if (t != '\n')
                {
                    os << t;
                }
                else
                {
                    auto previousColumnsWidth =
                    std::transform_reduce(
                    columns.begin(), columnIt,
                    leftPadding,
                    std::plus<>(),
                    [](const auto& col){ return col->getColumnWidth();}
                    );
                    os << t
                       << nSpace(previousColumnsWidth);
                }
            }
        }
        os << std::endl;
    }

    for (auto* column : columns)
        column->reset();
}

Table::~Table()
{
    std::destroy(columns.begin(), columns.end());
    for (AbstractColumn* columnPtr : columns)
        delete columnPtr;
}