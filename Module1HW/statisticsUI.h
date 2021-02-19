// Name : Long Duong 
// Date: 02/18/2020
// Description: A class that interacts with user to compute various statistics related metrics.

#ifndef PROJ1_STATISTICSUI_H
#define PROJ1_STATISTICSUI_H

#include <iostream>
#include "ui/OptionUI.h"
#include "statistics.h"
#include "ui/MixedColumn.h"

using namespace std::placeholders;

class StatsUI : public OptionUI, public Statistics<long>
{
public:
    // Preconditions: None.
    // Postconditions: Instance created
    StatsUI() = default;

    // Preconditions: Instance was initialized.
    // Postconditions: Output the  possible options a user has
    void showCurrentState() override;

    // Preconditions: Instance created.
    // Postconditions: Initialized optionCharacter with their respective handler.
    void init() override;

    // Preconditions: Expect a file path
    // Postconditions: Attempts to open file and display content on screen.
    void loadFileOptionHandler(std::string&& path);

    // Preconditions: Expect the name of the stat and the Function that retreive the statistics.
    // Postconditions: Return a functional object that will retrieve and display the stat upon invokcation.
    template <class WideString = std::wstring, typename Func>
    std::function<void(void)> statsDisplayAdapter(WideString name, Func statsGetter);

    // Preconditions: Expect the name of the stat and the Function that retreive the quartiles.
    // Postconditions: Return a functional object that will retrieve and display the quartiles upon invokcation.
    template <typename Func>
    std::function<void(void)> quartilesDisplayAdapter(Func quartilesGetter);

    // Preconditions: Expect the Function that retreive the frequency table.
    // Postconditions: Return a functional object that will retrieve and create a UI Table object on the heap.
    template <typename Func>
    Table* frequencyTableToUITable(Func frequencyTableGetter);

    // Preconditions: Expect the name of the stat and the Function that retreive the frequency table.
    // Postconditions: Return a functional object that will retrieve and display the table upon invokcation.
    template <typename Func>
    std::function<void(void)> frequencyTableDisplayAdapter(Func frequencyTableGetter);

    // Preconditions: None.
    // Postconditions: Display all stat then write summary to user-specified location.
    void displayAllResultAndWriteToFile();
};

#endif //PROJ1_STATISTICSUI_H
