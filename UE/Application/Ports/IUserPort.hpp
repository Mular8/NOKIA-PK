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
    virtual void showNewSms() = 0;
    virtual void showSmsList() = 0;
    virtual void showMenu() = 0;
    virtual void showSms(int id) = 0;
    virtual void showComposeSmsMode() = 0;
    virtual void showSmsReceived() = 0;
    virtual void showSentSMSList() = 0;
    virtual void showSentSMS(int id) = 0;
    virtual std::string encrypted(std::string sms) = 0;
    virtual std::string decrypted(std::string sms) = 0;
};

}
