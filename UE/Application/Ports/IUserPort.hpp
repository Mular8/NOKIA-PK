#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendSms(common::PhoneNumber from, std::string message) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showReceivedSms() = 0;
};

}
