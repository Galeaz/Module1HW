// Participant: Long Duong
// Date: 02-12-21
// Description: Implements methods that display choices and process user choices.

#include "statisticsUI.h"
#include "ui/configuration.h"

using namespace std;
using namespace config;
using namespace Group1DS;

void StatsUI::header()
{
    cout << '\n';
    cout << "\t\t\t" << char(201) << string(46, char(205)) << char(187) << '\n';
    cout << "\t\t\t" << char(186) << " CMPR131: Chapter 1 - Descriptive Statistics  " << char(186) << '\n';
    cout << "\t\t\t" << char(186) << "      \t\t    Made by:                   " << char(186) << '\n';
    cout << "\t\t\t" << char(186) << "   - Gabriela Lopez\t- Andrew Thompson      " << char(186) << '\n';
    cout << "\t\t\t" << char(186) << "   - Duyen Tran\t- Long Duong           " << char(186) << '\n';
    cout << "\t\t\t" << char(186) << "   - Christopher Gomez\t- Gia Minh Hoang       " << char(186) << '\n';
    cout << "\t\t\t" << char(186) << "   - Lincoln Nguyen                           " << char(186) << '\n';
    cout << "\t\t\t" << char(200) << string(46, char(205)) << char(188) << "\n\n";
}


void StatsUI::showCurrentState()
{
    header();
    auto* optionColumn1 = new MixedColumn (DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
    optionColumn1->addItems(
        L"A> Load data file",
        L"B> Minimum",
        L"C> Maximum",
        L"D> Range",
        L"E> Size",
        L"F> Sum",
        L"G> Mean",
        L"H> Median",
        L"I> Frequencies",
        L"J> Mode",
        L"K> Standard Deviation",
        L"L> Variance",
        L"W> Display result and write to file.",
        L"0> Return"
    );
    auto* optionColumn2 = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
    optionColumn2->addItems(
        L"M> Mid Range",
        L"N> Quartiles",
        L"O> Interquartile Range",
        L"P> Outliers",
        L"Q> Sum of Squares",
        L"R> Mean Absolute Deviation",
        L"S> Root Mean Square",
        L"T> Standard Error of the Mean",
        L"U> Coefficient of Variation",
        L"V> Relative Standard Deviation"
    );
    Table({ optionColumn1, optionColumn2 }, L"").dumpTableTo(wcout);
}


void StatsUI::init()
{
    this->terminateCharacter = '0';
    choiceCollector = CharParameter ("Option: ", [this](const char& c){ return c == terminateCharacter || (tolower(c) >= 'a' && tolower(c) <= 'w');});

    auto nonEmptyVector = shared_ptr<AbstractPrerequisite>( new RequireNonEmptyVector(ref(elements), "No elements in array"));

    addOption('a', bind(&StatsUI::loadFileOptionHandler, this, _1), StringParameter("Enter file path: "));
    addOption('b', statsDisplayAdapter(L"Minimum", bind(&Statistics::getMin, this))) .require(nonEmptyVector);
    addOption('c', statsDisplayAdapter(L"Maximum", bind(&Statistics::getMax, this))) .require(nonEmptyVector);
    addOption('d', statsDisplayAdapter(L"Range", bind(&Statistics::getRange, this))) .require(nonEmptyVector);
    addOption('e', statsDisplayAdapter(L"Size", bind(&Statistics::getSize, this))) .require(nonEmptyVector);
    addOption('f', statsDisplayAdapter(L"Sum", bind(&Statistics::getSum, this))) .require(nonEmptyVector);
    addOption('g', statsDisplayAdapter(L"Mean", bind(&Statistics::getMean, this))) .require(nonEmptyVector);
    addOption('h', statsDisplayAdapter(L"Median", bind(&Statistics::getMedian, this))).require(nonEmptyVector);
    addOption('i', frequencyTableDisplayAdapter(bind(&Statistics::getFrequencyTable, this))).require(nonEmptyVector);
    addOption('j', statsDisplayAdapter(L"Mode", bind(&Statistics::getMode, this))).require(nonEmptyVector);
    addOption('k', statsDisplayAdapter(L"Standard Deviation", bind(&Statistics::getStandardDeviation, this))).require(nonEmptyVector);
    addOption('l', statsDisplayAdapter(L"Variance", bind(&Statistics::getVariance, this))).require(nonEmptyVector);
    addOption('m', statsDisplayAdapter(L"Mid Range", bind(&Statistics::getMidRange, this))).require(nonEmptyVector);
    addOption('n', quartilesDisplayAdapter(bind(&Statistics::getQuartiles, this))).require(nonEmptyVector);
    addOption('o', statsDisplayAdapter(L"Interquartile Range", bind(&Statistics::getIQR, this))).require(nonEmptyVector);
    addOption('p', statsDisplayAdapter(L"Outliers", bind(&Statistics::getOutliers, this))).require(nonEmptyVector);
    addOption('q', statsDisplayAdapter(L"Sum of Squares", bind(&Statistics::getSumOfSquares, this))).require(nonEmptyVector);
    addOption('r', statsDisplayAdapter(L"Mean Absolute Deviation", bind(&Statistics::getMeanAbsoluteDeviation, this))).require(nonEmptyVector);
    addOption('s', statsDisplayAdapter(L"Root Mean Square", bind(&Statistics::getRootMeanSquare, this))).require(nonEmptyVector);
    addOption('t', statsDisplayAdapter(L"Standard Error of the Mean", bind(&Statistics::getStdErrorOfMean, this))).require(nonEmptyVector);
    addOption('u', statsDisplayAdapter(L"Coefficient of Variation", bind(&Statistics::getCoefficientOfVariation, this))).require(nonEmptyVector);
    addOption('v', statsDisplayAdapter(L"Relative Standard Deviation", bind(&Statistics::getRelativeStd, this))).require(nonEmptyVector);
    addOption('w', bind(&StatsUI::displayAllResultAndWriteToFile, this)).require(nonEmptyVector);
}

void StatsUI::loadFileOptionHandler(string&& path)
{
    Statistics::loadDataFromFilePath(path);
    wcout << "File opened successfully!" << endl;
    auto* numbers = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
    numbers->addItems(elements);
    auto table = Table({numbers}, L"Data");
    table.dumpTableTo(wcout);
    wcout << endl;
}

template <class WideString, typename Func>
function<void(void)> StatsUI::statsDisplayAdapter(WideString name, Func statsGetter)
{
    return [statsGetter, name] ()
    {
        auto stat = statsGetter();
        auto* nameColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", name);
        auto* equalColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", L"=");
        auto* statColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", stat);
        Table({nameColumn, equalColumn, statColumn}, L"Result: ").dumpTableTo(wcout);
    };
}

template <typename Func>
function<void(void)> StatsUI::quartilesDisplayAdapter(Func quartilesGetter)
{
    return [quartilesGetter] ()
    {
        Quartiles  quartiles = quartilesGetter();
        auto* nameColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", "Q1", "Q2", "Q3");
        auto* equalColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
        equalColumn->repeatedAddItems(vector<wstring>(3, L"-->"));
        auto* statsColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", quartiles.Q1, quartiles.Q2, quartiles.Q3);
        Table({nameColumn, equalColumn, statsColumn}, L"Quartiles: ").dumpTableTo(wcout);
    };
}

template <typename Func>
Table* StatsUI::frequencyTableToUITable(Func frequencyTableGetter)
{
    auto freqTable = frequencyTableGetter();
    vector<long> values;
    transform(freqTable.begin(), freqTable.end(), back_inserter(values), mem_fn(&FrequencyEntry::value));
    vector<long> frequency;
    transform(freqTable.begin(), freqTable.end(), back_inserter(frequency), mem_fn(&FrequencyEntry::frequency));
    vector<double> frequencyPercentage;
    transform(
        freqTable.begin(), freqTable.end(), 
        back_inserter(frequencyPercentage),
        [](const auto& entry){return 100 * mem_fn(&FrequencyEntry::frequencyPercentage)(entry);}
    );

    auto* valueColumn = new MixedColumn (DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"Values");
    valueColumn->repeatedAddItems(values);
    auto* freqColumn = new MixedColumn (DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"Frequency");
    freqColumn->repeatedAddItems(frequency);
    auto* freqPercentColumn = new MixedColumn (DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"Percentage");
    freqPercentColumn->repeatedAddItems(frequencyPercentage);
    return new Table({valueColumn, freqColumn, freqPercentColumn}, L"", -1, false);
}

template <typename Func>
function<void(void)> StatsUI::frequencyTableDisplayAdapter(Func frequencyTableGetter)
{
    return [this, frequencyTableGetter] ()
    {
        auto* table = frequencyTableToUITable(frequencyTableGetter);
        table->dumpTableTo(wcout);
        delete table;
    };
}

void StatsUI::displayAllResultAndWriteToFile()
{
    auto* statisticNameColumn = new MixedColumn (DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING,L"Concept");
    statisticNameColumn->addItems(
        L"Data",
        L"Minimum",
        L"Maximum",
        L"Range",
        L"Size",
        L"Sum",
        L"Mean",
        L"Median",
        L"Mode",
        L"Standard Deviation",
        L"Variance",
        L"Mid Range",
        L"Quartiles",
        L"Interquartile Range",
        L"Outliers",
        L"Sum of Squares",
        L"Mean Absolute Deviation",
        L"Root Mean Square",
        L"Standard Error of the Mean",
        L"Skewness",
        L"Kurtosis",
        L"Kurtosis Excess",
        L"Coefficient of Variation",
        L"Relative Standard Deviation",
        L"Frequency Table"
    );

    const auto& quartiles = getQuartiles();
    auto* quartileNames = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", "Q1", "Q2", "Q3");
    auto* arrowColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
    arrowColumn->repeatedAddItems(vector<const char*>(3, "-->"));
    auto* quartileValues = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"", quartiles.Q1, quartiles.Q2, quartiles.Q3);
    auto* quartileTable = new Table({quartileNames, arrowColumn, quartileValues}, L"", -1, false);

    auto* numbersColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"");
    numbersColumn->addItems(elements);
    auto* dataTable = new Table({numbersColumn}, L"", -1 , false);

    auto* statisticValueColumn = new MixedColumn(DEFAULT_LEFT_PADDING, DEFAULT_RIGHT_PADDING, L"Values");
    statisticValueColumn->addItems(
        dataTable,
        getMin(),
        getMax(),
        getRange(),
        getSize(),
        getSum(),
        getMean(),
        getMedian(),
        getMode(),
        getStandardDeviation(),
        getVariance(),
        getMidRange(),
        quartileTable,
        getIQR(),
        getOutliers(),
        getSumOfSquares(),
        getMeanAbsoluteDeviation(),
        getRootMeanSquare(),
        getStdErrorOfMean(),
        getSkewness(),
        getKurtosis(),
        getKurtosisExcess(),
        getCoefficientOfVariation(),
        to_wstring(getRelativeStd()) + L"%",
        frequencyTableToUITable(bind(&Statistics::getFrequencyTable, this))
    );

    auto* equalColumn = new MixedColumn(DEFAULT_LEFT_PADDING, 2, L"");
    equalColumn->repeatedAddItems(vector<const wchar_t*>(24, L"="));

    auto table = Table({statisticNameColumn, equalColumn, statisticValueColumn}, L"Statistics");
    table.dumpTableTo(wcout);

    auto filePath = StringParameter ("Enter file path: ").collectParam();
    auto outFile = wofstream (filePath);
    while (!outFile.is_open())
    {
        wcout << L"ERROR: Cannot open file. Try again." << endl;
        filePath = StringParameter ("Enter file path: ").collectParam();
        outFile = wofstream (filePath);
    }
    table.dumpTableTo(outFile);
    wcout << L"Summary was written to file." << endl;

}