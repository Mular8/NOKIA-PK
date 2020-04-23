#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"
#include "ISmsMock.hpp"
#include "Messages/PhoneNumber.hpp"
namespace ue
{

class SmsMock : ISmsMock
{
    using Value = std::uint8_t;
public:
    SmsMock()
    {
        srand(time(0));
    }
    std::string randomMessage() override
    {
        std::string temp;
        std::string mozliwosci="abcdefghijklmnoprstuwxyzABCDEFGHIJKLMNOPRSTUWXYZ";
        int ilosc_znakow=rand()%20+5;
        for(int i=0;i<ilosc_znakow;i++)
            temp.push_back(mozliwosci[rand()%mozliwosci.size()]);
        return temp;
    }
    Sms createSms()override
    {
        Sms sms;
        int temp=rand()%254+1;
        int temp2=rand()%254+1;
        sms.to=PhoneNumber{static_cast<Value>(temp)};
        sms.from=PhoneNumber{static_cast<Value>(temp2)};
        sms.message=randomMessage();
        sms.accepted=false;
        sms.encrypion_code=3;
        return sms;
    }
};

}
