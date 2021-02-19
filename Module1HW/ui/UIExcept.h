// Name : Long Duong 
// Date: 02/18/2020
// Description: The exception class thrown by various items in UI.

#ifndef PROJ1_UIEXCEPT_H
#define PROJ1_UIEXCEPT_H

#include <exception>
#include <string>

class UIExcept : public std::exception
{
public:
    UIExcept(const char* _msg) : msg {_msg}
    {}
    UIExcept(std::string _msg) : msg {_msg}
    {}
    std::string what() {return msg;}
private:
    std::string msg;
};

#endif //PROJ1_UIEXCEPT_H
