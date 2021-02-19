// Name : Long Duong 
// Date: 02/18/2020
// Description: Provides a standardized way to add pre-checks for each option in OptionUI.

#ifndef PROJ1_PREREQUISITE_H
#define PROJ1_PREREQUISITE_H


#include <map>
#include <vector>
#include <optional>
#include <functional>

using namespace std;

class AbstractPrerequisite
{
public:
    // Preconditions: Expect an error message
    // Postconditions: Instance initialized
    AbstractPrerequisite(const string& _errorMsg): errorMsg {_errorMsg}
    {}
    virtual ~AbstractPrerequisite() {} ;

    // Preconditions: None
    // Postconditions: Depends on derived class
    virtual bool isSatisfied() = 0;

    // Preconditions: None
    // Postconditions: Return errorMsg given.
    virtual const string getErrorMsg()
    {
        return errorMsg;
    }

private:
    string errorMsg;
};

class InvokeMethodRequirement : public AbstractPrerequisite
{
public:
    typedef function<bool(void)> CheckFunc_t;
    // Preconditions: expect a boolean checkFunction and an errorMessage
    // Postconditions: Instance initialized.
    InvokeMethodRequirement(CheckFunc_t&& _checkFunc,
                            const string& _errorMsg)
        :
        AbstractPrerequisite (_errorMsg),
        checkFunc {_checkFunc}
    {}
    ~InvokeMethodRequirement() override = default;

    // Preconditions: Instance was initialized with proper check function.
    // Postconditions: Return whether the conditions checked by CheckFunc is met.
    bool isSatisfied() override
    {
        return invoke(checkFunc);
    }
private:
    CheckFunc_t checkFunc;
};

template <typename OptionalType>
class RequireValuedOptional : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the optional needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireValuedOptional(reference_wrapper<OptionalType> _target,
                                   const string& _errorMsg) :
        InvokeMethodRequirement([_target]() { return _target.get().has_value(); }, _errorMsg ) {}
    virtual ~RequireValuedOptional() override {};
};

template <typename VecType>
class RequireNonEmptyVector : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the vector needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireNonEmptyVector(reference_wrapper<VecType> _target,
                                   const string& _errorMsg) :
        InvokeMethodRequirement([_target]() { return !_target.get().empty(); }, _errorMsg) {}
    virtual ~RequireNonEmptyVector() override {};
};

template <typename StringType>
class RequireNonEmptyString : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the string needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireNonEmptyString(reference_wrapper<StringType> _target,
                                   const string& _errorMsg) :
        InvokeMethodRequirement([_target] () { return !_target.get().empty() ;}) {}
    virtual ~RequireNonEmptyString() override {};
};

#endif //PROJ1_PREREQUISITE_H
