// Participant: Long Duong and Gabriela Lopez
// Date: 02-12-21
// Description: A class that does various statistic metrics on a sorted array.

#ifndef PROJ1_STATISTICS_H
#define PROJ1_STATISTICS_H

#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <fstream>
#include "ui/Table.h"

using namespace std;

template <typename T>
class Statistics
{
public:
    using Quartiles = struct {
        optional<double> Q1, Q2, Q3;
    };

    using FrequencyEntry = struct {
        T value;
        long frequency;
        double frequencyPercentage;
    };

    // Preconditions: A path to a text file
    // Postconditions: Initialized the instance with data from text file or throw exception if file cannot be opened.
    void loadDataFromFilePath(string path)
    {
        ifstream statsFile(path, ios::in);
        if (statsFile.is_open())
        {
            clear();
            T currentValue;
            while (statsFile >> currentValue)
                elements.push_back(currentValue);
            sort(elements.begin(), elements.end());
        }
        else throw UIExcept("Cannot open file");
    }

    // Preconditions: None
    // Postconditions: Internal states are cleared to prepare for new data.
    void clear()
    {
        elements.clear();
        _meanCache.reset();
        _sumCache.reset();
        _varianceCache.reset();
        _quartilesCache.reset();
    }

    Statistics() :
        elements {}
    {}

