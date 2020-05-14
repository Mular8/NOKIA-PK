#pragma once
#include "Messages/PhoneNumber.hpp"
#include <string.h>
namespace ue
{

using common::PhoneNumber;
//Opis klasy SMS w dokumencie na stronie 13
class ISms
{
public:
    virtual std::string decryption()=0;
    virtual std::string encryption()=0;
};

}
