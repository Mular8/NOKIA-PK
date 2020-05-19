#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"
#include "Sms/Sms.hpp"
namespace ue
{

class ISmsMock
{
    virtual std::string randomMessage();
    virtual Sms createSms();
};

}