    // Preconditions: Expect a vector of elements T
    // Postconditions: Instance initialized  with data in T
    Statistics(vector<T>&& elements) :
        elements {move(elements)}
    {
        sort(elements.begin(), elements.end());
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the minimum
    const T& getMin() const
    {
        return elements.front();
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return maximum
    const T& getMax() const
    {
        return elements.back();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return range
    const T getRange()
    {
        return getMax() - getMin();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return sum of all elements.
    const T& getSum() const
    {
        if (_sumCache.has_value())
            return _sumCache.value();
        else
        {
            _sumCache.emplace(accumulate(elements.cbegin(), elements.cend(), 0, plus<>()));
            return _sumCache.value();
        }
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return number of elements.
    long getSize() const
    {
        return elements.size();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the mean of all elements.
    const double& getMean() const
    {
        if (_meanCache.has_value())
            return _meanCache.value();
        else
        {
            _meanCache.emplace(static_cast<double>(getSum()) / getSize());
            return _meanCache.value();
        }
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return an optional that contains the median if exist and nullopt otherwise.
    optional<double> getMedian() const
    {
        return getMedianInRange(elements.begin(), elements.end());
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the mode.
    vector<T> getMode() const
    {
        auto freqTable = getFrequencyTable();
        auto maxEntry = max_element(freqTable.cbegin(), freqTable.cend(),
                                         [](const FrequencyEntry& entry1, const  FrequencyEntry& entry2)
                                         {
                                                return entry1.frequency < entry2.frequency;
                                         });
        auto modeElements = vector<T>();
        for (const auto& entry : freqTable)
        {
            if (entry.frequency >= maxEntry->frequency)
                modeElements.push_back(entry.value);
        }
        return modeElements;
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the variance
    const double& getVariance() const
    {
        if (_varianceCache.has_value())
            return _varianceCache.value();
        else
        {
            _varianceCache.emplace(
                transform_reduce(
                    elements.cbegin(), elements.cend(),
                    0.0,
                    plus<>(),
                    [this](const T& element) { return pow(element - this->getMean(), 2); }
                ) / (getSize() - 1)
            );
            return _varianceCache.value();
        }
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the standard deviation
    double getStandardDeviation() const
    {
        return sqrt(getVariance());
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the midRange
    double getMidRange() const
    {
        return (getMax() + getMin()) / 2.0;
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return a struct with 3 optionals for each quartiles that contains a value if the quartile exists.
    const Quartiles& getQuartiles() const
    {
        if (_quartilesCache.has_value())
            return _quartilesCache.value();
        else
        {
            if (getSize() % 2 == 0)
            {
                _quartilesCache.emplace(
                    Quartiles {
                        .Q1 = getMedianInRange(elements.cbegin(), elements.cbegin() + getSize() / 2),
                        .Q2 = getMedianInRange(elements.cbegin(), elements.cend()),
                        .Q3 = getMedianInRange(elements.cbegin() + getSize() / 2, elements.cend())
                    });
            }
            else
            {
                _quartilesCache.emplace(
                    Quartiles {
                        .Q1 = getMedianInRange(elements.cbegin(), elements.cbegin() + getSize() / 2),
                        .Q2 = getMedianInRange(elements.cbegin(), elements.cend()),
                        .Q3 = getMedianInRange(elements.cbegin() + getSize() / 2 + 1, elements.cend())
                    });
            }
            return _quartilesCache.value();
        }
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the IQR if it exists, otherwise nullopt
    optional<double> getIQR() const
    {
        auto& quartiles = getQuartiles();
        if (!quartiles.Q3.has_value() || !quartiles.Q1.has_value())
            return nullopt;
        return quartiles.Q3.value() - quartiles.Q1.value();
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return outlierFence if IQR exists, nullopt otherwise.
    optional<pair<double, double>> getOutlierFence() const
    {
        if (!getIQR().has_value()) return nullopt;
        const auto& q = getQuartiles();
        return make_pair(q.Q1.value() - 1.5 * getIQR().value(), q.Q3.value() + 1.5 * getIQR().value());
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return an array of outliers. 
    vector<T> getOutliers() const
    {
        auto outliers = vector<T>();
        if (!getOutlierFence().has_value()) return outliers;
        const auto& fence = getOutlierFence().value();
        copy_if(
            elements.cbegin(), elements.cend(),
            back_inserter(outliers),
            [&fence](const auto& e){ return e < fence.first || e > fence.second; }
        );
        return outliers;
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return sumOfSquares.
    double getSumOfSquares() const
    {
        return
        transform_reduce(
            elements.cbegin(), elements.cend(),
            0.0,
            plus<>(),
            [this](const T& element) { return pow(element - this->getMean(), 2);}
        );
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return mean absolute deviation.
    double getMeanAbsoluteDeviation() const
    {
        return
            transform_reduce(
                elements.cbegin(), elements.cend(),
                0.0,
                plus<>(),
                [this](const T& element) { return abs(element - this->getMean()); }
        ) / getSize();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return the root mean square
    double getRootMeanSquare() const
    {
        return
        sqrt(
            transform_reduce(
                elements.cbegin(), elements.cend(),
                0.0,
                plus<>(),
                [](const T& element) { return element * element; }
            ) / getSize()
        );
    }

    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return standard error of the mean
    double getStdErrorOfMean() const
    {
        return getStandardDeviation() / sqrt(getSize());
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return coefficient of variantion
    double getCoefficientOfVariation() const
    {
        return getStandardDeviation() / getMean();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return relative standard deviation.
    double getRelativeStd() const
    {
        return (100.0 * getStandardDeviation()) / getMean();
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return skewness
    optional<double> getSkewness() const
    {
        double n = getSize();
        if (n * pow(getStandardDeviation(), 3) == 0.0 || (n - 1)*(n - 2) == 0.0)
            return nullopt;
        double coefficient = static_cast<double>(n) / ((n - 1) * (n - 2));
        return
        coefficient * transform_reduce(
            elements.cbegin(), elements.cend(),
            0.0,
            plus<>(),
            [this](const double& e)
            {
                return pow((e - this->getMean())/(getStandardDeviation()), 3);
            }
        );
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return kurtosis.
    optional<double> getKurtosis() const
    {
        double n = getSize();
        if (pow(getStandardDeviation(), 4) == 0.0 || (n - 1)*(n - 2)*(n - 3) == 0.0)
            return nullopt;
        double coefficient = n * (n + 1) / ((n - 1) * (n - 2) * (n - 3));
        return
        coefficient * transform_reduce(
            elements.cbegin(), elements.cend(),
            0.0,
            plus<>(),
            [this](const auto& e){ return pow(e - this->getMean(), 4); }
        ) / pow(getStandardDeviation(), 4);
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return kurtosis excess
    optional<double> getKurtosisExcess() const
    {
        double n = getSize();
        if (!getKurtosis().has_value() || (n - 2) * (n - 3) == 0)
            return nullopt;
        double adjustmentTerm = -3* (n - 1) * (n - 1) / ((n - 2) * (n - 3));
        return getKurtosis().value() + adjustmentTerm;
    }
    
    // Preconditions: Instance was initialized with more than 0 element.
    // Postconditions: Return a vector of struct that contains value, frequency, and frequency percentage.
    vector<FrequencyEntry> getFrequencyTable() const
    {
        auto frequencyTable = vector<FrequencyEntry> ();
        auto it = elements.cbegin();
        for (; it != elements.cend(); it++)
        {
            auto newEntry = FrequencyEntry{
                .value = *it,
                .frequency = 1,
                .frequencyPercentage = -1
            };

            if (std::next(it) != elements.cend())
            {
                while (std::next(it) != elements.cend() && *std::next(it) == newEntry.value)
                {
                    newEntry.frequency++;
                    it++;
                }
            }
            frequencyTable.push_back(newEntry);
        }

        long totalFrequency = transform_reduce(
            frequencyTable.cbegin(), frequencyTable.cend(),
            0,
            plus<>(),
            [](const FrequencyEntry& entry) { return entry.frequency; }
        );
        for (auto& entry: frequencyTable)
        {
            entry.frequencyPercentage = static_cast<double>(entry.frequency) / totalFrequency;
        }
        return frequencyTable;
    }

protected:
    vector<T> elements;

    // caches for statistics that are used many times
    mutable optional<T> _sumCache;
    mutable optional<double> _meanCache;
    mutable optional<double> _varianceCache;
    mutable optional<Quartiles> _quartilesCache;

    /// Helpers
    optional<double> getMedianInRange(decltype(elements.cbegin()) lowBound, decltype(elements.cbegin()) highBound) const
    {
        ptrdiff_t distance = std::distance(lowBound, highBound);
        if (distance <= 1)
            return nullopt;

        if (distance % 2 == 0)
        {
            auto medianIndex = distance / 2 + std::distance(elements.cbegin(), lowBound);
            return make_optional((elements.at(medianIndex) + elements.at(medianIndex - 1)) / 2.0);
        }
        else
        {
            auto medianIndex = distance / 2 + std::distance(elements.cbegin(), lowBound);
            return make_optional(elements.at(medianIndex));
        }
    }
};

#endif //PROJ1_STATISTICS_H
