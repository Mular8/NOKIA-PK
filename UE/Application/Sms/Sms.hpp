#pragma once
#include "Messages/PhoneNumber.hpp"
#include <string.h>
namespace ue
{

using common::PhoneNumber;
//Opis klasy SMS w dokumencie na stronie 13
class Sms
{
public:
    Sms();
    Sms(PhoneNumber from, std::string text);
    long messageId;
    std::string message;
    PhoneNumber from;
    bool read;
};

}
