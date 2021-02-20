// Names: Gabriela Lopez, Andrew Thompson, Duyen Tran, Long Duong, Christopher Gomez, Gia Minh Hoang, and Lincoln Nguyen
// Date: 02-12-21
// Description:  Provides a convenient class for collecting user input with validator.

#ifndef PROJ1_PARAMETER_H
#define PROJ1_PARAMETER_H

#include <string>
#include <optional>
#include "inputType.h"

using namespace std;

template <typename T>
class AbstractParameter
{
public:
    // Preconditions:  Expect a prompt
    // Postconditions: Instance created with prompt.
    explicit AbstractParameter(string&& _prompt) :
        prompt {_prompt},
        validator {nullopt}
    {}

    // Preconditions:  Expect prompt and input validator
    // Postconditions: Instance created with prompt and input validator
    AbstractParameter(string&& _prompt,
                      function<bool(const T&)> _validator) :
        prompt {_prompt},
        validator {_validator}
    {}

    ~AbstractParameter() = default;

    // Preconditions: Instance was properly initialized.
    // Postconditions: Continuously ask the user for data of the type given and validate if validator was provided.
    T collectParam() const
    {
        T input;
        do
        {
            input = inputType<T>(prompt);
            if (validator.has_value() && !validator.value()(input))
                cout << "ERROR: Input did not pass validator\'s check." << endl;
            else
                return input;
        } while (true);
    }
private:
    string prompt;
    optional<function<bool(const T&)>> validator;
};

using LongParameter = AbstractParameter<long>;
using DoubleParameter = AbstractParameter<double>;
using CharParameter = AbstractParameter<char>;
using StringParameter = AbstractParameter<string>;

#endif //PROJ1_PARAMETER_H
