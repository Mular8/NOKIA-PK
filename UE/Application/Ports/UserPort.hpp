#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Database/ISmsDatabase.hpp"

namespace ue
{
enum class View{SMS_SENT, SMS_RECEIVED};
class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);

    void start(IUserEventsHandler& handler);
    void stop();
    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showReceivedSms() override;
private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    ISmsDatabase* db = nullptr;
};

}
